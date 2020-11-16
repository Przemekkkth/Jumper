#include "arrow.h"
#include "gamesettings.h"
#include "gamescene.h"
#include "player.h"

#include <QDebug>
#include <QGraphicsScene>
#include <QRandomGenerator>

QString Arrow::sPathFile = ":/environment/images/arrow/arrow.png";
const int Arrow::TIME_OF_THE_ROAD = 4400;
const int Arrow::SCORE_POINTS = 11;

Arrow::Arrow()
{
    setPixmap(QPixmap(sPathFile).scaled(int(boundingRect().width()), int(boundingRect().height())));
    m_xRandomizer = QRandomGenerator::global()->bounded(int(3*GameSettings::instance().unitSize().width()));
    mX_MovementAnim = new QPropertyAnimation(this, "x", this);
    setPos(QPointF(GameSettings::instance().resolutionSize().width()/2 + m_xRandomizer,
                   GameSettings::instance().resolutionSize().height()/2 - GameSettings::instance().unitSize().height() - height() - GameSettings::instance().unitSize().height())
           );
    mX_MovementAnim->setStartValue(GameSettings::instance().resolutionSize().width()/2 + m_xRandomizer);
    mX_MovementAnim->setEndValue(-GameSettings::instance().resolutionSize().width()/2 - GameSettings::instance().unitSize().width() );
    mX_MovementAnim->setEasingCurve(QEasingCurve::Linear);
    mX_MovementAnim->setDuration(TIME_OF_THE_ROAD);
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
}

QRectF Arrow::boundingRect() const
{
    return QRectF(0,0, 0.5*GameSettings::instance().unitSize().width(), 0.5*GameSettings::instance().unitSize().height());
}

qreal Arrow::x() const
{
    return  m_x;
}

qreal Arrow::height()
{
    return boundingRect().height();
}

QPropertyAnimation *Arrow::xMovementAnim() const
{
    return mX_MovementAnim;
}

void Arrow::setX(qreal x)
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

bool Arrow::collideWithPlayer()
{
    QList<QGraphicsItem*> collidedItems = collidingItems();
    for (int i = 0; i < collidedItems.size(); ++i) {
        Player* player = dynamic_cast<Player*>(collidedItems[i]);
        if(player)
        {
            qDebug() << "Cactus collides with Player";
            return true;
        }
    }
    return false;
}
