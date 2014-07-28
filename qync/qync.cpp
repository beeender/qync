#include <QApplication>
#include <QtQml/QQmlApplicationEngine>
#include <QtQml/QQmlContext>
#include <QtQml>
#include <QtQuick/QQuickView>

#include "QyncSipe.h"

#include "QyncBuddyListModel.h"

int main(int argc, char **argv)
{
    qmlRegisterType<QyncSipe>("QyncSipe", 1, 0, "QyncSipe");

    QApplication app (argc, argv);

    QyncSipe *qyncSipe = new QyncSipe();

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("qyncSipe", qyncSipe);
    engine.rootContext()->setContextProperty("buddyListModel", qyncSipe->getBuddyListModel());
#if 0
    QyncBuddyListModel listModel;
    QyncBuddyObject o1("test1");
    QyncBuddyObject o2("test2");
    listModel.addBuddy(o1);
    listModel.addBuddy(o2);
    engine.rootContext()->setContextProperty("buddyListModel", &listModel);
#endif
    engine.load(QUrl::fromLocalFile("ui/QyncApp.qml"));

    return app.exec();
}
