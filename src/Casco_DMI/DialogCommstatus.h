/******************************
** Date: 2016/06/23
** Author: noodlebin
** Brief: when driver click the Communication icon in mission area, the dialog will pop up  .h
** Version: 1.0
******************************/
#ifndef DIALOGCOMMSTATUS_H
#define DIALOGCOMMSTATUS_H

#include <QDialog>
#include <QDir>

namespace Ui {
class DialogCommstatus;
}

class DialogCommstatus : public QDialog
{
    Q_OBJECT

public:
    explicit DialogCommstatus(QWidget *parent = 0);
    ~DialogCommstatus();
    void setPicRadioCoverDMSELS(quint8 v);
    void setPicCommDMSELS(quint8 v);
    void setPicRadioDMSELS(quint8 v);

protected:
    bool eventFilter(QObject *, QEvent *);
private:
    Ui::DialogCommstatus *ui;
    QString currentPath;
};

#endif // DIALOGCOMMSTATUS_H
