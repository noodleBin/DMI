/******************************
** Date: 2016/06/23
** Author: noodlebin
** Brief: get and set els->dmi protocol (Message_A.xls suggested by alstom) .cpp
** Version: 1.0
******************************/
#include "els_dmi_protocol.h"

ELS_DMI_Protocol::ELS_DMI_Protocol()
{
    //        stepTwo();
    //    stepThree();
    stepOne(); //equal clear, such as sent some data size =0
    this->ELS_Message_Number=0;
}

ELS_DMI_Protocol::~ELS_DMI_Protocol()
{

}

void ELS_DMI_Protocol::getDataFromBytes(QByteArray &bytes)
{
    QDataStream readBytes(&bytes,QIODevice::ReadOnly);
    //    readBytes.setByteOrder(QDataStream::LittleEndian);
    readBytes>>this->Message_Format_Version>>this->ELS_Message_Number
            >>this->ELS_Message_Time_Stamp

            >>this->DMI_Control>>this->Current_Time>>this->Time_Zone

            >>this->ELS_Function_Detailed_Status

        #ifdef Baseline_2_0
            >>this->BCM_Status
        #endif

            >>this->Radio_Status

        #ifdef Baseline_2_0
            >>this->Radar_Status
            >>this->GPS_Status
        #endif

            >>this->System_Ok

            >>this->ELS_Service_Mode>>this->Train_Location_Status
            >>this->Communication_ELS_DMS_Status>>this->Radio_Coverage_ELS_DMS>>this->ELS_RR_CP_Shutdown
            >>this->ELS_Current_Speed

            >>this->Logical_Train_Id>>this->Physical_Train_Id
            >>this->Driver_Id>>this->Line_Id>>this->Schedule_Id
            >>this->Service_Id>>this->Trip_Id>>this->Path_Id>>this->Destination_Id

            >>this->Current_SSA_Id>>this->Next_SSA_Id>>this->Current_SSA_Depature_Time>>this->Next_SSA_Arrival_Time
            >>this->Passenger_Mission>>this->Running_Type>>this->Skip_Next_SSA>>this->Advance_Delay_Time
            >>this->Train_Hold>>this->Turn_Back_Required>>this->SSA_of_Driver_End_of_Service>>this->Time_of_Driver_End_of_Service
            >>this->Time_to_Driver_End_of_Service

            //Headway Data
            >>this->Distance_To_Upstream_Train>>this->Distance_To_Downstream_Train
            >>this->Time_To_Upstream_Train>>this->Time_To_Downstream_Train
            >>this->Time_Headway_Required

            //RR Data
            >>this->Right_Route_Status>>this->Left_Route_Status>>this->Straight_Route_Status
            >>this->Distance_To_End_Selection_Area>>this->Selection_Area_Length>>this->spare
            >>this->Route_Request_Area_Status>>this->Distance_To_Station_RR_Beacon>>this->Station_RR_Beacon_Link
            >>this->spare2

            //CP Data
            >>this->CP_Area_Status>>this->CP_Distance_To_End_Preselection_Area>>this->CP_Length_Preselection_Area
            >>this->CP_Distance_To_Beacon_of_CP_Request_Area>>this->CP_Beacon_Of_CP_Request_Area_Status

            //ATP Data
            >>this->Train_Protection_Control_Status>>this->ATP_Inhibition_Status>>this->Current_Speed
            >>this->Authorized_Speed>>this->In_Slowdown_Area>>this->ATP_Warning>>this->Emergency_Braking_Applied
            >>this->Service_Braking_Applied>>this->Pantograph_Authorization_Status>>this->Sanding_Authorization_Status
            >>this->Left_Doors_Authorization_Status>>this->Right_Doors_Authorization_Status>>this->Docking_Authorization_Status;

#ifdef Baseline_2_0
    //Signal Warning
    readBytes>>this->Distance_To_Signal
            >>this->Signal_Status
            >>this->Warning_Signal_Anticipation
            >>this->Warning_Signal_Infringement

            //PSR Warning
            >>this->Distance_To_Next_Restrictive_PSR
            >>this->Next_Restrictive_PSR_Speed
            >>this->Warning_PSR_Slowdown_Overspeed
            >>this->Current_PSR_Speed
            >>this->Warning_PSR_Overspeed
            >>this->RS_Max_Speed
            >>this->Warning_RS_Speed_Overspeed

            //Radar Data
            >>this->Radar_Speed
            >>this->Risk_Level
            >>this->Size_Of_Additional_Data
            >>this->Obstacle_Total_Num;
    Obstacle_ID = new quint8[Obstacle_Total_Num];
    Alarm_Level= new quint8[Obstacle_Total_Num];
    Obstacle_Straight_Distance= new quint8[Obstacle_Total_Num];
    Obstacle_Lateral_Distance= new qint8[Obstacle_Total_Num];
    Obstacle_Attribute= new quint8[Obstacle_Total_Num];

    for(int i=0;i<this->Obstacle_Total_Num;i++)
    {
        readBytes>>this->Obstacle_ID[i]>>this->Alarm_Level[i]>>this->Obstacle_Straight_Distance[i]
                >>this->Obstacle_Lateral_Distance[i]>>this->Obstacle_Attribute[i];
    }

    //DMI DMI Data Link
    readBytes>>this->DMS_DMI_Data_Size;
    DMS_DMI_Data=new quint8[this->DMS_DMI_Data_Size];
    for(int i=0;i<this->DMS_DMI_Data_Size;i++)
    {
        readBytes>>this->DMS_DMI_Data[i];
    }

#endif


    //Available Schedule, Service, Trip, Path, Destination
    readBytes>>Number_of_Schedule;
    Id_of_schedules=new quint16[Number_of_Schedule];
    for(int i=0;i<Number_of_Schedule;i++)
        readBytes>>Id_of_schedules[i];

    readBytes>>Number_of_Service;
    Id_of_services=new quint16[Number_of_Service];
    for(int i=0;i<Number_of_Service;i++)
        readBytes>>Id_of_services[i];

    readBytes>>Number_of_Trip;
    Id_of_Trips=new quint16[Number_of_Trip];
    for(int i=0;i<Number_of_Trip;i++)
        readBytes>>Id_of_Trips[i];

    readBytes>>Number_of_Path;
    Id_of_Paths=new quint16[Number_of_Path];
    for(int i=0;i<Number_of_Path;i++)
        readBytes>>Id_of_Paths[i];

    readBytes>>Number_of_Destinations;
    Id_of_Destinations=new quint16[Number_of_Destinations];
    for(int i=0;i<Number_of_Destinations;i++)
        readBytes>>Id_of_Destinations[i];

    //SMS To Driver Setting
    readBytes>>Driver_Message_Number>>Driver_Message_Length;
    Driver_Message_Text=new quint8[Driver_Message_Length];
    for(int i=0;i<Driver_Message_Length;i++)
        readBytes>>Driver_Message_Text[i];

    //SMS To OCC Report
    readBytes>>OCC_Message_Number>>OCC_Message_Status;

    //SMS To OSS Report
    readBytes>>OSS_Message_Number;

    //Maintenance Status
    readBytes>>Number_of_Active_Fault;
    Id_of_Fault = new quint16[Number_of_Active_Fault];
    Time_of_Appearance=new quint64[Number_of_Active_Fault];
    for(int i=0;i<Number_of_Active_Fault;i++)
        readBytes>>Id_of_Fault[i]>>Time_of_Appearance[i];

    //Geographic Events
    readBytes>>Number_of_Active_Events;
    Event_Id=new quint8[Number_of_Active_Events];
    Event_Output_Value=new quint8[Number_of_Active_Events];
    Geographic_Distance_To_begin=new quint16[Number_of_Active_Events];
    Geographic_Distance_To_End=new quint16[Number_of_Active_Events];
    for(int i=0;i<Number_of_Active_Events;i++)
        readBytes>>Event_Id[i]>>Event_Output_Value[i]>>Geographic_Distance_To_begin[i]>>Geographic_Distance_To_End[i];


    ;

}

