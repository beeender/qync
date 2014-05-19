#include <glib.h>
#include "QyncSipe.h"

#include "sipe-core.h"

#include <QThread>

QyncSipe::QyncSipe(QObject* parent)
    :QObject(parent), mAccountName(""), mDomainUser(""), mPassword(""),
    mEmail(""), mEmailUrl(""), mSso(FALSE),
    mSipePublic(0), mLoginManager(this)
{
    sipe_core_init("");
}

QyncSipe::~QyncSipe()
{

}

bool QyncSipe::start()
{
    qDebug("THREAD TEST 0x%08x QyncSipe::start", QThread::currentThreadId());
    const gchar *errmsg;

    gchar *username = (gchar *)mAccountName.toStdString().c_str();
    QStringList domainUser = mDomainUser.split("\\", QString::SkipEmptyParts);

    int tmpstatus;
    int ttype = SIPE_TRANSPORT_AUTO;
    guint authentication_type = SIPE_AUTHENTICATION_TYPE_NTLM;

    mSipePublic = sipe_core_allocate(
            mAccountName.toStdString().c_str(),
            mSso,
            domainUser.size() ? domainUser[0].toStdString().c_str() : NULL,
            domainUser.size() ? domainUser[1].toStdString().c_str() : NULL,
            mPassword.toStdString().c_str(),
            mEmail.toStdString().c_str(),
            mEmailUrl.toStdString().c_str(),
            &errmsg);

    mSipePublic->backend_private = (struct sipe_backend_private *)this;

    emit mLoginManager.login();
    return true;
}

