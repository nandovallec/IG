HEADERS += \
  PLYobject.h \
  colors.h \
  basic_object3d.h \
  cone.h \
  cube.h \
  cylinder.h \
  file_ply_stl.h \
  object3d.h \
  axis.h \
  sphere.h \
  tetrahedron.h \
  glwidget.h \
  torso.h \
  window.h

SOURCES += \
  PLYobject.cc \
  basic_object3d.cc \
  cone.cc \
  cube.cc \
  cylinder.cc \
  file_ply_stl.cc \
  object3d.cc \
  axis.cc \
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
