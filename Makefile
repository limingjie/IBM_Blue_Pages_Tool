#############################################################################
# Makefile for building: Bluepages
# Generated by qmake (2.01a) (Qt 4.8.4) on: Tue Dec 31 22:08:13 2013
# Project:  Bluepages.pro
# Template: app
# Command: c:\Qt\qt-4.8.4-msvc2010-static\bin\qmake.exe -spec c:\Qt\qt-4.8.4-msvc2010-static\mkspecs\win32-msvc2010 -o Makefile Bluepages.pro
#############################################################################

first: release
install: release-install
uninstall: release-uninstall
MAKEFILE      = Makefile
QMAKE         = c:\Qt\qt-4.8.4-msvc2010-static\bin\qmake.exe
DEL_FILE      = del
CHK_DIR_EXISTS= if not exist
MKDIR         = mkdir
COPY          = copy /y
COPY_FILE     = $(COPY)
COPY_DIR      = xcopy /s /q /y /i
INSTALL_FILE  = $(COPY_FILE)
INSTALL_PROGRAM = $(COPY_FILE)
INSTALL_DIR   = $(COPY_DIR)
DEL_FILE      = del
SYMLINK       = 
DEL_DIR       = rmdir
MOVE          = move
CHK_DIR_EXISTS= if not exist
MKDIR         = mkdir
SUBTARGETS    =  \
		release \
		debug

release: $(MAKEFILE).Release FORCE
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Release
release-make_default: $(MAKEFILE).Release FORCE
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Release 
release-make_first: $(MAKEFILE).Release FORCE
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Release first
release-all: $(MAKEFILE).Release FORCE
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Release all
release-clean: $(MAKEFILE).Release FORCE
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Release clean
release-distclean: $(MAKEFILE).Release FORCE
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Release distclean
release-install: $(MAKEFILE).Release FORCE
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Release install
release-uninstall: $(MAKEFILE).Release FORCE
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Release uninstall
debug: $(MAKEFILE).Debug FORCE
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Debug
debug-make_default: $(MAKEFILE).Debug FORCE
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Debug 
debug-make_first: $(MAKEFILE).Debug FORCE
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Debug first
debug-all: $(MAKEFILE).Debug FORCE
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Debug all
debug-clean: $(MAKEFILE).Debug FORCE
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Debug clean
debug-distclean: $(MAKEFILE).Debug FORCE
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Debug distclean
debug-install: $(MAKEFILE).Debug FORCE
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Debug install
debug-uninstall: $(MAKEFILE).Debug FORCE
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Debug uninstall

Makefile: Bluepages.pro  c:\Qt\qt-4.8.4-msvc2010-static\mkspecs\win32-msvc2010\qmake.conf c:\Qt\qt-4.8.4-msvc2010-static\mkspecs\qconfig.pri \
		c:\Qt\qt-4.8.4-msvc2010-static\mkspecs\features\qt_functions.prf \
		c:\Qt\qt-4.8.4-msvc2010-static\mkspecs\features\qt_config.prf \
		c:\Qt\qt-4.8.4-msvc2010-static\mkspecs\features\exclusive_builds.prf \
		c:\Qt\qt-4.8.4-msvc2010-static\mkspecs\features\default_pre.prf \
		c:\Qt\qt-4.8.4-msvc2010-static\mkspecs\features\win32\default_pre.prf \
		c:\Qt\qt-4.8.4-msvc2010-static\mkspecs\features\release.prf \
		c:\Qt\qt-4.8.4-msvc2010-static\mkspecs\features\debug_and_release.prf \
		c:\Qt\qt-4.8.4-msvc2010-static\mkspecs\features\default_post.prf \
		c:\Qt\qt-4.8.4-msvc2010-static\mkspecs\features\win32\default_post.prf \
		c:\Qt\qt-4.8.4-msvc2010-static\mkspecs\features\static.prf \
		c:\Qt\qt-4.8.4-msvc2010-static\mkspecs\features\win32\rtti.prf \
		c:\Qt\qt-4.8.4-msvc2010-static\mkspecs\features\win32\exceptions.prf \
		c:\Qt\qt-4.8.4-msvc2010-static\mkspecs\features\win32\stl.prf \
		c:\Qt\qt-4.8.4-msvc2010-static\mkspecs\features\win32\embed_manifest_exe.prf \
		c:\Qt\qt-4.8.4-msvc2010-static\mkspecs\features\win32\embed_manifest_dll.prf \
		c:\Qt\qt-4.8.4-msvc2010-static\mkspecs\features\warn_on.prf \
		c:\Qt\qt-4.8.4-msvc2010-static\mkspecs\features\qt.prf \
		c:\Qt\qt-4.8.4-msvc2010-static\mkspecs\features\win32\thread.prf \
		c:\Qt\qt-4.8.4-msvc2010-static\mkspecs\features\moc.prf \
		c:\Qt\qt-4.8.4-msvc2010-static\mkspecs\features\win32\windows.prf \
		c:\Qt\qt-4.8.4-msvc2010-static\mkspecs\features\resources.prf \
		c:\Qt\qt-4.8.4-msvc2010-static\mkspecs\features\uic.prf \
		c:\Qt\qt-4.8.4-msvc2010-static\mkspecs\features\yacc.prf \
		c:\Qt\qt-4.8.4-msvc2010-static\mkspecs\features\lex.prf \
		c:\Qt\qt-4.8.4-msvc2010-static\mkspecs\features\include_source_dir.prf \
		c:\Qt\qt-4.8.4-msvc2010-static\lib\qtmain.prl \
		c:\Qt\qt-4.8.4-msvc2010-static\lib\QtGui.prl \
		c:\Qt\qt-4.8.4-msvc2010-static\lib\QtNetwork.prl \
		c:\Qt\qt-4.8.4-msvc2010-static\lib\QtCore.prl
	$(QMAKE) -spec c:\Qt\qt-4.8.4-msvc2010-static\mkspecs\win32-msvc2010 -o Makefile Bluepages.pro
