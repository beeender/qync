#ifndef QYNCSIPE_H
#define QYNCSIPE_H

#include <QObject>
#include <QThread>

#include "QyncLoginManager.h"

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

    friend class QyncLoginManager;

    public:
        QyncSipe(QObject* parent = 0);
        ~QyncSipe();

        enum LoginStatusE {
            Idle,
            InProcess,
            LoggedIn,
        };

        Q_INVOKABLE bool start();

        struct sipe_core_public *getSipePublic() const { return mSipePublic; };
        LoginStatusE getStatus() { return mStatus; };

    private:
        QString mAccountName;
        QString mDomainUser;
        QString mPassword;
        QString mEmail;
        QString mEmailUrl;
        bool mSso;

        QThread mSipeThread;
        QyncLoginManager mLoginManager;

        struct sipe_core_public *mSipePublic;

        LoginStatusE mStatus;

        void setStatus(LoginStatusE s);

    private slots:

    signals:
        void statusChanged();
};

#endif

