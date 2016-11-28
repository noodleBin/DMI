/******************************
** Date: 2016/06/23
** Author: noodlebin
** Brief: when driver click the input button in bottom area, the dialog will pop up
** Version: 1.0
******************************/
#ifndef DIALOGSMSTODRIVER_H
#define DIALOGSMSTODRIVER_H

#include <QDialog>
#include <QListWidget>
#include <QQueue>
#include <QStack>
#include <QFileInfoList>
#include <QDateTime>
#include <QDebug>
#include <QDir>
#include <QTextStream>
#include "DMILog.h"
#include "DMISMS.h"
#include <QKeyEvent>

namespace Ui {
class DialogSMSToDriver;
}

class DialogSMSToDriver : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSMSToDriver(DMI_Log *log,DMISMS *sms,QWidget* parent);
    ~DialogSMSToDriver();

private slots:

    void on_btn_return_clicked();

    void on_btn_previous_clicked();

    void on_btn_next_clicked();

    void on_combox_smssource_currentIndexChanged(int index);

    void on_combox_sms_currentIndexChanged(int index);

private:
    Ui::DialogSMSToDriver *ui;
    //    QMap<qint16 ,QString > *smsmap;
    QQueue<QString> *que_sms;
    QTextStream qts;

    QString currentContent;

    QStack<qint64> *qpos;

    void getSMSContent();
    void getSelectFile(QString type);

    QFile smsFile;
    DMI_Log* m_log;
    DMISMS* m_sms;

protected:
   void showEvent(QShowEvent* e);
protected:
    bool eventFilter(QObject *, QEvent *);
};

#endif // DIALOGSMSTODRIVER_H
