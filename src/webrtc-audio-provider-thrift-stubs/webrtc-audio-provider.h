/* webrtc-audio-provider.h
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

#include <string>
#include <vector>

#include "thrift/protocol/TBinaryProtocol.h"
#include "thrift/transport/TBufferTransports.h"
#include "thrift/transport/TSocket.h"

#include <boost/shared_ptr.hpp>

#include "AudioProvider.h"

using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

class WebRtcAudioProvider
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
	boost::shared_ptr<TSocket> m_ThriftSocket;
	boost::shared_ptr<TBufferedTransport> m_ThriftTransport;
	boost::shared_ptr<TBinaryProtocol> m_ThriftProtocol;
	boost::shared_ptr<AudioProviderClient> m_ThriftAudioClient;
};
