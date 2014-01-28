# CMakeLists.txt for local WebRTC Audio Provider
#
# Copyright 2014 Yegor Mazur <yegor.mazur@gmail.com>
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
project(webrtc-audio-provider)

set(HEADERS webrtc-audio-provider.h)
set(SOURCES webrtc-audio-provider.cpp)

include_directories(
	${WEBRTC_ROOT}/webrtc/voice_engine/include
	${WEBRTC_ROOT}/webrtc
	${CMAKE_BINARY_DIR}
	)

set(LIBRARIES 
	${WEBRTC_ENGINE_OUTPUT}
	pthread
	dl
	)

add_library(${WEBRTC_AUDIO_PROVIDER_OUTPUT} STATIC ${SOURCES})
target_link_libraries(${WEBRTC_AUDIO_PROVIDER_OUTPUT} ${LIBRARIES})
