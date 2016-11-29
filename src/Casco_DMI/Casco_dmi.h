/******************************
** Date: 2016/06/23
** Author: noodlebin
** Brief: Main process logic .h
** Version: 1.0
******************************/
#ifndef CASCO_DMI_H
#define CASCO_DMI_H

#include "../DMIDataStruct/Public_Variable.h"
#include <QObject>
#include <QWidget>
#include <QFile>
#include <QUiLoader>
#include <QWidget>
#include <QLabel>
#include <QTextEdit>
#include <QEvent>
#include <QDebug>
#include <QDesktopWidget>
#include <QUdpSocket>
#include <QByteArray>
#include <QQueue>
#include <QDateTime>
#include <QMap>
#include <QDomDocument>

#include <QMovie>
#include <QProgressBar>
#include <QFrame>
#include <QTableWidget>
#include <QListWidget>
#include <QSlider>
#include <QMediaPlayer>
#include <QKeyEvent>
#include <QEvent>
#include <QStack>
#include <QTranslator>

#include "../DMIDataStruct/els_dmi_protocol.h"
#include "../DMIDataStruct/dmi_els_protocol.h"


#include "GeoEvents.h"
#include "Dashboard.h"

#include "DialogVersion.h"
#include "DialogLogin.h"
#include "DialogTimeshift.h"
#include "DialogTimeupdate.h"

#include "DialogObsstatus.h"
#include "DialogCommstatus.h"

#include "DialogDestination.h"
#include "DialogElsmodeselection.h"
#include "DialogSchedule.h"
#include "DialogSmstodriver.h"

#include "TTSWorkerThread.h"
#include "DMILog.h"
#include "DMISMS.h"
#include "Dialogwarningbox.h"

#ifdef Baseline_2_0
#include "Limitspeed.h"
#include "Dialogshutdown.h"
#endif

#include "TLEevents.h"
#include "tlepublicvariables.h"
#include "../DMIDataStruct/dms_dmi_protocol.h"

#include "sys/time.h"


/*************************************
 * *Alarm xml
 * *noodleBin
 * *2016/11/28
 * **********************************/

#define NOTALLOW 1
#define OVERSPEED 2
#define STARTUP 100
#define CLOSE 101
#define NEXTPSR 5
#define ELSERROR 6
#define DMIELSDISCON 7
#define DMIELSResume 8
#define SMS 9
#define ClEANDISK 11
#define CHECKTIME 12
#define OVERSHOOT 13
#define HIGHRADAR 14
#define NORMALRADAR 15
#define NEARDOWN 18
#define TURNBACK 19
#define SKIP 20
#define HOLD 21
#define LOSELOC 22
#define DEP 23
#define ELSDMSDISCON 24
#define RADARERROR 25
#define GPSERROR 26
#define BCMERROR 27
#define WIFILOSE 28
#define ELSMODECHANGE 29
#define ADVANCE 30
#define DELAY 31
#define CURRENTPSRMINUS 32


class Casco_DMI:public QObject
{
    Q_OBJECT
public:
    explicit Casco_DMI();
    ~Casco_DMI();
    bool isquit;
private :
    struct Description{
        QString English_Description;
        QString Chinese_Description;
    } ;

    struct DMS_Signal_Info{
        quint8 signalid;
        quint8 scene;
        quint8 type;
        quint8 location;
        quint8 restricid;
        quint8 restricloc;
    };

    struct DMI_CBI_Info{
        quint8 signalid;
        quint8 permissstatus;
        quint8 leftstatus;
    };
    struct Alarm_Record{
        quint8 id;
        QString str;
        quint8 priority;
        quint8 playtick;
        quint8 current_playtick;
        bool couldplay;
    };

    struct Signal_Info{
        quint8 id;
        quint8 image;
        quint8 x;
        quint8 y;
        quint8 bit;
        quint8 rotation;
        quint8 restricSignalCount;
        Signal_Info* restricSignals;
    };

