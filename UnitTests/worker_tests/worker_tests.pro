#-------------------------------------------------
#
# Project created by QtCreator 2019-11-25T16:06:15
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_default_worker
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

win32:CONFIG(release, debug|release): LIBS += \
    -L$$OUT_PWD/../../Course/CourseLib/release/ -lCourseLib
else:win32:CONFIG(debug, debug|release): LIBS += \
    -L$$OUT_PWD/../../Course/CourseLib/debug/ -lCourseLib
else:unix: LIBS += \
    -L$$OUT_PWD/../../Course/CourseLib/ -lCourseLib


INCLUDEPATH += \
    $$PWD/../../Course/CourseLib \
    $$PWD/../../Game/

DEPENDPATH += \
    $$PWD/../../Course/CourseLib \
    $$PWD/../../Game


win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../../Course/CourseLib/release/libCourseLib.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../../Course/CourseLib/debug/libCourseLib.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../../Course/CourseLib/release/CourseLib.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../../Course/CourseLib/debug/CourseLib.lib
else:unix: PRE_TARGETDEPS += \
    $$OUT_PWD/../../Course/CourseLib/libCourseLib.a


HEADERS += \
    $$PWD/../../Game/player.h \
    $$PWD/../../Game/workers/sawmillworker.h \
    $$PWD/../../Game/workers/mineworker.h \
    $$PWD/../../Game/objectmanager.h \
    $$PWD/../../Game/gameeventhandler.h


SOURCES += \
        tst_default_worker.cpp \
    $$PWD/../../Game/player.cpp \
    $$PWD/../../Game/workers/sawmillworker.cpp \
    $$PWD/../../Game/workers/mineworker.cpp \
    $$PWD/../../Game/objectmanager.cpp \
    $$PWD/../../Game/gameeventhandler.cpp
