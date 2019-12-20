#include "settings.h"

#include <QLocale>
#include <QStandardPaths>

const QString Settings::version = "0.0.1"; // 版本号

const QDate Settings::buildDate = QLocale(QLocale::English).toDate(QString(__DATE__).replace("  ", " 0"), "MMM dd yyyy");

const QTime Settings::buildTime = QTime::fromString(__TIME__, "hh:mm:ss");

/*
 * 1 -> PixivDownloader/作者名 - 作者ID/作品名 - 作品ID/一串随机字符.jpg
 * 2 -> PixivDownloader/作者名 - 作者ID/作品名 - 作者ID.jpg
 * 3 -> PixivDownloader/作者名 - 作者ID/一串随机字符.jpg
 * 4 -> PixivDownloader/作品名 - 作品ID.jpg
 * 5 -> PixivDownloader/一串随机字符.jpg
*/
int Settings::savePathSelection = 1;

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
