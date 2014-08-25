#include <glib.h>

#include "sipe-backend.h"

void sipe_backend_chat_session_destroy(struct sipe_backend_chat_session * /*session*/)
{
    SIPE_DEBUG_INFO("STUB %s", __func__);
}

void sipe_backend_chat_add(struct sipe_backend_chat_session * /*backend_session*/,
        const gchar * /*uri*/,
        gboolean /*is_new*/)
{
    SIPE_DEBUG_INFO("STUB %s", __func__);
}

void sipe_backend_chat_close(struct sipe_backend_chat_session * /*backend_session*/)
{
    SIPE_DEBUG_INFO("STUB %s", __func__);
}

struct sipe_backend_chat_session *sipe_backend_chat_create(
        struct sipe_core_public * /*sipe_public*/,
        struct sipe_chat_session * /*session*/,
        const gchar * /*title*/,
        const gchar * /*nick*/)
{
    SIPE_DEBUG_INFO("STUB %s", __func__);
    return 0;
}

gboolean sipe_backend_chat_find(struct sipe_backend_chat_session * /*backend_session*/,
        const gchar * /*uri*/)
{
    SIPE_DEBUG_INFO("STUB %s", __func__);
    return FALSE;
}

gboolean sipe_backend_chat_is_operator(struct sipe_backend_chat_session * /*backend_session*/,
        const gchar * /*uri*/)
{
    SIPE_DEBUG_INFO("STUB %s", __func__);
    return FALSE;
}

void sipe_backend_chat_message(struct sipe_core_public * /*sipe_public*/,
        struct sipe_backend_chat_session * /*backend_session*/,
        const gchar * /*from*/,
        time_t /*when*/,
        const gchar * /*html*/)
{
    SIPE_DEBUG_INFO("STUB %s", __func__);
}

void sipe_backend_chat_operator(struct sipe_backend_chat_session * /*backend_session*/,
        const gchar * /*uri*/)
{
    SIPE_DEBUG_INFO("STUB %s", __func__);
}

void sipe_backend_chat_rejoin(struct sipe_core_public * /*sipe_public*/,
        struct sipe_backend_chat_session * /*backend_session*/,
        const gchar * /*nick*/,
        const gchar * /*title*/)
{
    SIPE_DEBUG_INFO("STUB %s", __func__);
}

void sipe_backend_chat_rejoin_all(struct sipe_core_public * /*sipe_public*/)
{
    SIPE_DEBUG_INFO("STUB %s", __func__);
}

void sipe_backend_chat_remove(struct sipe_backend_chat_session * /*backend_session*/,
        const gchar * /*uri*/)
{
    SIPE_DEBUG_INFO("STUB %s", __func__);
}

void sipe_backend_chat_show(struct sipe_backend_chat_session * /*backend_session*/)
{
    SIPE_DEBUG_INFO("STUB %s", __func__);
}

void sipe_backend_chat_topic(struct sipe_backend_chat_session * /*backend_session*/,
        const gchar * /*topic*/)
{
    SIPE_DEBUG_INFO("STUB %s", __func__);
}
