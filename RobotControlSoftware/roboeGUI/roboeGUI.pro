TEMPLATE = app

QT += qml quick widgets

SOURCES += main.cpp \
    mysocket.cpp

RESOURCES += qml.qrc

INCLUDEPATH += /opt/local/include

LIBS += -L/opt/local/lib

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

DISTFILES +=

HEADERS += \
    mysocket.h
