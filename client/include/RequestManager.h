#pragma once

#include <QtCore>
#include <QtQuick>

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

#define TIMEOUT 100000


class RequestManager : public QObject 
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(QVariantMap reply READ getData)
    Q_PROPERTY(QString method MEMBER _method)
    Q_PROPERTY(int expectedStatus MEMBER _status)
private:
    QNetworkAccessManager* _manager;
    QNetworkReply* _reply;
    QVariantMap _data;
    bool _finished;
    int _status = 200;
    QString _method;

public:

    explicit RequestManager(QObject *parent = nullptr);
    Q_INVOKABLE void exec(const QUrl& url, const QJsonDocument& data = QJsonDocument());
    Q_INVOKABLE void setCredentials(const QString& user, const QString& password);

    QVariantMap& getData()
    {
        return _data;
    }

    void setExpectedStatus(int status) 
    {
        _status = status;
    }   
    void setMethod(QString method)
    {
        _method = method;
    }


    static QString user;
    static QString password;

public slots:
    void replyFinished(QNetworkReply* reply);

signals:
    void finished();
    void failed(int code, QString msg = "");
};