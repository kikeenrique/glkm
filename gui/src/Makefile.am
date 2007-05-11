## Process this file with automake to produce Makefile.in

## Created by Anjuta

gladedir = $(datadir)/glkm/glade
glade_DATA = glkm.glade

INCLUDES = \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	$(GLKM_CFLAGS)

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = glkm

glkm_SOURCES = \
	main.cc

glkm_LDFLAGS = 

glkm_LDADD = $(GLKM_LIBS)

EXTRA_DIST = $(glade_DATA)
