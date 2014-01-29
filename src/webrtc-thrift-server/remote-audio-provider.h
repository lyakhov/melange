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

#include "AudioProvider.h"
#include "webrtc-audio-provider.h"

#include <boost/shared_ptr.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/recursive_mutex.hpp>

using namespace webrtc;

class WebRtcAudioProviderThrift : public AudioProviderIf
{
public:
	WebRtcAudioProviderThrift();
	void get_playout_devices(std::vector<std::string> & _return);
	void get_recording_devices(std::vector<std::string> & _return);
	void set_playout_device(const std::string& name);
	void set_recording_device(const std::string& name);
	int8_t get_speech_input_level();
	void start_mic_test();
	void stop_mic_test();
	void play_tone();
	void make_call(const std::string& address);
	void end_call();
	virtual ~WebRtcAudioProviderThrift();
	
private:
	WebRtcAudioProvider m_audioProvider;
	
};
