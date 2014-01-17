# - Try to find the GIO2 framework
# Once done this will define
#
#  GIO2_FOUND - System has GIO2
#  GIO2_INCLUDE_DIRS - The GIO2 include directories
#  GIO2_LIBRARIES - The libraries needed to use GIO2
#  GIO2_DEFINITIONS - Compiler switches required for using GIO2
#  GIO2_VERSION_STRING - the version of GIO2 found
#
#=============================================================================
# Copyright 2014 Fedor Lyakhov <fedor.lyakhov@gmail.com>
#
# This file is part of Melange.
#
# Melange is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# Melange is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with Melange. If not, see <http://www.gnu.org/licenses/>.
#
#=============================================================================
# This file was derived from FindLibXml2.cmake and incorporates work covered by 
# the following copyright and permission notice:
#   Copyright 2006-2009 Kitware, Inc.
#   Copyright 2006 Alexander Neundorf <neundorf@kde.org>
#   Redistribution and use in source and binary forms, with or without
#   modification, are permitted provided that the following conditions
#   are met:
#
#   * Redistributions of source code must retain the above copyright
#     notice, this list of conditions and the following disclaimer.
#
#   * Redistributions in binary form must reproduce the above copyright
#     notice, this list of conditions and the following disclaimer in the
#     documentation and/or other materials provided with the distribution.
#
#   * Neither the names of Kitware, Inc., the Insight Software Consortium,
#     nor the names of their contributors may be used to endorse or promote
#     products derived from this software without specific prior written
#     permission.
#
#   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
#   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
#   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
#   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
#   HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
#   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
#   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
#   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
#   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
#   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
#   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#=============================================================================

# use pkg-config to get the directories and then use these values
# in the find_path() and find_library() calls
find_package(PkgConfig QUIET)
pkg_check_modules(PC_GIO2 QUIET gio-2.0)
set(GIO2_DEFINITIONS ${PC_GIO2_CFLAGS_OTHER})

find_path(GIO2_INCLUDE_DIRS NAMES gio/gio.h
	HINTS
	${PC_GIO2_INCLUDEDIR}
	${PC_GIO2_INCLUDE_DIRS}
	PATHS
	/usr/local/include
	/usr/include
	PATH_SUFFIXES glib-2.0
	)
find_library(GIO2_LIBRARIES NAMES gio-2.0 libgio-2.0
	HINTS
	${PC_GIO2_LIBDIR}
	${PC_GIO2_LIBRARY_DIRS}
	PATHS
	/usr/local/lib64
	/usr/local/lib
	/usr/lib64
	/usr/lib
	)
set(GIO2_VERSION_STRING ${PC_GIO2_VERSION})

# handle the QUIETLY and REQUIRED arguments and set GIO2_FOUND to TRUE if
# all listed variables are TRUE
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(GIO2
	REQUIRED_VARS GIO2_LIBRARIES GIO2_INCLUDE_DIRS
	VERSION_VAR GIO2_VERSION_STRING)

mark_as_advanced(GIO2_INCLUDE_DIRS GIO2_LIBRARIES)
