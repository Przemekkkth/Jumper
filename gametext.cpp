#include "gametext.h"
#include "gamesettings.h"
#include <QBrush>
#include <QPen>

GameText::GameText(QString text)
{
    setFont(GameSettings::instance().sGameFont);
    setText(text);
    setRect( QRectF( QPointF(0,0), 6*QSizeF(GameSettings::instance().unitSize()) ) );
    setBrush(QBrush(QColor(Qt::yellow)));
    setPen(QPen(QColor(Qt::red)) );
}

void GameText::setRect(QRectF newRect)
{
    if(mRect == newRect)
    {
        return;
    }
    prepareGeometryChange();
    mRect = newRect;
}

QRectF GameText::boundingRect() const
{
    return mRect;
}
