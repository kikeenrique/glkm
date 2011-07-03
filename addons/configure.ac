################################################################################
#               Prelude.
################################################################################
AC_PREREQ(2.65)

AC_INIT([linux-kernel-monitor],[0.3],[http://eldemonionegro.com/glkm/newticket],[linux-kernel-monitor])

AC_CONFIG_AUX_DIR([config-aux])
AC_CONFIG_MACRO_DIR([config-aux/m4])

GTKMM_REQUIRED=2.12
LIBDBUSMM_REQUIRED=0.5.0
AC_SUBST([GTKMM_REQUIRED])
AC_SUBST([LIBDBUSMM_REQUIRED])

################################################################################
#               Checks for programs.
################################################################################

AM_INIT_AUTOMAKE([gnu dist-bzip2 -Wall -Werror])

AC_SEARCH_LIBS([strerror],[cposix])
AC_PROG_CXX
AC_PROG_CC
AC_DIAGNOSE([obsolete],[AM_PROG_CC_STDC:
	your code should no longer depend upon `am_cv_prog_cc_stdc', but upon
	`ac_cv_prog_cc_stdc'.  Remove this warning and the assignment when
	you adjust the code.  You can also remove the above call to
	AC_PROG_CC if you already called it elsewhere.])
am_cv_prog_cc_stdc=$ac_cv_prog_cc_stdc

AC_HEADER_STDC

AC_PATH_PROG([PKGCONFIG_CONFIG], [pkg-config],[no])
if test x$PKGCONFIG_CONFIG = xno; then
        AC_MSG_ERROR([Please install the pkg-config package from \ 
                      http://www.freedesktop.org/software/pkgconfig/])
fi


################################################################################
#               Checks for Internationalization.
################################################################################
IT_PROG_INTLTOOL([0.35.0])
AM_PO_SUBDIRS

GETTEXT_PACKAGE=[$PACKAGE]
AC_SUBST(GETTEXT_PACKAGE)
AC_DEFINE_UNQUOTED(GETTEXT_PACKAGE,["$GETTEXT_PACKAGE"], [GETTEXT package name])
AM_GLIB_GNU_GETTEXT

PROGRAMNAME_LOCALEDIR=[${datadir}/locale]
AC_SUBST([PROGRAMNAME_LOCALEDIR])

################################################################################
#               Checks for libraries.
################################################################################
# gtkmm
# libglademm
PKG_CHECK_MODULES([GTKMM], [gtkmm-2.4 >= $GTKMM_REQUIRED])
AC_SUBST([GTKMM_CFLAGS])
AC_SUBST([GTKMM_LIBS])

# libdbusmm
PKG_CHECK_MODULES([LIBDBUSMM], [dbusmm-1.0 >= $LIBDBUSMM_REQUIRED])
AC_SUBST([LIBDBUSMM_CFLAGS])
AC_SUBST([LIBDBUSMM_LIBS])

################################################################################
#               Checks for header files.
################################################################################

AC_HEADER_STDC

################################################################################
#               Checks for typedefs, structures, and compiler characteristics.
################################################################################

AC_CONFIG_HEADERS([config.h])

AM_MAINTAINER_MODE
LT_INIT

################################################################################
#               Checks for library functions.
################################################################################


################################################################################
#               Output files
################################################################################

AC_CONFIG_FILES([
Makefile
data/Makefile
po/Makefile.in
src/Makefile
])

AC_OUTPUT
