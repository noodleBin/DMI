/******************************
** Date: 2016/06/23
** Author: noodlebin
** Brief: when driver click the elsmode text in atp area, the dialog will pop up  .cpp
** Version: 1.0
******************************/
#include "DialogElsmodeselection.h"
#include "ui_DialogElsmodeselection.h"
#include <QTranslator>
#include <QDebug>

DialogELSModeSelection::DialogELSModeSelection(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogELSModeSelection)
{

    ui->setupUi(this);
    modevalue=1;//初始第一个选中

    ui->radiobtn_automatic->setText(tr("automatic"));
    ui->radiobtn_deadhead->setText(tr("deadhead"))       ;
    ui->radiobtn_standalone->setText(tr("standalone"));
    ui->lblelsmodename->setText(tr("lblelsmodename"));
    ui->btn_ok->setText(tr("btnok"));
    ui->btn_cancel->setText(tr("btncancel"));
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::CoverWindow);


}

DialogELSModeSelection::~DialogELSModeSelection()
{
    delete ui;
}

void DialogELSModeSelection::on_btn_ok_clicked()
{
    if(ui->radiobtn_automatic->isChecked())
    {
        modevalue=1;
        this->accept();
    }
    else if(ui->radiobtn_standalone->isChecked())
    {
        modevalue=2;
        this->accept();
    }
    else if(ui->radiobtn_deadhead->isChecked())
    {
        modevalue=3;
        this->accept();
    }

}

void DialogELSModeSelection::on_btn_cancel_clicked()
{
    this->reject();
}
