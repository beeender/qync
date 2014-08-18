#define QYNCSIPECORE_CPP

#include "QyncSipeCore.h"
#include "QyncCategoryListModel.h"
#include "QyncGroup.h"
#include "QyncUtils.h"

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


    //FIXME:For testing.
#if 1
    login(loginInfo);
#else
    setStatus(StatusInProcess);
    setStatus(StatusActive);
#endif
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

const QByteArray *QyncSipeCore::getBuddyPhotoHash(const QString &buddyName)
{
    QSharedPointer<QyncBuddy> buddy = mGroupListModel->findBuddy(buddyName);
    if (buddy.isNull()) return nullptr;

    const QByteArray *imgName = buddy->getImageHash();
    if (!imgName->length()) return nullptr;

    QByteArray checksum = QyncUtils::calImageChecksum(*imgName);
    if (imgName == checksum) return imgName;

    return nullptr;
}

const QyncBuddy *QyncSipeCore::findBuddy(const QString &buddyName, const QString &groupName)
{
    QSharedPointer<QyncBuddy> buddy =
        mGroupListModel->findBuddy(buddyName, groupName);

    if (buddy.isNull()) return NULL;

    return buddy.data();
}

const QList<const QyncBuddyObject*> QyncSipeCore::findAllBuddies(const QString &buddyName, const QString &groupName)
{
    QList<const QyncBuddyObject*> list = mGroupListModel->findAllBuddies(buddyName, groupName);

    return list;
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
    buddyPtr->setGroup(group);
    buddyPtr->setAlias(alias);
    mGroupListModel->addBuddy(buddyPtr);
    mDb.insertBuddy(buddyPtr);

    return buddyPtr.data();
}

void QyncSipeCore::setBuddyPhoto(const QString &buddyName, const QByteArray &imgData, const QByteArray &hash)
{
    if (QyncUtils::writeImage(imgData, hash)) {
        mDb.updateImage(buddyName, hash);
    }
}

