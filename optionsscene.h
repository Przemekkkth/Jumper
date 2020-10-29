#ifndef OPTIONSSCENE_H
#define OPTIONSSCENE_H
#include "mainscene.h"
#include "gametext.h"
#include <QGraphicsProxyWidget>

class Button;

class OptionsScene : public MainScene
{
    Q_OBJECT
public:
    OptionsScene(QObject* parent = nullptr);
private:
    GameText* mTitle;
    QGraphicsProxyWidget *mAudioSlider, *mSFXSlider;
    GameText* mAudioSliderText, *mSFXSliderText, *mAudioSliderValue, *mSFXSliderValue;
    QGraphicsProxyWidget *mAudioCheckBox, *mSFXCheckBox;
    QGraphicsPixmapItem* mBackgroundPixmapItem;
    Button* mDefaultButton, *mBackButton;
protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
public slots:
    void setAudioSliderValue(int value);
    void setSFXSliderValue(int value);
    void setAudioCheckBox(bool on);
    void setSFXCheckBox(bool on);
    void setDefaultSettings();
signals:
    void backActionActivated();

    // QGraphicsScene interface
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // OPTIONSSCENE_H
