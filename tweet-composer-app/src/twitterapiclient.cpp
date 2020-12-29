#include "twitterapiclient.h"
#include "settings.h"

#include <QNetworkReply>
#include <QUrl>
#include <QUrlQuery>

TwitterApiClient::TwitterApiClient()
{
    networkAccessManager = new QNetworkAccessManager(this);
    replyToRequestIdMap = new QMap<QNetworkReply *, RequestId>();
}

TwitterApiClient::~TwitterApiClient()
{
    delete replyToRequestIdMap;
}

TwitterApiClient *TwitterApiClient::getInstance()
{
    static TwitterApiClient client;
    return &client;
}

RequestId TwitterApiClient::updateStatus(QString tweetText)
{
    QUrlQuery query;
    query.addQueryItem("status", tweetText);
    QByteArray postData = query.toString(QUrl::FullyEncoded).toUtf8();
    QNetworkRequest updateStatusRequest(QUrl("https://api.twitter.com/1.1/statuses/update.json"));
    updateStatusRequest.setRawHeader("oauth_consumer_key", Settings::apiKey.toUtf8());
    updateStatusRequest.setRawHeader("oauth_consumer_secret", Settings::apiSecret.toUtf8());
    updateStatusRequest.setRawHeader("oauth_token", Settings::accessToken.toUtf8());
    updateStatusRequest.setRawHeader("oauth_token_secret", Settings::accessTokenSecret.toUtf8());

    QNetworkReply *reply = networkAccessManager->post(updateStatusRequest, postData);
    connect(reply, SIGNAL(finished()), this, SLOT(onUpdateStatusFinished()));

    RequestId id = getNewRequestId();
    replyToRequestIdMap->insert(reply, id);
    return id;
}

void TwitterApiClient::onUpdateStatusFinished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());

    ResultType result = ResultType::OK;
    QNetworkReply::NetworkError error = reply->error();

    if (error == QNetworkReply::TimeoutError)
    {
        result = ResultType::TIMEOUT;
    }
    else if (error == QNetworkReply::ContentAccessDenied)
    {
        result = ResultType::AUTH_FAILED;
    }

    RequestId id = replyToRequestIdMap->value(reply);
    emit updateStatusFinished(id, result);

    replyToRequestIdMap->remove(reply);
    reply->deleteLater();
}
