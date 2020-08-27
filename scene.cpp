#include "scene.h"
#include "gamesettings.h"
#include <QKeyEvent>
#include <QApplication>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

Scene::Scene(QObject *parent) : QGraphicsScene (parent)
{
    setSceneRect(-1*GameSettings::instance().resolutionSize().width()/2,    //x0->mi
                 -1*GameSettings::instance().resolutionSize().height()/2,   //y0
                 GameSettings::instance().resolutionSize().width(),         //w0
                 GameSettings::instance().resolutionSize().height());       //h0
#ifndef QT_NO_DEBUG
    for(int row = 0; row < GameSettings::instance().proportionSize().height(); ++row)
    {
//        qDebug() << "x0 " << -1*GameSettings::instance().resolutionSize().width()/2 <<
//                    " y0 " << -1*GameSettings::instance().resolutionSize().height()/2 + row*GameSettings::instance().unitSize().height()
//                 << " x1 " << GameSettings::instance().resolutionSize().width()/2
//                 << " y1 " << -1*row*GameSettings::instance().unitSize().height()/2 + row*GameSettings::instance().unitSize().height();
        int offset = (row == 0 ? 1 : 0) || (row == GameSettings::instance().proportionSize().height() ? -1 : 0);
        addLine(-1*GameSettings::instance().resolutionSize().width()/2,
                -1*GameSettings::instance().resolutionSize().height()/2 + row*GameSettings::instance().unitSize().height(), // (x0, y0)
                GameSettings::instance().resolutionSize().width()/2,
                -1*GameSettings::instance().resolutionSize().height()/2 + row*GameSettings::instance().unitSize().height(),    // (x1,y1)
                QPen(QColor(Qt::blue)));                                    // color
    }
    for(int column = 0; column < GameSettings::instance().proportionSize().width(); ++column)
    {

    }
    addLine(0, -1*GameSettings::instance().resolutionSize().height()/2, // (x0, y0)
            0, GameSettings::instance().resolutionSize().height()/2,    // (x1,y1)
            QPen(QColor(Qt::red) ));                                    // color

    addLine(-1*GameSettings::instance().resolutionSize().width()/2, 0, // (x0, y0)
            GameSettings::instance().resolutionSize().width()/2, 0,    // (x1,y1)
            QPen(QColor(Qt::red)));                                    // color
#endif
}

void Scene::keyPressEvent(QKeyEvent *event)
{
    qDebug() << "void Scene::keyPressEvent(QKeyEvent *event)";
    if(event->key() == Qt::Key_Escape)
    {
        QApplication::instance()->quit();
    }
    if(event->key() == Qt::Key_Left || event->key() == Qt::Key_Right || event->key() == Qt::Key_Up || event->key() == Qt::Key_Down)
    {

    }
    else
    {
         QGraphicsScene::keyPressEvent(event);
    }
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        qDebug() << "Mouse clicked at " << event->scenePos();
    }
}

void Scene::wheelEvent(QGraphicsSceneWheelEvent *event)
{
    qDebug() << "void Scene::wheelEvent(QWheelEvent *event)";
    emit setCenterOn(QPointF(0,0));
}
