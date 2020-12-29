#ifndef STYLES_H
#define STYLES_H

#include <QColor>
#include <QString>

class Styles
{
public:
    static const int TWEET_MAX_LENGTH = 280;
    static const int TWEET_CHARS_REMAINING_LIMIT = 20;
    static const int TWEET_WIDTH_PX = 509;
    static const int TWEET_MAX_HEIGHT_PX = 190;
    static const int TWEET_FONT_SIZE = 15;

    static const QColor STANDARD_GREEN;
    static const QColor DELETE_RED;
    static const QString TYPEAHEAD_BORDER_COLOR;

    static const QString MAIN_WINDOW_STYLE_SHEET;
    static const QString MENU_BAR_STYLE_SHEET;
    static const QString MENU_STYLE_SHEET;
    static const QString SETTINGS_DIALOG_STYLE_SHEET;
    static const QString GROUPBOX_STYLE_SHEET;
    static const QString TWEET_TEXT_EDIT_STYLE_SHEET;
    static const QString LINE_EDIT_STYLE_SHEET;
    static const QString BOLD_TOGGLE_BUTTON_STYLE_SHEET;
    static const QString ITALIC_TOGGLE_BUTTON_STYLE_SHEET;
    static const QString UNDERLINE_TOGGLE_BUTTON_STYLE_SHEET;
    static const QString COMBOBOX_STYLE_SHEET;
    static const QString BUTTON_STYLE_SHEET;
    static const QString DELETE_BUTTON_STYLE_SHEET;
    static const QString TWITTER_BUTTON_STYLE_SHEET;
    static const QString CHECKBOX_STYLE_SHEET;
    static const QString TYPEAHEAD_STYLE_SHEET;
};

#endif // STYLES_H
