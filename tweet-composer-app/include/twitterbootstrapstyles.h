#ifndef TWITTERBOOTSTRAPSTYLES_H
#define TWITTERBOOTSTRAPSTYLES_H

/*
 * The following class ports CSS styles from the Twitter Boostrap libary, with style code
 * derived in part from Boostrap alerts.
 *
 * The following text contains the Twitter Bootstrap license
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2011-2018 Twitter, Inc.
 * Copyright (c) 2011-2018 The Bootstrap Authors
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#include <QString>

class TwitterBootstrapStyles
{
public:
    static const QString INFO_BG_COLOR;
    static const QString ERROR_BG_COLOR;
    static const QString INFO_TEXT_COLOR;
    static const QString ERROR_TEXT_COLOR;
    static const QString INFO_BORDER_COLOR;
    static const QString ERROR_BORDER_COLOR;
};

const QString TwitterBootstrapStyles::INFO_BG_COLOR = "#5bc0de";
const QString TwitterBootstrapStyles::ERROR_BG_COLOR = "#d9534f";
const QString TwitterBootstrapStyles::INFO_TEXT_COLOR = "#004085";
const QString TwitterBootstrapStyles::ERROR_TEXT_COLOR = "#721c24";
const QString TwitterBootstrapStyles::INFO_BORDER_COLOR = "#b8daff";
const QString TwitterBootstrapStyles::ERROR_BORDER_COLOR = "#f5c6cb";

#endif // TWITTERBOOSTRAPSTYLES_H
