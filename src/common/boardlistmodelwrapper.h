#ifndef BOARDLISTMODELWRAPPER_H
#define BOARDLISTMODELWRAPPER_H

#include <QAbstractListModel>
#include "boardmodel.h"

class BoardListModelWrapper : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit BoardListModelWrapper(BoardModel * model, QObject *parent = 0);

    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    QHash<int, QByteArray> roleNames() const;
    const QModelIndex rowToTableIndex(const QModelIndex &idx) const;
signals:

public slots:
    void dataChangedCB(const QModelIndex & topLeft, const QModelIndex & bottomRight);

private:
    BoardModel * model_;

};

#endif // BOARDLISTMODELWRAPPER_H
