#include <QApplication>
#include <QQuickWindow>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "validate.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    Validate validate;

    QObject *topLevel = engine.rootObjects().value(0);
    QQuickWindow *window = qobject_cast<QQuickWindow *>(topLevel);

    // Connections
    QObject::connect(window, SIGNAL(validationRequested(QUrl)),
                     &validate, SLOT(checkLicenseFile(QUrl)));

    return app.exec();
}
