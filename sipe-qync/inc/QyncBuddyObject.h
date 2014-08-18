#ifndef QYNCBUDDYOBJECT_H
#define QYNCBUDDYOBJECT_H

#include <QSharedPointer>

#include "QyncSipe.h"

class QyncBuddyObject
{
    public:
        virtual ~QyncBuddyObject();

        virtual QString getName() const = 0;
        virtual QString getAlias() const = 0;
        virtual QString getServerAlias() const { return getAlias(); };
        virtual QString getGroupName() const = 0;
        virtual QString getPropertyString(const QyncSipe::BuddyInfoFieldE field) const = 0;
        virtual bool isBlocked() const { return false; };

    protected:
        QyncBuddyObject();
};

#endif //QYNCBUDDYOBJECT_H
