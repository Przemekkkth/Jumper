#include "player.h"
#include "gamesettings.h"
#include <QFileInfo>
#include <QDebug>
#include <QTimer>
#include <QDir>

const int Player::m_countFrames = 3;

Player::Player(QString pathFile)
{
    setPixmap(QPixmap(pathFile).scaled(int(boundingRect().width()), int(boundingRect().height()) ) );
    m_pathFile = QFileInfo(pathFile).path();
    m_fileName = QFileInfo(pathFile).fileName();
    //find frame number ex. hero0.png
    for(int i = 0; i < m_fileName.length(); ++i)
    {
        if( m_fileName[i] >= 48 && m_fileName[i] <= 57)
        {
            m_frame = m_fileName[i].digitValue();
            break;
        }
    }
    qDebug() << m_frame;
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &Player::updatePixmap);
    m_timer->start(250);

    setPos(QPointF(0,0) - QPointF(boundingRect().width()/2, boundingRect().height()/2));
}

void Player::updatePixmap()
{
    ++m_frame;
    m_frame%=(m_countFrames);
    //qDebug() << "frame " << m_frame << " fileName " << m_fileName;
    for(int i = 0; i < m_fileName.length(); ++i)
    {
        if( m_fileName[i] >= 48 && m_fileName[i] <= 57)
        {
            m_fileName.replace(m_fileName[i], QString::number(m_frame));
        }
    }
    QString pathFile = m_pathFile + QDir::separator() + m_fileName;
    setPixmap(pathFile);
}

int Player::frames()
{
    return m_countFrames;
}


QRectF Player::boundingRect() const
{
    return QRectF(0, 0, GameSettings::instance().unitSize().width()/2, GameSettings::instance().unitSize().height());
}
