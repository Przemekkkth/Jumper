#ifndef SKY_H
#define SKY_H
#include <QGraphicsPixmapItem>
#include <QPixmap>

class Sky : public QGraphicsPixmapItem
{
public:
    Sky();
    static QString sPathFile;
    // QGraphicsItem interface
public:
    virtual QRectF boundingRect() const override;
private:
    QPixmap mPixmap;

};

#endif // SKY_H
