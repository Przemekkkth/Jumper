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
    GameSettings::instance().playBGGameAudio();
    View *view = new View();
    GameScene* gameScene = new GameScene();
    MenuScene* menuScene = new MenuScene();
    OptionsScene* optionsScene = new OptionsScene();
//connect for menuScene 1) Quit 2)Start Game 3) Go to OptionsView
    QObject::connect(menuScene, &MenuScene::quitButtonClicked, [](){
        QApplication::instance()->quit();
    });
    QObject::connect(menuScene, &MenuScene::startButtonClicked, [view, gameScene](){
        GameSettings::instance().setGameState(GameSettings::State::Played);
        gameScene->restartGame();
        view->setScene(gameScene);
    });
    QObject::connect(menuScene, &MenuScene::optionsButtonClicked, [view, optionsScene](){
//        GameSettings::instance().setGameState(GameSettings::State::Played);
//        gameScene->restartGame();
        view->setScene(optionsScene);
    });

//connect for gameScene 1) Go to MenuView
    QObject::connect(gameScene, &GameScene::backActionActivated, [view, gameScene](){
        GameSettings::instance().setGameState(GameSettings::State::Stopped);
        gameScene->restartGame();
        view->setScene(gameScene);
    });

    view->setScene(menuScene);
    GameSettings::instance().setShowMode(view);
    GameSettings::instance().debug();
    return a.exec();
}
