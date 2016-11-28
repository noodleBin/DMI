/******************************
** Date: 2016/06/23
** Author: noodlebin
** Brief: respond to log write and split
** Version: 1.0
******************************/
#include "DMILog.h"
#include <QDebug>
#define KB 1024.0                                               // 2^10
#define MB 1048576.0                                        // 2^20
#define GB 1073741824.0                                     // 2^30
DMI_Log::DMI_Log(quint64 promotesize, quint64 clearsize, quint64 splitsize)
{
    alarmcount=0;
    promotesizeMB=promotesize;
    clearsizeMB=clearsize;
    m_writecount=splitsize*1000;
}

quint8 DMI_Log::writeLog(QString content)
{

    if(writecount>=m_writecount) //size from Byte to MB
    {

        QString logname=QDir::currentPath()+"/Log/"+QDateTime::currentDateTime().toString("yyyy-MM-dd_hh:mm:ss.zzz")+".txt";
        if(!initialLog(logname))
            return 0;
    }



    if(!judgeSizeAboveSize(clearsizeMB))
    {
        emit aboveVolume(tr("日志剩余空间不足 ")+QString::number(clearsizeMB)+tr("M")+tr(" 已清理"));
        alarmcount=0;
        QStringList files= findLogsInDirec();
        if(files.count()>0)
        {
            QString fileToDel=findOldestLog(files);
            QFile::remove(fileToDel);
        }
    }

    qts<<QDateTime::currentDateTime().toString("yyyy-MM-dd_hh:mm:ss.zzz")<<" "<<" "<<content<<endl;
//      qts<<Tool::timeConvertDisplay( .toString("yyyy-MM-dd_hh:mm:ss.zzz")<<" "<<" "<<content<<endl;
    writecount++;
    return 1;
}


bool DMI_Log::judgeSizeAboveSize(quint64 sizebyMB)
{
    struct statfs diskinfo;
    char* path = (QDir::currentPath()+"/Log/").toUtf8().data();
    statfs(path,&diskinfo);

    quint64 blocksize = diskinfo.f_bsize;                   // 每个block里包含的字节数


    quint64 availableDisk = diskinfo.f_bavail * blocksize; // 可用空间大小

    //    qDebug()<<"availbldisk"<<availableDisk/MB;
    if(availableDisk/MB > sizebyMB)
        return true;
    else
        return false;
}



QStringList DMI_Log::findLogsInDirec()
{
    QDir dir(QDir::currentPath()+"/Log/");
    QStringList Filenamedes;
    QFileInfoList files = dir.entryInfoList();
    for(int i=0;i<files.count();i++)
    {
        QString filename=files[i].fileName();
        if(filename=="."||filename=="..")
            continue;
        Filenamedes.append(QDir::currentPath()+"/Log/"+filename);
    }
    return Filenamedes;
}

QString DMI_Log::findOldestLog(QStringList files)
{

    int oldestdifference=0;
    int onedaydifference=0;
    QString fileToDel=files[0];
    for(int i=0;i<files.count();i++)
    {
        QFileInfo tmpfileinfo=QFileInfo(files[i]);


        QDateTime tmp=tmpfileinfo.lastModified();

        onedaydifference=tmp.daysTo(QDateTime::currentDateTime());
        if(onedaydifference>oldestdifference)
        {
            oldestdifference=onedaydifference;
            fileToDel=files[i];
        }

    }
    return fileToDel;
}

void DMI_Log::setVolume(quint64 promotesize, quint64 clearsize, quint64 splitsize)
{
    promotesizeMB=promotesize;
    clearsizeMB=clearsize;
    m_writecount=splitsize*1000;
}

quint8 DMI_Log::initialLog(QString name)
{
    writecount=0;
    removeLog();
    QDir dir(QDir::current());
    dir.mkdir("Log");
    if(qLogfile.isOpen())
    {
        qLogfile.close();
    }

    qLogfile.setFileName(name);

    if(!qLogfile.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Append))
    {
        return 0    ;

    }
    qts.setDevice(&qLogfile);
    return 1;
}

void DMI_Log::removeLog()
{
    QStringList files=findLogsInDirec();
    QStringList rmfilenames;
    for(int i=0;i<files.count();i++)
    {

        QFileInfo tmpfileinfo=QFileInfo(files[i]);

        QDateTime tmp=tmpfileinfo.lastModified();

        if(tmp.daysTo(QDateTime::currentDateTime())>7)
        {
            rmfilenames.append(files[i]);
        }

        //        qDebug()<<"lastmodify"<<tmp
        //               <<"lastread"<<tmpfileinfo.lastRead()
        //              <<"created"<<tmpfileinfo.created()
        //             <<"currenttime"<<QDateTime::currentDateTime();

    }
    for(int i=0;i<rmfilenames.count();i++)
    {
        QFile::remove(rmfilenames[i]);
    }
}

