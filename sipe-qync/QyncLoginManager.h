#ifndef QYNCLOGINMANAGER_H
#define QYNCLOGINMANAGER_H

#include <QObject>

class QyncSipe;

class QyncLoginManager: public QObject
{
    Q_OBJECT

    friend class QyncSipe;

    public:

    signals:
        void statusChanged();
        void login();

    private:
        QyncLoginManager(QyncSipe *qyncSipe, QObject *parent = 0);
        ~QyncLoginManager();

        QyncSipe *mQyncSipe;

    private slots:
        void doLogin();
};

#endif

