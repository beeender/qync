#include <glib.h>
#include "QyncSipe.h"

#include "sipe-core.h"

#include "QyncBackend.h"


QyncSipe::QyncSipe(QObject* parent)
    :QObject(parent), mAccountName(""), mDomainUser(""), mPassword(""),
    mEmail(""), mEmailUrl(""), mSso(FALSE), mDb(),
    mSipePublic(NULL), mSipeThread(), mStatus(StatusOffline),
    mBuddyList(NULL), mGroupList(NULL)
{
    mGroupList = mDb.getGroupList();
    mBuddyList = mDb.getBuddyList();

    mBackend = new QyncBackend(this);
    mBackend->moveToThread(&mSipeThread);
    mSipeThread.start();

    mBuddyListModel = new QyncBuddyListModel();
}

QyncSipe::~QyncSipe()
{
    delete mBackend;
    delete mBuddyListModel;
}

bool QyncSipe::start()
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
    emit mBackend->login(loginInfo);

    return true;
}

void QyncSipe::setStatus(LoginStatusE s)
{
    mStatus = s;
    emit statusChanged();
}

bool QyncSipe::addGroup(const QString &group)
{
    return mDb.addGroup(group);
}

QyncBuddyObject *QyncSipe::findBuddy(const QString &buddyName, const QString &groupName)
{
    foreach(QyncBuddyObject *buddy, *mBuddyList) {
        if (buddy->getName().compare(buddyName) == 0 &&
                buddy->getGroup().compare(groupName) == 0) {
            return buddy;
        }
    }

    return NULL;
}

QyncBuddyObject *QyncSipe::addBuddy(const QString &buddyName, const QString &alias, const QString &groupName)
{
    QyncBuddyObject *buddy = mDb.addBuddy(buddyName, alias, groupName);
    mBuddyListModel->addBuddy(*buddy);
    return buddy;
}
