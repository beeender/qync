#include "QyncSipeCore.h"

QyncSipeCore::QyncSipeCore(QObject* /*parent*/, bool threadedBackend)
    :QyncSipe(threadedBackend),
    mAccountName(""), mDomainUser(""), mPassword(""),
    mEmail(""), mEmailUrl(""), mSso(false), mDb(), mStatus(StatusOffline)
{
    mGroupListModel = new QyncCategoryListModel();
}

QyncSipeCore::~QyncSipeCore()
{
    delete mGroupListModel;
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
    foreach(QSharedPointer<QyncGroupObject> group, mDb.getGroupList()) {
        mGroupListModel->addGroup(group);
    }
    foreach(QSharedPointer<QyncBuddyObject> buddy, mDb.getBuddyList()) {
        mGroupListModel->addBuddy(buddy);
    }

    //login(loginInfo);
    //FIXME:For testing.
    setStatus(StatusInProcess);
    setStatus(StatusActive);
    return true;
}

void QyncSipeCore::setStatus(LoginStatusE s)
{
    mStatus = s;
    emit statusChanged();
}

bool QyncSipeCore::addGroup(const QString &groupName)
{
    const QSharedPointer<QyncGroupObject> group = mDb.addGroup(groupName);
    if (group.isNull()) return false;

    mGroupListModel->addGroup(group);
    return true;
}

QyncBuddyObject *QyncSipeCore::findBuddy(const QString &buddyName, const QString &groupName)
{
    foreach(QSharedPointer<QyncBuddyObject> buddy, mDb.getBuddyList()) {
        if (buddy->getName().compare(buddyName) == 0 &&
                buddy->getGroup().compare(groupName) == 0) {
            return buddy.data();
        }
    }

    return NULL;
}

QyncBuddyObject *QyncSipeCore::addBuddy(const QString &buddyName, const QString &alias, const QString &groupName)
{
    QSharedPointer<QyncBuddyObject> buddy = mDb.addBuddy(buddyName, alias, groupName);
    mGroupListModel->addBuddy(buddy);
    return buddy.data();
}
