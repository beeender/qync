#ifndef QYNCGROUP_H
#define QYNCGROUP_H

#include <QObject>

class QyncGroup: public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ getName NOTIFY onChanged)
    Q_PROPERTY(quint32 id READ getId NOTIFY onChanged)

    public:
        explicit QyncGroup(const QString &name);

        QString getName() const { return mName; };
        qint32 getId() const { return mId; };

        void setName(const QString &name) { mName = name; };
        void setId(qint32 id) { mId = id; };

    private:
        QString mName;
        qint32 mId;

    signals:
        void onChanged();

};

#endif //QYNCGROUP_H
