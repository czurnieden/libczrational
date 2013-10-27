#############################################################################
# Makefile for building: libczrational
# Generated by qmake (2.01a) (Qt 4.6.3) on: So. Okt 27 03:39:51 2013
# Project:  libczrational.pro
# Template: subdirs
# Command: /usr/bin/qmake -unix -o Makefile libczrational.pro
#############################################################################

first: make_default
MAKEFILE      = Makefile
QMAKE         = /usr/bin/qmake
DEL_FILE      = rm -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p
COPY          = cp -f
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
INSTALL_FILE  = install -m 644 -p
INSTALL_PROGRAM = install -m 755 -p
INSTALL_DIR   = $(COPY_DIR)
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p
SUBTARGETS    =  \
		sub-lib_static \
		sub-lib_dyn \
		sub-test \
		sub-doc

lib_static//$(MAKEFILE): 
	@$(CHK_DIR_EXISTS) lib_static/ || $(MKDIR) lib_static/ 
	cd lib_static/ && $(QMAKE) /home/czurnieden/GITHUB/libczrational/lib_static/lib_static.pro -unix -o $(MAKEFILE)
sub-lib_static-qmake_all:  FORCE
	@$(CHK_DIR_EXISTS) lib_static/ || $(MKDIR) lib_static/ 
	cd lib_static/ && $(QMAKE) /home/czurnieden/GITHUB/libczrational/lib_static/lib_static.pro -unix -o $(MAKEFILE)
sub-lib_static: lib_static//$(MAKEFILE) FORCE
	cd lib_static/ && $(MAKE) -f $(MAKEFILE)
sub-lib_static-make_default-ordered: lib_static//$(MAKEFILE) FORCE
	cd lib_static/ && $(MAKE) -f $(MAKEFILE) 
sub-lib_static-make_default: lib_static//$(MAKEFILE) FORCE
	cd lib_static/ && $(MAKE) -f $(MAKEFILE) 
sub-lib_static-make_first-ordered: lib_static//$(MAKEFILE) FORCE
	cd lib_static/ && $(MAKE) -f $(MAKEFILE) first
sub-lib_static-make_first: lib_static//$(MAKEFILE) FORCE
	cd lib_static/ && $(MAKE) -f $(MAKEFILE) first
sub-lib_static-all-ordered: lib_static//$(MAKEFILE) FORCE
	cd lib_static/ && $(MAKE) -f $(MAKEFILE) all
sub-lib_static-all: lib_static//$(MAKEFILE) FORCE
	cd lib_static/ && $(MAKE) -f $(MAKEFILE) all
sub-lib_static-clean-ordered: lib_static//$(MAKEFILE) FORCE
	cd lib_static/ && $(MAKE) -f $(MAKEFILE) clean
sub-lib_static-clean: lib_static//$(MAKEFILE) FORCE
	cd lib_static/ && $(MAKE) -f $(MAKEFILE) clean
sub-lib_static-distclean-ordered: lib_static//$(MAKEFILE) FORCE
	cd lib_static/ && $(MAKE) -f $(MAKEFILE) distclean
sub-lib_static-distclean: lib_static//$(MAKEFILE) FORCE
	cd lib_static/ && $(MAKE) -f $(MAKEFILE) distclean
sub-lib_static-install_subtargets-ordered: lib_static//$(MAKEFILE) FORCE
	cd lib_static/ && $(MAKE) -f $(MAKEFILE) install
sub-lib_static-install_subtargets: lib_static//$(MAKEFILE) FORCE
	cd lib_static/ && $(MAKE) -f $(MAKEFILE) install
sub-lib_static-uninstall_subtargets-ordered: lib_static//$(MAKEFILE) FORCE
	cd lib_static/ && $(MAKE) -f $(MAKEFILE) uninstall
sub-lib_static-uninstall_subtargets: lib_static//$(MAKEFILE) FORCE
	cd lib_static/ && $(MAKE) -f $(MAKEFILE) uninstall
lib_dyn//$(MAKEFILE): 
	@$(CHK_DIR_EXISTS) lib_dyn/ || $(MKDIR) lib_dyn/ 
	cd lib_dyn/ && $(QMAKE) /home/czurnieden/GITHUB/libczrational/lib_dyn/lib_dyn.pro -unix -o $(MAKEFILE)
