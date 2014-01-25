# CMakeLists.txt for GStreamer API stubs redirecting calls to gstd,
# the GStreamer D-Bus Daemon
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

project(gst-dbus-stubs)

find_package(GLib2 REQUIRED)
find_package(GIO2 REQUIRED)

include_directories(
	${PROJECT_SOURCE_DIR}
	${GLIB2_INCLUDE_DIRS}
	${GIO2_INCLUDE_DIRS}
	)
add_definitions(${GLIB2_DEFINITIONS} ${GIO2_DEFINITIONS})

set(SOURCES
	gst-element-stub.c
	gst-dbus-stubs.c
	gst-bus-stub.c
	gstd-factory-interface.c
	gstd-pipeline-interface.c
	)
set(HEADERS
	gst/gst.h
	gst-element-stub.h
	gst-element-private-stub.h
	gst-bus-stub.h
	gst-bus-private-stub.h
	gstd-pipeline-interface.h
	gstd-factory-interface.h
	)

add_library(${GST_DBUS_STUBS_OUTPUT} SHARED ${SOURCES} ${HEADERS})
target_link_libraries(${GST_DBUS_STUBS_OUTPUT} ${GLIB2_LIBRARIES} ${GIO2_LIBRARIES})
