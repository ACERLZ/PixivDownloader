//
//  basepixivapi.cpp
//  PixivDownloader
//
//  Created by TheWanderingCoel on 2019/12/4.
//  Copyright © 2019 Coel Wu. All rights reserved.
//

#include "basepixivapi.h"
#include "paths.h"
#include "logger.h"
#include "settings.h"

#include <QDateTime>
#include <QDir>
#include <QFile>
#include <QDataStream>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkProxy>
#include <QCryptographicHash>
#include <QEventLoop>
#include <QJsonDocument>
#include <QJsonObject>

QString BasePixivAPI::client_id = "MOBrBDS8blbauoSck0ZfDbtuzpyT";
QString BasePixivAPI::client_secret = "lsACyCD94FhDUtGTXi3QzcFE2uU1hqtDaKeqrdwj";
QString BasePixivAPI::hash_secret = "28c1fdd170a5204386cb1313c7077b34f83e4aaf4aa829ce78c231e05b0bae2c";
QString BasePixivAPI::access_token;
int BasePixivAPI::user_id = 0;
QString BasePixivAPI::refresh_token = "";

bool BasePixivAPI::auth(QString username, QString password, QString refresh_token)
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
    QNetworkRequest request(QString("https://oauth.secure.pixiv.net/auth/token"));
    request.setRawHeader("User-Agent", "PixivAndroidApp/5.0.64 (Android 6.0)");
    QDateTime UTC(QDateTime::currentDateTimeUtc());
    QString local_time = UTC.toString("yyyy-MM-ddThh:mm:ss+00:00");
    request.setRawHeader("X-Client-Time", local_time.toUtf8());
    request.setRawHeader("X-Client-Hash", QCryptographicHash::hash((local_time + BasePixivAPI::hash_secret).toUtf8(),QCryptographicHash::Md5).toHex());
    request.setRawHeader("Content-type", "application/x-www-form-urlencoded");
    request.setRawHeader("host", "oauth.secure.pixiv.net");
    QByteArray data;
    data.append("get_secure_url=1&");
    data.append(QString("client_id=%1&").arg(BasePixivAPI::client_id));
    data.append(QString("client_secret=%1&").arg(BasePixivAPI::client_secret));
    QString type;
    if (username != "" && password != "") {
        type = "password";
        data.append("grant_type=password&");
        data.append(QString("username=%1&").arg(username));
        data.append(QString("password=%1").arg(password));
    } else if (refresh_token != "") {
        type = "refresh_token";
        data.append("grant_type=refresh_token&");
        data.append(QString("refresh_token=%1").arg(refresh_token));
    }
    QNetworkReply* reply = manager->sendCustomRequest(request, "POST", data);
    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();
    if (reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() != 200 && reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() != 301 && reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() != 302) {
        if (type == "password") {
            Logger::log("auth() failed! check username and password.", "error");
            return false;
        } else {
            Logger::log("auth() failed! check refresh_token.", "error");
            return false;
        }
    } else {
        Logger::log(QString("auth() successed! username: %1").arg(username), "info");
    }

    try {
        QJsonDocument jsonResponse = QJsonDocument::fromJson(reply->readAll());
        QJsonObject obj = jsonResponse.object().value("response").toObject();
        QJsonObject user = obj.value("user").toObject();
        BasePixivAPI::access_token = obj["access_token"].toString();
        BasePixivAPI::user_id = user["id"].toString().toInt();
        BasePixivAPI::refresh_token = obj["refresh_token"].toString();
    } catch (...) {

    }

    reply->deleteLater();

    return true;
}

void BasePixivAPI::download(QString url, QString authorName, int authorId, QString artworkTitle, int artworkId, QString referer)
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
    QNetworkRequest request(url);
    request.setRawHeader("Referer", referer.toUtf8());
    QNetworkReply* reply = manager->sendCustomRequest(request, "GET", "");
    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();
    QString path = Paths::downloadLocation + "/" + authorName + " - " +QString::number(authorId) + "/" + artworkTitle + " - " + QString::number(artworkId);
    QDir dir(path);
    if (!dir.exists()) {
        dir.mkpath(".");
    }
    QByteArray data = reply->readAll();
    QFile file(path + "/" + url.split("/")[url.split("/").length()-1]);
    file.open(QIODevice::WriteOnly);
    file.write(data);
    file.close();
    reply->deleteLater();
}
