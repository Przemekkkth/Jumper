#include "scene.h"
#include "gamesettings.h"
#include <QKeyEvent>
#include <QApplication>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QGraphicsLineItem>

Scene::Scene(QObject *parent) : QGraphicsScene (parent)
{
    setSceneRect(-1*GameSettings::instance().resolutionSize().width()/2,    //x0->mi
                 -1*GameSettings::instance().resolutionSize().height()/2,   //y0
                 GameSettings::instance().resolutionSize().width(),         //w0
                 GameSettings::instance().resolutionSize().height());       //h0
#ifndef QT_NO_DEBUG
    for(int row = 0; row < GameSettings::instance().proportionSize().height(); ++row)
    {
        QGraphicsLineItem* line = addLine(-1*GameSettings::instance().resolutionSize().width()/2,
                -1*GameSettings::instance().resolutionSize().height()/2 + row*GameSettings::instance().unitSize().height(), // (x0, y0)
                GameSettings::instance().resolutionSize().width()/2,
                -1*GameSettings::instance().resolutionSize().height()/2 + row*GameSettings::instance().unitSize().height(),    // (x1,y1)
                QPen(QColor(Qt::blue)));                                    // color
        qDebug() << "row: " << row;
        GameSettings::instance().debugGraphicsLineItem(line);

    }
    for(int column = 0; column < GameSettings::instance().proportionSize().width(); ++column)
    {
        QGraphicsLineItem* line = addLine(-1*GameSettings::instance().resolutionSize().width()/2 + column*GameSettings::instance().unitSize().width(),
                -1*GameSettings::instance().resolutionSize().height()/2,
                -1*GameSettings::instance().resolutionSize().width()/2 + column*GameSettings::instance().unitSize().width(),
                1*GameSettings::instance().resolutionSize().height()/2,
                QPen(QColor(Qt::blue)));
        qDebug() << "column: " << column;
        GameSettings::instance().debugGraphicsLineItem(line);
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
