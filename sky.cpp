#include "sky.h"
#include "gamesettings.h"

QString Sky::sPathFile{":/environment/images/environment/sky.png"};

Sky::Sky()
{
    setPixmap(QPixmap(sPathFile).scaled(int(boundingRect().width()), int(boundingRect().height())));
}


QRectF Sky::boundingRect() const
{
    qreal x0 = 0;
    qreal y0 = 0;
    qreal w0 = GameSettings::instance().unitSize().width() * GameSettings::instance().proportionSize().width() + 1;
    qreal h0 = GameSettings::instance().unitSize().height() * (GameSettings::instance().proportionSize().height() - 1) + 1;
    return QRectF(x0, y0, w0, h0);
}
