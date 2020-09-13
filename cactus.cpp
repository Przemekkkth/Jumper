#include "cactus.h"
#include "gamesettings.h"
#include "player.h"

#include <QRandomGenerator>
#include <QGraphicsScene>
#include <QDebug>

QString Cactus::sPathFile = ":/environment/images/environment/cactus1.png";
const int Cactus::TIME_OF_THE_ROAD = 2000;
Cactus::Cactus()
{
    setPixmap(QPixmap(sPathFile).scaled(int(boundingRect().width()), int(boundingRect().height())));
    m_xRandomizer = QRandomGenerator::global()->bounded(int(3*GameSettings::instance().unitSize().width()));
    mX_MovementAnim = new QPropertyAnimation(this, "x", this);
    setPos(QPointF(GameSettings::instance().resolutionSize().width()/2 + m_xRandomizer,
                   GameSettings::instance().resolutionSize().height()/2 - GameSettings::instance().unitSize().height() - height()));
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
}

QRectF Cactus::boundingRect() const
{
    return QRectF(0,0, 0.75*GameSettings::instance().unitSize().width(), 0.75*GameSettings::instance().unitSize().height());
}

qreal Cactus::x() const
{
    return  m_x;
}

qreal Cactus::height()
{
    return boundingRect().height();
}

QPropertyAnimation *Cactus::xMovementAnim() const
{
    return mX_MovementAnim;
}

void Cactus::setX(qreal x)
{
    qreal yPos = y();
    m_x = x;
    if(collideWithPlayer())
    {
        emit collidedWithPlayer();
    }
    setPos(QPointF(0,0) + QPointF(m_x, yPos));
}

bool Cactus::collideWithPlayer()
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
