/* audio-provider.thrift is thrift-based interface,
 * used by thrift compiler to generate cpp class
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

service AudioProvider {
	
	list<string> get_playout_devices(),

	list<string> get_recording_devices(),
	
	void set_playout_device(1:string name),
	
	void set_recording_device(1:string name),
	
	byte get_speech_input_level(),
	
	void start_mic_test(),
	
	void stop_mic_test(),
	
	void play_tone(),
	
	void make_call(1:string address),
	
	void end_call(),
}
