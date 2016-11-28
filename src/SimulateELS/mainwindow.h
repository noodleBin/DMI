#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "../DMIDataStruct/Public_Variable.h"
#include <QMainWindow>
#include <QUdpSocket>
#include <QTextStream>
#include <QDateTime>
#include <QFile>
#include <QQueue>
#include <QKeyEvent>
#include "../DMIDataStruct/dmi_els_protocol.h"
#include "../DMIDataStruct/els_dmi_protocol.h"
#include "../DMIDataStruct/dms_dmi_protocol.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT



public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void timerEvent(QTimerEvent* );
        void keyPressEvent(QKeyEvent *key);
private slots:

    void  recvMsg();
    void on_btn_onecycel_clicked();

    void on_btn_periodlly_clicked();

    void on_btn_random_clicked();

    void on_btn_autoinc_clicked();

    void on_btn_clearsend_clicked();

    void on_btn_clearrecv_clicked();

    void on_btn_confrmlocport_clicked();

    void on_chb_dmi1_clicked();

    void on_chb_dmi2_clicked();

    void on_btn_addgeo_clicked();

    void on_btn_subgeo_clicked();

    void on_btn_addfault_clicked();

    void on_btn_subfault_clicked();

    void on_btn_startstop_clicked();

    void on_btn_addsch_clicked();

    void on_btn_subsche_clicked();

    void on_btn_addserv_clicked();

    void on_btn_subserv_clicked();

    void on_btn_addtrip_clicked();

    void on_btn_subtrip_clicked();

    void on_btn_addpath_clicked();

    void on_btn_subpath_clicked();

    void on_btn_adddes_clicked();

    void on_btn_subdes_clicked();

    void on_btn_smsconfirm_clicked();

    void on_btn_sendtracklayout_clicked();

    void on_btn_auto_dmi_control_clicked();

    void on_btn_addradar_clicked();

    void on_btn_subradar_clicked();

    void on_btn_sigok_clicked();

    void on_btn_lcsok_clicked();



    void on_chksig_clicked();

    void on_chklcs_clicked();

private:
    Ui::MainWindow *ui;

    QUdpSocket *mySocket,*mySocket2; //socket只是用来接收

    QQueue<QByteArray>* que_els_dmi;
    bool isstartgeo;

    bool issmsconfirm;
    int initSocket();
    void setUifromData(DMI_ELS_Protocol& d);
    void setUifromData(ELS_DMI_Protocol& d);
    void getDatafromUi(DMI_ELS_Protocol& d);
    void getDatafromUi(ELS_DMI_Protocol& d);
    void clearUiDMI();
    void clearUiELS();
    void sendMsg(bool isdmi);
    int openFile();
    void writeLog(QString s,QByteArray bytearray);
    void randomData(bool isDMI);
    void  giveValueFromDMIToELS();

    QFile qFile;
    QTextStream qts;
    bool isonecycle;
    bool isperiodly;
    bool israndom;
    bool isautoinc;
    bool issendtracklayout;
    bool is_auto_dmi_control;

    int timer_100ms;
    int timer_1s;
    
    quint64 tmpsub;

    DMI_ELS_Protocol dmi_els_data;
    ELS_DMI_Protocol els_dmi_data;

    DMS_DMI_Protocol dms_dmi_data;
};

#endif // MAINWINDOW_H
