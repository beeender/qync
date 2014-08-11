#define QYNCUTILS_CPP

#include <QFile>
#include <QCryptographicHash>

#include "QyncUtils.h"
#include "QyncDB.h"

QByteArray QyncUtils::calImageChecksum(const QString &imageName)
{
    QString path = QString("%1/%2").arg(QyncDB::getImageDir()).arg(imageName);
    QFile file(path);
    if (!file.exists()) return QByteArray();

    QCryptographicHash cryHash(QCryptographicHash::Sha1);
    cryHash.addData(&file);

    return cryHash.result().toHex();
}
