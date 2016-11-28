#include "TLEevents.h"
#define MAX 65536


TLEEvents::TLEEvents(quint8 size, QWidget *parent): QWidget(parent)
{

    m_size=size;
    this->show();
}

void TLEEvents::setvalue(quint8 background, quint8 type, quint8 position, quint8 value)
{
    m_background=background;
    m_type=type;
    m_position=position;
    m_value=value;
    update();

}

void TLEEvents::paintEvent(QPaintEvent *e)
{

    Q_UNUSED(e)

    QPainter painter(this);

    painter.setRenderHints(QPainter::Antialiasing|QPainter::TextAntialiasing|QPainter::SmoothPixmapTransform|QPainter::HighQualityAntialiasing);

    //    painter.setRenderHints(QPainter::Antialiasing|QPainter::TextAntialiasing|QPainter::SmoothPixmapTransform);
    painter.setBrush(QColor(73,86,120));
    painter.drawRect(0,0,this->width(),this->height());


    switch (m_background)
    {
    case 1:
        drawEvent1(&painter);
        break;
    case 2:
        drawEvent2(&painter);
        break;
    case 3:
        drawEvent3(&painter);
    case 4:
        drawEvent4(&painter);
    default:
        break;
    }
    drawSignal(&painter,m_type,m_position,m_value);
    //    painter.setPen(Qt::NoPen);
    //    ispanto=true;
    //    if(m_number>0)
    //    {
    //        for(int i=0;i<m_number;i++)
    //        {
    //            switch(m_eventid[i])
    //            {
    //            case 1: drawEvent1(&painter,m_outputvalue[i],m_distobegin[i],m_distoend[i]);break;
    //            case 2:     drawEvent2(&painter,m_outputvalue[i],m_distobegin[i],m_distoend[i]);break;
    //            case 3:     drawEvent3(&painter,m_outputvalue[i],m_distobegin[i],m_distoend[i]);break;
    //            }
    //        }
    //        if(islimitspeed)
    //        {
    //            drawspeed(&painter,m_speed);
    //        }

    //    }




    //    painter.setPen(QPen(Qt::yellow,3));
    //    painter.drawLine(1*width()/6+35+10,1*height()/6+10,5*width()/6+35-30,2*height()/3+25);

    painter.end();
    //    QPainter realpix(this);
    //    realpix.drawPixmap(0,0,pix);

    //        qDebug()<<"is ref";
    //        isrefresh=false;
    //    }
}

QSize TLEEvents::sizeHint() const
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

