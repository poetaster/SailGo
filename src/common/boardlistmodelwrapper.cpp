#include "boardlistmodelwrapper.h"

BoardListModelWrapper::BoardListModelWrapper(BoardModel * model, QObject *parent) :
    QAbstractListModel(parent)
{
    this->model_ = model;

    connect(model_, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(dataChangedCB(QModelIndex,QModelIndex)));
}

QHash<int, QByteArray> BoardListModelWrapper::roleNames() const
{
    return this->model_->roleNames();
}

int BoardListModelWrapper::rowCount(const QModelIndex & parent) const
{
    return this->model_->rowCount() * this->model_->columnCount();
}

const QModelIndex BoardListModelWrapper::rowToTableIndex(const QModelIndex &idx) const
{
    int tableRow = 0;
    int tableColumn = 0;

    tableRow = idx.row() / this->model_->columnCount();
    tableColumn = idx.row() % this->model_->columnCount();

    QModelIndex tableIdx = this->createIndex(tableRow, tableColumn);

    return tableIdx;
}

void BoardListModelWrapper::dataChangedCB(const QModelIndex &topLeft, const QModelIndex &bottomRight)
{
    QModelIndex linTopLeft = model_->gridToLinearIndex(topLeft);
    QModelIndex linBottomRight = model_->gridToLinearIndex(bottomRight);

    emit dataChanged(linTopLeft, linBottomRight);

}

QVariant BoardListModelWrapper::data(const QModelIndex & index, int role) const
{
    QModelIndex tableIdx = rowToTableIndex(index);

    return this->model_->data(tableIdx, role);
}

