#ifndef SCENE_H
#define SCENE_H

#include "mainscene.h"
class Player;
class Ground;
class Sky;
class GameText;

class GameScene : public MainScene
{
    Q_OBJECT
public:
    explicit GameScene(QObject *parent = nullptr);
    virtual ~GameScene() override;
    void createEnvironment();
    void createPlayer();
    void createUI();
    void addScore(int points);
    void restartGame();
signals:
    void setCenterOn(const QPointF pos);
    void goToMenu();
public slots:
    void setUpEntitiesSpawner();
    // QGraphicsScene interface
protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void wheelEvent(QGraphicsSceneWheelEvent *event) override;
private:
    void pauseGame();
    void resumeGame();
    void stopGame();

    void pauseCacti();
    void resumeCacti();
    void removeCacti();

    void pauseCoins();
    void resumeCoins();
    void removeCoins();

    void pauseArrows();
    void resumeArrows();
    void removeArrows();

    static const int CACTUST_SPAWN_TIMER;
    static const int TIME_OF_ENTITY_ROAD;

    Player* mPlayer;
    QVector<Ground*> mGrounds;
    Sky* mSky;
    QTimer *mEntitySpawnTimer;
    bool mPaused;
    GameText *mPauseText, *mStopText, *mScoreText;
    int mScore;
    // QGraphicsScene interface
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // SCENE_H
