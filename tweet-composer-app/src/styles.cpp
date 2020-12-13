#include "styles.h"

const QColor Styles::STANDARD_GREEN("#17a81a");
const QColor Styles::DELETE_RED("#ff0000");
const QString Styles::TYPEAHEAD_BORDER_COLOR = "#17a81a";

const QString Styles::MAIN_WINDOW_STYLE_SHEET =
    "QMainWindow {"
    "background: white;"
    "}";

const QString Styles::MENU_BAR_STYLE_SHEET =
    "QMenuBar::item {"
    "color: #17a81a;"
    "}";

const QString Styles::MENU_STYLE_SHEET =
    "QMenu {"
    "background: white;"
    "}"
    "QMenu::item {"
    "color: #17a81a"
    "}"
    "QMenu::item:selected {"
    "color: white;"
    "background: #17a81a"
    "}"
    "QMenu::separator {"
    "height: 1px;"
    "margin: 3px 1px;"
    "background: #17a81a"
    "}";

const QString Styles::SETTINGS_DIALOG_STYLE_SHEET =
    "QDialog {"
    "background: white;"
    "}";

const QString Styles::GROUPBOX_STYLE_SHEET =
    "QGroupBox {"
    "margin-top: 0.5em;"
    "border: 1px solid #17a81a;"
    "}"
    "QGroupBox::title {"
    "subcontrol-origin: margin;"
    "left: 5px;"
    "padding: 0 3px 0 3px;"
    "color: #17a81a;"
    "}";

const QString Styles::TWEET_TEXT_EDIT_STYLE_SHEET =
    "QTextEdit {"
    "background: transparent;"
    "border: 1px solid #17a81a;"
    "font-size: 15px;"
    "}";

const QString Styles::LINE_EDIT_STYLE_SHEET =
    "QLineEdit { "
    "background: transparent;"
    "padding: 1px 3px; "
    "border: 1px solid #17a81a;"
    "font-size: 15px;"
    "}";

const QString Styles::COMBOBOX_STYLE_SHEET =
    "QComboBox {"
    "padding: 1px 3px;"
    "background: transparent;"
    "border: 1px solid #17a81a;"
    "font-size: 15px;"
    "}";

const QString Styles::BOLD_TOGGLE_BUTTON_STYLE_SHEET =
    "QPushButton {"
    "padding: 4px;"
    "color: #17a81a;"
    "font-size: 15px;"
    "font-weight: bold;"
    "}"
    "QPushButton:hover {"
    "color: white;"
    "}"
    "QPushButton:checked {"
    "color: white;"
    "background: #17a81a;"
    "}";

const QString Styles::ITALIC_TOGGLE_BUTTON_STYLE_SHEET =
    "QPushButton {"
    "padding: 4px;"
    "color: #17a81a;"
    "font-size: 15px;"
    "font-style: italic;"
    "}"
    "QPushButton:hover {"
    "color: white;"
    "}"
    "QPushButton:checked {"
    "color: white;"
    "background: #17a81a;"
    "}";

const QString Styles::UNDERLINE_TOGGLE_BUTTON_STYLE_SHEET =
    "QPushButton {"
    "padding: 4px;"
    "color: #17a81a;"
    "font-size: 15px; "
    "text-decoration: underline;"
    "}"
    "QPushButton:hover {"
    "color: white;"
    "}"
    "QPushButton:checked {"
    "color: white;"
    "background: #17a81a;"
    "}";

const QString Styles::BUTTON_STYLE_SHEET =
    "QPushButton {"
    "color: #17a81a; border: none; background-color: transparent; padding: 3px 4px;"
    "font-size: 15px;"
    "} "
    "QPushButton:disabled {"
    "color: gray; "
    "}"
    "QPushButton:hover {"
    "color: white; border-width: 2px; border-color: #17a81a; background-color: #17a81a;"
    "}";

const QString Styles::DELETE_BUTTON_STYLE_SHEET =
    "QPushButton { "
    "color: #ff0000; border: none; background-color: transparent; padding: 3px 4px;"
    "font-size: 15px;"
    "} "
    "QPushButton:disabled {"
    "color: gray;"
    "}"
    "QPushButton:hover {"
    "color: white; border-width: 2px; border-color: #ff0000; background-color: #ff0000;"
    "}";

const QString Styles::CHECKBOX_STYLE_SHEET =
    "QCheckBox {"
    "font-size: 15px;"
    "}"
    "QCheckBox::indicator {"
    "width: 15px; height: 15px;"
    "}";

const QString Styles::TYPEAHEAD_STYLE_SHEET =
    "QLineEdit {"
    "font-size: 15px; border-radius: 10px;"
    "background: transparent; border: 2px solid #17a81a; padding: 3px 5px;"
    "}";
