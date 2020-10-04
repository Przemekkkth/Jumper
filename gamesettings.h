#ifndef GAMESETTINGS_H
#define GAMESETTINGS_H
#include <QString>
#include <QSize>
#include <QPointF>
#include <QFont>


class QGraphicsLineItem;
class QWidget;
class QMediaPlayer;

class GameSettings
{
public:
    ~GameSettings();
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
    static QPointF sDefaultPlayerPosition;
    static QFont sGameFont;
    static int sGameFontDefaultSize;
    static QString sSliderStyleSheet;
//Audio
    static void playPlayerJumpSFX();
    static void playPlayerDeathSFX();
    static void playBGGameAudio();
    static void stopBGGameAudio();
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
//Audio
    static QString sBGAudioFilePath;
    static QString sJumpPlayerSFXFilePath;
    static QString sDeathPlayerSFXFilePath;
    static QMediaPlayer* sBGAudioMedia;
    static QMediaPlayer* sJumpPlayerSFXMedia;
    static QMediaPlayer* sDeathPlayerSFXMedia;
    static const int sDEFAULT_PLAYER_JUMP_VOLUME;
    static const int sDEFAULT_PLAYER_DEATH_VOLUME;
    static const int sDEFAULT_BG_AUDIO_VOLUME;
};

#endif // GAMESETTINGS_H
