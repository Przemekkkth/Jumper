#include "cactus.h"
#include "gamesettings.h"

QString Cactus::sPathFile = ":/environment/images/environment/cactus1.png";

Cactus::Cactus()
{
    setPixmap(QPixmap(sPathFile).scaled(int(boundingRect().width()), int(boundingRect().height())));
    mX_MovementAnim = new QPropertyAnimation(this, "x", this);
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

void Cactus::setX(qreal x)
{
    m_x = x;
}
