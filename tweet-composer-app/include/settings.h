#ifndef SETTINGS_H
#define SETTINGS_H

#include <QString>

class Settings
{
public:
    static QString apiKey;
    static QString apiSecret;
    static QString accessToken;
    static QString accessTokenSecret;
    static bool encryptDraftsOnDisk;
    static bool encryptTemplatesOnDisk;
    static bool persistWindowState;
};

#endif // SETTINGS_H
