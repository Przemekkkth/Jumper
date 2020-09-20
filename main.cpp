#include <QApplication>
#include "gamesettings.h"
#include <QDebug>
#include "view.h"
#include "gamescene.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    Widget w;
//    GameSettings::instance().setShowMode(&w);
    View *v = new View();
    GameScene* s = new GameScene(v);
    s->createEnvironment();
    s->createPlayer();
    s->createUI();
    v->setScene(s);
    s->debug();
    GameSettings::instance().setShowMode(v);
    GameSettings::instance().debug();
    return a.exec();
}
