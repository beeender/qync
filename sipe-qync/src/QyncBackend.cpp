#include <glib.h>

#include <QStringList>

#include "sipe-core.h"

#include "QyncSipeUtils.h"
#include "QyncBackend.h"

QyncBackend::QyncBackend(QyncSipe *qyncSipe, QObject *parent)
    :mQyncSipe(qyncSipe), QObject(parent), mDesiredStatus(SIPE_ACTIVITY_UNSET)
    ,mSipePublic(0)
{
    connect(this, SIGNAL(__login(const QyncSipe::LoginInfo &)), this, SLOT(doLogin(const QyncSipe::LoginInfo &)));
    sipe_core_init("");
}

QyncBackend::~QyncBackend()
{
}

void QyncBackend::doLogin(const QyncSipe::LoginInfo &loginInfo)
{
    const gchar *errmsg;

    gchar *username = (gchar *)loginInfo.accountName.toStdString().c_str();
    QStringList domainUser = loginInfo.domainUser.split("\\", QString::KeepEmptyParts);

    int ttype = SIPE_TRANSPORT_AUTO;
    guint authentication_type = SIPE_AUTHENTICATION_TYPE_NTLM;

    mSipePublic = sipe_core_allocate( loginInfo.accountName.toStdString().c_str(),
            loginInfo.sso,
            domainUser.size() == 2 ? domainUser[0].toStdString().c_str() : NULL,
            domainUser.size() == 2 ?
                domainUser[1].toStdString().c_str() : domainUser[0].toStdString().c_str(),
            loginInfo.password.toStdString().c_str(),
            loginInfo.email.toStdString().c_str(),
            loginInfo.emailUrl.toStdString().c_str(),
            &errmsg);

    //if (!mSipePublic) return false;

    mSipePublic->backend_private = (struct sipe_backend_private *)this;
    mQyncSipe->setStatus(QyncSipe::StatusInProcess);

    sipe_core_transport_sip_connect(
            mSipePublic,
            ttype,
            authentication_type,
            NULL,
            NULL);
}

void QyncBackend::setStatus(guint status)
{
    mQyncSipe->setStatus(QyncSipeUtils::SipeStatusToQync(status));
}

bool QyncBackend::addGroup(const gchar *groupName)
{
    return mQyncSipe->addGroup(QString(groupName));
}

QyncBuddyObject *QyncBackend::findBuddy(const gchar* buddyName, const gchar* groupName)
{
    return mQyncSipe->findBuddy(QString(buddyName), QString(groupName));
}

QyncBuddyObject *QyncBackend::addBuddy(const gchar *buddyName, const gchar *alias, const gchar *groupName)
{
    return mQyncSipe->addBuddy(buddyName, alias, groupName);
}
