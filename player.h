#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>

class QTimer;
class Player : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(qreal y READ y WRITE setY)
public:
    explicit Player(QString pathFile);
    static int frames();
    bool isJumping() const;
    void jump();
    void fall();
    qreal y() const;
    void freeze();
    void unFreeze();
signals:

public slots:
    void updatePixmap();
    void setY(qreal y);
private:
    int m_frame;
    static const int m_countFrames;
    QString m_pathFile;
    QString m_fileName;
    QTimer* m_timer;
    bool mIsJumping;
    QPixmap mJumpPixmap;
    QPropertyAnimation *mJumpUpAnim, *mJumpDownAnim;
    qreal m_y;
    // QGraphicsItem interface
public:
    virtual QRectF boundingRect() const override;
};

#endif // PLAYER_H