void TLEEvents::drawSignal(QPainter *painter, quint8 type, quint8 position, quint8 value)
{
    //    type=2;
    //    position=1;
    //    value=2;
    painter->save();
    painter->setPen(QPen(QColor(220,220,220),2));
    if(type==1)
    {
        switch(position)
        {
        case 1:

        {
            painter->drawLine(height()/7,height()/5,height()/7,height()/5+16);
            painter->drawLine(height()/7,height()/5+8,height()/6,height()/5+8);


            QRect r1(height()/6,height()/5,16,16);
            painter->drawEllipse(r1);

            if(value==1)
            {
                painter->setPen(QPen(Qt::red,2));

            }
            else
            {
                painter->setPen(QPen(QColor(220,220,220),2));
            }
            painter->drawLine(height()/6,height()/5+8,height()/6+16,height()/5+8);

                painter->setPen(QPen(QColor(220,220,220),2));
            QRect r2(height()/6+16,height()/5,16,16);
            painter->drawEllipse(r2);

            if(value==2)
            {
                painter->setPen(QPen(Qt::yellow,4));

                painter->drawLine(height()/6+48+10,height()/5+8,height()/6+48+10+height()/3,height()/5+8);
                painter->setPen(QPen(Qt::green,2));
            }
            else
            {
                painter->setPen(QPen(QColor(220,220,220),2));
            }
            painter->drawLine(height()/6+16+8,height()/5,height()/6+16+8,height()/5+16);




                            painter->setPen(QPen(QColor(220,220,220),2));
            QRect r3(height()/6+16+16,height()/5,16,16);
            painter->drawEllipse(r3);

            if(value==3||value==4)
            {
                painter->setPen(QPen(Qt::yellow,4));

                painter->drawLine(height()/3+16,height()/3,height()/3+height()/3+16,height()/3+height()/3);


                painter->setPen(QPen(Qt::yellow,2));

            }
            else
            {
                painter->setPen(QPen(QColor(220,220,220),2));
            }
            painter->drawLine(height()/6+16+16+4,height()/5+4,height()/6+16+16+12,height()/5+12);

            break;
        }
        case 2:
        {

            painter->drawLine(height()/7,2*height()/3+16,height()/7,2*height()/3+32);
            painter->drawLine(height()/7,2*height()/3+24,height()/7+16,2*height()/3+24);



            QRect r1(height()/6,2*height()/3+16,16,16);
            painter->drawEllipse(r1);

            if(value==1)
            {
                painter->setPen(QPen(Qt::red,2));

            }
            else
            {
                painter->setPen(QPen(QColor(220,220,220),2));
            }
            painter->drawLine(height()/6,2*height()/3+24,height()/6+16,2*height()/3+24);



            painter->setPen(QPen(QColor(220,220,220),2));

            QRect r2(height()/6+16,2*height()/3+16,16,16);
            painter->drawEllipse(r2);

            if(value==2)
            {
                painter->setPen(QPen(Qt::yellow,4));

                painter->drawLine(height()/6+48+10,height()/3+height()/3+24,height()/6+48+10+height()/3,height()/3+height()/3+24);

             painter->setPen(QPen(Qt::green,2));

            }
            else
            {
                painter->setPen(QPen(QColor(220,220,220),2));
            }
            painter->drawLine(height()/6+16+8,2*height()/3+16,height()/6+16+8,2*height()/3+16+16);

                painter->setPen(QPen(QColor(220,220,220),2));

            QRect r3(height()/6+16+16,2*height()/3+16,16,16);
            painter->drawEllipse(r3);

            if(value==3||value==4)
            {
                painter->setPen(QPen(Qt::yellow,4));

                painter->drawLine(height()/3+16,height()/3+height()/3,height()/3+height()/3+16,height()/3);
                painter->setPen(QPen(Qt::yellow,2));

            }
            else
            {
                painter->setPen(QPen(QColor(220,220,220),2));
            }
            painter->drawLine(height()/6+16+16+4,2*height()/3+16+4,height()/6+16+16+12,2*height()/3+16+12);

            break;
        }
        case 3:

        {

            QRect r1(height()/6+height()/3,height()/5,16,16);
            painter->drawEllipse(r1);

            if(value==1)
            {
                painter->setPen(QPen(Qt::red,2));

            }
            else
            {
                painter->setPen(QPen(QColor(220,220,220),2));
            }
            painter->drawLine(height()/6+height()/3,height()/5+8,height()/6+16+height()/3,height()/5+8);

            painter->setPen(QPen(QColor(220,220,220),2));

            QRect r2(height()/6+16+height()/3,height()/5,16,16);
            painter->drawEllipse(r2);

            if(value==2)
            {
                painter->setPen(QPen(Qt::yellow,4));

                painter->drawLine(height()/6+height()/3-6,height()/5+8,height()/6+height()/3-48,height()/5+8);
                painter->setPen(QPen(Qt::green,2));

            }
            else
            {
                painter->setPen(QPen(QColor(220,220,220),2));
            }
            painter->drawLine(height()/6+16+8+height()/3,height()/5,height()/6+16+8+height()/3,height()/5+16);

             painter->setPen(QPen(QColor(220,220,220),2));

            QRect r3(height()/6+16+16+height()/3,height()/5,16,16);
            painter->drawEllipse(r3);

            if(value==3||value==4)
            {
                painter->setPen(QPen(Qt::yellow,4));

                painter->drawLine(height()/3+height()/3-16,height()/3,height()/3-16,height()/3+height()/3);
                painter->setPen(QPen(Qt::yellow,2));

            }
            else
            {
                painter->setPen(QPen(QColor(220,220,220),2));
            }
            painter->drawLine(height()/6+16+16+4+height()/3,height()/5+4,height()/6+16+16+12+height()/3,height()/5+12);

            painter->drawLine(height()/6+16+16+height()/3+16,height()/5+8,height()/6+16+16+height()/3+24,height()/5+8);
            painter->drawLine(height()/6+16+16+height()/3+24,height()/5,height()/6+16+16+height()/3+24,height()/5+16);
            break;
        }
        case 4:

        {


            QRect r1(height()/6+height()/3,2*height()/3+16,16,16);
            painter->drawEllipse(r1);

            if(value==1)
            {
                painter->setPen(QPen(Qt::red,2));

            }
            else
            {
                painter->setPen(QPen(QColor(220,220,220),2));
            }
            painter->drawLine(height()/6+height()/3,2*height()/3+24,height()/6+16+height()/3,2*height()/3+24);


                 painter->setPen(QPen(QColor(220,220,220),2));

            QRect r2(height()/6+16+height()/3,2*height()/3+16,16,16);
            painter->drawEllipse(r2);

            if(value==2)
            {
                painter->setPen(QPen(Qt::yellow,4));

                painter->drawLine(height()/6+height()/3-6,height()/3+height()/3+24,height()/6+height()/3-48,height()/3+height()/3+24);
                painter->setPen(QPen(Qt::green,2));

            }
            else
            {
                painter->setPen(QPen(QColor(220,220,220),2));
            }
            painter->drawLine(height()/6+16+8+height()/3,2*height()/3+16,height()/6+16+8+height()/3,2*height()/3+32);

                  painter->setPen(QPen(QColor(220,220,220),2));

            QRect r3(height()/6+16+16+height()/3,2*height()/3+16,16,16);
            painter->drawEllipse(r3);

            if(value==3||value==4)
            {
                painter->setPen(QPen(Qt::yellow,4));

                painter->drawLine(height()/3+height()/3-16,height()/3+height()/3,height()/3-16,height()/3);
                painter->setPen(QPen(Qt::yellow,2));

            }
            else
            {
                painter->setPen(QPen(QColor(220,220,220),2));
            }
            painter->drawLine(height()/6+16+16+4+height()/3,2*height()/3+20,height()/6+16+16+12+height()/3,2*height()/3+28);

            painter->drawLine(height()/6+16+16+height()/3+16,2*height()/3+24,height()/6+16+16+height()/3+24,2*height()/3+24);
            painter->drawLine(height()/6+16+16+height()/3+24,2*height()/3+16,height()/6+16+16+height()/3+24,2*height()/3+32);
            break;
        }

        }
    }
    if(type==2)
    {
        switch(position)
        {
        case 1:

        {

            painter->drawLine(height()/7+1*height()/2,height()/15,height()/7+1*height()/2,height()/15+16);
            painter->drawLine(height()/7+1*height()/2,height()/15+8,height()/6+1*height()/2,height()/15+8);
            QRect r1(height()/6+1*height()/2,height()/15,16,16);
            painter->drawEllipse(r1);

            if(value==1)
            {
                painter->setPen(QPen(Qt::red,2));

            }
            else
            {
                painter->setPen(QPen(QColor(220,220,220),2));
            }
            painter->drawLine(height()/6+1*height()/2,height()/15+8,height()/6+16+1*height()/2,height()/15+8);


                 painter->setPen(QPen(QColor(220,220,220),2));
            if(value==2)
            {
                painter->setPen(QPen(Qt::green,2));

            }
            else
            {
                painter->setPen(QPen(QColor(220,220,220),2));
            }
            QRect r2(height()/6+16+1*height()/2,height()/15,16,16);
            painter->drawEllipse(r2);
//            QRect r21(height()/6+16+1*height()/2+3,height()/15+3,10,10);
//            painter->drawEllipse(r21);

//            if(value==3||value==4)
//            {
//                painter->setPen(QPen(Qt::yellow,2));

//            }
//            else
//            {
//                painter->setPen(QPen(QColor(220,220,220),2));
//            }
//            QRect r3(height()/6+16+16+1*height()/2,height()/15,16,16);
//            painter->drawEllipse(r3);
//            painter->drawLine(height()/6+16+16+4+1*height()/2,height()/15+4,height()/6+16+16+12+1*height()/2,height()/15+12);

            break;
        }
        case 2:
        {

            painter->drawLine(height()/7+1*height()/2,12*height()/15,height()/7+1*height()/2,12*height()/15+16);
            painter->drawLine(height()/7+1*height()/2,12*height()/15+8,height()/6+1*height()/2,12*height()/15+8);
            if(value==1)
            {
                painter->setPen(QPen(Qt::red,2));

            }
            else
            {
                painter->setPen(QPen(QColor(220,220,220),2));
            }
            QRect r1(height()/6+1*height()/2,12*height()/15,16,16);
            painter->drawEllipse(r1);
            painter->drawLine(height()/6+1*height()/2,12*height()/15+8,height()/6+16+1*height()/2,12*height()/15+8);

            if(value==2)
            {
                painter->setPen(QPen(Qt::green,2));

            }
            else
            {
                painter->setPen(QPen(QColor(220,220,220),2));
            }
            QRect r2(height()/6+16+1*height()/2,12*height()/15,16,16);
            painter->drawEllipse(r2);
//            QRect r21(height()/6+16+1*height()/2+3,12*height()/15+3,10,10);
//            painter->drawEllipse(r21);
//            if(value==3||value==4)
//            {
//                painter->setPen(QPen(Qt::yellow,2));

//            }
//            else
//            {
//                painter->setPen(QPen(QColor(220,220,220),2));
//            }
//            QRect r3(height()/6+16+16+1*height()/2,12*height()/15,16,16);
//            painter->drawEllipse(r3);
//            painter->drawLine(height()/6+16+16+4+1*height()/2,12*height()/15+4,height()/6+16+16+12+1*height()/2,12*height()/15+12);

            break;
        }
        case 3:

        {
            if(value==1)
            {
                painter->setPen(QPen(Qt::red,2));

            }
            else
            {
                painter->setPen(QPen(QColor(220,220,220),2));
            }
            QRect r1(height()/6+height()/3+1*height()/2+height()/3,height()/5,16,16);
            painter->drawEllipse(r1);
            painter->drawLine(height()/6+height()/3+1*height()/2+height()/3,height()/5+8,height()/6+16+height()/3+1*height()/3+height()/2,height()/5+8);

            if(value==2)
            {
                painter->setPen(QPen(Qt::green,2));

            }
            else
            {
                painter->setPen(QPen(QColor(220,220,220),2));
            }
            QRect r2(height()/6+16+height()/3+1*height()/2+1*height()/3,height()/5,16,16);
            painter->drawEllipse(r2);
//            QRect r21(height()/6+16+height()/3+1*height()/2+1*height()/3+3,height()/5+3,10,10);
//            painter->drawEllipse(r21);
//            if(value==3||value==4)
//            {
//                painter->setPen(QPen(Qt::yellow,2));

//            }
//            else
//            {
//                painter->setPen(QPen(QColor(220,220,220),2));
//            }
//            QRect r3(height()/6+16+16+height()/3+1*height()/2+1*height()/3,height()/5,16,16);
//            painter->drawEllipse(r3);
//            painter->drawLine(height()/6+16+16+4+height()/3+1*height()/2+1*height()/3,height()/5+4,height()/6+16+16+12+height()/3+1*height()/2+1*height()/3,height()/5+12);

            painter->drawLine(height()/6+16+16+height()/3+16+1*height()/2+1*height()/3,height()/5+8,height()/6+16+16+height()/3+24+1*height()/2+1*height()/3,height()/5+8);
            painter->drawLine(height()/6+16+16+height()/3+24+1*height()/2+1*height()/3,height()/5,height()/6+16+16+height()/3+24+1*height()/2+1*height()/3,height()/5+16);
            break;
        }
        case 4:

        {

            if(value==1)
            {
                painter->setPen(QPen(Qt::red,2));

            }
            else
            {
                painter->setPen(QPen(QColor(220,220,220),2));
            }
            QRect r1(height()/6+height()/3+1*height()/2+height()/3,12*height()/15,16,16);
            painter->drawEllipse(r1);
            painter->drawLine(height()/6+height()/3+1*height()/2+height()/3,12*height()/15+8,height()/6+16+height()/3+1*height()/3+height()/2,12*height()/15+8);

            if(value==2)
            {
                painter->setPen(QPen(Qt::green,2));

            }
            else
            {
                painter->setPen(QPen(QColor(220,220,220),2));
            }
            QRect r2(height()/6+16+height()/3+1*height()/2+1*height()/3,12*height()/15,16,16);
            painter->drawEllipse(r2);
//            QRect r21(height()/6+16+height()/3+1*height()/2+1*height()/3+3,12*height()/15+3,10,10);
//            painter->drawEllipse(r21);
//            if(value==3||value==4)
//            {
//                painter->setPen(QPen(Qt::yellow,2));

//            }
//            else
//            {
//                painter->setPen(QPen(QColor(220,220,220),2));
//            }
//            QRect r3(height()/6+16+16+height()/3+1*height()/2+1*height()/3,12*height()/15,16,16);
//            painter->drawEllipse(r3);
//            painter->drawLine(height()/6+16+16+4+height()/3+1*height()/2+1*height()/3,12*height()/15+4,height()/6+16+16+12+height()/3+1*height()/2+1*height()/3,12*height()/15+12);

            painter->drawLine(height()/6+16+16+height()/3+16+1*height()/2+1*height()/3,12*height()/15+8,height()/6+16+16+height()/3+24+1*height()/2+1*height()/3,12*height()/15+8);
            painter->drawLine(height()/6+16+16+height()/3+24+1*height()/2+1*height()/3,12*height()/15,height()/6+16+16+height()/3+24+1*height()/2+1*height()/3,12*height()/15+16);
            break;
        }

        }
    }
    painter->restore();
}

