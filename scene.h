#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
class Player;
class Ground;
class Sky;
class GameText;
class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(QObject *parent = nullptr);
    void createEnvironment();
    void createPlayer();
    void createUI();
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
    void pauseGame();
    void resumeGame();
    void restartGame();
    void pauseCacti();
    void resumeCacti();
    void removeCacti();

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
    GameText *mPauseText, *mStopText;
};

#endif // SCENE_H
