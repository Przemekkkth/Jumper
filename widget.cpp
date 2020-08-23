#include "widget.h"
#include "ui_widget.h"
#include "player.h"
#include "gamesettings.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    m_scene = new QGraphicsScene(this);
    m_scene->setSceneRect(-200, -200, 400, 400);
    Player* player = new Player(QString(":/img_x2/images/hero/hero_2/hero1.png"));
    m_scene->addItem(player);
    m_scene->addLine(0, -200, 0, 200, QPen(QColor(Qt::red)));
    m_scene->addLine(0, 0, 500, 0, QPen(QColor(Qt::red)));

    m_view = new QGraphicsView(this);
    m_view->setScene(m_scene);
    ui->verticalLayout->addWidget(m_view);
    GameSettings::instance().debug();
}

Widget::~Widget()
{
    delete ui;
}
