#ifndef QYNCSIPECORE_H
#define QYNCSIPECORE_H

#include <QList>
#include <QSharedPointer>

#include "QyncSipe.h"

#include "QyncBuddyObject.h"
#include "QyncGroupObject.h"
#include "QyncCategoryListModel.h"
#include "QyncDB.h"

class QyncBackend;
class QyncSipeCore : public QyncSipe
{
    Q_OBJECT
    Q_PROPERTY(QString accountName MEMBER mAccountName)
    Q_PROPERTY(QString domainUser MEMBER mDomainUser)
    Q_PROPERTY(QString password MEMBER mPassword)
    Q_PROPERTY(QString email MEMBER mEmail)
    Q_PROPERTY(QString emailUrl MEMBER mEmailUrl)
    Q_PROPERTY(bool sso MEMBER mSso)

    Q_PROPERTY(LoginStatusE status READ getStatus NOTIFY statusChanged)


    public:

        QyncSipeCore(QObject* parent = 0, bool threadedBackend = true);
        ~QyncSipeCore();

        Q_INVOKABLE bool start();

        QyncSipe::LoginStatusE getStatus() { return mStatus; };
        QyncCategoryListModel *getGroupListModel() const { return mGroupListModel; };

    private:
        QString mAccountName;
        QString mDomainUser;
        QString mPassword;
        QString mEmail;
        QString mEmailUrl;
        bool mSso;

        QyncCategoryListModel *mGroupListModel;

        QyncDB mDb;

        QyncSipe::LoginStatusE mStatus;

        void setStatus(const QyncSipe::LoginStatusE s);
        QyncBuddyObject *addBuddy(const QString &buddyName, const QString &alias, const QString &groupName);
        QyncBuddyObject *findBuddy(const QString &buddyName, const QString &groupName);
        bool addGroup(const QString &groupName);
    private slots:

    signals:
        void statusChanged();
};

#endif

