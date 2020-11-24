#ifndef TWEETTEMPLATE_H
#define TWEETTEMPLATE_H

#include <QObject>

class TweetTemplate : public QObject
{
    Q_OBJECT
public:
    explicit TweetTemplate(QObject *parent = nullptr);

    int getId() { return id; }
    QString getText() { return text; }

    void setId(int id) { this->id = id; }
    void setText(QString text) { this->text = text; }

signals:

private:
    static int numTemplates;

    int id;
    QString text;
};

#endif // TWEETTEMPLATE_H
