#include <glib.h>

#include "sipe-backend.h"

void sipe_backend_search_failed(struct sipe_core_public * /*sipe_public*/,
        struct sipe_backend_search_token * /*token*/,
        const gchar * /*msg*/)
{
    SIPE_DEBUG_INFO_NOFORMAT("STUB sipe_backend_search_failed");
}

struct sipe_backend_search_results *sipe_backend_search_results_start(struct sipe_core_public * /*sipe_public*/,
        struct sipe_backend_search_token * /*token*/)
{
    SIPE_DEBUG_INFO_NOFORMAT("STUB sipe_backend_search_results_start");
    return nullptr;
}

void sipe_backend_search_results_add(struct sipe_core_public * /*sipe_public*/,
        struct sipe_backend_search_results * /*results*/,
        const gchar * /*uri*/,
        const gchar * /*name*/,
        const gchar * /*company*/,
        const gchar * /*country*/,
        const gchar * /*email*/)
{
    SIPE_DEBUG_INFO_NOFORMAT("STUB sipe_backend_search_results_add");
}

void sipe_backend_search_results_finalize(struct sipe_core_public * /*sipe_public*/,
        struct sipe_backend_search_results * /*results*/,
        const gchar * /*description*/,
        gboolean /*more*/)
{
    SIPE_DEBUG_INFO_NOFORMAT("STUB sipe_backend_search_results_finalize");
}
