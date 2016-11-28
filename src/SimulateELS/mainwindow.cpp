#include "mainwindow.h"
#include "ui_mainwindow.h"

#define MAX 65536
#define WIDTH 5000
#define INC 100

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    isonecycle=false;
    isperiodly=false;
    israndom=false;
    isautoinc=false;
    issmsconfirm=true;
    issendtracklayout=true;
    is_auto_dmi_control=false;

    openFile();
    setUifromData(dmi_els_data);
    els_dmi_data.ELS_Function_Detailed_Status=15;
    els_dmi_data.Advance_Delay_Time=12;
    setUifromData(els_dmi_data);
    initSocket();
    que_els_dmi = new QQueue<QByteArray>();

    timer_1s=0;
    timer_100ms=startTimer(100);
    isstartgeo=false;

    ui->wdg_intialtime->setDateTime(QDateTime::currentDateTime());

    ui->wdg_curdeptime->setDateTime(QDateTime::currentDateTime());
    ui->wdg_nextarrtime->setDateTime(QDateTime::currentDateTime());

    tmpsub=QDateTime(QDate(1970,1,1)).secsTo(QDateTime(QDate(2000,1,1)));

    ui->tblwdg_geo->insertRow(0);
    ui->tblwdg_geo->insertRow(1);
    ui->tblwdg_geo->insertRow(2);

    ui->tblwdg_geo->setItem(0,0,new QTableWidgetItem(QString::number(1)));
    ui->tblwdg_geo->setItem(0,1,new QTableWidgetItem(QString::number(0)));
    //    ui->tblwdg_geo->setItem(0,2,new QTableWidgetItem(QString::number(15)));
    //    ui->tblwdg_geo->setItem(0,3,new QTableWidgetItem(QString::number(20)));

    ui->tblwdg_geo->setItem(0,2,new QTableWidgetItem(QString::number(MAX-5*WIDTH)));
    ui->tblwdg_geo->setItem(0,3,new QTableWidgetItem(QString::number(MAX-4*WIDTH)));

    ui->tblwdg_geo->setItem(1,0,new QTableWidgetItem(QString::number(2)));
    ui->tblwdg_geo->setItem(1,1,new QTableWidgetItem(QString::number(60)));
    ui->tblwdg_geo->setItem(1,2,new QTableWidgetItem(QString::number(MAX-3*WIDTH)));
    ui->tblwdg_geo->setItem(1,3,new QTableWidgetItem(QString::number(MAX-2*WIDTH)));



    ui->tblwdg_geo->setItem(2,0,new QTableWidgetItem(QString::number(3)));
    ui->tblwdg_geo->setItem(2,1,new QTableWidgetItem(QString::number(0)));
    ui->tblwdg_geo->setItem(2,2,new QTableWidgetItem(QString::number(MAX-1*WIDTH)));
    ui->tblwdg_geo->setItem(2,3,new QTableWidgetItem(QString::number(MAX)));

    isstartgeo=true;


}



MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::initSocket()
{

    mySocket = new QUdpSocket(this);
    mySocket2 = new QUdpSocket(this);
    int port = ui->le_localport->text().toInt();
    if(!mySocket->bind(port,QUdpSocket::ShareAddress|QUdpSocket::ReuseAddressHint))
        return 0;
    connect(mySocket,SIGNAL(readyRead()),this,SLOT(recvMsg()));
    return 1;
}

void MainWindow::recvMsg()
{


    //    qDebug()<<"recv";
    while(mySocket->hasPendingDatagrams())
    {

        QByteArray datagram;
        datagram.resize(mySocket->pendingDatagramSize());
        mySocket->readDatagram(datagram.data(),datagram.size());
        //        writeLog("recv data :",datagram);
        que_els_dmi->enqueue(datagram);

    }

}

void MainWindow::keyPressEvent(QKeyEvent* key)
{

    if(key->key()==Qt::Key_Q&&key->modifiers()==Qt::CTRL)
    {
        QApplication::exit();
    }

}

void MainWindow::setUifromData(DMI_ELS_Protocol &d)
{
    ui->le_msg_version->setText("0x"+QString::number(d.Message_Format_Version,16));
    ui->le_dmimsgnum->setText("0x"+QString::number(d.DMI_Message_Number,16));
    ui->le_dmimsgtime->setText("0x"+QString::number(d.DMI_Message_Time_Stamp,16));

    ui->le_dmistatus->setText("0x"+QString::number(d.DMI_Status,16));
    ui->le_displaystatus->setText(QString::number(d.Display_Status));

    if(d.Driver_Id>=0)
        ui->le_driverid->setText("0x"+QString::number(d.Driver_Id,16));
    else
        ui->le_driverid->setText(QString::number(d.Driver_Id));

    if(d.Schedule_Id>=0)
        ui->le_scheid->setText("0x"+QString::number(d.Schedule_Id,16));
    else
        ui->le_scheid->setText(QString::number(d.Schedule_Id));
    if(d.Service_Id>=0)
        ui->le_serviceid->setText("0x"+QString::number(d.Service_Id,16));
    else
        ui->le_serviceid->setText(QString::number(d.Service_Id));
    if(d.Trip_Id>=0)
        ui->le_tripid->setText("0x"+QString::number(d.Trip_Id,16));
    else
        ui->le_tripid->setText(QString::number(d.Trip_Id));
    if(d.Path_Id>=0)
        ui->le_pathid->setText("0x"+QString::number(d.Path_Id,16));
    else
        ui->le_pathid->setText(QString::number(d.Path_Id));
    if(d.Destination_Id>=0)
        ui->le_desid->setText("0x"+QString::number(d.Destination_Id,16));
    else
        ui->le_desid->setText(QString::number(d.Destination_Id));
    if(d.Manual_Location_Id>=0)
        ui->le_manuid->setText("0x"+QString::number(d.Manual_Location_Id,16));
    else
        ui->le_manuid->setText(QString::number(d.Manual_Location_Id));
    ui->le_manutimeupdate->setText("0x"+QString::number(d.Manual_Time_Update,16));
    ui->le_manutimevalidity->setText("0x"+QString::number(d.Manual_Time_Validity,16));

    ui->le_cprequest->setText(QString::number(d.Crossing_Priority_Request));

    ui->le_rrleft->setText(QString::number(d.RR_Left_Button));
    ui->le_rrright->setText(QString::number(d.RR_Right_Button));
    ui->le_rrstra->setText(QString::number(d.RR_Straight_Button));

    ui->le_elsmodesel->setText(QString::number(d.ELS_Mode_Selection));
    ui->le_timeshiftreq->setText(QString::number(d.Time_Shift_Request));

    if(d.OCC_Message_Number>0)
        ui->le_smstooccmsgnum->setText("0x"+QString::number(d.OCC_Message_Number,16));
    else
        ui->le_smstooccmsgnum->setText(QString::number(d.OCC_Message_Number));

    ui->le_smstooccmsglength->setText(QString::number(d.OCC_Message_Length));

    QString tmp="";
    for(int i=0;i<d.OCC_Message_Length;i++)
    {
        tmp+=" 0x"+QString::number(+d.OCC_Message_Text[i],16);

    }
    ui->le_smstooccmsgtxt->setText(tmp);

    if(d.OSS_Message_Number>0)
        ui->le_smstoossmsgnum->setText("0x"+QString::number(d.OSS_Message_Number,16));
    else
        ui->le_smstoossmsgnum->setText(QString::number(d.OSS_Message_Number));

    ui->le_smstoossmsglength->setText(QString::number(d.OSS_Message_Length));


    QString tmp2="";
    for(int i=0;i<d.OSS_Message_Length;i++)
    {
        tmp2+=" 0x"+QString::number(d.OSS_Message_Text[i],16);

    }
    ui->le_smstoossmsgtxt->setText(tmp2);


    if(d.Driver_Message_Number>0)
        ui->le_smstodrivermsgnu->setText("0x"+QString::number(d.Driver_Message_Number,16));
    else
        ui->le_smstodrivermsgnu->setText(QString::number(d.Driver_Message_Number));
}

