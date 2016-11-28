/******************************
** Date: 2016/06/23
** Author: noodlebin
** Brief: get and set dmi->els protocol (Message_A.xls suggested by alstom) .cpp
** Version: 1.0
******************************/
#include "dmi_els_protocol.h"
#include <QDebug>

DMI_ELS_Protocol::DMI_ELS_Protocol()
{

    stepOne();
    this->DMI_Message_Number=0;
}

void DMI_ELS_Protocol::resetDefault()
{
    //    this->ELS_Mode_Selection=0;
//    this->Schedule_Id=-1;
//    this->Service_Id=-1;
//    this->Trip_Id=-1;
//    this->Path_Id=-1;
//    this->Destination_Id=-1;
//    this->Time_Shift_Request=0;
}

void DMI_ELS_Protocol::stepOne()
{
    //Pegasus Header
    Message_Format_Version=0;
    //    DMI_Message_Number=0 ;
    DMI_Message_Time_Stamp=0;

    //DMI Status
    DMI_Status=1;
    Display_Status=0;

    //Service Data
    Driver_Id=-1;
    Schedule_Id=-1;
    Service_Id=-1;
    Trip_Id=-1;
    Path_Id=-1;
    Destination_Id=-1;
    Manual_Location_Id=-1;
    Manual_Time_Update=-1;
    Manual_Time_Validity=0;

    //Crossing Priority
    Crossing_Priority_Request=0;

    //Route Request
    RR_Left_Button=0;
    RR_Right_Button=0;
    RR_Straight_Button=0;

    //Mission Management
    ELS_Mode_Selection=0;
    Time_Shift_Request=0;

    //SMS To OCC Setting
    OCC_Message_Number=-1;
    OCC_Message_Length=0;

    //SMS_To_OSS Setting
    OSS_Message_Number=-1;
    OSS_Message_Length=0;


    //SMS To Driver Report
    Driver_Message_Number=-1;
    DMI_DMS_Data_Size=0;
}

void DMI_ELS_Protocol::stepTwo()
{
    //Pegasus Header
    Message_Format_Version=0x12;
    //    DMI_Message_Number=0 ;
    time_t now;
    time(&now);
    DMI_Message_Time_Stamp=now;



    //DMI Status
    DMI_Status=0;
    Display_Status=1;

    //Service Data
    Driver_Id=0x1234;
    Schedule_Id=0x2345;
    Service_Id=0x3456;
    Trip_Id=0x4567;
    Path_Id=0x5678;
    Destination_Id=0x6789;
    Manual_Location_Id=0x789A;
    Manual_Time_Update=now;
    Manual_Time_Validity=0;

    //Crossing Priority
    Crossing_Priority_Request=1;

    //Route Request
    RR_Left_Button=0;
    RR_Right_Button=1;
    RR_Straight_Button=0;

    //Mission Management
    ELS_Mode_Selection=2;
    Time_Shift_Request=1;

    //SMS To OCC Setting
    OCC_Message_Number=0x1234;
    OCC_Message_Length=20;


    OCC_Message_Text = new quint8[OCC_Message_Length];
    quint8 tmp=0x01;
    for(int i=0;i<OCC_Message_Length;i++)
    {
        OCC_Message_Text[i]=tmp+i;
    }

    //SMS To OSS Setting
    OSS_Message_Number=0x3456;
    OSS_Message_Length=20;


    OSS_Message_Text = new quint8[OSS_Message_Length];
    int tmp2=0x01;
    for(int i=0;i<OSS_Message_Length;i++)
    {
        OSS_Message_Text[i]=tmp2+i;
        //        qDebug()<<OSS_Message_Text[i]<<endl;
    }

    //SMS To Driver Report
    Driver_Message_Number=0x5678;
}

void DMI_ELS_Protocol::stepThree()
{
    //Pegasus Header
    Message_Format_Version=0xff;
    //    DMI_Message_Number=0 ;
    time_t now;
    time(&now);
    DMI_Message_Time_Stamp=0xffffffffffffffff;



    //DMI Status
    DMI_Status=1;
    Display_Status=1;

    //Service Data
    Driver_Id=0x7fff;
    Schedule_Id=0x7fff;
    Service_Id=0x7fff;
    Trip_Id=0x7fff;
    Path_Id=0x7fff;
    Destination_Id=0x7fff;
    Manual_Location_Id=0x7fff;
    Manual_Time_Update=0xffffffffffffffff;
    Manual_Time_Validity=1;

    //Crossing Priority
    Crossing_Priority_Request=1;

    //Route Request
    RR_Left_Button=1;
    RR_Right_Button=1;
    RR_Straight_Button=1;

    //Mission Management
    ELS_Mode_Selection=3;
    Time_Shift_Request=1;

    //SMS To OCC Setting
    OCC_Message_Number=0x7fff;
    OCC_Message_Length=140;


    OCC_Message_Text = new quint8[OCC_Message_Length];
    int tmp=0x01;
    for(int i=0;i<OCC_Message_Length;i++)
    {
        OCC_Message_Text[i]=tmp+i;
        //        qDebug()<<OCC_Message_Text[i]<<endl;
    }

    //SMS To OSS Setting
    OSS_Message_Number=0x7fff;
    OSS_Message_Length=140;


    OSS_Message_Text = new quint8[OSS_Message_Length];
    int tmp2=0x01;
    for(int i=0;i<OSS_Message_Length;i++)
    {
        OSS_Message_Text[i]=tmp2+i;
        //        qDebug()<<OSS_Message_Text[i]<<endl;
    }

    //SMS To Driver Report
    Driver_Message_Number=0x7fff;
}

