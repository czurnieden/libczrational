TEMPLATE = subdirs

SUBDIRS = lib_static\
          lib_dyn\
          test\
          doc
CONFIG += ordered
#OBJECTS_DIR += src
QMAKE_EXTRA_TARGETS += doc
HEADERS = src/*h

header.files = $$HEADERS
headers.path = $$INSTALL_INC_DIR/czrational
INSTALLS  += headers

lib_dyn.path =  $$INSTALL_LIB_DIR/czrational/
lib_dyn.files =  lib_dyn/libczrational.so*
INSTALLS += lib_dyn

lib_static.path = $$INSTALL_LIB_DIR/czrational/
lib_static.files =  lib_static/libczrational.a
INSTALLS += lib_static
