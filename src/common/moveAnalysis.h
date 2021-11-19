#ifndef _MOVEAN_H
#define _MOVEAN_H
#include <vector>

#include "boardmodel.h"
#include "common.h"

class BoardModel;

class MoveAnalysis
{
	public:
	bool isCorrect;
	player_t player;

	MoveAnalysis(BoardModel *b);
	~MoveAnalysis();
	void move(player_t p, int i);
	bool moveCorrect(player_t p, int i);
	void prisoners();

	private:
	static int dirs[4][2];
	BoardModel *board;
	std::vector<int> captives;

	struct NeighB {
		unsigned int nb, pos, i;
		slot_t idx[4];
		slot_t *ptr;
		void possibles(unsigned int pos_, unsigned int nbCol, unsigned int nbPos);
		inline void operator++ () { i++; ptr++; }
		inline bool more() { return i < nb; };
	};

	class Group {
		public:
		unsigned int nb, nb_freedom;
		std::vector<slot_t> places;

		Group(BoardModel*);
		~Group();
		void reset();

		void start(player_t p, slot_t s);

		private:
		BoardModel *board;
		player_t player;
		bool* done;

		void recur(slot_t);
	};

	Group *group;
	NeighB neig;
};
#endif
