#include "TLEevents.h"
#define MAX 65536
#include <QDebug>
#include <QPainterPath>
TLEEvents::TLEEvents(quint8 size, QWidget *parent): QWidget(parent)
{

    m_size=size;
    grid=24;
    xpos = new quint16[50];
    ypos = new quint16[50];
    status = new quint8[50];
    rotation = new quint8[50];
    m_bitmap=new quint8[200];
    display9cubic=false;
    isdisplay_signame=false;
    need_paint=false;
    need_txt=false;
    this->installEventFilter(this);
    this->show();
}

TLEEvents::~TLEEvents()
{
    delete[]   xpos;
    delete[] ypos;
    delete[] status;
    delete[] rotation;
}

void TLEEvents::setvalue(quint8 id,quint8 rtu_id,quint8 status,
                         quint16 bitmaplength,
                         quint8* bitmap)
{

    sigid =id;
    m_rtu_id=rtu_id;
    sigstatus=status;
    m_bitmaplength=bitmaplength;
    for(int i=0;i<m_bitmaplength;i++)
    {
        m_bitmap[i]=bitmap[i];
    }

    if(m_rtu_id==1)
        entryname=map_sigid_name->value(id);
    else
        entryname=map_olcid_name->value(id);
    //    qDebug()<<"signame"<<name;
    if(!map_sigentry->contains(entryname))
    {
        need_paint=false;
        //        qDebug()<<"paint entry"<<need_paint;
        update();
        return;
    }
    entry= map_sigentry->value(entryname);

    if(!map_ViewID->contains(entry.viewid))
    {
        need_paint=false;
        //        qDebug()<<"paint view"<<need_paint;
        update();
        return;
    }
    view= map_ViewID->value( entry.viewid);

    if(!map_Template->contains(view.templateid))
    {
        need_paint=false;
        //        qDebug()<<"paint tepl"<<need_paint;
        update();
        return;
    }
    tplete= map_Template->value( view.templateid);
    siglist=view.signallist;
    olclist=view.LCSlist;
    need_paint=true;

    if(map_View_Texts->contains(entry.viewid))
    {
        need_txt=true;
    }
    else
    {
        need_txt=false;
    }

    update();
}

