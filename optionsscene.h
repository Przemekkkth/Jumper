#ifndef OPTIONSSCENE_H
#define OPTIONSSCENE_H
#include "mainscene.h"
#include "gametext.h"
#include <QGraphicsProxyWidget>


class OptionsScene : public MainScene
{
public:
    OptionsScene(QObject* parent = nullptr);
private:
    GameText* mTitle;
    QGraphicsProxyWidget *mAudioSlider, *mSFXSlider;
    GameText* mAudioSliderText, *mSFXSliderText, *mAudioSliderValue, *mSFXSliderValue;
    QGraphicsProxyWidget *mAudioCheckBox, *mSFXCheckBox;
    QGraphicsPixmapItem* mBackgroundPixmapItem;
    // QGraphicsScene interface
protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
public slots:
    void setAudioSliderValue(int value);
    void setSFXSliderValue(int value);
};

#endif // OPTIONSSCENE_H
