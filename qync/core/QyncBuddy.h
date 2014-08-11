#ifndef QYNCBUDDY_H
#define QYNCBUDDY_H

#include <QSharedPointer>
#include <QWeakPointer>
#include <QList>
#include <QByteArray>

#include "QyncBuddyObject.h"

class QyncGroup;
class QyncBuddy : public QObject, public QyncBuddyObject
{
    Q_OBJECT
    Q_PROPERTY(QString account READ getName)
    Q_PROPERTY(QString alias READ getAlias)

    public:
        explicit QyncBuddy(const QString &account, QObject *parent = 0);
        virtual ~QyncBuddy();

        void setAlias(const QString &alias) { mBuddy->mAlias = alias; };
        void setImage(const QByteArray &checksum);
        const QByteArray *getImageName() const { return &mBuddy->mImageName; };
        void setGroup(const QSharedPointer<const QyncGroup> group);
        void setId(const qint32 id) { mId = id; };
        const QSharedPointer<const QyncGroup> getGroup() const { return mGroup; }

        //Virtual functions of QyncBuddyObject
        virtual QString getName() const { return mBuddy->mAccount; };
        virtual QString getAlias() const { return mBuddy->mAlias; };

    private:
        class Buddy {
            public:
            ~Buddy();

            static QSharedPointer<Buddy> create(const QString &account);
            static inline QSharedPointer<Buddy> find(const QString &account);

            QString mAccount;
            QString mAlias;
            QByteArray mImageName;

            private:
            Buddy(const QString &account);

            private:
            static QList< QWeakPointer<Buddy> > mBuddyPool;
        };

        explicit QyncBuddy(QSharedPointer<Buddy> buddy, QObject *parent = 0);

        QSharedPointer<Buddy> mBuddy;
        QSharedPointer<const QyncGroup> mGroup;
        qint32 mId;
};

#endif // QYNCBUDDY_H
