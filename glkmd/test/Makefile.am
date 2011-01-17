## Process this file with automake to produce Makefile.in

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" $(GLKM_DAEMON_CFLAGS)

AM_CXXFLAGS = -I$(top_srcdir)/src @AM_CXXFLAGS@

bin_PROGRAMS = glkmd_test_client

glkmd_test_client_SOURCES = \
	glkmd_test_client.cpp

glkmd_test_client_LDADD = $(GLKM_DAEMON_LIBS) $(top_builddir)/src/LinuxKernelMonitor.o
