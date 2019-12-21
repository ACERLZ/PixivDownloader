#  ______   ______     __         __     __  __        ______     _____     __     ______   __     ______     __   __
# /\  ___\ /\  ___\   /\ \       /\ \   /\_\_\_\      /\  ___\   /\  __-.  /\ \   /\__  _\ /\ \   /\  __ \   /\ "-.\ \
# \ \  __\ \ \  __\   \ \ \____  \ \ \  \/_/\_\/_     \ \  __\   \ \ \/\ \ \ \ \  \/_/\ \/ \ \ \  \ \ \/\ \  \ \ \-.  \
#  \ \_\    \ \_____\  \ \_____\  \ \_\   /\_\/\_\     \ \_____\  \ \____-  \ \_\    \ \_\  \ \_\  \ \_____\  \ \_\\"\_\
#   \/_/     \/_____/   \/_____/   \/_/   \/_/\/_/      \/_____/   \/____/   \/_/     \/_/   \/_/   \/_____/   \/_/ \/_/

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PixivDownloader

CONFIG += c++11
CONFIG+=sdk_no_version_check

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

unix:!mac {
    isEmpty(PREFIX) {
        PREFIX = /usr/local
    }

    target.path = $$PREFIX/bin

    shortcutfiles.files = resources/PixivDownloader.desktop
    shortcutfiles.path = $$PREFIX/share/applications/
    data.files += resources/icons/Icon.png
    data.path = $$PREFIX/share/hicolor/256x256/PixivDownloader.png

    INSTALLS += shortcutfiles
    INSTALLS += data
}

INSTALLS += target

SOURCES += \
    src/apppixivapi.cpp \
    src/basepixivapi.cpp \
    src/downloadwindow.cpp \
    src/logger.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/paths.cpp \
    src/preferenceswindow.cpp \
    src/settings.cpp

HEADERS += \
    src/apppixivapi.h \
    src/basepixivapi.h \
    src/downloadwindow.h \
    src/logger.h \
    src/mainwindow.h \
    src/paths.h \
    src/preferenceswindow.h \
    src/settings.h

INCLUDEPATH += $$PWD/src/plog/include

FORMS += \
    ui/downloadwindow.ui \
    ui/mainwindow.ui \
    ui/preferenceswindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources/resources.qrc
