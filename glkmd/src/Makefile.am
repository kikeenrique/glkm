## Process this file with automake to produce Makefile.in

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" $(GLKM_DAEMON_CFLAGS)

AM_CFLAGS = \
	 -Wall \
	 -fstack-protector-all \
	 -g

bin_PROGRAMS = glkm_daemon \
	glkmd_test_client

glkmd_test_client_SOURCES = \
	LinuxKernelMonitor.hpp\
	LinuxKernelMonitor.cpp \
	glkmd_test_client.cpp

glkm_daemon_SOURCES = \
	LinuxKernelMonitor.hpp \
	LinuxKernelMonitor.cpp \
	LinuxKernelMonitor_i.hpp \
	LinuxKernelMonitor_i.cpp \
	glkm_daemon.cpp \
	SocketNetlink.cpp \
	SocketNetlink.hpp \
	MessageNetlink.hpp \
	MessageNetlink.cpp \
	GlkmNetlinkClient.hpp \
	GlkmNetlinkClient.cpp \
	MessageNetlinkGlkm.hpp \
	MessageNetlinkGlkm.cpp

glkm_daemon_LDFLAGS = 

glkmd_test_client_LDADD = $(GLKM_DAEMON_LIBS)

glkm_daemon_LDADD = $(GLKM_DAEMON_LIBS)

#corba_idl_HEADERS = \
#glkm_daemon_HEADERS = \
#	LinuxKernelMonitor.idl

LinuxKernelMonitor.hpp: 	LinuxKernelMonitor.idl
	omniidl -bcxx -Wbh=.hpp -Wbs=.cpp -Wbd=.cpp -Wba -Wbexample -WbBOA $^

#corba_idldir = \
#	$(pkgincludedir)

#EXTRA_DIST = \
#	$(glkm_daemon_HEADERS)

