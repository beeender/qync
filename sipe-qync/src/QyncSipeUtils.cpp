
#include <glib.h>
#include "sipe-core.h"

#include "QyncSipeUtils.h"

QyncSipe::LoginStatusE QyncSipeUtils::SipeStatusToQync(int status)
{
    switch (status) {
        case SIPE_ACTIVITY_UNSET:
        case SIPE_ACTIVITY_OFFLINE:
            return QyncSipe::StatusOffline;
        case SIPE_ACTIVITY_AVAILABLE:
        case SIPE_ACTIVITY_ONLINE:
            return QyncSipe::StatusActive;
        case SIPE_ACTIVITY_INACTIVE:
            return QyncSipe::StatusInactive;
        case SIPE_ACTIVITY_BUSY:
        case SIPE_ACTIVITY_BUSYIDLE:
        case SIPE_ACTIVITY_ON_PHONE:
        case SIPE_ACTIVITY_IN_CONF:
        case SIPE_ACTIVITY_IN_MEETING:
            return QyncSipe::StatusBusy;
        case SIPE_ACTIVITY_DND:
        case SIPE_ACTIVITY_URGENT_ONLY:
            return QyncSipe::StatusDND;
        case SIPE_ACTIVITY_BRB:
        case SIPE_ACTIVITY_AWAY:
        case SIPE_ACTIVITY_LUNCH:
        case SIPE_ACTIVITY_OOF:
            return QyncSipe::StatusAway;
        case SIPE_ACTIVITY_INVISIBLE:
            break;
        default:
            break;
    }

    return QyncSipe::StatusActive;
}

int QyncSipeUtils::QyncStatusToSipe(QyncSipe::LoginStatusE status)
{
    switch (status) {
        case QyncSipe::StatusOffline:
            return SIPE_ACTIVITY_OFFLINE;
        case QyncSipe::StatusActive:
            return SIPE_ACTIVITY_AVAILABLE;
        case QyncSipe::StatusInactive:
            return SIPE_ACTIVITY_INACTIVE;
        case QyncSipe::StatusBusy:
            return SIPE_ACTIVITY_BUSY;
        case QyncSipe::StatusDND:
            return SIPE_ACTIVITY_DND;
        case QyncSipe::StatusAway:
            return SIPE_ACTIVITY_AWAY;
        default:
            break;
    }
    return SIPE_ACTIVITY_OFFLINE;
}

