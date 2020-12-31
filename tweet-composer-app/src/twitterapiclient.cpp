#include "twitterapiclient.h"
#include "settings.h"

#include <QNetworkReply>
#include <QUrl>
#include <QUrlQuery>

TwitterApiClient::TwitterApiClient()
{
    networkAccessManager = new QNetworkAccessManager(this);
    oauth1 = new QOAuth1(networkAccessManager, this);
    oauth1->setSignatureMethod(QOAuth1::SignatureMethod::Hmac_Sha1);
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
    // Update credentials as they may have changed
    oauth1->setClientCredentials(Settings::apiKey, Settings::apiSecret);
    oauth1->setTokenCredentials(Settings::accessToken, Settings::accessTokenSecret);

    QVariantMap parameters;
    parameters.insert("status", tweetText);
    QNetworkReply *reply = oauth1->post(QUrl("https://api.twitter.com/1.1/statuses/update.json"), parameters);
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
    else if (error == QNetworkReply::UnknownNetworkError)
    {
        result = ResultType::UNKNOWN_NETWORK_ERROR;
    }

    RequestId id = replyToRequestIdMap->value(reply);
    emit updateStatusFinished(id, result);

    replyToRequestIdMap->remove(reply);
    reply->deleteLater();
}
