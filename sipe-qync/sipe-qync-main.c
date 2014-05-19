#include <glib.h>

gchar *sipe_backend_version(void)
{
    char *version = malloc(5);
    memcpy(version, "qync", 5);
    return (gchar*)version;
}
