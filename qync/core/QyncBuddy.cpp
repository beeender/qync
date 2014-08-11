#define QYNCBUDDY_CPP

#include "QyncBuddy.h"
#include "QyncGroup.h"

QList< QWeakPointer<QyncBuddy::Buddy> > QyncBuddy::Buddy::mBuddyPool;

QyncBuddy::Buddy::Buddy(const QString &account) :
    mAccount(account), mAlias(), mImageName()
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
    QObject(parent), QyncBuddyObject(), mBuddy(Buddy::create(account)),
    mGroup(), mId()
{
}

QyncBuddy::QyncBuddy(QSharedPointer<Buddy> buddy, QObject *parent) :
    QObject(parent), QyncBuddyObject(), mBuddy(buddy)
{
}

QyncBuddy::~QyncBuddy()
{
}

void QyncBuddy::setImage(const QByteArray &checksum)
{
    mBuddy->mImageName = checksum;
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

