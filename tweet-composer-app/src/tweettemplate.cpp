#include "tweettemplate.h"

int TweetTemplate::numTemplates = 0;

TweetTemplate::TweetTemplate(QObject *parent) : QObject(parent)
{
    ++numTemplates;
    id = numTemplates;
}
