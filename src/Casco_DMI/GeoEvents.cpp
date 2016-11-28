/******************************
** Date: 2016/06/23
** Author: noodlebin
** Brief: paint the geo events
** Version: 1.0
******************************/
#include "GeoEvents.h"
#include <QDebug>
#include <QPaintEvent>
#include <QDateTime>
#define MAX 65536
MyGeoEvents::MyGeoEvents(quint8 size, QWidget *parent) : QWidget(parent)
{
    m_eventid=new quint8[10]; //because m_number will never above 10, so the id count will never above 10 too
    m_outputvalue=new quint8[10];
    m_distobegin=new quint16[10];
    m_distoend=new quint16[10];
    m_number=0;
    isrefresh=false;

    //    this->setBackgroundRole(QPalette::NoRole);

    m_size=size;
    this->show();
}

void MyGeoEvents::setvalue(quint8 number, quint8 *id, quint8 *output, quint16 *distobegin, quint16 *distoend)
{
    m_number=number;
    for(int i=0;i<m_number;i++)
    {
        m_eventid[i]=id[i];
        m_outputvalue[i]=output[i];
        m_distobegin[i]=distobegin[i];
        m_distoend[i]=distoend[i];
        //        qDebug()<<m_eventid[i]<<m_outputvalue[i]<<m_distobegin[i]<<m_distoend[i];
    }
    //    qDebug()<<"one update";
    //    update();
    repaint();

    //    isrefresh=true;
    //        repaint();
}


void MyGeoEvents::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)
    //        qDebug()<<QDateTime::currentDateTime().currentMSecsSinceEpoch();
    //    if(!isrefresh)
    //    {
    //        qDebug()<<"not ref";

    //    }
    //    else
    //    {
    islimitspeed=false;
    //    QRect ur= e->rect();

    //   qDebug()<<"ursizeis"<<ur.size();

    //    QPixmap pix(ur.size());

    //    QPainter painter(&pix);
    QPainter painter(this);

    painter.setRenderHints(QPainter::Antialiasing|QPainter::TextAntialiasing|QPainter::SmoothPixmapTransform|QPainter::HighQualityAntialiasing);

    //    painter.setRenderHints(QPainter::Antialiasing|QPainter::TextAntialiasing|QPainter::SmoothPixmapTransform);
    painter.setBrush(QColor(73,86,120));
    painter.drawRect(0,0,this->width(),this->height());
    painter.setPen(QPen(Qt::green,3));
    painter.drawLine(0,2*height()/3,width(),2*height()/3);
    painter.setPen(Qt::NoPen);
    ispanto=true;
    if(m_number>0)
    {
        for(int i=0;i<m_number;i++)
        {
            switch(m_eventid[i])
            {
            case 1: drawEvent1(&painter,m_outputvalue[i],m_distobegin[i],m_distoend[i]);break;
            case 2:     drawEvent2(&painter,m_outputvalue[i],m_distobegin[i],m_distoend[i]);break;
            case 3:     drawEvent3(&painter,m_outputvalue[i],m_distobegin[i],m_distoend[i]);break;
            }
        }
        if(islimitspeed)
        {
            drawspeed(&painter,m_speed);
        }

    }
    drawCar(&painter);
    painter.setPen(QPen(QColor(220,220,220),6));
    painter.drawLine(0,2*height()/3+35,width(),2*height()/3+35);
    painter.end();
    //    QPainter realpix(this);
    //    realpix.drawPixmap(0,0,pix);

    //        qDebug()<<"is ref";
    //        isrefresh=false;
    //    }
}

