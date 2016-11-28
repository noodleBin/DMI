/******************************
** Date: 2016/06/23
** Author: noodlebin
** Brief: get and set els->dmi protocol (Message_A.xls suggested by alstom) .h
** Version: 1.0
******************************/
#ifndef DMS_DMI_PROTOCOL_H
#define DMS_DMI_PROTOCOL_H

#include <QObject>
#include <QDataStream>
#include <time.h>

#pragma pack(push)
#pragma pack(1)
struct DMS_DMI_Protocol
{
public:
    DMS_DMI_Protocol();
    ~DMS_DMI_Protocol();

public:
    void getDataFromBytes(QByteArray& bytes);
    void setBytesFromData(QByteArray& qsend);
    void freePointer();
public:

    //Redundancy
    quint8 Version;
    quint16  Length ;
    quint16 Transmitter_Identity;
    quint16 Receiver_Identity;
    quint32 Sequence_number;


    //SIG
    quint8 Itf_Ver;
    quint16 Sig_Length;
    quint8 Src_SSTy;
    quint8 Src_Log_ID;
    quint8 Src_SSID;
    quint8 Dest_SSTy;
    quint8 Dest_Log_ID;
    quint8 Dest_SSID;
    quint64 DateTime;
    quint8 Msg_ID;
    quint8 Application;

    //Function
    quint16 Signal_ID;
    quint16 RTU_ID;
    quint8 RTU_Type;
    quint8 Signal_Status;
    quint16 Bitmap_Length;
    quint8* Bitmap;
};

#pragma pack(pop)

#endif // DMS_DMI_PROTOCOL_H
