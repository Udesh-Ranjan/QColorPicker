QT = core gui

greaterThan(QT_MAJOR_VERSION, 5): QT += widgets

SOURCES += \
    centralwidget.cpp \
    circularbutton.cpp \
    main.cpp \
    mainwindow.cpp \
    selectedcolorpanel.cpp \
    slider.cpp

HEADERS += \
    ColorChangeListener.h \
    ColorChangeManager.h \
    centralwidget.h \
    circularbutton.h \
    mainwindow.h \
    selectedcolorpanel.h \
    slider.h
