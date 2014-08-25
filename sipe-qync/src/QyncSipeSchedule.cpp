#include <glib.h>

#include <QTimer>

#include "sipe-backend.h"
#include "sipe-core.h"

class QyncSipeSchedule : QObject
{
    Q_OBJECT

public:
    QyncSipeSchedule(struct sipe_core_public *sipe_public, guint timeout,
            gpointer data, QObject *parent = 0);

    void cancel();
private:
    ~QyncSipeSchedule();

    QTimer mTimer;
    gpointer mData;

private slots:
        void schedule();
};

QyncSipeSchedule::QyncSipeSchedule(struct sipe_core_public * /*sipe_public*/, guint timeout,
        gpointer data, QObject *parent)
:QObject(parent), mTimer()
{
    mData = data;
    mTimer.setSingleShot(true);
    connect(&mTimer, SIGNAL(timeout()), this, SLOT(schedule()));
    mTimer.start(timeout);
}

QyncSipeSchedule::~QyncSipeSchedule()
{
}

void QyncSipeSchedule::cancel()
{
    mTimer.stop();
    delete this;
}

void QyncSipeSchedule::schedule()
{
    sipe_core_schedule_execute(mData);
    delete this;
}

gpointer sipe_backend_schedule_seconds(struct sipe_core_public *sipe_public,
        guint timeout,
        gpointer data)
{
    SIPE_DEBUG_INFO_NOFORMAT("sipe_backend_schedule_seconds");
    QyncSipeSchedule *schedule = new QyncSipeSchedule(sipe_public, timeout*1000, data);
    return schedule;
}

gpointer sipe_backend_schedule_mseconds(struct sipe_core_public *sipe_public,
        guint timeout,
        gpointer data)
{
    SIPE_DEBUG_INFO_NOFORMAT("sipe_backend_schedule_mseconds");
    QyncSipeSchedule *schedule = new QyncSipeSchedule(sipe_public, timeout, data);
    return schedule;
}

void sipe_backend_schedule_cancel(struct sipe_core_public * /*sipe_public*/,
        gpointer data)
{
    SIPE_DEBUG_INFO_NOFORMAT("sipe_backend_schedule_cancel");
    ((QyncSipeSchedule *)data)->cancel();
}

#include "QyncSipeSchedule.moc"

