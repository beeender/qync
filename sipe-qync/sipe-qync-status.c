#include <glib.h>

#include "sipe-backend.h"

guint sipe_backend_status(struct sipe_core_public *sipe_public)
{
	SIPE_DEBUG_INFO_NOFORMAT("sipe_backend_status");
}

gboolean sipe_backend_status_changed(struct sipe_core_public *sipe_public,
				     guint activity,
				     const gchar *message)
{
	SIPE_DEBUG_INFO_NOFORMAT("sipe_backend_status_changed");
}

void sipe_backend_status_and_note(struct sipe_core_public *sipe_public,
				  guint activity,
				  const gchar *message)
{
	SIPE_DEBUG_INFO_NOFORMAT("sipe_backend_status_and_note");
}
