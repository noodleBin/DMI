/******************************
** Date: 2016/06/23
** Author: noodlebin
** Brief: Paint the Dashboard in 10.4 display screen .h
** Version: 1.0
******************************/
#ifndef MYDASHBOARD_H
#define MYDASHBOARD_H

#include <QWidget>
#include <QTimer>
#include <QPainter>



#define LONG 21
#define OK 10
#define SHORT 8
#define SPACE 5
#define ANGLE 10

class MyDashboard : public QWidget
{
    Q_OBJECT
public:
    explicit MyDashboard(quint8 size, QWidget *parent = 0);

signals:

public slots:
    void setValue(quint8 curvalue,quint8 limitvalue,quint8 lblvalue);


protected:
    void paintEvent(QPaintEvent *);
    QSize sizeHint() const;


private:
    void drawOuterCircle(QPainter* painter);
    void drawInnerCircle(QPainter* painter);
    void drawMark(QPainter* painter);
    void drawCoverCircle(QPainter* painter);
    void drawColorPie(QPainter* painter);
    void drawIndicator(QPainter* painter);
    void drawCoverBall(QPainter* painter);
    void resetVariables(QPainter* painter);
    void drawTextRect(QPainter* painter);
    void drawLimitSpeed(QPainter *painter);

private:
    qreal m_outerRadius;
    qreal m_innerRadius;
    qreal m_coverCircleRadius;
    qreal m_colorCircleRadius;
    qreal m_coverBallRadius;
    QPointF m_center;
    QRectF m_colorCircleRect;
    quint8 m_lblvalue;

    quint8 m_currentValue;
    quint8 m_limitSpeedValue;
    quint8 m_size;



private:
    void initVariables();

};

#endif // MYDASHBOARD_H
