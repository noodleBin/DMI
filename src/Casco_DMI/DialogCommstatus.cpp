/******************************
** Date: 2016/06/23
** Author: noodlebin
** Brief: when driver click the Communication icon in mission area, the dialog will pop up  .cpp
** Version: 1.0
******************************/
#include "DialogCommstatus.h"
#include "ui_DialogCommstatus.h"
#include <QDebug>

DialogCommstatus::DialogCommstatus(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogCommstatus)
{
    ui->setupUi(this);
    currentPath=QDir::currentPath()+"/res/";

    ui->pic_exit->installEventFilter(this);


    ui->pic_dmselssta->setPixmap(currentPath+"Communication_ELS_DMS_Status0.png");
    ui->pic_radiostatus->setPixmap(currentPath+"Wifi_OK.png");
    ui->pic_radiocover->setPixmap(currentPath+"Comm_Cover_Status0.png");
    ui->pic_gpssta->setPixmap(currentPath+"GPS_OK.png");
    ui->pic_exit->setPixmap(currentPath+"Close.png");
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::CoverWindow);

}

DialogCommstatus::~DialogCommstatus()
{
//    qDebug()<<"delay commdial";
    delete ui;
}


bool DialogCommstatus::eventFilter(QObject *obj, QEvent *event)
{
    if(obj==ui->pic_exit)
    {
        if(event->type()==QEvent::MouseButtonRelease)
        {
            this->accept();
            return true;
        }
        else
            return false;
    }
    else
        return DialogCommstatus::eventFilter(obj,event);
}

void DialogCommstatus::setPicCommDMSELS(quint8 v)
{
    if(v==1)
        ui->pic_dmselssta->setPixmap(currentPath+"Communication_ELS_DMS_Status1.png");
    else
        ui->pic_dmselssta->setPixmap(currentPath+"Communication_ELS_DMS_Status0.png");
}

void DialogCommstatus::setPicRadioDMSELS(quint8 v)
{
    if(v==1)
        ui->pic_radiostatus->setPixmap(currentPath+"Wifi_OK.png");
    else
        ui->pic_radiostatus->setPixmap(currentPath+"Wifi_Error.png");
}

void DialogCommstatus::setPicRadioCoverDMSELS(quint8 v)
{
    if(v==1)
        ui->pic_radiocover->setPixmap(currentPath+"Comm_Cover_Status1.png");
    else
        ui->pic_radiocover->setPixmap(currentPath+"Comm_Cover_Status0.png");

}
