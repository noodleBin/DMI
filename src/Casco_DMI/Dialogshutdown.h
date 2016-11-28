#ifndef DIALOGSHUTDOWN_H
#define DIALOGSHUTDOWN_H

#include <QDialog>
#include <QMovie>
#include <QDir>

namespace Ui {
class DialogShutdown;
}

class DialogShutdown : public QDialog
{
    Q_OBJECT

public:
    explicit DialogShutdown(QWidget *parent = 0);
    ~DialogShutdown();
    void setValue(quint8 value);

private:
    Ui::DialogShutdown *ui;
    QString currentPath;
    QMovie *movieshutdown;

};

#endif // DIALOGSHUTDOWN_H