void TLEEvents::drawEvent1(QPainter *painter)
{
    painter->save();
    painter->setPen(QPen(QColor(220,220,220),4));
    painter->drawLine(0,1*height()/3,width(),1*height()/3);

    painter->drawLine(1*height()/3,1*height()/3,2*height()/3,2*height()/3);
    painter->drawLine(2*height()/3,1*height()/3,1*height()/3,2*height()/3);

    painter->drawLine(0,2*height()/3,width(),2*height()/3);
    painter->restore();
}

void TLEEvents::drawEvent2(QPainter *painter)
{
    painter->save();
    painter->setPen(QPen(QColor(220,220,220),4));
    painter->drawLine(0,1*height()/3,width(),1*height()/3);

    painter->drawLine(1*height()/3,1*height()/3,2*height()/3,2*height()/3);
    painter->drawLine(2*height()/3,1*height()/3,1*height()/3,2*height()/3);

    painter->drawLine(0,2*height()/3,width(),2*height()/3);


    for(int i=0,j=1;i<15;i++,j++)
    {
        painter->drawLine(height()*3/3,i*height()/14,height()*3/3,j*height()/14);
        i++,j++;
    }

    for(int i=0,j=1;i<15;i++,j++)
    {
        painter->drawLine(height()*4/3,i*height()/14,height()*4/3,j*height()/14);
        i++,j++;
    }

    painter->restore();

}

void TLEEvents::drawEvent3(QPainter *painter)
{
    painter->save();
    painter->setPen(QPen(QColor(220,220,220),4));
    painter->drawLine(0,1*height()/3,width(),1*height()/3);

    painter->drawLine(1*height()/3,1*height()/3,2*height()/3,2*height()/3);
    //    painter->drawLine(2*height()/3,1*height()/3,1*height()/3,2*height()/3);

    painter->drawLine(0,2*height()/3,width(),2*height()/3);
    painter->restore();
}

void TLEEvents::drawEvent4(QPainter *painter)
{
    painter->save();
    painter->setPen(QPen(QColor(220,220,220),4));
    painter->drawLine(0,1*height()/3,width(),1*height()/3);

    //    painter->drawLine(1*height()/3,1*height()/3,2*height()/3,2*height()/3);
    painter->drawLine(2*height()/3,1*height()/3,1*height()/3,2*height()/3);

    painter->drawLine(0,2*height()/3,width(),2*height()/3);
    painter->restore();
}

