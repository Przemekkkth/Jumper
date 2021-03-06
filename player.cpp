#include "player.h"
#include "gamesettings.h"
#include <QFileInfo>
#include <QDebug>
#include <QTimer>
#include <QDir>

const int Player::m_countFrames = 3;
const int Player::sChangeFramesMilliseconds = 250;

Player::Player(QString pathFile)
{
    mIsJumping = false;
    mJumpPixmap = QPixmap(":/img_x2/images/hero/hero_2/hero_jump.png");
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
    m_timer->start(sChangeFramesMilliseconds);

    mJumpUpAnim = new QPropertyAnimation(this,"y",this);
    mJumpDownAnim = new QPropertyAnimation(this,"y",this);
    mJumpHeight = GameSettings::instance().unitSize().height()*1.5;
}

void Player::updatePixmap()
{
    if(!mIsJumping)
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
        setPixmap(QPixmap(pathFile).scaled(int(boundingRect().width()), int(boundingRect().height()) ));
    }
    else {
        setPixmap(mJumpPixmap.scaled(int(boundingRect().width()), int(boundingRect().height())));
    }

}

void Player::setY(qreal y)
{
    moveBy(0,y-m_y);
    m_y = y;
}

int Player::frames()
{
    return m_countFrames;
}

bool Player::isJumping() const
{
    return mIsJumping;
}

void Player::jump()
{
    mIsJumping = true;
    mJumpUpAnim->setStartValue(y());
    mJumpUpAnim->setEndValue(y() - mJumpHeight);
    mJumpUpAnim->setEasingCurve(QEasingCurve::OutQuad);
    mJumpUpAnim->setDuration(250);
    mJumpUpAnim->start();
    connect(mJumpUpAnim, &QPropertyAnimation::finished, [this](){
       this->fall();
    });
}

void Player::fall()
{
    mJumpDownAnim->setStartValue(y());
    mJumpDownAnim->setEndValue(y() + mJumpHeight);
    mJumpDownAnim->setEasingCurve(QEasingCurve::InQuad);
    mJumpDownAnim->setDuration(250);
    mJumpDownAnim->start();
    connect(mJumpDownAnim, &QPropertyAnimation::finished, [this](){
        this->mIsJumping = false;
    });
}

qreal Player::y() const
{
    return m_y;
}

void Player::freeze()
{
    m_timer->stop();
    if(mJumpUpAnim->currentTime() > 0 && mJumpUpAnim->currentTime() < mJumpUpAnim->totalDuration() )
    {
        mJumpUpAnim->pause();
    }
    if(mJumpDownAnim->currentTime() > 0 && mJumpDownAnim->currentTime() < mJumpDownAnim->totalDuration() )
    {
        mJumpDownAnim->pause();
    }
}

void Player::unFreeze()
{
    m_timer->start(sChangeFramesMilliseconds);
    if(mJumpUpAnim->currentTime() > 0 && mJumpUpAnim->currentTime() < mJumpUpAnim->totalDuration() )
    {
        mJumpUpAnim->resume();
    }
    if(mJumpDownAnim->currentTime() > 0 && mJumpDownAnim->currentTime() < mJumpDownAnim->totalDuration() )
    {
        mJumpDownAnim->resume();
    }
}

void Player::reset()
{
   m_timer->start(sChangeFramesMilliseconds);
   mJumpUpAnim->setCurrentTime(0);
   mJumpDownAnim->setCurrentTime(mJumpDownAnim->totalDuration());
   mIsJumping = false;
}

QPropertyAnimation *Player::getJumpUpAnim() const
{
    return mJumpUpAnim;
}

QPropertyAnimation *Player::getJumpDownAnim() const
{
    return mJumpDownAnim;
}

QRectF Player::boundingRect() const
{
    return QRectF(0, 0, GameSettings::instance().unitSize().width()/2, GameSettings::instance().unitSize().height());
}
