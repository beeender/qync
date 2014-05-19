#include <glib.h>

#include "sipe-core.h"

#include <QyncSipe.h>
#include <QyncLoginManager.h>
#include <QThread>

QyncLoginManager::QyncLoginManager(QObject *parent)
    :QObject(parent), mStatus(IDLE)
{
    connect(this, SIGNAL(login()), this, SLOT(doLogin()));
}

QyncLoginManager::~QyncLoginManager()
{
}

void QyncLoginManager::doLogin()
{
    qDebug("THREAD TEST 0x%08x QyncLoginManager::doLogin", QThread::currentThreadId());
    int tmpstatus;
    int ttype = SIPE_TRANSPORT_AUTO;
    guint authentication_type = SIPE_AUTHENTICATION_TYPE_NTLM;

    sipe_core_transport_sip_connect(
            ((QyncSipe *)parent())->getSipePublic(),
            ttype,
            authentication_type,
            NULL,
            NULL);
}
