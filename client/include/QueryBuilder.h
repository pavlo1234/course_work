#pragma once

#include <QtCore>
#include <QtQuick>

class QueryBuilder : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON

private:
    const QString SCHEME = "http";
    const QString HOST = "localhost";
    const int PORT = 9180;

    static QueryBuilder* instance;
    explicit QueryBuilder(QObject *parent = nullptr) : QObject(parent) {}
    
public:
    static QObject* createInstance(QQmlEngine *engine,  QJSEngine *scriptEngine);

    QString prepareURL()
    {
        return SCHEME + "://" + HOST+":"+QString::number(PORT);
    }

    Q_INVOKABLE QUrl resource(QString name, QVariantMap prms = QVariantMap())
    {
        QString addr = prepareURL() + "/" + name + "?";
        for (auto i = prms.cbegin(), end = prms.cend(); i != end; ++i)
            addr += i.key() + "=" + i.value().toString() + (i != --prms.cend() ? "&" : "");
        return QUrl(addr);
    }


};