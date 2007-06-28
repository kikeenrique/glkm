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

#  AC_DEFUN([PACKAGE_NAME], [glkm])
AC_DEFUN([glkm_major_version], [0])
AC_DEFUN([glkm_minor_version], [2])
AC_DEFUN([glkm_micro_version], [3])
AC_DEFUN([glkm_version], [glkm_major_version.glkm_minor_version.glkm_micro_version])

AC_DEFUN([BUG_REPORT_ADDRESS], [http://eldemonionegro.com/glkm/newticket])

AC_INIT([GNOME LINUX Kernel Monitor], [glkm_version], [BUG_REPORT_ADDRESS], [glkm])

AC_CONFIG_AUX_DIR([config-aux])

GTKMM_REQUIRED=2.8 
LIBGLADEMM_REQUIRED=2.6
LIBGNOME_REQUIRED=2.14
AC_SUBST([GTKMM_REQUIRED])
AC_SUBST([LIBGLADEMM_REQUIRED])
AC_SUBST([LIBGNOME_REQUIRED])

################################################################################
#		Checks for programs.
################################################################################

#  DEPRECATED since autoconf 2.50 AM_INIT_AUTOMAKE([AC_PACKAGE_NAME], [AC_PACKAGE_VERSION])
AM_INIT_AUTOMAKE([gnu dist-bzip2 -Wall -Werror])

AC_PROG_CXX
AM_PROG_CC_STDC
# AC_LANG(C++)

AC_PATH_PROG([PKGCONFIG_CONFIG], [pkg-config],[no])
if test x$PKGCONFIG_CONFIG = xno; then
	AC_MSG_ERROR([Please install the pkg-config package from http://www.freedesktop.org/software/pkgconfig/])
fi

#  dnl  Future use maybe?
#  dnl we need gconftool-2 in order to install the schema
#  AC_PATH_PROG(GCONFTOOL, gconftool-2, no)
#
#  if test "x$GCONFTOOL" = "xno"; then
#   AC_MSG_ERROR([gconftool-2 executable not found in your path - should be installed with GConf])
#  fi
#
#  AM_GCONF_SOURCE_2


################################################################################
#		Checks for Internatinalization.
################################################################################
IT_PROG_INTLTOOL([0.35.0])
AM_PO_SUBDIRS

GETTEXT_PACKAGE=[$PACKAGE]
AC_SUBST([GETTEXT_PACKAGE])
AC_DEFINE_UNQUOTED([GETTEXT_PACKAGE], ["$GETTEXT_PACKAGE"], [GETTEXT package name])
AM_GLIB_GNU_GETTEXT

PROGRAMNAME_LOCALEDIR=[${datadir}/locale]
AC_SUBST([PROGRAMNAME_LOCALEDIR])


################################################################################
#		Checks for libraries.
################################################################################

PKG_CHECK_MODULES([GLKM], [gtkmm-2.4 >= $GTKMM_REQUIRED libglademm-2.4 >= $LIBGLADEMM_REQUIRED])
AC_SUBST([GLKM_CFLAGS])
AC_SUBST([GLKM_LIBS])

# Determine whether to compile with support for GNOME libraries (i.e libgnome and libgnomeui)
AC_ARG_ENABLE([gnome],
				    [AC_HELP_STRING([--disable-gnome], [build with libgnome support])], 
				    [enable_gnome=no],
				    [enable_gnome=yes])
 AC_MSG_CHECKING(whether to compile with support for GNOME libraries)
if test "x$enable_gnome" = "xyes"; then
	AC_MSG_RESULT(yes)
	PKG_CHECK_MODULES(LIBGNOME, [libgnome-2.0 >= $LIBGNOME_REQUIRED])
	AC_SUBST([LIBGNOME_CFLAGS])
	AC_SUBST([LIBGNOME_LIBS])
	AC_DEFINE([HAVE_LIBGNOME], [], [Compile with libgnome support])
else
	AC_MSG_RESULT(no)
fi

################################################################################
#		Checks for header files.
################################################################################

AC_HEADER_STDC

################################################################################
#		Checks for typedefs, structures, and compiler characteristics.
################################################################################

AC_CONFIG_HEADERS([config.h])

AM_MAINTAINER_MODE
AM_PROG_LIBTOOL

#  GNOME_COMPILE_WARNINGS(maximum)

# Determine whether to compile with debug settings.  Essentially this just disables compiler optimizations for now.
AC_ARG_ENABLE([debug-mode], 
					[AC_HELP_STRING([--enable-debug-mode], [build with debug settings (no optimization, test coverage)] )], 
					[],
					[AM_CFLAGS="$AM_CFLAGS -DDEBUG" AM_CPPFLAGS="$AM_CPPFLAGS -DDEBUG" enable_debug=no])
AC_MSG_CHECKING(whether to compile with DEBUG settings)
if test "x$enable_debug" = "xyes"; then
	AC_MSG_RESULT(yes)
	# remove optimization settings from CFLAGS
	CXXFLAGS=[`echo "$CXXFLAGS" | $SED -e 's/-O[0-9]*//g'`]
	CFLAGS=[`echo "$CFLAGS" | $SED -e 's/-O[0-9]*//g'`]
	AC_SUBST([AM_CFLAGS])
	AC_SUBST([AM_CXXFLAGS])
else
	AC_MSG_RESULT(no)
fi

################################################################################
#		Checks for library functions.
################################################################################


################################################################################
#		Output files
################################################################################


#dnl Setup Plugin directories
#glkm_data_dir='$(datadir)/glkm'
#glkm_ui_dir='$(datadir)/glkm/ui'
glkm_glade_dir='$(datadir)/glkm/glade'
#glkm_image_dir='$(datadir)/pixmaps/glkm'
#AC_SUBST(glkm_plugin_dir)
#AC_SUBST(glkm_data_dir)
#AC_SUBST(glkm_ui_dir)
AC_SUBST(glkm_glade_dir)
#AC_SUBST(glkm_image_dir)


AC_CONFIG_FILES([
Makefile
data/Makefile
data/glkm.desktop
po/Makefile.in
src/Makefile
])

AC_OUTPUT

################################################################################
#		Developer info
################################################################################

echo ""
echo "======================================================================"
echo ""
echo "<$PACKAGE_NAME> configuration:"
echo " C compiler			: $CC"
echo " C++ compiler			: $CXX"
echo " Prefix				: $prefix"
#echo " AM_CFLAGS		: $AM_CFLAGS"
#echo " AM_CPPFLAGS	: $AM_CPPFLAGS"
echo " CFLAGS				: $CFLAGS"
echo " CPPFLAGS			: $CPPFLAGS"
echo " CXXFLAGS			: $CXXFLAGS"
#echo " AM_CXXFLAGS	: $AM_CXXFLAGS"
echo " CXXCOMPILE			: $CXXCOMPILE"
echo " CXXLINK			: $CXXLINK"
echo ""
echo " DEFS				: $DEFS"
echo " LDFLAGS			: $LDFLAGS"
echo " LIBS				: $LIBS"
echo ""
echo " LIBINTL			: $LIBINTL"
echo ""
echo "<$PACKAGE_NAME> will be compiled with the following features:"
echo "  GNOME library support   : $enable_gnome"
echo "  DEBUG mode   : $enable_debug"
echo ""
echo "The following options will be passed to the compiler:"
echo "  GTKMM_REQUIRED: $GTKMM_REQUIRED"
echo "  LIBGLADEMM_REQUIRED: $LIBGLADEMM_REQUIRED"
echo "  LIBGNOME_REQUIRED: $LIBGNOME_REQUIRED"
echo ""
echo "  GETTEXT_PACKAGE: $GETTEXT_PACKAGE"
echo "  PROGRAMNAME_LOCALEDIR: $PROGRAMNAME_LOCALEDIR"
echo ""
echo "  GLKM_CFLAGS: $GLKM_CFLAGS"
echo "  GLKM_CPPLAGS: $GLKM_CPPLAGS"
echo "  GLKM_LIBS: $GLKM_LIBS"
echo ""
echo "  HAVE_LIBGNOME: $HAVE_LIBGNOME"
echo "  LIBGNOME_CFLAGS: $LIBGNOME_CFLAGS"
echo "  LIBGNOME_LIBS: $LIBGNOME_LIBS"
echo ""
echo ""
echo "======================================================================"
echo ""

