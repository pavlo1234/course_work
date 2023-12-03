#pragma once

#include <QtCore>
#include <QtQuick>
#include <QJSValue>

class DataContainer: public QObject
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(QVariantMap data READ getData)
private:
    QVariantMap _data;

public:
    explicit DataContainer(QObject *parent = nullptr) : QObject(parent) {}
    Q_INVOKABLE void fromJSON(const QJsonDocument& data)
    {
        _data = data.toVariant().toMap();
    }
    Q_INVOKABLE QJsonDocument toJSON()
    {
        return QJsonDocument::fromVariant(_data);
    }

    QVariantMap& getData(){
        return _data;
    }

    Q_INVOKABLE void add(const QString& key, const QVariant& value)
    {
        _data.insert(key, value);
    }

    Q_INVOKABLE void add(const QString& key, const QJSValue& value)
    {
        _data.insert(key, QJSEngine().fromScriptValue<QJsonValue>(value));
    }

};