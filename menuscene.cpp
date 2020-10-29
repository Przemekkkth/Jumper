#include "menuscene.h"
#include "gamesettings.h"
#include "button.h"
#include "gametext.h"
#include <QDebug>
#include <QKeyEvent>
#include <QApplication>
#include <QGraphicsPixmapItem>
#include <QFontMetrics>

MenuScene::MenuScene(QObject *parent) : MainScene(parent)
{
    mBackgroundPixmapItem = new QGraphicsPixmapItem();
    mBackgroundPixmapItem->setPixmap(QPixmap(":/gui/gui/bg.png").scaled(w_Resolution, h_Resolution));
    addItem(mBackgroundPixmapItem);
    mBackgroundPixmapItem->setPos(QPointF(x0, y0));

    mTitle = new GameText("Jumper");
    mTitle->setPen(QPen(QColor(Qt::red)));
    mTitle->setBrush( QBrush(QColor(252, 132, 3)));
    QFont titleFont = mTitle->font();
    titleFont.setPixelSize(int(1.5*h_Unit));
    mTitle->setFont(titleFont);
    addItem(mTitle);
    QFontMetrics titleFontMetrics(titleFont);
    qreal titleWidth = titleFontMetrics.horizontalAdvance(mTitle->text(), mTitle->text().length());
    mTitle->setPos( QPointF(-titleWidth/2, y0 + 1*h_Unit) );

    mStartButton = new Button("START");
    mStartButton->setPos(QPointF(x0 + (w_Proportion/2 - 3)*w_Unit, y0 + 3*h_Unit + 0.5*h_Unit) );
    addItem(mStartButton);
    mOptionButton = new Button("OPTION");
    mOptionButton->setPos(QPointF(x0 + (w_Proportion/2 - 3)*w_Unit, y0 + 5*h_Unit+0.5*h_Unit));
    addItem(mOptionButton);
    mQuitButton = new Button("QUIT");
    mQuitButton->setPos(QPointF(x0 + ( w_Proportion/2 - 3)*w_Unit, y0 + 7*h_Unit + 0.5*h_Unit));
    addItem(mQuitButton);
    createConnections();
}

void MenuScene::createConnections()
{
    connect(mStartButton, &Button::buttonClicked, [this](){
        emit startButtonClicked();
    });
    connect(mOptionButton, &Button::buttonClicked, [this](){
        emit optionsButtonClicked();
    });
    connect(mQuitButton, &Button::buttonClicked, [this](){
        emit quitButtonClicked();
    });
}

void MenuScene::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape)
    {
        QApplication::instance()->quit();
    }
}

void MenuScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "MenuScene";
    MainScene::mousePressEvent(event);
}