void TLEEvents::drawShape(QPainter* painter,Shape sh,QString name)
{

    if(name== "Line")
    {

        //                painter.save();
        QString color=sh.list_Attr->value("Color");
        QStringList colors= color.split(" ");

        painter->setPen(QPen( QColor(colors.at(0).toUInt(),
                                     colors.at(1).toUInt(),
                                     colors.at(2).toUInt()),
                              sh.list_Attr->value("LineStyle").toUInt()));

        painter->drawLine(sh.list_Attr->value("StartX").toUInt()*grid,
                          sh.list_Attr->value("StartY").toUInt()*grid,
                          sh.list_Attr->value("EndX").toUInt()*grid,
                          sh.list_Attr->value("EndY").toUInt()*grid);
        //                painter.restore();
    }
    else if(name== "Bezier")
    {
        //                painter.save();
        QString color=sh.list_Attr->value("Color");
        QStringList colors= color.split(" ");

        painter->setPen(QPen( QColor(colors.at(0).toUInt(),
                                     colors.at(1).toUInt(),
                                     colors.at(2).toUInt()),
                              sh.list_Attr->value("LineStyle").toUInt()));

        QPoint begin(sh.list_Attr->value("StartX").toUInt()*grid,
                     sh.list_Attr->value("StartY").toUInt()*grid);
        QPoint end( sh.list_Attr->value("EndX").toUInt()*grid,
                    sh.list_Attr->value("EndY").toUInt()*grid);
        QPoint c1(sh.list_Attr->value("StartX").toUInt()*grid,
                  (sh.list_Attr->value("StartY").toUInt()+
                   sh.list_Attr->value("EndY").toUInt())*grid/2 );
        QPoint c2(sh.list_Attr->value("EndX").toUInt()*grid,
                  (sh.list_Attr->value("StartY").toUInt()+
                   sh.list_Attr->value("EndY").toUInt())*grid/2 );
        QPainterPath pp(begin);
        pp.cubicTo(c1,c2,end);
        painter->drawPath(pp);

    }
    else if(name== "Rect")
    {
        QString brush=sh.list_Attr->value("BrushColor");
        QStringList brushcolors=brush.split(" ");
        painter->setBrush(QColor(brushcolors.at(0).toUInt(),
                                 brushcolors.at(1).toUInt(),
                                 brushcolors.at(2).toUInt()));
        QString color=sh.list_Attr->value("PenColor");
        QStringList colors= color.split(" ");

        painter->setPen(QPen( QColor(colors.at(0).toUInt(),
                                     colors.at(1).toUInt(),
                                     colors.at(2).toUInt()),
                              sh.list_Attr->value("LineStyle").toUInt()));

        painter->drawRect(sh.list_Attr->value("LeftTopX").toUInt()*grid,
                          sh.list_Attr->value("LeftTopY").toUInt()*grid,
                          sh.list_Attr->value("RightBottomX").toUInt()*grid,
                          sh.list_Attr->value("RightBottomY").toUInt()*grid);
        //                for(int j=0;j<sh.list_Attr->size();j++)
        //                    qDebug()<<j<<sh.list_Attr->at(j);
    }
    else if(name== "ARC")
    {
        QString color=sh.list_Attr->value("Color");
        QStringList colors= color.split(" ");

        painter->setPen(QPen( QColor(colors.at(0).toUInt(),
                                     colors.at(1).toUInt(),
                                     colors.at(2).toUInt()),
                              sh.list_Attr->value("LineStyle").toUInt()));

        //        painter->drawRect(QRect(QPoint(sh.list_Attr->value("StartX").toUInt()*grid,
        //                                       sh.list_Attr->value("StartY").toUInt()*grid),
        //                                QPoint(sh.list_Attr->value("EndX").toUInt()*grid,
        //                                       sh.list_Attr->value("EndY").toUInt()*grid)));
        painter->drawArc(QRect(QPoint(sh.list_Attr->value("StartX").toUInt()*grid,
                                      sh.list_Attr->value("StartY").toUInt()*grid),
                               QPoint(sh.list_Attr->value("EndX").toInt()*grid,
                                      sh.list_Attr->value("EndY").toInt()*grid)),
                         sh.list_Attr->value("StartAngle").toInt()*16,
                         sh.list_Attr->value("SpanAngle").toInt()*16);
    }
    else if(name== "Arrow")
    {
        QString color=sh.list_Attr->value("Color");
        QStringList colors= color.split(" ");

        painter->setPen(QPen( QColor(colors.at(0).toUInt(),
                                     colors.at(1).toUInt(),
                                     colors.at(2).toUInt()),
                              sh.list_Attr->value("LineStyle").toUInt()));

        QString brush=sh.list_Attr->value("BrushColor");
        QStringList brushcolors=brush.split(" ");
        painter->setBrush(QColor(brushcolors.at(0).toUInt(),
                                 brushcolors.at(1).toUInt(),
                                 brushcolors.at(2).toUInt()));
        quint16 x=sh.list_Attr->value("X").toUInt()*grid;
        quint16 y=sh.list_Attr->value("Y").toUInt()*grid;
        qint16 rotate=sh.list_Attr->value("Rotate").toInt();
        //        qDebug()<<"ang"<<x<<y<<rotate;
        painter->save();
        painter->translate(x,y);
        painter->rotate(-rotate);
        QPoint points[3];
        points[0]=(QPoint(0,0+0.5*grid));
        points[1]=(QPoint(0,0-0.5*grid));
        points[2]=(QPoint(0+grid,0));
        painter->drawPolygon(points,3);

        painter->restore();
    }
}

void TLEEvents::paintEvent(QPaintEvent *e)
{

    Q_UNUSED(e)

    QPainter painter(this);

    painter.setRenderHints(QPainter::Antialiasing
                           |QPainter::TextAntialiasing|
                           QPainter::SmoothPixmapTransform|
                           QPainter::HighQualityAntialiasing);

    //    painter.setRenderHints(QPainter::Antialiasing|QPainter::TextAntialiasing|QPainter::SmoothPixmapTransform);
    painter.setBrush(QColor(73,86,119));
    painter.drawRect(0,0,this->width(),this->height());


    draw18Grid(&painter);
    if(need_paint)
    {
        painter.save();
        if(entry.rotate!=0)
        {
            //            qDebug()<<entry.rotate<<entry.viewid;
            //            painter.rotate(entry.rotate);
            painter.translate(width()/2,height()/2);
            //

            painter.rotate(entry.rotate);
            painter.translate(-width()/2,-height()/2);

        }

        drawTemplate(&painter);


        QByteArray bytes((char*)m_bitmap,m_bitmaplength);

        //        for(int i=0;i<m_bitmaplength;i++)
        //        {
        //            qDebug()<<"bytes["<<i<<"]"<<(quint8)bytes.at(i);
        //        }


        drawAllSignals(&painter);
        drawAllRoutes(&painter);
        drawSigName(&painter);
        painter.restore();


        drawTram(&painter);
        drawTxt(&painter);



    }

    painter.end();

}

