#include "paths.h"
#include "settings.h"

#include <QStandardPaths>

#include <QDebug>
#include <QDir>

QString Paths::downloadLocation = QStandardPaths::writableLocation(QStandardPaths::DownloadLocation) + "/PixivDownloader";

const QString Paths::logsPath = QStandardPaths::writableLocation(QStandardPaths::DataLocation) + "/PixivDownloader";

const QString Paths::logFilePath = logsPath + "/PixivDownloader.log";

void Paths::init()
{
    QDir dir(Paths::downloadLocation);
    if (!dir.exists()) {
        dir.mkpath(".");
    }
}

QString Paths::getSavePath(QString authorName, int authorId, QString artworkTitle, int artworkId)
{
    switch (Settings::savePathSelection) {
        case 1:
            return Paths::downloadLocation + "/" + authorName + " - " + QString::number(authorId) + "/" + artworkTitle + " - " + QString::number(artworkId) + "/";
        case 2:
            return Paths::downloadLocation + "/" + authorName + " - " + QString::number(authorId) + "/";
        case 3:
            return Paths::downloadLocation + "/" + authorName + " - " + QString::number(authorId) + "/";
        case 4:
            return Paths::downloadLocation + "/";
        case 5:
            return Paths::downloadLocation + "/";
        default:
            return "";
    }
}

QString Paths::getSaveFileName(QString url, QString artworkTitle, int artworkId)
{
    switch (Settings::savePathSelection) {
        case 1:
            return url.split("/")[url.split("/").length()-1];
        case 2:
            return artworkTitle + " - " + QString::number(artworkId) + ".jpg";
        case 3:
            return url.split("/")[url.split("/").length()-1];
        case 4:
            return artworkTitle + " - " + QString::number(artworkId) + ".jpg";
        case 5:
            return url.split("/")[url.split("/").length()-1];
        default:
            return "";
    }
}
