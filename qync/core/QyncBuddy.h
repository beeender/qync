#ifndef QYNCBUDDY_H
#define QYNCBUDDY_H

#include <QSharedPointer>
#include <QWeakPointer>
#include <QList>
#include <QByteArray>
#include <QUrl>
#include <QMap>

#include "QyncBuddyObject.h"

class QyncGroup;
class QyncBuddy : public QObject, public QyncBuddyObject
{
    Q_OBJECT
    Q_PROPERTY(QString account READ getName NOTIFY onChanged)
    Q_PROPERTY(QString alias READ getAlias NOTIFY onChanged)
    Q_PROPERTY(QUrl imageUrl READ getImageUrl NOTIFY onChanged)

    public:
        explicit QyncBuddy(const QString &account, QObject *parent = 0);
        virtual ~QyncBuddy();

        void setAlias(const QString &alias) { mBuddy->mAlias = alias; };
        void setImage(const QString &imgName);
        const QByteArray *getImageHash() const { return &mBuddy->mImageName; };
        QUrl getImageUrl() const;
        void setGroup(const QSharedPointer<const QyncGroup> group);
        void setId(const qint32 id) { mId = id; };
        const QSharedPointer<const QyncGroup> getGroup() const { return mGroup; };
        void setPropertyString(const QyncSipe::BuddyInfoFieldE field, const QString &str);

        //Virtual functions of QyncBuddyObject
        virtual QString getName() const { return mBuddy->mAccount; };
        virtual QString getAlias() const { return mBuddy->mAlias; };
        virtual QString getGroupName() const;
        virtual QString getPropertyString(const QyncSipe::BuddyInfoFieldE field) const;

    private:
        class Buddy {
            public:
            ~Buddy();

            static QSharedPointer<Buddy> create(const QString &account);
            static inline QSharedPointer<Buddy> find(const QString &account);

            QString mAccount;
            QString mAlias;
            QByteArray mImageName;
            QMap<QyncSipe::BuddyInfoFieldE, QString> mPropMap;

            private:
            Buddy(const QString &account);

            private:
            static QList< QWeakPointer<Buddy> > mBuddyPool;
        };

        explicit QyncBuddy(QSharedPointer<Buddy> buddy, QObject *parent = 0);

        QSharedPointer<Buddy> mBuddy;
        QSharedPointer<const QyncGroup> mGroup;
        qint32 mId;

    signals:
        void onChanged();

    //Comparators
    public:
        struct BuddyNameComparator :
            public std::binary_function<QSharedPointer<QyncBuddy> &, QSharedPointer<QyncBuddy>, bool> {
                bool operator()(const QSharedPointer<const QyncBuddy> &lhs,
                        const QSharedPointer<const QyncBuddy> rhs) const {
                    return lhs->getName() < rhs->getName();
                };
            };

};

#endif // QYNCBUDDY_H
