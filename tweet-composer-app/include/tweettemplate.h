#ifndef TWEETTEMPLATE_H
#define TWEETTEMPLATE_H

#include <QString>

class TweetTemplate
{
public:
    explicit TweetTemplate();

    int getId() const { return id; }
    QString getText() const { return text; }

    void setId(int id) { this->id = id; }
    void setText(QString text) { this->text = text; }

    static int numTemplates;

private:
    int id;
    QString text;
};

#endif // TWEETTEMPLATE_H
