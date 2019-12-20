//
//  mainwindow.cpp
//  PixivDownloader
//
//  Created by TheWanderingCoel on 2019/12/4.
//  Copyright © 2019 Coel Wu. All rights reserved.
//

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "preferenceswindow.h"
#include "downloadwindow.h"
#include "apppixivapi.h"
#include "basepixivapi.h"
#include "settings.h"

#include <QJsonObject>
#include <QJsonArray>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("PixivDownloader");

    model = new QStandardItemModel();
    // set column number
    model->setColumnCount(5);
    // set up horizontal headers
    model->setHeaderData(0,Qt::Horizontal,"Author Name");
    model->setHeaderData(1,Qt::Horizontal,"Author ID");
    model->setHeaderData(2,Qt::Horizontal,"Artwork Name");
    model->setHeaderData(3,Qt::Horizontal,"Artwork ID");
    model->setHeaderData(4,Qt::Horizontal,"Progress");
    // have to be before other settings
    ui->tableView->setModel(model);
    // disable showing grid
    ui->tableView->setShowGrid(false);
    // disable auto sort
    ui->tableView->setSortingEnabled(false);
    // hide vertical header
    ui->tableView->verticalHeader()->hide();
    // set the whole row instead one section
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    // Set column width to be larger
    ui->tableView->setColumnWidth(0,155);
    ui->tableView->setColumnWidth(1,90);
    ui->tableView->setColumnWidth(2,155);
    ui->tableView->setColumnWidth(3,90);
    ui->tableView->setColumnWidth(4,155);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startDownload()
{

    if (Settings::method == "Bookmarks") {
        downloadBookmarks();
    } else if (Settings::method == "Artwork ID") {
        downloadArtworkId();
    } else if (Settings::method == "Author ID") {
        downloadAuthorId();
    }
}

// 下载收藏
void MainWindow::downloadBookmarks()
{
    AppPixivAPI apa;
    QJsonObject obj = apa.user_bookmarks_illust(BasePixivAPI::user_id);
    QJsonArray array = obj["illusts"].toArray();
    QString nextUrl = obj["next_url"].toString();
    for (const QJsonValue& val: array) {
        QJsonObject loopObj = val.toObject();
        QJsonObject user = loopObj.value("user").toObject();
        int pageCount = loopObj["page_count"].toInt(); // 作品页数
        QString authorName = user["name"].toString().replace("/",""); // 作者名称
        int authorId = user["id"].toInt(); // 作者ID
        QString artworkTitle = loopObj["title"].toString(); // 作品标题
        int artworkId = loopObj["id"].toInt(); // 作品ID
        // 多张图片
        if (pageCount > 1) {
            QJsonArray parray = loopObj["meta_pages"].toArray(); // 图片链接数组
            for (const QJsonValue& temp: parray) {
                QJsonObject ploopObj = temp.toObject(); // 先获取当前的Json
                QJsonObject images = ploopObj.value("image_urls").toObject(); // 再获取图片分辨率的Json
                QString artworkUrl = images["original"].toString(); // 图片链接
                MainWindow::add2Table(authorName, authorId, artworkTitle, artworkId);
                BasePixivAPI::download(artworkUrl, authorName, authorId, artworkTitle, artworkId);
                MainWindow::change2Table();
            }
        // 单张图片
        } else if (pageCount == 1) {
            QJsonObject singleImage = loopObj.value("meta_single_page").toObject(); // 单张图片Json
            QString artworkUrl = singleImage["original_image_url"].toString(); // 图片链接
            MainWindow::add2Table(authorName, authorId, artworkTitle, artworkId);
            BasePixivAPI::download(artworkUrl, authorName, authorId, artworkTitle, artworkId);
            MainWindow::change2Table();
        }
    }
    while (nextUrl != "") {
        QJsonObject obj = apa.follow_next_url(nextUrl);
        QJsonArray array = obj["illusts"].toArray();
        nextUrl = obj["next_url"].toString();
        for (const QJsonValue& val: array) {
            QJsonObject loopObj = val.toObject();
            QJsonObject user = loopObj.value("user").toObject();
            int pageCount = loopObj["page_count"].toInt(); // 作品页数
            QString authorName = user["name"].toString().replace("/",""); // 作者名称
            int authorId = user["id"].toInt(); // 作者ID
            QString artworkTitle = loopObj["title"].toString(); // 作品标题
            int artworkId = loopObj["id"].toInt(); // 作品ID
            // 多张图片
            if (pageCount > 1) {
                QJsonArray parray = loopObj["meta_pages"].toArray(); // 图片链接数组
                for (const QJsonValue& temp: parray) {
                    QJsonObject ploopObj = temp.toObject(); // 先获取当前的Json
                    QJsonObject images = ploopObj.value("image_urls").toObject(); // 再获取图片分辨率的Json
                    QString artworkUrl = images["original"].toString(); // 图片链接
                    MainWindow::add2Table(authorName, authorId, artworkTitle, artworkId);
                    BasePixivAPI::download(artworkUrl, authorName, authorId, artworkTitle, artworkId);
                    MainWindow::change2Table();
                }
            // 单张图片
            } else if (pageCount == 1) {
                QJsonObject singleImage = loopObj.value("meta_single_page").toObject(); // 单张图片Json
                QString artworkUrl = singleImage["original_image_url"].toString(); // 图片链接
                MainWindow::add2Table(authorName, authorId, artworkTitle, artworkId);
                BasePixivAPI::download(artworkUrl, authorName, authorId, artworkTitle, artworkId);
                MainWindow::change2Table();
            }
        }
    }
}

