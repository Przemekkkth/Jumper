#ifndef MENUSCENE_H
#define MENUSCENE_H

#include <QObject>

class MenuScene : public QObject
{
    Q_OBJECT
public:
    explicit MenuScene(QObject *parent = nullptr);

signals:

public slots:

private:
    int w_Resolution;
    int h_Resolution;
    int w_Proportion;
    int h_Proportion;
    qreal w_Unit;
    qreal h_Unit;
};

#endif // MENUSCENE_H
