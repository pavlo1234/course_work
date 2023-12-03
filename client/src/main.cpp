#include <QtGui>
#include <QtQml>


#include "QueryBuilder.h"
#include "DataContainer.h"
#include "RequestManager.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<DataContainer>("data", 1, 0, "DataContainer");

    qmlRegisterType<RequestManager>("services", 1, 0, "RequestManager");
    qmlRegisterSingletonType<QueryBuilder>("services", 1, 0, "QueryBuilder", QueryBuilder::createInstance);

    QQmlApplicationEngine engine("qrc:/main/ui/qml/default.qml");

    return app.exec();

}
