#include <glib.h>
#include <QApplication>
#include <QtQml/QQmlApplicationEngine>
#include <QtQml/QQmlContext>
#include <QtQuick/QQuickView>

#include "QyncSipe.h"

#include <QThread>

int main(int argc, char **argv)
{

    QApplication app (argc, argv);

    QyncSipe *qyncSipe = new QyncSipe();
    QThread *sipeThread = new QThread();
    sipeThread->start();
    qyncSipe->moveToThread(sipeThread);

    QQmlApplicationEngine engine;
    engine.load(QUrl::fromLocalFile("ui/QyncApp.qml"));
    engine.rootContext()->setContextProperty("qyncSipe", qyncSipe);

    qDebug("THREAD TEST 0x%08x main", QThread::currentThreadId());
    return app.exec();
}

#include "qync.moc"
