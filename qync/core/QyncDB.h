#ifndef QYNCDB_H
#define QYNCDB_H

#include <QSqlDatabase>
#include <QSharedPointer>

class QString;
class QyncBuddy;
class QyncGroup;
class QyncCategoryListModel;
class QyncDB {
    public:
        QyncDB();
        ~QyncDB();

        void init(const QString &account, QyncCategoryListModel &groupList);
        void insertGroup(const QSharedPointer<QyncGroup> group);
        void insertBuddy(const QSharedPointer<QyncBuddy> buddy);
        void updateImage(const QString &buddyName, const QString &imgName);

        static QString getImageDir() { return mImageDir; };

    private:
        QSqlDatabase mDb;
        static QString mBaseDir;
        static QString mDbPath;
        static QString mImageDir;

        void loadGroups(QyncCategoryListModel &groupList);
        void loadBuddies(QyncCategoryListModel &groupList);
};

#endif

