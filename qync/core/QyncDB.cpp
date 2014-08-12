#define QYNCDB_CPP

#include <QSqlError>
#include <QSqlQuery>
#include <QString>
#include <QCryptographicHash>
#include <QDir>
#include <QtDebug>

#include "QyncDB.h"
#include "QyncBuddy.h"
#include "QyncGroup.h"
#include "QyncCategoryListModel.h"

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
     image TEXT, \
     FOREIGN KEY(groupid) REFERENCES buddygroup(id))";
const static char *INSERT_GROUP =
    "INSERT INTO buddygroup values(NULL, '%1')";
const static char *INSERT_BUDDY=
    "INSERT INTO buddy (name, alias, groupid) VALUES('%1', '%2', '%3')";
const static char *SELECT_ALL_GROUPS =
    "SELECT id, name FROM buddygroup";
const static char *SELECT_ALL_BUDDIES =
    "SELECT buddy.id, buddy.name, buddy.alias, buddy.groupid, buddygroup.name FROM buddy, buddygroup where buddy.groupid = buddygroup.id";
const static char *UPDATE_BUDDY_IMAGE =
    "UPDATE buddy SET image = '%1' WHERE buddy.name = '%2'";

const static char *BASE_DIR = ".qync";
const static char *IMAGE_BASE_DIR = "images";
const static char *DB_NAME = "qync.db";

QString QyncDB::mBaseDir;
QString QyncDB::mDbPath;
QString QyncDB::mImageDir;

QyncDB::QyncDB() : mDb()
{
}

QyncDB::~QyncDB()
{
    mDb.close();
}

void QyncDB::init(const QString &account, QyncCategoryListModel &groupList)
{
    if (!mBaseDir.isEmpty()) qFatal("QyncDB cannot be inited twice!");

    mBaseDir = QString("%1/%2/%3/").arg(QDir::home().absolutePath(), BASE_DIR,
            QString(QCryptographicHash::hash(account.toUtf8(), QCryptographicHash::Md5).toHex()));
    QDir dir(mBaseDir);
    if (!dir.exists()) dir.mkpath(".");
    mDbPath =  QString("%1%2").arg(mBaseDir, DB_NAME);
    mImageDir = QString("%1%2/").arg(mBaseDir, IMAGE_BASE_DIR);


    mDb = QSqlDatabase::addDatabase("QSQLITE");
    mDb.setDatabaseName(mDbPath);

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

    loadGroups(groupList);
    loadBuddies(groupList);
}

void QyncDB::insertGroup(const QSharedPointer<QyncGroup> group)
{
    QSqlQuery query;

    if (query.exec(QString(INSERT_GROUP).arg(group->getName()))) {
        qint32 id = query.lastInsertId().toInt();
        group->setId(id);
    } else {
        qFatal("QyncDB: %s", SQL_ERROR_STR(query.lastError()));
    }
}

void QyncDB::loadGroups(QyncCategoryListModel &groupList)
{
    QSqlQuery query;
    if (!query.exec(QString(SELECT_ALL_GROUPS))) {
        qFatal("QyncDB: %s", SQL_ERROR_STR(query.lastError()));
    }

    while (query.next()) {
        int id = query.value(0).toInt();
        QString name = query.value(1).toString();
        QyncGroup *obj = new QyncGroup(name);
        obj->setId(id);
        groupList.addGroup(QSharedPointer<QyncGroup>(obj));
    }
}

void QyncDB::loadBuddies(QyncCategoryListModel &groupList)
{
    QSqlQuery query;
    if (!query.exec(QString(SELECT_ALL_BUDDIES))) {
        qFatal("QyncDB: %s", SQL_ERROR_STR(query.lastError()));
        return;
    }

    while (query.next()) {
        qint32 id = query.value(0).toInt();
        QString name = query.value(1).toString();
        QString alias = query.value(2).toString();
        QString groupName = query.value(4).toString();

        QyncBuddy *obj = new QyncBuddy(name);
        obj->setAlias(alias);
        obj->setId(id);
        //Group will be set by addBuddy
        groupList.addBuddy(QSharedPointer<QyncBuddy>(obj), groupName);
    }
}

void QyncDB::insertBuddy(const QSharedPointer<QyncBuddy> buddy)
{
    QSqlQuery query;
    if (query.exec(QString(INSERT_BUDDY).arg(buddy->getName()).
                    arg(buddy->getAlias()).arg(buddy->getGroup()->getId()))) {
        //qint32 id = query.lastInsertId().toInt();
    } else {
        qFatal("QyncDB: %s", SQL_ERROR_STR(query.lastError()));
    }
}

void QyncDB::updateImage(const QString &buddyName, const QString &imgName)
{
    QSqlQuery query;
    if (!query.exec(QString(UPDATE_BUDDY_IMAGE).arg(imgName).arg(buddyName))) {
        qWarning() << "Failed to update image " << imgName << " for " << buddyName;
    }
}

