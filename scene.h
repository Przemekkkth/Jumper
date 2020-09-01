#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
class Player;
class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(QObject *parent = nullptr);
    void init();

signals:
    void setCenterOn(const QPointF pos);
public slots:

    // QGraphicsScene interface
protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void wheelEvent(QGraphicsSceneWheelEvent *event) override;
private:
    Player* mPlayer;
};

#endif // SCENE_H
