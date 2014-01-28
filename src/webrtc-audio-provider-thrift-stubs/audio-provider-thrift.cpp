/* audio-provider-thrift.cpp
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

#include "audio-provider.h"
#include <iostream>

AudioProvider::AudioProvider()
{
	if (m_VmcTransport.get())
	{
		m_VmcTransport->close();
	}
	m_VmcSocket.reset(new TSocket("192.168.127.23", 9090));
	m_VmcTransport.reset(new TBufferedTransport(m_VmcSocket));
	m_VmcProtocol.reset(new TBinaryProtocol(m_VmcTransport));
	m_VmcAudioClient.reset(new AudioAdaptorClient(m_VmcProtocol));
	m_VmcTransport->open();
}

void AudioProvider::GetPlayBackDevices(std::vector<std::string> &dev)
{
	int number = m_VmcAudioClient->GetPlayoutDeviceNumber();
	
	for (int i = 0; i < number; i++)
	{
		std::string strNameUTF8;
		
		m_VmcAudioClient->GetPlayoutDeviceName(strNameUTF8, i);
		dev.push_back(strNameUTF8);
	}
}

void AudioProvider::GetRecordingDevices(std::vector<std::string> &dev)
{
	int number = m_VmcAudioClient->GetRecordingDeviceNumber();
	
	for (int i = 0; i < number; i++)
	{
		std::string strNameUTF8;
		
		m_VmcAudioClient->GetRecordingDeviceName(strNameUTF8, i);
		dev.push_back(strNameUTF8);
	}
}

void AudioProvider::SetPlayoutDevice(const std::string &dev)
{
	m_VmcAudioClient->SetPlayoutDevice(dev);
}

void AudioProvider::SetRecordingDevice(const std::string &dev)
{
	m_VmcAudioClient->SetRecordingDevice(dev);
}

unsigned int AudioProvider::GetMicrophoneLevel()
{
	return m_VmcAudioClient->GetSpeechInputLevel();
}

void AudioProvider::PlayTone()
{
	m_VmcAudioClient->PlayTone();
}

void AudioProvider::StartMicTest()
{
	m_VmcAudioClient->StartMicTest();
}

void AudioProvider::StopMicTest()
{
	m_VmcAudioClient->StopMicTest();
}

void AudioProvider::MakeCall(std::string &addr)
{
	m_VmcAudioClient->MakeCall(addr);
}

void AudioProvider::EndCall()
{
	m_VmcAudioClient->EndCall();
}

AudioProvider::~AudioProvider()
{

}
