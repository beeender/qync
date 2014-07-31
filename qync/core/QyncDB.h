#ifndef QYNCDB_H
#define QYNCDB_H

#include <QString>
#include <QSqlDatabase>
#include <QList>
#include <QSharedPointer>

#include "QyncBuddyObject.h"
#include "QyncGroupObject.h"

class QyncDB {
    public:
        QyncDB();
        ~QyncDB();

        void init(const QString &account);
        const QSharedPointer<QyncGroupObject> addGroup(const QString &groupName);
        const QSharedPointer<QyncBuddyObject> addBuddy(const QString &name, const QString &alias, const QString &groupName);

        const QList< QSharedPointer<QyncBuddyObject> > &getBuddyList() const { return mBuddyList; };
        const QList< QSharedPointer<QyncGroupObject> > &getGroupList() const { return mGroupList; };
    private:
        QSqlDatabase mDb;
        QList< QSharedPointer<QyncBuddyObject> > mBuddyList;
        QList< QSharedPointer<QyncGroupObject> > mGroupList;

        void loadGroups();
        void loadBuddies();
};

#endif

