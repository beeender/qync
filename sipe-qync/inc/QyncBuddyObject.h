#ifndef QYNCBUDDYOBJECT_H
#define QYNCBUDDYOBJECT_H

#include <QSharedPointer>

class QyncBuddyObject
{
    public:
        virtual ~QyncBuddyObject();

        virtual const QString getName() const = 0;
        virtual const QString getAlias() const = 0;

    protected:
        QyncBuddyObject();
};

#endif
