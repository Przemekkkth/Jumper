#include "menuscene.h"
#include "gamesettings.h"
#include "button.h"
#include "gametext.h"
#include <QDebug>
#include <QKeyEvent>
#include <QApplication>

MenuScene::MenuScene(QObject *parent) : QGraphicsScene(parent)
{
    w_Resolution = GameSettings::instance().resolutionSize().width();
    h_Resolution = GameSettings::instance().resolutionSize().height();
    w_Proportion = GameSettings::instance().proportionSize().width();
    h_Proportion = GameSettings::instance().proportionSize().height();
    w_Unit = GameSettings::instance().unitSize().width();
    h_Unit = GameSettings::instance().unitSize().height();
    setSceneRect(-1*w_Resolution/2,    //x0->mi
                 -1*h_Resolution/2,   //y0
                 w_Resolution,         //w0
                 h_Resolution);       //h0

    mTitle = new GameText("Jumper");
    mTitle->setPen(QPen(QColor(Qt::red)));
    mTitle->setBrush( QBrush(QColor(252, 132, 3)));
    addItem(mTitle);
    mTitle->setPos( QPointF(-w_Resolution/2+( w_Proportion/2 - 3)*w_Unit, -h_Resolution/2+2*h_Unit) );

    mStartButton = new Button("START");
    mStartButton->setPos(QPointF(-w_Resolution/2+( w_Proportion/2 - 3)*w_Unit, -h_Resolution/2+3*h_Unit) );
    addItem(mStartButton);
    mOptionButton = new Button("OPTION");
    mOptionButton->setPos(QPointF(-w_Resolution/2+( w_Proportion/2 - 3)*w_Unit, -h_Resolution/2+5*h_Unit));
    addItem(mOptionButton);
    mQuitButton = new Button("QUIT");
    mQuitButton->setPos(QPointF(-w_Resolution/2+( w_Proportion/2 - 3)*w_Unit, -h_Resolution/2+7*h_Unit));
    addItem(mQuitButton);
}

void MenuScene::debug()
{
#ifndef QT_NO_DEBUG
    for(int row = 0; row < h_Proportion; ++row)
    {
        QGraphicsLineItem* line = addLine(-1*w_Resolution/2,
                -1*h_Resolution/2 + row*h_Unit, // (x0, y0)
                w_Resolution/2,
                -1*h_Resolution/2 + row*h_Unit,    // (x1,y1)
                QPen(QColor(Qt::blue)));                                    // color
        qDebug() << "row: " << row;
        GameSettings::instance().debugGraphicsLineItem(line);

    }
    for(int column = 0; column < w_Proportion; ++column)
    {
        QGraphicsLineItem* line = addLine(-1*w_Resolution/2 + column*w_Unit,
                -1*h_Resolution/2,
                -1*w_Resolution/2 + column*w_Unit,
                1*h_Resolution/2,
                QPen(QColor(Qt::blue)));
        qDebug() << "column: " << column;
        GameSettings::instance().debugGraphicsLineItem(line);
    }
    addLine(0, -1*h_Resolution/2, // (x0, y0)
            0, h_Resolution/2,    // (x1,y1)
            QPen(QColor(Qt::red) ));                                    // color

    addLine(-1*w_Resolution/2, 0, // (x0, y0)
            w_Resolution/2, 0,    // (x1,y1)
            QPen(QColor(Qt::red)));                                    // color
    for (int r = 0; r < h_Proportion; ++r) {
        for (int c = 0; c < w_Proportion; ++c) {
            QGraphicsSimpleTextItem * text = addSimpleText(QString::number(r * w_Proportion + c));
            text->setPos(QPointF(-w_Resolution/2 + c*w_Unit + w_Unit/2, -h_Resolution/2 + r*h_Unit + h_Unit/2));
        }
    }
#endif
}


void MenuScene::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape)
    {
        QApplication::instance()->quit();
    }
}
