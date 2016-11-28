#include "DMISignal.h"
#include <QDebug>




MySignal::MySignal(quint8 size, QWidget *parent) : QWidget(parent)
{
    m_size=size;
    this->show();


}
QSize MySignal::sizeHint() const
{
    if(m_size==1)
    {
        return QSize(413,407);
    }
    else if(m_size==2)
    {
        return QSize(413,525);
    }
    else if(m_size==3)
    {
        return QSize(400,400);
    }
    return QSize(100,100);
}
void MySignal::setValue(quint8 type, quint8 status, QRect &r, bool isreverse)
{
    m_type=type;
    m_status=status;
    m_rect=r;
    m_isreverse=isreverse;
    update();
}
void MySignal::drawCBISignal(QPainter& painter)
{
    painter.save();
    painter.setPen(QPen(Qt::black,1));
    QBrush b1(Qt::black);
    painter.setBrush(b1);
//    qDebug()<<"onelight"<<m_rect.left()<<m_rect.top()<<m_rect.height()*3/4;
//    qDebug()<<"size"<<m_size;
    QRect onelight(m_rect.left(),m_rect.top(),m_rect.height()*3/4,m_rect.height()*3/4);
    painter.drawEllipse(onelight);
    painter.restore();

    if(m_isreverse==0)
    {
        painter.drawLine(m_rect.left()+m_rect.height()*3/8,m_rect.y()+ m_rect.height()*3/4,
                         m_rect.left()+m_rect.height()*3/8,m_rect.y()+ m_rect.height());
        painter.drawLine(m_rect.left(),m_rect.y()+ m_rect.height(),
                         m_rect.left()+m_rect.height()*3/4,m_rect.y()+ m_rect.height());
    }
    else
    {
        painter.drawLine(m_rect.left()+m_rect.height()*3/8,m_rect.top()- m_rect.height()*1/4,
                         m_rect.left()+m_rect.height()*3/8,m_rect.top());
        painter.drawLine(m_rect.left(),m_rect.top()- m_rect.height()*1/4,
                         m_rect.left()+m_rect.height()*3/4,m_rect.top()- m_rect.height()*1/4);
    }



    switch (m_status)
    {
    case 1:

        painter.setPen(QPen(Qt::red,5));
        painter.drawLine(m_rect.left()+6,m_rect.top()+m_rect.height()*3/8,
                         m_rect.left()+m_rect.height()*3/4-6,m_rect.top()+m_rect.height()*3/8);

        break;
    case 2:
        painter.setPen(QPen(Qt::green,5));
        painter.drawLine(m_rect.left()+m_rect.height()*6/16,m_rect.top()+m_rect.height()/4,
                         m_rect.left()+m_rect.height()*6/16,m_rect.top()+m_rect.height()*2/4);
        break;
    case 3:
//        painter.setPen(QPen(Qt::yellow,5));
//        painter.drawLine(m_rect.left()+m_rect.height()*4/16,m_rect.top()+m_rect.height()*4/16,
//                         m_rect.left()+m_rect.height()*8/16+1,m_rect.top()+m_rect.height()*8/16+1);
        painter.setPen(QPen(Qt::yellow,5));
        painter.drawLine(m_rect.left()+m_rect.height()*8/16+1,m_rect.top()+m_rect.height()*4/16,
                         m_rect.left()+m_rect.height()*4/16,m_rect.top()+m_rect.height()*8/16+1);
        break;
    }
}
//void MySignal::drawCBISignal(QPainter& painter)
//{
//    QRect redlight(m_rect.left(),m_rect.top(),m_rect.height()/4,m_rect.height()/4);
//    painter.drawEllipse(redlight);
//    QRect greenlight(m_rect.left(),m_rect.top()+redlight.height(),m_rect.height()/4,m_rect.height()/4);
//    painter.drawEllipse(greenlight);
//    QRect yellowlight(m_rect.left(),m_rect.top()+redlight.height()+greenlight.height(),
//                      m_rect.height()/4,m_rect.height()/4);
//    painter.drawEllipse(yellowlight);
//    painter.drawLine(m_rect.left()+m_rect.height()/8,m_rect.y()+ m_rect.height()*3/4,
//                     m_rect.left()+m_rect.height()/8,m_rect.y()+ m_rect.height());
//    painter.drawLine(m_rect.left(),m_rect.y()+ m_rect.height(),
//                     m_rect.left()+m_rect.height()/4,m_rect.y()+ m_rect.height());

//    switch (m_status)
//    {
//    case 1:

//        painter.setPen(QPen(Qt::red,3));
//        painter.drawLine(m_rect.left(),m_rect.top()+m_rect.height()/8,
//                         m_rect.left()+m_rect.height()/4,m_rect.top()+m_rect.height()/8);

//        break;
//    case 2:
//        painter.setPen(QPen(Qt::green,3));
//        painter.drawLine(m_rect.left()+m_rect.height()/8,m_rect.top()+m_rect.height()/4,
//                         m_rect.left()+m_rect.height()/8,m_rect.top()+m_rect.height()*2/4);
//        break;
//    case 3:
//        painter.setPen(QPen(Qt::yellow,3));
//        painter.drawLine(m_rect.left()+m_rect.height()/16,m_rect.top()+m_rect.height()*2/4,
//                         m_rect.left()+m_rect.height()*3/16,m_rect.top()+m_rect.height()*3/4);
//        break;
//    }
//}

void MySignal::drawOLCSignal(QPainter& painter)
{
    painter.save();
    QRect redlight(m_rect.left(),m_rect.top(),m_rect.height()/4,m_rect.height()/4);
    painter.drawEllipse(redlight);
    QRect greenlight(m_rect.left(),m_rect.top()+redlight.height(),m_rect.height()/4,m_rect.height()/4);
    painter.drawEllipse(greenlight);
    painter.drawLine(m_rect.left()+m_rect.height()/8,m_rect.y()+ m_rect.height()*2/4,
                     m_rect.left()+m_rect.height()/8,m_rect.y()+ m_rect.height()*3/4);
    painter.drawLine(m_rect.left(),m_rect.y()+ m_rect.height()*3/4,
                     m_rect.left()+m_rect.height()/4,m_rect.y()+ m_rect.height()*3/4);



    switch (m_status)
    {
    case 1:

        painter.setPen(QPen(Qt::red,3));
        painter.drawLine(m_rect.left(),m_rect.top()+m_rect.height()/8,
                         m_rect.left()+m_rect.height()/4,m_rect.top()+m_rect.height()/8);

        break;
    case 2:
        painter.setPen(QPen(Qt::green,3));
        painter.drawLine(m_rect.left()+m_rect.height()/8,m_rect.top()+m_rect.height()/4,
                         m_rect.left()+m_rect.height()/8,m_rect.top()+m_rect.height()*2/4);
        break;
    }

    painter.restore();
}



void MySignal::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing|QPainter::TextAntialiasing|QPainter::SmoothPixmapTransform|QPainter::HighQualityAntialiasing);
    //    painter.save();
    painter.setPen(QPen(QColor(220,220,220),1));
    //    painter.drawEllipse(m_rect);



    switch (m_type)
    {
    case 1:
        drawCBISignal(painter);
        break;
    case 2:
        drawOLCSignal(painter);
    default:
        break;
    }


}