sub-lib_dyn-qmake_all:  FORCE
	@$(CHK_DIR_EXISTS) lib_dyn/ || $(MKDIR) lib_dyn/ 
	cd lib_dyn/ && $(QMAKE) /home/czurnieden/GITHUB/libczrational/lib_dyn/lib_dyn.pro -unix -o $(MAKEFILE)
sub-lib_dyn: lib_dyn//$(MAKEFILE) FORCE
	cd lib_dyn/ && $(MAKE) -f $(MAKEFILE)
sub-lib_dyn-make_default-ordered: lib_dyn//$(MAKEFILE) sub-lib_static-make_default-ordered  FORCE
	cd lib_dyn/ && $(MAKE) -f $(MAKEFILE) 
sub-lib_dyn-make_default: lib_dyn//$(MAKEFILE) FORCE
	cd lib_dyn/ && $(MAKE) -f $(MAKEFILE) 
sub-lib_dyn-make_first-ordered: lib_dyn//$(MAKEFILE) sub-lib_static-make_first-ordered  FORCE
	cd lib_dyn/ && $(MAKE) -f $(MAKEFILE) first
sub-lib_dyn-make_first: lib_dyn//$(MAKEFILE) FORCE
	cd lib_dyn/ && $(MAKE) -f $(MAKEFILE) first
sub-lib_dyn-all-ordered: lib_dyn//$(MAKEFILE) sub-lib_static-all-ordered  FORCE
	cd lib_dyn/ && $(MAKE) -f $(MAKEFILE) all
sub-lib_dyn-all: lib_dyn//$(MAKEFILE) FORCE
	cd lib_dyn/ && $(MAKE) -f $(MAKEFILE) all
sub-lib_dyn-clean-ordered: lib_dyn//$(MAKEFILE) sub-lib_static-clean-ordered  FORCE
	cd lib_dyn/ && $(MAKE) -f $(MAKEFILE) clean
sub-lib_dyn-clean: lib_dyn//$(MAKEFILE) FORCE
	cd lib_dyn/ && $(MAKE) -f $(MAKEFILE) clean
sub-lib_dyn-distclean-ordered: lib_dyn//$(MAKEFILE) sub-lib_static-distclean-ordered  FORCE
	cd lib_dyn/ && $(MAKE) -f $(MAKEFILE) distclean
sub-lib_dyn-distclean: lib_dyn//$(MAKEFILE) FORCE
	cd lib_dyn/ && $(MAKE) -f $(MAKEFILE) distclean
sub-lib_dyn-install_subtargets-ordered: lib_dyn//$(MAKEFILE) sub-lib_static-install_subtargets-ordered  FORCE
	cd lib_dyn/ && $(MAKE) -f $(MAKEFILE) install
sub-lib_dyn-install_subtargets: lib_dyn//$(MAKEFILE) FORCE
	cd lib_dyn/ && $(MAKE) -f $(MAKEFILE) install
sub-lib_dyn-uninstall_subtargets-ordered: lib_dyn//$(MAKEFILE) sub-lib_static-uninstall_subtargets-ordered  FORCE
	cd lib_dyn/ && $(MAKE) -f $(MAKEFILE) uninstall
sub-lib_dyn-uninstall_subtargets: lib_dyn//$(MAKEFILE) FORCE
	cd lib_dyn/ && $(MAKE) -f $(MAKEFILE) uninstall
test//$(MAKEFILE): 
	@$(CHK_DIR_EXISTS) test/ || $(MKDIR) test/ 
	cd test/ && $(QMAKE) /home/czurnieden/GITHUB/libczrational/test/test.pro -unix -o $(MAKEFILE)
sub-test-qmake_all:  FORCE
	@$(CHK_DIR_EXISTS) test/ || $(MKDIR) test/ 
	cd test/ && $(QMAKE) /home/czurnieden/GITHUB/libczrational/test/test.pro -unix -o $(MAKEFILE)
sub-test: test//$(MAKEFILE) FORCE
	cd test/ && $(MAKE) -f $(MAKEFILE)
sub-test-make_default-ordered: test//$(MAKEFILE) sub-lib_dyn-make_default-ordered  FORCE
	cd test/ && $(MAKE) -f $(MAKEFILE) 
