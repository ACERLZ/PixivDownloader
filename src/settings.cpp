#include "settings.h"

#include <QLocale>
#include <QStandardPaths>

const QString Settings::version = "0.0.1"; // 版本号

const QDate Settings::buildDate = QLocale(QLocale::English).toDate(QString(__DATE__).replace("  ", " 0"), "MMM dd yyyy");

const QTime Settings::buildTime = QTime::fromString(__TIME__, "hh:mm:ss");

QString Settings::method = "bookmarks"; // 下载方式

int Settings::id = 0; // 下载ID

QString Settings::proxyType;

QString Settings::address = "127.0.0.1";

int Settings::port = 7891;

bool Settings::authentication = false;

QString Settings::username;

QString Settings::password;

QString Settings::proxyUsername;

QString Settings::proxyPassword;
