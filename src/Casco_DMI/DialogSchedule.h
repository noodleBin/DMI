/******************************
** Date: 2016/06/23
** Author: noodlebin
** Brief: when driver click the scheduleid text label in tab area, the dialog will pop up
** Version: 1.0
******************************/
#ifndef DIALOGSCHEDULE_H
#define DIALOGSCHEDULE_H

#include <QDialog>
#include <QMap>

namespace Ui {
class DialogSchedule;
}

class DialogSchedule : public QDialog
{
    Q_OBJECT
signals:
    void sendScheduleId(qint16 scheduleid);
    void sendServiceId(qint16 serviceid);
    void sendTripId(qint16 tripid);
protected:
    void showEvent(QShowEvent *);
    bool eventFilter(QObject *obj, QEvent *event);

public:
    explicit DialogSchedule(QMap<int,QString>*map,QWidget *parent = 0);
    ~DialogSchedule();
    void  setvalue(quint8 num1, quint16* schid, quint8 num2, quint16 *serviceid, quint8 num3, quint16 *tripid);
    int path;

    bool isexec;
private slots:
//    void on_btn_ok_clicked();
    void on_btn_cancel_clicked();


    void on_btn_sch_clicked();

    void on_btn_service_clicked();

    void on_btn_servicecancel_clicked();

    void on_btn_trip_clicked();

    void on_btn_tripcancel_clicked();

    void on_btn_schcancel_clicked();



private:
    Ui::DialogSchedule *ui;
    quint8 m_sch_num;
    quint8 m_service_num;
    quint8 m_trip_num;
    QMap<int,QString> *m_map_sch;
    quint16* m_sch_id;
    quint16* m_service_id;
    quint16* m_trip_id;
};

#endif // DIALOGSCHEDULE_H
