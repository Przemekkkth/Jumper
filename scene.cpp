#include "scene.h"
#include "gamesettings.h"
#include "player.h"
#include <QKeyEvent>
#include <QApplication>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QGraphicsLineItem>
#include <QGraphicsSimpleTextItem>

Scene::Scene(QObject *parent) : QGraphicsScene (parent)
{
    int w_Resolution = GameSettings::instance().resolutionSize().width();
    int h_Resolution = GameSettings::instance().resolutionSize().height();
    int w_Proportion = GameSettings::instance().proportionSize().width();
    int h_Proportion = GameSettings::instance().proportionSize().height();
    qreal w_Unit = GameSettings::instance().unitSize().width();
    qreal h_Unit = GameSettings::instance().unitSize().height();
    setSceneRect(-1*w_Resolution/2,    //x0->mi
                 -1*h_Resolution/2,   //y0
                 w_Resolution,         //w0
                 h_Resolution);       //h0
#ifndef QT_NO_DEBUG
    for(int row = 0; row < h_Proportion; ++row)
    {
        QGraphicsLineItem* line = addLine(-1*w_Resolution/2,
                -1*h_Resolution/2 + row*h_Unit, // (x0, y0)
                w_Resolution/2,
                -1*h_Resolution/2 + row*h_Unit,    // (x1,y1)
                QPen(QColor(Qt::blue)));                                    // color
        qDebug() << "row: " << row;
        GameSettings::instance().debugGraphicsLineItem(line);

    }
    for(int column = 0; column < w_Proportion; ++column)
    {
        QGraphicsLineItem* line = addLine(-1*w_Resolution/2 + column*w_Unit,
                -1*h_Resolution/2,
                -1*w_Resolution/2 + column*w_Unit,
                1*h_Resolution/2,
                QPen(QColor(Qt::blue)));
        qDebug() << "column: " << column;
        GameSettings::instance().debugGraphicsLineItem(line);
    }
    addLine(0, -1*h_Resolution/2, // (x0, y0)
            0, h_Resolution/2,    // (x1,y1)
            QPen(QColor(Qt::red) ));                                    // color

    addLine(-1*w_Resolution/2, 0, // (x0, y0)
            w_Resolution/2, 0,    // (x1,y1)
            QPen(QColor(Qt::red)));                                    // color
    for (int r = 0; r < h_Proportion; ++r) {
        for (int c = 0; c < w_Proportion; ++c) {
            QGraphicsSimpleTextItem * text = addSimpleText(QString::number(r * w_Proportion + c));
            text->setPos(QPointF(-w_Resolution/2 + c*w_Unit + w_Unit/2, -h_Resolution/2 + r*h_Unit + h_Unit/2));
        }
    }
#endif
}

void Scene::init()
{
    mPlayer = new Player(":/img_x2/images/hero/hero_2/hero1.png");
    mPlayer->setPos(0,0);
    addItem(mPlayer);
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
