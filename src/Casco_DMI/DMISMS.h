/******************************
** Date: 2016/06/23
** Author: noodlebin
** Brief: respond to sms write and split
** Version: 1.0
******************************/
#ifndef DMISMS_H
#define DMISMS_H
#include <QString>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QDateTime>
#include <QDebug>
#include "sys/statfs.h"
#include <QObject>

class DMISMS:public QObject
{
    Q_OBJECT

signals:
    void aboveVolume(QString);
public:
    DMISMS(quint64 promotesize, quint64 clearsize, quint64 splitsize);
    quint8 writeSMS(QString content);
    bool judgeSizeAboveSize(quint64 sizebyMB);
    void setVolume(quint64 promotesize=5000, quint64 clearsize=5000, quint64 splitsize=1000);
    quint8 initialSMS(QString name);
    void removeOldSMSFiles();
    QStringList findSMSInDirec();
    QString getSMSFileName();
    QString findOldestSMS(QStringList files);
private:
    QFile qSMSfile;
    QTextStream qts;
    quint8 alarmcount;
    quint64 promotesizeMB;
    quint64 clearsizeMB;
    quint64 writecount;
    quint64 m_writecount;
};

#endif // DMISMS_H



