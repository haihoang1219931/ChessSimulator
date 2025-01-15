TEMPLATE = app
CONFIG += c++11 no_keywords console

QT += qml quick qml
CONFIG += c++11

RESOURCES += qml.qrc
QML_DESIGNER_IMPORT_PATH =
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
    ChessController.h \
    ProjectTypes.h

unix:!macx: INCLUDEPATH += /usr/local/include/opencv4
unix:!macx: DEPENDPATH += /usr/local/include/opencv4
unix:!macx: LIBS += -L/usr/local/lib/  \
    -lopencv_objdetect \
    -lopencv_shape -lopencv_stitching -lopencv_superres -lopencv_features2d -lopencv_calib3d \
    -lopencv_videostab \
    -lopencv_video \
    -lopencv_core \
    -lopencv_highgui \
    -lopencv_imgcodecs \
    -lopencv_imgproc \
    -lopencv_videoio

win32: LIBS += -lpthread
