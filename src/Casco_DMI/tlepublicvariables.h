#ifndef TLEPUBLICVARIABLES
#define TLEPUBLICVARIABLES
#include <QMap>
struct SignalBit
{
    quint8 left;
    quint8 right;
    quint8 permiss;\
    quint8 restric;
};

struct Shape
{
    QString name;
    QMap<QString,QString>* list_Attr;
};

struct SignalInfo
{
    QString name;
    quint8 x;
    quint8 y;
    qint16 Rotate;
};

struct View
{
    quint8 templateid;
    QString name;
    QList<SignalInfo>* signallist;
    QList<SignalInfo>* LCSlist;
};

struct Entry
{
    quint8 viewid;
    qint16 rotate;
    quint8 tramx;
    quint8 tramy;
};

struct TextInfo
{
    QString txt;
    quint8 x;
    quint8 y;
    quint8 Size;
    QString Color;
    QString Font;
    qint16 Rotate;
};
#endif // TLEPUBLICVARIABLES

