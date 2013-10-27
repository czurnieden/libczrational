TEMPLATE = app
TARGET = test_library
DEPENDPATH += . ../src
INCLUDEPATH += . ../src
# build a dynamic library
CONFIG = dll debug warn_on 
   
# Input
SOURCES += test_library.c
HEADERS += ../src/czrational.h

LIBS = ../lib_static/libczrational.a -ltommath
unix:LIBS      +=  -lm
