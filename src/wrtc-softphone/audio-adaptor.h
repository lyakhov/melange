/* AudioAdaptor.h
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

#include "voe_base.h"
#include "voe_hardware.h"
#include "voe_network.h"
#include "voe_volume_control.h"
#include "voe_file.h"
#include <string>
#include <vector>

using namespace webrtc;

class AudioAdaptor
{
public:
	AudioAdaptor();
	virtual ~AudioAdaptor();
	
	void GetPlayBackDevices(std::vector<std::string> &dev);
	void GetRecordingDevices(std::vector<std::string> &dev);
	void SetPlayoutDevice (std::string &dev);
	void SetRecordingDevice (std::string &dev);
	unsigned int GetMicrophoneLevel();
	void PlayTone();
	void StartMicTest();
	void StopMicTest();
	void MakeCall(std::string & addr);
	void EndCall();
	
private:
	VoiceEngine* m_VoiceEngine;
	VoEBase* m_VoEBase;
	VoEHardware* m_VoEHardware;
	VoEVolumeControl* m_VoEVolumeControl;
	VoENetwork* m_VoENetwork;
	VoEFile* m_VoEFile;
	
	int m_TestAudioChannel;
	int m_audioCallChannel;
};
