/******************************
** Date: 2016/06/23
** Author: noodlebin
** Brief: when driver click the obs icon in mission area, the dialog will pop up   .cpp
** Version: 1.0
******************************/
#include "DialogObsstatus.h"
#include "ui_DialogObsstatus.h"
#include <QDebug>

DialogOBSStatus::DialogOBSStatus(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogOBSStatus)
{

    ui->setupUi(this);
    currentPath=QDir::currentPath()+"/res/";
    ui->pic_exit->installEventFilter(this);


    ui->pic_elssta->setPixmap(currentPath+"ELS_Status_OK.png");
    ui->pic_rrsta->setPixmap(currentPath+"RR_Status_OK.png");
    ui->pic_cpsta->setPixmap(currentPath+"CP_Status_OK.png");
    ui->pic_atpsta->setPixmap(currentPath+"ATP_Status_OK.png");
    ui->pic_exit->setPixmap(currentPath+"Close.png");
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::CoverWindow);

}

DialogOBSStatus::~DialogOBSStatus()
{

    delete ui;
}

bool DialogOBSStatus::eventFilter(QObject *obj, QEvent *event)
{
    if(obj==ui->pic_exit)
    {
        if(event->type()==QEvent::MouseButtonRelease)
        {
            this->reject();
            return true;
        }
        else
            return false;
    }
    else
        return DialogOBSStatus::eventFilter(obj,event);
}

void DialogOBSStatus::setPicStatus(quint8 v)
{
    if(v&0x01)
        ui->pic_elssta->setPixmap(currentPath+"ELS_Status_OK.png");
    else
        ui->pic_elssta->setPixmap(currentPath+"ELS_Status_Error.png");
    if(v&0x02)
        ui->pic_rrsta->setPixmap(currentPath+"RR_Status_OK.png");
    else
        ui->pic_rrsta->setPixmap(currentPath+"RR_Status_Error.png");
    if(v&0x04)
        ui->pic_cpsta->setPixmap(currentPath+"CP_Status_OK.png");
    else
        ui->pic_cpsta->setPixmap(currentPath+"CP_Status_Error.png");
    if(v&0x08)
        ui->pic_atpsta->setPixmap(currentPath+"ATP_Status_OK.png");
    else
        ui->pic_atpsta->setPixmap(currentPath+"ATP_Status_Error.png");
}
