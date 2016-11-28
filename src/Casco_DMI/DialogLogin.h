/******************************
** Date: 2016/06/23
** Author: noodlebin
** Brief: when driver click the driverid label in top area, the dialog will pop up .h
** Version: 1.0
******************************/
#ifndef DIALOGLOGIN_H
#define DIALOGLOGIN_H

#include <QDialog>
#include <QMessageBox>
#include <QMap>
#include <QKeyEvent>
#include <QDebug>
#include "Dialogwarningbox.h"
namespace Ui {
class DialogLogin;
}

class DialogLogin : public QDialog
{
    Q_OBJECT

public:
    explicit DialogLogin(QWidget *parent = 0);
    ~DialogLogin();
    void setTripAndPath(quint16 tripid, quint16 pathid, quint16 lineid, quint16 physicaltrainid);

private slots:
    void on_btn_7_clicked();
    void on_btn_8_clicked();
    void on_btn_9_clicked();
    void on_btn_back_clicked();
    void on_btn_clear_clicked();
    void on_btn_6_clicked();
    void on_btn_5_clicked();
    void on_btn_4_clicked();
    void on_btn_login_clicked();
    void on_btn_1_clicked();
    void on_btn_2_clicked();
    void on_btn_3_clicked();
    void on_btn_0_clicked();



    void on_btn_cancel_clicked();

    void on_btn_ok_clicked();



private:
    Ui::DialogLogin *ui;
    QMap<quint16,quint16> *m_driver_info;
    DialogWarningbox *warningbox;
    bool ispassword;

public :
    int test2;

    QString driverID;
    QString driverpassword;
    QString test;

    void setInfo(QMap<quint16, quint16> *map);
protected:
    bool eventFilter(QObject *, QEvent *);

};

#endif // DIALOGLOGIN_H
