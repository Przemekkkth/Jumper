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
    GameText* mAudioSliderText, *mSFXSliderText;
    QGraphicsProxyWidget *mAudioCheckBox, *mSFXCheckBox;
};

#endif // OPTIONSSCENE_H
