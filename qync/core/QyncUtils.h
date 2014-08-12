#ifndef QYNCUTILS_H
#define QYNCUTILS_H

#include <QString>
#include <QByteArray>

class QyncUtils
{
public:
    static QByteArray calImageChecksum(const QString &imageName);
    static bool writeImage(const QByteArray &imgData, const QByteArray &imgHash);
};

#endif // QYNCUTILS_H
