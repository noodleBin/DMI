/******************************
** Date: 2016/06/23
** Author: noodlebin
** Brief: when driver click the datetime in top area, the dialog will pop up
** Version: 1.0
******************************/
#include "DialogTimeupdate.h"
#include "ui_DialogTimeupdate.h"

DialogTimeUpdate::DialogTimeUpdate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogTimeUpdate)
{
    ui->setupUi(this);
    //    QDate date=QDateTime::currentDateTime().date();
    QDate date=ui->calendarWidget->selectedDate();
    ui->dateEdit->setDate(date);
    QTime time= QTime::currentTime();
    ui->timeEdit->setTime(time);
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::CoverWindow);
}

DialogTimeUpdate::~DialogTimeUpdate()
{
    delete ui;
}

void DialogTimeUpdate::on_btn_ok_clicked()
{
    this->accept();
}

void DialogTimeUpdate::on_calendarWidget_selectionChanged()
{
    QDate date=ui->calendarWidget->selectedDate();
    ui->dateEdit->setDate(date);
}

void DialogTimeUpdate::on_timeEdit_timeChanged(const QTime &time)
{
    //  int h=  time.hour();
    //  int m=time.minute();
    //  int s=time.second();
    QString temp=time.toString("hh:mm:ss");
    //  QString temp= QString::number(h)+":"+QString::number(m)+":"+QString::number(s);
    ui->lbl_time->setText(temp);
}
