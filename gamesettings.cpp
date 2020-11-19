#include "gamesettings.h"
#include <QStringList>
#include <QDebug>
#include <QWidget>
#include <QGraphicsLineItem>
#include <QFontDatabase>
#include <QSoundEffect>
#include <QMediaPlayer>
#include <QMediaPlaylist>

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
QString GameSettings::sPickUpCoinSFXFilePath = "qrc:/sfx/sfx/Retro_8-Bit_Game-Pickup_Object_Item_Coin_01.wav";
QMediaPlaylist* GameSettings::sMediaPlaylist;
QMediaPlayer* GameSettings::sBGAudioMedia;
QMediaPlayer* GameSettings::sJumpPlayerSFXMedia;
QMediaPlayer* GameSettings::sDeathPlayerSFXMedia;
QMediaPlayer* GameSettings::sPickUpCoinSFXMedia;
const int GameSettings::sDEFAULT_PLAYER_JUMP_VOLUME = 75;
const int GameSettings::sDEFAULT_PLAYER_DEATH_VOLUME = 75;
const int GameSettings::sDEFAULT_PICK_UP_COIN_VOLUME = 75;
const int GameSettings::sDEFAULT_BG_AUDIO_VOLUME = 50;
//StyleSheets
QString GameSettings::sSliderStyleSheet = "QSlider::groove:horizontal { "
                                          "border: 1px solid #999999; "
                                          "height: 64px; "
                                          "background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #B1B1B1, stop:1 #c4c4c4); "
                                          "margin: 2px 0; "
                                          "} "
                                          "QSlider::handle:horizontal { "
                                          "background-image: url(:/gui/gui/coin1.png); "
                                          "background-repeat: no-repeat;"
                                          "background-position: center;"
                                          "border: 1px solid #5c5c5c; "
                                          "width: 32px; "
                                          "height: 32px;"
                                          "} ";

QString GameSettings::sCheckBoxStyleSheet = "QCheckBox{background-color: #b5c153; color: #11ee11 }"
                                            "QCheckBox::indicator { width: 32px; height: 32px; }"
                                            "QCheckBox::indicator:unchecked { image: url(:/gui/gui/unchecked.png); }"
                                            "QCheckBox::indicator:checked { image: url(:/gui/gui/checked.png); }";

GameSettings::~GameSettings()
{
    delete sJumpPlayerSFXMedia;
    delete sDeathPlayerSFXMedia;
    delete sPickUpCoinSFXMedia;
    delete sBGAudioMedia;
}

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

void GameSettings::playPickUpCoinSFX()
{
    if (sPickUpCoinSFXMedia->state() == QMediaPlayer::PlayingState){
        sPickUpCoinSFXMedia->setPosition(0);
    }
    else if (sPickUpCoinSFXMedia->state() == QMediaPlayer::StoppedState){
        sPickUpCoinSFXMedia->play();
    }
}

void GameSettings::playBGGameAudio()
{
    sBGAudioMedia->play();
}

void GameSettings::stopBGGameAudio()
{
    sBGAudioMedia->stop();
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
    sJumpPlayerSFXMedia->setVolume(sDEFAULT_PLAYER_JUMP_VOLUME);
    sDeathPlayerSFXMedia = new QMediaPlayer();
    sDeathPlayerSFXMedia->setMedia(QUrl(sDeathPlayerSFXFilePath));
    sDeathPlayerSFXMedia->setVolume(sDEFAULT_PLAYER_DEATH_VOLUME);
    sPickUpCoinSFXMedia = new QMediaPlayer();
    sPickUpCoinSFXMedia->setMedia(QUrl(sPickUpCoinSFXFilePath));
    sPickUpCoinSFXMedia->setVolume(sDEFAULT_PICK_UP_COIN_VOLUME);

    sMediaPlaylist = new QMediaPlaylist();
    sMediaPlaylist->addMedia(QUrl(sBGAudioFilePath));
    sMediaPlaylist->setPlaybackMode(QMediaPlaylist::Loop);
    sBGAudioMedia = new QMediaPlayer();
    sBGAudioMedia->setPlaylist(sMediaPlaylist);
    sBGAudioMedia->setVolume(sDEFAULT_BG_AUDIO_VOLUME);
}
