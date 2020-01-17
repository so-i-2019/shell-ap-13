dnl    configure.ac - Autoconf script
dnl
dnl    Copyright 2019  Joao Vitor Silva Ramos and Vitor Santana Cordeiro
dnl
dnl    This file is part of GGshell
dnl
dnl    GGshell is free software: you can redistribute it and/or modify
dnl    it under the terms of the GNU General Public License as published by
dnl    the Free Software Foundation, either version 3 of the License, or
dnl    (at your option) any later version.
dnl
dnl    This software is distributed in the hope that it will be useful,
dnl    but WITHOUT ANY WARRANTY; without even the implied warranty of
dnl    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
dnl    GNU General Public License for more details.
dnl
dnl    You should have received a copy of the GNU General Public License
dnl    along with .  If not, see <http://www.gnu.org/licenses/>.
dnl

AC_INIT([project-name], [0.0.1])       dnl Init Autoconf
AC_PREREQ([2.65])                      dnl Required autoconf version
AC_CONFIG_AUX_DIR([build-aux])         dnl Where to write auxiliary files
AC_CONFIG_MACRO_DIR([m4])              dnl m4 files here
AC_CONFIG_HEADERS([config.h])          dnl Generate config.h

AM_INIT_AUTOMAKE([-Wall -Werror 1.14.1 subdir-objects])	dnl Init Automake options

AM_PROG_AR                             dnl Archiver for static lib
LT_INIT            		       dnl Libtool support in 'configure'


AC_PROG_CC 		               dnl Defines CC


dnl Define compiler user flags

AC_SUBST([CPP_FLAGS],"-ansi -D_POSIX_C_SOURCE=200809L -Wall -Wfatal-errors") dnl Define flags
AC_SUBST([C_FLAGS])
AC_SUBST([LD_FLAGS])
AC_SUBST([ac_macro_dir],"m4")

dnl Comment if you are not using libposixeg
dnl
AC_SEARCH_LIBS([posixeg_version], [posixeg],, AC_MSG_ERROR([*** Error: either libposixeg missing or CPPF/LAGS/LDFLAGS needed.]) ,[])
AC_SEARCH_LIBS([posixeg_version], [posixeg],
   AC_DEFINE(HAVE_POSIXEG,1,[Defined to 1 if POSIXeg library is present]
),AC_MSG_WARN([No POSIXeg]))



# Uncomment if you are using readline, see documentation in
# https://www.gnu.org/software/autoconf-archive/ax_lib_readline.html
# for how to use config.h in you project.
#
AX_LIB_READLINE


AC_CONFIG_FILES([Makefile src/Makefile])	dnl Output files

AC_OUTPUT					dnl Do it
