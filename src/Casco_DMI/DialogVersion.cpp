/******************************
** Date: 2016/06/23
** Author: noodlebin
** Brief: when driver click the casco logo in top area, the dialog will pop up
** Version: 1.0
******************************/
#include "DialogVersion.h"
#include "ui_DialogVersion.h"
#include <QDebug>

DialogVersion::DialogVersion(QMediaPlayer *player,QString version, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogVersion)
{
    //    qDebug()<<parent;
    //    this->setParent(parent);
    m_player=player;
    currentPath=QDir::currentPath()+"/res/";
    ui->setupUi(this);
    ui->lblappversionname->setText(tr("appversionname"));
    ui->lbldataversionname->setText(tr("dataversionname"));
    ui->lbl_logo->setPixmap(currentPath+"Casco_Logo_300.png");




    ui->lbl_sub_vol->installEventFilter(this);
    ui->lbl_add_vol->installEventFilter(this);
    ui->lbl_mute->installEventFilter(this);

    refreshSound();
    ui->lbl_sub_vol->setPixmap(currentPath+"sub_volume.png");
    ui->lbl_add_vol->setPixmap(currentPath+"add_volume.png");

    this->setWindowFlags(Qt::FramelessWindowHint|Qt::CoverWindow);

    ui->lbl_date->setText(version);

    connect(ui->volumeslider,SIGNAL(sliderMoved(int)),this,SLOT(on_volumeslider_sliderMoved(int)));

}

DialogVersion::~DialogVersion()
{
    //    qDebug()<<"delya";
    delete ui;
}
void DialogVersion::on_volumeslider_sliderMoved(int position)
{
    m_player->setVolume(position);
    //    qDebug()<<position;
}

void DialogVersion::setValue(QString appversion,QString dataversion)
{
    ui->lblappversion->setText(appversion);
    ui->lbldataversion->setText(dataversion);
}

void DialogVersion::on_btn_ok_clicked()
{
    this->accept();
}

void DialogVersion::refreshSound()
{
    if(m_player->isMuted())
    {
        ui->lbl_mute->setPixmap(currentPath+"Mute.png");
        ui->volumeslider->setEnabled(false);
        ui->lbl_add_vol->setEnabled(false);
        ui->lbl_sub_vol->setEnabled(false);
    }
    else
    {
        ui->lbl_mute->setPixmap(currentPath+"Sound.png");
        ui->volumeslider->setEnabled(true);
        ui->lbl_add_vol->setEnabled(true);
        ui->lbl_sub_vol->setEnabled(true);
    }
    //    qDebug()<<"after refresh mute in dialog"<<m_player->isMuted();
}

void DialogVersion::toggleSound()
{
    if(m_player->isMuted())
    {
        m_player->setMuted(false);
        ui->lbl_mute->setPixmap(currentPath+"Sound.png");
        ui->volumeslider->setEnabled(true);
        ui->lbl_add_vol->setEnabled(true);
        ui->lbl_sub_vol->setEnabled(true);
    }
    else
    {
        m_player->setMuted(true);
        ui->lbl_mute->setPixmap(currentPath+"Mute.png");
        ui->volumeslider->setEnabled(false);
        ui->lbl_add_vol->setEnabled(false);
        ui->lbl_sub_vol->setEnabled(false);
    }
    emit signalRefreshMute();
    //    qDebug()<<"after toggle mute in dialog"<<m_player->isMuted();
}

bool DialogVersion::eventFilter(QObject *obj, QEvent *event)
{
    if(obj==ui->lbl_sub_vol)
    {
        if(event->type()==QEvent::MouseButtonRelease)
        {
            if(m_player->isMuted())
                return true;
            int position=ui->volumeslider->sliderPosition();
            int newposition = position-10;
            //    qDebug()<<position<<newposition;
            ui->volumeslider->setValue(newposition);
            ui->volumeslider->sliderMoved(newposition);
            return true;
        }
        else
            return false;
    }
    else if(obj==ui->lbl_add_vol)
    {
        if(event->type()==QEvent::MouseButtonRelease)
        {
            if(m_player->isMuted())
                return true;
            int position=ui->volumeslider->sliderPosition();
            int newposition = 10+position;
            //    qDebug()<<position<<newposition;
            ui->volumeslider->setValue(newposition);
            ui->volumeslider->sliderMoved(newposition);
            return true;
        }
        else
            return false;
    }
    else if(obj==ui->lbl_mute)
    {
        if(event->type()==QEvent::MouseButtonRelease)
        {
            toggleSound();
            return true;
        }
        else
            return false;
    }
    else
        return QDialog::eventFilter(obj,event);
}

void DialogVersion::showEvent(QShowEvent *)
{
    refreshSound();
}
