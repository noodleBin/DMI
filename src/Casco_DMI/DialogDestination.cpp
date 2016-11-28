/******************************
** Date: 2016/06/23
** Author: noodlebin
** Brief: when driver click the destination icon in tab area, the dialog will pop up  .cpp
** Version: 1.0
******************************/
#include "DialogDestination.h"
#include "ui_DialogDestination.h"
#include <QDebug>

DialogDestination::DialogDestination(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogDestination)
{
    ui->setupUi(this);

    //    ui->btn_OK->setText(tr("ok"));
    //    ui->lbl_dialogdesname->setText(tr("dialogdesname"));

    m_des_id=new quint16[50];
    m_path_id=new quint16[50];
    isexec=false;
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::CoverWindow);
    m_servicemode=0;
    //    ui->combox_des->setCurrentIndex(0);
    //    ui->combox_des->setDisabled(true);
}
void DialogDestination::showEvent(QShowEvent *e)
{
    Q_UNUSED(e);
    quint8 index=(ui->cmb_desorpath->currentIndex());
    // qDebug()<<"index"<<index;
    on_cmb_desorpath_currentIndexChanged(index);
}
DialogDestination::~DialogDestination()
{
    delete ui;
    delete[] m_des_id;
    delete[] m_path_id;
}

void DialogDestination::on_btn_OK_clicked()
{
    if(ui->cmb_desorpath->currentIndex()==0)
    {
        if(ui->combox_des->count()>0)
        {
            if(m_des_map->size()>0)
            {
                chosen_value=m_des_map->key(ui->combox_des->currentText());
            }
            else
                chosen_value=ui->combox_des->currentText().toUInt();
//            qDebug()<<chosen_value;
        }
        else
        {
            chosen_value=-1;
        }
        m_desorpath=1;
    }
    else if(ui->cmb_desorpath->currentIndex()==1)
    {
        if(ui->combox_des->count()>0)
        {
            chosen_value=ui->combox_des->currentText().toUInt();
        }
        else
        {
            chosen_value=-1;
        }
        m_desorpath=2;
    }
    //    if(ui->combox_service->count()>0)
    //    {
    //        QString tmp= ui->combox_service->currentText();
    //        chosenservice=tmp.toInt();
    //    }
    //    else
    //    {
    //        chosenservice=-1;
    //    }

    //    if(ui->combox_trip->count()>0)
    //    {
    //        QString tmp= ui->combox_trip->currentText();
    //        chosentrip=tmp.toInt();
    //    }
    //    else
    //    {
    //        chosentrip=-1;
    //    }

    //    if(ui->combox_path->count()>0)
    //    {
    //        QString tmp= ui->combox_path->currentText();
    //        chosenpath=tmp.toInt();
    //    }
    //    else
    //    {
    //        chosenpath=-1;
    //    }

    this->accept();//index from 0
}

void DialogDestination::setDestinationValue(quint8 number, quint16 *desid)
{
    m_des_num=number;
    for(int i=0;i<m_des_num;i++)
    {
        m_des_id[i]=desid[i];
    }


}

//void DialogDestination::setServiceValue(quint8 number, quint16 *serviceid)
//{
//    m_number=number;
//    ui->combox_service->clear();//clear previous display
//    //    qDebug()<<"clean already"<<m_number;
//    for(int i=0;i<m_number;i++)
//    {
//        m_id[i]=serviceid[i];
//        ui->combox_service->addItem(QString::number(m_id[i]));
//    }
//    if(m_servicemode==2||m_servicemode==3)
//    {
//        ui->combox_service->setEnabled(false);
//    }
//    else
//    {
//        ui->combox_service->setEnabled(true);
//    }
//}

//void DialogDestination::setTripValue(quint8 number, quint16 *tripid)
//{
//    m_number=number;
//    ui->combox_trip->clear();//clear previous display
//    //    qDebug()<<"clean already"<<m_number;
//    for(int i=0;i<m_number;i++)
//    {
//        m_id[i]=tripid[i];
//        ui->combox_trip->addItem(QString::number(m_id[i]));
//    }
//    if(m_servicemode==2||m_servicemode==3)
//    {
//        ui->combox_trip->setEnabled(false);
//    }
//    else
//    {
//        ui->combox_trip->setEnabled(true);
//    }
//}

void DialogDestination::setPathValue(quint8 number, quint16 *pathid)
{
    m_path_num=number;
    for(int i=0;i<m_path_num;i++)
    {
        m_path_id[i]=pathid[i];
    }

}


void DialogDestination::intialmap(QMap<int, QString> *map)
{
    m_des_map=map;
}

void DialogDestination::on_cmb_desorpath_currentIndexChanged(int index)
{
    ui->combox_des->clear();
    if(index==0)
    {
        for(int i=0;i<m_des_num;i++)
        {
            quint8 key=m_des_id[i];
            if(m_des_map->contains(key))
                ui->combox_des->addItem(m_des_map->value(key));
            else
                ui->combox_des->addItem(QString::number(m_des_id[i]));
        }
    }
    else if(index==1)
    {
        for(int i=0;i<m_path_num;i++)
        {
            ui->combox_des->addItem(QString::number(m_path_id[i]));
        }
    }
}

void DialogDestination::on_btn_cancel_clicked()
{
    this->reject();
}
