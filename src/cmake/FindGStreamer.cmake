# - Try to find the GStreamer-1.0 framework
# Once done this will define
#
#  GSTREAMER_FOUND - System has GStreamer
#  GSTREAMER_INCLUDE_DIRS - The GStreamer include directories
#  GSTREAMER_LIBRARIES - The libraries needed to use GStreamer
#  GSTREAMER_DEFINITIONS - Compiler switches required for using GStreamer
#  GSTREAMER_VERSION_STRING - the version of GStreamer found
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
pkg_check_modules(PC_GSTREAMER QUIET gstreamer-1.0)
set(GSTREAMER_DEFINITIONS ${PC_GSTREAMER_CFLAGS_OTHER})

find_path(GSTREAMER_INCLUDE_DIRS NAMES gst/gst.h
    HINTS
    ${PC_GSTREAMER_INCLUDEDIR}
    ${PC_GSTREAMER_INCLUDE_DIRS}
    PATHS
    /usr/include/gstreamer-1.0
    PATH_SUFFIXES gst
    )

find_library(GSTREAMER_LIBRARIES NAMES gstreamer-1.0 libgstreamer-1.0
    HINTS
    ${PC_GSTREAMER_LIBDIR}
    ${PC_GSTREAMER_LIBRARY_DIRS}
    PATHS
    /usr/local/lib64
    /usr/local/lib
    /usr/lib64
    /usr/lib
    )

set(GSTREAMER_VERSION_STRING ${PC_GSTREAMER_VERSION})

# handle the QUIETLY and REQUIRED arguments and set GSTREAMER_FOUND to TRUE if
# all listed variables are TRUE
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(GStreamer
                                  REQUIRED_VARS GSTREAMER_LIBRARIES GSTREAMER_INCLUDE_DIRS
                                  VERSION_VAR GSTREAMER_VERSION_STRING)

mark_as_advanced(GSTREAMER_INCLUDE_DIRS GSTREAMER_LIBRARIES)
