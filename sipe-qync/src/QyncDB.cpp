#define QYNCDB_CPP

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QVariant>

#include "QyncDB.h"

#define SQL_ERROR_STR(error) \
    (error.text().toStdString().c_str())

const static char *CREATE_GROUP_TABLE =
    "CREATE TABLE IF NOT EXISTS buddygroup \
    (id INTEGER PRIMARY KEY NOT NULL, \
     name TEXT NOT NULL UNIQUE )";
const static char *CREATE_BUDDY_TABLE =
    "CREATE TABLE IF NOT EXISTS buddy \
    (id INTEGER PRIMARY KEY NOT NULL, \
     name TEXT NOT NULL, \
     alias TEXT, \
     groupid INTEGER, \
     FOREIGN KEY(groupid) REFERENCES buddygroup(id))";
const static char *INSERT_GROUP =
    "INSERT INTO buddygroup values(NULL, '%1')";
const static char *INSERT_BUDDY=
    "INSERT INTO buddy values(NULL, '%1', '%2', '%3')";
const static char *SELECT_ALL_GROUPS =
    "SELECT id, name FROM buddygroup";
const static char *SELECT_ALL_BUDDIES=
    "SELECT buddy.id, buddy.name, buddy.alias, buddy.groupid, buddygroup.name FROM buddy, buddygroup";

QyncDB::QyncDB() :
    mBuddyList(), mGroupList()
{
}

QyncDB::~QyncDB()
{
    while (!mGroupList.isEmpty())
        delete mGroupList.takeFirst();
    while (!mBuddyList.isEmpty())
        delete mBuddyList.takeFirst();
    mDb.close();
}

void QyncDB::init(QString account)
{
    mDb = QSqlDatabase::addDatabase("QSQLITE");
    mDb.setDatabaseName("database.db");

    if(!mDb.open()) {
        qFatal("QyncDB: Cannot open database. %s", mDb.lastError().text().toStdString().c_str()) ;
    }

    QSqlQuery query;
    if(!query.exec(CREATE_GROUP_TABLE)) {
        qFatal("QyncDB: %s", SQL_ERROR_STR(query.lastError()));
    }
    if(!query.exec(CREATE_BUDDY_TABLE)) {
        qFatal("QyncDB: %s", SQL_ERROR_STR(query.lastError()));
    }

    loadGroups();
    loadBuddies();
}

bool QyncDB::addGroup(QString groupName)
{
    foreach(QyncGroupObject *group, mGroupList)
    {
        if (group->getName().compare(groupName) == 0) return true;
    }

    bool r;
    QSqlQuery query;
    r = query.exec(QString(INSERT_GROUP).arg(groupName));
    if (r) {
        qint32 id = query.lastInsertId().toInt();
        QyncGroupObject *obj = new QyncGroupObject(id);
        obj->setName(groupName);
        mGroupList.append(obj);
    } else {
        qFatal("QyncDB: %s", SQL_ERROR_STR(query.lastError()));
    }

    return true;
}

void QyncDB::loadGroups()
{
    while (!mGroupList.isEmpty())
        delete mGroupList.takeFirst();

    QSqlQuery query;
    bool r = query.exec(QString(SELECT_ALL_GROUPS));
    if (!r) {
        qFatal("QyncDB: %s", SQL_ERROR_STR(query.lastError()));
    }

    while (query.next()) {
        int id = query.value(0).toInt();
        QString name = query.value(1).toString();
        QyncGroupObject *obj = new QyncGroupObject(id);
        obj->setName(name);
        mGroupList.append(obj);
    }
}

void QyncDB::loadBuddies()
{
    while (!mBuddyList.isEmpty())
        delete mBuddyList.takeFirst();

    QSqlQuery query;
    bool r = query.exec(QString(SELECT_ALL_BUDDIES));
    if (!r) {
        qFatal("QyncDB: %s", SQL_ERROR_STR(query.lastError()));
        return;
    }

    while (query.next()) {
        int id = query.value(0).toInt();
        QString name = query.value(1).toString();
        QString alias = query.value(2).toString();
        quint32 groupId = query.value(3).toInt();
        QString groupName = query.value(4).toString();

        QyncBuddyObject *obj = new QyncBuddyObject(name);
        obj->setGroupId(groupId);
        obj->setAlias(alias);
        obj->setGroup(groupName);
        mBuddyList.append(obj);
    }
}

QyncBuddyObject *QyncDB::addBuddy(const QString &name, const QString &alias, const QString &groupName)
{
    qint32 groupId = -1;
    foreach(QyncGroupObject* group, mGroupList) {
        if (group->getName().compare(groupName) == 0) {
            groupId = group->getId();
            break;
        }
    }
    if (groupId < 0) {
        qFatal("Cannot find group: %s", groupName.toStdString().c_str());
    }

    foreach(QyncBuddyObject *buddy, mBuddyList) {
        if (buddy->getName().compare(name) && buddy->getGroupId() == groupId) {
            return buddy;
        }
    }

    QSqlQuery query;
    QyncBuddyObject *obj = NULL;
    bool r = query.exec(QString(INSERT_BUDDY).arg(name, alias).arg(groupId));
    if (r) {
        qint32 id = query.lastInsertId().toInt();
        obj = new QyncBuddyObject(name);
        obj->setAlias(alias);
        obj->setGroup(groupName);
        obj->setGroupId(groupId);
        mBuddyList.append(obj);
    } else {
        qFatal("QyncDB: %s", SQL_ERROR_STR(query.lastError()));
    }

    return obj;
}
