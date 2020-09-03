
#include <QApplication>
#include "gamesettings.h"
#include <QDebug>
#include "view.h"
#include "scene.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    Widget w;
//    GameSettings::instance().setShowMode(&w);
    View *v = new View();
    Scene* s = new Scene(v);
    s->init();
    s->createEnvironment();
    v->setScene(s);
    GameSettings::instance().setShowMode(v);
    GameSettings::instance().debug();
    return a.exec();
}
