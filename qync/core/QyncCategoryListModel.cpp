#define QYNCCATEGORYLISTMODEL_CPP

#include <QQmlEngine>
#include <algorithm>
#include <iterator>

#include "QyncCategoryListModel.h"
#include "QyncBuddy.h"
#include "QyncGroup.h"

QyncCategoryListModel::QyncCategoryListModel(QObject * /*parent*/)
{
}

QyncCategoryListModel::~QyncCategoryListModel()
{
    foreach(auto &cat, mCategoryList) {
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
    auto it = std::find_if(mCategoryList.begin(), mCategoryList.end(),
            [&buddy](const Category *cat) {
                return (cat->mGroup == buddy->getGroup());
            });
    if (it == mCategoryList.end()) {
        qFatal("Cannot find group %s",
            buddy->getGroup()->getName().toStdString().c_str());
    }
    (*it)->mBuddyListModel.addBuddy(buddy);
}

void QyncCategoryListModel::addBuddy(const QSharedPointer<QyncBuddy> &buddy, const QString &groupName)
{
    if (!buddy->getGroup().isNull()) {
        qFatal("The group of given buddy %s must be NULL!",
                buddy->getName().toStdString().c_str());
    }

    auto it = std::find_if(mCategoryList.begin(), mCategoryList.end(),
            [&groupName](const Category *cat){
                return (cat->getName().compare(groupName) == 0);
            });
    if (it == mCategoryList.end()) {
        qFatal("Cannot find group %s",
            buddy->getGroup()->getName().toStdString().c_str());
    }

    buddy->setGroup((*it)->mGroup);
    (*it)->mBuddyListModel.addBuddy(buddy);
}

void QyncCategoryListModel::addGroup(const QSharedPointer<QyncGroup> &group)
{
    int index;
    auto it = lower_bound(mCategoryList.begin(), mCategoryList.end(), group->getName(), CatPtrStrComparator());
    if (it == mCategoryList.end()) {
        index = mCategoryList.size();
    } else {
        index = mCategoryList.indexOf(*it);
    }
    beginInsertRows(QModelIndex(), index, index);
    mCategoryList.insert(it, new Category(group));
    endInsertRows();
}

QSharedPointer<QyncGroup> QyncCategoryListModel::findGroup(const QString &groupName)
{
    auto it = std::find_if(mCategoryList.begin(), mCategoryList.end(),
            [&groupName](const Category *cat) {
                return (cat->getName().compare(groupName) == 0);
            });
    if (it == mCategoryList.end()) return QSharedPointer<QyncGroup>();

    return (*it)->mGroup;
}

QSharedPointer<QyncBuddy> QyncCategoryListModel::findBuddy(const QString &buddyName, const QString &groupName)
{
    auto it = std::find_if(mCategoryList.begin(), mCategoryList.end(),
            [&groupName](const Category *cat) {
                return (cat->mGroup->getName().compare(groupName) == 0);
            });
    if (it == mCategoryList.end()) return QSharedPointer<QyncBuddy>();

    return (*it)->mBuddyListModel.findBuddy(buddyName);
}

QSharedPointer<QyncBuddy> QyncCategoryListModel::findBuddy(const QString &buddyName)
{
    QSharedPointer<QyncBuddy> buddy;
    foreach (auto &cat, mCategoryList) {
        auto b = cat->mBuddyListModel.findBuddy(buddyName);
        if (b.isNull()) continue;
        buddy = b;
        break;
    }

    return buddy;
}

QList<const QyncBuddyObject *> QyncCategoryListModel::findAllBuddies(const QString &buddyName, const QString &groupName)
{
    QList<const QyncBuddyObject *> list;
    foreach (auto &cat, mCategoryList) {
        if (groupName.isEmpty() || cat->mGroup->getName().compare(groupName) == 0) {
            if (buddyName.isEmpty()) {
                auto &tmpList = cat->mBuddyListModel.getAllBuddies();
                transform(tmpList.begin(), tmpList.end(), std::back_inserter(list),
                        [](QSharedPointer<QyncBuddy> b) {
                            return b.data();
                        });
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

