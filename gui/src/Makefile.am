## Process this file with automake to produce Makefile.in

AM_CPPFLAGS = \
	$(GLKM_CFLAGS) \
	$(LIBDBUSMM_CFLAGS) \
	$(LIBGNOME_CFLAGS) \
	$(LIBSIGCMM_CFLAGS) \
	$(GIOMM_CFLAGS) \
	-DPROGRAMNAME_LOCALEDIR="${PROGRAMNAME_LOCALEDIR}" \
	-DPACKAGE_LOCALE_DIR="$(prefix)/$(DATADIRNAME)/locale" \
	-DPACKAGE_DATA_DIR='"$(datadir)"' \
	-DPACKAGE_SRC_DIR="$(srcdir)" 

bin_PROGRAMS = \
	glkm

glkm_SOURCES = \
	main.cpp \
	sigsegv.c \
	debug.hpp \
	debug.cpp \
	utils.hpp \
	hal-controller.hpp \
	hal-controller.cpp \
	file.hpp \
	file.cpp \
	about-dialog.cpp \
	about-dialog.hpp \
	hal-device-proxy.cpp \
	hal-device-proxy.hpp \
	hal-manager-proxy.cpp \
	hal-manager-proxy.hpp \
	main-window.cpp \
	main-window.hpp \
	status-bar.cpp \
	status-bar.hpp \
	tree-view-host.cpp \
	tree-view-host.hpp \
	host.cpp \
	host.hpp \
	process.cpp \
	process.hpp \
	icon-view-hosts.hpp \
	icon-view-hosts.cpp \
	host-select-dialog.hpp \
	host-select-dialog.cpp \
	hosts.hpp \
	hosts.cpp \
	filesystem.hpp \
	filesystem.cpp \
	controller.hpp \
	controller.cpp \
	notebook-hosts.hpp \
	notebook-hosts.cpp \
	notebook-page-host.hpp \
	notebook-page-host.cpp \
	hal-parser.hpp \
	hal-parser.cpp \
	linux-kernel-monitor-client.hpp \
	linux-kernel-monitor-client.cpp \
	notebook-processes.hpp \
	notebook-processes.cpp \
	notebook-page-process.hpp \
	notebook-page-process.cpp

glkm_CFLAGS= \
	$(GLKM_CFLAGS) 	$(AM_CFLAGS)	$(LIBGNOME_CFLAGS) -fstack-protector-all

#glkm_CPPFLAGS= \
#	$(GLKM_CPPFLAGS)	$(AM_CPPFLAGS)
glkm_LDADD = \
	$(GLKM_LIBS) \
	$(LIBGNOME_LIBS) \
	$(LIBDBUSMM_LIBS) \
	$(LIBSIGCMM_LIBS) \
    $(GIOMM_LIBS)

#glkm_LDFLAGS = \
#	$(GLKM_LDFLAGS)
