TEMPLATE	= app
QT          += widgets
HEADERS         = MyView.h \
    myscene.h \
    readmap.h \
    simpleitem.h \
    stationitem.h
SOURCES		= main.cpp  \
    MyView.cpp \
    myscene.cpp \
    readmap.cpp \
    stationitem.cpp
windows:TARGET	= ../CustomGraphicsView