void ELS_DMI_Protocol::setBytesFromData(QByteArray &qsend)
{
    QDataStream sendBytes(&qsend,QIODevice::WriteOnly);
    //    sendBytes.setByteOrder(QDataStream::LittleEndian);  默认大端
    sendBytes<<this->Message_Format_Version;
    //    this->ELS_Message_Number++;
    sendBytes<<this->ELS_Message_Number<<this->ELS_Message_Time_Stamp

               //DMI Control
            <<this->DMI_Control

              //Time Control
           <<this->Current_Time<<this->Time_Zone

             //System status
          <<this->ELS_Function_Detailed_Status;

#ifdef Baseline_2_0
    sendBytes<<this->BCM_Status;
#endif

    sendBytes<<this->Radio_Status;

#ifdef Baseline_2_0
    sendBytes<<this->Radar_Status<<this->GPS_Status;
#endif
    sendBytes<<this->System_Ok

               //ELS Data
            <<this->ELS_Service_Mode<<this->Train_Location_Status<<this->Communication_ELS_DMS_Status
           <<this->Radio_Coverage_ELS_DMS<<this->ELS_RR_CP_Shutdown<<this->ELS_Current_Speed

             //Service Data
          <<this->Logical_Train_Id<<this->Physical_Train_Id<<this->Driver_Id<<this->Line_Id
         <<this->Schedule_Id<<this->Service_Id<<this->Trip_Id
        <<this->Path_Id<<this->Destination_Id

          //Mission Management Data
       <<this->Current_SSA_Id<<this->Next_SSA_Id<<this->Current_SSA_Depature_Time<<this->Next_SSA_Arrival_Time
      <<this->Passenger_Mission<<this->Running_Type<<this->Skip_Next_SSA<<this->Advance_Delay_Time<<this->Train_Hold
     <<this->Turn_Back_Required<<this->SSA_of_Driver_End_of_Service<<this->Time_of_Driver_End_of_Service
    <<this->Time_to_Driver_End_of_Service

      //Headway Data
    <<this->Distance_To_Upstream_Train<<this->Distance_To_Downstream_Train<<this->Time_To_Upstream_Train
    <<this->Time_To_Downstream_Train<<this->Time_Headway_Required

      //RR Data
    <<this->Right_Route_Status<<this->Left_Route_Status<<this->Straight_Route_Status<<this->Distance_To_End_Selection_Area
    <<this->Selection_Area_Length<<this->spare<<this->Route_Request_Area_Status<<this->Distance_To_Station_RR_Beacon
    <<this->Station_RR_Beacon_Link<<this->spare2

      //Crossing Priority Data
    <<this->CP_Area_Status<<this->CP_Distance_To_End_Preselection_Area<<this->CP_Length_Preselection_Area
    <<this->CP_Distance_To_Beacon_of_CP_Request_Area<<this->CP_Beacon_Of_CP_Request_Area_Status

      //ATP Data
    <<this->Train_Protection_Control_Status<<this->ATP_Inhibition_Status<<this->Current_Speed<<this->Authorized_Speed
    <<this->In_Slowdown_Area<<this->ATP_Warning<<this->Emergency_Braking_Applied<<this->Service_Braking_Applied
    <<this->Pantograph_Authorization_Status<<this->Sanding_Authorization_Status<<this->Left_Doors_Authorization_Status
    <<this->Right_Doors_Authorization_Status<<this->Docking_Authorization_Status;

#ifdef Baseline_2_0
    //Signal Warning
    sendBytes<<this->Distance_To_Signal
            <<this->Signal_Status
           <<this->Warning_Signal_Anticipation
          <<this->Warning_Signal_Infringement

            //PSR Warning
         <<this->Distance_To_Next_Restrictive_PSR
        <<this->Next_Restrictive_PSR_Speed
       <<this->Warning_PSR_Slowdown_Overspeed
      <<this->Current_PSR_Speed
     <<this->Warning_PSR_Overspeed
    <<this->RS_Max_Speed
    <<this->Warning_RS_Speed_Overspeed

      //Radar Data
    <<this->Radar_Speed
    <<this->Risk_Level
    <<this->Size_Of_Additional_Data
    <<this->Obstacle_Total_Num;
    for(int i=0;i<this->Obstacle_Total_Num;i++)
    {
        sendBytes<<this->Obstacle_ID[i]
                   <<this->Alarm_Level[i]
                     <<this->Obstacle_Straight_Distance[i]
                       <<this->Obstacle_Lateral_Distance[i]
                         <<this->Obstacle_Attribute[i];
    }

    //DMI DMI Data Link
    sendBytes<<this->DMS_DMI_Data_Size;
    for(int i=0;i<this->DMS_DMI_Data_Size;i++)
    {
        sendBytes<<this->DMS_DMI_Data[i];
    }

#endif



    //Available Schedule, Service, Trip, Path, Destination
    sendBytes<<Number_of_Schedule;
    for(int i=0;i<Number_of_Schedule;i++)
        sendBytes<<Id_of_schedules[i];
    sendBytes<<Number_of_Service;
    for(int i=0;i<Number_of_Service;i++)
        sendBytes<<Id_of_services[i];
    sendBytes<<Number_of_Trip;
    for(int i=0;i<Number_of_Trip;i++)
        sendBytes<<Id_of_Trips[i];
    sendBytes<<Number_of_Path;
    for(int i=0;i<Number_of_Path;i++)
        sendBytes<<Id_of_Paths[i];
    sendBytes<<Number_of_Destinations;
    for(int i=0;i<Number_of_Destinations;i++)
        sendBytes<<Id_of_Destinations[i];

    sendBytes<<Driver_Message_Number<<Driver_Message_Length;
    for(int i=0;i<Driver_Message_Length;i++)
        sendBytes<<Driver_Message_Text[i];

    sendBytes<<OCC_Message_Number<<OCC_Message_Status;

    sendBytes<<OSS_Message_Number;

    sendBytes<<Number_of_Active_Fault;
    for(int i=0;i<Number_of_Active_Fault;i++)
        sendBytes<<Id_of_Fault[i]<<Time_of_Appearance[i];

    sendBytes<<Number_of_Active_Events;
    for(int i=0;i<Number_of_Active_Events;i++)
        sendBytes<<Event_Id[i]<<Event_Output_Value[i]<<Geographic_Distance_To_begin[i]<<Geographic_Distance_To_End[i];
}

