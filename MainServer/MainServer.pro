QT += sql network declarative
win32: LIBS += -lwsock32
win32: RC_FILE = myapp.rc

SOURCES += \
    main.cpp \
    webserver.cpp \
    mongoose.c \
    signalbridge.cpp \
    mainwindow.cpp \
    centralwidget.cpp \
    mainviewarea.cpp \
    navigatebar.cpp \
    button.cpp \
    addnewmenu.cpp \
    switchbutton.cpp \
    informationbar.cpp \
    iconview.cpp \
    ordermodel.cpp \
    managemenus.cpp \
    searchlineedit.cpp \
    synchronousdialog.cpp \
    server.cpp \
    clientsocket.cpp \
    listview.cpp \
    message.cpp

HEADERS += \
    webserver.h \
    mongoose.h \
    signalbridge.h \
    mainwindow.h \
    centralwidget.h \
    mainviewarea.h \
    navigatebar.h \
    button.h \
    addnewmenu.h \
    switchbutton.h \
    informationbar.h \
    iconview.h \
    ordermodel.h \
    managemenus.h \
    searchlineedit.h \
    synchronousdialog.h \
    server.h \
    clientsocket.h \
    listview.h \
    message.h

RESOURCES += \
    OpenMenus.qrc

OTHER_FILES += \
    wsock32.lib \
    SwitchButton.qml \
    libquazip.lib \
    IconView.qml \
    myapp.rc

FORMS += \
    addnewmenu.ui

win32: LIBS += -L$$PWD/quazip/ -llibquazip

INCLUDEPATH += $$PWD/quazip
DEPENDPATH += $$PWD/quazip

win32: PRE_TARGETDEPS += $$PWD/quazip/libquazip.lib
