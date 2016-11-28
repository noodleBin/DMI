#-------------------------------------------------
#
# Project created by QtCreator 2016-05-27T10:53:15
#
#-------------------------------------------------

QT       += core gui\
            uitools\
            network\
            xml\
            multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


TARGET = Casco_Tram_DMI
TEMPLATE = app



SOURCES += main.cpp\
    ../DMIDataStruct/els_dmi_protocol.cpp \
    DialogSmstodriver.cpp \
    Dashboard.cpp \
    DialogCommstatus.cpp \
    DialogDestination.cpp \
    DialogElsmodeselection.cpp \
    DialogObsstatus.cpp \
    DialogSchedule.cpp \
    DialogTimeshift.cpp \
    DialogTimeupdate.cpp \
    DialogVersion.cpp \
    ../DMIDataStruct/dmi_els_protocol.cpp \
    DialogLogin.cpp \
    DMILog.cpp \
    GeoEvents.cpp \
    TTSWorkerThread.cpp \
    DMISMS.cpp \
    TLEevents.cpp \
    ../DMIDataStruct/dms_dmi_protocol.cpp \
    Casco_dmi.cpp \
    Dialogwarningbox.cpp \
    Limitspeed.cpp \
    Dialogshutdown.cpp

HEADERS  += \
    ../DMIDataStruct/els_dmi_protocol.h \
    DialogSmstodriver.h \
    Dashboard.h \
    DialogCommstatus.h \
    DialogDestination.h \
    DialogElsmodeselection.h \
    DialogLogin.h \
    DialogObsstatus.h \
    DialogSchedule.h \
    DialogTimeshift.h \
    DialogTimeupdate.h \
    DialogVersion.h \
    ../DMIDataStruct/dmi_els_protocol.h \
    TTSWorkerThread.h \
    GeoEvents.h \
    DMILog.h \
    DMISMS.h \
    ../DMIDataStruct/dmi_dms_protocol.h \
    ../DMIDataStruct/dms_dmi_protocol.h \
    TLEevents.h \
    Casco_dmi.h \
    Dialogwarningbox.h \
     ../DMIDataStruct/Public_Variable.h \
    Limitspeed.h \
    Dialogshutdown.h \
    tlepublicvariables.h

LIBS += -L$$PWD/ -lmsc

FORMS    += \
    DialogCommstatus.ui \
    DialogDestination.ui \
    DialogElsmodeselection.ui \
    DialogLogin.ui \
    DialogObsstatus.ui \
    DialogSchedule.ui \
    DialogSmstodriver.ui \
    DialogTimeshift.ui \
    DialogTimeupdate.ui \
    DialogVersion.ui \
    Dialogwarningbox.ui \
    Dialogshutdown.ui

TRANSLATIONS+=  app_zh.ts

RESOURCES += \
    res.qrc

