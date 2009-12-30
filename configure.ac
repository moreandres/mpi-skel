#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_INIT([mpi-skel], [0.1], [more.andres@gmail.com])

AC_CONFIG_SRCDIR([lib/mpiskel.c])
AC_CONFIG_HEADERS([inc/config.h])

AM_INIT_AUTOMAKE

# Checks for programs.
AC_PROG_CC
AC_PROG_CXX
AC_PROG_LIBTOOL
AC_PROG_RANLIB

# Checks for libraries.

# Checks for header files.
AC_HEADER_TIME
AC_CHECK_HEADERS([fcntl.h] [sys/time.h] [syslog.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST

# Checks for library functions.
AC_FUNC_STRFTIME
AC_FUNC_MALLOC
AC_CHECK_FUNCS([gettimeofday] [strtol])

# Extra arguments
AC_ARG_ENABLE(debug,
              AC_HELP_STRING([--enable-debug], [Turn on debugging]),
	      AC_DEFINE([DEBUG], [1], [Turn on debugging]))

# Makefiles
AC_CONFIG_FILES([Makefile
                 lib/Makefile
                 inc/Makefile
                 src/Makefile
                 doc/Makefile
                 t/Makefile])

AC_OUTPUT