QSize MyGeoEvents::sizeHint() const
{
    if(m_size==1)
    {
        return QSize(381,211);
    }
    else if(m_size==2)
    {
        return QSize(394,255);
    }
    else if(m_size==3)
    {
        return QSize(531,273);
    }
    return QSize(100,100);
}
void MyGeoEvents::drawEvent1(QPainter *painter, quint8 output, quint16 begin, quint16 end)
{
    Q_UNUSED(output)
    //  static quint16 begint=24;
    //   static quint16 endt=29;
    //   begin=begint,end=endt;

    if(begin>0&&end>0&&begin<end)
    {
        painter->save();
        painter->setBrush(QColor(102,123,180));
        painter->setPen(Qt::NoPen);


        qreal x1=(qreal)begin/MAX*this->width();
        qreal w1=(qreal)(end-begin)/MAX*this->width();
        qreal tmp=x1+w1;
        QPointF topleft=QPointF(x1,0);

        QPointF bottomright=QPointF(tmp,this->height());
        QRectF rec=QRectF(topleft,bottomright);


        //            quint16 x=(quint16)(begin*width()/MAX);
        //            quint16 w=(quint16)((end-begin)/MAX*width());
        //            QPoint topleft=QPoint(x,0);
        //            QPoint bottomright=QPoint(x+w,height());
        //            QRect rec =QRect(topleft,bottomright);


        //        qDebug()<<"event1"<<x1<<w1<<begin<<end;
        painter->drawRect(rec);
        painter->setPen(QPen(Qt::green,3));
        painter->drawLine(x1,2*height()/3,tmp,2*height()/3);

        painter->restore();

        //        begint--,endt--;
    }



}

void MyGeoEvents::drawEvent2(QPainter *painter, quint8 output, quint16 begin, quint16 end)
{

    if(begin>0&&end>0&&begin<end)
    {
        painter->save();
        painter->setBrush(QColor(170,170,170));
        painter->setPen(Qt::NoPen);


        qreal x1=(qreal)begin/MAX*this->width();
        if(x1<=90)
            ispanto=false;
        else
            ispanto=true;
        qreal w1=(qreal)(end-begin)/MAX*this->width();
        qreal tmp=x1+w1;
        QPointF topleft=QPointF(x1,0);
        QPointF bottomright=QPointF(tmp,this->height());
        QRectF rec=QRectF(topleft,bottomright);
        //    qDebug()<<"event2"<<begin<<x1<<tmp;
        painter->drawRect(rec);

        islimitspeed=true;
        m_speed=output;
        painter->setPen(QColor(170,170,170));
        painter->drawLine(x1,2*height()/3,x1+w1,2*height()/3);


        painter->restore();
    }



}

void MyGeoEvents::drawEvent3(QPainter *painter, quint8 output, quint16 begin, quint16 end)
{
    Q_UNUSED(output)
    if(begin>0&&end>0&&begin<end)
    {
        painter->save();
        painter->setBrush(Qt::yellow);
        painter->setPen(Qt::NoPen);

        qreal x1=(qreal)begin/MAX*this->width();
        qreal w1=(qreal)(end-begin)/MAX*this->width();
        qreal tmp=x1+w1;
        QPointF topleft=QPointF(x1,0);
        QPointF bottomright=QPointF(tmp,this->height());
        QRectF rec=QRectF(topleft,bottomright);
        painter->drawRect(rec);
        //        painter->setPen(Qt::black);
        // qDebug()<<"event3"<<begin<<x1<<tmp;
        painter->setPen(Qt::yellow);
        painter->drawLine(x1,2*height()/3,x1+w1,2*height()/3);

        painter->restore();
    }



}

void MyGeoEvents::drawspeed(QPainter* painter,quint8 speed)
{

    painter->save();
    painter->setBrush(Qt::red);

    painter->setPen(Qt::NoPen);
    qreal r=(qreal)this->height()/8;
    qreal rinside=r-7;
    QRectF rect(width()-r-r-5,0+5,r+r,r+r);
    //    painter->drawEllipse(rect);
    painter->drawEllipse(rect);  //x,y,w,h

    painter->setBrush(Qt::white);
    QRectF rectinside(width()-r-r+r-rinside-5,r-rinside+5,rinside*2,rinside*2);
    painter->drawEllipse(rectinside);

    qreal fontSize=(qreal)2*r/3;
    QFont font;
    font.setPointSize(fontSize);
    painter->setFont(font);

    painter->setPen(Qt::black);
    painter->drawText(rect,Qt::AlignHCenter|Qt::AlignVCenter,QString::number( speed));
    painter->restore();
}

void MyGeoEvents::drawCar(QPainter* painter)
{
    painter->save();

    QRect rect(0,2*height()/3,75,30);

    if(ispanto)
        painter->drawPixmap(rect,QPixmap("res/Tram_p.png"));
    else
        painter->drawPixmap(rect,QPixmap("res/tram_np.png"));

    painter->restore();
}

