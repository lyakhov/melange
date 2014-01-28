/* audio-provider.h
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

#include "AudioAdaptor.h"

using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

class AudioProvider
{
public:
	AudioProvider();
	virtual ~AudioProvider();
	
	void GetPlayBackDevices(std::vector<std::string> &dev);
	void GetRecordingDevices(std::vector<std::string> &dev);
	void SetPlayoutDevice(const std::string &dev);
	void SetRecordingDevice(const std::string &dev);
	unsigned int GetMicrophoneLevel();
	void PlayTone();
	void StartMicTest();
	void StopMicTest();
	void MakeCall(std::string &addr);
	void EndCall();
	
private:
	boost::shared_ptr<TSocket> m_VmcSocket;
	boost::shared_ptr<TBufferedTransport> m_VmcTransport;
	boost::shared_ptr<TBinaryProtocol> m_VmcProtocol;
	boost::shared_ptr<AudioAdaptorClient> m_VmcAudioClient;
};
