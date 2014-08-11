#define QYNCCATEGORYLISTMODEL_CPP

#include <QQmlEngine>

#include "QyncCategoryListModel.h"
#include "QyncBuddy.h"
#include "QyncGroup.h"

QyncCategoryListModel::QyncCategoryListModel(QObject * /*parent*/)
{
}

QyncCategoryListModel::~QyncCategoryListModel()
{
    foreach(auto cat, mCategoryList) {
        delete cat;
    }
    mCategoryList.clear();
}

QHash<int, QByteArray> QyncCategoryListModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[TypeRole] = "type";
    roles[NameRole] = "name";
    return roles;
}

int QyncCategoryListModel::rowCount(const QModelIndex & /*parent*/) const
{
    return mCategoryList.size();
}

QVariant QyncCategoryListModel::data(const QModelIndex & index, int role) const
{
    switch (role) {
        case NameRole:
            return QVariant(mCategoryList.at(index.row())->getName());
        case TypeRole:
        default:
            break;
    }

    return QVariant();
}

void QyncCategoryListModel::addBuddy(const QSharedPointer<QyncBuddy> &buddy)
{
    QyncBuddyListModel *bListModel = nullptr;
    foreach(auto cat, mCategoryList) {
        if (cat->mGroup == buddy->getGroup()) {
            bListModel = &cat->mBuddyListModel;
        }
    }
    if (!bListModel) {
        qFatal("Cannot find group %s",
            buddy->getGroup()->getName().toStdString().c_str());
    }

    bListModel->addBuddy(buddy);
}

void QyncCategoryListModel::addBuddy(const QSharedPointer<QyncBuddy> &buddy, const QString &groupName)
{
    if (!buddy->getGroup().isNull()) {
        qFatal("The group of given buddy %s must be NULL!",
                buddy->getName().toStdString().c_str());
    }

    QyncBuddyListModel *bListModel = nullptr;
    foreach(auto cat, mCategoryList) {
        if (cat->mGroup->getName().compare(groupName) == 0) {
            bListModel = &cat->mBuddyListModel;
            buddy->setGroup(cat->mGroup);
        }
    }
    if (!bListModel) {
        qFatal("Cannot find group %s",
            buddy->getGroup()->getName().toStdString().c_str());
    }

    bListModel->addBuddy(buddy);
}

void QyncCategoryListModel::addGroup(const QSharedPointer<QyncGroup> &group)
{
    int index;

    for (auto it = mCategoryList.begin(); it != mCategoryList.end(); ++it) {
        //Ignore the duplicated group.
        if ((*it)->mGroup == group) return;
        //Sort the groups by name
        if ((*it)->mGroup->getName().compare(group->getName()) > 0) {
            index = mCategoryList.indexOf(*it);
            beginInsertRows(QModelIndex(), index, index);
            mCategoryList.insert(it, new Category(group));
            endInsertRows();
            return;
        }
    }

    index = mCategoryList.size();
    beginInsertRows(QModelIndex(), index, index);
    mCategoryList.append(new Category(group));
    endInsertRows();
}

QSharedPointer<QyncGroup> QyncCategoryListModel::findGroup(const QString &groupName)
{
    foreach(auto i, mCategoryList) {
        if (i->getName().compare(groupName) == 0) {
            return i->mGroup;
        }
    }

    return QSharedPointer<QyncGroup>();
}

QSharedPointer<QyncBuddy> QyncCategoryListModel::findBuddy(const QString &buddyName, const QString &groupName)
{
    QyncBuddyListModel *bListModel = nullptr;
    foreach(auto cat, mCategoryList) {
        if (cat->mGroup->getName().compare(groupName) == 0) {
            bListModel = &cat->mBuddyListModel;
        }
    }

    if (!bListModel) return QSharedPointer<QyncBuddy>();

    return bListModel->findBuddy(buddyName);
}

QSharedPointer<QyncBuddy> QyncCategoryListModel::findBuddy(const QString &buddyName)
{
    QSharedPointer<QyncBuddy> buddy;
    foreach(auto cat, mCategoryList) {
        auto b = cat->mBuddyListModel.findBuddy(buddyName);
        if (b.isNull()) continue;
        buddy = b;
    }

    return buddy;
}

QList<QyncBuddyObject *> QyncCategoryListModel::findAllBuddies(const QString &buddyName, const QString &groupName)
{
    QList<QyncBuddyObject *> list;
    foreach (auto cat, mCategoryList) {
        if (groupName.isEmpty() || cat->mGroup->getName().compare(groupName) == 0) {
            if (buddyName.isEmpty()) {
                foreach (auto buddy, cat->mBuddyListModel.getAllBuddies()) {
                    list.append(buddy.data());
                }
            } else {
                auto buddy = cat->mBuddyListModel.findBuddy(buddyName);
                if (!buddy.isNull()) list.append(buddy.data());
            }
        }
    }

    return list;
}

QObject *QyncCategoryListModel::getBuddyListModel(int index)
{
    if (index < 0 || index >= mCategoryList.size()) return nullptr;

    QQmlEngine::setObjectOwnership(&mCategoryList.at(index)->mBuddyListModel,
            QQmlEngine::CppOwnership);
    return &mCategoryList.at(index)->mBuddyListModel;
}

