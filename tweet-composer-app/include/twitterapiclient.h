#ifndef TWITTERAPICLIENT_H
#define TWITTERAPICLIENT_H

#include <QMap>
#include <QNetworkAccessManager>
#include <QOAuth1>

typedef int RequestId;

class TwitterApiClient : public QObject
{
    Q_OBJECT

public:
    enum class ResultType
    {
        OK,
        TIMEOUT,
        AUTH_FAILED,
        UNKNOWN_NETWORK_ERROR,
        PROTOCOL_INVALID_OPERATION_ERROR,
    };

    static TwitterApiClient *getInstance();

    void updateCredentials();

    RequestId updateStatus(QString tweetText);

signals:
    void updateStatusFinished(RequestId id, TwitterApiClient::ResultType result);

private slots:
    void onUpdateStatusFinished();

private:
    TwitterApiClient();
    ~TwitterApiClient();

    RequestId getNewRequestId() { return ++numRequests; }

    int numRequests = 0;

    QNetworkAccessManager *networkAccessManager;
    QOAuth1 *oauth1;
    QMap<QNetworkReply *, RequestId> *replyToRequestIdMap;
};

#endif // TWITTERAPICLIENT_H
