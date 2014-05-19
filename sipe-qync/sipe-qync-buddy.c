#include <glib.h>

#include "sipe-backend.h"

sipe_backend_buddy sipe_backend_buddy_find(struct sipe_core_public *sipe_public,
					   const gchar *buddy_name,
					   const gchar *group_name)
{
    return NULL;
}

GSList* sipe_backend_buddy_find_all(struct sipe_core_public *sipe_public,
				    const gchar *buddy_name,
				    const gchar *group_name)
{
    return NULL;
}

gchar* sipe_backend_buddy_get_name(struct sipe_core_public *sipe_public,
				   const sipe_backend_buddy who)
{
    return "";
}

gchar* sipe_backend_buddy_get_alias(struct sipe_core_public *sipe_public,
				    const sipe_backend_buddy who)
{
    return "";
}

gchar* sipe_backend_buddy_get_server_alias(struct sipe_core_public *sipe_public,
					   const sipe_backend_buddy who)
{
    return "";
}

gchar *sipe_backend_buddy_get_local_alias(struct sipe_core_public *sipe_public,
					  const sipe_backend_buddy who)
{
    return "";
}

gchar* sipe_backend_buddy_get_group_name(struct sipe_core_public *sipe_public,
					 const sipe_backend_buddy who)
{
    return "";
}

gchar* sipe_backend_buddy_get_string(struct sipe_core_public *sipe_public,
				     sipe_backend_buddy buddy,
				     const sipe_buddy_info_fields key)
{
    return "";
}

void sipe_backend_buddy_set_string(struct sipe_core_public *sipe_public,
				   sipe_backend_buddy buddy,
				   const sipe_buddy_info_fields key,
				   const gchar *val)
{
}

void sipe_backend_buddy_refresh_properties(struct sipe_core_public *sipe_public,
					   const gchar *uri)
{
}

guint sipe_backend_buddy_get_status(struct sipe_core_public *sipe_public,
				    const gchar *uri)
{
    return 0;
}

void sipe_backend_buddy_set_alias(struct sipe_core_public *sipe_public,
				  const sipe_backend_buddy who,
				  const gchar *alias)
{
    return;
}

void sipe_backend_buddy_set_server_alias(struct sipe_core_public *sipe_public,
					 const sipe_backend_buddy who,
					 const gchar *alias)
{
}

void sipe_backend_buddy_list_processing_start(struct sipe_core_public *sipe_public)
{
}

void sipe_backend_buddy_list_processing_finish(struct sipe_core_public *sipe_public)
{
}

sipe_backend_buddy sipe_backend_buddy_add(struct sipe_core_public *sipe_public,
					  const gchar *name,
					  const gchar *alias,
					  const gchar *groupname)
{
    return NULL;
}

void sipe_backend_buddy_remove(struct sipe_core_public *sipe_public,
			       const sipe_backend_buddy who)
{
}


void sipe_backend_buddy_request_add(struct sipe_core_public *sipe_public,
				    const gchar *who,
				    const gchar *alias)
{
}

void sipe_backend_buddy_request_authorization(struct sipe_core_public *sipe_public,
					      const gchar *who,
					      const gchar *alias,
					      gboolean on_list,
					      sipe_backend_buddy_request_authorization_cb auth_cb,
					      sipe_backend_buddy_request_authorization_cb deny_cb,
					      gpointer data)
{
}

gboolean sipe_backend_buddy_is_blocked(struct sipe_core_public *sipe_public,
				       const gchar *who)
{
    return FALSE;
}

void sipe_backend_buddy_set_blocked_status(struct sipe_core_public *sipe_public,
					   const gchar *who,
					   gboolean blocked)
{
}

void sipe_backend_buddy_set_status(struct sipe_core_public *sipe_public,
				   const gchar *who,
				   guint activity)
{
}

gboolean sipe_backend_uses_photo(void)
{
    return FALSE;
}

void sipe_backend_buddy_set_photo(struct sipe_core_public *sipe_public,
				  const gchar *who,
				  gpointer image_data,
				  gsize image_len,
				  const gchar *photo_hash)
{
}

const gchar *sipe_backend_buddy_get_photo_hash(struct sipe_core_public *sipe_public,
					       const gchar *who)
{
    return "";
}

gboolean sipe_backend_buddy_group_add(struct sipe_core_public *sipe_public,
				      const gchar *group_name)
{
    return FALSE;
}

gboolean sipe_backend_buddy_group_rename(struct sipe_core_public *sipe_public,
					 const gchar *old_name,
					 const gchar *new_name)
{
    return FALSE;
}

void sipe_backend_buddy_group_remove(struct sipe_core_public *sipe_public,
				     const gchar *group_name)
{
}

struct sipe_backend_buddy_info *sipe_backend_buddy_info_start(
        struct sipe_core_public *sipe_public)
{
    return NULL;
}

void sipe_backend_buddy_info_add(struct sipe_core_public *sipe_public,
				 struct sipe_backend_buddy_info *info,
				 sipe_buddy_info_fields key,
				 const gchar *value)
{
}

void sipe_backend_buddy_info_break(struct sipe_core_public *sipe_public,
				   struct sipe_backend_buddy_info *info)
{
}

void sipe_backend_buddy_info_finalize(struct sipe_core_public *sipe_public,
				      struct sipe_backend_buddy_info *info,
				      const gchar *uri)
{
}

void sipe_backend_buddy_tooltip_add(struct sipe_core_public *sipe_public,
				    struct sipe_backend_buddy_tooltip *tooltip,
				    const gchar *description,
				    const gchar *value)
{
}

struct sipe_backend_buddy_menu *sipe_backend_buddy_menu_start(struct sipe_core_public *sipe_public)
{
    return NULL;
}

struct sipe_backend_buddy_menu *sipe_backend_buddy_menu_add(struct sipe_core_public *sipe_public,
							    struct sipe_backend_buddy_menu *menu,
							    const gchar *label,
							    enum sipe_buddy_menu_type type,
							    gpointer parameter)
{
    return NULL;
}

struct sipe_backend_buddy_menu *sipe_backend_buddy_menu_separator(struct sipe_core_public *sipe_public,
								  struct sipe_backend_buddy_menu *menu,
								  const gchar *label)
{
    return NULL;
}

struct sipe_backend_buddy_menu *sipe_backend_buddy_sub_menu_add(struct sipe_core_public *sipe_public,
								struct sipe_backend_buddy_menu *menu,
								const gchar *label,
								struct sipe_backend_buddy_menu *sub)
{
    return NULL;
}

