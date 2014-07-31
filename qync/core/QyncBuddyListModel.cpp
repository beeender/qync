#define QYNCBUDDYLISTMODEL_CPP

#include "QyncBuddyListModel.h"

QyncBuddyListModel::QyncBuddyListModel(QObject * /*parent*/)
{
}

QyncBuddyListModel::QyncBuddyListModel(const QList<QyncBuddyObject *> /*buddyList*/, QObject * /*parent*/)
{
}

QyncBuddyListModel::~QyncBuddyListModel()
{
    foreach(BuddyOrGroup *bg, mBuddyOrGroupList) {
        delete bg;
    }
    mBuddyOrGroupList.clear();
}

QHash<int, QByteArray> QyncBuddyListModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[AliasRole] = "aliasName";
    roles[IsGroupRole] = "isGroup";
    roles[GroupNameRole] = "groupName";
    return roles;
}

int QyncBuddyListModel::rowCount(const QModelIndex & /*parent*/) const
{
    return mBuddyOrGroupList.size();
}

QVariant QyncBuddyListModel::data(const QModelIndex & index, int role) const
{
    switch (role) {
        case AliasRole:
            return QVariant(mBuddyOrGroupList.at(index.row())->getAlias());
        case IsGroupRole:
            return QVariant(mBuddyOrGroupList.at(index.row())->isGroup());
        case GroupNameRole:
            return QVariant(mBuddyOrGroupList.at(index.row())->getGroupName());
        default:
            break;
    }

    return QVariant();
}

void QyncBuddyListModel::addBuddy(const QSharedPointer<QyncBuddyObject> &buddy)
{
    int index;
    bool foundGroup = false;
    for (QList<BuddyOrGroup*>::iterator it = mBuddyOrGroupList.begin(); it != mBuddyOrGroupList.end(); ++it) {
        if (!foundGroup && (*it)->isGroup() && (*it)->mGroup->getId() == buddy->getGroupId()) {
            foundGroup = true;
            continue;
        }

        //The group has not been found yet
        if(!foundGroup) continue;

        //Ignore the duplicated group.
        if ((*it)->mBuddy == buddy) return;

        //Sort the buddies by alias.
        //Insert if it is a empty group or
        //it has a greater order.
        if (((*it)->isGroup()) ||
                (!(*it)->isGroup() && (*it)->mBuddy->getAlias().compare(buddy->getAlias()) > 0)) {
            index = mBuddyOrGroupList.indexOf(*it);
            beginInsertRows(QModelIndex(), index, index);
            mBuddyOrGroupList.insert(it, new BuddyOrGroup(buddy));
            endInsertRows();
            return;
        }
    }

    //The last group is empty!
    index = mBuddyOrGroupList.size();
    beginInsertRows(QModelIndex(), index, index);
    mBuddyOrGroupList.append(new BuddyOrGroup(buddy));
    endInsertRows();
}

void QyncBuddyListModel::addGroup(const QSharedPointer<QyncGroupObject> &group)
{
    int index;

    for (QList<BuddyOrGroup*>::iterator it = mBuddyOrGroupList.begin(); it != mBuddyOrGroupList.end(); ++it) {
        if (!(*it)->isGroup()) continue;

        //Ignore the duplicated group.
        if ((*it)->mGroup == group) return;
        //Sort the groups by name
        if ((*it)->mGroup->getName().compare(group->getName()) > 0) {
            index = mBuddyOrGroupList.indexOf(*it);
            beginInsertRows(QModelIndex(), index, index);
            mBuddyOrGroupList.insert(it, new BuddyOrGroup(group));
            endInsertRows();
            return;
        }
    }

    index = mBuddyOrGroupList.size();
    beginInsertRows(QModelIndex(), index, index);
    mBuddyOrGroupList.append(new BuddyOrGroup(group));
    endInsertRows();
}

