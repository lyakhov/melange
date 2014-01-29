# Top-level CMakeLists.txt for Melange
#
# Copyright 2014 Fedor Lyakhov <fedor.lyakhov@gmail.com>
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

project(melange) # Use CMAKE_PROJECT_NAME to get this name

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/src/cmake)

set(GST_DBUS_STUBS_ROOT ${PROJECT_SOURCE_DIR}/src/gst-dbus-stubs)
set(GST_AUDIOPLAYER_ROOT ${PROJECT_SOURCE_DIR}/src/gst-audioplayer)
set(GST_AUDIOPLAYER_LOCAL_ROOT ${PROJECT_SOURCE_DIR}/src/gst-audioplayer/local)
set(GST_AUDIOPLAYER_REMOTE_ROOT ${PROJECT_SOURCE_DIR}/src/gst-audioplayer/remote)

set(WEBRTC_AUDIO_PROVIDER_ROOT ${PROJECT_SOURCE_DIR}/src/webrtc-audio-provider)
set(WEBRTC_AUDIO_PROVIDER_THRIFT_ROOT ${PROJECT_SOURCE_DIR}/src/webrtc-audio-provider-thrift)
set(WEBRTC_AUDIO_PROVIDER_THRIFT_GEN_ROOT 
	${PROJECT_SOURCE_DIR}/src/webrtc-audio-provider-thrift/gen)
set(WEBRTC_AUDIO_PROVIDER_THRIFT_STUBS_ROOT
	${PROJECT_SOURCE_DIR}/src/webrtc-audio-provider-thrift-stubs)
set(WEBRTC_ENGINE_ROOT ${PROJECT_SOURCE_DIR}/src/webrtc-engine)
set(WEBRTC_SOFTPHONE_ROOT ${PROJECT_SOURCE_DIR}/src/webrtc-softphone)
set(WEBRTC_SOFTPHONE_LOCAL_ROOT ${PROJECT_SOURCE_DIR}/src/webrtc-softphone/local)
set(WEBRTC_SOFTPHONE_REMOTE_ROOT ${PROJECT_SOURCE_DIR}/src/webrtc-softphone/remote)
set(WEBRTC_ROOT ${PROJECT_SOURCE_DIR}/third-party/webrtc)
set(WEBRTC_THRIFT_SERVER_ROOT ${PROJECT_SOURCE_DIR}/src/webrtc-thrift-server)
set(RESOURCES_ROOT ${PROJECT_SOURCE_DIR}/resources)
set(AUDIO_RESOURCES_ROOT ${RESOURCES_ROOT}/audio)

configure_file(
	"${PROJECT_SOURCE_DIR}/config.h.in"
	"${PROJECT_BINARY_DIR}/config.h"
	)

set(WEBRTC_AUDIO_PROVIDER_OUTPUT webrtc-audio-provider)
set(WEBRTC_AUDIO_PROVIDER_THRIFT_GEN_OUTPUT webrtc-audio-provider-thrift-gen)
set(WEBRTC_AUDIO_PROVIDER_THRIFT_STUBS_OUTPUT webrtc-audio-provider-thrift-stubs)
set(WEBRTC_ENGINE_OUTPUT webrtc-engine)
set(WEBRTC_SOFTPHONE_LOCAL_OUTPUT webrtc-softphone-local)
set(WEBRTC_SOFTPHONE_REMOTE_OUTPUT webrtc-softphone-remote)
set(WEBRTC_THRIFT_SERVER_OUTPUT thrift-server)

set(GST_DBUS_STUBS_OUTPUT gst-dbus-stubs)

add_subdirectory(${GST_DBUS_STUBS_ROOT})
add_subdirectory(${GST_AUDIOPLAYER_LOCAL_ROOT})
add_subdirectory(${GST_AUDIOPLAYER_REMOTE_ROOT})

add_subdirectory(${WEBRTC_AUDIO_PROVIDER_ROOT})
add_subdirectory(${WEBRTC_AUDIO_PROVIDER_THRIFT_GEN_ROOT})
add_subdirectory(${WEBRTC_AUDIO_PROVIDER_THRIFT_STUBS_ROOT})
add_subdirectory(${WEBRTC_ENGINE_ROOT})
add_subdirectory(${WEBRTC_SOFTPHONE_LOCAL_ROOT})
add_subdirectory(${WEBRTC_SOFTPHONE_REMOTE_ROOT})
add_subdirectory(${WEBRTC_THRIFT_SERVER_ROOT})
