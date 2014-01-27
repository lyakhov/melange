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

VMCAudioAdaptor::VMCAudioAdaptor()
{
	m_VoiceEngine = VoiceEngine::Create();
	
	m_VoEBase = VoEBase::GetInterface(m_VoiceEngine);
	m_VoEBase->Init();
	
	m_VoEHardware = VoEHardware::GetInterface(m_VoiceEngine);
	m_VoEVolumeControl = VoEVolumeControl::GetInterface(m_VoiceEngine);
	m_VoEFile = VoEFile::GetInterface(m_VoiceEngine);
	m_VoENetwork = VoENetwork::GetInterface(m_VoiceEngine);
}

int8_t VMCAudioAdaptor::GetRecordingDeviceNumber()
{
	int number;
	m_VoEHardware->GetNumOfRecordingDevices(number);
	return number;
}

int8_t VMCAudioAdaptor::GetPlayoutDeviceNumber()
{
	int number;
	m_VoEHardware->GetNumOfPlayoutDevices(number);
	return number;
}

void VMCAudioAdaptor::GetPlayoutDeviceName(std::string& _return, const int8_t number)
{
	char strNameUTF8[128];
	char strGuidUTF8[128];

	m_VoEHardware->GetPlayoutDeviceName(number, strNameUTF8, strGuidUTF8);
	_return = strNameUTF8;
}

void VMCAudioAdaptor::GetRecordingDeviceName(std::string& _return, const int8_t number)
{
	char strNameUTF8[128];
	char strGuidUTF8[128];

	m_VoEHardware->GetRecordingDeviceName(number, strNameUTF8, strGuidUTF8);
	_return = strNameUTF8;
}

void VMCAudioAdaptor::SetPlayoutDevice(const std::string& name)
{
	int number = GetPlayoutDeviceNumber();
	for (int i = 0; i < number; i++)
	{
		std::string device;
		GetPlayoutDeviceName(device, i);
		if (device == name)
		{
			m_VoEHardware->SetPlayoutDevice(i);
			break;
		}
	}
}

void VMCAudioAdaptor::SetRecordingDevice(const std::string& name)
{
	int number = GetRecordingDeviceNumber();
	for (int i = 0; i < number; i++)
	{
		std::string device;
		GetRecordingDeviceName(device, i);
		if (device == name)
		{
			m_VoEHardware->SetRecordingDevice(i);
			break;
		}
	}
}

int8_t VMCAudioAdaptor::GetSpeechInputLevel()
{
	unsigned int volume;
	m_VoEVolumeControl->GetSpeechInputLevel(volume);
	return volume;
}

void VMCAudioAdaptor::StartMicTest()
{
	class MicTest : public OutStream
	{
	public:
		bool Write(const void *buf,int len) 
		{
			return true;
		};
	};
	
	static MicTest test;
	
	m_VoEFile->StartRecordingMicrophone(&test);
}

void VMCAudioAdaptor::StopMicTest()
{
	m_VoEFile->StopRecordingMicrophone();
}

void VMCAudioAdaptor::PlayTone()
{
	m_TestAudioChannel = m_VoEBase->CreateChannel();
	char tone[1024] = "\0";
	strcat(tone, PATH_TO_AUDIO_FILE);
	strcat(tone, "/tone.wav");
	
	m_VoEBase->StartPlayout(m_TestAudioChannel);
	m_VoEFile->StartPlayingFileLocally(m_TestAudioChannel, tone);
}

void VMCAudioAdaptor::MakeCall(const std::string& address)
{
	m_audioCallChannel = m_VoEBase->CreateChannel();
	
	if (m_VoEBase->SetLocalReceiver(m_audioCallChannel, 55555) != 0)
	{
		std::cout << "Error SetLocalReceiver " << m_VoEBase->LastError();
	}
	
	if (m_VoEBase->StartReceive(m_audioCallChannel) != 0)
	{
		std::cout << "Error StartReceive " << m_VoEBase->LastError();
	}
	
	if (m_VoEBase->StartPlayout(m_audioCallChannel) != 0)
	{
		std::cout << "Error StartPlayout " << m_VoEBase->LastError();
	}
	
	if (m_VoEBase->SetSendDestination(m_audioCallChannel, 55555, address.c_str()) != 0)
	{
		std::cout << "Error SetSendDestination " << m_VoEBase->LastError();
	}
	
	if (m_VoEBase->StartSend(m_audioCallChannel) != 0)
	{
		std::cout << "Error StartSend " << m_VoEBase->LastError();
	}
}

void VMCAudioAdaptor::EndCall()
{
	if (m_VoEBase->StopPlayout(m_audioCallChannel) != 0)
	{
		std::cout << "Error StopPlayout " << m_VoEBase->LastError();
	}
	
	if (m_VoEBase->StopSend(m_audioCallChannel) != 0)
	{
		std::cout << "Error StopSend " << m_VoEBase->LastError();
	}
	
	if (m_VoEBase->StopReceive(m_audioCallChannel) != 0)
	{
		std::cout << "Error StopReceive " << m_VoEBase->LastError();
	}
	
	m_VoEBase->DeleteChannel(m_audioCallChannel);
}

VMCAudioAdaptor::~VMCAudioAdaptor()
{

}
