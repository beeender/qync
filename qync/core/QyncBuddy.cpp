#define QYNCBUDDY_CPP

#include "QyncBuddy.h"
#include "QyncGroup.h"

QList< QWeakPointer<QyncCommonBuddy::Buddy> > QyncCommonBuddy::Buddy::mBuddyPool;

QyncCommonBuddy::Buddy::Buddy(const QString &account) :
    mAccount(account), mAlias(), mImageName()
{
}

QyncCommonBuddy::Buddy::~Buddy()
{
    //Remove from the pool
    for(auto it = mBuddyPool.begin(); it != mBuddyPool.end(); ++it) {
        if (it->data() == this) {
            mBuddyPool.erase(it);
            break;
        }
    }
}

QSharedPointer<QyncCommonBuddy::Buddy>
QyncCommonBuddy::Buddy::find(const QString &account)
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

QSharedPointer<QyncCommonBuddy::Buddy> QyncCommonBuddy::Buddy::create(const QString &account)
{
    QSharedPointer<Buddy> buddy = Buddy::find(account);
    //The buddy doesn't exist yet. Create a new one.
    if (buddy.isNull()) {
        buddy = QSharedPointer<Buddy>(new Buddy(account));
        mBuddyPool.append(buddy);
    }

    return buddy;
}


QyncCommonBuddy::QyncCommonBuddy(const QString &account, QObject *parent) :
    QObject(parent), QyncBuddyObject(), mBuddy(Buddy::create(account))
{
}

QyncCommonBuddy::QyncCommonBuddy(QSharedPointer<Buddy> buddy, QObject *parent) :
    QObject(parent), QyncBuddyObject(), mBuddy(buddy)
{
}

QyncCommonBuddy::~QyncCommonBuddy()
{
}

QSharedPointer<QyncCommonBuddy> QyncCommonBuddy::findCommonBuddy(const QString &account)
{
    return QSharedPointer<QyncCommonBuddy>(new QyncCommonBuddy(Buddy::find(account)));
}

QyncBuddy::QyncBuddy(const QString &account, QObject * /*parent*/) :
    QyncCommonBuddy(account), mGroup()
{
}

QyncBuddy::~QyncBuddy()
{
}

void QyncCommonBuddy::setImage(const QByteArray &checksum)
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

