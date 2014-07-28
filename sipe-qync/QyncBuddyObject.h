#ifndef QYNCBUDDYOBJECT_H
#define QYNCBUDDYOBJECT_H

#include <QObject>


class QyncBuddyObject: public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ getName NOTIFY onChanged)
    Q_PROPERTY(QString group READ getGroup NOTIFY onChanged)
    Q_PROPERTY(QString alias READ getAlias)

    friend class QyncDB;

    public:
        QyncBuddyObject(const QString &name);

        QString getName() const { return mName; };
        QString getGroup() const { return mGroup; };
        QString getAlias() const { return mAlias; };
        quint32 getGroupId() const { return mGroupId; };
    private:
        void setAlias(const QString &name);
        void setGroup(const QString &group);
        void setGroupId(quint32 groupId);

        QString mAlias;
        QString mName;
        QString mGroup;
        quint32 mGroupId;

    signals:
        void onChanged();
};

#endif