QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dailyplan.cpp \
    dailysentencedialog.cpp \
    ddlreminder.cpp \
    longtermproject.cpp \
    main.cpp \
    mainwindow.cpp \
    pomodorowidget.cpp \
    projectitem.cpp \
    projectwidget.cpp \
    thecalendar.cpp\
    ddlitem.cpp\
    mycalendar.cpp\
    calendardialog.cpp\
    ddlwidget.cpp\


HEADERS += \
    dailyplan.h \
    dailysentencedialog.h \
    ddlreminder.h \
    longtermproject.h \
    mainwindow.h \
    pomodorowidget.h \
    projectitem.h \
    projectwidget.h \
    thecalendar.h\
    ddlitem.h\
    mycalendar.h\
    calendardialog.h\
    ddlwidget.h\

FORMS += \
    dailyplan.ui \
    ddlreminder.ui \
    longtermproject.ui \
    mainwindow.ui \
    thecalendar.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
