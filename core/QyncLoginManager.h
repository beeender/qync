#ifndef QYNCLOGINMANAGER_H
#define QYNCLOGINMANAGER_H

#include <QObject>
#include <QtQuick/QQuickItem>

class QyncSipe;

class QyncLoginManager: QObject
{
    Q_OBJECT
    Q_PROPERTY(LoginStatusE status READ getStatus NOTIFY statusChanged)

    friend class QyncSipe;

    public:
        enum LoginStatusE {
            IDLE,
            IN_PROCESS,
            LOGGED_IN,
        };

        LoginStatusE getStatus() { return mStatus; }

    signals:
        void statusChanged();
        void login();

    private:
        QyncLoginManager(QObject *parent = 0);
        ~QyncLoginManager();

        LoginStatusE mStatus;

    private slots:
        void doLogin();
};

#endif

