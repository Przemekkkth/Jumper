#ifndef ARROW_H
#define ARROW_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>

class Arrow :  public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x WRITE setX)
public:
    Arrow( int TIME = TIME_OF_THE_ROAD);
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
    bool mPastPlayer;
    static const int SCORE_POINTS;
signals:
    void collidedWithPlayer();
};

#endif // ARROW_H
