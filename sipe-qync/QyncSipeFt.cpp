#include <glib.h>

#include "sipe-backend.h"

void sipe_backend_ft_error(struct sipe_file_transfer *ft,
			   const gchar *errmsg)
{
	SIPE_DEBUG_INFO_NOFORMAT("STUB sipe_backend_ft_error");
}

const gchar *sipe_backend_ft_get_error(struct sipe_file_transfer *ft)
{
	SIPE_DEBUG_INFO_NOFORMAT("STUB sipe_backend_ft_get_error");
    return "";
}

void sipe_backend_ft_deallocate(struct sipe_file_transfer *ft)
{
	SIPE_DEBUG_INFO_NOFORMAT("STUB sipe_backend_ft_deallocate");
}

gssize sipe_backend_ft_read(struct sipe_file_transfer *ft,
			    guchar *data,
			    gsize size)
{
	SIPE_DEBUG_INFO_NOFORMAT("STUB sipe_backend_ft_read");
    return 0;
}

gssize sipe_backend_ft_write(struct sipe_file_transfer *ft,
			     const guchar *data,
			     gsize size)
{
	SIPE_DEBUG_INFO_NOFORMAT("STUB sipe_backend_ft_write");
}


void sipe_backend_ft_cancel_local(struct sipe_file_transfer *ft)
{
	SIPE_DEBUG_INFO_NOFORMAT("STUB sipe_backend_ft_cancel_local");
}

void sipe_backend_ft_cancel_remote(struct sipe_file_transfer *ft)
{
	SIPE_DEBUG_INFO_NOFORMAT("STUB sipe_backend_ft_cancel_remote");
}

void sipe_backend_ft_incoming(struct sipe_core_public *sipe_public,
			      struct sipe_file_transfer *ft,
			      const gchar *who,
			      const gchar *file_name,
			      gsize file_size)
{
	SIPE_DEBUG_INFO_NOFORMAT("STUB sipe_backend_ft_incoming");
}

void sipe_backend_ft_start(struct sipe_file_transfer *ft,
			   struct sipe_backend_fd *fd,
			   const char* ip, unsigned port)
{
	SIPE_DEBUG_INFO_NOFORMAT("STUB sipe_backend_ft_start");
}

gboolean sipe_backend_ft_is_incoming(struct sipe_file_transfer *ft)
{
	SIPE_DEBUG_INFO_NOFORMAT("STUB sipe_backend_ft_is_incoming");
    return FALSE;
}