void MainWindow::setUifromData(ELS_DMI_Protocol &d)
{
    ui->le_elsmsgversion->setText("0x"+QString::number(d.Message_Format_Version,16));
    ui->le_elselsmsgnum->setText("0x"+QString::number(d.ELS_Message_Number,16));
    ui->le_elselsmsgtime->setText("0x"+QString::number(d.ELS_Message_Time_Stamp,16));

    //    ui->le_dmictrl->setText(QString::number(d.DMI_Control));

    //    ui->le_elsinitialtime->setText("0x"+QString::number(d.Initialization_Time,16));
    if(d.Time_Zone>0)
        ui->le_elstimezone->setText("0x"+QString::number(d.Time_Zone));
    else
        ui->le_elstimezone->setText(QString::number(d.Time_Zone));

    ui->le_elsfuncdetailedsta->setText(QString::number(d.ELS_Function_Detailed_Status));
    ui->le_radiosta->setText(QString::number(d.Radio_Status));
    ui->le_systemok->setText(QString::number(d.System_Ok));

    ui->le_elssermode->setText(QString::number(d.ELS_Service_Mode));
    ui->le_tralocsta->setText(QString::number(d.Train_Location_Status));
    ui->le_comelsdms->setText(QString::number(d.Communication_ELS_DMS_Status));
    ui->le_radioelsdms->setText(QString::number(d.Radio_Coverage_ELS_DMS));
    ui->le_elsrrcpshutdown->setText(QString::number((d.ELS_RR_CP_Shutdown)));

    ui->le_logicaltrainid->setText("0x"+QString::number(d.Logical_Train_Id,16));
    ui->le_phytrainid->setText("0x"+QString::number(d.Physical_Train_Id,16));
    ui->le_elsdriverid->setText("0x"+QString::number(d.Driver_Id,16));
    ui->le_elslineid->setText("0x"+QString::number(d.Line_Id,16));
    ui->le_elsscheduleid->setText("0x"+QString::number(d.Schedule_Id,16));
    ui->le_elsserviceid->setText("0x"+QString::number(d.Service_Id,16));
    ui->le_elstripid->setText("0x"+QString::number(d.Trip_Id,16));
    ui->le_elspathid->setText("0x"+QString::number(d.Path_Id,16));
    ui->le_elsdesid->setText("0x"+QString::number(d.Destination_Id,16));


    ui->le_cussaid->setText("0x"+QString::number(d.Current_SSA_Id,16));
    ui->le_nextssa->setText("0x"+QString::number(d.Next_SSA_Id,16));
    //    ui->le_currssadeptime->setText("0x"+QString::number(d.Current_SSA_Depature_Time,16));
    //    ui->le_nextssaarrtime->setText("0x"+QString::number(d.Next_SSA_Arrival_Time,16));
    ui->le_passmission->setText(QString::number(d.Passenger_Mission));
    ui->le_runningtype->setText(QString::number(d.Running_Type));
    ui->le_skip->setText(QString::number(d.Skip_Next_SSA));
    ui->le_addelay->setText(QString::number(d.Advance_Delay_Time));
    ui->le_trainhold->setText(QString::number(d.Train_Hold));
    ui->le_turnback->setText(QString::number(d.Turn_Back_Required));
    ui->le_ssaofdriend->setText("0x"+QString::number(d.SSA_of_Driver_End_of_Service,16));
    ui->le_timeofdriend->setText("0x"+QString::number(d.Time_of_Driver_End_of_Service,16));
    ui->le_timetodriend->setText("0x"+QString::number(d.Time_to_Driver_End_of_Service ,16));

    ui->le_distoup->setText(QString::number(d.Distance_To_Upstream_Train));
    ui->le_distodown->setText(QString::number(d.Distance_To_Downstream_Train));
    ui->le_timetoup->setText(QString::number(d.Time_To_Upstream_Train));
    ui->le_timetodown->setText(QString::number(d.Time_To_Downstream_Train));
    ui->le_timeheadrequired->setText(QString::number(d.Time_Headway_Required));

    //RR Data
    ui->le_rroutesta->setText(QString::number(d.Right_Route_Status));
    ui->le_lroutesta->setText(QString::number(d.Left_Route_Status));
    ui->le_straroutesta->setText(QString::number(d.Straight_Route_Status));
    if(d.Distance_To_End_Selection_Area>=0)
        ui->le_distoendselearea->setText("0x"+QString::number(d.Distance_To_End_Selection_Area,16));
    else
        ui->le_distoendselearea->setText(QString::number(d.Distance_To_End_Selection_Area));
    ui->le_selearealen->setText("0x"+QString::number(d.Selection_Area_Length,16));
    ui->le_ackroutesta->setText(QString::number(d.spare));
    ui->le_rrareasta->setText(QString::number(d.Route_Request_Area_Status));
    ui->le_distorrbea->setText(QString::number(d.Distance_To_Station_RR_Beacon));
    ui->le_starrbealink->setText(QString::number(d.Station_RR_Beacon_Link));
    ui->le_timetoendsele->setText("0x"+QString::number(d.spare2,16));

    //CP Data
    ui->le_cpareasta->setText(QString::number(d.CP_Area_Status));
    if(d.CP_Distance_To_End_Preselection_Area>=0)
        ui->le_cpdistoendpreselearea->setText("0x"+QString::number(d.CP_Distance_To_End_Preselection_Area,16));
    else
        ui->le_cpdistoendpreselearea->setText(QString::number(d.CP_Distance_To_End_Preselection_Area));

    ui->le_cplengthpreselearea->setText("0x"+QString::number(d.CP_Length_Preselection_Area,16));
    ui->le_cpdistobea->setText(QString::number(d.CP_Distance_To_Beacon_of_CP_Request_Area));
    ui->le_cpbeasta->setText(QString::number(d.CP_Beacon_Of_CP_Request_Area_Status));

    //ATP Data
    ui->le_traprosta->setText(QString::number(d.Train_Protection_Control_Status));
    ui->le_atpinhista->setText(QString::number(d.ATP_Inhibition_Status));
    ui->le_currspeed->setText("0x"+QString::number(d.Current_Speed,16));
    ui->le_authspeed->setText("0x"+QString::number(d.Authorized_Speed,16));
    ui->le_inslow->setText(QString::number(d.In_Slowdown_Area));
    ui->le_atpwarning->setText(QString::number(d.ATP_Warning));
    ui->le_eb->setText(QString::number(d.Emergency_Braking_Applied));
    ui->le_sb->setText(QString::number(d.Service_Braking_Applied));
    ui->le_panto->setText(QString::number(d.Pantograph_Authorization_Status));
    ui->le_sanding->setText(QString::number(d.Sanding_Authorization_Status));
    ui->le_leftdoor->setText(QString::number(d.Left_Doors_Authorization_Status));
    ui->le_rightdoor->setText(QString::number(d.Right_Doors_Authorization_Status));
    ui->le_docking->setText(QString::number(d.Docking_Authorization_Status));




    //SMS To Driver Setting
    if(d.Driver_Message_Number>=0)
        ui->le_DriNum->setText("0x"+QString::number(d.Driver_Message_Number,16));
    else
        ui->le_DriNum->setText(QString::number(d.Driver_Message_Number));

    //    ui->le_Drivermsglen->setText(QString::number(d.Driver_Message_Length));


    if(d.Driver_Message_Length>0)
    {

        QString tmpdvrmsgtxt="";
        for(int i=0;i<d.Driver_Message_Length;i++)
        {
            tmpdvrmsgtxt+=" 0x"+QString::number(d.Driver_Message_Text[i],16);

        }
        ui->le_drimsgtxt->setText(tmpdvrmsgtxt);
    }


    //SMS To OCC Report
    if(d.OCC_Message_Number>=0)
        ui->le_occmsgnum->setText("0x"+QString::number(d.OCC_Message_Number,16));
    else
        ui->le_occmsgnum->setText(QString::number(d.OCC_Message_Number));
    ui->le_occmsgsta->setText(QString::number(d.OCC_Message_Status));

    //SMS To OSS Report
    if(d.OSS_Message_Number>=0)
        ui->le_ossmsgnum->setText("0x"+QString::number(d.OSS_Message_Number,16));
    else
        ui->le_ossmsgnum->setText(QString::number(d.OSS_Message_Number));



    QString tmpfaultid="";
    QString tmpfaulttime="";
    if(d.Number_of_Active_Fault>0)
    {
        for(int i=0;i<d.Number_of_Active_Fault;i++)
        {
            tmpfaultid+=" 0x"+QString::number(d.Id_of_Fault[i],16);
            tmpfaulttime+=" 0x"+QString::number(d.Time_of_Appearance[i],16);
        }
    }


    //Geographic Events

    QString tmpeventid="";
    QString tmpeventoutput="";
    QString tmpdistobegin="";
    QString tmpdistoend="";
    if(d.Number_of_Active_Events>0)
    {
        for(int i=0;i<d.Number_of_Active_Events;i++)
        {
            tmpeventid+=" "+QString::number(d.Event_Id[i]);
            tmpeventoutput+=" "+QString::number(d.Event_Output_Value[i]);
            tmpdistobegin+=" "+QString::number(d.Geographic_Distance_To_begin[i]);
            tmpdistoend+=" "+QString::number(d.Geographic_Distance_To_End[i]);
        }
    }





}

