#ifndef QYNCGROUPOBJECT_H
#define QYNCGROUPOBJECT_H

#include <QObject>

class QyncDB;
class QyncGroupObject: public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ getName NOTIFY onChanged)
    Q_PROPERTY(quint32 id READ getId NOTIFY onChanged)

    public:
        QyncGroupObject(quint32 id) { mId = id; } ;

        const QString &getName() { return mName; };
        qint32 getId() { return mId; };
        void setName(const QString name) { mName = name; };

    private:
        QString mName;
        qint32 mId;

    signals:
        void onChanged();

};

#endif