// 下载单部作品
void MainWindow::downloadArtworkId()
{
    AppPixivAPI apa;
    QJsonObject obj = apa.illust_detail(Settings::id);
    QJsonObject illust = obj.value("illust").toObject();
    QJsonObject user = illust.value("user").toObject();
    int pageCount = illust["page_count"].toInt(); // 作品页数
    QString authorName = user["name"].toString().replace("/",""); // 作者名称
    int authorId = user["id"].toInt(); // 作者ID
    QString artworkTitle = illust["title"].toString(); // 作品标题
    int artworkId = illust["id"].toInt(); // 作品ID
    if (pageCount > 1) {
        QJsonArray array = illust["meta_pages"].toArray(); // 图片链接数组
        for (const QJsonValue & val: array) {
            QJsonObject loopObj = val.toObject(); // 先获取当前的Json
            QJsonObject images = loopObj.value("image_urls").toObject(); // 再获取图片分辨率的Json
            QString artworkUrl = images["original"].toString(); // 图片链接
            MainWindow::add2Table(authorName, authorId, artworkTitle, artworkId);
            BasePixivAPI::download(artworkUrl, authorName, authorId, artworkTitle, artworkId);
            MainWindow::change2Table();
        }
    } else if (pageCount == 1) {
        QJsonObject singleImage = illust.value("meta_single_page").toObject(); // 单张图片Json
        QString artworkUrl = singleImage["original_image_url"].toString(); // 图片链接
        MainWindow::add2Table(authorName, authorId, artworkTitle, artworkId);
        BasePixivAPI::download(artworkUrl, authorName, authorId, artworkTitle, artworkId);
        MainWindow::change2Table();
    }
}

