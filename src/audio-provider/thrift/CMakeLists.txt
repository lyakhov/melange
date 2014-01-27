# CMakeLists.txt for remote audio provider using thrift
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

set(HEADERS
	../main-window.h
	)

set(SOURCES
	../main.cpp
	../main-window.cpp
	audio-provider-thrift.cpp
	${THRIFT_GEN_ROOT}/AudioAdaptor.cpp
	)

find_package(Qt4 REQUIRED)

INCLUDE(${QT_USE_FILE})

include_directories(
	${WRTC_ROOT}/webrtc/voice_engine/include
	${WRTC_ROOT}/webrtc
	${AUDIO_PROVIDER_THRIFT_ROOT}
	${THRIFT_GEN_ROOT}
	${PROJECT_BINARY_DIR}
	)
	
set(LIBRARIES 
	${QT_LIBRARIES}
	thrift
	)

QT4_WRAP_CPP(HEADERS_MOC ${HEADERS})

add_executable(${AUDIO_PROVIDER_THRIFT_OUTPUT} ${SOURCES} ${HEADERS_MOC})
target_link_libraries(${AUDIO_PROVIDER_THRIFT_OUTPUT} ${LIBRARIES})

