#include <glib.h>

#include "sipe-backend.h"

void sipe_backend_notify_message_error(struct sipe_core_public *sipe_public,
				       struct sipe_backend_chat_session *backend_session,
				       const gchar *who,
				       const gchar *message)
{
    SIPE_DEBUG_INFO_NOFORMAT("STUB sipe_backend_notify_message_error");
}

void sipe_backend_notify_message_info(struct sipe_core_public *sipe_public,
				      struct sipe_backend_chat_session *backend_session,
				      const gchar *who,
				      const gchar *message)
{
    SIPE_DEBUG_INFO_NOFORMAT("STUB sipe_backend_notify_message_info");
}

void sipe_backend_notify_error(struct sipe_core_public *sipe_public,
			       const gchar *title,
			       const gchar *msg)
{
    SIPE_DEBUG_INFO_NOFORMAT("STUB sipe_backend_notify_error");
}

