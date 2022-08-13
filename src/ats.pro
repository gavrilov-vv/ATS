QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

TARGET = ats


# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include(qtservice/src/qtservice.pri)

SOURCES += \
        AppLogger.cpp \
        AutoClickController.cpp \
        Configurator.cpp \
        Dispatcher.cpp \
        Models.cpp \
        Service.cpp \
        main.cpp

HEADERS += \
    AppLogger.h \
    AutoClickController.h \
    Configurator.h \
    Dispatcher.h \
    Models.h \
    Service.h \
    global_defs.h

OBJECTS_DIR = generated_files
MOC_DIR     = generated_files
UI_DIR      = generated_files
RCC_DIR     = generated_files
unix {

    DEPLOY_FOLDER = $$OUT_PWD/../deploy_files/ats

    tgt1.path  = $$DEPLOY_FOLDER
    tgt1.files += ats.conf
    tgt1.files += $$TARGET

    tgt2.path  = $$OUT_PWD
    tgt2.files += ats.conf

    tgt3.path  = $$OUT_PWD
    tgt3.files += $$PWD/scripts

    tgt4.path  = $$DEPLOY_FOLDER
    tgt4.files += $$PWD/scripts


    CONFIG(release, debug|release) {
        message(APC RELEASE BUILD)

        DEFINES += QT_NO_DEBUG_OUTPUT

        QMAKE_POST_LINK += make clean

    }

    CONFIG(debug, debug|release) {
        message(APC DEBUG BUILD)

    }

}

unix:!isEmpty(tgt1.path): INSTALLS += tgt1 tgt2 tgt3 tgt4

unix:!macx: LIBS += -L$$PWD/lib/ -llog4cplus

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

unix:!macx: PRE_TARGETDEPS += $$PWD/lib/liblog4cplus.a

DISTFILES += \
    ats.conf \
    scripts/Clicker.py \
    scripts/global_defs.py \
    scripts/main.py
