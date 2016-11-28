/******************************
** Date: 2016/06/23
** Author: noodlebin
** Brief: when driver click the scheduleid text label in tab area, the dialog will pop up
** Version: 1.0
******************************/
#include "DialogSchedule.h"
#include "ui_DialogSchedule.h"
#include <QDebug>
void DialogSchedule::showEvent(QShowEvent *)
{
    ui->cmb_service->setEnabled(false);
    ui->cmb_trip->setEnabled(false);
    ui->lbl_service->setEnabled(false);
    ui->lbl_trip->setEnabled(false);
    ui->btn_service->setEnabled(false);
    ui->btn_servicecancel->setEnabled(false);
    ui->btn_trip->setEnabled(false);
    ui->btn_tripcancel->setEnabled(false);

    ui->btn_sch->setEnabled(true);
    ui->cmb_schedule->setEnabled(true);
    ui->cmb_schedule->clear();
    for(int i=0;i<m_sch_num;i++)
    {
        if(m_map_sch->contains(m_sch_id[i]))
        {
            ui->cmb_schedule->addItem(m_map_sch->value(m_sch_id[i]));
        }
        else
        {
            ui->cmb_schedule->addItem(QString::number(m_sch_id[i]));
        }
    }
    ui->cmb_schedule->installEventFilter(this);
    ui->cmb_service->installEventFilter(this);
    ui->cmb_trip->installEventFilter(this);
}

bool DialogSchedule::eventFilter(QObject *obj, QEvent *event)
{
    if(obj==ui->cmb_schedule)
    {
        if(  event->type()==QEvent::MouseButtonPress)
        {
            if(ui->cmb_schedule->isEnabled())
            {
                ui->cmb_schedule->clear();
                for(int i=0;i<m_sch_num;i++)
                {
                    ui->cmb_schedule->addItem(QString::number(m_sch_id[i]));
                }
                ui->cmb_schedule->showPopup();
            }

            return true;

        }
        else
            return false;
    }
    if(obj==ui->cmb_service)
    {
        if(  event->type()==QEvent::MouseButtonPress)
        {
            if(ui->cmb_service->isEnabled())
            {
                ui->cmb_service->clear();
                for(int i=0;i<m_service_num;i++)
                {
                    ui->cmb_service->addItem(QString::number(m_service_id[i]));
                }
                ui->cmb_service->showPopup();
            }
            return true;
        }
        else
            return false;
    }
    if(obj==ui->cmb_trip)
    {
        if(  event->type()==QEvent::MouseButtonPress)
        {
            if(ui->cmb_trip->isEnabled())
            {
                ui->cmb_trip->clear();
                for(int i=0;i<m_trip_num;i++)
                {
                    ui->cmb_trip->addItem(QString::number(m_trip_id[i]));
                }
                ui->cmb_trip->showPopup();
            }
            return true;
        }
        else
            return false;
    }
}



DialogSchedule::DialogSchedule(QMap<int, QString> *map, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSchedule)
{
    ui->setupUi(this);
    //    ui->btn_cancel->setText("cancel");
    //    ui->btn_ok->setText("ok");
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::CoverWindow);

    m_sch_id = new quint16[50];
    m_service_id=new quint16[50];
    m_trip_id=new quint16[50];


    if(map->size()>0)
        m_map_sch=map;
    else
        m_map_sch=new QMap<int,QString>;
}

DialogSchedule::~DialogSchedule()
{
    delete ui;
    delete[] m_sch_id;
    delete[] m_service_id;
    delete[] m_trip_id;
}

void DialogSchedule::setvalue(quint8 num1, quint16 *schid,
                              quint8 num2,quint16*serviceid,
                              quint8 num3,quint16*tripid)
{
    m_sch_num=num1;
    m_service_num=num2;
    m_trip_num=num3;

    for(int i=0;i<m_sch_num;i++)
    {
        m_sch_id[i]=schid[i];
    }
    for(int i=0;i<m_service_num;i++)
    {
        m_service_id[i]=serviceid[i];
    }
    for(int i=0;i<m_trip_num;i++)
    {
        m_trip_id[i]=tripid[i];
    }
}