c:\Qt\qt-4.8.4-msvc2010-static\mkspecs\qconfig.pri:
c:\Qt\qt-4.8.4-msvc2010-static\mkspecs\features\qt_functions.prf:
c:\Qt\qt-4.8.4-msvc2010-static\mkspecs\features\qt_config.prf:
c:\Qt\qt-4.8.4-msvc2010-static\mkspecs\features\exclusive_builds.prf:
c:\Qt\qt-4.8.4-msvc2010-static\mkspecs\features\default_pre.prf:
c:\Qt\qt-4.8.4-msvc2010-static\mkspecs\features\win32\default_pre.prf:
c:\Qt\qt-4.8.4-msvc2010-static\mkspecs\features\release.prf:
c:\Qt\qt-4.8.4-msvc2010-static\mkspecs\features\debug_and_release.prf:
c:\Qt\qt-4.8.4-msvc2010-static\mkspecs\features\default_post.prf:
c:\Qt\qt-4.8.4-msvc2010-static\mkspecs\features\win32\default_post.prf:
c:\Qt\qt-4.8.4-msvc2010-static\mkspecs\features\static.prf:
c:\Qt\qt-4.8.4-msvc2010-static\mkspecs\features\win32\rtti.prf:
c:\Qt\qt-4.8.4-msvc2010-static\mkspecs\features\win32\exceptions.prf:
c:\Qt\qt-4.8.4-msvc2010-static\mkspecs\features\win32\stl.prf:
c:\Qt\qt-4.8.4-msvc2010-static\mkspecs\features\win32\embed_manifest_exe.prf:
c:\Qt\qt-4.8.4-msvc2010-static\mkspecs\features\win32\embed_manifest_dll.prf:
c:\Qt\qt-4.8.4-msvc2010-static\mkspecs\features\warn_on.prf:
c:\Qt\qt-4.8.4-msvc2010-static\mkspecs\features\qt.prf:
c:\Qt\qt-4.8.4-msvc2010-static\mkspecs\features\win32\thread.prf:
c:\Qt\qt-4.8.4-msvc2010-static\mkspecs\features\moc.prf:
c:\Qt\qt-4.8.4-msvc2010-static\mkspecs\features\win32\windows.prf:
c:\Qt\qt-4.8.4-msvc2010-static\mkspecs\features\resources.prf:
c:\Qt\qt-4.8.4-msvc2010-static\mkspecs\features\uic.prf:
c:\Qt\qt-4.8.4-msvc2010-static\mkspecs\features\yacc.prf:
c:\Qt\qt-4.8.4-msvc2010-static\mkspecs\features\lex.prf:
c:\Qt\qt-4.8.4-msvc2010-static\mkspecs\features\include_source_dir.prf:
c:\Qt\qt-4.8.4-msvc2010-static\lib\qtmain.prl:
c:\Qt\qt-4.8.4-msvc2010-static\lib\QtGui.prl:
c:\Qt\qt-4.8.4-msvc2010-static\lib\QtNetwork.prl:
c:\Qt\qt-4.8.4-msvc2010-static\lib\QtCore.prl:
qmake: qmake_all FORCE
	@$(QMAKE) -spec c:\Qt\qt-4.8.4-msvc2010-static\mkspecs\win32-msvc2010 -o Makefile Bluepages.pro

qmake_all: FORCE

make_default: release-make_default debug-make_default FORCE
make_first: release-make_first debug-make_first FORCE
all: release-all debug-all FORCE
clean: release-clean debug-clean FORCE
	-$(DEL_FILE) ".\Bluepages.intermediate.manifest"
distclean: release-distclean debug-distclean FORCE
	-$(DEL_FILE) Makefile

check: first

release-mocclean: $(MAKEFILE).Release
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Release mocclean
debug-mocclean: $(MAKEFILE).Debug
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Debug mocclean
mocclean: release-mocclean debug-mocclean

release-mocables: $(MAKEFILE).Release
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Release mocables
debug-mocables: $(MAKEFILE).Debug
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Debug mocables
mocables: release-mocables debug-mocables
FORCE:

$(MAKEFILE).Release: Makefile
$(MAKEFILE).Debug: Makefile