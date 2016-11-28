/******************************
** Date: 2016/06/23
** Author: noodlebin
** Brief: when driver click the input button in bottom area, the dialog will pop up
** Version: 1.0
******************************/
#include "DialogSmstodriver.h"
#include "ui_DialogSmstodriver.h"


DialogSMSToDriver::DialogSMSToDriver(DMI_Log*log,DMISMS* sms, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSMSToDriver)
{
    ui->setupUi(this);

    ui->btn_return->setText(tr("cancel"));
    que_sms = new QQueue<QString>;
    qpos=new QStack<qint64>();


    ui->combox_smssource->addItem("运营信息");
    ui->combox_smssource->addItem("维护信息");
    m_log=log;
    m_sms=sms;
    this->installEventFilter(this);
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::CoverWindow);


}

DialogSMSToDriver::~DialogSMSToDriver()
{
    delete ui;
}

void DialogSMSToDriver::getSelectFile(QString type)
{
    //    qDebug()<<"type"<<type.ra;
    QString title=ui->combox_sms->currentText();
    QString filename;
    if(type=="运营信息")
    {
        filename =QDir::currentPath()+"/SMS/"+title;
    }
    else
    {
        filename =QDir::currentPath()+"/Log/"+title;
    }
    if(smsFile.isOpen())
    {
        smsFile.close();
    }
    smsFile.setFileName(filename);


    if(!smsFile.isOpen())
    {
        if(!smsFile.open(QIODevice::ReadOnly|QIODevice::Text))
        {

            qDebug()<<"open error";

        }
        qts.setDevice(&smsFile);
        qpos->clear();
        qpos->push(0); //push the original to stack
    }
}

void DialogSMSToDriver::showEvent(QShowEvent *e)
{
    Q_UNUSED(e);
    quint8 index=(ui->combox_sms->currentIndex());
    on_combox_sms_currentIndexChanged(index);
}

bool DialogSMSToDriver::eventFilter(QObject *obj, QEvent *event)
{
    if(event->type()==QEvent::KeyRelease)
    {
        QKeyEvent* key =(QKeyEvent*)(event);
        if(key->key()==Qt::Key_0)
        {
            on_btn_return_clicked();
            return true;
        }
        else
            return false;

    }
    else
        return QDialog::eventFilter(obj,event);
}

void DialogSMSToDriver::getSMSContent()
{

    QString s;
    int row=0;
    while(!qts.atEnd())
    {

        s=qts.readLine();
        row++;
        ui->textEdit->insertPlainText(s+"\n");

        if(row>=15)
        {
            row=0;
            qint64 nn=qts.pos();
            qpos->push(nn);
            break;
        }
    }

}




void DialogSMSToDriver::on_btn_return_clicked()
{
    if(smsFile.isOpen())
    {

        smsFile.close();
    }

    this->accept();
}



void DialogSMSToDriver::on_btn_previous_clicked()
{
    ui->textEdit->clear();
    quint64 n;
    //    qDebug()<<"qpos size pre"<<qpos->size();
    //    for(int i=0;i<qpos->size();i++)
    //        qDebug()<<"previous"<<qpos->at(i);
    if(qpos->size()>2)
    {
        qpos->pop();
        qpos->pop();

        n = qpos->top(); //not pop, because need record
    }
    else if(qpos->size()>0)
    {
        qpos->pop(); //just leave 0 in qpos
        n=0;


        //        int i=qpos->length()-4;
        //        qDebug()<<"begini"<<i<<"length"<<(qpos->length());
        //        if(i<=0)
        //            i=0;
        //        qint64 mm=qpos->at(i);
        //        qts.seek(mm);
        //        //        qDebug()<<"mm"<<mm;
        //        if(qpos->size()>3)
        //        {
        //            qpos->pop();
        //            qpos->pop();
        //            qpos->pop();
        //        }
        //        qDebug()<<"after"<<"length"<<(qpos->length());

    }
    else
    {
        qpos->push(0);
        n=0;
    }
    qts.seek(n);
    getSMSContent();
}

void DialogSMSToDriver::on_btn_next_clicked()
{
    ui->textEdit->clear();
    //    qDebug()<<"qpos size next"<<qpos->size();
    //    for(int i=0;i<qpos->size();i++)
    //        qDebug()<<"next"<<qpos->at(i);
    if(qpos->size()>0)
    {
        //        qpos->pop();
        qint64 mm=qpos->top();//not pop, because need record the weiba.
        qts.seek(mm);
        //        qDebug()<<"mm"<<mm;
    }
    getSMSContent();
}

void DialogSMSToDriver::on_combox_smssource_currentIndexChanged(int index)
{
    QString smssource=ui->combox_smssource->itemText(index);
    //    qDebug()<<"sms source"<<smssource;
    QStringList filestobesele;
    if(smssource== "运营信息")
    {
        filestobesele=m_sms->findSMSInDirec();

    }
    else
    {
        filestobesele=m_log->findLogsInDirec();
    }

    ui->combox_sms->clear();
    for(int i=0;i<filestobesele.size();i++)
    {
        QString absolutetitle=filestobesele.at(i);
        QString title=absolutetitle.section("/",-1);
        ui->combox_sms->addItem(title);
    }

    ui->combox_sms->setCurrentIndex(ui->combox_sms->count()-1); //always the newest
}

void DialogSMSToDriver::on_combox_sms_currentIndexChanged(int index)
{
    if(index==-1)
        return;
    ui->textEdit->clear();
    getSelectFile(ui->combox_smssource->currentText());
    getSMSContent();
}
