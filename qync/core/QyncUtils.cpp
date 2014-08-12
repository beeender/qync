#define QYNCUTILS_CPP

#include <QFile>
#include <QDir>
#include <QCryptographicHash>

#include "QyncUtils.h"
#include "QyncDB.h"

QByteArray QyncUtils::calImageChecksum(const QString &imageName)
{
#if 0
    QString path = QString("%1/%2").arg(QyncDB::getImageDir()).arg(imageName);
    QFile file(path);
    if (!file.exists()) return QByteArray();

    QCryptographicHash cryHash(QCryptographicHash::Sha1);
    cryHash.addData(&file);

    return cryHash.result().toHex();
#endif
    return QByteArray(imageName.toStdString().c_str());
}

bool QyncUtils::writeImage(const QByteArray &imgData, const QByteArray &imgHash)
{
#if 0
    QCryptographicHash cryHash(QCryptographicHash::Sha1);
    cryHash.addData(imgData);
    QByteArray r = cryHash.result().toHex();

    if (r != imgHash) return false;
#endif

    QDir dir(QyncDB::getImageDir());
    if (!dir.exists()) dir.mkpath(".");

    QString path = QString("%1/%2").arg(QyncDB::getImageDir()).arg(QString(imgHash));
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly)) {
        return false;
    }

    file.write(imgData);
    file.flush();
    file.close();
    return true;
}
