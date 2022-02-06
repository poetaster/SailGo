#include "abstractboardcontroller.h"

AbstractBoardController::AbstractBoardController(BoardModel * model, QObject *parent) :
    QObject(parent)
{
    this->model_ = model;
    this->nextPlayer_ = BlackPlayer;
    this->analysis = new MoveAnalysis(model);
}

AbstractBoardController::~AbstractBoardController()
{
	delete analysis;
}

void AbstractBoardController::playMove(int linearIndex)
{
	if(!model_->isEmpty(linearIndex) || model_->isForbidden(linearIndex) || !analysis->moveCorrect(this->nextPlayer_, linearIndex)) {
		qDebug("Not playable.");
		return;
	}
	this->model_->setPiece(linearIndex, this->nextPlayer_ == WhitePlayer ? model_->WhitePiece : model_->BlackPiece);
	analysis->prisoners();
    switchPlayer();
}

/* This should  be calculated. It's fixed to the 13x13 size as such */

void AbstractBoardController::resetBoard()
{
    qDebug("Reset");
    int n = 0;
    while (n < 169 ) {
        this->model_->setPiece(n, model_->NoPiece);
        n++;
    }
    // reset the totals
    Q_EMIT blackTotalChanged();
    Q_EMIT whiteTotalChanged();
}

QString AbstractBoardController::getBlacks()
{
    this->_blackTotal =  this->model_->getBlackPieces();
    return QString::number(this->_blackTotal);
}

QString AbstractBoardController::getWhites()
{
    this->_whiteTotal =  this->model_->getWhitePieces();
    return QString::number(this->_whiteTotal);
}

void AbstractBoardController::playMove(int line, int column)
{
	 playMove(model_->gridToLinearIndex(line, column));
}

QString AbstractBoardController::nextPlayer()
{
    QString player;

    player = nextPlayer_ == WhitePlayer ? "white" : "black";

    //getBlacks();
    //getWhites();
    Q_EMIT blackTotalChanged();
    Q_EMIT whiteTotalChanged();

    return player;
}

player_t AbstractBoardController::nextPlayerIndex()
{
	return nextPlayer_;
}

void AbstractBoardController::switchPlayer()
{
    this->nextPlayer_ = this->nextPlayer_ == WhitePlayer ? BlackPlayer : WhitePlayer;
    emit nextPlayerChanged();
}
