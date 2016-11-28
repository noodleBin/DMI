#-------------------------------------------------
#
# Project created by QtCreator 2016-02-25T10:13:56
#
#-------------------------------------------------

QT       += core gui\
            network\
            xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SimulateELS
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ../DMIDataStruct/dms_dmi_protocol.cpp \
    ../DMIDataStruct/dmi_els_protocol.cpp \
    ../DMIDataStruct/els_dmi_protocol.cpp

HEADERS  += mainwindow.h \
    ../DMIDataStruct/dmi_dms_protocol.h \
    ../DMIDataStruct/dms_dmi_protocol.h \
    ../DMIDataStruct/dmi_els_protocol.h \
    ../DMIDataStruct/els_dmi_protocol.h

FORMS    += mainwindow.ui
