/* webrtc-audio-provider-thrift-stubs.cpp
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

#include "webrtc-audio-provider.h"
#include <iostream>

WebRtcAudioProvider::WebRtcAudioProvider()
{
	if (m_ThriftTransport.get())
	{
		m_ThriftTransport->close();
	}
	m_ThriftSocket.reset(new TSocket("localhost", 9090));
	m_ThriftTransport.reset(new TBufferedTransport(m_ThriftSocket));
	m_ThriftProtocol.reset(new TBinaryProtocol(m_ThriftTransport));
	m_ThriftAudioClient.reset(new AudioProviderClient(m_ThriftProtocol));
	m_ThriftTransport->open();
}

void WebRtcAudioProvider::get_playout_devices(std::vector<std::string> &dev)
{
	m_ThriftAudioClient->get_playout_devices(dev);
}

void WebRtcAudioProvider::get_recording_devices(std::vector<std::string> &dev)
{
	m_ThriftAudioClient->get_recording_devices(dev);
}

void WebRtcAudioProvider::set_playout_device(const std::string &dev)
{
	m_ThriftAudioClient->set_playout_device(dev);
}

void WebRtcAudioProvider::set_recording_device(const std::string &dev)
{
	m_ThriftAudioClient->set_recording_device(dev);
}

unsigned int WebRtcAudioProvider::get_speech_input_level()
{
	return m_ThriftAudioClient->get_speech_input_level();
}

void WebRtcAudioProvider::play_tone()
{
	m_ThriftAudioClient->play_tone();
}

void WebRtcAudioProvider::start_recording_device_test()
{
	m_ThriftAudioClient->start_mic_test();
}

void WebRtcAudioProvider::stop_recording_device_test()
{
	m_ThriftAudioClient->stop_mic_test();
}

void WebRtcAudioProvider::make_call(std::string &addr)
{
	m_ThriftAudioClient->make_call(addr);
}

void WebRtcAudioProvider::end_call()
{
	m_ThriftAudioClient->end_call();
}

WebRtcAudioProvider::~WebRtcAudioProvider()
{

}
