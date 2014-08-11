#ifndef QYNCBUDDYOBJECT_H
#define QYNCBUDDYOBJECT_H

#include <QSharedPointer>

class QyncBuddyObject
{
    public:
        virtual ~QyncBuddyObject();

        virtual QString getName() const = 0;
        virtual QString getAlias() const = 0;

    protected:
        QyncBuddyObject();
};

#endif //QYNCBUDDYOBJECT_H
