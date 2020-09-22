#include <QApplication>
#include "gamesettings.h"
#include <QDebug>
#include "view.h"
#include "gamescene.h"
#include "menuscene.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    GameSettings::instance().setShowMode(&w);
    View *v = new View();
//    GameScene* s = new GameScene(v);
//    s->createEnvironment();
//    s->createPlayer();
//    s->createUI();
//    v->setScene(s);
//    s->debug();
    MenuScene* s = new MenuScene();
    s->debug();
    v->setScene(s);
    GameSettings::instance().setShowMode(v);
    GameSettings::instance().debug();
    return a.exec();
}
