#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QGraphicsPixmapItem>

class QTimer;
class Player : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Player(QString pathFile);
    static int frames();
signals:

public slots:
    void updatePixmap();
private:
    int m_frame;
    static const int m_countFrames;
    QString m_pathFile;
    QString m_fileName;
    QTimer* m_timer;
};

#endif // PLAYER_H
