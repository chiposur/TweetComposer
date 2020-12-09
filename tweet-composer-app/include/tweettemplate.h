#ifndef TWEETTEMPLATE_H
#define TWEETTEMPLATE_H

#include <QString>

class TweetTemplate
{
public:
    explicit TweetTemplate();

    int getId() const { return id; }
    QString getText() const { return text; }
    QString getName() const { return name; }

    void setId(int id) { this->id = id; }
    void setText(QString text) { this->text = text; }
    void setName(QString name) { this->name = name; }

    static int numTemplates;

    bool operator==(const TweetTemplate &other) { return id == other.getId(); }

    TweetTemplate &operator=(const TweetTemplate &other)
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

#endif // TWEETTEMPLATE_H