sub-test-make_default: test//$(MAKEFILE) FORCE
	cd test/ && $(MAKE) -f $(MAKEFILE) 
sub-test-make_first-ordered: test//$(MAKEFILE) sub-lib_dyn-make_first-ordered  FORCE
	cd test/ && $(MAKE) -f $(MAKEFILE) first
sub-test-make_first: test//$(MAKEFILE) FORCE
	cd test/ && $(MAKE) -f $(MAKEFILE) first
sub-test-all-ordered: test//$(MAKEFILE) sub-lib_dyn-all-ordered  FORCE
	cd test/ && $(MAKE) -f $(MAKEFILE) all
sub-test-all: test//$(MAKEFILE) FORCE
	cd test/ && $(MAKE) -f $(MAKEFILE) all
sub-test-clean-ordered: test//$(MAKEFILE) sub-lib_dyn-clean-ordered  FORCE
	cd test/ && $(MAKE) -f $(MAKEFILE) clean
sub-test-clean: test//$(MAKEFILE) FORCE
	cd test/ && $(MAKE) -f $(MAKEFILE) clean
sub-test-distclean-ordered: test//$(MAKEFILE) sub-lib_dyn-distclean-ordered  FORCE
	cd test/ && $(MAKE) -f $(MAKEFILE) distclean
sub-test-distclean: test//$(MAKEFILE) FORCE
	cd test/ && $(MAKE) -f $(MAKEFILE) distclean
sub-test-install_subtargets-ordered: test//$(MAKEFILE) sub-lib_dyn-install_subtargets-ordered  FORCE
	cd test/ && $(MAKE) -f $(MAKEFILE) install
sub-test-install_subtargets: test//$(MAKEFILE) FORCE
	cd test/ && $(MAKE) -f $(MAKEFILE) install
sub-test-uninstall_subtargets-ordered: test//$(MAKEFILE) sub-lib_dyn-uninstall_subtargets-ordered  FORCE
	cd test/ && $(MAKE) -f $(MAKEFILE) uninstall
sub-test-uninstall_subtargets: test//$(MAKEFILE) FORCE
	cd test/ && $(MAKE) -f $(MAKEFILE) uninstall
doc//$(MAKEFILE): 
	@$(CHK_DIR_EXISTS) doc/ || $(MKDIR) doc/ 
	cd doc/ && $(QMAKE) /home/czurnieden/GITHUB/libczrational/doc/doc.pro -unix -o $(MAKEFILE)
sub-doc-qmake_all:  FORCE
	@$(CHK_DIR_EXISTS) doc/ || $(MKDIR) doc/ 
	cd doc/ && $(QMAKE) /home/czurnieden/GITHUB/libczrational/doc/doc.pro -unix -o $(MAKEFILE)
sub-doc: doc//$(MAKEFILE) FORCE
	cd doc/ && $(MAKE) -f $(MAKEFILE)
sub-doc-make_default-ordered: doc//$(MAKEFILE) sub-test-make_default-ordered  FORCE
	cd doc/ && $(MAKE) -f $(MAKEFILE) 
sub-doc-make_default: doc//$(MAKEFILE) FORCE
	cd doc/ && $(MAKE) -f $(MAKEFILE) 
sub-doc-make_first-ordered: doc//$(MAKEFILE) sub-test-make_first-ordered  FORCE
	cd doc/ && $(MAKE) -f $(MAKEFILE) first
sub-doc-make_first: doc//$(MAKEFILE) FORCE
	cd doc/ && $(MAKE) -f $(MAKEFILE) first
sub-doc-all-ordered: doc//$(MAKEFILE) sub-test-all-ordered  FORCE
	cd doc/ && $(MAKE) -f $(MAKEFILE) all
sub-doc-all: doc//$(MAKEFILE) FORCE
	cd doc/ && $(MAKE) -f $(MAKEFILE) all
sub-doc-clean-ordered: doc//$(MAKEFILE) sub-test-clean-ordered  FORCE
	cd doc/ && $(MAKE) -f $(MAKEFILE) clean
sub-doc-clean: doc//$(MAKEFILE) FORCE
	cd doc/ && $(MAKE) -f $(MAKEFILE) clean
