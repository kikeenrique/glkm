dnl
dnl    configure.ac
dnl
dnl    Copyright (C) Enrique García Álvarez 2007-2011 <kike + glkm @ eldemonionegro.com>
dnl
dnl    configure.ac is free software
dnl
dnl    You may redistribute it and/or modify it under the terms of the
dnl    GNU General Public License, as published by the Free Software
dnl    Foundation; either version 2 of the License, or (at your option)
dnl    any later version.
dnl
dnl    configure.ac is distributed in the hope that it will be useful,
dnl    but WITHOUT ANY WARRANTY; without even the implied warranty of
dnl    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
dnl    See the GNU General Public License for more details.
dnl
dnl    You should have received a copy of the GNU General Public License
dnl    along with configure.ac.  If not, write to:
dnl        The Free Software Foundation, Inc.,
dnl        51 Franklin Street, Fifth Floor
dnl        Boston, MA  02110-1301, USA.
dnl


dnl Process this file with autoconf to produce a configure script.
################################################################################
#        Prelude.
################################################################################
AC_PREREQ([2.68])

m4_define([glkm_major_version],[0])
m4_define([glkm_minor_version],[2])
m4_define([glkm_micro_version],[3])
m4_define([glkm_version],[glkm_major_version.glkm_minor_version.glkm_micro_version])

