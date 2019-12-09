HEADERS += \
  PLYobject.h \
  arm.h \
  body.h \
  chess_board.h \
  colors.h \
  basic_object3d.h \
  cone.h \
  cube.h \
  cylinder.h \
  eye.h \
  feet.h \
  file_ply_stl.h \
  hand.h \
  head.h \
  human.h \
  leg.h \
  mouth.h \
  object3d.h \
  axis.h \
  pupil.h \
  revolutionobject.h \
  semisphere.h \
  sphere.h \
  stick.h \
  tetrahedron.h \
  glwidget.h \
  texturelight.h \
  torso.h \
  window.h

SOURCES += \
  PLYobject.cc \
  arm.cpp \
  basic_object3d.cc \
  body.cpp \
  chess_board.cpp \
  cone.cc \
  cube.cc \
  cylinder.cc \
  eye.cpp \
  feet.cpp \
  file_ply_stl.cc \
  hand.cpp \
  head.cpp \
  human.cpp \
  leg.cpp \
  mouth.cpp \
  object3d.cc \
  axis.cc \
  pupil.cpp \
  revolutionobject.cpp \
  semisphere.cpp \
  sphere.cc \
  stick.cpp \
  tetrahedron.cc \
  main.cc \
  glwidget.cc \
  texturelight.cpp \
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
