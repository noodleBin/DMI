/******************************
** Date: 2016/06/23
** Author: noodlebin
** Brief: when driver click the driverid label in top area, the dialog will pop up .cpp
** Version: 1.0
******************************/
#include "DialogLogin.h"
#include "ui_DialogLogin.h"

DialogLogin::DialogLogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogLogin)
{
    driverID="";
    driverpassword="";
    ui->setupUi(this);
    ui->btn_cancel->setText(tr("cancel"));
    ui->btn_ok->setText(tr("ok"));
    ui->btn_login->setText(tr("login"));


    ispassword=false;
    warningbox = new DialogWarningbox(parent);

    ui->lineEdit_driverID->installEventFilter(this);
    ui->lbl_password->setVisible(false);
    ui->lineEdit_driverpassword->setVisible(false);
    ui->lineEdit_driverpassword->installEventFilter(this);
    this->installEventFilter(this);
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::CoverWindow);

    ui->btn_0->setFocusPolicy(Qt::NoFocus);
    ui->btn_1->setFocusPolicy(Qt::NoFocus);
    ui->btn_2->setFocusPolicy(Qt::NoFocus);
    ui->btn_3->setFocusPolicy(Qt::NoFocus);
    ui->btn_4->setFocusPolicy(Qt::NoFocus);
    ui->btn_5->setFocusPolicy(Qt::NoFocus);
    ui->btn_6->setFocusPolicy(Qt::NoFocus);
    ui->btn_7->setFocusPolicy(Qt::NoFocus);
    ui->btn_8->setFocusPolicy(Qt::NoFocus);
    ui->btn_9->setFocusPolicy(Qt::NoFocus);
    ui->btn_login->setFocusPolicy(Qt::NoFocus);
    ui->btn_cancel->setFocusPolicy(Qt::NoFocus);
    ui->btn_ok->setFocusPolicy(Qt::NoFocus);
    ui->btn_back->setFocusPolicy(Qt::NoFocus);  //这部分就是为了当键盘按return，能不被其他按键影响
    ui->btn_clear->setFocusPolicy(Qt::NoFocus);
    ui->btn_dot->setFocusPolicy(Qt::NoFocus);
}

DialogLogin::~DialogLogin()
{
    delete ui;
}

void DialogLogin::setTripAndPath(quint16 tripid, quint16 pathid,quint16 lineid,quint16 physicaltrainid)
{
    ui->lbl_tripid->setText(QString::number(tripid));
    ui->lbl_pathid->setText(QString::number(pathid));
    ui->lbl_lineid->setText(QString::number(lineid));
    ui->lbl_physicaltrainid->setText(QString::number(physicaltrainid));
}


void DialogLogin::on_btn_7_clicked()
{
    if(!ispassword)
    {
        driverID+="7";
        ui->lineEdit_driverID->setText(driverID);
        ui->lineEdit_driverID->setFocus();
    }
    else
    {
        driverpassword+="7";
        ui->lineEdit_driverpassword->setText(driverpassword);
        ui->lineEdit_driverpassword->setFocus();
    }
}

void DialogLogin::on_btn_8_clicked()
{
    if(!ispassword)
    {
        driverID+="8";
        ui->lineEdit_driverID->setText(driverID);
        ui->lineEdit_driverID->setFocus();
    }
    else
    {
        driverpassword+="8";
        ui->lineEdit_driverpassword->setText(driverpassword);
        ui->lineEdit_driverpassword->setFocus();
    }

}

void DialogLogin::on_btn_9_clicked()
{
    if(!ispassword)
    {
        driverID+="9";
        ui->lineEdit_driverID->setText(driverID);
        ui->lineEdit_driverID->setFocus();
    }
    else
    {
        driverpassword+="9";
        ui->lineEdit_driverpassword->setText(driverpassword);
        ui->lineEdit_driverpassword->setFocus();
    }

}

void DialogLogin::on_btn_back_clicked()
{
    if(!ispassword)
    {
        driverID.chop(1);
        ui->lineEdit_driverID->setText(driverID);
        ui->lineEdit_driverID->setFocus();
    }
    else
    {
        driverpassword.chop(1);
        ui->lineEdit_driverpassword->setText(driverpassword);
        ui->lineEdit_driverpassword->setFocus();
    }
}

void DialogLogin::on_btn_clear_clicked()
{
    if(!ispassword)
    {
        driverID="";
        ui->lineEdit_driverID->setText(driverID);
        ui->lineEdit_driverID->setFocus();
    }
    else
    {
        driverpassword="";
        ui->lineEdit_driverpassword->setText(driverpassword);
        ui->lineEdit_driverpassword->setFocus();
    }

}

void DialogLogin::on_btn_6_clicked()
{
    if(!ispassword)
    {
        driverID+="6";
        ui->lineEdit_driverID->setText(driverID);
        ui->lineEdit_driverID->setFocus();
    }
    else
    {
        driverpassword+="6";
        ui->lineEdit_driverpassword->setText(driverpassword);
        ui->lineEdit_driverpassword->setFocus();
    }
}

void DialogLogin::on_btn_5_clicked()
{
    if(!ispassword)
    {
        driverID+="5";
        ui->lineEdit_driverID->setText(driverID);
        ui->lineEdit_driverID->setFocus();
    }
    else
    {
        driverpassword+="5";
        ui->lineEdit_driverpassword->setText(driverpassword);
        ui->lineEdit_driverpassword->setFocus();
    }
}

