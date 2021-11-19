#include <iostream>

#include "common.h"
#include "moveAnalysis.h"

using namespace std;

int MoveAnalysis::dirs[4][2] = {{ -1, 0 }, { 0, 1 }, { 1, 0 }, { 0, -1 }};

MoveAnalysis::MoveAnalysis(BoardModel *b)
{
	board = b;
	group = new Group(b);
}

MoveAnalysis::~MoveAnalysis()
{
	delete group;
}

void MoveAnalysis::move(player_t p, int pos)
{
	isCorrect = false;
	captives.clear();
	player = p;
	player_t otherPlayer = (p == 1) ? 2 : 1;

	neig.possibles(pos, board->columnCount(), board->nslotsCount());

	board->setPieceTmp(pos, player);
	for(; neig.more(); ++neig) if ((*board)[*neig.ptr] == otherPlayer) {
		group->start(otherPlayer, *neig.ptr);
		if (group->nb_freedom == 0) {
			captives.reserve(captives.size() + group->places.size());
			captives.insert(captives.end(), group->places.begin(), group->places.end());
		}
	}
	board->setPieceTmp(pos, 0);
	
	if (captives.size() > 0) {
		isCorrect = true;
		return;
	}

	group->start(player, pos);
	qDebug("groupe nb:%u, freedom:%u", group->nb, group->nb_freedom);
	isCorrect = group->nb_freedom > 0;
}

void MoveAnalysis::prisoners()
{
	for (auto p : captives) {
		board->prisoner(p);
	}
	if (captives.size() == 1) board->setForbiddenPlay(captives.front());
	else board->setForbiddenPlay(-1);
}

bool MoveAnalysis::moveCorrect(player_t p, int pos)
{
	if ((*board)[pos] != 0) return false;
	move(p, pos);
	return isCorrect;
}

/* possibles neighbours struct */

void MoveAnalysis::NeighB::possibles(unsigned int pos_, unsigned int nbCol, unsigned int nbPos)
{
	pos = pos_;
	nb = i = 0;
	ptr = idx;

	if (pos >= nbCol) idx[nb++] = pos - nbCol;
	if (pos + nbCol < nbPos) idx[nb++] = pos + nbCol;
	if (pos % nbCol < nbCol - 1) idx[nb++] = pos + 1;
	if (pos % nbCol > 0) idx[nb++] = pos - 1;
}

/* Group class */

MoveAnalysis::Group::Group(BoardModel *b)
{
	board = b;
	done = new bool[board->nslotsCount()];
}

MoveAnalysis::Group::~Group()
{
	delete[] done;
}

void MoveAnalysis::Group::reset()
{
	nb = nb_freedom = 0;
	std::fill(done, done + board->nslotsCount(), 0);
	places.clear();
}

void MoveAnalysis::Group::start(player_t p, slot_t s)
{
	reset();
	player = p;
	recur(s);
}

void MoveAnalysis::Group::recur(slot_t s)
{
	// add current
	places.push_back(s);
	done[s] = true;
	nb++;

	// look neighbours
	NeighB neig;
	neig.possibles(s, board->columnCount(), board->nslotsCount());
	for(; neig.more(); ++neig) {
		if (done[*neig.ptr]) continue;
		done[*neig.ptr] = true;
		const piece_t p = (*board)[*neig.ptr];
		if (p == BoardModel::NoPiece) nb_freedom++;
		else if (p == player) recur(*neig.ptr);
	}
}
