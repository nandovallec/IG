HEADERS += \
  PLYobject.h \
  arm.h \
  colors.h \
  basic_object3d.h \
  cone.h \
  cube.h \
  cylinder.h \
  file_ply_stl.h \
  hand.h \
  human.h \
  leg.h \
  object3d.h \
  axis.h \
  semisphere.h \
  sphere.h \
  tetrahedron.h \
  glwidget.h \
  torso.h \
  window.h

SOURCES += \
  PLYobject.cc \
  arm.cpp \
  basic_object3d.cc \
  cone.cc \
  cube.cc \
  cylinder.cc \
  file_ply_stl.cc \
  hand.cpp \
  human.cpp \
  leg.cpp \
  object3d.cc \
  axis.cc \
  semisphere.cpp \
  sphere.cc \
  tetrahedron.cc \
  main.cc \
  glwidget.cc \
  torso.cpp \
  window.cc


LIBS += -L/usr/X11R6/lib64 -lGL


CONFIG += c++11
QT += widgets

DISTFILES += \
    ant.ply \
    beethoven.ply \
    big_dodge.ply \
    peon.ply \
    peon2.ply
