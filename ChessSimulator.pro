TEMPLATE = app
CONFIG += c++11 no_keywords console

QT += qml quick qml
CONFIG += c++11

RESOURCES += qml.qrc

SOURCES += main.cpp  \
    ApplicationController.cpp \
    VideoDisplay/I420Render.cpp \
    VideoDisplay/VideoRender.cpp \
    ApplicationSim.cpp \
    MainProcess.cpp \
    RobotControler.cpp \
    Motor.cpp \
    ChessController.cpp

HEADERS += \
    ApplicationController.h \
    VideoDisplay/I420Render.h \
    VideoDisplay/VideoRender.h \
    ApplicationSim.h \
    MainProcess.h \
    RobotControler.h \
    Motor.h \
    ChessController.h

DISTFILES +=