void DMI_ELS_Protocol::freePointer()
{
#ifdef Baseline_2_0
    if(this->DMI_DMS_Data_Size>0)
        delete[] this->DMI_DMS_Data;
#endif
    if(this->OCC_Message_Length>0)
        delete[] this->OCC_Message_Text;   //释放内存
    if(this->OSS_Message_Length>0)
        delete[] this->OSS_Message_Text;
}

void DMI_ELS_Protocol::clearAll()
{
    Message_Format_Version=0;


    //DMI Status
    DMI_Status=1;
    Display_Status=1;

    //Service Data
    Driver_Id=-1;
    Schedule_Id=-1;
    Service_Id=-1;
    Trip_Id=-1;
    Path_Id=-1;
    Destination_Id=-1;
    Manual_Location_Id=-1;
    Manual_Time_Update=-1;

    //Crossing Priority
    Crossing_Priority_Request=0;

    //Route Request
    RR_Left_Button=0;
    RR_Right_Button=0;
    RR_Straight_Button=0;

    //Mission Management
    ELS_Mode_Selection=0;
    Time_Shift_Request=0;


    //Driver SMS 这部分不在本版基线中
    OCC_Message_Number = -1;
    OCC_Message_Length = 0;

    //SMS_To_OSS_Setting
    OSS_Message_Number = -1;
    OSS_Message_Length = 0;

    //SMS_To_Driver_Report
    Driver_Message_Number = -1;
}

void DMI_ELS_Protocol::getDataFromBytes(QByteArray &bytes)
{
    QDataStream readBytes(&bytes,QIODevice::ReadOnly);
    //    readBytes.setByteOrder(QDataStream::LittleEndian);
    readBytes>>this->Message_Format_Version>>this->DMI_Message_Number
            >>this->DMI_Message_Time_Stamp

            >>this->DMI_Status>>this->Display_Status



            >>this->Driver_Id>>this->Schedule_Id
            >>this->Service_Id>>this->Trip_Id>>this->Path_Id>>this->Destination_Id>>this->Manual_Location_Id
            >>this->Manual_Time_Update>>this->Manual_Time_Validity

            >>this->Crossing_Priority_Request

            >>this->RR_Left_Button>>this->RR_Right_Button>>this->RR_Straight_Button

            >>this->ELS_Mode_Selection>>this->Time_Shift_Request;

#ifdef Baseline_2_0
    //DMI DMS Data Link
    readBytes>>this->DMI_DMS_Data_Size;
    DMI_DMS_Data=new quint8[this->DMI_DMS_Data_Size];
    for(int i=0;i<this->DMI_DMS_Data_Size;i++)
    {
        readBytes>>this->DMI_DMS_Data[i];
    }
#endif

    readBytes>>this->OCC_Message_Number>>this->OCC_Message_Length;

    this->OCC_Message_Text=new quint8[OCC_Message_Length];

    for(int i=0;i<OCC_Message_Length;i++)
        readBytes>>this->OCC_Message_Text[i];

    readBytes>>this->OSS_Message_Number>>this->OSS_Message_Length;
    OSS_Message_Text=new quint8[OSS_Message_Length];
    for(int i=0;i<OSS_Message_Length;i++)
        readBytes>>this->OSS_Message_Text[i];

    readBytes>>Driver_Message_Number;
}

void DMI_ELS_Protocol::setBytesFromData(QByteArray &qsend)
{
    QDataStream sendBytes(&qsend,QIODevice::WriteOnly);
    //    sendBytes.setByteOrder(QDataStream::LittleEndian);  默认大端
    sendBytes<<this->Message_Format_Version;
    //    this->DMI_Message_Number++;
    sendBytes<<this->DMI_Message_Number<<this->DMI_Message_Time_Stamp

               //DMI Status
            <<this->DMI_Status<<this->Display_Status

              //Service Setting
           <<this->Driver_Id<<this->Schedule_Id<<this->Service_Id<<this->Trip_Id
          <<this->Path_Id<<this->Destination_Id<<this->Manual_Location_Id
         <<this->Manual_Time_Update<<this->Manual_Time_Validity

           //Crossing Priority
        <<this->Crossing_Priority_Request

          //Route Request
       <<this->RR_Left_Button<<this->RR_Right_Button<<this->RR_Straight_Button

         //Mission Management
      <<this->ELS_Mode_Selection<<this->Time_Shift_Request;

#ifdef Baseline_2_0
    sendBytes<<this->DMI_DMS_Data_Size;
    if(this->DMI_DMS_Data_Size>0)
    {
        for(int i=0;i<this->DMI_DMS_Data_Size;i++)
            sendBytes<<this->DMI_DMS_Data[i];
    }
#endif

    //Driver SMS
    sendBytes<<this->OCC_Message_Number<<this->OCC_Message_Length;
    if(OCC_Message_Length>0)
    {
        for(int i=0;i<OCC_Message_Length;i++)
            sendBytes<<OCC_Message_Text[i];
    }
    sendBytes<<this->OSS_Message_Number<<this->OSS_Message_Length;
    if(OSS_Message_Length>0)
    {
        for(int i=0;i<OSS_Message_Length;i++)
            sendBytes<<OSS_Message_Text[i];
    }

    sendBytes<<this->Driver_Message_Number;
}

