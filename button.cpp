#include "button.h"
#include "gametext.h"
#include "gamesettings.h"
#include <QGraphicsPixmapItem>
#include <QFontMetrics>

const QString Button::sImageFilePath = ":/gui/gui/button.png";

Button::Button(QString text)
{
    mCreated = false;
    setRect( QRectF( 0, 0, 6*GameSettings::instance().unitSize().width(), GameSettings::instance().unitSize().height() ) );
    mPixmap = QPixmap(sImageFilePath);
    setPixmap( mPixmap.scaled(int(mRect.size().width()), int(mRect.size().height())) );
    mText = new GameText(text);
    mText->setParentItem(this);
    mText->setRect(mRect);
    QFontMetrics fontMetrics(mText->font());
    mText->setPos(QPointF(boundingRect().center())
                  - QPointF( qreal( fontMetrics.horizontalAdvance(mText->text(), mText->text().length())) / 2., fontMetrics.height()/2));
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


void Button::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit buttonClicked();
}
