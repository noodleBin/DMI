/******************************
** Date: 2016/06/23
** Author: noodlebin
** Brief: respond to tts function, use the tts library provided by kedaxunfei
** Version: 1.0
******************************/
#ifndef TTSWORKER_H
#define TTSWORKER_H
#include <QDebug>
#include <stdlib.h>
#include <stdio.h>
//#include <windows.h>
//#include <conio.h>
#include <errno.h>
#include "qtts.h"
#include "msp_cmn.h"
#include "msp_errors.h"
#include <QObject>


#include <QThread>

class TTSWorker:public QObject
{
    Q_OBJECT

public :
    TTSWorker();
public slots:
    void TTSConvert(QString txt, char* filename);

signals:
    void resultReady();
};

#endif // TTSWORKER_H
