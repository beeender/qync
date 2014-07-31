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
        IsGroupRole,
        GroupNameRole
    };

    QyncBuddyListModel(QObject *parent = 0);
    QyncBuddyListModel(const QList<QyncBuddyObject *> buddyList, QObject *parent = 0);
    virtual ~QyncBuddyListModel();

    virtual QHash<int, QByteArray> roleNames() const;
    virtual int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    void addBuddy(const QSharedPointer<QyncBuddyObject> &buddy);
    void addGroup(const QSharedPointer<QyncGroupObject> &group);

private:
    struct BuddyOrGroup{
        QSharedPointer<QyncBuddyObject> mBuddy;
        QSharedPointer<QyncGroupObject> mGroup;

        BuddyOrGroup(const QSharedPointer<QyncBuddyObject> &buddy) : mGroup(0) {
            mBuddy = buddy;
        };

        BuddyOrGroup(const QSharedPointer<QyncGroupObject> &group) : mBuddy(0) {
            mGroup = group;
        };

        bool isGroup() {
            if (mBuddy.isNull()) return true;
            return false;
        }

        const QString getName() {
            if (mBuddy.isNull()) return "";
            return mBuddy->getName();
        };

        const QString getAlias() {
            if (mBuddy.isNull()) return "";
            return mBuddy->getAlias();
        };

        const QString getGroupName() {
            if (mGroup.isNull()) return "";
            return mGroup->getName();
        }
    };

    QList<BuddyOrGroup *> mBuddyOrGroupList;
};

#endif

