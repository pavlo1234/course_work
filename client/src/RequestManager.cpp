#include "RequestManager.h"

QString RequestManager::user = "";
QString RequestManager::password = "";

RequestManager::RequestManager(QObject* parent): QObject(parent) 
{
    _manager = new QNetworkAccessManager(this);
    _reply = nullptr;
    _finished = false;
    _manager->setTransferTimeout(TIMEOUT);

    connect(_manager, &QNetworkAccessManager::finished,
        this, &RequestManager::replyFinished);
}

void RequestManager::exec(const QUrl& url, const QJsonDocument& data)
{
    _data.clear();
    _finished = false;
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "text/json");
    if(RequestManager::user != "" && RequestManager::password != ""){
        QString auth = user+":"+password;
        QByteArray data = auth.toLocal8Bit().toBase64();
        QString header = "Basic " + data;
        request.setRawHeader(QByteArray("Authorization"), header.toLocal8Bit());
    }
    if(_method == "GET")
        _reply = _manager->get(request);
    else if(_method == "POST") 
        _reply = _manager->post(request, data.toJson(QJsonDocument::Compact));
    else if(_method == "PUT")
        _reply = _manager->put(request, data.toJson(QJsonDocument::Compact));
    else if(_method == "DELETE")
        _reply = _manager->deleteResource(request);
    
}

void RequestManager::replyFinished(QNetworkReply* reply) 
{
    if(reply->error() == QNetworkReply::ConnectionRefusedError) {
        emit failed(1, "Cannot connect to the server");
        return;
    }
    if(reply->error() == QNetworkReply::TimeoutError) {
        emit failed(4, "Server is not responding");
        return;
    }
    if(reply->error() == QNetworkReply::OperationCanceledError) {
        emit failed(5, "Server error");
        return;
    }

    int responseStatus = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    QByteArray arr = reply->readAll();
    _data = QJsonDocument::fromJson(arr).toVariant().toMap();
    if(responseStatus == _status) {    
        _finished = true;
        emit finished();    
    }
    else emit failed(responseStatus, _data["error"].toString());
    
}

void RequestManager::setCredentials(const QString& user, const QString& password) 
{
    RequestManager::user = user;
    RequestManager::password = password;
}