QT -= gui core opengl
TARGET = exercise
TEMPLATE = app
OBJECTS_DIR = obj
VPATH = ../.. ../../include ../../src

DEFINES += GL_EXT_PROTOTYPES

INCLUDEPATH += ../../include

linux-g++ {
    LIBS += -lGL -lGLU -lglut -lalut
}

macx {
        LIBS += -framework OpenGL -framework GLUT
}


SOURCES +=  \
main.cpp\
types.cpp\
utils.cpp\
timer.cpp\
applicationParameters.cpp\
window.cpp\
scene.cpp\
camera.cpp\
camera2D.cpp\
camera3D.cpp\
material.cpp\
texture.cpp\
screenTexture.cpp\
light.cpp\
positionalLight.cpp\
directionalLight.cpp\
spotLight.cpp\
text.cpp\
plyData.cpp\
plyModel.cpp\
monitor.cpp\
stage.cpp\
text3d.cpp\
soundClass.cpp\


HEADERS += \
defs.hpp\
opengl_includes.hpp\
exception.hpp\
types.hpp\
vector.hpp\
utils.hpp\
timer.hpp\
keyboardEventHandler.hpp\
mouseEventHandler.hpp\
applicationParameters.hpp\
window.hpp\
scene.hpp\
camera.hpp\
camera2D.hpp\
camera3D.hpp\
material.hpp\
texture.hpp\
screenTexture.hpp\
light.hpp\
positionalLight.hpp\
directionalLight.hpp\
spotLight.hpp\
drawable.hpp\
text.hpp\
plyData.hpp\
plyModel.hpp\
monitor.hpp\
stage.hpp\
text3d.h\
soundClass.hpp\
