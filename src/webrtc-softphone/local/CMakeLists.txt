# CMakeLists.txt for local audio provider
#
# Copyright 2014 Yegor Mazur <yegor.mazur@gmail.com>
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
project(webrtc-softphone-local)

set(HEADERS
	../main-window.h
	)

set(SOURCES
	../main.cpp
	../main-window.cpp
	)

find_package(Qt4 COMPONENTS QtCore QtGui REQUIRED)
include(${QT_USE_FILE})

include_directories(
	${WEBRTC_AUDIO_PROVIDER_ROOT}
	)
	
set(LIBRARIES 
	${QT_LIBRARIES}
	${WEBRTC_AUDIO_PROVIDER_OUTPUT}
	)

qt4_wrap_cpp(HEADERS_MOC ${HEADERS})

add_executable(${WEBRTC_SOFTPHONE_LOCAL_OUTPUT} ${SOURCES} ${HEADERS_MOC})
target_link_libraries(${WEBRTC_SOFTPHONE_LOCAL_OUTPUT} ${LIBRARIES})
