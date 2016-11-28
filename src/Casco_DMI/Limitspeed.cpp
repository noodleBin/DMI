#include "Limitspeed.h"

LimitSpeed::LimitSpeed(quint8 size, QWidget *parent) : QWidget(parent)
{
    m_speed=0;
    m_size=size;
    this->show();
}

void LimitSpeed::setSpeed(quint8 speed)
{
    m_speed=speed;
    //    qDebug()<<"now spe"<<m_speed;
    update();
}

void LimitSpeed::paintEvent(QPaintEvent *)
{

    QPainter painter(this);
    painter.save();
    painter.setBrush(Qt::red);
    painter.setRenderHints(QPainter::Antialiasing|
                           QPainter::TextAntialiasing|
                           QPainter::SmoothPixmapTransform|QPainter::HighQualityAntialiasing);
    painter.setPen(Qt::NoPen);
    qreal r=(qreal)this->height()/2;
    qreal rinside=r-5;

    QRectF rect(0,0,r+r,r+r);

    painter.drawEllipse(rect);  //x,y,w,h

    painter.setBrush(Qt::white);

    QRectF rectinside(0+5,0+5,rinside*2,rinside*2);
    painter.drawEllipse(rectinside);

    qreal fontSize=(qreal)2*r/3;
    QFont font;
    font.setPointSize(fontSize);
    painter.setFont(font);

    painter.setPen(Qt::black);
    painter.drawText(rect,Qt::AlignHCenter|Qt::AlignVCenter,QString::number( m_speed));

    painter.restore();

}

QSize LimitSpeed::sizeHint() const
{
    switch (m_size)
    {
    case 1:
        return QSize(80,80);
        break;
    case 2:
        return QSize(64,64);
        break;
    default:
        return QSize(48,48);
        break;
    }

}

