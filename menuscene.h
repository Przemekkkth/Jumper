#ifndef MENUSCENE_H
#define MENUSCENE_H

#include <QGraphicsScene>
#include "button.h"
class QGraphicsPixmapItem;
class GameText;
class MenuScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit MenuScene(QObject *parent = nullptr);
    void debug();
signals:

public slots:

private:
    int w_Resolution;
    int h_Resolution;
    int w_Proportion;
    int h_Proportion;
    qreal w_Unit;
    qreal h_Unit;
    Button* mStartButton, *mOptionButton, *mQuitButton;
    GameText* mTitle;
    QGraphicsPixmapItem* mBackgroundPixmapItem;
protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
};

#endif // MENUSCENE_H
