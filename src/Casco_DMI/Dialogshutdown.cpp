#include "Dialogshutdown.h"
#include "ui_Dialogshutdown.h"

DialogShutdown::DialogShutdown(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogShutdown)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::FramelessWindowHint|Qt::CoverWindow);
    currentPath=QDir::currentPath()+"/res/";
    movieshutdown=new QMovie(currentPath+"ELS_RR_CP_Shutdown1.gif");
}

DialogShutdown::~DialogShutdown()
{
    delete ui;
}

void DialogShutdown::setValue(quint8 value)
{

    switch(value)
    {
    case 2:
        ui->pic_shutdown->setPixmap(currentPath+"ELS_RR_CP_Shutdown2.png");
        ui->lbl_shutdowntxt->setText("上传完毕，可以关机");
        break;
    case 1:
        ui->pic_shutdown->setMovie(movieshutdown);
        movieshutdown->start();
        ui->lbl_shutdowntxt->setText("正在上传数据");
        break;
    }

}

