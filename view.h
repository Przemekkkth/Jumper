#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsView>

class View : public QGraphicsView
{
    Q_OBJECT
public:
    explicit View(QWidget *parent = nullptr);

signals:

public slots:

    // QWidget interface
protected:
    virtual void wheelEvent(QWheelEvent *event) override;

    // QAbstractScrollArea interface
protected:
    virtual void scrollContentsBy(int dx, int dy) override;
    virtual void keyPressEvent(QKeyEvent *event) override;
};

#endif // VIEW_H
