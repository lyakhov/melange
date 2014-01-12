# Top-level CMakeLists.txt for Melange
#
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
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with Melange.  If not, see <http://www.gnu.org/licenses/>.

cmake_minimum_required (VERSION 2.8)

project(melange) # Use CMAKE_PROJECT_NAME to get this name

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/src/cmake)

set(GST_AUDIOPLAYER_ROOT ${PROJECT_SOURCE_DIR}/src/gst-audioplayer)
set(GST_AUDIOPLAYER_LOCAL_ROOT ${PROJECT_SOURCE_DIR}/src/gst-audioplayer/local)

add_subdirectory(${GST_AUDIOPLAYER_LOCAL_ROOT})
