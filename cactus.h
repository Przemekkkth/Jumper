#ifndef CACTUS_H
#define CACTUS_H

#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>

class Cactus : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x WRITE setX)
public:
    Cactus();
    static QString sPathFile;
    virtual QRectF boundingRect() const override;
    qreal x() const;
    qreal height();
    QPropertyAnimation* xMovementAnim() const;
public slots:
    void setX(qreal x);
private:
    static const int TIME_OF_THE_ROAD;

    bool collideWithPlayer();

    QPropertyAnimation* mX_MovementAnim;
    qreal m_x;
    int m_xRandomizer;

signals:
    void collidedWithPlayer();
};

#endif // CACTUS_H
