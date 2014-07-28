#include <glib.h>

#include <sipe-backend.h>

void sipe_backend_user_feedback_typing(struct sipe_core_public *sipe_public,
				       const gchar *from)
{
	SIPE_DEBUG_INFO_NOFORMAT("STUB sipe_backend_user_feedback_typing");
}

void sipe_backend_user_feedback_typing_stop(struct sipe_core_public *sipe_public,
					    const gchar *from)
{
	SIPE_DEBUG_INFO_NOFORMAT("STUB sipe_backend_user_feedback_typing_stop");
}

void sipe_backend_user_ask(struct sipe_core_public *sipe_public,
			   const gchar *message,
			   const gchar *accept_label,
			   const gchar *decline_label,
			   gpointer key)
{
	SIPE_DEBUG_INFO_NOFORMAT("STUB sipe_backend_user_ask");
}

void sipe_backend_user_close_ask(gpointer key)
{
	SIPE_DEBUG_INFO_NOFORMAT("STUB sipe_backend_user_close_ask");
}
