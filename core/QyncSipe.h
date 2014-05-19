#ifndef QYNCSIPE_H
#define QYNCSIPE_H

#include <QObject>

#include "QyncLoginManager.h"

class QyncSipe : public QObject
{
    Q_OBJECT
    //Q_PROPERTY(QString accountName WRITE setAccountName READ getAccountName)
    Q_PROPERTY(QString accountName MEMBER mAccountName)
    Q_PROPERTY(QString domainUser MEMBER mDomainUser)
    Q_PROPERTY(QString password MEMBER mPassword)
    Q_PROPERTY(QString email MEMBER mEmail)
    Q_PROPERTY(QString emailUrl MEMBER mEmailUrl)
    Q_PROPERTY(bool sso MEMBER mSso)

    public:
        QyncSipe(QObject* parent = 0);
        ~QyncSipe();

        Q_INVOKABLE bool start();

        QyncLoginManager *getLoginManager() { return &mLoginManager; };

        struct sipe_core_public *getSipePublic() const { return mSipePublic; };
    private:
        QString mAccountName;
        QString mDomainUser;
        QString mPassword;
        QString mEmail;
        QString mEmailUrl;
        bool mSso;

        QyncLoginManager mLoginManager;

        struct sipe_core_public *mSipePublic;
    private slots:

    signals:
};

#endif

