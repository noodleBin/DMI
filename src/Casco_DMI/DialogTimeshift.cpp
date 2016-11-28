/******************************
** Date: 2016/06/23
** Author: noodlebin
** Brief: when driver click the delay/advance text label in top area, the dialog will pop up  .cpp
** Version: 1.0
******************************/
#include "DialogTimeshift.h"
#include "ui_DialogTimeshift.h"

Dialogtimeshift::Dialogtimeshift(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialogtimeshift)
{
    ui->setupUi(this);
    ui->lbl_delaynametitle->setText(tr("delaynametitle"));
    ui->lbl_desnametitle->setText(tr("desnametitle"));
    ui->lbl_servicenametitle->setText(tr("servicenametitle"));
    ui->btn_cancel->setText(tr("cancel"));
    ui->btn_timeshift->setText(tr("timeshift"));
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::CoverWindow);
}

Dialogtimeshift::~Dialogtimeshift()
{
    delete ui;
}

void Dialogtimeshift::setvalue(quint16 service, QString des, qint16 delay)
{
    ui->lbl_service->setText(QString::number(service));
    ui->lbl_des->setText(des);

    if(delay<0)
    {
        delay=-delay; //绝对值
        ui->lbl_delayname->setText(tr("提前"));

    }
    else
    {
        ui->lbl_delayname->setText(tr("延误"));
    }
    ui->lbl_delay->setText(QString::number(delay));
}

void Dialogtimeshift::on_btn_timeshift_clicked()
{
    this->accept();
}

void Dialogtimeshift::on_btn_cancel_clicked()
{
    this->reject();
}
