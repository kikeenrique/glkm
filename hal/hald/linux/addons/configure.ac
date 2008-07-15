dnl Process this file with autoconf to produce a configure script.
dnl Created by Anjuta application wizard.

AC_INIT(hald-addon-linux-kernel-monitor, 0.3, eldemonionegro.com/glkm)

AM_INIT_AUTOMAKE(AC_PACKAGE_NAME, AC_PACKAGE_VERSION)
AC_CONFIG_HEADERS([config.h])
AM_MAINTAINER_MODE

AC_ISC_POSIX
AC_PROG_CXX
AM_PROG_CC_STDC
AC_HEADER_STDC




dnl ***************************************************************************
dnl Internatinalization
dnl ***************************************************************************
GETTEXT_PACKAGE=hald-addon-linux-kernel-monitor
AC_SUBST(GETTEXT_PACKAGE)
AC_DEFINE_UNQUOTED(GETTEXT_PACKAGE,"$GETTEXT_PACKAGE", [GETTEXT package name])
AM_GLIB_GNU_GETTEXT
IT_PROG_INTLTOOL([0.35.0])



AM_PROG_LIBTOOL



PKG_CHECK_MODULES(HALD_ADDON_LINUX_KERNEL_MONITOR, [dbusmm-1.0 glibmm-2.4 giomm-2.4])
AC_SUBST(HALD_ADDON_LINUX_KERNEL_MONITOR_CFLAGS)
AC_SUBST(HALD_ADDON_LINUX_KERNEL_MONITOR_LIBS)




AC_OUTPUT([
Makefile
src/Makefile
po/Makefile.in
data/Makefile
])
