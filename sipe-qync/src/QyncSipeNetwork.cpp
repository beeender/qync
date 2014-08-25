#include <glib.h>
#include <QHostAddress>
#include <QNetworkInterface>
#include <algorithm>

#include "sipe-backend.h"

const gchar *sipe_backend_network_ip_address(struct sipe_core_public * /*sipe_public*/)
{
    static gchar addr[16] = {0};
    if (addr[0]) return addr;

    auto l = QNetworkInterface::allAddresses();
    auto it = std::find_if(l.begin(), l.end(),
            [](const QHostAddress &a) {
                return (a.protocol() == QAbstractSocket::IPv4Protocol &&
                    a!= QHostAddress(QHostAddress::LocalHost));
            });
    if (it == l.end()) return "";

    g_strlcpy(addr, (*it).toString().toStdString().c_str(), 16);
    SIPE_DEBUG_INFO("sipe_backend_network_ip_address %s", addr);
    return addr;
}

struct sipe_backend_listendata *
sipe_backend_network_listen_range(unsigned short /*port_min*/,
				  unsigned short /*port_max*/,
				  sipe_listen_start_cb /*listen_cb*/,
				  sipe_client_connected_cb /*connect_cb*/,
				  gpointer /*data*/)
{
    SIPE_DEBUG_INFO_NOFORMAT("sipe_backend_network_listen_range");
    return NULL;
}

void sipe_backend_network_listen_cancel(struct sipe_backend_listendata * /*ldata*/)
{
    SIPE_DEBUG_INFO_NOFORMAT("sipe_backend_network_listen_cancel");
}

gboolean sipe_backend_fd_is_valid(struct sipe_backend_fd * /*fd*/)
{
    SIPE_DEBUG_INFO_NOFORMAT("sipe_backend_fd_is_valid");
    return FALSE;
}

void sipe_backend_fd_free(struct sipe_backend_fd * /*fd*/)
{
    SIPE_DEBUG_INFO_NOFORMAT("sipe_backend_fd_free");
}