void DialogLogin::on_btn_4_clicked()
{
    if(!ispassword)
    {
        driverID+="4";
        ui->lineEdit_driverID->setText(driverID);
        ui->lineEdit_driverID->setFocus();
    }
    else
    {
        driverpassword+="4";
        ui->lineEdit_driverpassword->setText(driverpassword);
        ui->lineEdit_driverpassword->setFocus();
    }
}





void DialogLogin::on_btn_login_clicked()
{
    bool ok,ok1;
    quint16 driverid=driverID.toShort(&ok,10);
    ok1=true;
//    quint16 password=driverpassword.toShort(&ok1,10);
    if(ok&&driverid<=32767)
    {
//        if(driverid==0)
//        {
            this->accept();
//        }
//        else if(ok1&&password<=32767)
//        {
//            if(m_driver_info->value(driverid)==password)
//            {
//                this->accept();
//            }
//            else
//            {
//                warningbox->setValue("司机号和密码不匹配");
//                warningbox->exec();
//            }
//        }
//        else
//        {
//            warningbox->setValue("密码输入范围在0-32767");
//            warningbox->exec();
//         }
    }
    else
    {
        warningbox->setValue("司机号输入范围在0-32767");
        warningbox->exec();
    }

}

void DialogLogin::on_btn_1_clicked()
{
    if(!ispassword)
    {
        driverID+="1";
        ui->lineEdit_driverID->setText(driverID);
        ui->lineEdit_driverID->setFocus();
    }
    else
    {
        driverpassword+="1";
        ui->lineEdit_driverpassword->setText(driverpassword);
        ui->lineEdit_driverpassword->setFocus();
    }

}

void DialogLogin::on_btn_2_clicked()
{
    if(!ispassword)
    {
        driverID+="2";
        ui->lineEdit_driverID->setText(driverID);
        ui->lineEdit_driverID->setFocus();
    }
    else
    {
        driverpassword+="2";
        ui->lineEdit_driverpassword->setText(driverpassword);
        ui->lineEdit_driverpassword->setFocus();
    }
}

void DialogLogin::on_btn_3_clicked()
{
    if(!ispassword)
    {
        driverID+="3";
        ui->lineEdit_driverID->setText(driverID);
        ui->lineEdit_driverID->setFocus();
    }
    else
    {
        driverpassword+="3";
        ui->lineEdit_driverpassword->setText(driverpassword);
        ui->lineEdit_driverpassword->setFocus();
    }
}

void DialogLogin::on_btn_0_clicked()
{
    if(!ispassword)
    {
        driverID+="0";
        ui->lineEdit_driverID->setText(driverID);
        ui->lineEdit_driverID->setFocus();
    }
    else
    {
        driverpassword+="0";
        ui->lineEdit_driverpassword->setText(driverpassword);
        ui->lineEdit_driverpassword->setFocus();
    }
}

bool DialogLogin::eventFilter(QObject *obj, QEvent * event)
{
    if(obj==ui->lineEdit_driverID)
    {
        if(event->type()==QEvent::MouseButtonRelease)
        {
            ispassword=false;
            return true;
        }
        else
            return false;
    }
    else if(obj==ui->lineEdit_driverpassword)
    {
        if(event->type()==QEvent::MouseButtonRelease)
        {
            ispassword=true;
            return true;
        }
        else
            return false;
    }
    //    qDebug()<<"type"<<event->type();
    if(event->type()==QEvent::KeyRelease)
    {
        QKeyEvent* key =(QKeyEvent*)(event);
        if(key->key()==Qt::Key_Return)
        {
            if(ispassword)
            {
                ui->lineEdit_driverID->setFocus();
            }
            else
            {
                ui->lineEdit_driverpassword->setFocus();
            }
            ispassword=!ispassword;
            return true;
        }
        else if(key->key()==Qt::Key_1)
        {
            on_btn_1_clicked();
            return true;
        }
        else if(key->key()==Qt::Key_2)
        {
            on_btn_2_clicked();
            return true;
        }
        else if(key->key()==Qt::Key_3)
        {
            on_btn_3_clicked();
            return true;
        }
        else if(key->key()==Qt::Key_4)
        {
            on_btn_4_clicked();
            return true;
        }
        else if(key->key()==Qt::Key_5)
        {
            on_btn_5_clicked();
            return true;
        }
        else if(key->key()==Qt::Key_6)
        {
            on_btn_6_clicked();
            return true;
        }
        else if(key->key()==Qt::Key_7)
        {
            on_btn_7_clicked();
            return true;
        }
        else if(key->key()==Qt::Key_8)
        {
            on_btn_8_clicked();
            return true;
        }
        else if(key->key()==Qt::Key_9)
        {
            on_btn_9_clicked();
            return true;
        }
        else if(key->key()==Qt::Key_0)
        {
            on_btn_0_clicked();
            return true;
        }
        else if(key->key()==Qt::Key_Backspace)
        {

            on_btn_back_clicked();
            return true;
        }

        else
            return false;

    }
    else
        return QDialog::eventFilter(obj,event);
}




void DialogLogin::on_btn_cancel_clicked()
{
    this->reject();
}

void DialogLogin::on_btn_ok_clicked()
{
    if(ispassword)
    {
        ui->lineEdit_driverID->setFocus();
    }
    else
    {
        ui->lineEdit_driverpassword->setFocus();
    }
    ispassword=!ispassword;
}

void DialogLogin::setInfo(QMap<quint16, quint16> *map)
{
    m_driver_info=map;
}
