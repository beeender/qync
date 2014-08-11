#ifndef QYNCBUDDYLISTMODEL_H
#define QYNCBUDDYLISTMODEL_H

#include <QList>
#include <QAbstractListModel>
#include <QSharedPointer>

#include "QyncBuddy.h"
#include "QyncGroup.h"

class QyncBuddyListModel: public QAbstractListModel
{
    Q_OBJECT

public:
    enum BuddyRoles {
        BuddyRole= Qt::UserRole + 1,
    };

    QyncBuddyListModel(QObject *parent = 0);
    virtual ~QyncBuddyListModel();

    virtual QHash<int, QByteArray> roleNames() const;
    virtual int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    void addBuddy(const QSharedPointer<QyncBuddy> &buddy);
    QSharedPointer<QyncBuddy> findBuddy(const QString &name) const;
    //TODO: Not good enough. const QyncBuddy would be better.
    const QList< QSharedPointer<QyncBuddy> > &getAllBuddies() { return mBuddyList; };

private:
    QList< QSharedPointer<QyncBuddy> > mBuddyList;
};

#endif

