dnl
dnl	configure.ac
dnl
dnl	Copyright (C) Enrique García Álvarez 2007-2011 <kike + glkm @ eldemonionegro.com>
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
dnl	along with configure.ac.  If not, write to:
dnl		The Free Software Foundation, Inc.,
dnl		51 Franklin Street, Fifth Floor
dnl		Boston, MA  02110-1301, USA.
dnl


dnl Process this file with autoconf to produce a configure script.
################################################################################
#		Prelude.
################################################################################
AC_PREREQ([2.67])

m4_define([glkmd_major_version],[0])
m4_define([glkmd_minor_version],[1])
m4_define([glkmd_micro_version],[0])
m4_define([glkmd_version],[glkmd_major_version.glkmd_minor_version.glkmd_micro_version])

AC_INIT([GNOME LINUX Kernel Monitor Daemon],[m4_defn([glkmd_version])],[http://eldemonionegro.com/glkm/newticket],[glkmd])
m4_ifdef([AM_SILENT_RULES],[AM_SILENT_RULES([yes])])

AC_CONFIG_AUX_DIR([config-aux])
AC_CONFIG_MACRO_DIR([config-aux])

OMNIORB_REQUIRED=4.1.3
AC_SUBST([OMNIORB_REQUIRED])

LIBNETLINK_REQUIRED=3.0
AC_SUBST([LIBNETLINK_REQUIRED])

GOOGLETEST_REQUIRED=1.5.0
AC_SUBST([GOOGLETEST_REQUIRED])

################################################################################
#		Checks for programs.
################################################################################
AM_INIT_AUTOMAKE(AC_PACKAGE_NAME, AC_PACKAGE_VERSION)

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


################################################################################
#		Checks for Internationalization.
################################################################################
IT_PROG_INTLTOOL([0.35.0])
AM_PO_SUBDIRS

GETTEXT_PACKAGE=glkm_daemon
AC_SUBST(GETTEXT_PACKAGE)
AC_DEFINE_UNQUOTED(GETTEXT_PACKAGE,"$GETTEXT_PACKAGE", [GETTEXT package name])
AM_GLIB_GNU_GETTEXT

PROGRAMNAME_LOCALEDIR=[${datadir}/locale]
AC_SUBST([PROGRAMNAME_LOCALEDIR])

################################################################################
#		Checks for libraries.
################################################################################
AC_SEARCH_LIBS([strerror],[cposix])

PKG_CHECK_MODULES([GLKM_DAEMON], [omniORB4 omniConnectionMgmt4 omniDynamic4 libnl-3.0])
AC_SUBST([GLKM_DAEMON_CFLAGS])
AC_SUBST([GLKM_DAEMON_LIBS])

#PKG_CHECK_MODULES([LIBNETLINK], [libnl-2.0])
#AC_SUBST([LIBNETLINK_CFLAGS])
#AC_SUBST([LIBNETLINK_LIBS])


m4_include(tmp/gtest.m4)
#GTEST_LIB_CHECK([$GOOGLETEST_REQUIRED], AC_MSG_WARN([YAY]), AC_MSG_WARN([NON])
#GTEST_LIB_CHECK([1.5.0])

################################################################################
#		Checks for header files.
################################################################################
AC_HEADER_STDC


################################################################################
#		Checks for typedefs, structures, and compiler characteristics.
################################################################################
AC_CONFIG_HEADERS([config.h])
#Disable maintainer mode, see http://www.gnu.org/software/hello/manual/automake/maintainer_002dmode.html
#AM_MAINTAINER_MODE
LT_PREREQ([2.2.6])
LT_INIT()

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
test/Makefile
])

AC_OUTPUT

################################################################################
#		Developer info
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
echo ""
echo " DEFS             : $DEFS"
echo ""
echo " LIBINTL          : $LIBINTL"
echo ""
echo "<$PACKAGE_NAME> will be compiled with the following features:"
echo "  DEBUG mode   : $enable_debug"
echo ""
echo "Required version libraries:"
echo "  OMNIORB    : $OMNIORB_REQUIRED"
echo "  LIBNETLINK : $LIBNETLINK_REQUIRED"
echo "	GOOGLETEST : $GOOGLETEST_REQUIRED"
echo ""
echo "The following options will be passed to the compiler:"
echo "	GLKM_DAEMON_CFLGAGS : $GLKM_DAEMON_CFLAGS"
echo "	GLKM_DAEMON_CXXFLAGS: $GLKM_DAEMON_LIBS"
echo "	GOOGLETEST_CPPFLAGS : $GTEST_CPPFLAGS"
echo "	GOOGLETEST_CXXFLAGS : $GTEST_CXXFLAGS"
echo "	GOOGLETEST_LDFLAGS  : $GTEST_LDFLAGS"
echo "	GOOGLETEST_LIBS     : $GTEST_LIBS"
echo ""
echo "  GETTEXT_PACKAGE: $GETTEXT_PACKAGE"
echo "  PROGRAMNAME_LOCALEDIR: $PROGRAMNAME_LOCALEDIR"
echo ""
echo ""
echo "======================================================================"
echo ""
