#include <glib.h>

#include "sipe-backend.h"
#include "sipe-core.h"
#include "QyncBackend.h"
#include "QyncBuddyObject.h"
#include "QyncSipeUtils.h"

sipe_backend_buddy sipe_backend_buddy_find(struct sipe_core_public *sipe_public,
        const gchar *buddy_name,
        const gchar *group_name)
{
    SIPE_DEBUG_INFO("%s", __func__);

    QyncBackend *backend = (QyncBackend *)sipe_public->backend_private;
    return (sipe_backend_buddy)backend->findBuddy(buddy_name, group_name);
}

GSList* sipe_backend_buddy_find_all(struct sipe_core_public *sipe_public,
        const gchar *buddy_name,
        const gchar *group_name)
{
    SIPE_DEBUG_INFO("%s", __func__);

    QyncBackend *backend = (QyncBackend *)sipe_public->backend_private;
    return backend->findAllBuddies(buddy_name, group_name);
}

gchar* sipe_backend_buddy_get_name(struct sipe_core_public * /*sipe_public*/,
        const sipe_backend_buddy who)
{
    SIPE_DEBUG_INFO("%s", __func__);

    QyncBuddyObject* buddy = (QyncBuddyObject *)who;
    return g_strdup(buddy->getName().toStdString().c_str());
}

gchar* sipe_backend_buddy_get_alias(struct sipe_core_public * /*sipe_public*/,
        const sipe_backend_buddy who)
{
    SIPE_DEBUG_INFO("%s", __func__);
    QyncBuddyObject* buddy = (QyncBuddyObject *)who;
    return g_strdup(buddy->getAlias().toStdString().c_str());
}

gchar* sipe_backend_buddy_get_server_alias(struct sipe_core_public * /*sipe_public*/,
        const sipe_backend_buddy who)
{
    SIPE_DEBUG_INFO("%s", __func__);
    QyncBuddyObject* buddy = (QyncBuddyObject *)who;
    return g_strdup(buddy->getServerAlias().toStdString().c_str());
}

gchar *sipe_backend_buddy_get_local_alias(struct sipe_core_public * /*sipe_public*/,
        const sipe_backend_buddy /*who*/)
{
    SIPE_DEBUG_INFO("STUB %s", __func__);
    return g_strdup("");
}

gchar* sipe_backend_buddy_get_group_name(struct sipe_core_public * /*sipe_public*/,
        const sipe_backend_buddy who)
{
    SIPE_DEBUG_INFO("%s", __func__);
    QyncBuddyObject* buddy = (QyncBuddyObject *)who;
    return g_strdup(buddy->getGroupName().toStdString().c_str());
}

gchar* sipe_backend_buddy_get_string(struct sipe_core_public * /*sipe_public*/,
        sipe_backend_buddy who,
        const sipe_buddy_info_fields key)
{
    SIPE_DEBUG_INFO("%s", __func__);
    QyncBuddyObject* buddy = (QyncBuddyObject *)who;
    return g_strdup(buddy->getPropertyString(
                QyncSipeUtils::SipeBuddyInfoFieldToQync(key)).toStdString().c_str());
}

void sipe_backend_buddy_set_string(struct sipe_core_public *sipe_public,
        sipe_backend_buddy buddy,
        const sipe_buddy_info_fields key,
        const gchar *val)
{
    SIPE_DEBUG_INFO("%s", __func__);
    QyncBackend *backend = reinterpret_cast<QyncBackend *>(sipe_public->backend_private);
    backend->setBuddyProperty(static_cast<QyncBuddyObject*>(buddy), key, val);
}

void sipe_backend_buddy_refresh_properties(struct sipe_core_public * /*sipe_public*/,
        const gchar * /*uri*/)
{
    SIPE_DEBUG_INFO("STUB %s", __func__);
}

guint sipe_backend_buddy_get_status(struct sipe_core_public * /*sipe_public*/,
        const gchar * /*uri*/)
{
    SIPE_DEBUG_INFO("STUB %s", __func__);
    return 0;
}

void sipe_backend_buddy_set_alias(struct sipe_core_public * /*sipe_public*/,
        const sipe_backend_buddy /*who*/,
        const gchar * /*alias*/)
{
    SIPE_DEBUG_INFO("STUB %s", __func__);
}

void sipe_backend_buddy_set_server_alias(struct sipe_core_public * /*sipe_public*/,
        const sipe_backend_buddy /*who*/,
        const gchar * /*alias*/)
{
    SIPE_DEBUG_INFO("STUB %s", __func__);
}

void sipe_backend_buddy_list_processing_start(struct sipe_core_public * /*sipe_public*/)
{
    SIPE_DEBUG_INFO("STUB %s", __func__);
}

void sipe_backend_buddy_list_processing_finish(struct sipe_core_public * /*sipe_public*/)
{
    SIPE_DEBUG_INFO("STUB %s", __func__);
}

sipe_backend_buddy sipe_backend_buddy_add(struct sipe_core_public *sipe_public,
        const gchar *name,
        const gchar *alias,
        const gchar *groupname)
{
    SIPE_DEBUG_INFO("%s", __func__);

    QyncBackend *backend = (QyncBackend *)sipe_public->backend_private;

    return (sipe_backend_buddy)backend->addBuddy(name, alias, groupname);
}

void sipe_backend_buddy_remove(struct sipe_core_public * /*sipe_public*/,
        const sipe_backend_buddy /*who*/)
{
    SIPE_DEBUG_INFO("STUB %s", __func__);
}


void sipe_backend_buddy_request_add(struct sipe_core_public * /*sipe_public*/,
        const gchar * /*who*/,
        const gchar * /*alias*/)
{
    SIPE_DEBUG_INFO("STUB %s", __func__);
}

