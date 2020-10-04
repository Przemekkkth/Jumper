#include "gamescene.h"
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

const int GameScene::CACTUST_SPAWN_TIMER = 1000;

GameScene::GameScene(QObject *parent) : MainScene (parent)
{
    mPaused = false;
    mScore = 0;
    mCactusTimer = new QTimer(this);
    connect(mCactusTimer, &QTimer::timeout, this, &GameScene::setUpCactusSpawner);
    mCactusTimer->start(CACTUST_SPAWN_TIMER);
    createEnvironment();
    createPlayer();
    createUI();
    GameSettings::instance().setGameState(GameSettings::State::Stopped);
    stopGame();
}

GameScene::~GameScene()
{

}

void GameScene::createEnvironment()
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
        mGrounds[i]->setPos(QPointF(x0 + i*w_Unit - w_Unit, -y0 - h_Unit));
    }

    //init sky
    mSky = new Sky();
    addItem(mSky);
    mSky->setPos(QPointF(x0, y0));
}

void GameScene::createPlayer()
{
    mPlayer = new Player(":/img_x2/images/hero/hero_2/hero1.png");
    mPlayer->setPos( GameSettings::instance().sDefaultPlayerPosition );
    addItem(mPlayer);
}

void GameScene::createUI()
{
    mPauseText = new GameText("Press P to resume");
    addItem(mPauseText);
    mPauseText->setPos(QPointF(x0 + w_Unit*(w_Proportion/2) - 3*w_Unit, y0 + h_Unit));
    mPauseText->hide();

    mStopText = new GameText("Press R to start");
    addItem(mStopText);
    mStopText->setPos(QPointF(x0 + w_Unit*(w_Proportion/2) - 3*w_Unit, y0 + h_Unit));
    mStopText->hide();

    mScoreText = new GameText("0");
    mScoreText->setBrush(QBrush( QColor(Qt::blue) ) );
    mScoreText->setPos( QPointF( x0 - 5*w_Unit, y0 + h_Unit) );
    addItem(mScoreText);
}

void GameScene::stopGame()
{
    this->mPlayer->freeze();
    this->mCactusTimer->stop();
    this->pauseCacti();
    this->mStopText->show();
}

void GameScene::setUpCactusSpawner()
{
    Cactus* cactus = new Cactus();
    connect(cactus, &Cactus::collidedWithPlayer, [this](){
        GameSettings::instance().setGameState(GameSettings::State::Stopped);
        GameSettings::instance().playPlayerDeathSFX();
        stopGame();
    });
    addItem(cactus);
}

void GameScene::pauseGame()
{
    mCactusTimer->stop();
    mPlayer->freeze();
    mPauseText->show();
    pauseCacti();
}

void GameScene::resumeGame()
{
    resumeCacti();
    mCactusTimer->start();
    mPlayer->unFreeze();
    mPauseText->hide();
}

void GameScene::restartGame()
{
    removeCacti();
    mCactusTimer->start();
    mPlayer->reset();
    mStopText->hide();
    mScoreText->setText("0");
    mScore = 0;
}

void GameScene::pauseCacti()
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

void GameScene::resumeCacti()
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

void GameScene::removeCacti()
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

void GameScene::addScore(int points)
{
    mScore += points;
    mScoreText->setText(QString::number(mScore));
}

void GameScene::keyPressEvent(QKeyEvent *event)
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
                GameSettings::instance().playPlayerJumpSFX();
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
    else if( event->key() == Qt::Key_Backspace)
    {
            GameSettings::setGameState(GameSettings::State::Stopped);
            pauseGame();
    }
    else
    {
         QGraphicsScene::keyPressEvent(event);
    }
}

void GameScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        qDebug() << "Mouse clicked at " << event->scenePos();
    }
}

void GameScene::wheelEvent(QGraphicsSceneWheelEvent *event)
{
    qDebug() << "void Scene::wheelEvent(QWheelEvent *event)";
    emit setCenterOn(QPointF(0,0));
}