// 下载作者的所有作品
void MainWindow::downloadAuthorId()
{
    AppPixivAPI apa;
    QJsonObject obj = apa.user_illusts(Settings::id);
    QJsonArray array = obj["illusts"].toArray();
    QString nextUrl = obj["next_url"].toString();
    for (const QJsonValue& val: array) {
        QJsonObject loopObj = val.toObject();
        QJsonObject user = loopObj.value("user").toObject();
        int pageCount = loopObj["page_count"].toInt(); // 作品页数
        QString authorName = user["name"].toString().replace("/",""); // 作者名称
        int authorId = user["id"].toInt(); // 作者ID
        QString artworkTitle = loopObj["title"].toString(); // 作品标题
        int artworkId = loopObj["id"].toInt(); // 作品ID
        // 多张图片
        if (pageCount > 1) {
            QJsonArray parray = loopObj["meta_pages"].toArray(); // 图片链接数组
            for (const QJsonValue& temp: parray) {
                QJsonObject ploopObj = temp.toObject(); // 先获取当前的Json
                QJsonObject images = ploopObj.value("image_urls").toObject(); // 再获取图片分辨率的Json
                QString artworkUrl = images["original"].toString(); // 图片链接
                MainWindow::add2Table(authorName, authorId, artworkTitle, artworkId);
                BasePixivAPI::download(artworkUrl, authorName, authorId, artworkTitle, artworkId);
                MainWindow::change2Table();
            }
        // 单张图片
        } else if (pageCount == 1) {
            QJsonObject singleImage = loopObj.value("meta_single_page").toObject(); // 单张图片Json
            QString artworkUrl = singleImage["original_image_url"].toString(); // 图片链接
            MainWindow::add2Table(authorName, authorId, artworkTitle, artworkId);
            BasePixivAPI::download(artworkUrl, authorName, authorId, artworkTitle, artworkId);
            MainWindow::change2Table();
        }
    }
    while (nextUrl != "") {
        QJsonObject obj = apa.follow_next_url(nextUrl);
        QJsonArray array = obj["illusts"].toArray();
        nextUrl = obj["next_url"].toString();
        for (const QJsonValue& val: array) {
            QJsonObject loopObj = val.toObject();
            QJsonObject user = loopObj.value("user").toObject();
            int pageCount = loopObj["page_count"].toInt(); // 作品页数
            QString authorName = user["name"].toString().replace("/",""); // 作者名称
            int authorId = user["id"].toInt(); // 作者ID
            QString artworkTitle = loopObj["title"].toString(); // 作品标题
            int artworkId = loopObj["id"].toInt(); // 作品ID
            // 多张图片
            if (pageCount > 1) {
                QJsonArray parray = loopObj["meta_pages"].toArray(); // 图片链接数组
                for (const QJsonValue& temp: parray) {
                    QJsonObject ploopObj = temp.toObject(); // 先获取当前的Json
                    QJsonObject images = ploopObj.value("image_urls").toObject(); // 再获取图片分辨率的Json
                    QString artworkUrl = images["original"].toString(); // 图片链接
                    MainWindow::add2Table(authorName, authorId, artworkTitle, artworkId);
                    BasePixivAPI::download(artworkUrl, authorName, authorId, artworkTitle, artworkId);
                    MainWindow::change2Table();
                }
            // 单张图片
            } else if (pageCount == 1) {
                QJsonObject singleImage = loopObj.value("meta_single_page").toObject(); // 单张图片Json
                QString artworkUrl = singleImage["original_image_url"].toString(); // 图片链接
                MainWindow::add2Table(authorName, authorId, artworkTitle, artworkId);
                BasePixivAPI::download(artworkUrl, authorName, authorId, artworkTitle, artworkId);
                MainWindow::change2Table();
            }
        }
    }

}

void MainWindow::add2Table(QString authorName, int authorId, QString artworkTitle, int artworkId)
{
    int rowCount = model->rowCount();
    model->setItem(rowCount, 0, new QStandardItem(authorName));
    model->setItem(rowCount, 1, new QStandardItem(QString::number(authorId)));
    model->setItem(rowCount, 2, new QStandardItem(artworkTitle));
    model->setItem(rowCount, 3, new QStandardItem(QString::number(artworkId)));
    model->setItem(rowCount, 4, new QStandardItem("Downloading..."));
}

void MainWindow::change2Table()
{
    int rowCount = model->rowCount() - 1;
    model->setItem(rowCount, 4, new QStandardItem("Finished"));
}

void MainWindow::on_preferencesBtn_clicked()
{
    PreferencesWindow *w = new PreferencesWindow(this);
    w->show();
}

void MainWindow::on_addTaskBtn_clicked()
{
    DownloadWindow *w = new DownloadWindow(this);
    if (w->exec() == QDialog::Accepted) {
        startDownload();
    }
}
