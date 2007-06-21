## Process this file with automake to produce Makefile.in

glkm_gladedir = \
	$(glkm_glade_dir)
glkm_glade_DATA = \
	glkm.glade

AM_CFLAGS =\
	 -Wall

AM_CPPFLAGS = \
	$(GLKM_CFLAGS) \
	$(AM_CFLAGS) \
	$(LIBGNOME_CFLAGS) \
	-DPROGRAMNAME_LOCALEDIR="${PROGRAMNAME_LOCALEDIR}" \
	-DPACKAGE_LOCALE_DIR="$(prefix)/$(DATADIRNAME)/locale" \
	-DPACKAGE_SRC_DIR="$(srcdir)" \
	-DPACKAGE_DATA_DIR="$(datadir)"

bin_PROGRAMS = \
	glkm

glkm_SOURCES = \
	main.cc \
	glkm_mainwindow.h glkm_mainwindow.cc \
	glkm_aboutdialog.h glkm_aboutdialog.cc

#glkm_CFLAGS= \
#	$(GLKM_CFLAGS) 	$(AM_CFLAGS)	$(LIBGNOME_CFLAGS)
#glkm_CPPFLAGS= \
#	$(GLKM_CPPFLAGS)	$(AM_CPPFLAGS)
glkm_LDADD = \
	$(GLKM_LIBS) 		$(LIBGNOME_LIBS)
glkm_LDFLAGS = \
	$(GLKM_LDFLAGS)


	 

EXTRA_DIST = \
	$(glkm_glade_DATA)
