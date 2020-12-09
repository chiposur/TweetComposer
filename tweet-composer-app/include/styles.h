#ifndef STYLES_H
#define STYLES_H

#include <QString>

class Styles
{
public:
    static const int TWEET_MAX_LENGTH = 280;
    static const int TWEET_CHARS_REMAINING_LIMIT = 20;
    static const int TWEET_WIDTH_PX = 509;
    static const int TWEET_MAX_HEIGHT_PX = 190;
    static const int TWEET_FONT_SIZE = 15;

    static const int TYPEAHEAD_BORDER_RADIUS = 10;
    static const int TYPEAHEAD_PADDING_TOP_BOTTOM = 3;
    static const int TYPEAHEAD_PADDING_LEFT_RIGHT = 5;
    static const QString TYPEAHEAD_BORDER_COLOR;
};

#endif // STYLES_H
