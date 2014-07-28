#include <QDnsLookup>
#include <QHostAddress>
#include <glib.h>

#include "sipe-core.h"
#include "sipe-backend.h"

class QyncSipeDnsQuery : QObject
{
    Q_OBJECT

    public:
        QyncSipeDnsQuery(sipe_core_public *sipe_public,
                sipe_dns_resolved_cb callback, gpointer data,
                QObject *parent = 0);

        void queryA(const gchar *hostname, guint port);
        void querySrv(const gchar *protocol, const char *transport, const char *domain);

    private:
        ~QyncSipeDnsQuery();
        void returnResult(QString hostname, quint16 port);
        void returnEmptyResult();

        struct sipe_core_public *mSipePublic;
        sipe_dns_resolved_cb mCallback;
        gpointer mData;
        QDnsLookup *mDns;
        guint mPort;

    private slots:
        void handleQueryA();
        void handleQuerySrv();
};

QyncSipeDnsQuery::QyncSipeDnsQuery(sipe_core_public *sipe_public,
        sipe_dns_resolved_cb callback,  gpointer data,
        QObject *parent)
        :QObject(parent), mPort(0)
{
    mSipePublic = sipe_public;
    mCallback = callback;
    mData = data;

    mDns = new QDnsLookup(this);
}

QyncSipeDnsQuery::~QyncSipeDnsQuery()
{
    mDns->abort();
    delete mDns;
}

void QyncSipeDnsQuery::returnResult(QString hostname, quint16 port)
{
    mCallback(mData, hostname.toStdString().c_str(), port);
    delete this;
}

void QyncSipeDnsQuery::returnEmptyResult()
{
    mCallback(mData, 0, 0);
    delete this;
}

void QyncSipeDnsQuery::querySrv(const gchar *protocol, const char *transport,
        const char *domain)
{
    connect(mDns, SIGNAL(finished()),
            this, SLOT(handleQuerySrv()));

    mDns->setType(QDnsLookup::SRV);
    QString name = QString("_%1._%2.%3").arg(protocol, transport, domain);
    mDns->setName(name);
    mDns->lookup();
}

void QyncSipeDnsQuery::queryA(const gchar *hostname, guint port)
{
    connect(mDns, SIGNAL(finished()),
            this, SLOT(handleQueryA()));

    mPort = port;
    mDns->setType(QDnsLookup::A);
    mDns->setName(hostname);
    mDns->lookup();
}

void QyncSipeDnsQuery::handleQuerySrv()
{
    // Check the lookup succeeded.
    if (mDns->error() != QDnsLookup::NoError) {
        qWarning("DNS lookup failed %d", mDns->error());

        returnEmptyResult();
        return;
    }

    // Handle the results.
    foreach (const QDnsServiceRecord &record, mDns->serviceRecords()) {
        returnResult(record.target(), record.port());
        break;
    }
}

void QyncSipeDnsQuery::handleQueryA()
{
    // Check the lookup succeeded.
    if (mDns->error() != QDnsLookup::NoError) {
        qWarning("DNS lookup failed %d", mDns->error());

        returnEmptyResult();
        return;
    }

    // Handle the results.
    foreach (const QDnsHostAddressRecord &record, mDns->hostAddressRecords()) {
        returnResult(record.value().toString(), mPort);
        break;
    }
}
struct sipe_dns_query *sipe_backend_dns_query_srv(struct sipe_core_public *sipe_public,
						  const gchar *protocol,
						  const gchar *transport,
						  const gchar *domain,
						  sipe_dns_resolved_cb callback,
						  gpointer data)
{
	SIPE_DEBUG_INFO("sipe_backend_dns_query_srv: %s %s %s", protocol, transport, domain);
    QyncSipeDnsQuery *query = new QyncSipeDnsQuery(sipe_public, callback, data,
            (QObject *)(sipe_public->backend_private));
    query->querySrv(protocol, transport, domain);

    return (struct sipe_dns_query *)query;
}

struct sipe_dns_query *sipe_backend_dns_query_a(struct sipe_core_public *sipe_public,
						const gchar *hostname,
						guint port,
						sipe_dns_resolved_cb callback,
						gpointer data)
{
	SIPE_DEBUG_INFO("sipe_backend_dns_query_a: %s %d", hostname, port);
    QyncSipeDnsQuery *query = new QyncSipeDnsQuery(sipe_public, callback, data);
    query->queryA(hostname, port);

    return (struct sipe_dns_query *)query;
}

void sipe_backend_dns_query_cancel(struct sipe_dns_query *query)
{
	SIPE_DEBUG_INFO_NOFORMAT("sipe_backend_dns_query_cancel");
}

#include "QyncSipeDnsQuery.moc"
