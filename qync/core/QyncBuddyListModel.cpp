#define QYNCBUDDYLISTMODEL_CPP

#include <algorithm>

#include "QyncBuddyListModel.h"

QyncBuddyListModel::QyncBuddyListModel(QObject * /*parent*/)
{
}

QyncBuddyListModel::~QyncBuddyListModel()
{
    mBuddyList.clear();
}

QHash<int, QByteArray> QyncBuddyListModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[BuddyRole] = "buddy";
    return roles;
}

int QyncBuddyListModel::rowCount(const QModelIndex & /*parent*/) const
{
    return mBuddyList.size();
}

QVariant QyncBuddyListModel::data(const QModelIndex & index, int role) const
{
    switch (role) {
        case BuddyRole:
            return QVariant::fromValue<QObject *>(mBuddyList.at(index.row()).data());
        default:
            break;
    }

    return QVariant();
}

void QyncBuddyListModel::addBuddy(const QSharedPointer<QyncBuddy> &buddy)
{
    int index;
    auto it = lower_bound(mBuddyList.begin(), mBuddyList.end(),
            buddy, QyncBuddy::BuddyNameComparator());
    if (it == mBuddyList.end()) {
        index = mBuddyList.size();
    } else {
        index = mBuddyList.indexOf(*it);
    }
    beginInsertRows(QModelIndex(), index, index);
    mBuddyList.insert(it, buddy);
    endInsertRows();
}

QSharedPointer<QyncBuddy> QyncBuddyListModel::findBuddy(const QString &name) const
{
    auto it = std::find_if(mBuddyList.begin(), mBuddyList.end(),
            [&name](const QSharedPointer<QyncBuddy> &b) {
                return (b->getName().compare(name) == 0);
            });

    if(it != mBuddyList.end()) return (*it);
    return QSharedPointer<QyncBuddy>();
}

