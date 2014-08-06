#ifndef QYNCCATEGORYLISTMODEL_H
#define QYNCCATEGORYLISTMODEL_H

#include <QList>
#include <QAbstractListModel>
#include <QSharedPointer>

#include "QyncBuddyObject.h"
#include "QyncGroupObject.h"
#include "QyncBuddyListModel.h"

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
    void addBuddy(const QSharedPointer<QyncBuddyObject> &buddy);
    void addGroup(const QSharedPointer<QyncGroupObject> &group);
    Q_INVOKABLE QObject *getBuddyListModel(int index);

private:
    struct Category {
        Category(const QSharedPointer<QyncGroupObject> group) : mGroup(group) {};
        QSharedPointer<QyncGroupObject> mGroup;
        QyncBuddyListModel mBuddyListModel;
        const QString &getName() { return mGroup->getName(); };
    };

    QList<Category *> mCategoryList;
};

#endif

