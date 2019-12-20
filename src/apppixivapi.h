//
//  apppixivapi.h
//  PixivDownloader
//
//  Created by TheWanderingCoel on 2019/12/5.
//  Copyright © 2019 Coel Wu. All rights reserved.
//

#ifndef APPPIXIVAPI_H
#define APPPIXIVAPI_H

#include <QNetworkReply>

class AppPixivAPI: public QObject
{
public:
    static QNetworkReply* req(QString url, QString method, QUrlQuery data, bool setData = true);
    static QJsonObject follow_next_url(QString url);
    QJsonObject user_illusts(int user_id, QString type = "illust", QString filter = "for_ios");
    QJsonObject user_bookmarks_illust(int user_id, QString restrict = "public", QString filter = "for_ios");
    QJsonObject illust_follow(QString restrict = "public");
    QJsonObject illust_detail(int illust_id);
    QJsonObject illust_comments(int illust_id);
    QJsonObject illust_related(int illust_id, QString filter);
};

#endif // APPPIXIVAPI_H
