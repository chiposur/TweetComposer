#ifndef TWEETDRAFT_H
#define TWEETDRAFT_H

#include <QObject>

class TweetDraft : public QObject
{
    Q_OBJECT
public:
    explicit TweetDraft(QObject *parent = nullptr);

    int getId() { return id; }
    QString getText() { return text; }

    void setId(int id) { this->id = id; }
    void setText(QString text) { this->text = text; }

signals:

private:
    static int numDrafts;

    int id;
    QString text;
};

#endif // TWEETDRAFT_H
