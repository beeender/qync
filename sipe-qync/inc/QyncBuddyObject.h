#ifndef QYNCBUDDYOBJECT_H
#define QYNCBUDDYOBJECT_H

#include <QSharedPointer>

#include "QyncSipe.h"

class QyncBuddyObject : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString account READ getName NOTIFY onChanged)
    Q_PROPERTY(QString alias READ getAlias NOTIFY onChanged)
    Q_PROPERTY(QyncSipe::LoginStatusE status READ getStatus NOTIFY onChanged)

    public:
        QyncBuddyObject(QObject *parent = 0);
        virtual ~QyncBuddyObject();

        virtual QString getName() const = 0;
        virtual QString getAlias() const = 0;
        virtual QString getServerAlias() const { return getAlias(); };
        virtual QString getGroupName() const = 0;
        virtual QString getPropertyString(const QyncSipe::BuddyInfoFieldE field) const = 0;
        virtual void setStatus(QyncSipe::LoginStatusE status) = 0;
        virtual QyncSipe::LoginStatusE getStatus() const = 0;
        virtual bool isBlocked() const { return false; };

    protected:
        QyncBuddyObject();

    signals:
        void onChanged();
};

#endif //QYNCBUDDYOBJECT_H
