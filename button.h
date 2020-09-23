#ifndef BUTTON_H
#define BUTTON_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QPixmap>

class GameText;
class Button : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Button(QString text = "");

signals:
    void buttonClicked();
public slots:

private:
    GameText* mText;
    QPixmap mPixmap;
    static const QString sImageFilePath;
    void setRect(QRectF newRect);
    bool mCreated;
protected:
    QRectF mRect;

    // QGraphicsItem interface
public:
    virtual QRectF boundingRect() const override;

    // QGraphicsItem interface
protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // BUTTON_H