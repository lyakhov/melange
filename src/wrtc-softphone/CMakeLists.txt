# Top-level CMakeLists.txt for wrtc-softphone
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
project (wrtc-softphone)

set(HEADERS
	main-window.h
	audio-adaptor.h
	)

set(SOURCES
	main.cpp
	audio-adaptor.cpp
	main-window.cpp
	)
	
find_package(Qt4 REQUIRED)

INCLUDE(${QT_USE_FILE})

include_directories(
	${PROJECT_SOURCE_DIR}/../../third-party/webrtc/webrtc/voice_engine/include
	${PROJECT_SOURCE_DIR}/../../third-party/webrtc/webrtc
	)

QT4_WRAP_CPP(HEADERS_MOC ${HEADERS})
	
set(WEBRTCBUILD_ROOT ${PROJECT_SOURCE_DIR}/../webrtc-build)
set(WRTC_BUILD_OUTPUT webrtc-build)

add_subdirectory(${WEBRTCBUILD_ROOT} "${CMAKE_CURRENT_BINARY_DIR}/wrtc-build")

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS_MOC})
target_link_libraries(${PROJECT_NAME} ${QT_LIBRARIES} ${WRTC_BUILD_OUTPUT} pthread dl)

add_dependencies(${PROJECT_NAME} "${WRTC_BUILD_OUTPUT}")


