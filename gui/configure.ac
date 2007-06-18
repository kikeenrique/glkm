dnl   
dnl	configure.ac
dnl   
dnl	Copyright (C) Enrique García Álvarez 2007 <kike @ eldemonionegro.com>
dnl
dnl	configure.ac is free software
dnl   
dnl	You may redistribute it and/or modify it under the terms of the
dnl	GNU General Public License, as published by the Free Software
dnl	Foundation; either version 2 of the License, or (at your option)
dnl	any later version.
dnl
dnl	configure.ac is distributed in the hope that it will be useful,
dnl	but WITHOUT ANY WARRANTY; without even the implied warranty of
dnl	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
dnl	See the GNU General Public License for more details.
dnl
dnl	You should have received a copy of the GNU General Public License
dnl	along with main.cc.  If not, write to:
dnl		The Free Software Foundation, Inc.,
dnl		51 Franklin Street, Fifth Floor
dnl		Boston, MA  02110-1301, USA.
dnl   


dnl Process this file with autoconf to produce a configure script.
################################################################################
#		Prelude.
################################################################################

AC_PREREQ([2.61])

BUG_REPORT_ADDRESS=http://eldemonionegro.com/glkm/newticket
AC_SUBST(BUG_REPORT_ADDRESS)

AC_DEFUN([glkm_major_version], [0])
AC_DEFUN([glkm_minor_version], [2])
AC_DEFUN([glkm_micro_version], [3])
AC_DEFUN([glkm_version], [glkm_major_version.glkm_minor_version.glkm_micro_version])


AC_INIT([glkm], [glkm_version], [BUG_REPORT_ADDRESS])

AC_CONFIG_AUX_DIR([config-aux])

GTKMM_REQUIRED=2.8 
LIBGLADEMM_REQUIRED=2.6
AC_SUBST(GTKMM_REQUIRED)
AC_SUBST(LIBGLADEMM_REQUIRED)

################################################################################
#		Checks for programs.
################################################################################

AM_INIT_AUTOMAKE(AC_PACKAGE_NAME, AC_PACKAGE_VERSION)
AM_INIT_AUTOMAKE([-Wall -Werror])

# Unknown effects #AC_ISC_POSIX

AC_PROG_CXX
AM_PROG_CC_STDC

AC_PATH_PROG(PKGCONFIG_CONFIG, pkg-config,no)
if test x$PKGCONFIG_CONFIG = xno; then
  AC_MSG_ERROR(Please install the pkg-config package from http://www.freedesktop.org/software/pkgconfig/)
fi

#dnl  Future use maybe?
#dnl we need gconftool-2 in order to install the schema
#AC_PATH_PROG(GCONFTOOL, gconftool-2, no)
#
#if test "x$GCONFTOOL" = "xno"; then
# AC_MSG_ERROR([gconftool-2 executable not found in your path - should be installed with GConf])
#fi
#
#AM_GCONF_SOURCE_2

dnl ***************************************************************************
dnl Internatinalization

IT_PROG_INTLTOOL([0.35.0])
AM_PO_SUBDIRS

GETTEXT_PACKAGE=glkm
AC_SUBST([GETTEXT_PACKAGE])
AC_DEFINE_UNQUOTED([GETTEXT_PACKAGE], ["$GETTEXT_PACKAGE"], [GETTEXT package name])
AM_GLIB_GNU_GETTEXT

PROGRAMNAME_LOCALEDIR=[${datadir}/locale]
AC_SUBST([PROGRAMNAME_LOCALEDIR])

################################################################################
#		Checks for libraries.
################################################################################

PKG_CHECK_MODULES(GLKM, [gtkmm-2.4 >= $GTKMM_REQUIRED libglademm-2.4 >= $LIBGLADEMM_REQUIRED])
AC_SUBST(GLKM_CFLAGS)
AC_SUBST(GLKM_LIBS)


################################################################################
#		Checks for header files.
################################################################################

AC_HEADER_STDC

################################################################################
#		Checks for typedefs, structures, and compiler characteristics.
################################################################################

AM_CONFIG_HEADER([config.h])
AM_MAINTAINER_MODE
AM_PROG_LIBTOOL

#GNOME_COMPILE_WARNINGS(maximum)

dnl Enable debugging mode
AC_ARG_ENABLE(debug,
  [  --enable-debug           Enable debug messages],
  AM_CFLAGS="$AM_CFLAGS -DDEBUG"
  AM_CXXFLAGS="$AM_CXXFLAGS -DDEBUG")
AC_SUBST(AM_CFLAGS)
AC_SUBST(AM_CXXFLAGS)

#dnl Setup Plugin directories
#glkm_plugin_dir='$(libdir)/glkm'
#glkm_data_dir='$(datadir)/glkm'
#glkm_ui_dir='$(datadir)/glkm/ui'
#glkm_glade_dir='$(datadir)/glkm/glade'
#glkm_image_dir='$(datadir)/pixmaps/glkm'
#AC_SUBST(glkm_plugin_dir)
#AC_SUBST(glkm_data_dir)
#AC_SUBST(glkm_ui_dir)
#AC_SUBST(glkm_glade_dir)
#AC_SUBST(glkm_image_dir)

################################################################################
#		Checks for library functions.
################################################################################


################################################################################
#		Output files
################################################################################

AC_CONFIG_FILES([
Makefile
src/Makefile
po/Makefile.in
glkm.desktop
])

AC_OUTPUT


