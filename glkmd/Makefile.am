## Process this file with automake to produce Makefile.in
## Created by Anjuta

SUBDIRS = src po

glkm_daemondocdir = ${prefix}/doc/glkm_daemon
glkm_daemondoc_DATA = \
	README\
	COPYING\
	AUTHORS\
	ChangeLog\
	INSTALL\
	NEWS


INTLTOOL_FILES = intltool-extract.in \
	intltool-merge.in \
	intltool-update.in

EXTRA_DIST = $(glkm_daemondoc_DATA) \
	$(INTLTOOL_FILES)

DISTCLEANFILES = intltool-extract \
	intltool-merge \
	intltool-update \
	po/.intltool-merge-cache


# Remove doc directory on uninstall
uninstall-local:
	-rm -r $(glkm_daemondocdir)