void MainWindow::randomData(bool isDMI)
{
    QTime time;
    time=QTime::currentTime();
    qsrand(time.msec()+time.second()*1000);
    if(isDMI)
    {
        ui->le_msg_version->setText(QString::number(qrand()%256));
        ui->le_dmimsgnum->setText(QString::number(qrand()%65536));
        ui->le_dmimsgtime->setText(QString::number(qrand()%65536));

        ui->le_dmistatus->setText(QString::number(qrand()%2));
        ui->le_displaystatus->setText(QString::number(qrand()%2));

        ui->le_driverid->setText(QString::number(qrand()%32769-1));
        ui->le_scheid->setText(QString::number(qrand()%32769-1));
        ui->le_serviceid->setText(QString::number(qrand()%32769-1));
        ui->le_tripid->setText(QString::number(qrand()%32769-1));
        ui->le_pathid->setText(QString::number(qrand()%32769-1));
        ui->le_desid->setText(QString::number(qrand()%32769-1));
        ui->le_manuid->setText(QString::number(qrand()%32769-1));
        ui->le_manutimeupdate->setText(QString::number(qrand()%32769-1));
        ui->le_manutimevalidity->setText(QString::number(qrand()%2));

        ui->le_cprequest->setText(QString::number(qrand()%2));

        ui->le_rrleft->setText(QString::number(qrand()%2));
        ui->le_rrright->setText(QString::number(qrand()%2));
        ui->le_rrstra->setText(QString::number(qrand()%2));

        ui->le_elsmodesel->setText(QString::number(qrand()%4));
        ui->le_timeshiftreq->setText(QString::number(qrand()%2));

        ui->le_smstooccmsgnum->setText(QString::number(qrand()%32769-1));
        ui->le_smstooccmsglength->setText(QString::number(qrand()%141));

        ui->le_smstoossmsgnum->setText(QString::number(qrand()%32769-1));
        ui->le_smstoossmsglength->setText(QString::number(qrand()%141));

        ui->le_smstodrivermsgnu->setText(QString::number(qrand()%32769-1));

    }
    else
    {
        ui->le_elsmsgversion->setText(QString::number(qrand()%256));
        ui->le_elselsmsgnum->setText(QString::number(qrand()%65536));
        ui->le_elselsmsgtime->setText(QString::number(qrand()%65536));
        ui->wdg_intialtime->setDateTime(QDateTime::currentDateTime());

        //                ui->le_elsinitialtime->setText(QString::number(qrand()%65536));
        ui->le_elstimezone->setText(QString::number(qrand()%105-48));

        //        ui->le_elsfuncdetailedsta->setText(QString::number(qrand()%16));
        ui->le_elsfuncdetailedsta->setText(QString::number(15));
        ui->le_radiosta->setText(QString::number(qrand()%2));
        ui->le_systemok->setText(QString::number(qrand()%2));

        ui->le_elssermode->setText(QString::number(qrand()%4));
        ui->le_tralocsta->setText(QString::number(qrand()%3));
        ui->le_comelsdms->setText(QString::number(qrand()%2));
        ui->le_radioelsdms->setText(QString::number(qrand()%3));
        ui->le_elsrrcpshutdown->setText(QString::number(qrand()%3));

        ui->le_logicaltrainid->setText(QString::number(qrand()%65536));
        ui->le_phytrainid->setText(QString::number(qrand()%65536));
        ui->le_elsdriverid->setText(QString::number(qrand()%32768));
        ui->le_elslineid->setText(QString::number(qrand()%32768));
        ui->le_elsscheduleid->setText(QString::number(qrand()%6));
        ui->le_elsserviceid->setText(QString::number(qrand()%32768));
        ui->le_elstripid->setText(QString::number(qrand()%32768));
        ui->le_elspathid->setText(QString::number(qrand()%32768));
        ui->le_elsdesid->setText(QString::number(qrand()%6));

        ui->le_cussaid->setText(QString::number(qrand()%6));
        ui->le_nextssa->setText(QString::number(qrand()%6));
        //        ui->le_currssadeptime->setText(QString::number(qrand()%65536));
        //        ui->le_nextssaarrtime->setText(QString::number(qrand()%65536));
        ui->le_passmission->setText(QString::number(qrand()%3));
        ui->le_runningtype->setText(QString::number(qrand()%4));
        ui->le_skip->setText(QString::number(qrand()%2));
        ui->le_addelay->setText(QString::number((qrand()%100)-50));
        ui->le_trainhold->setText(QString::number(qrand()%3));
        ui->le_turnback->setText(QString::number(qrand()%4));
        ui->le_ssaofdriend->setText(QString::number(qrand()%65536));
        ui->le_timeofdriend->setText(QString::number(qrand()%65536));
        ui->le_timetodriend->setText(QString::number(qrand()%65536));


        ui->le_distoup->setText(QString::number(qrand()%1001));
        ui->le_distodown->setText(QString::number(qrand()%1001));
        ui->le_timetoup->setText(QString::number(qrand()%60));
        ui->le_timetodown->setText(QString::number(qrand()%60));
        ui->le_timeheadrequired->setText(QString::number(qrand()%3601));

        //RR和CP需要依照一定逻辑，DMI上才能显示效果，因此不做随机数，需要人手工输入发送值
        ui->le_cpareasta->setText(QString::number(qrand()%2));
        ui->le_cplengthpreselearea->setText(QString::number(qrand()%201));
        ui->le_cpdistoendpreselearea->setText(QString::number(qrand()%181));

        ui->le_traprosta->setText(QString::number(qrand()%4));
        ui->le_atpinhista->setText(QString::number(qrand()%2));
        //        ui->le_currspeed->setText(QString::number(qrand()%100));
        //        ui->le_authspeed->setText(QString::number(qrand()%100));
        quint8 curspeed=qrand()%100;
        quint8 auspeed1=curspeed+10;
        ui->le_currspeed->setText(QString::number(curspeed));
        ui->le_authspeed->setText(QString::number(auspeed1));

        ui->le_drimsgtxt->setText("前方大雾，请注意瞭望。 ");
        ui->le_inslow->setText(QString::number(qrand()%2));
        ui->le_atpwarning->setText(QString::number(qrand()%4));
        //        ui->le_eb->setText(QString::number(qrand()%2));
        //        ui->le_sb->setText(QString::number(qrand()%2));

        ui->le_eb->setText(QString::number(0));
        ui->le_sb->setText(QString::number(0));
        ui->le_panto->setText(QString::number(qrand()%3));
        ui->le_sanding->setText(QString::number(qrand()%3));
        ui->le_leftdoor->setText(QString::number(qrand()%3));
        ui->le_rightdoor->setText(QString::number(qrand()%3));
        ui->le_docking->setText(QString::number(qrand()%3));



        ui->le_DriNum->setText(QString::number(qrand()%32769-1));
        //        ui->le_Drivermsglen->setText(QString::number(qrand()%141));

        ui->le_occmsgnum->setText(QString::number(qrand()%32769-1));
        ui->le_occmsgsta->setText(QString::number(qrand()%4));
        ui->le_ossmsgnum->setText(QString::number(qrand()%32769-1));


        //        ui->le_back->setText(QString::number(qrand()%4+1));
        //        ui->le_type->setText(QString::number(qrand()%2+1));
        //        ui->le_position->setText(QString::number(qrand()%4+1));
        //        ui->le_value->setText(QString::number(qrand()%3+1));

#ifdef Baseline_2_0
        ui->le_warning_sig_infi->setText(QString::number(qrand()%4));
        ui->le_warningpsrover->setText(QString::number(qrand()%4));
        ui->le_psroverspeed->setText(QString::number(qrand()%4));
        ui->le_sig_status->setText(QString::number(qrand()%5));
#endif
    }
}

