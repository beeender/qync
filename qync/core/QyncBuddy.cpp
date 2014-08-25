#define QYNCBUDDY_CPP

#include <QFile>

#include "QyncBuddy.h"
#include "QyncGroup.h"
#include "QyncDB.h"

QList< QWeakPointer<QyncBuddy::Buddy> > QyncBuddy::Buddy::mBuddyPool;

QyncBuddy::Buddy::Buddy(const QString &account) :
    mAccount(account), mAlias(), mImageName(), mStatus(QyncSipe::StatusOffline)
{
}

QyncBuddy::Buddy::~Buddy()
{
    //Remove from the pool
    for(auto it = mBuddyPool.begin(); it != mBuddyPool.end(); ++it) {
        if (it->data() == this) {
            mBuddyPool.erase(it);
            break;
        }
    }
}

QSharedPointer<QyncBuddy::Buddy>
QyncBuddy::Buddy::find(const QString &account)
{
    QSharedPointer<Buddy> buddy;
    auto it = mBuddyPool.begin();
    while(it != mBuddyPool.end()) {
        if ((*it).data()->mAccount.compare(account) == 0) {
            buddy = it->toStrongRef();
            break;
        }
        ++it;
    }
    return buddy;
}

QSharedPointer<QyncBuddy::Buddy> QyncBuddy::Buddy::create(const QString &account)
{
    QSharedPointer<Buddy> buddy = Buddy::find(account);
    //The buddy doesn't exist yet. Create a new one.
    if (buddy.isNull()) {
        buddy = QSharedPointer<Buddy>(new Buddy(account));
        mBuddyPool.append(buddy);
    }

    return buddy;
}


QyncBuddy::QyncBuddy(const QString &account, QObject *parent) :
    QyncBuddyObject(parent), mBuddy(Buddy::create(account)),
    mGroup(), mId()
{
}

QyncBuddy::QyncBuddy(QSharedPointer<Buddy> buddy, QObject *parent) :
    QyncBuddyObject(parent), mBuddy(buddy)
{
}

QyncBuddy::~QyncBuddy()
{
}

void QyncBuddy::setImage(const QString &imgName)
{
    mBuddy->mImageName = imgName.toLatin1();
}

QUrl QyncBuddy::getImageUrl() const
{
    QString str = QString("%1/%2").arg(QyncDB::getImageDir()).arg(QString(mBuddy->mImageName));
    QFile file(str);
    if (!mBuddy->mImageName.isEmpty() && file.exists()) {
        return QUrl::fromLocalFile(str);
    }

    //Use the default buddy image
    return QUrl("qrc:/images/DefaultBuddy.png");
}

void QyncBuddy::setGroup(const QSharedPointer<const QyncGroup> group)
{
    if (!mGroup.isNull()) {
        qFatal("The group of %s has already been set to %s",
                getName().toStdString().c_str(),
                mGroup->getName().toStdString().c_str());
    }

    mGroup = group;
}


QString QyncBuddy::getGroupName() const
{
    return mGroup->getName();
}

QString QyncBuddy::getPropertyString(const QyncSipe::BuddyInfoFieldE field) const
{
    return mBuddy->mPropMap.value(field);
}

void QyncBuddy::setPropertyString(const QyncSipe::BuddyInfoFieldE field, const QString &str)
{
    mBuddy->mPropMap[field] = str;
}

void QyncBuddy::setStatus(const QyncSipe::LoginStatusE status)
{
    mBuddy->mStatus = status;
}

QyncSipe::LoginStatusE QyncBuddy::getStatus() const
{
    return mBuddy->mStatus;
}

