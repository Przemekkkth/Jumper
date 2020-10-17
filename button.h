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
    void setRect(QRectF newRect);
signals:
    void buttonClicked();
public slots:

private:
    GameText* mText;
    QPixmap mPixmap;
    static const QString sImageFilePath;

    bool mCreated;
protected:
    QRectF mRect;
public:
    virtual QRectF boundingRect() const override;
protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // BUTTON_H
