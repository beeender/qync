#include <glib.h>

#include "sipe-backend.h"

void sipe_backend_chat_session_destroy(struct sipe_backend_chat_session *session)
{
}

void sipe_backend_chat_add(struct sipe_backend_chat_session *backend_session,
			   const gchar *uri,
			   gboolean is_new)
{
}

void sipe_backend_chat_close(struct sipe_backend_chat_session *backend_session)
{
}

struct sipe_backend_chat_session *sipe_backend_chat_create(
        struct sipe_core_public *sipe_public,
        struct sipe_chat_session *session,
        const gchar *title,
        const gchar *nick)
{
    return 0;
}

gboolean sipe_backend_chat_find(struct sipe_backend_chat_session *backend_session,
				const gchar *uri)
{
    return FALSE;
}

gboolean sipe_backend_chat_is_operator(struct sipe_backend_chat_session *backend_session,
				       const gchar *uri)
{
    return FALSE;
}

void sipe_backend_chat_message(struct sipe_core_public *sipe_public,
			       struct sipe_backend_chat_session *backend_session,
			       const gchar *from,
			       time_t when,
			       const gchar *html)
{
}

void sipe_backend_chat_operator(struct sipe_backend_chat_session *backend_session,
				const gchar *uri)
{
}

void sipe_backend_chat_rejoin(struct sipe_core_public *sipe_public,
			      struct sipe_backend_chat_session *backend_session,
			      const gchar *nick,
			      const gchar *title)
{
}

void sipe_backend_chat_rejoin_all(struct sipe_core_public *sipe_public)
{
}

void sipe_backend_chat_remove(struct sipe_backend_chat_session *backend_session,
			      const gchar *uri)
{
}

void sipe_backend_chat_show(struct sipe_backend_chat_session *backend_session)
{
}

void sipe_backend_chat_topic(struct sipe_backend_chat_session *backend_session,
			     const gchar *topic)
{
}