AC_INIT([GNOME LINUX Kernel Monitor],[m4_defn([glkm_version])],[http://eldemonionegro.com/glkm/newticket],[glkm])
m4_ifdef([AM_SILENT_RULES],[AM_SILENT_RULES([yes])])

AC_CONFIG_AUX_DIR([config-aux])
AC_CONFIG_MACRO_DIR([config-aux])

GTKMM_REQUIRED=3.4
#LIBGLADEMM_REQUIRED=2.6
LIBGNOME_REQUIRED=2.20
LIBDBUSMM_REQUIRED=0.5.0
LIBSIGCMM_REQUIRED=2.2.9
GIOMM_REQUIRED=2.22.1
AC_SUBST([GTKMM_REQUIRED])
#AC_SUBST([LIBGLADEMM_REQUIRED])
AC_SUBST([LIBGNOME_REQUIRED])
AC_SUBST([LIBDBUSMM_REQUIRED])
AC_SUBST([GIOMM_REQUIRED])

################################################################################
#        Checks for programs.
################################################################################
#AM_INIT_AUTOMAKE(AC_PACKAGE_NAME, AC_PACKAGE_VERSION)
AM_INIT_AUTOMAKE

# Read ahead about OLD_CXXFLAGS, it also applies here
OLD_CFLAGS=$CFLAGS
AC_PROG_CPP
AC_PROG_CC
CFLAGS=$OLD_CFLAGS

#AM_PROG_CC_C_O
AC_PROG_CC_STDC

# store current user given compiler flags to avoid default setup via AC_PROG_CXX
# Unfortunately, it is not only checking if the user has set the variable to
# provide additional compiler information. In case the variable is specified,
# nothing happens to it. But if not present, the check sets the variable
# automatically to '-g -O2'
# see http://www.gnu.org/savannah-checkouts/gnu/autoconf/manual/autoconf-2.63/
#  html_node/C_002b_002b-Compiler.html#index-AC_005fPROG_005fCXX-808
OLD_CXXFLAGS=$CXXFLAGS
# check for C++ preprocessor and compiler and the library compiler
# (might change the compiler flags)
AC_PROG_CXXCPP
AC_PROG_CXX
# reset compiler flags to initial flags
CXXFLAGS=$OLD_CXXFLAGS

AC_LANG([C++])

AC_PATH_PROG([PKGCONFIG_CONFIG], [pkg-config],[no])
if test x$PKGCONFIG_CONFIG = xno; then
    AC_MSG_ERROR([Please install the pkg-config package from \
                  http://www.freedesktop.org/software/pkgconfig/])
fi

# TODO - Future use maybe?
#  dnl we need gconftool-2 in order to install the schema
#  AC_PATH_PROG(GCONFTOOL, gconftool-2, no)
#
#  if test "x$GCONFTOOL" = "xno"; then
#   AC_MSG_ERROR([gconftool-2 executable not found in your path \
#                 - should be installed with GConf])
#  fi
#
#  AM_GCONF_SOURCE_2

################################################################################
#        Checks for Internationalization.
################################################################################
IT_PROG_INTLTOOL([0.40.0])
AM_PO_SUBDIRS

GETTEXT_PACKAGE=[$PACKAGE]
AC_SUBST([GETTEXT_PACKAGE])
AC_DEFINE_UNQUOTED([GETTEXT_PACKAGE], ["$GETTEXT_PACKAGE"], [GETTEXT package name])
AM_GLIB_GNU_GETTEXT

PROGRAMNAME_LOCALEDIR=[${datadir}/locale]
AC_SUBST([PROGRAMNAME_LOCALEDIR])

################################################################################
#        Checks for libraries.
################################################################################

# gtkmm
# libglademm
PKG_CHECK_MODULES([GLKM], [gtkmm-3.0 >= $GTKMM_REQUIRED])
AC_SUBST([GLKM_CFLAGS])
AC_SUBST([GLKM_LIBS])

# dbusmm
PKG_CHECK_MODULES([LIBDBUSMM], [dbusmm-1.0 >= $LIBDBUSMM_REQUIRED])
AC_SUBST([LIBDBUSMM_CFLAGS])
AC_SUBST([LIBDBUSMM_LIBS])

#giomm and glibmm
PKG_CHECK_MODULES([GIOMM], [giomm-2.4 >= $GIOMM_REQUIRED])
AC_SUBST([GIOMM_CFLAGS])
AC_SUBST([GIOMM_LIBS])

# libsigcmm
PKG_CHECK_MODULES([LIBSIGCMM], [sigc++-2.0 >= $LIBSIGCMM_REQUIRED])
AC_SUBST([LIBSIGCMM_CFLAGS])
AC_SUBST([LIBSIGCMM_LIBS])

# Determine whether to compile or not with support for GNOME libraries
#(i.e libgnome and libgnomeui)
AC_ARG_ENABLE([gnome],
        [AS_HELP_STRING([--disable-gnome],[build with GNOME support (default=disabled)])],
        [enable_gnome=yes],
        [enable_gnome=no])
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
#        Checks for header files.
################################################################################
AC_HEADER_STDC
AC_HEADER_STDBOOL
AC_CHECK_HEADERS([libintl.h])

################################################################################
#        Checks for typedefs, structures, and compiler characteristics.
################################################################################
AC_CONFIG_HEADERS([config.h])
#Disable maintainer mode, see http://www.gnu.org/software/hello/manual/automake/maintainer_002dmode.html
#or http://blogs.gnome.org/desrt/2011/09/08/am_maintainer_mode-is-not-cool/
#AM_MAINTAINER_MODE
LT_PREREQ([2.2.6])
LT_INIT()

# GNOME_COMPILE_WARNINGS(maximum)

# Determine whether to compile or not with debug settings.
# Essentially this just disables compiler optimizations.
AC_ARG_ENABLE([debug-mode],
              [AS_HELP_STRING([--enable-debug-mode],[build with debug settings (no optimization, test coverage) ])],
              [enable_debug=yes],
              [enable_debug=no])
AC_MSG_CHECKING(whether to compile or not with DEBUG settings)

if test "x$enable_debug" = "xyes"; then
        AC_MSG_RESULT(yes)

        # remove optimization settings from CFLAGS
        AM_CFLAGS="[`echo "$AM_CFLAGS" | $SED -e 's/-O[0-9]*//g'`]"
        AM_CXXFLAGS="[`echo "$AM_CXXFLAGS" | $SED -e 's/-O[0-9]*//g'`]"

        #Add our compilation settings
        AM_CPPFLAGS="$AM_CPPFLAGS -DDEBUG"
        AM_CXXFLAGS="$AM_CXXFLAGS -rdynamic -ggdb -g -O0"
        AM_CXXFLAGS="$AM_CXXFLAGS -Wall -Wno-uninitialized -fstack-protector-all"

        AC_SUBST([AM_CFLAGS])
        AC_SUBST([AM_CXXFLAGS])
        AC_DEFINE([DEBUG],
                [],
                [build with debug settings (no optimization, test coverage)])
else
        AC_MSG_RESULT(no)

        AM_CXXFLAGS="$AM_CXXFLAGS -Wall -Wno-uninitialized -fstack-protector-all -O2"
        AC_SUBST([AM_CXXFLAGS])
fi


# Determine whether to compile or not with GNOME 3 compilation warnings.
# This introduces some compatibility flags.
AC_ARG_ENABLE([gnome3-compat-mode],
              [AS_HELP_STRING([--enable-gnome3-compat-mode],[build with gnome3 warnings ])],
              [AM_CFLAGS="$AM_CFLAGS -DG_DISABLE_DEPRECATED -DG_DISABLE_SINGLE_INCLUDES -DGDK_DISABLE_DEPRECATED -DGTK_DISABLE_DEPRECATED -DGDK_DISABLE_SINGLE_INCLUDES -DGTK_DISABLE_SINGLE_INCLUDES"
               AM_CXXFLAGS="$AM_CXXFLAGS -DG_DISABLE_DEPRECATED -DG_DISABLE_SINGLE_INCLUDES -DGDK_DISABLE_DEPRECATED -DGTK_DISABLE_DEPRECATED -DGDK_DISABLE_SINGLE_INCLUDES -DGTK_DISABLE_SINGLE_INCLUDES"
               enable_gnome3_compat=yes],
              [enable_gnome3_compat=no])
AC_MSG_CHECKING(whether to compile or not with GNOME3 settings)
if test "x$enable_gnome3_compat" = "xyes"; then
        AC_MSG_RESULT(yes)
        AC_SUBST([AM_CFLAGS])
        AC_SUBST([AM_CXXFLAGS])
        AC_DEFINE([GNOME3_COMPAT_MODE],
                [],
                [build with gnome3 warnings])
else
        AC_MSG_RESULT(no)
fi

AC_ARG_ENABLE(gcov,
              [AS_HELP_STRING([--enable-gcov],[turn on code coverage analysis tools])],
              [enable_gcov=yes],
              [enable_gcov=no])
AC_MSG_CHECKING(whether to compile or not with code coverage settings)

# Check for --enable-gcov and add appropriate flags for gcc
# Note that these extra switches are NOT applied to the loader
if test "x$enable_gcov" = "xyes"; then
        AC_MSG_RESULT(yes)
        # Turn off optimization so code coverage tool
        # can get accurate line numbers
        AM_CFLAGS="[`echo "$AM_CFLAGS" | $SED -e 's/-O[0-9]*//g'`]"
        AM_CXXFLAGS="[`echo "$AM_CXXFLAGS" | $SED -e 's/-O[0-9]*//g'`]"

        #Add our compilation settings
        AM_CPPFLAGS="$AM_CPPFLAGS -DGCOV"
        AM_CXXFLAGS="$AM_CXXFLAGS -fprofile-arcs -ftest-coverage"

        AC_SUBST([AM_CFLAGS])
        AC_SUBST([AM_CXXFLAGS])
        AC_DEFINE([GCOV],
                  [],
                  [build with gcov settings (test coverage)])
else
        AC_MSG_RESULT(no)
        AC_SUBST([AM_CXXFLAGS])
fi

AC_TYPE_SIZE_T
AC_FUNC_MALLOC
AC_FUNC_REALLOC

################################################################################
#        Checks for library functions.
################################################################################
AC_C_INLINE

AC_CHECK_FUNCS([memset])
AC_CHECK_FUNCS([setenv])

################################################################################
#        Output files
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
#        Developer info
################################################################################
echo ""
echo "======================================================================"
echo ""
echo "<$PACKAGE_NAME> configuration:"
echo " C compiler       : $CC"
echo " Prefix           : $prefix"
echo " AM_CPPFLAGS      : $AM_CPPFLAGS"
echo " CPPFLAGS         : $CPPFLAGS"
echo " CXXCPP           : $CXXCPP"
echo " AM_CFLAGS        : $AM_CFLAGS"
echo " OLD_CFLAGS       : $OLD_CFLAGS"
echo " CFLAGS           : $CFLAGS"
echo " C++ compiler     : $CXX"
echo " AM_CXXFLAGS      : $AM_CXXFLAGS"
echo " CXXFLAGS         : $CXXFLAGS"
echo " CXXCOMPILE       : $CXXCOMPILE"
echo " CXXLINK          : $CXXLINK"
echo " LDFLAGS          : $LDFLAGS"
echo " LIBS             : $LIBS"
echo " LIBS             : $GCOV"
echo ""
echo " DEFS             : $DEFS"
echo ""
echo " LIBINTL          : $LIBINTL"
echo ""
echo "<$PACKAGE_NAME> will be compiled with the following features:"
echo "  GNOME library support       : $enable_gnome"
echo "  DEBUG mode                  : $enable_debug"
echo "  GNOME3 compatiblity mode    : $enable_gnome3_compat"
echo "  GCOV code coverage          : $enable_gcov"
echo ""
echo "The following options will be passed to the compiler:"
echo "  GTKMM_REQUIRED: $GTKMM_REQUIRED"
#echo "  LIBGLADEMM_REQUIRED: $LIBGLADEMM_REQUIRED"
echo "  LIBDBUSMM_REQUIRED: $LIBDBUSMM_REQUIRED"
echo "  LIBGNOME_REQUIRED: $LIBGNOME_REQUIRED"
echo "  GIOMM_REQUIRED: $GIOMM_REQUIRED"
echo ""
echo "  GETTEXT_PACKAGE: $GETTEXT_PACKAGE"
echo "  PROGRAMNAME_LOCALEDIR: $PROGRAMNAME_LOCALEDIR"
echo ""
echo "  GLKM_CFLAGS: $GLKM_CFLAGS"
echo "  GLKM_LIBS: $GLKM_LIBS"
echo ""
echo "  LIBDBUSMM_CFLAGS: $LIBDBUSMM_CFLAGS"
echo "  LIBDBUSMM_LIBS: $LIBDBUSMM_LIBS"
echo ""
echo "  LIBSIGCMM_CFLAGS: $LIBSIGCMM_CFLAGS"
echo "  LIBSIGCMM_LIBS: $LIBSIGCMM_LIBS"
echo ""
echo "  GIOMM_CFLAGS: $GIOMM_CFLAGS"
echo "  GIOMM_LIBS: $GIOMM_LIBS"
echo ""
echo "  HAVE_LIBGNOME: $HAVE_LIBGNOME"
echo "  LIBGNOME_CFLAGS: $LIBGNOME_CFLAGS"
echo "  LIBGNOME_LIBS: $LIBGNOME_LIBS"
echo ""
echo "======================================================================"
echo ""
