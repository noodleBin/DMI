/******************************
** Date: 2016/06/23
** Author: noodlebin
** Brief: when driver click the elsmode text in atp area, the dialog will pop up  .h
** Version: 1.0
******************************/
#ifndef DIALOGELSMODESELECTION_H
#define DIALOGELSMODESELECTION_H

#include <QDialog>

namespace Ui {
class DialogELSModeSelection;
}

class DialogELSModeSelection : public QDialog
{
    Q_OBJECT

public:
    explicit DialogELSModeSelection(QWidget *parent = 0);
    ~DialogELSModeSelection();

    quint8 modevalue;
private slots:
    void on_btn_ok_clicked();

    void on_btn_cancel_clicked();

private:
    Ui::DialogELSModeSelection *ui;
};

#endif // DIALOGELSMODESELECTION_H
