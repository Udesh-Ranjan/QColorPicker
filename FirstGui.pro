QT = core gui

greaterThan(QT_MAJOR_VERSION, 5): QT += widgets

SOURCES += \
    centralwidget.cpp \
    circularbutton.cpp \
    cmykcolorgroupbox.cpp \
    colorgroupbox.cpp \
    hexcolorgroupbox.cpp \
    hslcolorgroupbox.cpp \
    hsvcolorgroupbox.cpp \
    main.cpp \
    mainwindow.cpp \
    rgbcolorgroupbox.cpp \
    rightpanelcircularbutton.cpp \
    selectedcolorpanel.cpp \
    slider.cpp

HEADERS += \
    ColorChangeListener.h \
    ColorChangeManager.h \
    centralwidget.h \
    circularbutton.h \
    cmykcolorgroupbox.h \
    colorgroupbox.h \
    hexcolorgroupbox.h \
    hslcolorgroupbox.h \
    hsvcolorgroupbox.h \
    mainwindow.h \
    rgbcolorgroupbox.h \
    rightpanelcircularbutton.h \
    selectedcolorpanel.h \
    slider.h
