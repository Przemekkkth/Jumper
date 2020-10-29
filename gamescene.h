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

    void pauseCacti();
    void resumeCacti();
    void removeCacti();

    static const int CACTUST_SPAWN_TIMER;

    Player* mPlayer;
    QVector<Ground*> mGrounds;
    Sky* mSky;
    QTimer *mCactusTimer;
    bool mPaused;
    GameText *mPauseText, *mStopText, *mScoreText;
    int mScore;

    void stopGame();

    // QGraphicsScene interface
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // SCENE_H
