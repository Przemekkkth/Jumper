#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(QObject *parent = nullptr);

signals:
    void setCenterOn(const QPointF pos);
public slots:

    // QGraphicsScene interface
protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    // QGraphicsScene interface
protected:
    virtual void wheelEvent(QGraphicsSceneWheelEvent *event) override;
};

#endif // SCENE_H
