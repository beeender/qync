#include <glib.h>
#include <QHostAddress>
#include <QNetworkInterface>

#include "sipe-backend.h"

const gchar *sipe_backend_network_ip_address(struct sipe_core_public *sipe_public)
{
    QString addr;
    foreach (const QHostAddress &address, QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol &&
                address != QHostAddress(QHostAddress::LocalHost)) {
            addr = address.toString();
            qDebug() << address.toString();
        }
    }
    SIPE_DEBUG_INFO("sipe_backend_network_ip_address %s", addr.toStdString().c_str());
    return addr.toStdString().c_str();
}

struct sipe_backend_listendata *
sipe_backend_network_listen_range(unsigned short port_min,
				  unsigned short port_max,
				  sipe_listen_start_cb listen_cb,
				  sipe_client_connected_cb connect_cb,
				  gpointer data)
{
    SIPE_DEBUG_INFO_NOFORMAT("sipe_backend_network_listen_range");
    return NULL;
}

void sipe_backend_network_listen_cancel(struct sipe_backend_listendata *ldata)
{
    SIPE_DEBUG_INFO_NOFORMAT("sipe_backend_network_listen_cancel");
}

gboolean sipe_backend_fd_is_valid(struct sipe_backend_fd *fd)
{
    SIPE_DEBUG_INFO_NOFORMAT("sipe_backend_fd_is_valid");
    return FALSE;
}

void sipe_backend_fd_free(struct sipe_backend_fd *fd)
{
    SIPE_DEBUG_INFO_NOFORMAT("sipe_backend_fd_free");
}