void MainWindow::getDatafromUi(DMI_ELS_Protocol &d)
{
    d.Message_Format_Version=ui->le_msg_version->text().toInt();
    d.DMI_Message_Number=ui->le_dmimsgnum->text().toInt();
    d.DMI_Message_Time_Stamp=ui->le_dmimsgtime->text().toInt();

    d.DMI_Status=ui->le_dmistatus->text().toInt();
    d.Display_Status=ui->le_displaystatus->text().toInt();

    d.Driver_Id=ui->le_driverid->text().toInt();
    d.Schedule_Id=ui->le_scheid->text().toInt();
    d.Service_Id=ui->le_serviceid->text().toInt();
    d.Trip_Id=ui->le_tripid->text().toInt();
    d.Path_Id=ui->le_pathid->text().toInt();
    d.Destination_Id=ui->le_desid->text().toInt();
    d.Manual_Location_Id=ui->le_manuid->text().toInt();
    d.Manual_Time_Update=ui->le_manutimeupdate->text().toInt();
    d.Manual_Time_Validity=ui->le_manutimevalidity->text().toInt();

    d.Crossing_Priority_Request=ui->le_cprequest->text().toInt();

    d.RR_Left_Button=ui->le_rrleft->text().toInt();
    d.RR_Right_Button=ui->le_rrright->text().toInt();
    d.RR_Straight_Button=ui->le_rrstra->text().toInt();

    d.ELS_Mode_Selection=ui->le_elsmodesel->text().toInt();
    d.Time_Shift_Request=ui->le_timeshiftreq->text().toInt();

    d.OCC_Message_Number=ui->le_smstooccmsgnum->text().toInt();
    d.OCC_Message_Length=ui->le_smstooccmsglength->text().toInt();
    if(d.OCC_Message_Length>0)
    {
        d.OCC_Message_Text = new quint8[d.OCC_Message_Length];
        for(int i=0;i<d.OCC_Message_Length;i++)
            d.OCC_Message_Text[i]=1;
    }

    d.OSS_Message_Number=ui->le_smstoossmsgnum->text().toInt();
    d.OSS_Message_Length=ui->le_smstoossmsglength->text().toInt();
    if(d.OSS_Message_Length>0)
    {
        d.OSS_Message_Text=new quint8[d.OSS_Message_Length];
        for(int i=0;i<d.OSS_Message_Length;i++)
            d.OSS_Message_Text[i]=2;
    }

    d.Driver_Message_Number=ui->le_smstodrivermsgnu->text().toInt();

}

