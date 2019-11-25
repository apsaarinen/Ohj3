TEMPLATE = app
TARGET = TheGame

QT += core gui widgets

CONFIG += c++14

SOURCES += \
    main.cpp \
    mapwindow.cc \
    objectmanager.cpp \
    gameeventhandler.cpp \
    gameengine.cpp \
    player.cpp \
    buildings/mine.cpp \
    buildings/sawmill.cpp \
    begindialog.cpp \
    enddialog.cpp \
    tiles/blockfield.cpp \
    tiles/oredeposit.cpp \
    workers/mineworker.cpp \
    workers/sawmillworker.cpp \
    tiles/water.cpp \
    graphics/gamescene.cpp \
    graphics/mapitem.cpp

HEADERS += \
    mapwindow.hh \
    objectmanager.h \
    gameeventhandler.h \
    gameengine.h \
    player.h \
    buildings/mine.hh \
    buildings/sawmill.hh \
    begindialog.hh \
    resourcemaps_v2.hh \
    enddialog.hh \
    tiles/blockfield.h \
    tiles/oredeposit.h \
    workers/mineworker.h \
    workers/sawmillworker.h \
    tiles/water.h \
    graphics/gamescene.h \
    graphics/mapitem.h

win32:CONFIG(release, debug|release): LIBS += \
    -L$$OUT_PWD/../Course/CourseLib/release/ -lCourseLib
else:win32:CONFIG(debug, debug|release): LIBS += \
    -L$$OUT_PWD/../Course/CourseLib/debug/ -lCourseLib
else:unix: LIBS += \
    -L$$OUT_PWD/../Course/CourseLib/ -lCourseLib

INCLUDEPATH += \
    $$PWD/../Course/CourseLib

DEPENDPATH += \
    $$PWD/../Course/CourseLib

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/release/libCourseLib.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/debug/libCourseLib.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/release/CourseLib.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/debug/CourseLib.lib
else:unix: PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/libCourseLib.a

FORMS += \
    mapwindow.ui \
    begindialog.ui \
    enddialog.ui

DISTFILES += \
    images/SawMillWorker.png \
    images/Sawmill.png \
    images/Outpost.png \
    images/MineWorker.png \
    images/Mine.png \
    images/HeadQuarters.png \
    images/hakku.png \
    images/Farm.png \
    images/BasicWorker.png

RESOURCES += \
    resources.qrc
