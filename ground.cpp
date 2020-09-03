#include "ground.h"
#include "gamesettings.h"
#include <QRandomGenerator>

QVector<QString> Ground::sPathFiles{
    ":/environment/images/environment/grass1.png",
    ":/environment/images/environment/grass2.png",
    ":/environment/images/environment/grass2.png"
};

Ground::Ground()
{
    QRandomGenerator random;
    quint32 randomValue = random.bounded(quint32(sPathFiles.size()));
    setPixmap(QPixmap(sPathFiles[int(randomValue)])
              .scaled(int(boundingRect().width()), int(boundingRect().height())));
}


QRectF Ground::boundingRect() const
{
    int width = int(GameSettings::instance().unitSize().width());
    if( GameSettings::instance().unitSize().width() > width )
    {
        width += 1;
    }
    int height = int(GameSettings::instance().unitSize().width());
    if( GameSettings::instance().unitSize().width() > width )
    {
        height += 1;
    }
    return QRectF(0,0, width, height);
}
