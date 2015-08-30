#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])
AC_INIT([ipap], [0.1], [la.marentes455@uniandes.edu.co])
AM_INIT_AUTOMAKE([subdir-objects])
AM_PATH_CPPUNIT(1.9.6)
LT_INIT
AC_CONFIG_SRCDIR([src/main.cpp])
AC_CONFIG_MACRO_DIR([m4])


## ------------------------Begin instantiation part 
## Meaning:
## An instantiating macro is one which defines one or more tags, 
## usually referring to files that are to be translated by the generated 
## configure scripts, from a template containing Autoconf substitution 
## variables.


AM_MAINTAINER_MODE

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_AWK
AC_PROG_INSTALL

AC_LANG_CPLUSPLUS

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL

# Checks for library functions.

# Checks for libraries.
#
# os check
#

AC_LANG(C++)

AC_ARG_ENABLE(debug,
  [  --enable-debug            enable debug build ],
  [case "${enableval}" in
    yes) debug=true ;;
    no)  debug=false ;;
    *) AC_MSG_ERROR(bad value ${enableval} for --enable-debug) ;;
  esac],[debug=false])
AM_CONDITIONAL(ENABLE_DEBUG, test x$debug = xtrue)
if test $debug = true ; then
  AC_DEFINE(ENABLE_DEBUG, 1, [enable debug build])
fi


sysconfdir="/home/luis/IPAP_Protocol/etc"

#DEF_SYSCONFDIR=`eval echo ${sysconfdir}`
DEF_SYSCONFDIR="/home/luis/IPAP_Protocol/etc"
AC_DEFINE_UNQUOTED(DEF_SYSCONFDIR, "$DEF_SYSCONFDIR", "sysconfig dir")

DEF_STATEDIR=`eval echo ${localstatedir}`
AC_DEFINE_UNQUOTED(DEF_STATEDIR, "$DEF_STATEDIR", "state dir")

libdir="${libdir}/$PACKAGE"
if test "${exec_prefix}" = "NONE" ; then
  exec_prefix=${prefix}
fi
DEF_LIBDIR=`eval echo ${libdir}`
AC_DEFINE_UNQUOTED(DEF_LIBDIR, "$DEF_LIBDIR", "lib dir")

DEF_BINDIR=`eval echo ${bindir}`
AC_DEFINE_UNQUOTED(DEF_BINDIR, "$DEF_BINDIR", "bin dir")


AC_CONFIG_FILES([Makefile
                 src/Makefile
                 test/Makefile])

AC_OUTPUT
