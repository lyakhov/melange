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

#ifndef __AUDIO_PROVIDER_H__
#define __AUDIO_PROVIDER_H__

#include <string>
#include <vector>

class AudioProvider
{
public:
	virtual ~AudioProvider() {};
	
	virtual void get_playout_devices(std::vector<std::string> &dev) = 0;
	virtual void get_recording_devices(std::vector<std::string> &dev) = 0;
	virtual void set_playout_device(const std::string &dev) = 0;
	virtual void set_recording_device(const std::string &dev) = 0;

	virtual void play_tone() = 0;
	virtual unsigned int get_speech_input_level() = 0;
	virtual void start_recording_device_test() = 0;
	virtual void stop_recording_device_test() = 0;

	virtual void make_call(std::string &addr) = 0;
	virtual void end_call() = 0;
};

#endif // __AUDIO_PROVIDER_H__