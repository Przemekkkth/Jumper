#include "optionsscene.h"
#include "gamesettings.h"
#include <QCheckBox>
#include <QSlider>
#include <QKeyEvent>
#include <QApplication>

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
    mAudioSlider->resize(QSizeF(3*w_Unit, h_Unit/2));
    mAudioSlider->setWidget(audioSlider);
    addItem(mAudioSlider);
    mAudioSlider->setPos(QPointF(x0 + 7*w_Unit, y0 + 3*h_Unit));


    mSFXSlider = new QGraphicsProxyWidget();
    QSlider* sfxSlider = new QSlider(Qt::Horizontal);
    sfxSlider->setStyleSheet(GameSettings::sSliderStyleSheet);
    sfxSlider->setRange(0, 100);
    mSFXSlider->setWidget(sfxSlider);
    addItem(mSFXSlider);

    mAudioSliderText = new GameText("Audio Volume");
    addItem(mAudioSliderText);
    mAudioSliderText->setPos(QPointF(x0 + 2*w_Unit, y0 + 3*h_Unit));
    mSFXSliderText  = new GameText("SFX Volume");
    addItem(mSFXSliderText);
    mSFXSliderText->setPos(QPointF(x0 + 2*w_Unit, y0 + 4*h_Unit));

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


void OptionsScene::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape)
    {
        QApplication::instance()->quit();
    }
}
