#include "Dialogwarningbox.h"
#include "ui_Dialogwarningbox.h"

DialogWarningbox::DialogWarningbox(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogWarningbox)
{
    ui->setupUi(this);

    currentPath=QDir::currentPath()+"/res/";

    ui->lbl_logo->setPixmap(currentPath+"Casco_Logo_300.png");
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::CoverWindow);
}

DialogWarningbox::~DialogWarningbox()
{
    delete ui;
}

void DialogWarningbox::setValue(QString txt)
{
    ui->label->setText(txt);
}

void DialogWarningbox::on_btn_ok_clicked()
{
    this->accept();
}