void MainWindow::getDatafromUi(ELS_DMI_Protocol &d)
{
    d.Message_Format_Version=ui->le_elsmsgversion->text().toInt();
    d.ELS_Message_Number=ui->le_elselsmsgnum->text().toInt();
    quint32 timestamp =QDateTime::currentDateTime().toTime_t()-tmpsub+32*15*60;//sub 32*15*60ss timezone
    //    quint64 tmp64=tmptime>>32;

    d.ELS_Message_Time_Stamp=(quint64)timestamp<<32;


    d.Time_Zone=32;
    quint32 tmptime = ui->wdg_intialtime->dateTime().toTime_t()-tmpsub;//sub 32*15*60ss timezone
    //    quint64 tmp64=tmptime>>32;

    d.Current_Time=(quint64)tmptime<<32;
    //    qDebug()<<"initialtime"<<hex<<tmptime<<d.Initialization_Time;



    d.ELS_Function_Detailed_Status=ui->le_elsfuncdetailedsta->text().toUInt();
    //    qDebug()<<"elsfunc"<<ui->le_elsfuncdetailedsta->text().toUInt(0,16)<<ui->le_elsfuncdetailedsta->text();
    d.Radio_Status=ui->le_radiosta->text().toInt();
    d.System_Ok=ui->le_systemok->text().toInt();

    //    qDebug()<<"simulator"<<ui->le_elssermode->text()<<d.ELS_Service_Mode;
    d.ELS_Service_Mode=ui->le_elssermode->text().toInt();
    d.Train_Location_Status=ui->le_tralocsta->text().toInt();
    d.Communication_ELS_DMS_Status=ui->le_comelsdms->text().toInt();
    d.Radio_Coverage_ELS_DMS=ui->le_radioelsdms->text().toInt();
    d.ELS_RR_CP_Shutdown=ui->le_elsrrcpshutdown->text().toInt();

    d.Logical_Train_Id=ui->le_logicaltrainid->text().toInt();
    d.Physical_Train_Id=ui->le_phytrainid->text().toInt();
    d.Driver_Id=ui->le_elsdriverid->text().toInt();
    d.Line_Id=ui->le_elslineid->text().toInt();
    d.Schedule_Id=ui->le_elsscheduleid->text().toInt();
    d.Service_Id=ui->le_elsserviceid->text().toInt();
    d.Trip_Id=ui->le_elstripid->text().toInt();
    d.Path_Id=ui->le_elspathid->text().toInt();
    d.Destination_Id=ui->le_elsdesid->text().toInt();

    d.Current_SSA_Id=ui->le_cussaid->text().toInt();
    d.Next_SSA_Id=ui->le_nextssa->text().toInt();

    //    d.Current_SSA_Depature_Time=ui->le_currssadeptime->text().toInt();
    //    d.Next_SSA_Arrival_Time=ui->le_nextssaarrtime->text().toInt();

    if(!ui->checkBox_dep->isChecked())
    {
        quint32 tmpcurdeptime = ui->wdg_curdeptime->dateTime().toTime_t()-tmpsub;
        d.Current_SSA_Depature_Time=(quint64)tmpcurdeptime<<32;
    }
    else
    {
        d.Current_SSA_Depature_Time=0;
    }

    if(!ui->checkBox_arr->isChecked())
    {
        quint32 tmpnextarrtime=ui->wdg_nextarrtime->dateTime().toTime_t()-tmpsub;
        d.Next_SSA_Arrival_Time=(quint64)tmpnextarrtime<<32;
    }
    else
    {
        d.Next_SSA_Arrival_Time=0;
    }
    d.Passenger_Mission=ui->le_passmission->text().toInt();
    d.Running_Type=ui->le_runningtype->text().toInt();
    d.Skip_Next_SSA=ui->le_skip->text().toInt();
    d.Advance_Delay_Time=ui->le_addelay->text().toInt();
    d.Train_Hold=ui->le_trainhold->text().toInt();
    d.Turn_Back_Required=ui->le_turnback->text().toInt();
    d.SSA_of_Driver_End_of_Service=ui->le_ssaofdriend->text().toInt();
    d.Time_of_Driver_End_of_Service=ui->le_timeofdriend->text().toInt();
    d.Time_to_Driver_End_of_Service=ui->le_timetodriend->text().toInt();

    d.Distance_To_Upstream_Train=ui->le_distoup->text().toInt();
    d.Distance_To_Downstream_Train=ui->le_distodown->text().toInt();
    d.Time_To_Upstream_Train=ui->le_timetoup->text().toInt();
    d.Time_To_Downstream_Train=ui->le_timetodown->text().toInt();
    d.Time_Headway_Required=ui->le_timeheadrequired->text().toInt();

    d.Right_Route_Status=ui->le_rroutesta->text().toInt();
    d.Left_Route_Status=ui->le_lroutesta->text().toInt();
    d.Straight_Route_Status=ui->le_straroutesta->text().toInt();
    d.Distance_To_End_Selection_Area=ui->le_distoendselearea->text().toInt();
    d.Selection_Area_Length=ui->le_selearealen->text().toInt();
    d.spare=ui->le_ackroutesta->text().toInt();
    d.Route_Request_Area_Status=ui->le_rrareasta->text().toInt();
    d.Distance_To_Station_RR_Beacon=ui->le_distorrbea->text().toInt();
    d.Station_RR_Beacon_Link=ui->le_starrbealink->text().toInt();
    d.spare2=ui->le_timetoendsele->text().toInt();

    d.CP_Area_Status=ui->le_cpareasta->text().toInt();
    d.CP_Distance_To_End_Preselection_Area=ui->le_cpdistoendpreselearea->text().toInt();
    d.CP_Length_Preselection_Area=ui->le_cplengthpreselearea->text().toInt();
    d.CP_Distance_To_Beacon_of_CP_Request_Area=ui->le_cpdistobea->text().toInt();
    d.CP_Beacon_Of_CP_Request_Area_Status=ui->le_cpbeasta->text().toInt();

    d.Train_Protection_Control_Status=ui->le_traprosta->text().toInt();
    d.ATP_Inhibition_Status=ui->le_atpinhista->text().toInt();
    //    d.Current_Speed=ui->le_currspeed->text().toInt();
    d.ELS_Current_Speed=ui->le_currspeed->text().toInt();
    d.Authorized_Speed=ui->le_authspeed->text().toInt();
    d.In_Slowdown_Area=ui->le_inslow->text().toInt();
    d.ATP_Warning=ui->le_atpwarning->text().toInt();
    d.Emergency_Braking_Applied=ui->le_eb->text().toInt();
    d.Service_Braking_Applied=ui->le_sb->text().toInt();
    d.Pantograph_Authorization_Status=ui->le_panto->text().toInt();
    d.Sanding_Authorization_Status=ui->le_sanding->text().toInt();
    d.Left_Doors_Authorization_Status=ui->le_leftdoor->text().toInt();
    d.Right_Doors_Authorization_Status=ui->le_rightdoor->text().toInt();
    d.Docking_Authorization_Status=ui->le_docking->text().toInt();

    d.Number_of_Schedule= ui->tblwdg_schedule->rowCount();
    if(d.Number_of_Schedule>0)
    {
        //        qDebug()<<d.Number_of_Schedule;
        d.Id_of_schedules=new quint16[d.Number_of_Schedule];
        for(int i=0;i<d.Number_of_Schedule;i++ )
        {

            d.Id_of_schedules[i]=ui->tblwdg_schedule->item(i,0)->text().toUShort();
            //            qDebug()<<d.Id_of_schedules[i];
        }
    }

    d.Number_of_Service= ui->tblwdg_serv->rowCount();
    if(d.Number_of_Service>0)
    {
        d.Id_of_services=new quint16[d.Number_of_Service];
        for(int i=0;i<d.Number_of_Service;i++ )
        {
            d.Id_of_services[i]=ui->tblwdg_serv->item(i,0)->text().toUShort();
        }
    }

    d.Number_of_Trip= ui->tblwdg_trip->rowCount();
    if(d.Number_of_Trip>0)
    {
        d.Id_of_Trips=new quint16[d.Number_of_Trip];
        for(int i=0;i<d.Number_of_Trip;i++ )
        {
            d.Id_of_Trips[i]=ui->tblwdg_trip->item(i,0)->text().toUShort();
        }
    }

    d.Number_of_Path= ui->tblwdg_path->rowCount();
    if(d.Number_of_Path>0)
    {
        d.Id_of_Paths=new quint16[d.Number_of_Path];
        for(int i=0;i<d.Number_of_Path;i++ )
        {
            d.Id_of_Paths[i]=ui->tblwdg_path->item(i,0)->text().toUShort();
        }
    }

    d.Number_of_Destinations= ui->tblwdg_des->rowCount();
    //    qDebug()<<"desnum"<<d.Number_of_Destinations;
    if(d.Number_of_Destinations>0)
    {
        d.Id_of_Destinations=new quint16[d.Number_of_Destinations];
        for(int i=0;i<d.Number_of_Destinations;i++ )
        {
            d.Id_of_Destinations[i]=ui->tblwdg_des->item(i,0)->text().toUShort();
        }
    }

#ifdef Baseline_2_0
    d.BCM_Status=ui->le_bcm->text().toUInt();
    d.Radar_Status=ui->le_radar->text().toUInt();
    d.GPS_Status=ui->le_gps->text().toUInt();
    d.Distance_To_Signal=ui->le_distosig->text().toUInt();
    d.Signal_Status=ui->le_sig_status->text().toUInt();
    d.Warning_Signal_Anticipation=ui->le_warning_sig_anti->text().toUInt();
    d.Warning_Signal_Infringement=ui->le_warning_sig_infi->text().toUInt();
    d.Distance_To_Next_Restrictive_PSR=ui->le_distonextpsr->text().toUInt();
    d.Next_Restrictive_PSR_Speed=ui->le_nextpsrspeed->text().toUInt();
    d.Warning_PSR_Slowdown_Overspeed=ui->le_psroverspeed->text().toUInt();
    d.Current_PSR_Speed=ui->le_currentpsrspeed->text().toUInt();
    d.Warning_PSR_Overspeed=ui->le_warningpsrover->text().toUInt();
    d.RS_Max_Speed=ui->le_rsmax->text().toUInt();
    d.Warning_RS_Speed_Overspeed=ui->le_warningrs->text().toUInt();
    d.Radar_Speed=ui->le_radarspeed->text().toUInt();
    d.Risk_Level=ui->le_risklevel->text().toUInt();
    d.Size_Of_Additional_Data=ui->le_sizeofaddition->text().toUInt();

    d.Obstacle_Total_Num=0;
#endif

#ifdef Baseline_2_0
    if(issendtracklayout)
    {
        dms_dmi_data.Bitmap_Length=64;
        d.DMS_DMI_Data_Size=sizeof(dms_dmi_data)-sizeof(dms_dmi_data.Bitmap)
                +sizeof(quint8)*dms_dmi_data.Bitmap_Length;
        QByteArray bytes;
        bytes.resize(d.DMS_DMI_Data_Size);

        dms_dmi_data.Signal_ID=ui->le_back->text().toInt();
        dms_dmi_data.RTU_Type=ui->le_type->text().toInt();
        dms_dmi_data.RTU_ID=ui->le_position->text().toInt();
        dms_dmi_data.Signal_Status=ui->le_value->text().toInt();
        dms_dmi_data.Bitmap=new quint8[dms_dmi_data.Bitmap_Length];

        for(int i=0;i<dms_dmi_data.Bitmap_Length;i++)
        {
            dms_dmi_data.Bitmap[i]=0;
        }
//        dms_dmi_data.Bitmap[0]=ui->le_value->text().toInt();
//        dms_dmi_data.Bitmap[1]=ui->le_resvalue->text().toInt();
//        dms_dmi_data.Bitmap[2]=ui->le_resvalue_2->text().toInt();

        quint8 bit=ui->le_sigbit->text().toUInt();
        if(ui->chksig->isChecked())
            (dms_dmi_data.Bitmap[bit/8])|=(1<<bit%8);
        else
            (dms_dmi_data.Bitmap[bit/8])&=(~(1<<bit%8));
        qint8 result=(dms_dmi_data.Bitmap[bit/8]&=(1<<bit%8))>>bit%8;
//        qDebug()<<"in getdata bit="<<bit<<result;





        dms_dmi_data.setBytesFromData(bytes);
        dms_dmi_data.freePointer();


        d.DMS_DMI_Data = new quint8[d.DMS_DMI_Data_Size];
        for(int i=0;i<d.DMS_DMI_Data_Size;i++)
        {
            d.DMS_DMI_Data[i]=bytes[i];
        }
    }
    else
    {
        d.DMS_DMI_Data_Size=0;
    }
#endif

//    qDebug()<<issmsconfirm;
    if(issmsconfirm)
    {
        issmsconfirm=false;


        d.Driver_Message_Number=ui->le_DriNum->text().toInt();

        QString dritxt=ui->le_drimsgtxt->text();
//        qDebug()<<"Dd"<<dritxt;
        if(dritxt!="")
        {
            QByteArray tmpdritxt= dritxt.toUtf8();
            int tmplen=tmpdritxt.length();

            if (tmplen>139)
            {
                //            qDebug()<<"over size in sms"<<tmplen;
                return;
            }
            //        qDebug()<<tmplen;
            d.Driver_Message_Length=tmplen+1;
            ui->le_Drivermsglen_test->setText(QString::number(d.Driver_Message_Length));

            //        qDebug()<<"driver sms length"<<d.Driver_Message_Length;ffffffffffffff
            d.Driver_Message_Text=new quint8[d.Driver_Message_Length];
            for(int i=0;i<d.Driver_Message_Length-1;i++)
            {
                d.Driver_Message_Text[i]=((quint8*)tmpdritxt.data())[i]; //必须深拷贝，否则delete error
            }
            d.Driver_Message_Text[d.Driver_Message_Length-1]='\0';
            //        for(int i=0;i<tmplen;i++)
            //            qDebug()<<"tmp"<<tmpdritxt.data()[i];
            //        for(int j=0;j<d.Driver_Message_Length;j++)
            //            qDebug()<<"dri"<<d.Driver_Message_Text[j];
            //       ui->le_drimsgtxt->setText("");
        }


    }

    d.OCC_Message_Number=ui->le_occmsgnum->text().toInt();
    d.OCC_Message_Status=ui->le_occmsgsta->text().toInt();

    d.OSS_Message_Number=ui->le_ossmsgnum->text().toInt();

    d.Number_of_Active_Fault=ui->tblwdg_fault->rowCount();
    if(d.Number_of_Active_Fault>0)
    {
        d.Id_of_Fault=new quint16[d.Number_of_Active_Fault];
        d.Time_of_Appearance=new quint64[d.Number_of_Active_Fault];
        for(int i=0;i<d.Number_of_Active_Fault;i++)
        {
            d.Id_of_Fault[i]=ui->tblwdg_fault->item(i,0)->text().toInt();
            quint32 tmp=ui->tblwdg_fault->item(i,1)->text().toInt()+ui->wdg_intialtime->dateTime().toTime_t()-tmpsub;
            d.Time_of_Appearance[i]=(quint64)tmp<<32;
            //            d.Time_of_Appearance[i]=ui->tblwdg_fault->item(i,1)->text().toInt();
        }
    }
    d.Number_of_Active_Events=ui->tblwdg_geo->rowCount();
    //    qDebug()<<"simlator number events"<<d.Number_of_Active_Events;
    if(d.Number_of_Active_Events>0)
    {
        d.Event_Id=new quint8[d.Number_of_Active_Events];
        d.Event_Output_Value=new quint8[d.Number_of_Active_Events];
        d.Geographic_Distance_To_begin=new quint16[d.Number_of_Active_Events];
        d.Geographic_Distance_To_End= new quint16[d.Number_of_Active_Events];

        for(int i=0;i<d.Number_of_Active_Events;i++)
        {

            d.Event_Id[i]=ui->tblwdg_geo->item(i,0)->text().toInt();
            d.Event_Output_Value[i]=ui->tblwdg_geo->item(i,1)->text().toInt();
            d.Geographic_Distance_To_begin[i]=ui->tblwdg_geo->item(i,2)->text().toInt();
            d.Geographic_Distance_To_End[i]=ui->tblwdg_geo->item(i,3)->text().toInt();
            //            qDebug()<<QDateTime::currentMSecsSinceEpoch()<<d.Event_Id[i]<<d.Event_Output_Value[i]<<d.Geographic_Distance_To_begin[i]<<d.Geographic_Distance_To_End[i];
        }
    }

#ifdef Baseline_2_0
    d.Obstacle_Total_Num=ui->tblwdg_radar->rowCount();
    //    qDebug()<<"simlator number events"<<d.Number_of_Active_Events;
    if(d.Obstacle_Total_Num>0)
    {
        d.Obstacle_ID=new quint8[d.Obstacle_Total_Num];
        d.Alarm_Level=new quint8[d.Obstacle_Total_Num];
        d.Obstacle_Straight_Distance=new quint8[d.Obstacle_Total_Num];
        d.Obstacle_Lateral_Distance= new qint8[d.Obstacle_Total_Num];
        d.Obstacle_Attribute=new quint8[d.Obstacle_Total_Num];

        for(int i=0;i<d.Obstacle_Total_Num;i++)
        {

            d.Obstacle_ID[i]=ui->tblwdg_radar->item(i,0)->text().toInt();
            d.Alarm_Level[i]=ui->tblwdg_radar->item(i,1)->text().toInt();
            d.Obstacle_Straight_Distance[i]=ui->tblwdg_radar->item(i,2)->text().toInt();
            d.Obstacle_Lateral_Distance[i]=ui->tblwdg_radar->item(i,3)->text().toInt();
            d.Obstacle_Attribute[i]=ui->tblwdg_radar->item(i,4)->text().toInt();
        }
    }
#endif

}

