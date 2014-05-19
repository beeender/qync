#include <glib.h>

#include "sipe-backend.h"

void sipe_backend_connection_completed(struct sipe_core_public *sipe_public)
{
	SIPE_DEBUG_INFO_NOFORMAT("sipe_backend_connection_completed");
}

void sipe_backend_connection_error(struct sipe_core_public *sipe_public,
				   sipe_connection_error error,
				   const gchar *msg)
{
	SIPE_DEBUG_INFO_NOFORMAT("sipe_backend_connection_error");
}

gboolean sipe_backend_connection_is_disconnecting(struct sipe_core_public *sipe_public)
{
	SIPE_DEBUG_INFO_NOFORMAT("sipe_backend_connection_is_disconnecting");
    return FALSE;
}

gboolean sipe_backend_connection_is_valid(struct sipe_core_public *sipe_public)
{
	SIPE_DEBUG_INFO_NOFORMAT("sipe_backend_connection_is_valid");
    return FALSE;
}
