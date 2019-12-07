#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QDate>
#include <QTime>

class Settings: public QObject
{
public:
    const static QString version;
    const static QDate buildDate;
    const static QTime buildTime;
    static QString method;
    static int id;
    static QString username;
    static QString password;
    static QString proxyType;
    static QString address;
    static int port;
    static bool authentication;
    static QString proxyUsername;
    static QString proxyPassword;
};

#endif // SETTINGS_H
