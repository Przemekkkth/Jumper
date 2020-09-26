#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(QObject *parent = nullptr);
    virtual void debug();
signals:

public slots:

protected:
    int w_Resolution;
    int h_Resolution;
    int w_Proportion;
    int h_Proportion;
    qreal w_Unit;
    qreal h_Unit;
    qreal x0, y0;
};

#endif // SCENE_H
