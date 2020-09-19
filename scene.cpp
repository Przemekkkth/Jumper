#include "scene.h"
#include "gamesettings.h"
#include "player.h"
#include "ground.h"
#include "sky.h"
#include "cactus.h"
#include "gametext.h"

#include <QKeyEvent>
#include <QApplication>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QGraphicsLineItem>
#include <QGraphicsSimpleTextItem>
#include <QTimer>

 const int Scene::CACTUST_SPAWN_TIMER = 1000;

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
    mPaused = false;
    mCactusTimer = new QTimer(this);
    connect(mCactusTimer, &QTimer::timeout, this, &Scene::setUpCactusSpawner);
    mCactusTimer->start(CACTUST_SPAWN_TIMER);
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
}

void Scene::createPlayer()
{
    mPlayer = new Player(":/img_x2/images/hero/hero_2/hero1.png");
    mPlayer->setPos( GameSettings::instance().sDefaultPlayerPosition );
    addItem(mPlayer);
}

void Scene::createUI()
{
    mPauseText = new GameText("Press P to resume");
    addItem(mPauseText);
    mPauseText->setPos(QPointF(-w_Resolution/2+w_Unit*(w_Proportion/2)-3*w_Unit, -h_Resolution/2+h_Unit));
    mPauseText->hide();

    mStopText = new GameText("Press R to start");
    addItem(mStopText);
    mStopText->setPos(QPointF(-w_Resolution/2+w_Unit*(w_Proportion/2)-3*w_Unit, -h_Resolution/2+h_Unit));
    mStopText->hide();
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
    Cactus* cactus = new Cactus();
    connect(cactus, &Cactus::collidedWithPlayer, [this](){
        GameSettings::instance().setGameState(GameSettings::State::Stopped);
        this->mPlayer->freeze();
        this->mCactusTimer->stop();
        this->pauseCacti();
        this->mStopText->show();
    });
    addItem(cactus);
}

void Scene::pauseGame()
{
    mCactusTimer->stop();
    mPlayer->freeze();
    mPauseText->show();
    pauseCacti();
}

void Scene::resumeGame()
{
    resumeCacti();
    mCactusTimer->start();
    mPlayer->unFreeze();
    mPauseText->hide();
}

void Scene::restartGame()
{
    removeCacti();
    mCactusTimer->start();
    mPlayer->reset();
    mStopText->hide();
}

void Scene::pauseCacti()
{
    QList<QGraphicsItem*> allItems = items();
    for(int i = 0; i < allItems.size(); ++i)
    {
        Cactus* cactus = dynamic_cast<Cactus*>(allItems[i]);
        if( cactus )
        {
            cactus->xMovementAnim()->pause();
        }
    }
}

void Scene::resumeCacti()
{
    QList<QGraphicsItem*> allItems = items();
    for(int i = 0; i < allItems.size(); ++i)
    {
        Cactus* cactus = dynamic_cast<Cactus*>(allItems[i]);
        if( cactus )
        {
            cactus->xMovementAnim()->resume();
        }
    }
}

void Scene::removeCacti()
{
    QList<QGraphicsItem*> allItems = items();
    for(int i = 0; i < allItems.size(); ++i)
    {
        Cactus* cactus = dynamic_cast<Cactus*>(allItems[i]);
        if( cactus )
        {
            removeItem(cactus);
            delete cactus;
        }
    }
}

void Scene::keyPressEvent(QKeyEvent *event)
{
    if( event->isAutoRepeat() )
    {
        return;
    }
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
        if(GameSettings::GameState() == GameSettings::State::Played )
        {
            if(!mPlayer->isJumping() )
            {
                mPlayer->jump();
            }
        }
    }
    else if( event->key() == Qt::Key_P )
    {
        if( GameSettings::GameState() == GameSettings::State::Played )
        {
            GameSettings::setGameState(GameSettings::State::Paused);
            qDebug() << "paused";
            pauseGame();
        }
        else if(GameSettings::GameState() == GameSettings::State::Paused)
        {
            GameSettings::setGameState(GameSettings::State::Played);
            qDebug() << "played";
            resumeGame();
        }
    }
    else if( event->key() == Qt::Key_R)
    {
        if(GameSettings::GameState() == GameSettings::State::Stopped )
        {
            GameSettings::setGameState(GameSettings::State::Played);
            restartGame();
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
