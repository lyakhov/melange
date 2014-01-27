/* remote-audio-provider.h
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

#include "AudioAdaptor.h"
#include "vmc_types.h"

#include "voe_base.h"
#include "voe_hardware.h"
#include "voe_network.h"
#include "voe_volume_control.h"
#include "voe_file.h"

#include <boost/shared_ptr.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/recursive_mutex.hpp>

using namespace webrtc;

class VMCAudioAdaptor : public AudioAdaptorIf
{
public:
	VMCAudioAdaptor();
	
	int8_t GetPlayoutDeviceNumber();
	int8_t GetRecordingDeviceNumber();
	void GetPlayoutDeviceName(std::string& _return, const int8_t number);
	void GetRecordingDeviceName(std::string& _return, const int8_t number);
	void SetPlayoutDevice(const std::string& name);
	void SetRecordingDevice(const std::string& name);
	int8_t GetSpeechInputLevel();
	void StartMicTest();
	void StopMicTest();
	void PlayTone();
	void MakeCall(const std::string& address);
	void EndCall();
	
	virtual ~VMCAudioAdaptor();
	
private:
	int m_TestAudioChannel;
	int m_audioCallChannel;
	
	VoiceEngine* m_VoiceEngine;
	VoEBase* m_VoEBase;
	VoEHardware* m_VoEHardware;
	VoEVolumeControl* m_VoEVolumeControl;
	VoENetwork* m_VoENetwork;
	VoEFile* m_VoEFile;
};
