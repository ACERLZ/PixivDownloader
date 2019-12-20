//
//  apppixivapi.cpp
//  PixivDownloader
//
//  Created by TheWanderingCoel on 2019/12/5.
//  Copyright © 2019 Coel Wu. All rights reserved.
//

#include "apppixivapi.h"
#include "basepixivapi.h"
#include "settings.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkProxy>
#include <QUrlQuery>
#include <QEventLoop>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

QNetworkReply* AppPixivAPI::req(QString turl, QString method, QUrlQuery data, bool setData)
{
    QNetworkAccessManager* manager = new QNetworkAccessManager();
    if (Settings::proxyType != "None") {
        QNetworkProxy proxy;
        if (Settings::proxyType == "Socks5") {
            proxy.setType(QNetworkProxy::Socks5Proxy);
        } else if (Settings::proxyType == "Http") {
            proxy.setType(QNetworkProxy::HttpProxy);
        }
        proxy.setHostName(Settings::address);
        proxy.setPort(Settings::port);
        if (Settings::authentication) {
            proxy.setUser(Settings::proxyUsername);
            proxy.setPassword(Settings::proxyPassword);
        }
        manager->setProxy(proxy);
    }
    QUrl url(turl);
    if (setData) {
        url.setQuery(data);
    }
    QNetworkRequest request(url);
    request.setRawHeader("App-OS", "ios");
    request.setRawHeader("App-OS-Version", "12.2");
    request.setRawHeader("App-Version", "7.6.2");
    request.setRawHeader("User-Agent", "PixivIOSApp/7.6.2 (iOS 12.2; iPhone9,1)");
    request.setRawHeader("Authorization", QString("Bearer %1").arg(BasePixivAPI::access_token).toUtf8());
    QNetworkReply* reply = manager->sendCustomRequest(request, method.toUtf8(), "");
    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();
    return reply;
}

QJsonObject AppPixivAPI::follow_next_url(QString url)
{
    QUrlQuery query;
    QNetworkReply *reply = req(url, "GET", query, false);
    QJsonDocument jsonResponse = QJsonDocument::fromJson(reply->readAll());
    QJsonObject obj = jsonResponse.object();
    return obj;
}


// 用户作品列表
QJsonObject AppPixivAPI::user_illusts(int user_id, QString type, QString filter)
{
    QUrlQuery query;
    query.addQueryItem("user_id", QString::number(user_id));
    query.addQueryItem("filter", filter);
    if (type != "") {
        query.addQueryItem("type", type);
    }
    QNetworkReply *reply = req("https://app-api.pixiv.net/v1/user/illusts", "GET", query);
    QJsonDocument jsonResponse = QJsonDocument::fromJson(reply->readAll());
    QJsonObject obj = jsonResponse.object();
    return obj;
}

// 用户收藏作品列表
QJsonObject AppPixivAPI::user_bookmarks_illust(int user_id, QString restrict, QString filter)
{
    QUrlQuery query;
    query.addQueryItem("user_id", QString::number(user_id));
    query.addQueryItem("restrict", restrict);
    query.addQueryItem("filter", filter);
    QNetworkReply *reply = req("https://app-api.pixiv.net/v1/user/bookmarks/illust", "GET", query);
    QJsonDocument jsonResponse = QJsonDocument::fromJson(reply->readAll());
    QJsonObject obj = jsonResponse.object();
    return obj;
}

// 关注用户的新作
// restrict: [public, private]
QJsonObject AppPixivAPI::illust_follow(QString restrict)
{
    QUrlQuery query;
    query.addQueryItem("restrict", restrict);
    QNetworkReply *reply = req("https://app-api.pixiv.net/v2/illust/follow", "GET", query);
    QJsonDocument jsonResponse = QJsonDocument::fromJson(reply->readAll());
    QJsonObject obj = jsonResponse.object();
    return obj;
}

// 作品详情 (类似PAPI.works()，iOS中未使用)
QJsonObject AppPixivAPI::illust_detail(int illust_id)
{
    QUrlQuery query;
    query.addQueryItem("illust_id", QString::number(illust_id));
    QNetworkReply *reply = req("https://app-api.pixiv.net/v1/illust/detail", "GET", query);
    QJsonDocument jsonResponse = QJsonDocument::fromJson(reply->readAll());
    QJsonObject obj = jsonResponse.object();
    return obj;
}

// 作品评论
QJsonObject AppPixivAPI::illust_comments(int illust_id)
{
    QUrlQuery query;
    query.addQueryItem("illust_id", QString::number(illust_id));
    QNetworkReply *reply = req("https://app-api.pixiv.net/v1/illust/comments", "GET", query);
    QJsonDocument jsonResponse = QJsonDocument::fromJson(reply->readAll());
    QJsonObject obj = jsonResponse.object();
    return obj;
}

// 相关作品列表
QJsonObject AppPixivAPI::illust_related(int illust_id, QString filter)
{
    QUrlQuery query;
    query.addQueryItem("illust_id", QString::number(illust_id));
    query.addQueryItem("filter", filter);
    QNetworkReply *reply = req("https://app-api.pixiv.net/v2/illust/related", "GET", query);
    QJsonDocument jsonResponse = QJsonDocument::fromJson(reply->readAll());
    QJsonObject obj = jsonResponse.object();
    return obj;
}

/*
// 作品排行
QJsonObject AppPixivAPI::illust_ranking()
{

}
*/
