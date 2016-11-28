#ifndef TLEEVENTS_H
#define TLEEVENTS_H

#include <QPainter>
#include <QFrame>
#include <QEvent>
#include <QKeyEvent>
#include "tlepublicvariables.h"

class TLEEvents : public QWidget
{
    Q_OBJECT
public:
    explicit TLEEvents(quint8 size, QWidget *parent = 0);
    ~TLEEvents();

    void setvalue(quint8 id, quint8 rtu_id, quint8 status, quint16 bitmaplength, quint8 *bitmap);
    bool display9cubic;
    bool isdisplay_signame;



protected:
    void paintEvent(QPaintEvent *);
    QSize sizeHint() const;



private:
    quint8 image,signals_count;
    quint16 *xpos,*ypos;
    quint8 m_size,*status,*rotation;

    qint16 arrow_x,arrow_y;

    bool need_paint,need_txt;

    quint8 sigid,sigstatus;
    quint8 m_rtu_id;
    quint16 m_bitmaplength;
    quint8* m_bitmap;

    float grid;




    void drawArrow(QPainter*painter, QPoint &end, QColor color);
    //    void drawArrow(QPainter*painter, QPoint &p1, QPoint &p2, QPoint &p3, QColor &color);




    QList<Shape>* tplete;
    View view;

    QList<SignalInfo> *siglist;
    QList<SignalInfo> *olclist;

    Entry entry;
    QString entryname;

    void drawSignal(quint8 x,quint8 y,qint16 rotate,quint8 status,QPainter *painter);
    void drawShape(QPainter *, Shape, QString name);
    void drawRoute(QString signame, quint8 status, QPainter *painter);

    void drawAllSignals(QPainter* painter);
    void drawAllRoutes(QPainter* painter);
    void draw18Grid(QPainter* painter);
    void drawTemplate(QPainter *painter);
    void drawTram(QPainter *painter);
    void drawTxt(QPainter *painter);
    quint8 parserBitMap(SignalInfo s);
    void drawSigName(QPainter *painter);

    QMap<quint8,QString> *map_sigid_name;
    QMap<quint8,QString> *map_olcid_name;
    QMap<QString,SignalBit> *map_Signal;
    QMap<QString,SignalBit> *map_OLC;
    QMap<quint16,QList<Shape>* > *map_Template;
    QMap<quint16,View> *map_ViewID;
    QMap<QString,Entry> *map_sigentry;
    QMap<QString,QMap<QString,QList<Shape>*>*>* map_Route;
    QMap<quint16,QList<TextInfo>*> *map_View_Texts;
    /**********end***********/

public:

    void setMap(QMap<quint8, QString> *mapsigidname,
                QMap<quint8, QString> *mapolcidname,
                QMap<QString, SignalBit> *mapsignal,
                QMap<QString, SignalBit> *mapolc,
                QMap<quint16, QList<Shape> *> *mapTemplate,
                QMap<quint16, View> *mapViewID,
                QMap<QString, Entry> *mapsigentry,
                QMap<QString,QMap<QString,QList<Shape>*>*>* mapRoute,
                QMap<quint16,QList<TextInfo>*> *mapViewTexts);


};





#endif // TLEEVENTS_H


