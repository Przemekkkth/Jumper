#ifndef GAMESETTINGS_H
#define GAMESETTINGS_H
#include <QString>
#include <QSize>
class QGraphicsLineItem;
class QWidget;

class GameSettings
{
public:
    static GameSettings& instance();
    static void debug();
    static QSize resolutionSize();
    static QSize proportionSize();
    static QSize unitSize();
    static void setShowMode(QWidget* widget);
    static void debugGraphicsLineItem(QGraphicsLineItem* line);
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
    static bool sFullScreen;
    static void init();
};

#endif // GAMESETTINGS_H
