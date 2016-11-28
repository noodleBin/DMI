/******************************
** Date: 2016/06/23
** Author: noodlebin
** Brief: respond to sms write and split
** Version: 1.0
******************************/
#include "DMISMS.h"
#define KB 1024.0                                               // 2^10
#define MB 1048576.0                                        // 2^20
#define GB 1073741824.0                                     // 2^30
DMISMS::DMISMS(quint64 promotesize, quint64 clearsize, quint64 splitsize)
{
    alarmcount=0;
    promotesizeMB=promotesize;
    clearsizeMB=clearsize;
    m_writecount=splitsize*1000;

}

quint8 DMISMS::writeSMS(QString content)
{

    if(writecount>m_writecount) //size from Byte to MB
    {
        QString smsname=QDir::currentPath()+"/SMS/"+QDateTime::currentDateTime().toString("yyyy-MM-dd_hh:mm:ss.zzz")+".txt";
        if(!initialSMS(smsname))
            return 0;
    }

    if(!judgeSizeAboveSize(clearsizeMB))
    {
        emit aboveVolume(tr("短消息剩余空间不足 ")+QString::number(clearsizeMB)+tr("M")+tr(" 已清理"));
        alarmcount=0;
        QStringList files= findSMSInDirec();
        if(files.count()>0)
        {
            QString fileToDel=findOldestSMS(files);
            QFile::remove(QDir::currentPath()+"/SMS/"+fileToDel);
        }
    }


    qts<<QDateTime::currentDateTime().toString("yyyy-MM-dd_hh:mm:ss.zzz")<<" "<<content<<endl;
    writecount++;
    qts.flush();
    qSMSfile.flush();
    return 1;

}

bool DMISMS::judgeSizeAboveSize(quint64 sizebyMB)
{
    struct statfs diskinfo;
    char* path = (QDir::currentPath()+"/SMS/").toUtf8().data();
    statfs(path,&diskinfo);

    quint64 blocksize = diskinfo.f_bsize;                   // 每个block里包含的字节数
    quint64 availableDisk = diskinfo.f_bavail * blocksize; // 可用空间大小

    //    qDebug()<<availableDisk/MB<<sizebyMB<<"MB";
    if(availableDisk/MB > sizebyMB)
        return true;
    else
        return false;
}

void DMISMS::setVolume(quint64 promotesize, quint64 clearsize, quint64 splitsize)
{
    promotesizeMB=promotesize;
    clearsizeMB=clearsize;
    m_writecount=splitsize*1000;
}

QStringList DMISMS::findSMSInDirec()
{
    QDir dir(QDir::currentPath()+"/SMS/");
    QFileInfoList files = dir.entryInfoList();
    QStringList filenames;
    for(int i=0;i<files.count();i++)
    {
        QString filename=files[i].fileName();
        if(filename=="."||filename=="..")
            continue;
        filenames.append(QDir::currentPath()+"/SMS/"+filename);
    }
    return filenames;
}

QString DMISMS::findOldestSMS(QStringList files)
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

QString DMISMS::getSMSFileName()
{
    return qSMSfile.fileName();
}


quint8 DMISMS::initialSMS(QString name)
{
    writecount=0;

    removeOldSMSFiles();

    QDir dir(QDir::current());
    dir.mkdir("SMS");
    if(qSMSfile.isOpen())
    {
        qSMSfile.close();
    }
    qSMSfile.setFileName(name);

    if(!qSMSfile.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Append))
    {
        return 0;
    }
    qts.setDevice(&qSMSfile);
    return 1;
}

void DMISMS::removeOldSMSFiles()
{
    QStringList files=findSMSInDirec();
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
        //  qDebug()<<rmfilenames[i];
        QFile::remove(rmfilenames[i]);
    }
}

