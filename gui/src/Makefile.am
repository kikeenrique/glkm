## Process this file with automake to produce Makefile.in

AM_CFLAGS =\
	 -Wall

AM_CPPFLAGS = \
	$(GLKM_CFLAGS) \
	$(AM_CFLAGS) \
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
	glkm_treeview_process.cpp \
	glkm_treeview_process.hpp \
	glkm_statusbar.hpp \
	glkm_statusbar.cpp

#glkm_CFLAGS= \
#	$(GLKM_CFLAGS) 	$(AM_CFLAGS)	$(LIBGNOME_CFLAGS)
#glkm_CPPFLAGS= \
#	$(GLKM_CPPFLAGS)	$(AM_CPPFLAGS)
glkm_LDADD = \
	$(GLKM_LIBS) 		$(LIBGNOME_LIBS)
glkm_LDFLAGS = \
	$(GLKM_LDFLAGS)
