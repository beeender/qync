#ifndef QYNCBUDDYLISTMODEL_H
#define QYNCBUDDYLISTMODEL_H

#include <QList>
#include <QAbstractListModel>
#include <QSharedPointer>

#include "QyncBuddyObject.h"
#include "QyncGroupObject.h"

class QyncBuddyListModel: public QAbstractListModel
{
    Q_OBJECT

public:
    enum BuddyRoles {
        AliasRole = Qt::UserRole + 1,
    };

    QyncBuddyListModel(QObject *parent = 0);
    QyncBuddyListModel(const QList<QyncBuddyObject *> buddyList, QObject *parent = 0);
    virtual ~QyncBuddyListModel();

    virtual QHash<int, QByteArray> roleNames() const;
    virtual int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    void addBuddy(const QSharedPointer<QyncBuddyObject> &buddy);

private:
    QList< QSharedPointer<QyncBuddyObject> > mBuddyList;
};

#endif