void ELS_DMI_Protocol::stepOne()
{
    //Pegasus Header
    Message_Format_Version=0;

    ELS_Message_Time_Stamp=0;

    //DMI Control
    DMI_Control=0;


    //Time Control
    Current_Time=0;
    Time_Zone=-48;

    //System Status
    ELS_Function_Detailed_Status=0;
    Radio_Status=0;
    System_Ok=0;


    //ELS Data
    ELS_Service_Mode=0;
    Train_Location_Status=0;
    Communication_ELS_DMS_Status=0;
    Radio_Coverage_ELS_DMS=0;
    ELS_RR_CP_Shutdown=0;

    //Service Data
    Logical_Train_Id=0;
    Physical_Train_Id=0;
    Driver_Id=0;
    Line_Id=0;
    Schedule_Id=0;
    Service_Id=0;
    Trip_Id=0;
    Path_Id=0;
    Destination_Id=0;

    //Mission Management Data
    Current_SSA_Id=0;
    Next_SSA_Id =0;
    Current_SSA_Depature_Time=0;
    Next_SSA_Arrival_Time=0;
    Passenger_Mission=0;
    Running_Type=0;
    Skip_Next_SSA=0;
    Advance_Delay_Time=-32768;
    Train_Hold=0;
    Turn_Back_Required=0;
    SSA_of_Driver_End_of_Service=0;
    Time_of_Driver_End_of_Service=0;
    Time_to_Driver_End_of_Service=0;

    //Headway Data
    Distance_To_Upstream_Train=0;
    Distance_To_Downstream_Train=0;
    Time_To_Upstream_Train=0;
    Time_To_Downstream_Train=0;
    Time_Headway_Required=0;

    //Route Request Data
    Right_Route_Status=0;
    Left_Route_Status=0;
    Straight_Route_Status=0;
    Distance_To_End_Selection_Area=-1;
    Selection_Area_Length=0;
    spare=0;
    Route_Request_Area_Status=0;
    Distance_To_Station_RR_Beacon=-128;
    Station_RR_Beacon_Link=0;
    spare2=0;

    //Crossroad Priority data
    CP_Area_Status=0;
    CP_Distance_To_End_Preselection_Area=-1;
    CP_Length_Preselection_Area=0;
    CP_Distance_To_Beacon_of_CP_Request_Area=-128;
    CP_Beacon_Of_CP_Request_Area_Status=0;

    //ATP Data
    Train_Protection_Control_Status=0;
    ATP_Inhibition_Status=0;
    Current_Speed=0;
    Authorized_Speed=0;
    In_Slowdown_Area=0;
    ATP_Warning=0;
    Emergency_Braking_Applied=0;
    Service_Braking_Applied=0;
    Pantograph_Authorization_Status=0;
    Sanding_Authorization_Status=0;
    Left_Doors_Authorization_Status=0;
    Right_Doors_Authorization_Status=0;
    Docking_Authorization_Status=0;


    //Available Schedule,Service,Trip,Path,Destination
    Number_of_Schedule=0;
    Number_of_Service=0;
    Number_of_Trip=0;
    Number_of_Path=0;
    Number_of_Destinations=0;

    //SMS To Driver Setting
    Driver_Message_Number=3;
    Driver_Message_Length=0;

    //SMS_To OCC Report
    OCC_Message_Number=-1;
    OCC_Message_Status=0;

    //SMS_To OSS Report
    OSS_Message_Number=-1;

    //Maintenance Status
    Number_of_Active_Fault=0;


    //Geographic Events
    Number_of_Active_Events=0;

#ifdef Baseline_2_0
    //Signal Warning
//    qint16 Distance_To_Signal;
//    quint8 Signal_Status;
//    quint8 Warning_Signal_Anticipation;
//    quint8 Warning_Signal_Infringement;

//    //PSR Warning
//    qint16 Distance_To_Next_Restrictive_PSR;
//    quint8 Next_Restrictive_PSR_Speed;
//    quint8 Warning_PSR_Slowdown_Overspeed;
//    quint8 Current_PSR_Speed;
//    quint8 Warning_PSR_Overspeed;
//    quint8 RS_Max_Speed;
//    quint8 Warning_RS_Speed_Overspeed;

//    //Radar Data
//    qint16 Radar_Speed;
//    quint8 Risk_Level;
//    quint8 Size_Of_Additional_Data;
     Obstacle_Total_Num=0;
//    quint8 *Obstacle_ID;
//    quint8 *Alarm_Level;
//    quint8 *Obstacle_Straight_Distance;
//    qint8 *Obstacle_Lateral_Distance;
//    quint8 *Obstacle_Attribute;

    //DMI DMI Data Link
    DMS_DMI_Data_Size=0;
//    quint8 *DMS_DMI_Data;

#endif


}

