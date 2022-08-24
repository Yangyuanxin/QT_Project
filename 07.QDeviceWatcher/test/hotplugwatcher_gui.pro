TARGET = hotplugwatcher_gui
include(../src/libQDeviceWatcher.pri)

win32:!wince*:LIBS += -lUser32

HEADERS += \
    hotplugwatcher_gui.h

SOURCES += \
    hotplugwatcher_gui.cpp \
    main_gui.cpp

contains(MEEGO_EDITION,harmattan) {
    target.path = /opt/hotplugwatcher_gui/bin
    INSTALLS += target
}

maemo5 {
    target.path = /opt/hotplugwatcher_gui/bin
    INSTALLS += target
}
