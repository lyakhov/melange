/* server.cpp
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

#include <thrift/server/TSimpleServer.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

#include <boost/shared_ptr.hpp>

#include "remote-audio-provider.h"

using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using namespace apache::thrift::server;

int main(int argc, char *argv[])
{
	boost::shared_ptr<TBinaryProtocolFactory> protocolFactory(new TBinaryProtocolFactory());
	boost::shared_ptr<WebRtcAudioProviderThrift> handler(new WebRtcAudioProviderThrift());
	boost::shared_ptr<AudioProviderProcessor> processor(new AudioProviderProcessor(handler));
	boost::shared_ptr<TServerSocket> serverTransport(new TServerSocket(9090));
	boost::shared_ptr<TBufferedTransportFactory> transportFactory(new TBufferedTransportFactory());
  
	printf("Creating TSimpleServer...\n");
	TSimpleServer server(processor, 
						serverTransport, 
						transportFactory, 
						protocolFactory);

	printf("Starting the server...\n");
	server.serve();
	return 0;
}
