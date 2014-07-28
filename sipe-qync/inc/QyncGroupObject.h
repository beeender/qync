#ifndef QYNCGROUPOBJECT_H
#define QYNCGROUPOBJECT_H

#include <QObject>

class QyncDB;
class QyncGroupObject: public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ getName NOTIFY onChanged)
    Q_PROPERTY(quint32 id READ getId NOTIFY onChanged)

    friend class QyncDB;

    public:
        QyncGroupObject(quint32 id) { mId = id; } ;

        QString getName() { return mName; };
        quint32 getId() { return mId; };

    protected:
        void setName(const QString name) { mName = name; };

    private:
        QString mName;
        quint32 mId;

    signals:
        void onChanged();

};

#endif
