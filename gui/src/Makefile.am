## Process this file with automake to produce Makefile.in

AM_CFLAGS =\
	 -Wall

AM_CPPFLAGS = \
	$(GLKM_CFLAGS) \
	$(LIBDBUSMM_CFLAGS) \
	$(LIBGNOME_CFLAGS) \
	-DPROGRAMNAME_LOCALEDIR="${PROGRAMNAME_LOCALEDIR}" \
	-DPACKAGE_LOCALE_DIR="$(prefix)/$(DATADIRNAME)/locale" \
	-DPACKAGE_DATA_DIR="$(datadir)" \
	-DPACKAGE_SRC_DIR="$(srcdir)" 

bin_PROGRAMS = \
	glkm

glkm_SOURCES = \
	main.cpp \
	glkm_mainwindow.hpp glkm_mainwindow.cpp \
	glkm_aboutdialog.hpp glkm_aboutdialog.cpp \
	glkm_procces.cpp \
	glkm_procces.hpp \
	glkm_statusbar.hpp \
	glkm_statusbar.cpp \
	debug.hpp \
	debug.cpp \
	glkm_hal_device_proxy.hpp \
	glkm_hal_device_proxy.cpp \
	glkm_hal_manager_proxy.cpp \
	glkm_hal_manager_proxy.hpp \
	glkm_host.cpp \
	glkm_host.hpp \
	utils.hpp \
	hal-controller.hpp \
	hal-controller.cpp \
	glkm_treeviewhost.cpp \
	glkm_treeviewhost.hpp \
	file.hpp \
	file.cpp

#glkm_CFLAGS= \
#	$(GLKM_CFLAGS) 	$(AM_CFLAGS)	$(LIBGNOME_CFLAGS)
#glkm_CPPFLAGS= \
#	$(GLKM_CPPFLAGS)	$(AM_CPPFLAGS)
glkm_LDADD = \
	$(GLKM_LIBS) \
	$(LIBGNOME_LIBS) \
	$(LIBDBUSMM_LIBS)

#glkm_LDFLAGS = \
#	$(GLKM_LDFLAGS)
