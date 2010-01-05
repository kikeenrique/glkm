## Process this file with automake to produce Makefile.in

SUBDIRS = src \
	po \
	data

linux_kernel_monitordocdir = ${prefix}/doc/linux_kernel_monitor
linux_kernel_monitordoc_DATA = \
	README\
	COPYING\
	AUTHORS\
	ChangeLog\
	INSTALL\
	NEWS

EXTRA_DIST = $(linux_kernel_monitordoc_DATA) 

# Copy all the spec files. Of cource, only one is actually used.
dist-hook:
	for specfile in *.spec; do \
		if test -f $$specfile; then \
			cp -p $$specfile $(distdir); \
		fi \
	done

