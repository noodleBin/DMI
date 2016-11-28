/******************************
** Date: 2016/06/23
** Author: noodlebin
** Brief: get and set els->dmi protocol (Message_A.xls suggested by alstom) .h
** Version: 1.0
******************************/


#include <QObject>
#include <QDataStream>
#include <QDebug>

#include "dms_dmi_protocol.h"


DMS_DMI_Protocol::DMS_DMI_Protocol()
{

}

DMS_DMI_Protocol::~DMS_DMI_Protocol()
{

}

void DMS_DMI_Protocol::getDataFromBytes(QByteArray &bytes)
{
    QDataStream readBytes(&bytes,QIODevice::ReadOnly);
    //        readBytes.setByteOrder(QDataStream::LittleEndian);
    readBytes>>this->Version>>this->Length
            >>this->Transmitter_Identity
            >>this->Receiver_Identity>>this->Sequence_number

            >>this->Itf_Ver
            >>this->Sig_Length
            >>this->Src_SSTy
            >>this->Src_Log_ID
            >>this->Src_SSID
            >>this->Dest_SSTy
            >>this->Dest_Log_ID
            >>this->Dest_SSID
            >>this->DateTime
            >>this->Msg_ID
            >>this->Application

            >>this->Signal_ID
            >>this->RTU_ID
            >>this->RTU_Type;

    if(this->Msg_ID==102)
        return;
    readBytes>>this->Signal_Status
            >>this->Bitmap_Length;

    if(this->Bitmap_Length>0)
    {
        this->Bitmap=new quint8[this->Bitmap_Length];
        for(int i=0;i<this->Bitmap_Length;i++)
        {
            readBytes>>this->Bitmap[i];
        }
    }
}

void DMS_DMI_Protocol::setBytesFromData(QByteArray &qsend)
{
    QDataStream sendBytes(&qsend,QIODevice::WriteOnly);
    //    sendBytes.setByteOrder(QDataStream::LittleEndian);  默认大端
    sendBytes<<this->Version;
    sendBytes<<this->Length<<this->Transmitter_Identity<<this->Receiver_Identity
            <<this->Sequence_number

           <<this->Itf_Ver<<this->Sig_Length<<this->Src_SSTy<<this->Src_Log_ID
          <<this->Src_SSID<<this->Dest_SSTy<<this->Dest_Log_ID<<this->Dest_SSID
         <<this->DateTime<<this->Msg_ID<<this->Application


//    sendBytes<<this->Length<<this->Receiver_Identity<<this->Transmitter_Identity
//            <<this->Sequence_number

//           <<this->Itf_Ver<<this->Sig_Length<<this->Dest_SSTy<<this->Dest_Log_ID
//          <<this->Dest_SSID<<this->Src_SSTy<<this->Src_Log_ID<<this->Src_SSID
//         <<this->DateTime<<this->Msg_ID<<this->Application

        <<this->Signal_ID<<this->RTU_ID<<this->RTU_Type;
    if(this->Msg_ID==103)
        return;
    sendBytes<<this->Signal_Status
            <<this->Bitmap_Length;
    if(this->Bitmap_Length>0)
    {
//        qDebug()<<"in simu bitmaplen"<<Bitmap_Length;
        for(int i=0;i<this->Bitmap_Length;i++)
        {
            sendBytes<<Bitmap[i];
//            qDebug()<<"Bitmap["<<i<<"]"<<Bitmap[i];
        }
    }

}

void DMS_DMI_Protocol::freePointer()
{
        if(this->Bitmap_Length>0)
        {
            delete[] this->Bitmap;
            this->Bitmap_Length=0;
        }
}
