TEMPLATE = app
TARGET = TheGame

QT += core gui widgets

CONFIG += c++14

SOURCES += \
    main.cpp \
    ui/mapwindow.cc \
    core/objectmanager.cpp \
    core/gameeventhandler.cpp \
    core/player.cpp \
    buildings/mine.cpp \
    buildings/sawmill.cpp \
    ui/begindialog.cpp \
    ui/enddialog.cpp \
    tiles/blockfield.cpp \
    tiles/oredeposit.cpp \
    workers/mineworker.cpp \
    workers/sawmillworker.cpp \
    tiles/water.cpp \
    graphics/gamescene.cpp \
    graphics/mapitem.cpp \
    setupgame.cpp

HEADERS += \
    ui/mapwindow.hh \
    core/objectmanager.h \
    core/gameeventhandler.h \
    core/player.h \
    buildings/mine.hh \
    buildings/sawmill.hh \
    ui/begindialog.hh \
    core/resourcemaps_v2.hh \
    ui/enddialog.hh \
    tiles/blockfield.h \
    tiles/oredeposit.h \
    workers/mineworker.h \
    workers/sawmillworker.h \
    tiles/water.h \
    graphics/gamescene.h \
    graphics/mapitem.h \
    setupgame.h

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
    ui/mapwindow.ui \
    ui/begindialog.ui \
    ui/enddialog.ui

DISTFILES += \
    images/SawMillWorker.png \
    images/Sawmill.png \
    images/Outpost.png \
    images/MineWorker.png \
    images/Mine.png \
    images/HeadQuarters.png \
    images/Farm.png \
    images/BasicWorker.png

RESOURCES += \
    resources.qrc
