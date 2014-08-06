#define QYNCCATEGORYLISTMODEL_CPP

#include "QyncCategoryListModel.h"

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

void QyncCategoryListModel::addBuddy(const QSharedPointer<QyncBuddyObject> &buddy)
{
    QyncBuddyListModel *bListModel = nullptr;
    foreach(auto cat, mCategoryList) {
        if (cat->getName().compare(buddy->getGroup()) == 0) {
            bListModel = &cat->mBuddyListModel;
        }
    }
    if (!bListModel) qFatal("Cannot find group %s", buddy->getGroup().toStdString().c_str());

    bListModel->addBuddy(buddy);
}

void QyncCategoryListModel::addGroup(const QSharedPointer<QyncGroupObject> &group)
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

QObject *QyncCategoryListModel::getBuddyListModel(int index)
{
    if (index < 0 || index >= mCategoryList.size()) return nullptr;

    return &mCategoryList.at(index)->mBuddyListModel;
}

