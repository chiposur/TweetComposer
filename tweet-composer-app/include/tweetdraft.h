#ifndef TWEETDRAFT_H
#define TWEETDRAFT_H

#include <QString>

class TweetDraft
{
public:
    explicit TweetDraft();

    int getId() const { return id; }
    QString getText() const { return text; }
    QString getName() const { return name; }

    void setId(int id) { this->id = id; }
    void setText(QString text) { this->text = text; }
    void setName(QString name) { this->name = name; }

    static int numDrafts;

    bool operator==(const TweetDraft &other) { return id == other.getId(); }

    TweetDraft &operator=(const TweetDraft &other)
    {
        id = other.getId();
        text = other.getText();
        name = other.getName();

        return *this;
    }

private:
    int id = -1;
    QString text;
    QString name;
};

#endif // TWEETDRAFT_H
