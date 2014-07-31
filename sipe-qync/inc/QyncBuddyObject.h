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

        const QString &getName() const { return mName; };
        const QString &getGroup() const { return mGroup; };
        const QString &getAlias() const { return mAlias; };
        const quint32 &getGroupId() const { return mGroupId; };
    private:
        void setAlias(const QString &name);
        void setGroup(const QString &group);
        void setGroupId(const quint32 groupId);

        QString mAlias;
        QString mName;
        QString mGroup;
        quint32 mGroupId;

    signals:
        void onChanged();
};

#endif
