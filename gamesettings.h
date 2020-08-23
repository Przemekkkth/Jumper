#ifndef GAMESETTINGS_H
#define GAMESETTINGS_H
#include <QString>
#include <QSize>

class GameSettings
{
public:
    static GameSettings& instance();
    static void debug();
private:
    GameSettings();
    GameSettings(const GameSettings&) = delete;
    GameSettings& operator=(const GameSettings&) = delete;
    static QString sResolutionStr;
    static QSize sResolution;
    static int sWidth;
    static int sHeight;
    static QString sProportionStr;
    static QSize sProportion;
    static int sProportionWidth;
    static int sProportionHeight;
    static QSize sUnitSize;
    static int sUnitSizeWidth;
    static int sUnitSizeHeight;

    static void init();
};

#endif // GAMESETTINGS_H
