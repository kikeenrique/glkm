## Process this file with automake to produce Makefile.in

## Created by Anjuta

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" $(HALD_ADDON_LINUX_KERNEL_MONITOR_CFLAGS)

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = hald-addon-linux-kernel-monitor

hald_addon_linux_kernel_monitor_SOURCES = \
	main.cc						\
	linux-kernel-monitor-server-adaptor.hpp		\
	linux-kernel-monitor-server.hpp			\
	linux-kernel-monitor-server.cpp			\
	hal-device-proxy.cpp				\
	hal-device-proxy.hpp				\
	hal-manager-proxy.cpp				\
	hal-manager-proxy.hpp				\
	utils.hpp


hald_addon_linux_kernel_monitor_LDFLAGS = 

hald_addon_linux_kernel_monitor_LDADD = $(HALD_ADDON_LINUX_KERNEL_MONITOR_LIBS)

linux-kernel-monitor-server-adaptor.hpp: 	../data/introspect-hal-device-linuxkernelmonitor.xml
	dbusmm-xml2cpp $^ --adaptor=$@

linux-kernel-monitor-client-proxy.hpp: 	../data/introspect-hal-device-linuxkernelmonitor.xml
	dbusmm-xml2cpp $^ --proxy=$@

