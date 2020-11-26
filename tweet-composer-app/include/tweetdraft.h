#ifndef TWEETDRAFT_H
#define TWEETDRAFT_H

#include <QString>

class TweetDraft
{
public:
    explicit TweetDraft();

    int getId() const { return id; }
    QString getText() const { return text; }

    void setId(int id) { this->id = id; }
    void setText(QString text) { this->text = text; }

    static int numDrafts;

    bool operator==(const TweetDraft &other) { return id == other.getId(); }

    TweetDraft &operator=(const TweetDraft &other)
    {
        id = other.getId();
        text = other.getText();

        return *this;
    }

private:
    int id;
    QString text;
};

#endif // TWEETDRAFT_H
