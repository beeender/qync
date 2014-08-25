#include <glib.h>

#include <QTcpSocket>
#include <QSslSocket>

#include <cstring>

#include "sipe-backend.h"
#include "sipe-core.h"

class QyncSipeTransport : QObject
{
    Q_OBJECT

public:
    QyncSipeTransport(struct sipe_core_public *sipe_public,
            const sipe_connect_setup *setup, QObject *parent = 0);
    ~QyncSipeTransport();

    struct SipeTransportConnection {
        //public part shared with core
        struct sipe_transport_connection pub;

        //QyncSipeTransport instance to this
        QyncSipeTransport *thiz;
    };

    struct SipeTransportConnection *getSipeTransportConnection()
    { return &mSipeTransportCon; };

    void write(const char *data);
    void flush();

private:
    struct sipe_core_public *mSipeCorePublic;
    sipe_connect_setup mConSetup;
    struct SipeTransportConnection mSipeTransportCon;

    QSslSocket mSocket;
    QVector<char> mReadBuf;
    private slots:
        void onSocketReady();
    void onReadyRead();
    void onDisconnected();
    void onError(QAbstractSocket::SocketError socketError);
    void onStateChanged(QAbstractSocket::SocketState socketState);
};

QyncSipeTransport::QyncSipeTransport(struct sipe_core_public *sipe_public,
        const sipe_connect_setup *setup, QObject *parent)
:QObject(parent), mSipeCorePublic(sipe_public), mConSetup(*setup)
{
    std::memset(&mSipeTransportCon, 0, sizeof(mSipeTransportCon));
    mSipeTransportCon.thiz = this;
    mSipeTransportCon.pub.type = setup->type;
    mSipeTransportCon.pub.user_data = setup->user_data;

    switch(setup->type) {
        case SIPE_TRANSPORT_AUTO:
            break;
        case SIPE_TRANSPORT_TLS:
            connect(&mSocket, SIGNAL(encrypted()), this, SLOT(onSocketReady()));
            connect(&mSocket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
            connect(&mSocket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
            connect(&mSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onError(QAbstractSocket::SocketError)));
            connect(&mSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(onStateChanged(QAbstractSocket::SocketState)));
            mSocket.connectToHostEncrypted(mConSetup.server_name, mConSetup.server_port);
            break;
        case SIPE_TRANSPORT_TCP:
            //mSocket.connectToHost(mConSetup.server_name, mConSetup.server_port);
            break;
        default:
            qFatal("sipe_connect_setup type error! %d\n", setup->type);
            break;
    }
}

QyncSipeTransport::~QyncSipeTransport()
{
}

void QyncSipeTransport::onSocketReady()
{
    mSipeTransportCon.pub.client_port = mSocket.localPort();
    mConSetup.connected((struct sipe_transport_connection*)&mSipeTransportCon);
}

void QyncSipeTransport::onReadyRead()
{

    struct sipe_transport_connection *conn = &mSipeTransportCon.pub;
    quint64 av = mSocket.bytesAvailable();
    quint64 len = conn->buffer_used + av + 1;
    mReadBuf.resize(len);
    conn->buffer = (gchar *)mReadBuf.data();
    mSocket.read(mReadBuf.data() + conn->buffer_used, av);
    mReadBuf.last() = 0;
    conn->buffer_used = len - 1;
    conn->buffer_length = len;

    mConSetup.input((struct sipe_transport_connection *)&mSipeTransportCon);
}

void QyncSipeTransport::onDisconnected()
{
    qWarning("onDisconnected");
}

void QyncSipeTransport::onError(QAbstractSocket::SocketError socketError)
{
    qWarning("onError %d", socketError);
    mConSetup.error((struct sipe_transport_connection *)&mSipeTransportCon, "SocketError");
}

void QyncSipeTransport::onStateChanged(QAbstractSocket::SocketState socketState)
{
    qWarning("onStateChanged: %d", socketState);
}

void QyncSipeTransport::write(const char *data)
{
    //if (mSocket.state() != QAbstractSocket::ConnectedState) return;

    qint64 written = 0;
    qint64 len = strlen(data);
    do {
        if (written < 0) {
            return;
        }
        written += mSocket.write(data + written);
        qWarning("write: %lld, %lld", len, written);
    } while (written < len);
}

void QyncSipeTransport::flush()
{
    mSocket.flush();
}

struct sipe_transport_connection *sipe_backend_transport_connect(
        struct sipe_core_public *sipe_public,
        const sipe_connect_setup *setup)
{
    SIPE_DEBUG_INFO_NOFORMAT("sipe_backend_transport_connect");
    QyncSipeTransport *q_sipe_trans = new QyncSipeTransport(sipe_public, setup);
    return (struct sipe_transport_connection *)q_sipe_trans->getSipeTransportConnection();
}

void sipe_backend_transport_disconnect(struct sipe_transport_connection *conn)
{
    SIPE_DEBUG_INFO_NOFORMAT("sipe_backend_transport_disconnect");
    delete ((QyncSipeTransport::SipeTransportConnection *)conn)->thiz;
}

void sipe_backend_transport_message(struct sipe_transport_connection *conn,
        const gchar *buffer)
{
    SIPE_DEBUG_INFO_NOFORMAT("sipe_backend_transport_message");
    ((QyncSipeTransport::SipeTransportConnection *)conn)->thiz->write(buffer);
}

void sipe_backend_transport_flush(struct sipe_transport_connection *conn)
{
    SIPE_DEBUG_INFO_NOFORMAT("sipe_backend_transport_flush");
    ((QyncSipeTransport::SipeTransportConnection *)conn)->thiz->flush();
}


#include "QyncSipeTransport.moc"