void ELS_DMI_Protocol::stepTwo()
{
    //Pegasus Header
    Message_Format_Version=0x23;


    time_t now;
    time(&now);
    ELS_Message_Time_Stamp=now;

    //DMI Control
    DMI_Control=0;


    //Time Control
    Current_Time=0x0123456789ABCDEF;
    Time_Zone=32;

    //System Status
    ELS_Function_Detailed_Status=0b00001001;
    Radio_Status=1;
    System_Ok=0;


    //ELS Data
    ELS_Service_Mode=2;
    Train_Location_Status=1;
    Communication_ELS_DMS_Status=0;
    Radio_Coverage_ELS_DMS=1;
    ELS_RR_CP_Shutdown=2;

    //Service Data
    Logical_Train_Id=0xcdef;
    Physical_Train_Id=0xbcde;
    Driver_Id=0x7890;
    Line_Id=0x6789;
    Schedule_Id=0x5678;
    Service_Id=0x4567;
    Trip_Id=0x3456;
    Path_Id=0x2345;
    Destination_Id=0x1234;

    //Mission Management Data
    Current_SSA_Id=0xabcd;
    Next_SSA_Id =0xdef0;
    Current_SSA_Depature_Time=0x0111111111111112;
    Next_SSA_Arrival_Time=0x5666666666666667;
    Passenger_Mission=1;
    Running_Type=2;
    Skip_Next_SSA=0;
    Advance_Delay_Time=50;
    Train_Hold=1;
    Turn_Back_Required=2;
    SSA_of_Driver_End_of_Service=0x1234;
    Time_of_Driver_End_of_Service=0x7888888888888889;
    Time_to_Driver_End_of_Service=0xabcd;

    //Headway Data
    Distance_To_Upstream_Train=100;
    Distance_To_Downstream_Train=200;
    Time_To_Upstream_Train=1000;
    Time_To_Downstream_Train=2000;
    Time_Headway_Required=3000;

    //Route Request Data
    Right_Route_Status=2;
    Left_Route_Status=1;
    Straight_Route_Status=2;
    Distance_To_End_Selection_Area=0xaa;
    Selection_Area_Length=0xbb;
    spare=1;
    Route_Request_Area_Status=2;
    Distance_To_Station_RR_Beacon=40;
    Station_RR_Beacon_Link=1;
    spare2=0x99;

    //Crossroad Priority data
    CP_Area_Status=3;
    CP_Distance_To_End_Preselection_Area=0x11;
    CP_Length_Preselection_Area=0x22;
    CP_Distance_To_Beacon_of_CP_Request_Area=50;
    CP_Beacon_Of_CP_Request_Area_Status=1;

    //ATP Data
    Train_Protection_Control_Status=2;
    ATP_Inhibition_Status=1;
    Current_Speed=130;
    Authorized_Speed=120;
    In_Slowdown_Area=0;
    ATP_Warning=1;
    Emergency_Braking_Applied=0;
    Service_Braking_Applied=1;
    Pantograph_Authorization_Status=2;
    Sanding_Authorization_Status=1;
    Left_Doors_Authorization_Status=2;
    Right_Doors_Authorization_Status=1;
    Docking_Authorization_Status=2;


    //Available Schedule,Service,Trip,Path,Destination
    Number_of_Schedule=1;
    Id_of_schedules = new quint16[1];
    Id_of_schedules[0]=0x7fff;

    Number_of_Service=2;
    Id_of_services = new quint16[2];
    Id_of_services[0]=0x0001;
    Id_of_services[1]=0x0002;

    Number_of_Trip=3;
    Id_of_Trips=new quint16[3];
    Id_of_Trips[0]=0x1001;
    Id_of_Trips[1]=0x1002;
    Id_of_Trips[2]=0x1003;

    Number_of_Path=4;
    Id_of_Paths=new quint16[4];
    Id_of_Paths[0]=0x2001;
    Id_of_Paths[1]=0x2002;
    Id_of_Paths[2]=0x2003;
    Id_of_Paths[3]=0x2004;

    Number_of_Destinations=5;
    Id_of_Destinations=new quint16[5];
    Id_of_Destinations[0]=0x3001;
    Id_of_Destinations[1]=0x3002;
    Id_of_Destinations[2]=0x3003;
    Id_of_Destinations[3]=0x3004;
    Id_of_Destinations[4]=0x3005;


    //SMS To Driver Setting
    Driver_Message_Number=0x1234;
    Driver_Message_Length=20;
    Driver_Message_Text = new quint8[Driver_Message_Length];
    quint8 tmpdrivermsgtxt=0x01;
    for(int i=0;i<Driver_Message_Length;i++)
        Driver_Message_Text[i]=tmpdrivermsgtxt+i;


    //SMS_To OCC Report
    OCC_Message_Number=0x2345;
    OCC_Message_Status=2;

    //SMS_To OSS Report
    OSS_Message_Number=0x3456;

    //Maintenance Status
    Number_of_Active_Fault=1;
    Id_of_Fault=new quint16[1];
    Id_of_Fault[0]=0xffff;
    Time_of_Appearance=new quint64[1];
    Time_of_Appearance[0]=0xffffffffffffffff;



    //Geographic Events
    Number_of_Active_Events=4;
    Event_Id = new quint8[4];
    quint8 tmpeventid=1;
    for(int i=0;i<4;i++)
        Event_Id[i]=tmpeventid+i;

    Event_Output_Value=new quint8[4];
    Event_Output_Value[0]=0;
    Event_Output_Value[1]=1;
    Event_Output_Value[2]=2;
    Event_Output_Value[3]=255;

    Geographic_Distance_To_begin=new quint16[4];
    Geographic_Distance_To_begin[0]=0;
    Geographic_Distance_To_begin[1]=1;
    Geographic_Distance_To_begin[2]=2;
    Geographic_Distance_To_begin[3]=65535;

    Geographic_Distance_To_End=new quint16[4];
    Geographic_Distance_To_End[0]=0;
    Geographic_Distance_To_End[1]=1;
    Geographic_Distance_To_End[2]=2;
    Geographic_Distance_To_End[3]=65535;
}
void ELS_DMI_Protocol::stepThree()
{
    //Pegasus Header
    Message_Format_Version=0xff;



    ELS_Message_Time_Stamp=0xffffffffffffffff;

    //DMI Control
    DMI_Control=1;


    //Time Control
    Current_Time=0xfffffffffffffffF;
    Time_Zone=56;

    //System Status
    ELS_Function_Detailed_Status=0b00001111;
    Radio_Status=1;
    System_Ok=1;


    //ELS Data
    ELS_Service_Mode=3;
    Train_Location_Status=2;
    Communication_ELS_DMS_Status=1;
    Radio_Coverage_ELS_DMS=2;
    ELS_RR_CP_Shutdown=1;

    //Service Data
    Logical_Train_Id=0xffff;
    Physical_Train_Id=0xffff;
    Driver_Id=0x7fff;
    Line_Id=0x7fff;
    Schedule_Id=0x7fff;
    Service_Id=0x7fff;
    Trip_Id=0x7fff;
    Path_Id=0x7fff;
    Destination_Id=0x7fff;

    //Mission Management Data
    Current_SSA_Id=0xffff;
    Next_SSA_Id =0xffff;
    Current_SSA_Depature_Time=0xffffffffffffffff;
    Next_SSA_Arrival_Time=0xffffffffffffffff;
    Passenger_Mission=2;
    Running_Type=3;
    Skip_Next_SSA=1;
    Advance_Delay_Time=32767;
    Train_Hold=2;
    Turn_Back_Required=3;
    SSA_of_Driver_End_of_Service=0xffff;
    Time_of_Driver_End_of_Service=0xffffffffffffffff;
    Time_to_Driver_End_of_Service=0xffff;

    //Headway Data
    Distance_To_Upstream_Train=1000;
    Distance_To_Downstream_Train=1000;
    Time_To_Upstream_Train=3600;
    Time_To_Downstream_Train=3600;
    Time_Headway_Required=3600;

    //Route Request Data
    Right_Route_Status=3;
    Left_Route_Status=3;
    Straight_Route_Status=3;
    Distance_To_End_Selection_Area=0xff;
    Selection_Area_Length=0xff;
    spare=2;
    Route_Request_Area_Status=4;
    Distance_To_Station_RR_Beacon=127;
    Station_RR_Beacon_Link=2;
    spare2=0xff;

    //Crossroad Priority data
    CP_Area_Status=5;
    CP_Distance_To_End_Preselection_Area=0xff;
    CP_Length_Preselection_Area=0xff;
    CP_Distance_To_Beacon_of_CP_Request_Area=127;
    CP_Beacon_Of_CP_Request_Area_Status=2;

    //ATP Data
    Train_Protection_Control_Status=3;
    ATP_Inhibition_Status=1;
    Current_Speed=0xff;
    Authorized_Speed=0xff;
    In_Slowdown_Area=1;
    ATP_Warning=2;
    Emergency_Braking_Applied=1;
    Service_Braking_Applied=1;
    Pantograph_Authorization_Status=1;
    Sanding_Authorization_Status=2;
    Left_Doors_Authorization_Status=1;
    Right_Doors_Authorization_Status=2;
    Docking_Authorization_Status=1;


    //Available Schedule,Service,Trip,Path,Destination
    Number_of_Schedule=50;
    Id_of_schedules = new quint16[50];
    quint16 tmpidsche=0x0001;
    for(int i=0;i<50;i++)
        Id_of_schedules[i]=tmpidsche+i;

    Number_of_Service=100;
    Id_of_services = new quint16[100];
    quint16 tmpidser=0x0001;
    for(int i=0;i<100;i++)
        Id_of_services[i]=tmpidser+i;

    Number_of_Trip=100;
    Id_of_Trips = new quint16[100];
    quint16 tmpidtrip=0x0001;
    for(int i=0;i<100;i++)
        Id_of_Trips[i]=tmpidtrip+i;

    Number_of_Path=100;
    Id_of_Paths = new quint16[100];
    quint16 tmpidpath=0x0001;
    for(int i=0;i<100;i++)
        Id_of_Paths[i]=tmpidpath+i;

    Number_of_Destinations=100;
    Id_of_Destinations = new quint16[100];
    quint16 tmpiddes=0x0001;
    for(int i=0;i<100;i++)
        Id_of_Destinations[i]=tmpiddes+i;


    //SMS To Driver Setting
    Driver_Message_Number=0x7fff;
    Driver_Message_Length=140;
    Driver_Message_Text = new quint8[Driver_Message_Length];
    quint8 tmpdrivermsgtxt=0x01;
    for(int i=0;i<Driver_Message_Length;i++)
        Driver_Message_Text[i]=tmpdrivermsgtxt+i;


    //SMS_To OCC Report
    OCC_Message_Number=0x7fff;
    OCC_Message_Status=3;

    //SMS_To OSS Report
    OSS_Message_Number=0x7fff;

    //Maintenance Status
    Number_of_Active_Fault=255;
    Id_of_Fault=new quint16[255];
    quint16 tmpidfault=0x0001;
    for(int i=0;i<255;i++)
        Id_of_Fault[i]=tmpidfault+i;

    Time_of_Appearance=new quint64[255];
    quint64 tmptimeapp=0x0000000000000001;
    for(int i=0;i<255;i++)
        Time_of_Appearance[i]=tmptimeapp+i;


    //Geographic Events
    Number_of_Active_Events=10;
    Event_Id = new quint8[10];

    for(int i=0;i<10;i++)
        Event_Id[i]=1;

    Event_Output_Value=new quint8[10];
    for(int i=0;i<10;i++)
        Event_Output_Value[i]=i+1;

    Geographic_Distance_To_begin=new quint16[10];
    for(int i=0;i<10;i++)
        Geographic_Distance_To_begin[i]=i+1;

    Geographic_Distance_To_End=new quint16[10];
    for(int i=0;i<10;i++)
        Geographic_Distance_To_End[i]=i+1;
}

