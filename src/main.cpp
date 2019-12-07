//
//  main.cpp
//  PixivDownloader
//
//  Created by TheWanderingCoel on 2019/12/4.
//  Copyright © 2019 Coel Wu. All rights reserved.
//

#include "mainwindow.h"
#include "paths.h"
#include "logger.h"

#include <QApplication>
#include <QLoggingCategory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Init Download Folder
    Paths::init();
    // Init Logger
    Logger::init();
    // qt.network.ssl: Failed to create SecCertificate from QSslCertificate
    QLoggingCategory::setFilterRules("qt.network.ssl.warning=false");

    MainWindow w;
    w.show();
    return a.exec();
}
