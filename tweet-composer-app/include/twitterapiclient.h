#ifndef TWITTERAPICLIENT_H
#define TWITTERAPICLIENT_H

#include <QMap>
#include <QNetworkAccessManager>
#include <QObject>

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
    };

    static TwitterApiClient *getInstance();

    RequestId updateStatus(QString tweetText);

signals:
    void updateStatusFinished(RequestId id, ResultType result);

private slots:
    void onUpdateStatusFinished();

private:
    TwitterApiClient();
    ~TwitterApiClient();

    RequestId getNewRequestId() { return ++numRequests; }

    int numRequests = 0;

    QNetworkAccessManager *networkAccessManager;
    QMap<QNetworkReply *, RequestId> *replyToRequestIdMap;
};

#endif // TWITTERAPICLIENT_H
