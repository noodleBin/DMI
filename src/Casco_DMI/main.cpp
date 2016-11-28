#include <QApplication>
#include <QTranslator>
#include <Casco_dmi.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle("fusion");
    Casco_DMI w;
    if(w.isquit)
    {
       return 1;
    }
    return a.exec();
}


