#ifndef COIN_H
#define COIN_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>

class QTimer;
class Coin : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x WRITE setX)
public:
    static const int SCORE_POINTS;
    Coin(int Time = TIME_OF_THE_ROAD);
    static QString sPathFile;
    virtual QRectF boundingRect() const override;
    qreal x() const;
    qreal height();
    QPropertyAnimation* xMovementAnim() const;
public slots:
    void setX(qreal x);
private slots:
    void updatePixmap();
private:
    static const int TIME_OF_THE_ROAD;

    bool collideWithPlayer();

    QPropertyAnimation* mX_MovementAnim;
    qreal m_x;
    int m_xRandomizer;
    bool mPastPlayer;
    unsigned int mCurrentFrame;
    QTimer* mTimer;

    static QStringList PATH_FILES;
    static int COUNT_OF_FILES;
    static const int sChangeFramesMilliseconds;
signals:
    void collidedWithPlayer();
};

#endif // COIN_H
