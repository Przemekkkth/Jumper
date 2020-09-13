#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
class Player;
class Ground;
class Sky;

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(QObject *parent = nullptr);
    void createEnvironment();
    void createPlayer();
    void debug();
signals:
    void setCenterOn(const QPointF pos);
public slots:
    void setUpCactusSpawner();
    // QGraphicsScene interface
protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void wheelEvent(QGraphicsSceneWheelEvent *event) override;
private:
    static const int CACTUST_SPAWN_TIMER;

    Player* mPlayer;
    QVector<Ground*> mGrounds;
    Sky* mSky;
    int w_Resolution;
    int h_Resolution;
    int w_Proportion;
    int h_Proportion;
    qreal w_Unit;
    qreal h_Unit;
    QTimer *mCactusTimer;
    bool mPaused;
    void pauseGame();
    void resumeGame();
};

#endif // SCENE_H
