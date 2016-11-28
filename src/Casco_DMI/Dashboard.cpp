/******************************
** Date: 2016/06/23
** Author: noodlebin
** Brief: Paint the Dashboard in 10.4 display screen .cpp
** Version: 1.0
******************************/
#include "Dashboard.h"
#include <QDebug>

MyDashboard::MyDashboard(quint8 size,QWidget *parent) : QWidget(parent)
{
    initVariables();
    setValue(10,50,10);
    m_size=size;
    this->show();
}
QSize MyDashboard::sizeHint() const
{
    if(m_size==2)
    {
        return QSize(273,273);
    }
    else if(m_size==3)
    {
        return QSize(320,320);
    }
    else if(m_size==4)
    {
        return QSize(360,360);
    }
    return QSize(100,100);
}
void MyDashboard::setValue(quint8 curvalue, quint8 limitvalue,quint8 lblvalue)
{
    m_currentValue=curvalue; //指针的显示值
    m_limitSpeedValue=limitvalue;
    m_lblvalue=lblvalue; //lbl_txt的显示值

    //    qDebug()<<"in dashborad setvalue"<<m_currentValue<<m_limitSpeedValue<<m_lblvalue;
    update();
}

void MyDashboard::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing|QPainter::TextAntialiasing|QPainter::SmoothPixmapTransform);
    resetVariables(&painter);

    drawColorPie(&painter);
    drawCoverCircle(&painter);
    drawMark(&painter);
    drawIndicator(&painter);
    drawLimitSpeed(&painter);
    drawCoverBall(&painter);
    //    drawTextRect(&painter);
    painter.end();
}




void MyDashboard::drawMark(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::white);
    painter->translate(m_center);

    qreal dAngle=(qreal)270/100;//180+45-(-45)=270，均分成100格，因此每一格角度如此。
    qreal startAngle=45;
    int value=0;
    QString strValue;
    for(int i=0;i<=100;i++)
    {
        painter->save();
        painter->rotate(startAngle);

        if(i%10==0)
        {
            strValue=tr("%1").arg(value);
            qreal textWidth=fontMetrics().width(strValue);
            qreal textHeight=fontMetrics().height();
            QPointF bottomPot(0,m_colorCircleRadius-2*SPACE);
            QPointF topPot(0,m_colorCircleRadius-2*SPACE-LONG);
            painter->drawLine(bottomPot,topPot);
            value+=10;

            painter->save();
            QPointF textPot(0-textWidth/2,m_colorCircleRadius+SPACE+LONG+SPACE+textHeight);
            painter->translate(textPot);
            painter->rotate(180);
            qreal fontSize=textHeight/4*3;
            QFont font;
            font.setPointSize(fontSize);
            painter->setFont(font);


            painter->drawText(QPointF(-textWidth,5*textHeight),strValue);
            painter->restore();
        }
        else if(i%5==0)
        {
            QPointF bottomPot(0,m_colorCircleRadius-2*SPACE);
            QPointF topPot(0,m_colorCircleRadius-2*SPACE-OK);
            painter->drawLine(bottomPot,topPot);

        }
        else
        {
            QPointF bottomPot(0,m_colorCircleRadius-2*SPACE);
            QPointF topPot(0,m_colorCircleRadius-2*SPACE-SHORT);
            painter->drawLine(bottomPot,topPot);
        }
        painter->restore();
        startAngle+=dAngle;
    }
    painter->restore();
}

void MyDashboard::drawCoverCircle(QPainter *painter)
{
    painter->save();
    //    painter->setBrush(QColor(130,130,130));
    painter->setBrush(QColor(0,0,0));
    painter->setPen(Qt::NoPen);
    painter->drawEllipse(m_center,m_coverCircleRadius,m_coverCircleRadius);
    painter->restore();
}

void MyDashboard::drawColorPie(QPainter *painter)
{
    painter->save();

    QPointF topLeftPot(m_center.x()-m_colorCircleRadius,m_center.y()-m_colorCircleRadius);
    QPointF bottomRightPot(m_center.x()+m_colorCircleRadius,m_center.y()+m_colorCircleRadius);
    m_colorCircleRect=QRectF(topLeftPot,bottomRightPot); //圆的外切矩形
    painter->setPen(Qt::NoPen);


    painter->setBrush(Qt::green);
    painter->drawPie(m_colorCircleRect,-45*16,270*16); //后两个参数startangle，spanangle，从右往左画spanangle,单位为1/16度，因此需乘16
    //先用绿色画满整个扇形
    //painter->drawPie(m_colorCircleRect,45,180);
    //    painter->setBrush(QColor(218,218,0));
    //    painter->drawPie(m_colorCircleRect,0*16,45*16);

    painter->setBrush(QColor(240,50,50));
    //    painter->drawPie(m_colorCircleRect,0,-45*16);
    painter->drawPie(m_colorCircleRect,-45*16,((100-m_limitSpeedValue)*(qreal)270/100)*16); //因为起始角度为最大速度的对于角度，
    //因此划过的角度为（最大速度-限速）转换成角度后*16
    painter->restore();
}



