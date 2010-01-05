## Process this file with automake to produce Makefile.in

AM_CPPFLAGS = \
        $(GTKMM_CFLAGS) \
        $(LIBDBUSMM_CFLAGS) \
        -DPROGRAMNAME_LOCALEDIR="${PROGRAMNAME_LOCALEDIR}" \
        -DPACKAGE_LOCALE_DIR="$(prefix)/$(DATADIRNAME)/locale" \
        -DPACKAGE_DATA_DIR="$(datadir)" \
        -DPACKAGE_SRC_DIR="$(srcdir)" 

AM_CFLAGS = \
        $(GTKMM_CFLAGS) \
        $(LIBDBUSMM_CFLAGS) \
         -Wall -fstack-protector-all -rdynamic -ggdb -g

bin_PROGRAMS = linux-kernel-monitor \
	launcher-glkm-daemon

launcher_glkm_daemon_SOURCES = \
	launcher_main.cpp

linux_kernel_monitor_SOURCES = \
	main.cc						\
	linux-kernel-monitor-server-adaptor.hpp		\
	linux-kernel-monitor-server.hpp			\
	linux-kernel-monitor-server.cpp			\
	hal-device-proxy.cpp				\
	hal-device-proxy.hpp				\
	hal-manager-proxy.cpp				\
	hal-manager-proxy.hpp				\
	utils.hpp


linux_kernel_monitor_LDFLAGS = 

linux_kernel_monitor_LDADD = $(GTKMM_LIBS) \
		       $(LIBDBUSMM_LIBS)

linux-kernel-monitor-server-adaptor.hpp: 	../data/introspect-hal-device-linuxkernelmonitor.xml
	dbusmm-xml2cpp $^ --adaptor=$@

linux-kernel-monitor-client-proxy.hpp: 	../data/introspect-hal-device-linuxkernelmonitor.xml
	dbusmm-xml2cpp $^ --proxy=$@

