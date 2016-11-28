/******************************
** Date: 2016/06/23
** Author: noodlebin
** Brief: when driver click the datetime in top area, the dialog will pop up
** Version: 1.0
******************************/
#ifndef DIALOGTIMEUPDATE_H
#define DIALOGTIMEUPDATE_H

#include <QDialog>
#include <QDateTime>
namespace Ui {
class DialogTimeUpdate;
}

class DialogTimeUpdate : public QDialog
{
    Q_OBJECT

public:
    explicit DialogTimeUpdate(QWidget *parent = 0);
    ~DialogTimeUpdate();

private slots:
    void on_btn_ok_clicked();

    void on_calendarWidget_selectionChanged();

    void on_timeEdit_timeChanged(const QTime &time);

private:
    Ui::DialogTimeUpdate *ui;
};

#endif // DIALOGTIMEUPDATE_H
