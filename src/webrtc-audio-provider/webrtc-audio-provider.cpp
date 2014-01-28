/* audio-provider-wrtc.cpp
 *
 * Copyright 2014 Yegor Mazur <yegor.mazur@gmail.com>
 * Copyright 2014 Fedor Lyakhov <fedor.lyakhov@gmail.com>
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
 *namespace
 * You should have received a copy of the GNU Lesser General Public License
 * along with Melange. If not, see <http://www.gnu.org/licenses/>.
 */

#include "webrtc-audio-provider.h"
#include "config.h"

#include <voe_base.h>
#include <voe_hardware.h>
#include <voe_volume_control.h>
#include <voe_file.h>

#include <string.h>
#include <iostream>

#define WEBRTC_DEVICE_NAME_LENGTH 128
#define FILE_PATH_LENGHT 260 // FIXME
#define RTP_PORT 55555 // FIXME

using namespace webrtc;

WebRtcAudioProvider::WebRtcAudioProvider()
 : m_AudioTestChannel(-1), m_AudioCallChannel(-1)
{
	m_pVoiceEngine = VoiceEngine::Create();
	if (!m_pVoiceEngine) {
		std::cerr << "Failed to create VoiceEngine" << std::endl;
		throw std::exception();
	}
	
	m_pVoEBase = VoEBase::GetInterface(m_pVoiceEngine);
	if (m_pVoEBase->Init() != 0) {
		std::cerr << "Failed to initialize VoEBase, error code: " << m_pVoEBase->LastError() 
			<< std::endl;
		throw std::exception();
	}
	
	m_pVoEHardware = VoEHardware::GetInterface(m_pVoiceEngine);
	m_pVoEVolumeControl = VoEVolumeControl::GetInterface(m_pVoiceEngine);
	m_pVoEFile = VoEFile::GetInterface(m_pVoiceEngine);
	
	m_AudioTestChannel = m_pVoEBase->CreateChannel();
}

WebRtcAudioProvider::~WebRtcAudioProvider()
{
	if (m_AudioTestChannel >= 0)
		m_pVoEBase->DeleteChannel(m_AudioTestChannel);
	if (m_AudioCallChannel >= 0)
		m_pVoEBase->DeleteChannel(m_AudioCallChannel);
	m_pVoEHardware->Release();
	m_pVoEVolumeControl->Release();
	m_pVoEFile->Release();
	m_pVoEBase->Terminate();
	
	VoiceEngine::Delete(m_pVoiceEngine);
}

void WebRtcAudioProvider::get_playout_devices(std::vector<std::string> &dev)
{
	int number;
	m_pVoEHardware->GetNumOfPlayoutDevices(number);
	
	for (int i = 0; i < number; i++)
	{
		char sName[WEBRTC_DEVICE_NAME_LENGTH];
		char sGuid[WEBRTC_DEVICE_NAME_LENGTH];
		
		m_pVoEHardware->GetPlayoutDeviceName(i, sName, sGuid);
		dev.push_back(sName);
	}
}

void WebRtcAudioProvider::get_recording_devices(std::vector<std::string> &dev)
{
	int number;
	m_pVoEHardware->GetNumOfRecordingDevices(number);
	
	for (int i = 0; i < number; i++)
	{
		char sName[WEBRTC_DEVICE_NAME_LENGTH];
		char sGuid[WEBRTC_DEVICE_NAME_LENGTH];
		
		m_pVoEHardware->GetRecordingDeviceName(i, sName, sGuid);
		dev.push_back(sName);
	}
}

void WebRtcAudioProvider::set_playout_device(const std::string &dev)
{
	std::vector<std::string> vec;
	get_playout_devices(vec);
	for (int i = 0; i < vec.size(); i++) // TODO: use std::find
	{
		if (dev == vec[i])
		{
			m_pVoEHardware->SetPlayoutDevice(i);
			break;
		}
	}
}

void WebRtcAudioProvider::set_recording_device(const std::string &dev)
{
	std::vector<std::string> vec;
	get_recording_devices(vec);
	for (int i = 0; i < vec.size(); i++) // TODO: use std::find
	{
		if (dev == vec[i])
		{
			m_pVoEHardware->SetRecordingDevice(i);
			break;
		}
	}
}

unsigned int WebRtcAudioProvider::get_speech_input_level()
{
	unsigned int level;
	m_pVoEVolumeControl->GetSpeechInputLevel(level);
	return level;
}

void WebRtcAudioProvider::play_tone()
{
	char tone[FILE_PATH_LENGHT] = AUDIO_RESOURCES_ROOT;
	strcat(tone, "/tone.wav");
	
	m_pVoEBase->StartPlayout(m_AudioTestChannel);
	m_pVoEFile->StartPlayingFileLocally(m_AudioTestChannel, tone, false, kFileFormatWavFile);
}

void WebRtcAudioProvider::start_recording_device_test()
{
	class RecordingDeviceTest : public OutStream
	{
	public:
		bool Write(const void *buf,int len) 
		{
			return true;
		};
	};
	
	static RecordingDeviceTest test;
	
	m_pVoEFile->StartRecordingMicrophone(&test);
}

void WebRtcAudioProvider::stop_recording_device_test()
{
	m_pVoEFile->StopRecordingMicrophone();
}

void WebRtcAudioProvider::make_call(std::string &addr)
{
	m_AudioCallChannel = m_pVoEBase->CreateChannel();
	
	if (m_pVoEBase->SetLocalReceiver(m_AudioCallChannel, RTP_PORT) != 0)
	{
		std::cerr << "Error in SetLocalReceiver " << m_pVoEBase->LastError();
	}
	
	if (m_pVoEBase->StartReceive(m_AudioCallChannel) != 0)
	{
		std::cerr << "Error in StartReceive " << m_pVoEBase->LastError();
	}
	
	if (m_pVoEBase->StartPlayout(m_AudioCallChannel) != 0)
	{
		std::cerr << "Error in StartPlayout " << m_pVoEBase->LastError();
	}
	
	if (m_pVoEBase->SetSendDestination(m_AudioCallChannel, RTP_PORT, addr.c_str()) != 0)
	{
		std::cerr << "Error in SetSendDestination " << m_pVoEBase->LastError();
	}
	
	if (m_pVoEBase->StartSend(m_AudioCallChannel) != 0)
	{
		std::cerr << "Error in StartSend " << m_pVoEBase->LastError();
	}
}

void WebRtcAudioProvider::end_call()
{
	if (m_pVoEBase->StopPlayout(m_AudioCallChannel) != 0)
	{
		std::cerr << "Error in StopPlayout " << m_pVoEBase->LastError();
	}
	
	if (m_pVoEBase->StopSend(m_AudioCallChannel) != 0)
	{
		std::cerr << "Error StopSend " << m_pVoEBase->LastError();
	}
	
	if (m_pVoEBase->StopReceive(m_AudioCallChannel) != 0)
	{
		std::cerr << "Error StopReceive " << m_pVoEBase->LastError();
	}
	
	m_pVoEBase->DeleteChannel(m_AudioCallChannel);
}
