#include "tweetdraft.h"

int TweetDraft::numDrafts = 0;

TweetDraft::TweetDraft(QObject *parent) : QObject(parent)
{
    ++numDrafts;
    id = numDrafts;
}
