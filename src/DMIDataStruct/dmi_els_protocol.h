/******************************
** Date: 2016/06/23
** Author: noodlebin
** Brief: get and set dmi->els protocol (Message_A.xls suggested by alstom) .h
** Version: 1.0
******************************/
#ifndef DMI_ELS_PROTOCOL_H
#define DMI_ELS_PROTOCOL_H
#include "Public_Variable.h"


#include <QObject>
#include <QDataStream>
#include <time.h>

#pragma pack(push)
#pragma pack(1)
//class DMI_ELS_Protocol : public QObject
struct DMI_ELS_Protocol
{
//    Q_OBJECT
public:
    explicit DMI_ELS_Protocol();
    void clearAll();
public:
    void getDataFromBytes(QByteArray& bytes);
    void setBytesFromData(QByteArray& qsend);
    void stepOne();
    void stepTwo();
    void stepThree();
    void freePointer();
    void resetDefault();
public:
    //Pegasus Header  11bytes
    quint8 Message_Format_Version;
    quint16  DMI_Message_Number ;
    quint64  DMI_Message_Time_Stamp;

    //DMI Status 2bytes
    quint8 DMI_Status;
    quint8 Display_Status;

    //Service Data   23byttes
    qint16 Driver_Id;
    qint16 Schedule_Id;
    qint16 Service_Id;
    qint16 Trip_Id;
    qint16 Path_Id;
    qint16 Destination_Id;
    qint16 Manual_Location_Id;
    quint64 Manual_Time_Update;
    quint8 Manual_Time_Validity;

    //Crossing Priority 1byte
    quint8 Crossing_Priority_Request;

    //Route Request 3bytes
    quint8 RR_Left_Button;
    quint8 RR_Right_Button;
    quint8 RR_Straight_Button;

    //Mission Management  2bytes
    quint8 ELS_Mode_Selection;
    quint8 Time_Shift_Request;

#ifdef Baseline_2_0
    //DMI DMS Data Link
    quint8 DMI_DMS_Data_Size;
    quint8 *DMI_DMS_Data;
#endif

    //SMS To OCC Setting  7bytes
    qint16 OCC_Message_Number;
    quint8 OCC_Message_Length;
    quint8* OCC_Message_Text;

    //SMS_To_OSS_Setting
    qint16 OSS_Message_Number;
    quint8 OSS_Message_Length;
    quint8* OSS_Message_Text;

    //SMS_To_Driver_Report
    qint16 Driver_Message_Number;

    //58bytes not include three text content,include three pointer



};

#pragma pack(pop)

#endif // DMI_ELS_PROTOCOL_H
