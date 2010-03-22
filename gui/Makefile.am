## Process this file with automake to produce Makefile.in

SUBDIRS = src po data

glkmdocdir = ${prefix}/doc/glkm
glkmdoc_DATA = \
	README \
	COPYING \
	AUTHORS \
	ChangeLog \
	INSTALL \
	NEWS \
	TODO.tasks

INTLTOOL_FILES = \
	intltool-extract.in \
	intltool-merge.in \
	intltool-update.in

EXTRA_DIST = \
	autogen.sh \
	$(INTLTOOL_FILES)

ACLOCAL_AMFLAGS = -I config-aux

DISTCHECK_CONFIGURE_FLAGS =

# Copy all the spec files. Of cource, only one is actually used.
#dist-hook:
#	for specfile in *.spec; do \
#		if test -f $$specfile; then \
#			cp -p $$specfile $(distdir); \
#		fi \
#	done


DISTCLEANFILES =  \
	intltool-extract \
	intltool-merge \
	intltool-update \
	po/.intltool-merge-cache
