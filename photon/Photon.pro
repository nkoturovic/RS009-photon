QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    blurdialog.cpp \
    brightnessdialog.cpp \
    contrastdialog.cpp \
    cropdialog.cpp \
    custom_visitors.cpp \
    folijadijalog.cpp \
    label_image.cpp \
    main.cpp \
    oprogramudialog.cpp \
    photon_main.cpp \
    photon_undo.cpp \
    undoitem.cpp \
    undopreview.cpp

HEADERS += \
    blurdialog.h \
    brightnessdialog.h \
    contrastdialog.h \
    cropdialog.h \
    custom_visitors.hpp \
    folijadijalog.h \
    label_image.h \
    oprogramudialog.h \
    photon_main.h \
    photon_undo.hpp \
    undoitem.h \
    undopreview.h

FORMS += \
    blurdialog.ui \
    brightnessdialog.ui \
    contrastdialog.ui \
    cropdialog.ui \
    folijadijalog.ui \
    oprogramudialog.ui \
    photon_main.ui

INCLUDEPATH += \
    include

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Icons.qrc \
    logo.qrc

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/./release/ -lrsimg
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/./debug/ -lrsimg
else:unix: LIBS += -L$$PWD/./ -lrsimg

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/./release/librsimg.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/./debug/librsimg.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/./release/rsimg.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/./debug/rsimg.lib
else:unix: PRE_TARGETDEPS += $$PWD/./librsimg.a

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += opencv