void MyDashboard::drawIndicator(QPainter *painter)
{
    //    qDebug()<<"drawindicator";
    painter->save();

    painter->translate(m_center);
    qreal increment=(qreal)270/100;
    qreal changedAngle=45+increment*m_currentValue;
    painter->rotate(changedAngle);//旋转之后指针的x就为0，y为m_colorCircleRadius+LONG,long代表刻度的长度

    QPointF topPot(0,m_colorCircleRadius-LONG);
    QPointF bottomLeftPot(-m_coverBallRadius/3,0);
    QPointF bottomRightPot(m_coverBallRadius/3,0);
    painter->setPen(Qt::NoPen);


    QLinearGradient indicatorGradient(topPot,bottomLeftPot);
    indicatorGradient.setColorAt(0.0,QColor(236,187,62));
    indicatorGradient.setColorAt(0.5,QColor(220,147,0));
    indicatorGradient.setColorAt(1.0,QColor(236,187,62));
    painter->setBrush(indicatorGradient);

    QVector<QPointF> potVec;


    potVec.push_back(topPot);
    potVec.push_back(bottomLeftPot);
    potVec.push_back(bottomRightPot);
    painter->drawPolygon(potVec);

    painter->restore();
}

void MyDashboard::drawCoverBall(QPainter *painter)
{
    painter->save();

    qreal ballRadius=m_outerRadius/7;
    m_coverBallRadius=ballRadius;
    QRadialGradient ballGradient(m_center,ballRadius,m_center);
    ballGradient.setColorAt(0.0,QColor(140,140,140));
    ballGradient.setColorAt(0.7,QColor(140,140,140));
    ballGradient.setColorAt(1.0,QColor(60,60,60));
    painter->setBrush(ballGradient);
    painter->setPen(Qt::NoPen);
    painter->drawEllipse(m_center,ballRadius,ballRadius);


    QRectF textRect(m_center.x()-ballRadius,m_center.y()-ballRadius,
                    2*ballRadius,
                    2*ballRadius);


    qreal fontSize=textRect.height()/3;
    QFont font;
    font.setPointSize(fontSize);
    painter->setFont(font);

    painter->setOpacity(1.0);
    if(m_currentValue<24)
        painter->setPen(Qt::green);
    else
        painter->setPen(Qt::red);
    QString strValue;
    strValue=tr("%1").arg(m_currentValue);
    painter->drawText(textRect,Qt::AlignHCenter|Qt::AlignVCenter,strValue);

    painter->restore();
}

void MyDashboard::resetVariables(QPainter *painter)
{
    Q_UNUSED(painter)
    m_outerRadius=width()*2/3;
    m_innerRadius=m_outerRadius/8*7;
    m_coverCircleRadius=m_outerRadius/8*4+LONG;
    m_colorCircleRadius=m_outerRadius/8*5;

    m_center=rect().center();
}

void MyDashboard::drawTextRect(QPainter *painter)
{
    //    qDebug()<<"drawText";
    painter->save();
    qreal rectWidth=m_coverCircleRadius/5;

    QPointF topLeftPot(m_center.x()-1.5*rectWidth,m_center.y()+rectWidth*2);
    QPointF bottomRightPot(topLeftPot.x()+3*rectWidth,topLeftPot.y()+rectWidth*2);
    QRectF textRect(topLeftPot,bottomRightPot);

    painter->setPen(Qt::NoPen);
    painter->setBrush(QColor(50,50,50));
    painter->setOpacity(0.6);
    painter->drawRoundRect(textRect,ANGLE,ANGLE);

    qreal fontSize=textRect.height()/3;
    QFont font;
    font.setPointSize(fontSize);
    painter->setFont(font);

    painter->setOpacity(1.0);
    painter->setPen(Qt::white);
    QString strValue;
    strValue=tr("%1").arg(m_lblvalue);
    painter->drawText(textRect,Qt::AlignHCenter|Qt::AlignVCenter,strValue);
    painter->restore();
}

void MyDashboard::drawLimitSpeed(QPainter *painter)
{
    //    qDebug()<<"drawlimitspeed";
    //    m_limitSpeedValue=m_currentValue+8;
    painter->save();

    painter->translate(m_center);
    qreal increment=(qreal)270/100;
    qreal changedAngle=45+increment*m_limitSpeedValue; //+45就是为了旋转后能和圆相切
    painter->rotate(changedAngle);//旋转之后指针的x就为0，y为m_colorCircleRadius+LONG,long代表刻度的长度
    //旋转后的x轴与圆相切，x就是圆心坐标0，y为圆半径+刻度长度
    QPointF topPot(0,m_colorCircleRadius);
    QPointF bottomLeftPot(-8,m_colorCircleRadius+10);
    QPointF bottomRightPot(8,m_colorCircleRadius+10);
    painter->setPen(Qt::NoPen);


    painter->setBrush(QBrush(QColor(255,10,10)));


    QVector<QPointF> potVec;
    potVec.push_back(topPot);
    potVec.push_back(bottomLeftPot);
    potVec.push_back(bottomRightPot);

    painter->drawPolygon(potVec);



    painter->restore();
}

void MyDashboard::initVariables()
{
    m_outerRadius= width()*2/3;
    m_innerRadius=m_outerRadius/8*7;
    m_coverCircleRadius=m_outerRadius/8*4+10;
    m_colorCircleRadius=m_outerRadius/8*5;
    m_center=rect().center();
    m_lblvalue=0;
    m_currentValue=0;
    m_limitSpeedValue=0;
}


