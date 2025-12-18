QT       += core gui widgets

CONFIG += c++17

INCLUDEPATH += $$PWD/headers

SOURCES += \
    src/main.cpp \
    src/MainWindow.cpp

HEADERS += \
    headers/CalculatorModel.h \
    headers/MainWindow.h

DESTDIR     = $$OUT_PWD/bin
OBJECTS_DIR = $$OUT_PWD/obj
MOC_DIR     = $$OUT_PWD/moc
RCC_DIR     = $$OUT_PWD/rcc
UI_DIR      = $$OUT_PWD/ui
