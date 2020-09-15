#ifndef GAMETEXT_H
#define GAMETEXT_H
#include <QGraphicsSimpleTextItem>

class GameText : public QGraphicsSimpleTextItem
{
public:
    GameText( QString text );
    void setRect(QRectF newRect);
protected:
    QRectF mRect;

    // QGraphicsItem interface
public:
    virtual QRectF boundingRect() const override;
};

#endif // GAMETEXT_H
