/******************************
** Date: 2016/06/23
** Author: noodlebin
** Brief: when driver click the delay/advance text label in top area, the dialog will pop up  .h
** Version: 1.0
******************************/
#ifndef DIALOGTIMESHIFT_H
#define DIALOGTIMESHIFT_H

#include <QDialog>

namespace Ui {
class Dialogtimeshift;
}

class Dialogtimeshift : public QDialog
{
    Q_OBJECT

public:
    explicit Dialogtimeshift(QWidget *parent = 0);
    ~Dialogtimeshift();
    void setvalue(quint16 service,QString des, qint16 delay);

private slots:
    void on_btn_timeshift_clicked();

    void on_btn_cancel_clicked();

private:
    Ui::Dialogtimeshift *ui;
};

#endif // DIALOGTIMESHIFT_H
