#ifndef PATHS_H
#define PATHS_H

#include <QString>

class Paths
{
public:
    static void init();
    static QString getSavePath(QString authorName, int authorID, QString artworkTitle, int artworkId);
    static QString getSaveFileName(QString url, QString artworkTitle, int artworkId);
    static QString downloadLocation;
    const static QString logsPath;
    const static QString logFilePath;
};

#endif // PATHS_H
