#define QYNCSIPECORE_CPP

#include "QyncSipeCore.h"
#include "QyncCategoryListModel.h"
#include "QyncGroup.h"

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

    mDb.init(mAccountName, *mGroupListModel);

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
    QSharedPointer<QyncGroup> group =
        mGroupListModel->findGroup(groupName);

    if(!group.isNull()) return true;

    //TODO: Should be atom operation
    group = QSharedPointer<QyncGroup>(new QyncGroup(groupName));
    mGroupListModel->addGroup(group);
    mDb.insertGroup(group);

    return true;
}

const QyncBuddy *QyncSipeCore::findBuddy(const QString &buddyName, const QString &groupName)
{
    QSharedPointer<QyncBuddy> buddy =
        mGroupListModel->findBuddy(buddyName, groupName);

    if (buddy.isNull()) return NULL;

    return buddy.data();
}

const QyncBuddy *QyncSipeCore::addBuddy(const QString &buddyName, const QString &alias, const QString &groupName)
{
    const QyncBuddy* buddy = findBuddy(buddyName, groupName);
    if (buddy) return buddy;

    QSharedPointer<QyncGroup> group =
        mGroupListModel->findGroup(groupName);
    if(group.isNull()) {
        qFatal("Group %s doesn't exist yet!", groupName.toStdString().c_str());
    }

    //TODO: Should be atom operation
    QSharedPointer<QyncBuddy> buddyPtr(new QyncBuddy(buddyName));
    buddyPtr->setAlias(alias);
    mGroupListModel->addBuddy(buddyPtr);
    mDb.insertBuddy(buddyPtr);

    return buddyPtr.data();
}
