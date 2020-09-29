#include "optionsscene.h"
#include <QCheckBox>
#include <QSlider>

OptionsScene::OptionsScene(QObject *parent) : MainScene (parent)
{
    mTitle = new GameText("Options");
    addItem(mTitle);

    mAudioSlider = new QGraphicsProxyWidget();
    QSlider* audioSlider = new QSlider();
    mAudioSlider->setWidget(audioSlider);
    addItem(mAudioSlider);

    mSFXSlider = new QGraphicsProxyWidget();
    QSlider* sfxSlider = new QSlider();
    mSFXSlider->setWidget(sfxSlider);
    addItem(mSFXSlider);

    mAudioSliderText = new GameText("Audio Volume");
    addItem(mAudioSliderText);
    mSFXSliderText  = new GameText("SFX Volume");
    addItem(mSFXSliderText);

    mAudioCheckBox = new QGraphicsProxyWidget();
    QCheckBox* audioCheckBox = new QCheckBox("Audio Sound");
    mAudioCheckBox->setWidget(audioCheckBox);
    addItem(mAudioCheckBox);
    mSFXCheckBox = new QGraphicsProxyWidget();
    QCheckBox* sfxCheckBox = new QCheckBox("SFX Sound");
    mAudioCheckBox->setWidget(sfxCheckBox);
    addItem(mAudioCheckBox);


    debug();
}
