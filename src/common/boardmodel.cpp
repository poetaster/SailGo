#include "boardmodel.h"
#include "moveAnalysis.h"

BoardModel::BoardModel(int rows, int columns, QObject *parent) :
    QAbstractTableModel(parent)
{
    this->nrows_ = rows;
    this->ncolumns_ = columns;
     this->nslots = rows * columns;

    p_pieces = (piece_t *) calloc(this->nslots, sizeof(piece_t));
	 this->forbidden = -1;
}

QHash<int, QByteArray> BoardModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[GridRole] = "squareState";
    roles[PieceRole] = "pieceState";
    roles[TerritoryRole] = "territory";
    roles[NoteRole] = "note";
    return roles;
}

void BoardModel::setPiece(int row, int column, PieceState state)
{
    p_pieces[gridToLinearIndex(row, column)] = state;

    QModelIndex topLeft = this->createIndex(row, column);
    QModelIndex bottomRight = this->createIndex(row, column);

    emit this->dataChanged(topLeft, bottomRight);
}

void BoardModel::setPiece(int linearIndex, PieceState state)
{
    qDebug() << "Played " << ((state == WhitePiece) ? "white" : "black");
    p_pieces[linearIndex] = state;

    int row;
    int column;
    linearToGridIndex(linearIndex, &row, &column);

    QModelIndex topLeft = this->createIndex(row, column);
    QModelIndex bottomRight = this->createIndex(row, column);

    emit this->dataChanged(topLeft, bottomRight);
}

int BoardModel::getBlackPieces()
{
    int totalPieces = 0;
    int n = 0;
    while (n < 169 ) {
        if (p_pieces[n] == BlackPiece) {
            totalPieces++ ;
        }
        n++;
    }
    return totalPieces;
}

int BoardModel::getWhitePieces()
{
    int totalPieces = 0;
    int n = 0;
    while (n < 169 ) {
        if (p_pieces[n] == WhitePiece) {
            totalPieces++ ;
        }
        n++;
    }
    return totalPieces;
}

void BoardModel::setPieceTmp(int linearIndex, piece_t state)
{
	p_pieces[linearIndex] = state;
}

void BoardModel::prisoner(int linearIndex)
{
	setPiece(linearIndex, NoPiece);
}

void BoardModel::setForbiddenPlay(int linearIndex)
{
	forbidden = linearIndex;
}

bool BoardModel::isForbidden(int linearIndex)
{
	return linearIndex == forbidden;
}

bool BoardModel::isEmpty(int row, int column)
{
    return (p_pieces[gridToLinearIndex(row, column)] == NoPiece);
}

bool BoardModel::isEmpty(int linearIndex)
{
    return (p_pieces[linearIndex] == NoPiece);
}

int BoardModel::rowCount(const QModelIndex & parent) const
{
    return this->nrows_;
}

int BoardModel::columnCount(const QModelIndex & parent) const
{
    return this->ncolumns_;
}

unsigned int BoardModel::nslotsCount() const
{
	return this->nslots;
}

QVariant BoardModel::data(const QModelIndex & index, int role) const
{
    QString state;	// grid state

    QModelIndex linearIndex = gridToLinearIndex(index);

    int linearRow = linearIndex.row();
    int row = index.row();
    int column = index.column();

    u_int8_t piece = p_pieces[linearRow];

    switch(role){
            case GridRole:
                if((row == 0) && (column == 0)){
                    state = "TopLeft";
                }else if((row == 0) && (column < columnCount()-1)){
                    state = "Top";
                }else if((row == 0) && (column == columnCount()-1)){
                    state = "TopRight";
                }else if((row == rowCount()-1) && (column == 0)){
                    state = "BottomLeft";
                }else if((row == rowCount()-1) && (column == columnCount()-1)){
                    state = "BottomRight";
                }else if(column == 0){
                    state = "Left";
                }else if(column == columnCount()-1){
                    state = "Right";
                }else if(row == rowCount()-1){
                    state = "Bottom";
                }else{
                    state = "Normal";
                }

                return state;
            case PieceRole:
                if(piece == NoPiece){
                    return QString("empty");
                }else if(piece == BlackPiece){
                    return QString("black");
                }else if(piece == WhitePiece){
                    return QString("white");
                }else return QString("empty");

            case TerritoryRole:
                return QString("neutral");
            case NoteRole:
                return QString("");
            default:
                return QVariant();
        }

    return QVariant();
}

QModelIndex BoardModel::gridToLinearIndex(const QModelIndex gridIdx) const
{
    int linearRow = 0;
    int linearColumn = 0;

    linearRow = gridIdx.row() * this->columnCount() + gridIdx.column();

    QModelIndex linIdx = this->createIndex(linearRow, linearColumn);

    return linIdx;
}

int BoardModel::gridToLinearIndex(int row, int column)
{
    int linearRow = 0;

    linearRow = row * this->columnCount() + column;

    return linearRow;
}



QModelIndex BoardModel::linearToGridIndex(const QModelIndex linIdx) const
{
    int tableRow = 0;
    int tableColumn = 0;

    tableRow = linIdx.row() / this->columnCount();
    tableColumn = linIdx.row() % this->columnCount();

    QModelIndex tableIdx = this->createIndex(tableRow, tableColumn);

    return tableIdx;
}

void BoardModel::linearToGridIndex(int linearIndex, int *row, int *column)
{
    *row = linearIndex / this->columnCount();
    *column = linearIndex % this->columnCount();
}
