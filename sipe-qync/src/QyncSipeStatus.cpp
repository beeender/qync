#include <glib.h>

#include "sipe-core.h"
#include "sipe-backend.h"
#include "QyncBackend.h"

guint sipe_backend_status(struct sipe_core_public *sipe_public)
{
	SIPE_DEBUG_INFO_NOFORMAT("STUB sipe_backend_status");
}

gboolean sipe_backend_status_changed(struct sipe_core_public *sipe_public,
				     guint activity,
				     const gchar *message)
{
	SIPE_DEBUG_INFO_NOFORMAT("sipe_backend_status_changed");
    QyncBackend *backend = (QyncBackend *)sipe_public->backend_private;
    if (backend->getDesiredStatus() == activity) return FALSE;

    return TRUE;
}

void sipe_backend_status_and_note(struct sipe_core_public *sipe_public,
				  guint activity,
				  const gchar *message)
{
	SIPE_DEBUG_INFO_NOFORMAT("sipe_backend_status_and_note");
    QyncBackend *backend = (QyncBackend *)sipe_public->backend_private;
    backend->setStatus(activity);
}
