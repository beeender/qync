#ifndef QYNCSIPEUTILS_H
#define QYNCSIPEUTILS_H

#include "QyncSipe.h"

class QyncSipeUtils {
    private:
    QyncSipeUtils() {};
    ~QyncSipeUtils() {};

    public:
    static QyncSipe::LoginStatusE SipeStatusToQync(int status);
    static int QyncStatusToSipe(QyncSipe::LoginStatusE status);
    static QyncSipe::BuddyInfoFieldE SipeBuddyInfoFieldToQync(const int field);
};
#endif

