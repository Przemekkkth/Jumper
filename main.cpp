#include <QApplication>
#include "gamesettings.h"
#include <QDebug>
#include "view.h"
#include "gamescene.h"
#include "menuscene.h"
#include "mainscene.h"
#include "optionsscene.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
   //a.setStyleSheet("QSlider { background-color: yellow } QSlider::handle{ background-image: url(:/gui/gui/coin1.png); width: 32px; height: 32px;}" );
    GameSettings::instance().playBGGameAudio();
    View *view = new View();
    GameScene* gameScene = new GameScene();
    MenuScene* menuScene = new MenuScene();
    OptionsScene* optionsScene = new OptionsScene();
//connect for menuScene 1)Start Game 2) Go to OptionsView 3) Quit
    QObject::connect(menuScene, &MenuScene::startButtonClicked, [view, gameScene](){
        GameSettings::instance().setGameState(GameSettings::State::Played);
        gameScene->restartGame();
        view->setScene(gameScene);
    });
    QObject::connect(menuScene, &MenuScene::optionsButtonClicked, [view, optionsScene](){
        view->setScene(optionsScene);
    });
    QObject::connect(menuScene, &MenuScene::quitButtonClicked, [](){
        QApplication::instance()->quit();
    });
//connect for gameScene 1) Go to MenuScene
    QObject::connect(gameScene, &GameScene::goToMenu, [view, optionsScene, menuScene](){
        GameSettings::instance().setGameState(GameSettings::State::Stopped);
        view->setScene(optionsScene);
        view->setScene(menuScene);
    });
//connect for optionsScene 1) Go to MenuScene
    QObject::connect(optionsScene, &OptionsScene::backActionActivated, [view, menuScene](){
        view->setScene(menuScene);
    });
    view->setScene(menuScene);
    GameSettings::instance().setShowMode(view);
    GameSettings::instance().debug();
    return a.exec();
}
