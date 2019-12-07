#ifndef PATHS_H
#define PATHS_H

#include <QString>

class Paths
{
public:
    static void init();
    static QString downloadLocation;
    const static QString logsPath;
    const static QString logFilePath;
};

#endif // PATHS_H
