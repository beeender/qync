#include "QyncSipeCore.h"

QyncSipeCore::QyncSipeCore(QObject* parent, bool threadedBackend)
    :QyncSipe(threadedBackend),
    mAccountName(""), mDomainUser(""), mPassword(""),
    mEmail(""), mEmailUrl(""), mSso(false), mDb(), mStatus(StatusOffline),
    mBuddyList(NULL), mGroupList(NULL)
{
    mGroupList = mDb.getGroupList();
    mBuddyList = mDb.getBuddyList();

    mBuddyListModel = new QyncBuddyListModel();
}

QyncSipeCore::~QyncSipeCore()
{
    delete mBuddyListModel;
}

bool QyncSipeCore::start()
{
    LoginInfo loginInfo;
    loginInfo.accountName = mAccountName;
    loginInfo.domainUser = mDomainUser;
    loginInfo.password = mPassword;
    loginInfo.email = mEmail;
    loginInfo.emailUrl = mEmailUrl;
    loginInfo.sso = mSso;

    mDb.init(mAccountName);
    foreach(QyncBuddyObject *buddy, *mBuddyList) {
        mBuddyListModel->addBuddy(*buddy);
    }

    login(loginInfo);
    return true;
}

void QyncSipeCore::setStatus(LoginStatusE s)
{
    mStatus = s;
    emit statusChanged();
}

bool QyncSipeCore::addGroup(const QString &group)
{
    return mDb.addGroup(group);
}

QyncBuddyObject *QyncSipeCore::findBuddy(const QString &buddyName, const QString &groupName)
{
    foreach(QyncBuddyObject *buddy, *mBuddyList) {
        if (buddy->getName().compare(buddyName) == 0 &&
                buddy->getGroup().compare(groupName) == 0) {
            return buddy;
        }
    }

    return NULL;
}

QyncBuddyObject *QyncSipeCore::addBuddy(const QString &buddyName, const QString &alias, const QString &groupName)
{
    QyncBuddyObject *buddy = mDb.addBuddy(buddyName, alias, groupName);
    mBuddyListModel->addBuddy(*buddy);
    return buddy;
}
