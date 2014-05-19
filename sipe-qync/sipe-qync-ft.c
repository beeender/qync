#include <glib.h>

#include "sipe-backend.h"

void sipe_backend_ft_error(struct sipe_file_transfer *ft,
			   const gchar *errmsg)
{
}

const gchar *sipe_backend_ft_get_error(struct sipe_file_transfer *ft)
{
    return "";
}

void sipe_backend_ft_deallocate(struct sipe_file_transfer *ft)
{
}

gssize sipe_backend_ft_read(struct sipe_file_transfer *ft,
			    guchar *data,
			    gsize size)
{
    return 0;
}

gssize sipe_backend_ft_write(struct sipe_file_transfer *ft,
			     const guchar *data,
			     gsize size)
{
}


void sipe_backend_ft_cancel_local(struct sipe_file_transfer *ft)
{
}

void sipe_backend_ft_cancel_remote(struct sipe_file_transfer *ft)
{
}

void sipe_backend_ft_incoming(struct sipe_core_public *sipe_public,
			      struct sipe_file_transfer *ft,
			      const gchar *who,
			      const gchar *file_name,
			      gsize file_size)
{
}

void sipe_backend_ft_start(struct sipe_file_transfer *ft,
			   struct sipe_backend_fd *fd,
			   const char* ip, unsigned port)
{
}

gboolean sipe_backend_ft_is_incoming(struct sipe_file_transfer *ft)
{
    return FALSE;
}

