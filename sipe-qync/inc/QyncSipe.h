#ifndef QYNCSIPE_H
#define QYNCSIPE_H

#include <QObject>
#include <QThread>
#include <QList>

#include "QyncBackend.h"
#include "QyncDB.h"
#include "QyncBuddyObject.h"
#include "QyncGroupObject.h"
#include "QyncBuddyListModel.h"

class QyncSipe : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString accountName MEMBER mAccountName)
    Q_PROPERTY(QString domainUser MEMBER mDomainUser)
    Q_PROPERTY(QString password MEMBER mPassword)
    Q_PROPERTY(QString email MEMBER mEmail)
    Q_PROPERTY(QString emailUrl MEMBER mEmailUrl)
    Q_PROPERTY(bool sso MEMBER mSso)

    Q_ENUMS(LoginStatusE)
    Q_PROPERTY(LoginStatusE status READ getStatus NOTIFY statusChanged)

    friend class QyncBackend;

    public:
        enum LoginStatusE {
            StatusOffline,
            StatusInProcess,
            StatusActive,
            StatusInactive,
            StatusBusy,
            StatusAway,
            StatusDND,
        };

        QyncSipe(QObject* parent = 0);
        ~QyncSipe();

        Q_INVOKABLE bool start();

        struct sipe_core_public *getSipePublic() const { return mSipePublic; };
        LoginStatusE getStatus() { return mStatus; };
        QyncBuddyListModel *getBuddyListModel() const { return mBuddyListModel; };
    private:
        QString mAccountName;
        QString mDomainUser;
        QString mPassword;
        QString mEmail;
        QString mEmailUrl;
        bool mSso;

        const QList<QyncBuddyObject *> *mBuddyList;
        const QList<QyncGroupObject *> *mGroupList;
        QyncBuddyListModel *mBuddyListModel;

        QThread mSipeThread;
        QyncBackend mBackend;
        QyncDB mDb;

        struct sipe_core_public *mSipePublic;

        LoginStatusE mStatus;

        void setStatus(LoginStatusE s);
        bool addGroup(const QString &group);
        QyncBuddyObject *findBuddy(const QString &buddyName, const QString &groupName);
        QyncBuddyObject *addBuddy(const QString &buddyName, const QString &alias, const QString &groupName);

    private slots:

    signals:
        void statusChanged();
};

#endif

