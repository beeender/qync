#ifndef QYNCDB_H
#define QYNCDB_H

#include <QString>
#include <QSqlDatabase>
#include <QList>

#include "QyncBuddyObject.h"
#include "QyncGroupObject.h"

class QyncDB {
    public:
        QyncDB();
        ~QyncDB();

        void init(QString account);
        bool addGroup(QString groupName);
        QyncBuddyObject *addBuddy(const QString &name, const QString &alias, const QString &groupName);

        const QList<QyncBuddyObject *> *getBuddyList() const { return &mBuddyList; };
        const QList<QyncGroupObject *> *getGroupList() const { return &mGroupList; };
    private:
        QSqlDatabase mDb;
        QList<QyncBuddyObject *> mBuddyList;
        QList<QyncGroupObject *> mGroupList;

        void loadGroups();
        void loadBuddies();
};

#endif

