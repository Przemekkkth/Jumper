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
};

#endif // MENUSCENE_H
