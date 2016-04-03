#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])
AC_INIT([ipap], [0.1], [la.marentes455@uniandes.edu.co])
AM_INIT_AUTOMAKE([subdir-objects])
AM_PATH_CPPUNIT(1.9.6)
LT_INIT
AC_CONFIG_SRCDIR([src/IpAp_message.cpp])
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

AC_ARG_ENABLE(threads,
  [  --enable-threads            enable threads ],
  [case "${enableval}" in
    yes) threads=true ;;
    no)  threads=false ;;
    *) AC_MSG_ERROR(bad value ${enableval} for --enable-threads) ;;
  esac],[threads=false])
AM_CONDITIONAL(ENABLE_THREADS, test x$threads = xtrue)
if test $threads = true ; then
  AC_DEFINE(ENABLE_THREADS, 1, [enable multi threading])
fi


# check for headers

AC_CHECK_HEADERS([float.h types.h limits.h stdlib.h string.h sys/time.h unistd.h float.h])

if test $threads = true ; then
  AC_CHECK_HEADERS([pthread.h])
  if test $OS = FREEBSD ; then
    OCCFLAGS=$CXXFLAGS
    OCFLAGS=$CFLAGS
    CXXFLAGS="$CXXFLAGS -D_THREAD_SAFE -I/usr/local/include/pthread/linuxthreads"
    CFLAGS="$CFLAGS -D_THREAD_SAFE -I/usr/local/include/pthread/linuxthreads"
    have_linux_threads="yes"
    AC_CHECK_LIB(lthread, pthread_create,
    [PTHREADLIB="-llthread -llgcc_r"],[ have_linux_threads="no" ] )
    #if no linuxthreads try libc_r 
    CXXFLAGS="$OCXXFLAGS -pthread"
    CFLAGS="$OCFLAGS -pthread"
    AC_CHECK_LIB(c_r, pthread_create, [PTHREADLIB="-lc_r"])
    # actually newer FREEBSD version should have pthread... 
  else
    AC_CHECK_LIB(pthread, pthread_create,
      [PTHREADLIB="-lpthread"])
  fi
fi


# Additional arguments (and substitutions)
# Allow the pkg-config directory to be set
AC_ARG_WITH(pkgconfigdir,
	AC_HELP_STRING([--with-pkgconfigdir],
	[Use the specified pkgconfig dir (default is pkgconfig)]),
	[pkgconfigdir=${withval}],
	[pkgconfigdir='${exec_prefix}/lib/pkgconfig'])

AC_SUBST([pkgconfigdir])
AC_MSG_NOTICE([pkgconfig directory is ${pkgconfigdir}])

if test "${prefix}" = "NONE" ; then
  prefix=${ac_default_prefix}
fi

sysconfdir="${sysconfdir}/$PACKAGE"
DEF_SYSCONFDIR=`eval echo ${sysconfdir}`
AC_DEFINE_UNQUOTED(DEF_SYSCONFDIR, "$DEF_SYSCONFDIR", "sysconfig dir")

DEF_STATEDIR=`eval echo ${prefix}/var`
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
				 libipap-0.0.pc
                 src/Makefile
                 test/Makefile])

AC_OUTPUT
