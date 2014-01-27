/* audio-provider-wrtc.cpp
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
#include "config.h"
#include <string.h>
#include <iostream>

AudioAdaptor::AudioAdaptor()
{
	m_VoiceEngine = VoiceEngine::Create();
	int err;
	
	m_VoEBase = VoEBase::GetInterface(m_VoiceEngine);
	if (m_VoEBase->Init() != 0)
	{
		err = m_VoEBase->LastError();
	}
	
	m_VoEHardware = VoEHardware::GetInterface(m_VoiceEngine);
	m_VoEVolumeControl = VoEVolumeControl::GetInterface(m_VoiceEngine);
	m_VoEFile = VoEFile::GetInterface(m_VoiceEngine);
	m_VoENetwork = VoENetwork::GetInterface(m_VoiceEngine);
}

void AudioAdaptor::GetPlayBackDevices(std::vector<std::string> &dev)
{
	int number;
	m_VoEHardware->GetNumOfPlayoutDevices(number);
	
	for (int i = 0; i < number; i++)
	{
		char strNameUTF8[128];
		char strGuidUTF8[128];
		
		m_VoEHardware->GetPlayoutDeviceName(i, strNameUTF8, strGuidUTF8);
		dev.push_back(strNameUTF8);
	}
}

void AudioAdaptor::GetRecordingDevices(std::vector<std::string> &dev)
{
	int number;
	m_VoEHardware->GetNumOfRecordingDevices(number);
	
	for (int i = 0; i < number; i++)
	{
		char strNameUTF8[128];
		char strGuidUTF8[128];
		
		m_VoEHardware->GetRecordingDeviceName(i, strNameUTF8, strGuidUTF8);
		dev.push_back(strNameUTF8);
	}
}

void AudioAdaptor::SetPlayoutDevice(const std::string &dev)
{
	std::vector<std::string> vec;
	GetPlayBackDevices(vec);
	for (int i = 0; i < vec.size(); i++)
	{
		if (dev == vec[i])
		{
			m_VoEHardware->SetPlayoutDevice(i);
			break;
		}
	}
}

void AudioAdaptor::SetRecordingDevice(const std::string &dev)
{
	std::vector<std::string> vec;
	GetRecordingDevices(vec);
	for (int i = 0; i < vec.size(); i++)
	{
		if (dev == vec[i])
		{
			m_VoEHardware->SetRecordingDevice(i);
			break;
		}
	}
}

unsigned int AudioAdaptor::GetMicrophoneLevel()
{
	unsigned int lev;
	m_VoEVolumeControl->GetSpeechInputLevel(lev);
	return lev;
}

void AudioAdaptor::PlayTone()
{
	m_TestAudioChannel = m_VoEBase->CreateChannel();
	char tone[1024] = "\0";
	strcat(tone, PATH_TO_AUDIO_FILE);
	strcat(tone, "/tone.wav");
	
	m_VoEBase->StartPlayout(m_TestAudioChannel);
	m_VoEFile->StartPlayingFileLocally(m_TestAudioChannel, tone);
}

void AudioAdaptor::StartMicTest()
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

void AudioAdaptor::StopMicTest()
{
	m_VoEFile->StopRecordingMicrophone();
}

void AudioAdaptor::MakeCall(std::string &addr)
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
	
	if (m_VoEBase->SetSendDestination(m_audioCallChannel, 55555, addr.c_str()) != 0)
	{
		std::cout << "Error SetSendDestination " << m_VoEBase->LastError();
	}
	
	if (m_VoEBase->StartSend(m_audioCallChannel) != 0)
	{
		std::cout << "Error StartSend " << m_VoEBase->LastError();
	}
}

void AudioAdaptor::EndCall()
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

AudioAdaptor::~AudioAdaptor()
{
	m_VoEBase->DeleteChannel(m_TestAudioChannel);
	m_VoEHardware->Release();
	m_VoEVolumeControl->Release();
	m_VoEFile->Release();
	m_VoENetwork->Release();
	m_VoEBase->Terminate();
	
	VoiceEngine::Delete(m_VoiceEngine);
}
