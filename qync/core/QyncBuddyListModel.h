#ifndef QYNCBUDDYLISTMODEL_H
#define QYNCBUDDYLISTMODEL_H

#include <QList>
#include <QAbstractListModel>

#include "QyncBuddyObject.h"

class QyncBuddyListModel: public QAbstractListModel
{
    Q_OBJECT

public:
    enum BuddyRoles {
        NameRole = Qt::UserRole + 1,
        GroupRole,
        AliasRole
    };

    QyncBuddyListModel(QObject *parent = 0);
    QyncBuddyListModel(QList<QyncBuddyObject *> buddyList, QObject *parent = 0);
    virtual QHash<int, QByteArray> roleNames() const;
    virtual int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    void addBuddy(QyncBuddyObject &buddy);

private:
    QList<QyncBuddyObject *> mBuddyList;
};

#endif