    /**********tle events***********/
    /**********begin***********/

    QMap<quint8,QString> *map_sigid_name;
    QMap<quint8,QString> *map_olcid_name;
    QMap<QString,SignalBit> *map_Signal;
    QMap<QString,SignalBit> *map_OLC;
    QMap<quint16,QList<Shape>* > *map_Template;
    QMap<quint16,View> *map_ViewID;
    QMap<QString,Entry> *map_sigentry;
    QMap<QString,QMap<QString,QList<Shape>*>*>* map_Route;
    QMap<quint16,QList<TextInfo>*> *map_View_Texts;
    /**********end***********/

    QMediaPlayer *player;
    void initMainWindow(QString type);
    void initialControl();
    void initialNormalControl();
    void initialDisconnectControl();
    void initDialog();
    int initSocket();
    void initialVariable();
    void initDefaultValue();
    int initialMapFromXml();
    int initStation(QMap<int, QString> *map, QString);
    int initSchedule(QMap<int,QString> *map,QString);
    int initDriverPassword(QString);
    int initNet(QString);
    int initSignal(QString path);
    void parseElement(QDomNode node, QString nodename,
                                 QMap<quint8,QString>* mapid,QMap<QString,SignalBit> * map);
    void setSignalInfo(QDomElement e, Signal_Info *value);
    int initFault(QString);

    int initScreenmode(QString);
    int initOther(QString);
    int initAlarm(QString);
    int initTranslation(QString);
    int initCBIBitmap(QString path);
    void translateAll();
    int  initialLogSMS();

    void setRecvDataFromSocket(QByteArray& bytes);//因为消息是变长的，因此无法用指针强转
    void setRecvDMSDataFromSocket(QByteArray &bytes);
    void refreshUI();
    void refreshRadarPic();
    void refreshAlarmQue(quint8 index,QString filter,bool issms=true);
    void refreshAlarmQue(quint8 index, QString filter, QString sms_arg1,bool issms=true);
    void refreshAlarmQue(quint8 index, QString filter, QString sms_arg1, QString alarm_arg1,bool issms=true);
    void refreshAlarmText(quint8 index, QString filter, QString );
    void refreshSMSText(quint8 index, QString filter);
    void refreshAlarmMap();
    void putAlarmInQue(Alarm_Record info);
    void getAlarmOutQue();
    void initWorkTTS();

    void popFaultBox(QString content);
    int  setLogSMSVolume();
    void popExitBox(QString txt);
    void refreshTop();
    void refreshATP();
    void refreshMission();
    void refreshRRCP();
    void refreshOperation();
    void refreshTabMission();
    void refreshGeoEvents();
    void refreshMaintence();
    void refreshTLE();
    void refreshSMS();
    void flashUI();
    void sendMsgToELS();
    void sendDataFromStruct(QByteArray& qsend);
    void smsPromte(QString);
    void alarmPromte(QString);
    void writeSMSToFile();
    void writeAlarmToFile();
    void writeAllSMStoFile();
    void ToggleMute();
    void refreshMute();
    void checkTimeWithELS(quint64 time);

    void setScheduleId(qint16 scheduleid);
    void setServiceId(qint16 serviceid);
    void setTripId(qint16 tripid);

    void processScheduleServiceTripID();

    void processTabMaintance(int i);


signals:
    void ttsConvertNow(QString ,char*);
    void changeVolume(int volume);

protected:
    bool eventFilter(QObject *, QEvent *);
    void timerEvent(QTimerEvent* );


private slots:
    void recvMsg();
    void playEnd(QMediaPlayer::MediaStatus status);
    void playMediaNow();
    //    void on_volumeslider_sliderMoved(int position);
    void recvMySMS(QString promotetext);
private:

    QString logcontent;
    //time
    quint64 timeConvertDisplay(quint64 ntptime);

