#ifndef GROUND_H
#define GROUND_H
#include <QGraphicsPixmapItem>
#include <QPixmap>

class Ground : public QGraphicsPixmapItem
{
public:
    Ground();

    // QGraphicsItem interface
public:
    virtual QRectF boundingRect() const override;
private:
    static QVector<QString> sPathFiles;
};

#endif // GROUND_H
