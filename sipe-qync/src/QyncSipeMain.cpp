#include <glib.h>
#include "sipe-backend.h"

extern "C"
gchar *sipe_backend_version(void)
{
    return g_strdup("qync");
}
