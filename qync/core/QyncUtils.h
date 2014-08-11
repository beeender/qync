#ifndef QYNCUTILS_H
#define QYNCUTILS_H

#include <QString>
#include <QByteArray>

class QyncUtils
{
public:
    static QByteArray calImageChecksum(const QString &imageName);
};

#endif // QYNCUTILS_H
