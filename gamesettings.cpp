#include "gamesettings.h"
#include <QStringList>
#include <QDebug>
#include <QWidget>
#include <QGraphicsLineItem>

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

GameSettings::GameSettings()
{
    init();
}

void GameSettings::init()
{
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
    sState = Stopped;
}
