/******************************
** Date: 2016/06/23
** Author: noodlebin
** Brief: respond to log write and split
** Version: 1.0
******************************/
#ifndef DMI_LOG_H
#define DMI_LOG_H
#include <QString>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QDateTime>
#include <QObject>
#include "sys/statfs.h"

class DMI_Log:public QObject
{
    Q_OBJECT
signals:
    void aboveVolume(QString);

public:
    DMI_Log(quint64 promotesize,quint64 clearsize,quint64 splitsize);
    quint8 writeLog(QString content);
    bool judgeSizeAboveSize(quint64 sizebyMB);
    quint8 initialLog(QString name);
    void removeLog();
    QStringList findLogsInDirec();
    QString findOldestLog(QStringList files);
    void setVolume(quint64 promotesize=5000,quint64 clearsize=5000,quint64 splitsize=1000);
private:
    QFile qLogfile;
    QTextStream qts;
    quint8 alarmcount;
    quint64 promotesizeMB;
    quint64 clearsizeMB;
    quint64 writecount;
    quint64 m_writecount;


};

#endif // DMI_LOG_H
