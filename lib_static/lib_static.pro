
TEMPLATE = lib
TARGET = czrational
VERSION = 0.0.1
DEPENDPATH += . ../src
INCLUDEPATH += . ../src
# build a dynamic library
CONFIG = staticlib debug warn_on
OBJECTS_DIR = ../src
# Input
SOURCES += ../src/*c
HEADERS += ../src/czrational.h

LIBS = -ltommath
unix:LIBS      +=  -lm

header.path = /usr/local/include/czrational/
header.files = $$HEADERS
lib_static.path = /usr/local/lib/czrational/
lib_static.files +=  libczrational.a
INSTALLS += lib_static
INSTALLS += header