void MainWindow::clearUiDMI()
{
    ui->le_msg_version->setText("");
    ui->le_dmimsgnum->setText("");
    ui->le_dmimsgtime->setText("");

    ui->le_dmistatus->setText("");
    ui->le_displaystatus->setText("");

    ui->le_driverid->setText("");
    ui->le_scheid->setText("");
    ui->le_serviceid->setText("");
    ui->le_tripid->setText("");
    ui->le_pathid->setText("");
    ui->le_desid->setText("");
    ui->le_manuid->setText("");
    ui->le_manutimeupdate->setText("");
    ui->le_manutimevalidity->setText("");

    ui->le_cprequest->setText("");

    ui->le_rrleft->setText("");
    ui->le_rrright->setText("");
    ui->le_rrstra->setText("");

    ui->le_elsmodesel->setText("");
    ui->le_timeshiftreq->setText("");

    ui->le_smstooccmsgnum->setText("");
    ui->le_smstooccmsglength->setText("");
    ui->le_smstooccmsgtxt->setText("");

    ui->le_smstoossmsgnum->setText("");
    ui->le_smstoossmsglength->setText("");
    ui->le_smstoossmsgtxt->setText("");


    ui->le_smstodrivermsgnu->setText("");

}

void MainWindow::clearUiELS()
{

}

int MainWindow::openFile()
{
    QString date= QDate::currentDate().toString("yyyy-MM-dd");
    qFile.setFileName("casco dmi "+date+".txt");
    if(!qFile.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Append))
    {
        return 0;
    }
    qts.setDevice(&qFile);
    return 1;
}

void MainWindow::writeLog(QString s,QByteArray bytearray)
{
    QString date= QDate::currentDate().toString("yyyy-MM-dd");
    QString time = QTime::currentTime().toString("hh:mm:ss");
    qts<<date<<" "<<time<<" "<<s<<endl;
    if(bytearray!=NULL)
    {
        char *c = bytearray.data();
        qts<<"size is "<<QString::number(bytearray.count())<<endl;
        for(int i=0;i<bytearray.size();i++)
        {
            qts<<hex<<(quint8)c[i]<<" ";
        }
        qts<<endl;
    }
}

void  MainWindow::giveValueFromDMIToELS()
{
    //从dmi界面上获得数据
    int tmpdriverid=ui->le_driverid->text().toInt(0,16);
    int tmpscheduleid =ui->le_scheid->text().toInt(0,16);
    int tmpserviceid=ui->le_serviceid->text().toInt(0,16);
    int tmptripid=ui->le_tripid->text().toInt(0,16);
    int tmppathid=ui->le_pathid->text().toInt(0,16);
    int tmpdesid=ui->le_desid->text().toInt(0,16);
    int tmpelservicemode=ui->le_elsmodesel->text().toInt(0,16);
    int timeshift=ui->le_timeshiftreq->text().toInt();

    //更新到els上
    if(tmpdriverid!=-1)
    {
        //            qDebug()<<"tmpdriverid"<<tmpdriverid;
        ui->le_elsdriverid->setText(QString::number(tmpdriverid));
    }
    if(tmpscheduleid!=-1)
    {
        ui->le_elsscheduleid->setText(QString::number(tmpscheduleid));

    }
    if(tmpserviceid!=-1)
    {
        ui->le_elsserviceid->setText(QString::number(tmpserviceid));
    }
    if(tmptripid!=-1)
    {
        ui->le_elstripid->setText(QString::number(tmptripid));
    }
    if(tmppathid!=-1)
    {
        ui->le_elspathid->setText(QString::number(tmppathid));
    }

    if(tmpdesid!=-1)
    {
        ui->le_elsdesid->setText(QString::number(tmpdesid));
    }

    if(tmpelservicemode!=0)
    {
        ui->le_elssermode->setText(QString::number(tmpelservicemode));
    }
    if(timeshift!=0)
    {
        ui->le_addelay->setText("0");
    }
}

