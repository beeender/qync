#include <glib.h>

#include "sipe-backend.h"

void sipe_backend_groupchat_room_add(struct sipe_core_public * /*sipe_public*/,
        const gchar * /*uri*/,
        const gchar * /*name*/,
        const gchar * /*description*/,
        guint /*users*/,
        guint32 /*flags*/)
{
    SIPE_DEBUG_INFO_NOFORMAT("STUB sipe_backend_groupchat_room_add");
}

void sipe_backend_groupchat_room_terminate(struct sipe_core_public * /*sipe_public*/)
{
    SIPE_DEBUG_INFO_NOFORMAT("STUB sipe_backend_groupchat_room_terminate");
}