    quint64 timediff;
    quint64 currentSecondsFromELS ;//recv ELS Time

    QString buildtime;
    QString builddate;

    QString warning_msg;
    quint8 warning_index;
    Alarm_Record warning_record;
    QTranslator translator;
    //top area
    QLabel *lblNameDriver,*lblCascoLogo,*lblNameDriverId,*lblDriverId,*lblServiceId,*lblNextstaId,
    *lblNextstaId2,*lblArrTime,*lblArrTime2,
    *lblNameDelay,*lblDelayunit,*lblDelay,*lblDateTime;

    //atp area
    QLabel *lblCurrentSpeed,*lblAuthoritySpeed,*lblAtpProtection,*lblAtpInhibited,*lblAtpWarning,
    *lblNameServiceMode,*lblServiceMode;
    QWidget* widDashboard;
    //mission area
    QLabel *lblObsStatus,*lblELSDMSStatus,*lblWifi,
    *lblBCM,*lblRadar,*lblGPS,*lblLocStatus,*lblPassengerType,*lblRunningType,*lblSystemOK,
    *lblShutdownStatus,*lblActiveEnd,*lblEb,*lblSb,*lblTurnback,*lblSkip,*lblHold,
    *lblRR,*lblRRDis,*lblSig,*lblSigDis,*lblNextPsrDis,*lblNextPsrName;



    //RRCP area
    QProgressBar *RRCPbar;
    QLabel *lblBarName,*lblBarTotalValue,*lblBarRemainValue,*lblCPTotal,
    *lblCPUnit,*lblCPRemain,*lblCPRemainunit;

    //Operate area
    QLabel *btnleft,*btnstra,*btnright,*btncp,*btninput;
    QFrame *frameRR;


    //tab mission
    QLabel *lblNamesch,*lblNamedes,*lblSchId,*lblDesId,*lblDownstreamDis,*lblDownstreamTime,*lblUpstreamDis,*lblUpstreamTime,
    *lblCurStaId,*lblDepTime,*btnMute,   *lblNameCurSta,*lblNameDepTime;
    QSlider *btnSlider;
    //tab geo
    QWidget *widGeo,*widTLE,*widDMS,*widcurrentpsr,*widnextpsr;
    MyGeoEvents* mygeoevents;
    TLEEvents* mytleevents;

#ifdef Baseline_2_0
    LimitSpeed* currentpsr;
    LimitSpeed* nextpsr;
    bool  needinfri,isinfri,mute_radar,
    needcurpsrflash,iscurpsrflash,
    neednextpsrflash,isnextpsrflash;
    QLabel *btnRadarSetting ;
    QTabWidget *tabmaintance,*tabwork;
    quint16 oritaby,oritabh,longy,longh,oritabworky,oritabworkh,shorty,shorth;
    bool isdidi;
#endif
    //tab maintence
    //    QTableWidget* tblwidgetMaintance;
    QTextEdit* listAlarm;
    //sms
    QTextEdit *listSMS;
    //        QListWidget *listSMS;
    quint16 smsCount;
    //dashboard
    MyDashboard* mydashboard;

    //Dialog
    DialogVersion* dialversion;
    DialogLogin* diallogin;
    Dialogtimeshift *dialtimeshift;
    DialogTimeUpdate *dialtimeupdate;
    DialogWarningbox *msbox;
    DialogOBSStatus *dialobs;
    DialogCommstatus *dialcommstatus;

#ifdef Baseline_2_0
    DialogShutdown *dialshutdown;
#endif
    bool isdialobspop,isdialcommstatuspop;

    DialogDestination *dialdes;
    DialogELSModeSelection *dialelsmode;
    DialogSchedule *dialschedule;
    DialogSMSToDriver *dialsms;

    //net
    QUdpSocket  *mySocket,*mySocket2;
    int port,remoteport,port2,remoteport2;
    QString remoteip,remoteip2;

