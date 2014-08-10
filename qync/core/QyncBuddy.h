#ifndef QYNCBUDDY_H
#define QYNCBUDDY_H

#include <QSharedPointer>
#include <QWeakPointer>
#include <QList>

#include "QyncBuddyObject.h"

class QyncGroup;
class QyncBuddy : public QObject, public QyncBuddyObject
{
    Q_OBJECT

    public:
        explicit QyncBuddy(const QString &account, QObject *parent = 0);

        const QSharedPointer<const QyncGroup> getGroup() const { return mGroup; }
        void setAlias(const QString &alias) { mBuddy->setAlias(alias); };
        void setGroup(const QSharedPointer<const QyncGroup> group);

        //Virtual functions of QyncBuddyObject
        const QString getName() const { return mBuddy->getAccount(); };
        const QString getAlias() const { return mBuddy->getAlias(); };

    signals:

    private:
        class Buddy {
            public:
            ~Buddy();
            const QString &getAccount() { return mAccount; };
            const QString &getAlias() { return mAlias; };
            void setAlias(const QString &alias);

            static QSharedPointer<Buddy> createBuddy(const QString &account);

            private:
            Buddy(const QString &account);

            private:
            QString mAccount;
            QString mAlias;
            static QList< QWeakPointer<Buddy> > mBuddyPool;
        };

    QSharedPointer<Buddy> mBuddy;
    QSharedPointer<const QyncGroup> mGroup;
};

#endif // QYNCBUDDY_H
