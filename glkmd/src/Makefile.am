## Process this file with automake to produce Makefile.in

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" $(LIBOMNIORB_CFLAGS)

bin_PROGRAMS = glkm_daemon

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

#glkm_daemon_LDFLAGS = 

glkm_daemon_LDADD = $(LIBOMNIORB_LIBS) $(LIBNETLINK_LIBS)

#corba_idl_HEADERS = \
#glkm_daemon_HEADERS = \
#	LinuxKernelMonitor.idl

LinuxKernelMonitor.hpp: 	LinuxKernelMonitor.idl
	omniidl -bcxx -Wbh=.hpp -Wbs=.cpp -Wbd=.cpp -Wba -Wbexample -WbBOA $^

#corba_idldir = \
#	$(pkgincludedir)

#EXTRA_DIST = \
#	$(glkm_daemon_HEADERS)

