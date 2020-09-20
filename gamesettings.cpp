#include "gamesettings.h"
#include <QStringList>
#include <QDebug>
#include <QWidget>
#include <QGraphicsLineItem>
#include <QFontDatabase>
#include <QSoundEffect>
#include <QMediaPlayer>

QString GameSettings::sResolutionStr;
QSize GameSettings::sResolution;
int GameSettings::sWidth;
int GameSettings::sHeight;
QString GameSettings::sProportionStr;
QSize GameSettings::sProportion;
int GameSettings::sProportionWidth;
int GameSettings::sProportionHeight;
QSizeF GameSettings::sUnitSize;
qreal GameSettings::sUnitSizeWidth;
qreal GameSettings::sUnitSizeHeight;
bool GameSettings::sFullScreen;
GameSettings::State GameSettings::sState;
QPointF GameSettings::sDefaultPlayerPosition;
QFont GameSettings::sGameFont;
int GameSettings::sGameFontDefaultSize = 25;
//Audio
QString GameSettings::sBGAudioFilePath = "qrc:/audio/audio/Around the Bend 100 BPM.wav";
QString GameSettings::sJumpPlayerSFXFilePath = "qrc:/sfx/sfx/Retro_8-Bit_Game-Jump_Lift_TakeOff_07.wav";
QString GameSettings::sDeathPlayerSFXFilePath = "qrc:/sfx/sfx/Death01.wav";
QMediaPlayer* GameSettings::sBGAudioMedia;
QMediaPlayer* GameSettings::sJumpPlayerSFXMedia;
QMediaPlayer* GameSettings::sDeathPlayerSFXMedia;

GameSettings &GameSettings::instance()
{
    static GameSettings gameSettings;
    return gameSettings;
}

void GameSettings::debug()
{
    qDebug() << "Resolution: " << sResolutionStr << " Proportion: " << sProportionStr << " UnitSize: " <<
                sUnitSize.width() << "x" << sUnitSize.height();
}

QSize GameSettings::resolutionSize()
{
    return sResolution;
}

QSize GameSettings::proportionSize()
{
    return sProportion;
}

QSizeF GameSettings::unitSize()
{
    return sUnitSize;
}

void GameSettings::setShowMode(QWidget *widget)
{
    if(sFullScreen)
    {
        widget->showFullScreen();
    }
    else {
        widget->show();
    }
}

void GameSettings::debugGraphicsLineItem(QGraphicsLineItem *line)
{
    qDebug() << "Vert Lines: (" << line->line().x1() << "," << line->line().y1() << "), (" << line->line().x2() << ", " << line->line().y2() << ")";
}

GameSettings::State GameSettings::GameState()
{
    return sState;
}

void GameSettings::setGameState(GameSettings::State newState)
{
    if(sState == newState)
        return;
    else {
        sState = newState;
    }
}

void GameSettings::playPlayerJumpSFX()
{
    if (sJumpPlayerSFXMedia->state() == QMediaPlayer::PlayingState){
        sJumpPlayerSFXMedia->setPosition(0);
    }
    else if (sJumpPlayerSFXMedia->state() == QMediaPlayer::StoppedState){
        sJumpPlayerSFXMedia->play();
    }
}

void GameSettings::playPlayerDeathSFX()
{
    sDeathPlayerSFXMedia->play();
}

GameSettings::GameSettings()
{
    init();
}

void GameSettings::init()
{
    //Font
    int id = QFontDatabase::addApplicationFont(":/fonts/fonts/Blue Sky 8x8 Monospaced.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    sGameFont.setFamily(family);
    sGameFont.setPixelSize(sGameFontDefaultSize);
    //Resolution
    sResolutionStr = "1366x768";
    int width = sResolutionStr.split("x").at(0).toInt();
    int height = sResolutionStr.split("x").at(1).toInt();
    sResolution = QSize(width, height);
    sWidth = sResolution.width();
    sHeight = sResolution.height();
    //Proportion
    sProportionStr = "16x9";
    int propWidth = sProportionStr.split('x').at(0).toInt();
    int propHeight = sProportionStr.split('x').at(1).toInt();
    sProportion = QSize(propWidth, propHeight);
    sProportionWidth = sProportion.width();
    sProportionHeight = sProportion.height();
    sUnitSize = QSizeF( qreal(sWidth)/qreal(sProportionWidth), qreal(sHeight)/qreal(sProportionHeight));
    sUnitSizeWidth = sUnitSize.width();
    sUnitSizeHeight = sUnitSize.height();
    //Others
    sFullScreen = true;
    sState = Played;
    //Player
    sDefaultPlayerPosition = QPointF(-sWidth/2+3*sUnitSizeWidth, sHeight/2-2*sUnitSizeHeight);
    //Audio
    sJumpPlayerSFXMedia = new QMediaPlayer();
    sJumpPlayerSFXMedia->setMedia(QUrl(sJumpPlayerSFXFilePath));
}
