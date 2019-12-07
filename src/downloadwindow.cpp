//
//  downloadwindow.cpp
//  PixivDownloader
//
//  Created by TheWanderingCoel on 2019/12/5.
//  Copyright © 2019 Coel Wu. All rights reserved.
//

#include "downloadwindow.h"
#include "ui_downloadwindow.h"

#include "mainwindow.h"
#include "settings.h"

#include <QJsonObject>
#include <QJsonArray>

DownloadWindow::DownloadWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DownloadWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Add Task");

    ui->type->addItem("Bookmarks");
    ui->type->addItem("Artwork ID");
    ui->type->addItem("Author ID");

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

DownloadWindow::~DownloadWindow()
{
    delete ui;
}

void DownloadWindow::on_buttonBox_accepted()
{
    Settings::method = ui->type->currentText();
    Settings::id = ui->id->text().toInt();
}
