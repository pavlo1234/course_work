
#include "QueryBuilder.h"

QueryBuilder* QueryBuilder::instance = nullptr;

QObject* QueryBuilder::createInstance(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);
    if(instance==nullptr) instance = new QueryBuilder();
    return instance;
}
