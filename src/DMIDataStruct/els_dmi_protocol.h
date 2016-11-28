/******************************
** Date: 2016/06/23
** Author: noodlebin
** Brief: get and set els->dmi protocol (Message_A.xls suggested by alstom) .h
** Version: 1.0
******************************/
#ifndef ELS_DMI_PROTOCOL_H
#define ELS_DMI_PROTOCOL_H

#include "Public_Variable.h"

#include <QObject>
#include <QDataStream>
#include <time.h>
#include <QDebug>

#pragma pack(push)
#pragma pack(1)
struct ELS_DMI_Protocol
{
public:
    ELS_DMI_Protocol();
    ~ELS_DMI_Protocol();

public:
    void getDataFromBytes(QByteArray& bytes);
    void setBytesFromData(QByteArray& qsend);

    void stepOne();
    void stepTwo();
    void stepThree();
    void freePointer();
public:


    //Pegasus Header
    quint8 Message_Format_Version;
    quint16 ELS_Message_Number ;
    quint64 ELS_Message_Time_Stamp;

    //DMI Control
    quint8 DMI_Control;

    //Time Control
    quint64 Current_Time;
    qint8 Time_Zone;

    //System Status
    quint8 ELS_Function_Detailed_Status;

#ifdef Baseline_2_0
    quint8 BCM_Status;
#endif

    quint8 Radio_Status;

#ifdef Baseline_2_0
    quint8 Radar_Status;
    quint8 GPS_Status;
#endif

    quint8 System_Ok;

    //ELS Data
    quint8 ELS_Service_Mode;
    quint8 Train_Location_Status;
    quint8 Communication_ELS_DMS_Status;
    quint8 Radio_Coverage_ELS_DMS;
    quint8 ELS_RR_CP_Shutdown;
    quint8 ELS_Current_Speed;

    //Service Data
    quint16 Logical_Train_Id;
    quint16 Physical_Train_Id;
    quint16 Driver_Id;
    quint16 Line_Id;
    quint16 Schedule_Id;
    quint16 Service_Id;
    quint16 Trip_Id;
    quint16 Path_Id;
    quint16 Destination_Id;

    //Mission Management Data
    quint16 Current_SSA_Id;
    quint16 Next_SSA_Id ;
    quint64 Current_SSA_Depature_Time;
    quint64 Next_SSA_Arrival_Time;
    quint8 Passenger_Mission;
    quint8 Running_Type;
    quint8 Skip_Next_SSA;
    qint16 Advance_Delay_Time;
    quint8 Train_Hold;
    quint8 Turn_Back_Required;
    quint16 SSA_of_Driver_End_of_Service;
    quint64 Time_of_Driver_End_of_Service;
    quint16 Time_to_Driver_End_of_Service;

    //Headway Data
    quint16 Distance_To_Upstream_Train;
    quint16 Distance_To_Downstream_Train;
    quint16 Time_To_Upstream_Train;
    quint16 Time_To_Downstream_Train;
    quint16 Time_Headway_Required;

    //Route Request Data
    quint8 Right_Route_Status;
    quint8 Left_Route_Status;
    quint8 Straight_Route_Status;
    qint16 Distance_To_End_Selection_Area;
    quint8 Selection_Area_Length;
    quint8 spare;
    quint8 Route_Request_Area_Status;
    qint8 Distance_To_Station_RR_Beacon;
    quint8 Station_RR_Beacon_Link;
    quint8 spare2;

    //Crossroad Priority data
    quint8 CP_Area_Status;
    qint16 CP_Distance_To_End_Preselection_Area;
    quint8 CP_Length_Preselection_Area;
    qint8 CP_Distance_To_Beacon_of_CP_Request_Area;
    quint8 CP_Beacon_Of_CP_Request_Area_Status;

    //ATP Data
    quint8 Train_Protection_Control_Status;
    quint8 ATP_Inhibition_Status;
    quint8 Current_Speed;
    quint8 Authorized_Speed;
    quint8 In_Slowdown_Area;
    quint8 ATP_Warning;
    quint8 Emergency_Braking_Applied;
    quint8 Service_Braking_Applied;
    quint8 Pantograph_Authorization_Status;
    quint8 Sanding_Authorization_Status;
    quint8 Left_Doors_Authorization_Status;
    quint8 Right_Doors_Authorization_Status;
    quint8 Docking_Authorization_Status;

#ifdef Baseline_2_0
    //Signal Warning
    qint16 Distance_To_Signal;
    quint8 Signal_Status;
    quint8 Warning_Signal_Anticipation;
    quint8 Warning_Signal_Infringement;

    //PSR Warning
    qint16 Distance_To_Next_Restrictive_PSR;
    quint8 Next_Restrictive_PSR_Speed;
    quint8 Warning_PSR_Slowdown_Overspeed;
    quint8 Current_PSR_Speed;
    quint8 Warning_PSR_Overspeed;
    quint8 RS_Max_Speed;
    quint8 Warning_RS_Speed_Overspeed;

    //Radar Data
    qint16 Radar_Speed;
    quint8 Risk_Level;
    quint8 Size_Of_Additional_Data;
    quint8 Obstacle_Total_Num;
    quint8 *Obstacle_ID;
    quint8 *Alarm_Level;
    quint8 *Obstacle_Straight_Distance;
    qint8 *Obstacle_Lateral_Distance;
    quint8 *Obstacle_Attribute;

    //DMI DMI Data Link
    quint8 DMS_DMI_Data_Size;
    quint8 *DMS_DMI_Data;

#endif

    //Available Schedule, Service, Trip, Path, Destination
    quint8 Number_of_Schedule;
    quint16* Id_of_schedules;
    quint8 Number_of_Service;
    quint16* Id_of_services;
    quint8 Number_of_Trip;
    quint16* Id_of_Trips;
    quint8 Number_of_Path;
    quint16* Id_of_Paths;
    quint8 Number_of_Destinations;
    quint16* Id_of_Destinations;

    //SMS_To_Driver_Setting
    qint16 Driver_Message_Number;
    quint8 Driver_Message_Length;
    quint8* Driver_Message_Text;

    //SMS_To_OCC_Report
    qint16 OCC_Message_Number;
    quint8 OCC_Message_Status;

    //SMS_To_OSS_Report
    qint16 OSS_Message_Number;

    //Maintance Status
    quint8 Number_of_Active_Fault;
    quint16* Id_of_Fault;
    quint64* Time_of_Appearance;

    //Geographic Events
    quint8 Number_of_Active_Events;
    quint8* Event_Id;
    quint8* Event_Output_Value;
    quint16* Geographic_Distance_To_begin;
    quint16* Geographic_Distance_To_End;


public slots:
};

#pragma pack(pop)

#endif // ELS_DMI_PROTOCOL_H
