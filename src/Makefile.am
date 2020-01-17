##   main.c - My humble shell project
##
##   Copyright (c) 2019, <project-developers>
##
##   This file is part of <project-name>
##
##   <project-name> is free software: you can redistribute it and/or modify
##   it under the terms of the GNU General Public License as published by
##   the Free Software Foundation, either version 3 of the License, or
##   (at your option) any later version.
##
##   This program is distributed in the hope that it will be useful,
##   but WITHOUT ANY WARRANTY; without even the implied warranty of
##   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
##   GNU General Public License for more details.
##
##   You should have received a copy of the GNU General Public License
##   along with this program.  If not, see <http://www.gnu.org/licenses/>.

AM_CPPFLAGS = -I$(top_srcdir)/lib @CPP_FLAGS@
AM_CFLAGS =   @C_FLAGS@ 
AM_LDFLAGS =  @LD_FLAGS@

bin_PROGRAMS = myshell

myshell_SOURCES = main.c

# Uncommment if you use libposixeg
#
myshell_LDFLAGS = -lposixeg

