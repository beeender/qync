#include <glib.h>
#include "sipe-backend.h"

gchar *sipe_backend_version(void)
{
    static char version[] = "qync";
    return (gchar*)version;
}
