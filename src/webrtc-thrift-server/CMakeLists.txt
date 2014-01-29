# CMakeLists.txt for thrift-server
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

set(SOURCES
	server.cpp
	remote-audio-provider.cpp
	)

set(Boost_USE_STATIC_LIBS     ON)
set(Boost_USE_MULTITHREADED   ON)
set(Boost_USE_STATIC_RUNTIME  OFF)

set(BOOST_COMPONENTS system)
find_package(Boost COMPONENTS ${BOOST_COMPONENTS} REQUIRED)

set(LIBRARIES
	${Boost_LIBRARIES}
	${WEBRTC_AUDIO_PROVIDER_THRIFT_GEN_OUTPUT}
	${WEBRTC_AUDIO_PROVIDER_OUTPUT}
	thrift
	)

include_directories(
	${WEBRTC_AUDIO_PROVIDER_THRIFT_GEN_ROOT}
	${WEBRTC_AUDIO_PROVIDER_ROOT}
	${CMAKE_BINARY_DIR}
	)

add_executable(${WEBRTC_THRIFT_SERVER_OUTPUT} ${SOURCES})
target_link_libraries(${WEBRTC_THRIFT_SERVER_OUTPUT} ${LIBRARIES})

