# CMakeLists.txt for local GStreamer-based audio player
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

project(gst-audioplayer-local)

find_package(GLib2 REQUIRED)
find_package(GStreamer REQUIRED)

include_directories(${GLIB2_INCLUDE_DIRS} ${GSTREAMER_INCLUDE_DIRS})
add_definitions(${GLIB2_DEFINITIONS} ${GSTREAMER_DEFINITIONS})

set(SOURCES ../audioplayer.c)
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${GLIB2_LIBRARIES} ${GSTREAMER_LIBRARIES})
