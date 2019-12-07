#include "paths.h"

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