//void DialogSchedule::on_btn_ok_clicked()
//{
//    if(ui->list_sch->count()>0)
//    {
//        if(ui->list_sch->currentRow()==-1)
//        {
//            ui->list_sch->setCurrentRow(0);
//        }
//        QString tmp=ui->list_sch->currentItem()->text();
//        int t= tmp.toUInt();
//        path=t;
//    }

//    this->accept();//index from 0
//}

void DialogSchedule::on_btn_cancel_clicked()
{
    this->reject();
}



void DialogSchedule::on_btn_sch_clicked()
{
    qint8 schedule_index=ui->cmb_schedule->currentIndex();
    if(schedule_index==-1)
        return;
    quint16 scheduleid;
    if(m_map_sch->size()>0)
        scheduleid=m_map_sch->key(ui->cmb_schedule->currentText());
    else
        scheduleid=ui->cmb_schedule->currentText().toUInt();
    emit sendScheduleId(scheduleid);
    //    qDebug()<<scheduleid;
    ui->cmb_schedule->setEnabled(false);
    ui->btn_sch->setEnabled(false);
    ui->btn_schcancel->setEnabled(false);
    ui->lbl_schedule->setEnabled(false);

    ui->lbl_service->setEnabled(true);
    ui->cmb_service->setEnabled(true);
    ui->btn_service->setEnabled(true);
    ui->btn_servicecancel->setEnabled(true);
    ui->cmb_service->clear();
    for(int i=0;i<m_service_num;i++)
    {
        ui->cmb_service->addItem(QString::number(m_service_id[i]));
    }
}

void DialogSchedule::on_btn_schcancel_clicked()
{
    emit sendScheduleId(-1);
    //    emit sendServiceId(-1);
    //    emit sendTripId(-1); /有时候用户全都选完了，然后重开对话框
}

void DialogSchedule::on_btn_service_clicked()
{
    qint8 service_index =ui->cmb_service->currentIndex();
    if(service_index==-1)
        return;

    //    qDebug()<<"service"<<ui->cmb_service->currentText()<<ui->cmb_service->currentText().toUInt();
    emit sendServiceId(ui->cmb_service->currentText().toUInt());

    ui->cmb_service->setEnabled(false);
    ui->btn_service->setEnabled(false);
    ui->btn_servicecancel->setEnabled(false);
    ui->lbl_service->setEnabled(false);

    ui->lbl_trip->setEnabled(true);
    ui->cmb_trip->setEnabled(true);
    ui->btn_trip->setEnabled(true);
    ui->btn_tripcancel->setEnabled(true);
    ui->cmb_trip->clear();
    for(int i=0;i<m_trip_num;i++)
    {
        ui->cmb_trip->addItem(QString::number(m_trip_id[i]));
    }
}

void DialogSchedule::on_btn_servicecancel_clicked()
{
    emit sendServiceId(-1);
    ui->cmb_service->setEnabled(false);
    ui->btn_service->setEnabled(false);
    ui->btn_servicecancel->setEnabled(false);
    ui->lbl_service->setEnabled(false);

    ui->lbl_schedule->setEnabled(true);
    ui->cmb_schedule->setEnabled(true);
    ui->btn_sch->setEnabled(true);
    ui->btn_schcancel->setEnabled(true);
}

void DialogSchedule::on_btn_trip_clicked()
{
    qint8 trip_index=ui->cmb_trip->currentIndex();
    if(trip_index==-1)
        return;
    emit sendTripId(ui->cmb_trip->currentText().toUInt());
    ui->cmb_trip->setEnabled(false);
    ui->btn_trip->setEnabled(false);
    ui->lbl_trip->setEnabled(false);

}

void DialogSchedule::on_btn_tripcancel_clicked()
{
    emit sendTripId(-1);
    ui->cmb_trip->setEnabled(false);
    ui->btn_trip->setEnabled(false);
    ui->btn_tripcancel->setEnabled(false);

    ui->lbl_service->setEnabled(true);
    ui->cmb_service->setEnabled(true);
    ui->btn_service->setEnabled(true);
    ui->btn_servicecancel->setEnabled(true);
}




