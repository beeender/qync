#ifndef QYNCLOGINMANAGER_H
#define QYNCLOGINMANAGER_H

#include <glib.h>
#include <QObject>
#include "QyncSipe.h"

class QyncBuddyObject;
class QyncBackend: public QObject
{
    Q_OBJECT

    public:
        QyncBackend(QyncSipe *qyncSipe, QObject *parent = 0);
        ~QyncBackend();

        guint getDesiredStatus() const { return mDesiredStatus; };
        void setStatus(guint status);
        bool addGroup(const gchar *groupName);
        QyncBuddyObject *findBuddy(const gchar *buddyName, const gchar *groupName);
        QyncBuddyObject *addBuddy(const gchar *buddyName, const gchar *alias, const gchar *groupName);

    signals:
        //Signals should only be emitted by QyncSipe
        void __login(const QyncSipe::LoginInfo &);

    private:
        QyncSipe *mQyncSipe;
        guint mDesiredStatus;
        struct sipe_core_public *mSipePublic;

    private slots:
        void doLogin(const QyncSipe::LoginInfo &loginInfo);
};

#endif

