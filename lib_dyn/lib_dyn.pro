
TEMPLATE = lib
TARGET = czrational
VERSION = 0.0.1
DEPENDPATH += . ../src
INCLUDEPATH += . ../src
# build a dynamic library
CONFIG = dll debug warn_on

# Input
#SOURCES += ../src/*c
HEADERS += ../src/czrational.h
OBJECTS_DIR = ../src
INPUT = ../src/*o 
LIBS =  $${INPUT}  -ltommath
unix:LIBS      +=  -lm

header.path = /usr/local/include/czrational/
header.files = $$HEADERS
lib_dyn.path = /usr/local/lib/czrational/
lib_dyn.files =  libczrational.so*
INSTALLS += lib_dyn
INSTALLS += header