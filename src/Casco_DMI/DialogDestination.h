/******************************
** Date: 2016/06/23
** Author: noodlebin
** Brief: when driver click the destination icon in tab area, the dialog will pop up  .h
** Version: 1.0
******************************/
#ifndef DIALOGDESTINATION_H
#define DIALOGDESTINATION_H

#include <QDialog>

namespace Ui {
class DialogDestination;
}

class DialogDestination : public QDialog
{
    Q_OBJECT
protected:
    void showEvent(QShowEvent *e);
public:
    explicit DialogDestination(QWidget *parent = 0);
    ~DialogDestination();
    int chosendes;
    int chosenservice;
    int chosentrip;
    int chosenpath;
    qint16 chosen_value;
    quint8 m_desorpath;
    void  setDestinationValue(quint8 number, quint16* desid);
    //    void setServiceValue(quint8 number, quint16 *serviceid);
    //    void setTripValue(quint8 number, quint16 *tripid);
    void setPathValue(quint8 number, quint16 *pathid);

    void intialmap(QMap<int,QString>* map);
    bool isexec;
    void cleartest();

private slots:
    void on_btn_OK_clicked();

    void on_cmb_desorpath_currentIndexChanged(int index);

    void on_btn_cancel_clicked();

private:
    Ui::DialogDestination *ui;
    quint8 m_des_num,m_path_num;
    quint16* m_des_id;
    quint16* m_path_id;

    QMap<int,QString>* m_des_map;
    quint8 m_servicemode;
};

#endif // DIALOGDESTINATION_H