sub-doc-distclean-ordered: doc//$(MAKEFILE) sub-test-distclean-ordered  FORCE
	cd doc/ && $(MAKE) -f $(MAKEFILE) distclean
sub-doc-distclean: doc//$(MAKEFILE) FORCE
	cd doc/ && $(MAKE) -f $(MAKEFILE) distclean
sub-doc-install_subtargets-ordered: doc//$(MAKEFILE) sub-test-install_subtargets-ordered  FORCE
	cd doc/ && $(MAKE) -f $(MAKEFILE) install
sub-doc-install_subtargets: doc//$(MAKEFILE) FORCE
	cd doc/ && $(MAKE) -f $(MAKEFILE) install
sub-doc-uninstall_subtargets-ordered: doc//$(MAKEFILE) sub-test-uninstall_subtargets-ordered  FORCE
	cd doc/ && $(MAKE) -f $(MAKEFILE) uninstall
sub-doc-uninstall_subtargets: doc//$(MAKEFILE) FORCE
	cd doc/ && $(MAKE) -f $(MAKEFILE) uninstall

Makefile: libczrational.pro  /usr/share/qt4/mkspecs/linux-g++/qmake.conf /usr/share/qt4/mkspecs/common/g++.conf \
		/usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf
	$(QMAKE) -unix -o Makefile libczrational.pro
/usr/share/qt4/mkspecs/common/g++.conf:
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
/usr/share/qt4/mkspecs/features/release.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/warn_on.prf:
/usr/share/qt4/mkspecs/features/qt.prf:
/usr/share/qt4/mkspecs/features/unix/thread.prf:
/usr/share/qt4/mkspecs/features/moc.prf:
/usr/share/qt4/mkspecs/features/resources.prf:
/usr/share/qt4/mkspecs/features/uic.prf:
/usr/share/qt4/mkspecs/features/yacc.prf:
/usr/share/qt4/mkspecs/features/lex.prf:
/usr/share/qt4/mkspecs/features/include_source_dir.prf:
qmake: qmake_all FORCE
	@$(QMAKE) -unix -o Makefile libczrational.pro

qmake_all: sub-lib_static-qmake_all sub-lib_dyn-qmake_all sub-test-qmake_all sub-doc-qmake_all FORCE

make_default: sub-lib_static-make_default-ordered sub-lib_dyn-make_default-ordered sub-test-make_default-ordered sub-doc-make_default-ordered FORCE
make_first: sub-lib_static-make_first-ordered sub-lib_dyn-make_first-ordered sub-test-make_first-ordered sub-doc-make_first-ordered FORCE
all: sub-lib_static-all-ordered sub-lib_dyn-all-ordered sub-test-all-ordered sub-doc-all-ordered FORCE
clean: sub-lib_static-clean-ordered sub-lib_dyn-clean-ordered sub-test-clean-ordered sub-doc-clean-ordered FORCE
distclean: sub-lib_static-distclean-ordered sub-lib_dyn-distclean-ordered sub-test-distclean-ordered sub-doc-distclean-ordered FORCE
	-$(DEL_FILE) Makefile
install_subtargets: sub-lib_static-install_subtargets-ordered sub-lib_dyn-install_subtargets-ordered sub-test-install_subtargets-ordered sub-doc-install_subtargets-ordered FORCE
uninstall_subtargets: sub-lib_static-uninstall_subtargets-ordered sub-lib_dyn-uninstall_subtargets-ordered sub-test-uninstall_subtargets-ordered sub-doc-uninstall_subtargets-ordered FORCE

doc:

sub-lib_static-check_ordered: lib_static/$(MAKEFILE)
	cd lib_static/ && $(MAKE) check
sub-lib_dyn-check_ordered: lib_dyn/$(MAKEFILE) sub-lib_static-check_ordered 
	cd lib_dyn/ && $(MAKE) check
sub-test-check_ordered: test/$(MAKEFILE) sub-lib_dyn-check_ordered 
	cd test/ && $(MAKE) check
sub-doc-check_ordered: doc/$(MAKEFILE) sub-test-check_ordered 
	cd doc/ && $(MAKE) check
check: sub-lib_static-check_ordered sub-lib_dyn-check_ordered sub-test-check_ordered sub-doc-check_ordered

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all
install: install_subtargets  FORCE

uninstall:  uninstall_subtargets FORCE

FORCE:
