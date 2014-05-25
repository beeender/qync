#include <glib.h>
#include <QApplication>
#include <QtQml/QQmlApplicationEngine>
#include <QtQml/QQmlContext>
#include <QtQml>
#include <QtQuick/QQuickView>

#include "QyncSipe.h"

int main(int argc, char **argv)
{
    qmlRegisterType<QyncSipe>("QyncSipe", 1, 0, "QyncSipe");

    QApplication app (argc, argv);

    QyncSipe *qyncSipe = new QyncSipe();

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("qyncSipe", qyncSipe);
    engine.load(QUrl::fromLocalFile("ui/QyncApp.qml"));

    return app.exec();
}

#include "qync.moc"
