#include <glib.h>

#include "sipe-core.h"

#include "QyncSipe.h"
#include "QyncLoginManager.h"

QyncLoginManager::QyncLoginManager(QyncSipe *qyncSipe, QObject *parent)
    :mQyncSipe(qyncSipe), QObject(parent)
{
    connect(this, SIGNAL(login()), this, SLOT(doLogin()));
}

QyncLoginManager::~QyncLoginManager()
{
}

void QyncLoginManager::doLogin()
{
    mQyncSipe->setStatus(QyncSipe::InProcess);
    int tmpstatus;
    int ttype = SIPE_TRANSPORT_AUTO;
    guint authentication_type = SIPE_AUTHENTICATION_TYPE_NTLM;

    sipe_core_transport_sip_connect(
            mQyncSipe->getSipePublic(),
            ttype,
            authentication_type,
            NULL,
            NULL);
}
