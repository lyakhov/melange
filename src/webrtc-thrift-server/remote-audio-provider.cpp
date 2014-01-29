/* remote-audio-provider.cpp
 *
 * Copyright 2014 Yegor Mazur <yegor.mazur@gmail.com>
 *
 * This file is part of Melange.
 *
 * Melange is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Melange is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Melange. If not, see <http://www.gnu.org/licenses/>.
 */

#include "remote-audio-provider.h"
#include "config.h"

#include <boost/foreach.hpp>
#include <boost/thread/locks.hpp>
#include <boost/weak_ptr.hpp>

using namespace boost;

WebRtcAudioProviderThrift::WebRtcAudioProviderThrift()
{
}

void WebRtcAudioProviderThrift::get_playout_devices(std::vector< std::string >& _return)
{

	m_audioProvider.get_playout_devices(_return);
}

void WebRtcAudioProviderThrift::get_recording_devices(std::vector< std::string >& _return)
{

	m_audioProvider.get_recording_devices(_return);
}

void WebRtcAudioProviderThrift::set_playout_device(const std::string& name)
{
	m_audioProvider.set_playout_device(name);
}

void WebRtcAudioProviderThrift::set_recording_device(const std::string& name)
{
	m_audioProvider.set_recording_device(name);
}

int8_t WebRtcAudioProviderThrift::get_speech_input_level()
{
	return m_audioProvider.get_speech_input_level();
}

void WebRtcAudioProviderThrift::start_mic_test()
{
	m_audioProvider.start_recording_device_test();
}

void WebRtcAudioProviderThrift::stop_mic_test()
{
	m_audioProvider.stop_recording_device_test();
}

void WebRtcAudioProviderThrift::play_tone()
{
	m_audioProvider.play_tone();
}

void WebRtcAudioProviderThrift::make_call(const std::string& address)
{
	m_audioProvider.make_call(address);
}

void WebRtcAudioProviderThrift::end_call()
{
	m_audioProvider.end_call();
}

WebRtcAudioProviderThrift::~WebRtcAudioProviderThrift()
{

}
