#define QYNCBUDDY_CPP

#include "QyncBuddy.h"
#include "QyncGroup.h"

QList< QWeakPointer<QyncBuddy::Buddy> > QyncBuddy::Buddy::mBuddyPool;

QyncBuddy::QyncBuddy(const QString &account, QObject *parent) :
    QObject(parent), QyncBuddyObject(), mBuddy(Buddy::createBuddy(account)),
    mGroup()
{
}

QSharedPointer<QyncBuddy::Buddy> QyncBuddy::Buddy::createBuddy(const QString &account)
{
    QSharedPointer<Buddy> buddy;
    auto it = mBuddyPool.begin();
    while(it != mBuddyPool.end()) {
        if ((*it).data()->getAccount().compare(account) == 0) {
            buddy = it->toStrongRef();
            break;
        }
        ++it;
    }

    //The buddy doesn't exist yet. Create a new one.
    if (buddy.isNull()) {
        buddy = QSharedPointer<Buddy>(new Buddy(account));
        mBuddyPool.append(buddy);
    }

    return buddy;
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

QyncBuddy::Buddy::Buddy(const QString &account) : mAccount(account), mAlias()
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

void QyncBuddy::Buddy::setAlias(const QString &alias)
{
    mAlias = alias;
}

