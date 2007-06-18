## Process this file with automake to produce Makefile.in

gladedir = $(datadir)/glkm/glade
glade_DATA = glkm.glade

AM_CPPFLAGS = \
	-DPROGRAMNAME_LOCALEDIR=\"${PROGRAMNAME_LOCALEDIR}\"\
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	$(GLKM_CFLAGS)

AM_CFLAGS =\
	 -Wall\
	 -DPROGRAMNAME_LOCALEDIR=\"${PROGRAMNAME_LOCALEDIR}\"\
	 -g

bin_PROGRAMS = glkm

glkm_SOURCES = \
	main.cc \
	glkm_mainwindow.h glkm_mainwindow.c\
	glkm_aboutdialog.h glkm_aboutdialog.c
	
glkm_LDFLAGS = 

glkm_LDADD = $(GLKM_LIBS)

EXTRA_DIST = $(glade_DATA)
