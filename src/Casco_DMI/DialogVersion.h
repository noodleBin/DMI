/******************************
** Date: 2016/06/23
** Author: noodlebin
** Brief: when driver click the casco logo in top area, the dialog will pop up
** Version: 1.0
******************************/
#ifndef DIALOGVERSION_H
#define DIALOGVERSION_H

#include <QDialog>
#include <QDir>
#include <QMediaPlayer>

namespace Ui {
class DialogVersion;
}

class DialogVersion : public QDialog
{
    Q_OBJECT

public:
    explicit DialogVersion(QMediaPlayer* player, QString version, QWidget *parent = 0);
    void  setValue(QString appversion,QString dataversion);
    ~DialogVersion();

private slots:

    void on_btn_ok_clicked();
    void  on_volumeslider_sliderMoved(int position);

signals:
  void signalRefreshMute();

private:
    Ui::DialogVersion *ui;
    QString currentPath;
    QMediaPlayer* m_player;

    void toggleSound();
    void refreshSound();
protected:
    bool eventFilter(QObject *, QEvent *);
     void showEvent(QShowEvent *);
};

#endif // DIALOGVERSION_H
