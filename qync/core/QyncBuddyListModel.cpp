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
    mBuddyList.clear();
}

QHash<int, QByteArray> QyncBuddyListModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[AliasRole] = "aliasName";
    return roles;
}

int QyncBuddyListModel::rowCount(const QModelIndex & /*parent*/) const
{
    return mBuddyList.size();
}

QVariant QyncBuddyListModel::data(const QModelIndex & index, int role) const
{
    switch (role) {
        case AliasRole:
            return QVariant(mBuddyList.at(index.row())->getAlias());
        default:
            break;
    }

    return QVariant();
}

void QyncBuddyListModel::addBuddy(const QSharedPointer<QyncBuddyObject> &buddy)
{
    int index;

    for (auto it = mBuddyList.begin(); it != mBuddyList.end(); ++it) {
        //Ignore the duplicated buddy.
        if ((*it) == buddy) return;
        //Sort the buddies by name
        if ((*it)->getAlias().compare(buddy->getAlias()) > 0) {
            index = mBuddyList.indexOf(*it);
            beginInsertRows(QModelIndex(), index, index);
            mBuddyList.insert(it, buddy);
            endInsertRows();
            return;
        }
    }

    index = mBuddyList.size();
    beginInsertRows(QModelIndex(), index, index);
    mBuddyList.append(buddy);
    endInsertRows();
}

