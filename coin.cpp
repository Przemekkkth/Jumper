#include "coin.h"
#include "gamesettings.h"
#include "gamescene.h"
#include "player.h"

#include <QRandomGenerator>
#include <QGraphicsScene>
#include <QDebug>
#include <QTimer>

const int Coin::TIME_OF_THE_ROAD = 4000;
const int Coin::SCORE_POINTS = 75;
QStringList Coin::PATH_FILES = {
                                ":/environment/images/coin/coin0.png", ":/environment/images/coin/coin1.png",
                                ":/environment/images/coin/coin2.png", ":/environment/images/coin/coin3.png",
                                ":/environment/images/coin/coin4.png",":/environment/images/coin/coin5.png",
                                ":/environment/images/coin/coin6.png", ":/environment/images/coin/coin7.png"
                               };
int Coin::COUNT_OF_FILES = Coin::PATH_FILES.size();
const int Coin::sChangeFramesMilliseconds = 125;

Coin::Coin(int Time)
{
    mCurrentFrame = 0;
    setPixmap(QPixmap(PATH_FILES[mCurrentFrame]).scaled(int(boundingRect().width()), int(boundingRect().height())));
    m_xRandomizer = QRandomGenerator::global()->bounded(int(3*GameSettings::instance().unitSize().width()));
    mX_MovementAnim = new QPropertyAnimation(this, "x", this);
    setPos(QPointF(GameSettings::instance().resolutionSize().width()/2 + m_xRandomizer,
                   GameSettings::instance().resolutionSize().height()/2 - GameSettings::instance().unitSize().height() - height()));
    mX_MovementAnim->setStartValue(GameSettings::instance().resolutionSize().width()/2 + m_xRandomizer);
    mX_MovementAnim->setEndValue(-GameSettings::instance().resolutionSize().width()/2 - GameSettings::instance().unitSize().width() );
    mX_MovementAnim->setEasingCurve(QEasingCurve::Linear);
    mX_MovementAnim->setDuration(Time);
    mX_MovementAnim->start();
    //delete object
    connect( mX_MovementAnim, &QPropertyAnimation::finished, [this](){
        if(this->scene())
        {
            this->scene()->removeItem(this);
        }
        delete this;
    });
    mPastPlayer = false;

    mTimer = new QTimer(this);
    connect(mTimer, &QTimer::timeout, this, &Coin::updatePixmap);
    mTimer->start(sChangeFramesMilliseconds);
}


QRectF Coin::boundingRect() const
{
    return QRectF(0,0, 32, 32);
}

qreal Coin::x() const
{
    return  m_x;
}

qreal Coin::height()
{
    return boundingRect().height();
}

QPropertyAnimation *Coin::xMovementAnim() const
{
    return mX_MovementAnim;
}

void Coin::setX(qreal x)
{
    qreal yPos = y();
    m_x = x;
    if(collideWithPlayer())
    {
        emit collidedWithPlayer();
    }
    if( !mPastPlayer && pos().x() < GameSettings::instance().sDefaultPlayerPosition.x() )
    {
        mPastPlayer = true;
        GameScene* tmpScene = dynamic_cast<GameScene*>(scene());
        if(tmpScene)
        {
            tmpScene->addScore(SCORE_POINTS);
        }

    }
    setPos(QPointF(0,0) + QPointF(m_x, yPos));
}

void Coin::updatePixmap()
{
    mCurrentFrame++;
    mCurrentFrame %= COUNT_OF_FILES;
    setPixmap( QPixmap( PATH_FILES[mCurrentFrame] ).scaled(int(boundingRect().width()), int(boundingRect().height())) );
}

bool Coin::collideWithPlayer()
{
    QList<QGraphicsItem*> collidedItems = collidingItems();
    for (int i = 0; i < collidedItems.size(); ++i) {
        Player* player = dynamic_cast<Player*>(collidedItems[i]);
        if(player)
        {
            qDebug() << "Coin collides with Player";
            return true;
        }
    }
    return false;
}
