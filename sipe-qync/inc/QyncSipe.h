#ifndef QYNCSIPE_H
#define QYNCSIPE_H

#include <QObject>
#include <QString>
#include <QMetaType>

class QyncBackend;
class QThread;
class QyncBuddyObject;
class QyncSipe : public QObject
{
    Q_OBJECT
    Q_ENUMS(LoginStatusE)

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

        struct LoginInfo {
            QString accountName;
            QString domainUser;
            QString password;
            QString email;
            QString emailUrl;
            bool sso;
        };

    public:
        QyncSipe(bool threadedBackend = true);
        virtual ~QyncSipe();

        //Callback functions called by the backend
        virtual void setStatus(const LoginStatusE s) = 0;
        virtual const QyncBuddyObject *addBuddy(const QString &buddyName, const QString &alias, const QString &groupName) = 0;
        virtual const QyncBuddyObject *findBuddy(const QString &buddyName, const QString &groupName) = 0;
        virtual bool addGroup(const QString &group) = 0;
        //Return hash string which is corresponding the given buddy.
        //The hash sting needs to be hold by the frontend.
        virtual const QByteArray *getBuddyPhotoHash(const QString &buddyName) = 0;

        //Interfaces for the frontend
        void login(const LoginInfo &loginInfo);
    private:
        QyncBackend *mBackend;
        QThread *mBackendThread;
        QByteArray a;
};

Q_DECLARE_METATYPE(QyncSipe::LoginInfo);

#endif

