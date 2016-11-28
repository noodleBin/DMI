#ifndef DIALOGWARNINGBOX_H
#define DIALOGWARNINGBOX_H

#include <QDialog>
#include <QDir>
namespace Ui {
class DialogWarningbox;
}

class DialogWarningbox : public QDialog
{
    Q_OBJECT

public:
    explicit DialogWarningbox(QWidget *parent = 0);
    ~DialogWarningbox();
    void setValue(QString txt);

private slots:
    void on_btn_ok_clicked();

private:
    Ui::DialogWarningbox *ui;
    QString currentPath;
};

#endif // DIALOGWARNINGBOX_H
