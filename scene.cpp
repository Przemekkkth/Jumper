#include "scene.h"
#include "gamesettings.h"
#include "player.h"
#include "ground.h"
#include "sky.h"
#include "cactus.h"

#include <QKeyEvent>
#include <QApplication>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QGraphicsLineItem>
#include <QGraphicsSimpleTextItem>
#include <QTimer>

Scene::Scene(QObject *parent) : QGraphicsScene (parent)
{
    w_Resolution = GameSettings::instance().resolutionSize().width();
    h_Resolution = GameSettings::instance().resolutionSize().height();
    w_Proportion = GameSettings::instance().proportionSize().width();
    h_Proportion = GameSettings::instance().proportionSize().height();
    w_Unit = GameSettings::instance().unitSize().width();
    h_Unit = GameSettings::instance().unitSize().height();
    setSceneRect(-1*w_Resolution/2,    //x0->mi
                 -1*h_Resolution/2,   //y0
                 w_Resolution,         //w0
                 h_Resolution);       //h0
    mCactusTimer = new QTimer(this);
    connect(mCactusTimer, &QTimer::timeout, this, &Scene::setUpCactusSpawner);
    mCactusTimer->start(1000);
}

void Scene::createEnvironment()
{

    //init ground
    for(int i = 0; i <= GameSettings::instance().proportionSize().width(); ++i)
    {
        mGrounds.push_back(new Ground());
        addItem(mGrounds[i]);
    }
    //set pos for groundTiles
    for(int i = 0; i <= GameSettings::instance().proportionSize().width(); ++i)
    {
        mGrounds[i]->setPos(QPointF(-w_Resolution/2 + i*w_Unit - w_Unit, h_Resolution/2 - h_Unit));
    }

    //init sky
    mSky = new Sky();
    addItem(mSky);
    mSky->setPos(QPointF(-w_Resolution/2, -h_Resolution/2));
    //cactus
    Cactus* cactus = new Cactus();
    cactus->setPos(QPointF(-w_Resolution/2 + 10*w_Unit - w_Unit, h_Resolution/2 - h_Unit - cactus->height()));
    addItem(cactus);
}

void Scene::createPlayer()
{
    mPlayer = new Player(":/img_x2/images/hero/hero_2/hero1.png");
    mPlayer->setPos(-w_Resolution/2+3*w_Unit,h_Resolution/2-2*h_Unit);
    //mPlayer->setPos(0,0);
    addItem(mPlayer);
}

void Scene::debug()
{
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

void Scene::setUpCactusSpawner()
{
    Cactus* catus = new Cactus();
    addItem(catus);
}

void Scene::keyPressEvent(QKeyEvent *event)
{
    qDebug() << "void Scene::keyPressEvent(QKeyEvent *event)";
    if(event->key() == Qt::Key_Escape)
    {
        QApplication::instance()->quit();
    }
    else if(event->key() == Qt::Key_Left || event->key() == Qt::Key_Right || event->key() == Qt::Key_Up || event->key() == Qt::Key_Down)
    {

    }
    else if( event->key() == Qt::Key_Space)
    {
        qDebug() << "jump";
        if(!mPlayer->isJumping())
        {
            mPlayer->jump();
        }
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
