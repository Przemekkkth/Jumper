#ifndef MENUSCENE_H
#define MENUSCENE_H

#include <QGraphicsScene>
#include "button.h"
#include "mainscene.h"

class QGraphicsPixmapItem;
class GameText;
class MenuScene : public MainScene
{
    Q_OBJECT
public:
    explicit MenuScene(QObject *parent = nullptr);
signals:
    void startButtonClicked();
    void optionsButtonClicked();
    void quitButtonClicked();
public slots:

private:
    Button* mStartButton, *mOptionButton, *mQuitButton;
    GameText* mTitle;
    QGraphicsPixmapItem* mBackgroundPixmapItem;
    //Scene *mScene;

    void createConnections();
protected:
    virtual void keyPressEvent(QKeyEvent *event) override;

    // QGraphicsScene interface
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // MENUSCENE_H