void MainWindow::sendMsg(bool isdmi)
{
    //    qDebug()<<"sendmsg"<<QDateTime::currentMSecsSinceEpoch();
    QByteArray qsend,qsend2;
    //    if(isdmi)
    //    {
    //        if(ui->chkstep->isChecked())
    //        {
    //            switch(ui->le_stepno->text().toInt())
    //            {
    //            case 1:
    //                dmi_els_data.stepOne();
    //                break;
    //            case 2:
    //                dmi_els_data.stepTwo();
    //                break;
    //            case 3:
    //                dmi_els_data.stepThree();
    //                break;
    //            }

    //            dmi_els_data.DMI_Message_Number++;
    //            setUifromData(dmi_els_data);  //将要发送的数据显示在界面上
    //        }
    //        else
    //        {
    //            getDatafromUi(dmi_els_data);

    //        }
    //        int sendlength = sizeof(dmi_els_data)-sizeof(dmi_els_data.OCC_Message_Text)
    //                +dmi_els_data.OCC_Message_Length-sizeof(dmi_els_data.OSS_Message_Text)+sizeof(quint8)*dmi_els_data.OSS_Message_Length;
    //        qsend.resize(sendlength);
    //        dmi_els_data.setBytesFromData(qsend);
    //        dmi_els_data.freePointer();

    //        int elsport=ui->le_elsport->text().toInt();
    //        QString elsip=ui->le_elsip->text();



    //        int  sendsize =mySocket->writeDatagram(qsend,QHostAddress(elsip),elsport);
    //        writeLog("dmi_els send data is "+QString::number(sendsize)+"bytes",qsend);

    //    }
    //    else
    {
        if(ui->chkstep->isChecked())
        {
            switch(ui->le_stepno->text().toInt())
            {
            case 1:
                els_dmi_data.stepOne();
                break;
            case 2:
                els_dmi_data.stepTwo();
                break;
            case 3:
                els_dmi_data.stepThree();
                break;
            }

            els_dmi_data.ELS_Message_Number++;
            setUifromData(els_dmi_data);  //将要发送的数据显示在界面上
        }
        else
        {
            //            qDebug()<<"send time"<<QDateTime::currentMSecsSinceEpoch();
            getDatafromUi(els_dmi_data);
        }

        int sendlength=sizeof(els_dmi_data)
                -sizeof(els_dmi_data.Id_of_schedules)+sizeof(quint16)*els_dmi_data.Number_of_Schedule
                -sizeof(els_dmi_data.Id_of_services)+sizeof(quint16)*els_dmi_data.Number_of_Service
                -sizeof(els_dmi_data.Id_of_Trips)+sizeof(quint16)*els_dmi_data.Number_of_Trip
                -sizeof(els_dmi_data.Id_of_Paths)+sizeof(quint16)*els_dmi_data.Number_of_Path
                -sizeof(els_dmi_data.Id_of_Destinations)+sizeof(quint16)*els_dmi_data.Number_of_Destinations
                -sizeof(els_dmi_data.Driver_Message_Text)+sizeof(quint8)*els_dmi_data.Driver_Message_Length
                -sizeof(els_dmi_data.Id_of_Fault)-sizeof(els_dmi_data.Time_of_Appearance)
                +(sizeof(quint16)+sizeof(quint64))*els_dmi_data.Number_of_Active_Fault
                -sizeof(els_dmi_data.Event_Id)-sizeof(els_dmi_data.Event_Output_Value)
                -sizeof(els_dmi_data.Geographic_Distance_To_begin)-sizeof(els_dmi_data.Geographic_Distance_To_End)
                +(sizeof(quint8)+sizeof(quint16))*2*els_dmi_data.Number_of_Active_Events;
#ifdef Baseline_2_0
        sendlength +=els_dmi_data.DMS_DMI_Data_Size;
        //        qDebug()<<sendlength<<"dmsdmidatasize"<<(els_dmi_data.DMS_DMI_Data_Size);

#endif

        qsend.resize(sendlength);


        int port1,port2;
        QString ip1,ip2;
        port1=ui->le_dmi1port->text().toInt();
        ip1=ui->le_dmi1ip->text();
        port2=ui->le_dmi2port->text().toInt();
        ip2=ui->le_dmi2ip->text();

        if(ui->chb_dmi1->isChecked())
        {
            //            qDebug()<<"1 1";
            els_dmi_data.DMI_Control=1;
            els_dmi_data.setBytesFromData(qsend);
            //            els_dmi_data.freePointer();


            int i =mySocket->writeDatagram(qsend,QHostAddress(ip1),port1);




        }
        else
        {
            //                 qDebug()<<"1 0";
            els_dmi_data.DMI_Control=0;
            els_dmi_data.setBytesFromData(qsend);
            //            els_dmi_data.freePointer();

            int i =mySocket->writeDatagram(qsend,QHostAddress(ip1),port1);
            //                        writeLog("els_dmi1 send data is "+QString::number(i)+"bytes",qsend);

            //            els_dmi_data.DMI_Control=0;
            //            els_dmi_data.setBytesFromData(qsend);
            //            els_dmi_data.freePointer();
        }
        if(ui->chb_dmi2->isChecked())
        {
            //                 qDebug()<<"2 1";
            //            qDebug()<<"2";
            els_dmi_data.DMI_Control=1;
            els_dmi_data.setBytesFromData(qsend);
            //            els_dmi_data.freePointer();

            int i =mySocket->writeDatagram(qsend,QHostAddress(ip2),port2);
            //            writeLog("els_dmi2 send data is "+QString::number(i)+"bytes",qsend);

            //            els_dmi_data.DMI_Control=0;
            //            els_dmi_data.setBytesFromData(qsend);


            //            i =mySocket->writeDatagram(qsend,QHostAddress(ip1),port1);
            //            writeLog("els_dmi1 send data is "+QString::number(i)+"bytes",qsend);

        }
        else
        {
            //                 qDebug()<<"2 0";
            els_dmi_data.DMI_Control=0;
            els_dmi_data.setBytesFromData(qsend);
            //            els_dmi_data.freePointer();

            int i =mySocket->writeDatagram(qsend,QHostAddress(ip2),port2);
            //            writeLog("els_dmi2 send data is "+QString::number(i)+"bytes",qsend);

            //            els_dmi_data.DMI_Control=0;
            //            els_dmi_data.setBytesFromData(qsend);

        }

        els_dmi_data.freePointer();
    }
    QString txt;


    QString date= QDate::currentDate().toString("yyyy-MM-dd");
    QString time = QTime::currentTime().toString("hh:mm:ss");
    txt+= " "+date+" "+time;

    char *c = qsend.data();
    txt+="size is "+ QString::number(qsend.count());
    txt+="\n";
    for(int i=0;i<qsend.size();i++)
    {
        txt+=" 0x"+QString::number( (quint8)c[i],16);
    }

    ui->txt_send->append(txt);
    if(   ui->txt_send->toPlainText().length()>1000000)
        ui->txt_send->clear();


}
void MainWindow::timerEvent(QTimerEvent *e)
{
    QByteArray temp;
    timer_1s++;
    if(issendtracklayout&&isperiodly)
        ui->frame->setEnabled(true);
    else
        ui->frame->setEnabled(false);
    if(timer_1s>=10)
    {
        ui->wdg_intialtime->setDateTime(QDateTime::currentDateTime());
        timer_1s=0; //get 1 second
        if(is_auto_dmi_control)
        {
            if(ui->chb_dmi1->isChecked())
            {
                ui->chb_dmi1->setChecked(false);
            }
            else
            {
                ui->chb_dmi1->setChecked(true);
            }
        }
    }

    if(isautoinc)
    {
        int tmpstep=   ui->le_stepno->text().toInt();
        tmpstep++;
        if(tmpstep>3)
            tmpstep=1;
        ui->le_stepno->setText(QString::number( tmpstep));
    }

    if(e->timerId()==timer_100ms) //100ms只收一条，只发一条
    {
        //        qDebug()<<"timer100"<<QDateTime::currentMSecsSinceEpoch();
        if(isonecycle)
        {
            isonecycle=false;
            if(ui->radiobtn_dmi->isChecked())
            {
                sendMsg(true);
            }
            else
            {
                sendMsg(false);
            }
        }
        if(israndom)
        {
            randomData(ui->radiobtn_dmi->isChecked());

        }

        if(isperiodly)
        {
            if(isstartgeo)
            {
                int rows=ui->tblwdg_geo->rowCount();
                for(int j=0;j<rows;j++)
                {
                    QString oldbegin=ui->tblwdg_geo->item(j,2)->text();
                    QString oldend=ui->tblwdg_geo->item(j,3)->text();
                    quint16 temp=oldbegin.toUInt();
                    quint16 end=oldend.toUInt();
                    temp-=INC;
                    end-=INC; //带状宽度
                    if(temp>0&&end>0&&temp<end)
                    {

                    }
                    else
                    {
                        //                        qDebug()<<"reset";
                        temp =MAX-WIDTH;
                        end = MAX;

                    }
                    QString newbegin=QString::number(temp);
                    QString newend=QString::number(end);
                    ui->tblwdg_geo->item(j,2)->setText(newbegin);
                    ui->tblwdg_geo->item(j,3)->setText(newend);



                }
            }
            if(ui->radiobtn_dmi->isChecked())
            {
                sendMsg(true);
            }
            else
                sendMsg(false);

        }
        if(que_els_dmi->count()>0) //如果没收到消息不用刷新
        {

            while(!que_els_dmi->isEmpty())
            {
                temp=que_els_dmi->dequeue();
            }
            QString txt="";

            QString date= QDate::currentDate().toString("yyyy-MM-dd");
            QString time = QTime::currentTime().toString("hh:mm:ss");
            txt+= " "+date+" "+time;

            char *c = temp.data();
            txt+="size is "+ QString::number(temp.count());
            txt+="\n";
            for(int i=0;i<temp.size();i++)
            {
                txt+=" 0x"+QString::number( (quint8)c[i],16);
            }

            ui->txt_recv->append(txt);
            if(   ui->txt_recv->toPlainText().length()>1000000)
                ui->txt_recv->clear();


            if(!ui->radiobtn_dmi->isChecked())  //当前是ELS模式
            {

                dmi_els_data.getDataFromBytes(temp); //将字节转换为各个字段
                //                qDebug()<<"it is simulator , now dmi display_status"<<dmi_els_data.Display_Status;
                if(!dmi_els_data.Display_Status)
                {
                    //                    qDebug()<<"not play";
                    return;
                }
                setUifromData(dmi_els_data); //将接收的数据显示在界面上
                //                qDebug()<<"sim"<<dmi_els_data.ELS_Mode_Selection;
                giveValueFromDMIToELS();
                dmi_els_data.freePointer();

            }
            else
            {
                els_dmi_data.getDataFromBytes(temp); //将字节转换为各个字段
                setUifromData(els_dmi_data); //将接收的数据显示在界面上
                els_dmi_data.freePointer();

            }
        }

    }

}

