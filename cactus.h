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
public slots:
    void setX(qreal x);
private:
    QPropertyAnimation* mX_MovementAnim;
    qreal m_x;
};

#endif // CACTUS_H
