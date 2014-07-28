#ifndef QYNCLOGINMANAGER_H
#define QYNCLOGINMANAGER_H

#include <glib.h>
#include <QObject>

class QyncSipe;

struct LoginInfo {
    QString accountName;
    QString domainUser;
    QString password;
    QString email;
    QString emailUrl;
    bool sso;
};

class QyncBuddyObject;
class QyncBackend: public QObject
{
    Q_OBJECT

    friend class QyncSipe;

    public:
        guint getDesiredStatus() const { return mDesiredStatus; };
        void setStatus(guint status);
        bool addGroup(const gchar *groupName);
        QyncBuddyObject *findBuddy(const gchar *buddyName, const gchar *groupName);
        QyncBuddyObject *addBuddy(const gchar *buddyName, const gchar *alias, const gchar *groupName);
    signals:
        void login(const LoginInfo &);

    private:
        QyncBackend(QyncSipe *qyncSipe, QObject *parent = 0);
        ~QyncBackend();

        QyncSipe *mQyncSipe;
        guint mDesiredStatus;
        struct sipe_core_public *mSipePublic;

    private slots:
        void doLogin(const LoginInfo &loginInfo);
};

Q_DECLARE_METATYPE(LoginInfo);
#endif

