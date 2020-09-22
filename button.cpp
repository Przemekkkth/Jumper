#include "button.h"
#include "gametext.h"
#include "gamesettings.h"
#include <QGraphicsPixmapItem>

const QString Button::sImageFilePath = ":/gui/gui/button.png";

Button::Button(QString text)
{
    mCreated = false;
    setRect( QRectF( QPointF(0,0), 6*QSizeF(GameSettings::instance().unitSize()) ) );
    mPixmap = QPixmap(sImageFilePath);
    setPixmap( mPixmap.scaled(int(mRect.size().width()), int(mRect.size().height())) );
    mText = new GameText(text);
    mText->setParentItem(this);
    mText->setRect(mRect);
    mCreated = true;
}

void Button::setRect(QRectF newRect)
{
    if(mRect == newRect)
    {
        return;
    }
    prepareGeometryChange();
    mRect = newRect;
    if(mCreated)
    {
        setPixmap( mPixmap.scaled(int(mRect.size().width()), int(mRect.size().height())) );
        mText->setRect(mRect);
    }
}

QRectF Button::boundingRect() const
{
    return mRect;
}
