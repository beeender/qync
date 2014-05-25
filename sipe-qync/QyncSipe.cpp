#include <glib.h>
#include "QyncSipe.h"

#include "sipe-core.h"

#include <QThread>
#include <QStringList>

QyncSipe::QyncSipe(QObject* parent)
    :QObject(parent), mAccountName(""), mDomainUser(""), mPassword(""),
    mEmail(""), mEmailUrl(""), mSso(FALSE),
    mSipePublic(0), mSipeThread(), mLoginManager(this), mStatus(Idle)
{
    sipe_core_init("");
    mLoginManager.moveToThread(&mSipeThread);
    mSipeThread.start();
}

QyncSipe::~QyncSipe()
{

}

bool QyncSipe::start()
{
    const gchar *errmsg;

    gchar *username = (gchar *)mAccountName.toStdString().c_str();
    QStringList domainUser = mDomainUser.split("\\", QString::KeepEmptyParts);

    int tmpstatus;
    int ttype = SIPE_TRANSPORT_AUTO;
    guint authentication_type = SIPE_AUTHENTICATION_TYPE_NTLM;

    mSipePublic = sipe_core_allocate(
            mAccountName.toStdString().c_str(),
            mSso,
            domainUser.size() == 2 ? domainUser[0].toStdString().c_str() : NULL,
            domainUser.size() == 2 ?
                domainUser[1].toStdString().c_str() : domainUser[0].toStdString().c_str(),
            mPassword.toStdString().c_str(),
            mEmail.toStdString().c_str(),
            mEmailUrl.toStdString().c_str(),
            &errmsg);

    if (!mSipePublic) return false;

    mSipePublic->backend_private = (struct sipe_backend_private *)this;
    emit mLoginManager.login();

    return true;
}

void QyncSipe::setStatus(LoginStatusE s)
{
    mStatus = s;
    emit statusChanged();
}

