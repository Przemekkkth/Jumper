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
    static QSizeF unitSize();
    static void setShowMode(QWidget* widget);
    static void debugGraphicsLineItem(QGraphicsLineItem* line);
    enum State{Played, Stopped, Paused};
    static State GameState();
    static void setGameState(State newState);
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
    static QSizeF sUnitSize;
    static qreal sUnitSizeWidth;
    static qreal sUnitSizeHeight;
    static bool sFullScreen;
    static State sState;
    static void init();
};

#endif // GAMESETTINGS_H