void ELS_DMI_Protocol::freePointer()
{
#ifdef Baseline_2_0
//    qDebug()<<"obs num"<<Obstacle_Total_Num;
    if(this->Obstacle_Total_Num>0)
    {
        delete[] this->Obstacle_ID;
        delete[] this->Alarm_Level;
        delete[] this->Obstacle_Straight_Distance;
        delete[] this->Obstacle_Lateral_Distance;
        delete[] this->Obstacle_Attribute;
    }
    if(this->DMS_DMI_Data_Size>0)
    {
        delete[] DMS_DMI_Data;
    }
#endif
    if(this->Number_of_Schedule>0)
    {
        delete[] this->Id_of_schedules;
        this->Number_of_Schedule=0;  //释放前会先判断长度，释放完清0可以避免重复释放
    }
    if(this->Number_of_Service>0)
    {
        delete[] this->Id_of_services;
        this->Number_of_Service=0;
    }
    if(this->Number_of_Trip>0)
    {
        delete[] this->Id_of_Trips;
        this->Id_of_Trips=0;
    }
    if(this->Number_of_Path>0)
    {
        delete[] this->Id_of_Paths;
        this->Id_of_Paths=0;
    }
    if(this->Number_of_Destinations>0)
    {
        delete[] this->Id_of_Destinations;
        this->Id_of_Destinations=0;
    }
    if(this->Driver_Message_Length>0)
    {

        delete[] this->Driver_Message_Text;
        this->Driver_Message_Length=0;

    }
    if(this->Number_of_Active_Fault>0)
    {
        delete[] this->Id_of_Fault;
        delete[] this->Time_of_Appearance;
        this->Number_of_Active_Fault=0;
    }

    if(this->Number_of_Active_Events>0)
    {
        delete[] this->Event_Id;
        delete[] this->Event_Output_Value;
        delete[] this->Geographic_Distance_To_begin;
        delete[] this->Geographic_Distance_To_End;
        this->Number_of_Active_Events=0;
    }
}
