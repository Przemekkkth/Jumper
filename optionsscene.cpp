#include "optionsscene.h"
#include "gamesettings.h"
#include <QCheckBox>
#include <QSlider>
#include <QKeyEvent>
#include <QApplication>
#include <QMediaPlayer>

OptionsScene::OptionsScene(QObject *parent) : MainScene (parent)
{

    mBackgroundPixmapItem = new QGraphicsPixmapItem();
    mBackgroundPixmapItem->setPixmap(QPixmap(":/gui/gui/bg.png").scaled(w_Resolution, h_Resolution));
    addItem(mBackgroundPixmapItem);
    mBackgroundPixmapItem->setPos(QPointF(x0, y0));

    mTitle = new GameText("Options");
    mTitle->setPen(QPen(QColor(Qt::blue)));
    mTitle->setBrush( QBrush(QColor(252, 100, 3)));
    QFont titleFont = mTitle->font();
    titleFont.setPixelSize(int(1.2*h_Unit));
    mTitle->setFont(titleFont);
    addItem(mTitle);
    QFontMetrics titleFontMetrics(titleFont);
    qreal titleWidth = titleFontMetrics.horizontalAdvance(mTitle->text(), mTitle->text().length());
    mTitle->setPos( QPointF(-titleWidth/2, y0 + 1*h_Unit) );

    mAudioSlider = new QGraphicsProxyWidget();
    QSlider* audioSlider = new QSlider(Qt::Horizontal);
    //audioSlider->setStyleSheet("QSlider::handle:horizontal{ width: 32px; height: 32px;}");
    //:/gui/gui/bg.png      qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #b4b4b4, stop:1 #8f8f8f);
    audioSlider->setStyleSheet(GameSettings::sSliderStyleSheet);
    audioSlider->setRange(0, 100);
    audioSlider->setGeometry(0, 0, 3*int(w_Unit), int(h_Unit)/2);
    connect(audioSlider, &QSlider::valueChanged, this, &OptionsScene::setAudioSliderValue);
    mAudioSlider->resize(QSizeF(3*w_Unit, h_Unit/2));
    mAudioSlider->setWidget(audioSlider);
    addItem(mAudioSlider);
    mAudioSlider->setPos(QPointF(x0 + 7*w_Unit, y0 + 3*h_Unit - h_Unit/8));

    mSFXSlider = new QGraphicsProxyWidget();
    QSlider* sfxSlider = new QSlider(Qt::Horizontal);
    sfxSlider->setStyleSheet(GameSettings::sSliderStyleSheet);
    sfxSlider->setRange(0, 100);
    sfxSlider->setGeometry(0, 0, 3*int(w_Unit), int(h_Unit)/2);
    connect(sfxSlider, &QSlider::valueChanged, this, &OptionsScene::setSFXSliderValue);
    mSFXSlider->resize(QSizeF(3*w_Unit, h_Unit));
    mSFXSlider->setWidget(sfxSlider);
    addItem(mSFXSlider);
    mSFXSlider->setPos(QPointF(x0 + 7*w_Unit, y0 + 4*h_Unit - h_Unit/8));

    mAudioSliderText = new GameText("Audio Volume");
    addItem(mAudioSliderText);
    mAudioSliderText->setPos(QPointF(x0 + 2*w_Unit, y0 + 3*h_Unit));
    mAudioSliderValue = new GameText("100%");
    addItem(mAudioSliderValue);
    mAudioSliderValue->setPos(QPointF(x0 + 10*w_Unit, y0 + 3*h_Unit));

    mSFXSliderText  = new GameText("SFX Volume");
    addItem(mSFXSliderText);
    mSFXSliderText->setPos(QPointF(x0 + 2*w_Unit, y0 + 4*h_Unit));
    mSFXSliderValue = new GameText("100%");
    addItem(mSFXSliderValue);
    mSFXSliderValue->setPos(QPointF(x0 + 10*w_Unit, y0 + 4*h_Unit));


    mAudioCheckBox = new QGraphicsProxyWidget();
    QCheckBox* audioCheckBox = new QCheckBox("Audio Sound");
    audioCheckBox->setFont(GameSettings::sGameFont);
    audioCheckBox->setGeometry(0, 0, 2*int(w_Unit), int(h_Unit)/2);
    audioCheckBox->setStyleSheet("QCheckBox{background-color: #b5c153;}");
    mAudioCheckBox->setWidget(audioCheckBox);
    addItem(mAudioCheckBox);
    mAudioCheckBox->setPos(QPointF(x0 + 2*w_Unit, y0 + 5*h_Unit - h_Unit/8));

    mSFXCheckBox = new QGraphicsProxyWidget();
    QCheckBox* sfxCheckBox = new QCheckBox("SFX Sound");
    mSFXCheckBox->setWidget(sfxCheckBox);
    sfxCheckBox->setFont(GameSettings::sGameFont);
    addItem(mSFXCheckBox);
    mSFXCheckBox->setPos(QPointF(x0 + 2*w_Unit, y0 + 6*h_Unit - h_Unit/8));

    debug();
}


void OptionsScene::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape)
    {
        QApplication::instance()->quit();
    }
}

void OptionsScene::setAudioSliderValue(int value)
{
    mAudioSliderValue->setText(QString::number(value) + "%");
    GameSettings::sBGAudioMedia->setVolume(value);
}

void OptionsScene::setSFXSliderValue(int value)
{
    mSFXSliderValue->setText(QString::number(value) + "%");

    GameSettings::sJumpPlayerSFXMedia->setVolume(value);
    GameSettings::sDeathPlayerSFXMedia->setVolume(value);
}
