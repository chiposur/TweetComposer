#include "tweetdraft.h"

int TweetDraft::numDrafts = 0;

TweetDraft::TweetDraft()
{
    id = numDrafts;
}
