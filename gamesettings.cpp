#include "gamesettings.h"
#include <QStringList>
#include <QDebug>

QString GameSettings::sResolutionStr;
QSize GameSettings::sResolution;
int GameSettings::sWidth;
int GameSettings::sHeight;
QString GameSettings::sProportionStr;
QSize GameSettings::sProportion;
int GameSettings::sProportionWidth;
int GameSettings::sProportionHeight;
QSize GameSettings::sUnitSize;
int GameSettings::sUnitSizeWidth;
int GameSettings::sUnitSizeHeight;

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
    sUnitSize = QSize( sWidth/sProportionWidth, sHeight/sProportionHeight);
    sUnitSizeWidth = sUnitSize.width();
    sUnitSizeHeight = sUnitSize.height();
}
