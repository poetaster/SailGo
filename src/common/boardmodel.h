#ifndef BOARDMODEL_H
#define BOARDMODEL_H

#include <QAbstractTableModel>
#include <QDebug>
#include <vector>

#include "common.h"
#include "moveAnalysis.h"

class MoveAnalysis;

class BoardModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit BoardModel(int rows = 13, int columns = 13, QObject *parent = 0);

    enum BoardRoles {
        GridRole = Qt::UserRole+1,
        PieceRole,
        TerritoryRole,
        NoteRole
    };

    enum PieceState {
        NoPiece = 0,
        WhitePiece,
        BlackPiece
    };

	 inline piece_t operator[] (int i) { return p_pieces[i]; }

    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    int columnCount(const QModelIndex & parent = QModelIndex()) const;
	 unsigned int nslotsCount() const;

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    QHash<int, QByteArray> roleNames() const;

    QModelIndex linearToGridIndex(const QModelIndex linIdx) const;
    void linearToGridIndex(int linearIndex, int * row, int * column);
    QModelIndex gridToLinearIndex(const QModelIndex gridRow) const;
    int gridToLinearIndex(int row, int column);

    void setPiece(int row, int column, PieceState state);
    void setPiece(int linearIndex, PieceState state);
	 void setPieceTmp(int linearIndex, piece_t state);
	 void prisoner(int linearIndex);

	 void setForbiddenPlay(int linearIndex);
    bool isForbidden(int linearIndex);

    bool isEmpty(int row, int column);
    bool isEmpty(int linearIndex);
signals:

public slots:

private:
    int nrows_;
    int ncolumns_;
	 int nslots;
    piece_t * p_pieces;
	 int forbidden; // to avoid recursive play
};

#endif // BOARDMODEL_H
