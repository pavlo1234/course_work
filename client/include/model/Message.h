#pragma once

#include <QtCore>


class Message
{
private:
    int _id, _cid;
    QString _login, _text;
    QDateTime _dt;

public:
    Message() {}
    Message(const Message&) = default;
    Message(int id, const QString& login, int cid, const QString& text, const QDateTime& dt);
    Message(const QString& login, int cid, const QString& text, const QDateTime& dt);

    int getID() {
        return _id;
    }
    void setID(const int& id) {
        _id = id;
    }

    QString& getLogin(){
        return _text;
    }
    void setLogin(const QString& login)
    {
        _login = login;
    }

    int getCID() {
        return _cid;
    }
    void setCID(const int& cid) {
        _cid = cid;
    }

    QString& getText(){
        return _text;
    }
    void setText(const QString& text)
    {
        _text = text;
    }

    QDateTime& getDateTime()
    {
        return _dt;
    }
    void setDateTime(const QDateTime& dt)
    {
        _dt = dt;
    }

    QString toJSON();
    static Message fromJSON(const QJsonObject& obj);

};