void TLEEvents::drawRoute(QString signame,quint8 status,QPainter *painter)
{
    if(!map_Route->contains(signame))
        return;
    QMap<QString,QList<Shape>*>* m=  map_Route->value(signame);
    QList<Shape>* s;
    painter->setPen(QPen(QColor(Qt::green),4));
    switch(status)
    {
    case 2:
        if(m->contains("Permiss"))
        {
            s =   m->value("Permiss");
            for(int i=0;i<s->size();i++)
            {
                drawShape(painter,s->at(i),s->at(i).name);
                //            painter->drawLine(0,0,500,500);
            }
        }
        break;
    case 3:
        if(m->contains("Left"))
        {
            s=   m->value("Left");
            for(int i=0;i<s->size();i++)
            {
                drawShape(painter,s->at(i),s->at(i).name);
            }
        }
        break;
    case 4:
        if(m->contains("Right"))
        {
            s=   m->value("Right");
            for(int i=0;i<s->size();i++)
            {
                drawShape(painter,s->at(i),s->at(i).name);
            }
        }
        break;
    }
}

void TLEEvents::drawAllSignals(QPainter *painter)
{
    QList<SignalInfo> *sl;
    if(m_rtu_id==1)
        sl=siglist;
    else
        sl=olclist;
    for(int i=0;i<sl->size();i++)
    {
        SignalInfo s=sl->at(i);
        painter->save();

        if(s.name==entryname)
        {
            drawSignal(s.x,
                       s.y,
                       s.Rotate,sigstatus,
                       painter);

        }
        else
        {
            quint8 status=parserBitMap(s);

            drawSignal(s.x,
                       s.y,
                       s.Rotate,status,
                       painter);

        }

        painter->restore();

    }
}

void TLEEvents::drawAllRoutes(QPainter *painter)
{
    QList<SignalInfo> *sl;
    if(m_rtu_id==1)
        sl=siglist;
    else
        sl=olclist;
    for(int i=0;i<sl->size();i++)
    {
        SignalInfo s=sl->at(i);


        painter->save();


        if(s.name==entryname)
        {

            drawRoute(s.name,sigstatus,
                      painter);
        }
        else
        {
            quint8 status=parserBitMap(s);
            drawRoute(s.name,status,painter);
        }

        painter->restore();

    }
}

void TLEEvents::draw18Grid(QPainter *painter)
{
    if(display9cubic)
    {
        painter->setPen(QPen( QColor(220,220,220),1,Qt::DotLine));

        for(int i=0;i<19;i++)
            painter->drawLine(0,i*grid,width(),i*grid);
        for(int i=0;i<19;i++)
            painter->drawLine(i*grid,0,i*grid,height());
    }
}

void TLEEvents::drawTemplate(QPainter *painter)
{
    if(tplete->size()>0)
    {

        for(int i=0;i<tplete->size();i++)
        {
            Shape sh = tplete->at(i);
            QString name=sh.name;

            drawShape(painter,sh,name);

        }
    }
}

void TLEEvents::drawTram(QPainter* painter)
{
    QRect rect=QRect(entry.tramx*grid-7,entry.tramy*grid,16,66);
    painter->drawPixmap(rect,QPixmap("res/Tram_Tracklayout.png"));
}

void TLEEvents::drawTxt(QPainter* painter)
{
    if(need_txt)
    {
        QList<TextInfo>* list_txt=map_View_Texts->value(entry.viewid);
        for(int i=0;i<list_txt->size();i++)
        {
            TextInfo t=list_txt->at(i);
            QFont f(t.Font,t.Size);

            painter->setFont(f);



            QString color=t.Color;
            QStringList colors= color.split(" ");

            painter->setPen(QPen( QColor(colors.at(0).toUInt(),
                                         colors.at(1).toUInt(),
                                         colors.at(2).toUInt()),
                                  2));

            painter->save();


            painter->translate(t.x*grid,t.y*grid);

            if(t.Rotate>0)
            {

                painter->rotate(t.Rotate);


            }
            painter->drawText(QRect(0,0,5*grid,5*grid),t.txt);
            painter->restore();
        }

    }
}

quint8 TLEEvents::parserBitMap(SignalInfo s)
{
    SignalBit b;
    if(m_rtu_id==1)
        b= map_Signal->value(s.name);
    else
        b= map_OLC->value(s.name);

    quint8 status;

    quint8 left = (m_bitmap[b.left/8]);
    left&=1<<b.left%8;
    quint8 right = (m_bitmap[b.right/8]);
    right&=1<<b.right%8;
    quint8 permiss = (m_bitmap[b.permiss/8]);
    permiss&=1<<b.permiss%8;
    quint8 restric = (m_bitmap[b.restric/8]);
    restric&=1<<b.restric%8;
    if(b.restric!=0&&restric)
    {
        status=1;
    }
    else if(b.permiss!=0&&permiss)
    {
        status=2;
    }
    else   if(b.left!=0&&left)
    {
        status=3;
    }
    else   if(b.right!=0&&right)
    {
        status=4;
    }
    else
    {
        status=1;
    }
    return status;
}

