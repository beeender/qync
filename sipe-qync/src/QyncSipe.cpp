#define QYNCSIPE_CPP

#include <QThread>

#include "QyncSipe.h"
#include "QyncBackend.h"

QyncSipe::QyncSipe(bool threadedBackend) : mBackendThread(NULL)
{
    qRegisterMetaType<QyncSipe::LoginInfo>("QyncSipe::LoginInfo");
    mBackend = new QyncBackend(this);
    if (threadedBackend) {
        mBackendThread = new QThread();
        mBackend->moveToThread(mBackendThread);
        mBackendThread->start();
    }
}

QyncSipe::~QyncSipe()
{
    delete mBackend;
    if(mBackendThread) delete mBackendThread;
}

void QyncSipe::login(const LoginInfo &loginInfo)
{
    emit mBackend->__login(loginInfo);
}
