/******************************
** Date: 2016/06/23
** Author: noodlebin
** Brief: when driver click the obs icon in mission area, the dialog will pop up   .h
** Version: 1.0
******************************/
#ifndef DIALOGOBSSTATUS_H
#define DIALOGOBSSTATUS_H

#include <QDialog>
#include <QDir>

namespace Ui {
class DialogOBSStatus;
}

class DialogOBSStatus : public QDialog
{
    Q_OBJECT

public:
    explicit DialogOBSStatus(QWidget *parent = 0);
    ~DialogOBSStatus();
    void setPicStatus(quint8 v);


protected:
    bool eventFilter(QObject *, QEvent *);
private:
    Ui::DialogOBSStatus *ui;
    QString currentPath;
};

#endif // DIALOGOBSSTATUS_H