void sipe_backend_buddy_request_authorization(struct sipe_core_public * /*sipe_public*/,
        const gchar * /*who*/,
        const gchar * /*alias*/,
        gboolean /*on_list*/,
        sipe_backend_buddy_request_authorization_cb /*auth_cb*/,
        sipe_backend_buddy_request_authorization_cb /*deny_cb*/,
        gpointer /*data*/)
{
    SIPE_DEBUG_INFO("STUB %s", __func__);
}

gboolean sipe_backend_buddy_is_blocked(struct sipe_core_public * /*sipe_public*/,
        const gchar * /*who*/)
{
    SIPE_DEBUG_INFO("STUB %s", __func__);
    return FALSE;
}

void sipe_backend_buddy_set_blocked_status(struct sipe_core_public * /*sipe_public*/,
        const gchar * /*who*/,
        gboolean /*blocked*/)
{
    SIPE_DEBUG_INFO("STUB %s", __func__);
}

void sipe_backend_buddy_set_status(struct sipe_core_public * /*sipe_public*/,
        const gchar * /*who*/,
        guint /*activity*/)
{
    SIPE_DEBUG_INFO("STUB %s", __func__);
}

gboolean sipe_backend_uses_photo(void)
{
    SIPE_DEBUG_INFO("%s", __func__);
    return TRUE;
}

void sipe_backend_buddy_set_photo(struct sipe_core_public *sipe_public,
        const gchar *who,
        gpointer image_data,
        gsize image_len,
        const gchar *photo_hash)
{
    SIPE_DEBUG_INFO("%s", __func__);

    QyncBackend *backend = (QyncBackend *)sipe_public->backend_private;
    backend->setBuddyPhoto(who, image_data, image_len, photo_hash);
}

const gchar *sipe_backend_buddy_get_photo_hash(struct sipe_core_public *sipe_public,
        const gchar *who)
{
    SIPE_DEBUG_INFO("%s", __func__);
    QyncBackend *backend = (QyncBackend *)sipe_public->backend_private;
    return backend->getBuddyPhotoHash(who);
}

gboolean sipe_backend_buddy_group_add(struct sipe_core_public *sipe_public,
        const gchar *group_name)
{
    SIPE_DEBUG_INFO("%s", __func__);

    QyncBackend *backend = (QyncBackend *)sipe_public->backend_private;

    return backend->addGroup(group_name);
}

gboolean sipe_backend_buddy_group_rename(struct sipe_core_public * /*sipe_public*/,
        const gchar * /*old_name*/,
        const gchar * /*new_name*/)
{
    SIPE_DEBUG_INFO("STUB %s", __func__);
    return FALSE;
}

void sipe_backend_buddy_group_remove(struct sipe_core_public * /*sipe_public*/,
        const gchar * /*group_name*/)
{
    SIPE_DEBUG_INFO("STUB %s", __func__);
}

struct sipe_backend_buddy_info *sipe_backend_buddy_info_start(
        struct sipe_core_public * /*sipe_public*/)
{
    SIPE_DEBUG_INFO("STUB %s", __func__);
    return NULL;
}

void sipe_backend_buddy_info_add(struct sipe_core_public * /*sipe_public*/,
        struct sipe_backend_buddy_info * /*info*/,
        sipe_buddy_info_fields /*key*/,
        const gchar * /*value*/)
{
    SIPE_DEBUG_INFO("STUB %s", __func__);
}

void sipe_backend_buddy_info_break(struct sipe_core_public * /*sipe_public*/,
        struct sipe_backend_buddy_info * /*info*/)
{
    SIPE_DEBUG_INFO("STUB %s", __func__);
}

void sipe_backend_buddy_info_finalize(struct sipe_core_public * /*sipe_public*/,
        struct sipe_backend_buddy_info * /*info*/,
        const gchar * /*uri*/)
{
    SIPE_DEBUG_INFO("STUB %s", __func__);
}

void sipe_backend_buddy_tooltip_add(struct sipe_core_public * /*sipe_public*/,
        struct sipe_backend_buddy_tooltip * /*tooltip*/,
        const gchar * /*description*/,
        const gchar * /*value*/)
{
    SIPE_DEBUG_INFO("STUB %s", __func__);
}

struct sipe_backend_buddy_menu *sipe_backend_buddy_menu_start(struct sipe_core_public * /*sipe_public*/)
{
    SIPE_DEBUG_INFO("STUB %s", __func__);
    return NULL;
}

struct sipe_backend_buddy_menu *sipe_backend_buddy_menu_add(struct sipe_core_public * /*sipe_public*/,
        struct sipe_backend_buddy_menu * /*menu*/,
        const gchar * /*label*/,
        enum sipe_buddy_menu_type /*type*/,
        gpointer /*parameter*/)
{
    SIPE_DEBUG_INFO("STUB %s", __func__);
    return NULL;
}

struct sipe_backend_buddy_menu *sipe_backend_buddy_menu_separator(struct sipe_core_public * /*sipe_public*/,
        struct sipe_backend_buddy_menu * /*menu*/,
        const gchar * /*label*/)
{
    SIPE_DEBUG_INFO("STUB %s", __func__);
    return NULL;
}

struct sipe_backend_buddy_menu *sipe_backend_buddy_sub_menu_add(struct sipe_core_public * /*sipe_public*/,
        struct sipe_backend_buddy_menu * /*menu*/,
        const gchar * /*label*/,
        struct sipe_backend_buddy_menu * /*sub*/)
{
    SIPE_DEBUG_INFO("STUB %s", __func__);
    return NULL;
}

