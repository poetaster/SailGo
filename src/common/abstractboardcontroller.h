#ifndef ABSTRACTBOARDCONTROLLER_H
#define ABSTRACTBOARDCONTROLLER_H

#include <QObject>

#include "common.h"
#include "boardmodel.h"


class AbstractBoardController : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString nextPlayer READ nextPlayer NOTIFY nextPlayerChanged)

public:
    explicit AbstractBoardController(BoardModel * model, QObject *parent = 0);
	 ~AbstractBoardController();
    int blackCount;
    int whiteCount;
    Q_INVOKABLE void playMove(int linearIndex);
    Q_INVOKABLE void playMove(int line, int column);
    Q_INVOKABLE void resetBoard();
    // abusing the controller, this could be 100% model.
    Q_INVOKABLE int getBlacks();
    Q_INVOKABLE int getWhites();

    QString nextPlayer();
    player_t nextPlayerIndex();
    void switchPlayer();

signals:
    QString moveForbidden();
    int playerPassed();
    void nextPlayerChanged();

public slots:

private:
    enum Player {
        WhitePlayer = 1,
        BlackPlayer = 2
    };
    player_t nextPlayer_;
    BoardModel * model_;
    MoveAnalysis *analysis;

};

#endif // ABSTRACTBOARDCONTROLLER_H
