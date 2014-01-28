/* audio-provider.h
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
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Melange. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __WEBRTC_AUDIO_PROVIDER_H__
#define __WEBRTC_AUDIO_PROVIDER_H__

#include "audio-provider.h"

namespace webrtc {
	class VoiceEngine;
	class VoEBase;
	class VoEHardware;
	class VoEVolumeControl;
	class VoEFile;
}

class WebRtcAudioProvider : public AudioProvider
{
public:
	WebRtcAudioProvider();
	virtual ~WebRtcAudioProvider();

	virtual void get_playout_devices(std::vector<std::string> &dev);
	virtual void get_recording_devices(std::vector<std::string> &dev);
	virtual void set_playout_device(const std::string &dev);
	virtual void set_recording_device(const std::string &dev);

	virtual void play_tone();
	virtual unsigned int get_speech_input_level();
	virtual void start_recording_device_test();
	virtual void stop_recording_device_test();

	virtual void make_call(std::string &addr);
	virtual void end_call();

private:
	webrtc::VoiceEngine* m_pVoiceEngine;
	webrtc::VoEBase* m_pVoEBase;
	webrtc::VoEHardware* m_pVoEHardware;
	webrtc::VoEVolumeControl* m_pVoEVolumeControl;
	webrtc::VoEFile* m_pVoEFile;
	
	int m_AudioTestChannel;
	int m_AudioCallChannel;
};

#endif // __WEBRTC_AUDIO_PROVIDER_H__
