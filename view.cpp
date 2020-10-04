#include "view.h"
#include <QDebug>
#include <QKeyEvent>

View::View(QWidget *parent) : QGraphicsView (parent)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //setStyleSheet("QSlider::handle:vertical { height: 10px; background: green;  margin: 0 -4px; /* expand outside the groove */}");
}

void View::wheelEvent(QWheelEvent *event)
{
    qDebug() << "void View::wheelEvent(QWheelEvent *event)";
}

void View::scrollContentsBy(int dx, int dy)
{

}

void View::keyPressEvent(QKeyEvent *event)
{
    qDebug() << "void View::keyPressEvent(QKeyEvent *event)";
    if(event->key() == Qt::Key_P)
    {
        centerOn(0,0);
    }
    QGraphicsView::keyPressEvent(event);
}
