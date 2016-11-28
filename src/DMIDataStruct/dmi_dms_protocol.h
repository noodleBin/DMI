/******************************
** Date: 2016/06/23
** Author: noodlebin
** Brief: get and set dmi->els protocol (Message_A.xls suggested by alstom) .h
** Version: 1.0
******************************/
#ifndef DMI_DMS_PROTOCOL_H
#define DMI_DMS_PROTOCOL_H

#include <QObject>
#include <QDataStream>
#include <time.h>

#pragma pack(push)
#pragma pack(1)
struct DMI_DMS_Protocol
{
public:
    explicit DMI_DMS_Protocol();
    ~ DMI_DMS_Protocol();
    void clearAll();
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
    quint64 Sequence_number;


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

};

#pragma pack(pop)

#endif // DMI_DMS_PROTOCOL_H
