/******************************
** Date: 2016/06/23
** Author: noodlebin
** Brief: paint the geo events
** Version: 1.0
******************************/
#ifndef MYGEOEVENTS_H
#define MYGEOEVENTS_H

#include <QPainter>
#include <QFrame>

class MyGeoEvents : public QWidget
{
    Q_OBJECT
public:
    explicit MyGeoEvents(quint8 size, QWidget *parent = 0);
    void setvalue(quint8 number,quint8* id,quint8* output,quint16* distobegin, quint16* distoend);


protected:
    void paintEvent(QPaintEvent *);
    QSize sizeHint() const;


private:
    quint8 m_number;
    quint8* m_eventid;
    quint8* m_outputvalue;
    quint16* m_distobegin;
    quint16* m_distoend;
    quint8 m_speed; //limitspeed in no pan zone
    bool islimitspeed;
    bool ispanto;
    quint8 m_size; //1 indicate 7ch 2 indicate 10ch
    bool isrefresh;

    void   drawEvent1(QPainter* painter,quint8 output,quint16 begin,quint16 end);
    void   drawEvent2(QPainter* painter,quint8 output,quint16 begin,quint16 end);
    void   drawEvent3(QPainter* painter,quint8 output,quint16 begin,quint16 end);
    void drawspeed(QPainter* painter,quint8 speed);
    void drawCar(QPainter* painter);

};

#endif // MYGEOEVENTS_H
