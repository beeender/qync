#ifndef QYNCBUDDYOBJECT_H
#define QYNCBUDDYOBJECT_H

#include <QObject>
#include <QSharedPointer>

class QyncBuddyObject: public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ getName NOTIFY onChanged)
    Q_PROPERTY(QString group READ getGroup NOTIFY onChanged)
    Q_PROPERTY(QString alias READ getAlias)

    public:
        QyncBuddyObject(const QString &name);

        const QString &getName() const { return mName; };
        const QString &getGroup() const { return mGroup; };
        const QString &getAlias() const { return mAlias; };
        qint32 getGroupId() const { return mGroupId; };
        void setAlias(const QString &name);
        void setGroup(const QString &group);
        void setGroupId(const qint32 groupId);

    private:
        QString mAlias;
        QString mName;
        QString mGroup;
        qint32 mGroupId;

    signals:
        void onChanged();
};

#endif
