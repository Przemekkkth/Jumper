#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
class Player;
class Ground;
class Sky;
class GameText;
class GameScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GameScene(QObject *parent = nullptr);
    virtual ~GameScene() override;
    void createEnvironment();
    void createPlayer();
    void createUI();
    void debug();
    void addScore(int points);
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
    GameText *mPauseText, *mStopText, *mScoreText;
    int mScore;
};

#endif // SCENE_H
