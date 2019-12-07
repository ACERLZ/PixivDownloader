#ifndef BASEPIXIVAPI_H
#define BASEPIXIVAPI_H

#include <QObject>

class BasePixivAPI: public QObject
{
public:
    static bool auth(QString username = "", QString password = "", QString refresh_token = "");
    static void download(QString url, QString authorName, int authorId, QString artworkTitle, int artworkId, QString referer = "https://app-api.pixiv.net/");
    static QString client_id;
    static QString client_secret;
    static QString hash_secret;
    static QString access_token;
    static int user_id;
    static QString refresh_token;
};

#endif // BASEPIXIVAPI_H
