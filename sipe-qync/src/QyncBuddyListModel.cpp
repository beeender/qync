#define QYNCBUDDYLISTMODEL_CPP

#include "QyncBuddyListModel.h"

QyncBuddyListModel::QyncBuddyListModel(QObject *parent)
{
}

QyncBuddyListModel::QyncBuddyListModel(QList<QyncBuddyObject *> buddyList, QObject *parent)
{
}

QHash<int, QByteArray> QyncBuddyListModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[GroupRole] = "group";
    roles[AliasRole] = "alias";
    return roles;
}

int QyncBuddyListModel::rowCount(const QModelIndex & parent) const
{
    return mBuddyList.size();
}

QVariant QyncBuddyListModel::data(const QModelIndex & index, int role) const
{
    switch (role) {
        case NameRole:
            return QVariant(mBuddyList.at(index.row())->getName());
        case GroupRole:
            return QVariant(mBuddyList.at(index.row())->getGroup());
        case AliasRole:
            return QVariant(mBuddyList.at(index.row())->getAlias());
        default:
            break;
    }

    return QVariant();
}

void QyncBuddyListModel::addBuddy(QyncBuddyObject &buddy)
{
    int index = mBuddyList.size();
    beginInsertRows(QModelIndex(), index, index);
    mBuddyList.append(&buddy);
    endInsertRows();
}
