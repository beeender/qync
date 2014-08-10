#ifndef QYNCCATEGORYLISTMODEL_H
#define QYNCCATEGORYLISTMODEL_H

#include <QList>
#include <QAbstractListModel>
#include <QSharedPointer>

#include "QyncBuddyListModel.h"

class QyncBuddy;
class QyncGroup;
class QyncCategoryListModel: public QAbstractListModel
{
    Q_OBJECT

public:
    enum CategoryRoles {
        TypeRole = Qt::UserRole + 1,
        NameRole
    };

    QyncCategoryListModel(QObject *parent = 0);
    virtual ~QyncCategoryListModel();

    virtual QHash<int, QByteArray> roleNames() const;
    virtual int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    void addBuddy(const QSharedPointer<QyncBuddy> &buddy);
    //Add an "group unknown" buddy. Only for DB init.
    void addBuddy(const QSharedPointer<QyncBuddy> &buddy, const QString &groupName);
    void addGroup(const QSharedPointer<QyncGroup> &group);
    QSharedPointer<QyncGroup> findGroup(const QString &groupName);
    QSharedPointer<QyncBuddy> findBuddy(const QString &buddyName, const QString &groupName);

    //QML calls
    Q_INVOKABLE QObject *getBuddyListModel(int index);

private:
    struct Category {
        Category(const QSharedPointer<QyncGroup> group) : mGroup(group) {};
        QSharedPointer<QyncGroup> mGroup;
        QyncBuddyListModel mBuddyListModel;
        const QString getName() { return mGroup->getName(); };
    };

    QList<Category *> mCategoryList;
};

#endif

