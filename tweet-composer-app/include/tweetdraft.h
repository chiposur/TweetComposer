#ifndef TWEETDRAFT_H
#define TWEETDRAFT_H

#include <QString>

class TweetDraft
{
public:
    explicit TweetDraft();

    int getId() { return id; }
    QString getText() { return text; }

    void setId(int id) { this->id = id; }
    void setText(QString text) { this->text = text; }

    static int numDrafts;

private:
    int id;
    QString text;
};

#endif // TWEETDRAFT_H
