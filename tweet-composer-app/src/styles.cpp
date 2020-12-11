#include "styles.h"

const QColor Styles::STANDARD_GREEN("#17a81a");
const QColor Styles::DELETE_RED("#ff0000");
const QString Styles::TYPEAHEAD_BORDER_COLOR = "#17a81a";

const QString Styles::BUTTON_STYLE_SHEET =
    "QPushButton { color: #17a81a; border: none; background-color: transparent; padding: 3px 4px; "
    "font-size: 15px; } "
    "QPushButton:disabled { color: gray; }"
    "QPushButton:hover { color: white; border-width: 2px; border-color: #17a81a; background-color: #17a81a; }";

const QString Styles::DELETE_BUTTON_STYLE_SHEET =
    "QPushButton { color: #ff0000; border: none; background-color: transparent; padding: 3px 4px; "
    "font-size: 15px; } "
    "QPushButton:disabled { color: gray; }"
    "QPushButton:hover { color: white; border-width: 2px; border-color: #ff0000; background-color: #ff0000; }";

const QString Styles::CHECKBOX_STYLE_SHEET =
    "QCheckBox { font-size: 15px; }";

const QString Styles::TYPEAHEAD_STYLE_SHEET =
    "QLineEdit { font-size: 15px; border-radius: 10px; "
    "background: transparent; border: 2px solid #17a81a; padding: 3px 5px; }";