    //DMS Signal
    QMap<quint8,DMS_Signal_Info> *map_CBI_Signal,*map_OLC_Signal;
    QMap<quint8,DMI_CBI_Info> *map_DMI_CBI_Bitmap;

    quint8 screenmode;
    quint8 m_diffflash;
    quint8 m_discontime;
    QString m_appversion;
    QString m_dataversion;
    quint8 m_smsdisplaycount,m_maintancedisplaycount;
    quint8 m_globalsmsdisplaycount;
    quint16 listsms_height;
    QString m_lastsms;
    quint64 m_promotesizeMB;
    quint64 m_clearsizeMB;
    quint64 m_writecount;

    quint8 m_checktime;
    quint8 m_sendTime;
    quint8 m_activeEnd;
    quint16 m_todown;
    quint16 m_difftime;
    quint16 m_advance;
    quint16 m_delay;
    quint8 m_cp_sendtime,m_elsmode_sendtime,m_timeshift_sendtime,
    m_driverid_sendtime,
    m_scheduleid_sendtime,
    m_serviceid_sendtime,
    m_tripid_sendtime,
    m_pathid_sendtime,
    m_desid_sendtime;

    bool is_cp_send,is_elsmode_send,is_driverid_send,is_timeshift_send,
    is_scheduleid_send,is_serviceid_send,is_tripid_send,
    is_pathid_send,is_desid_send;

    bool m_Debug;

    QMap<quint8,Alarm_Record>* m_Alarm_Record_map;
    QMap<quint8,Signal_Info>* m_Signal_map;


    quint8 displayno; //4种显示界面,1代表默认界面
    quint8 languageno;//语言序号，1代表中文，2代表English


    QString operateType; //if driver operate, then will log
    bool isDebug,stepOneMsg;

    quint8 timer1s;
    int timer100ms;
    int timerchecktime;
    int one_minute_increase;
    quint8 timerdisconnect;
    QString exePath;
    QString resPath;
    quint8 last_turnback,last_skip,last_hold,last_curpsr;


    QQueue<QByteArray> *que_els_dmi,*que_dms_dmi;
    QByteArray last_els_dmi_data,last_dms_dmi_data;
    QQueue<QByteArray>* que_dmi_els;
    QQueue<Alarm_Record>* m_alarm_que;
    Alarm_Record m_current_alarm;
    char* m_alarm_filename;
    QQueue<QString> * list_sms;
    QQueue<QString> * list_sms_display;
    QQueue<QString> * list_alarm_display;
    QQueue<QString> * list_alarm;

    int   timerflash;
    bool needspeedflash,needatpwarning,
    needleftflash,needstraflash,needrightflash,
    isatpwarningflash,isspeedflash,isleftflash,isrightflash,isstraflash;



    bool isLogin,isDiscon,time_checked;

    QMap<int,QString>* stationIdMap;
    QMap<int,QString>* scheduleIdMap;
    QMap<int,QString>* SSAIdMap;

    QMap<int,Description>* DMI_Description;
    QMap<quint16,quint16>* driver_Password;

    ELS_DMI_Protocol* els_dmi_data;
    DMI_ELS_Protocol* dmi_els_data;

    DMS_DMI_Protocol* dms_dmi_data;

    QMovie *movieshutdown;

    quint16 xpos,ypos;//the posion
    QWidget *wid;  //mainwindow

    //tts
    QThread* workerthread;
    TTSWorker* myttsworker;
    bool ttsthreadisstart;

    QFont font;
    DMI_Log *log;
    DMISMS *sms;
    quint64 smsindex; //every write sms to file from the index
    //    quint64 smsaddition;//every write addition;




    //DMS - DMI
    quint8 timeforhidepnl;

    quint8 backgroud,type,position,status,restricpos,restricstaus;
    DMS_Signal_Info sig;
};

#endif // CASCO_DMI_H
