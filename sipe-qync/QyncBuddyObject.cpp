#define QYNCBUDDYOBJECT_CPP

#include "QyncBuddyObject.h"

QyncBuddyObject::QyncBuddyObject(const QString &name) :
    mAlias(),mGroup()
{
    mName = name;
}

void QyncBuddyObject::setAlias(const QString &alias)
{
    mAlias = alias;
}

void QyncBuddyObject::setGroup(const QString &group)
{
    mGroup = group;
}

void QyncBuddyObject::setGroupId(quint32 groupId)
{
    mGroupId = groupId;
}