void MainWindow::on_btn_onecycel_clicked()
{
    isonecycle=true;
}

void MainWindow::on_btn_periodlly_clicked()
{
    isperiodly=!isperiodly;
    if(isperiodly)
    {
        ui->btn_periodlly->setText(tr("stop"));
    }
    else
    {
        ui->btn_periodlly->setText(tr("periodly"));
    }
}

void MainWindow::on_btn_random_clicked()
{
    israndom=!israndom;
    if(israndom)
    {
        //        this->setDisabled(true);
        ui->btn_random->setText(tr("stop"));
        //        ui->btn_random->setDisabled(false);

    }
    else
    {
        ui->btn_random->setText(tr("random"));
        //        this->setDisabled(false);
    }

}

void MainWindow::on_btn_autoinc_clicked()
{
    isautoinc=!isautoinc;
    if(isautoinc)
    {
        ui->btn_autoinc->setText(tr("NoInc"));
    }
    else
    {
        ui->btn_autoinc->setText(tr("AutoIncStep"));
    }
}

void MainWindow::on_btn_clearsend_clicked()
{
    ui->txt_send->clear();
}

void MainWindow::on_btn_clearrecv_clicked()
{
    ui->txt_recv->clear();
}

void MainWindow::on_btn_confrmlocport_clicked()
{
    int port = ui->le_localport->text().toInt();
    mySocket->abort();
    mySocket = new QUdpSocket(this);
    if(!mySocket->bind(port,QUdpSocket::ShareAddress|QUdpSocket::ReuseAddressHint)) //需要读取配置文件获得port之后才能bind
        qDebug()<<"error";
    connect(mySocket,SIGNAL(readyRead()),this,SLOT(recvMsg()));

}

void MainWindow::on_chb_dmi1_clicked()
{
    //    if(ui->chb_dmi2->isChecked())
    //        ui->chb_dmi2->setChecked(false);
}

void MainWindow::on_chb_dmi2_clicked()
{
    //    if(ui->chb_dmi1->isChecked())
    //        ui->chb_dmi1->setChecked(false);
}

void MainWindow::on_btn_addgeo_clicked()
{
    int cols=ui->tblwdg_geo->colorCount();
    int rows=ui->tblwdg_geo->rowCount();
    //    qDebug()<<rows;
    ui->tblwdg_geo->insertRow(rows);
    for(int i=0;i<2;i++)
    {
        ui->tblwdg_geo->setItem(rows,i,new QTableWidgetItem(QString::number(rows)));
        ui->tblwdg_geo->setItem(rows,2,new QTableWidgetItem(QString::number(25)));
        ui->tblwdg_geo->setItem(rows,3,new QTableWidgetItem(QString::number(30)));
    }
    ui->tblwdg_geo->selectRow(rows);
}

void MainWindow::on_btn_subgeo_clicked()
{

    ui->tblwdg_geo->removeRow(ui->tblwdg_geo->currentRow());

}

void MainWindow::on_btn_addfault_clicked()
{
    int cols=ui->tblwdg_fault->colorCount();
    int rows=ui->tblwdg_fault->rowCount();
    //    qDebug()<<rows;
    ui->tblwdg_fault->insertRow(rows);
    for(int i=0;i<cols;i++)
    {
        ui->tblwdg_fault->setItem(rows,i, new QTableWidgetItem(QString::number(rows)));

    }
    ui->tblwdg_fault->selectRow(rows);
}

void MainWindow::on_btn_subfault_clicked()
{
    ui->tblwdg_fault->removeRow(ui->tblwdg_fault->currentRow());
}

void MainWindow::on_btn_startstop_clicked()
{
    if(ui->btn_startstop->text()=="start")
    {
        ui->btn_startstop->setText("stop");
        isstartgeo=true;

    }
    else
    {
        ui->btn_startstop->setText("start");
        isstartgeo=false;
    }
}

void MainWindow::on_btn_addsch_clicked()
{
    int rows=ui->tblwdg_schedule->rowCount();
    ui->tblwdg_schedule->insertRow(rows);

    ui->tblwdg_schedule->setItem(rows,0, new QTableWidgetItem(QString::number(rows)));


}

void MainWindow::on_btn_subsche_clicked()
{
    ui->tblwdg_schedule->removeRow(ui->tblwdg_schedule->currentRow());
}

void MainWindow::on_btn_addserv_clicked()
{
    int rows=ui->tblwdg_serv->rowCount();
    ui->tblwdg_serv->insertRow(rows);

    ui->tblwdg_serv->setItem(rows,0, new QTableWidgetItem(QString::number(rows)));
}

void MainWindow::on_btn_subserv_clicked()
{
    ui->tblwdg_serv->removeRow(ui->tblwdg_serv->currentRow());
}

void MainWindow::on_btn_addtrip_clicked()
{
    int rows=ui->tblwdg_trip->rowCount();
    ui->tblwdg_trip->insertRow(rows);

    ui->tblwdg_trip->setItem(rows,0, new QTableWidgetItem(QString::number(rows)));
}

void MainWindow::on_btn_subtrip_clicked()
{
    ui->tblwdg_trip->removeRow(ui->tblwdg_trip->currentRow());
}

void MainWindow::on_btn_addpath_clicked()
{
    int rows=ui->tblwdg_path->rowCount();
    ui->tblwdg_path->insertRow(rows);

    ui->tblwdg_path->setItem(rows,0, new QTableWidgetItem(QString::number(rows)));
}

void MainWindow::on_btn_subpath_clicked()
{
    ui->tblwdg_path->removeRow(ui->tblwdg_path->currentRow());
}

void MainWindow::on_btn_adddes_clicked()
{
    int rows=ui->tblwdg_des->rowCount();
    ui->tblwdg_des->insertRow(rows);

    ui->tblwdg_des->setItem(rows,0, new QTableWidgetItem(QString::number(rows)));
}

void MainWindow::on_btn_subdes_clicked()
{
    ui->tblwdg_des->removeRow(ui->tblwdg_des->currentRow());
}

void MainWindow::on_btn_smsconfirm_clicked()
{
    issmsconfirm=true;
}

void MainWindow::on_btn_sendtracklayout_clicked()
{
    issendtracklayout=!issendtracklayout;
    //    qDebug()<<"now track"<<issendtracklayout;
    QString txt=ui->btn_sendtracklayout->text();
    if(txt=="begin")
    {
        txt="stop";
    }
    else
    {
        txt="begin";
    }
    ui->btn_sendtracklayout->setText(txt);
}

void MainWindow::on_btn_auto_dmi_control_clicked()
{
    is_auto_dmi_control=!is_auto_dmi_control;
    if(ui->btn_auto_dmi_control->text()=="begin")
    {
        ui->btn_auto_dmi_control->setText("stop");
        is_auto_dmi_control=true;
    }
    else if(ui->btn_auto_dmi_control->text()=="stop")
    {
        ui->btn_auto_dmi_control->setText("begin");
        is_auto_dmi_control=false;
    }

}

void MainWindow::on_btn_addradar_clicked()
{
    int cols=ui->tblwdg_radar->colorCount();
    int rows=ui->tblwdg_radar->rowCount();
    //    qDebug()<<rows;
    ui->tblwdg_radar->insertRow(rows);
    for(int i=0;i<5;i++)
    {
        ui->tblwdg_radar->setItem(rows,i,new QTableWidgetItem(QString::number(rows)));
        ui->tblwdg_radar->setItem(rows,1,new QTableWidgetItem(QString::number(3)));
        ui->tblwdg_radar->setItem(rows,2,new QTableWidgetItem(QString::number(30)));
        ui->tblwdg_radar->setItem(rows,3,new QTableWidgetItem(QString::number(35)));
        ui->tblwdg_radar->setItem(rows,4,new QTableWidgetItem(QString::number(40)));
    }
    ui->tblwdg_radar->selectRow(rows);
}

void MainWindow::on_btn_subradar_clicked()
{
    ui->tblwdg_radar->removeRow(ui->tblwdg_radar->currentRow());
}

void MainWindow::on_btn_sigok_clicked()
{

}

void MainWindow::on_btn_lcsok_clicked()
{

}



void MainWindow::on_chksig_clicked()
{

}

void MainWindow::on_chklcs_clicked()
{

}