void TLEEvents::drawSigName(QPainter* painter)
{
    if(isdisplay_signame)
    {
        QList<SignalInfo>* s;
        if(m_rtu_id==1)
            s=siglist;
        else
            s=olclist;
        for(int i=0;i<s->size();i++)
        {
            SignalInfo si=s->at(i);

            painter->setPen(QPen(QColor(Qt::black),1));
            //                    qDebug()<<s.name<<s.Rotate;
            switch(si.Rotate)
            {
            case 0:
                painter->drawText(QRect((si.x-1)*grid,(si.y-1)*grid,width(),grid),Qt::AlignLeft,si.name);
                break;
            case 90:
                painter->drawText(QRect((si.x)*grid+5,(si.y)*grid-7,width(),grid),Qt::AlignLeft,si.name);
                break;
            case -90:
                painter->drawText(QRect((si.x-1)*grid-20,(si.y)*grid-8,width(),grid),Qt::AlignLeft,si.name);
                break;
            case 180:
                painter->drawText(QRect((si.x-1)*grid,(si.y+1)*grid-15,width(),grid),Qt::AlignLeft,si.name);
                break;

            }


        }
    }
}

void TLEEvents:: drawSignal(quint8 x,quint8 y,qint16 rotate,quint8 status,QPainter *painter)
{

    painter->translate(x*grid,y*grid);
    painter->rotate(rotate);
    painter->setBrush(Qt::black);
    painter->setPen(QPen(Qt::black,2));
    painter->drawEllipse(0-grid/2,0,grid,grid);
    painter->drawLine(0,grid,0,grid+grid/2);
    painter->drawLine(0-grid/2,grid+grid/2,grid/2,grid+grid/2);

    switch(status)
    {
    case 1:
        painter->setPen(QPen(QColor(Qt::red),6));
        painter->drawLine(0-grid/2+4,grid/2,grid/2-4,grid/2);
        break;
    case 2:
        painter->setPen(QPen(QColor(Qt::green),6));
        painter->drawLine(0,0+4,0,grid-4);
        break;
    case 3:
        painter->setPen(QPen(QColor(Qt::yellow),6));
        painter->drawLine(0-grid/4,grid/4,grid/4,3*grid/4);
        break;
    case 4 :
        painter->setPen(QPen(QColor(Qt::yellow),6));
        painter->drawLine(grid/4,grid/4,0-grid/4,3*grid/4);
        break;
    }
    //    painter->drawLine(0,0,2*grid,2*grid);
    //    painter->restore();
}

QSize TLEEvents::sizeHint() const
{
    if(m_size==1)
    {
        return QSize(413,407);
    }
    else if(m_size==2)
    {
        return QSize(300,300);
    }
    else if(m_size==3)
    {
        return QSize(432,432);
    }
    return QSize(100,100);
}

void TLEEvents::drawArrow(QPainter *painter, QPoint &end,QColor color)
{
    QPoint p1,p2,p3,p4,p5,p6;
    QPoint ps[6];
    p1= QPoint(end.x()-10,end.y()-10);
    p2=        QPoint(end.x(),end.y()-25);
    p3=       QPoint(end.x()+10,end.y()-10);


    p4= QPoint(end.x()-10,end.y()+15);
    p5=        QPoint(end.x(),end.y());
    p6=       QPoint(end.x()+10,end.y()+15);

    ps[0]=p1;
    ps[1]=p2;
    ps[2]=p3;
    ps[3]=p6;
    ps[4]=p5;
    ps[5]=p4;
    painter->setPen(QPen(color,1));
    painter->setBrush(color);
    painter->drawPolygon(ps,6);
}



void TLEEvents::setMap(QMap<quint8, QString> *mapsigidname, QMap<quint8, QString> *mapolcidname, QMap<QString, SignalBit> *mapsignal, QMap<QString, SignalBit> *mapolc, QMap<quint16, QList<Shape> *> *mapTemplate, QMap<quint16, View> *mapViewID, QMap<QString, Entry> *mapsigentry, QMap<QString, QMap<QString, QList<Shape> *> *> *mapRoute, QMap<quint16, QList<TextInfo> *> *mapViewTexts)
{
    map_sigid_name=mapsigidname;
    map_olcid_name=mapolcidname;
    map_Signal=mapsignal;
    map_OLC=mapolc;
    map_Template=mapTemplate;
    map_ViewID=mapViewID;
    map_sigentry=mapsigentry;
    map_Route=mapRoute;
    map_View_Texts=mapViewTexts;
}



