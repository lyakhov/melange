/* AudioAdaptor.cpp
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

AudioAdaptor::AudioAdaptor()
{
	m_VoiceEngine = VoiceEngine::Create();
	int err;
	
	m_VoEBase = VoEBase::GetInterface(m_VoiceEngine);
	if (m_VoEBase->Init() != 0)
	{
		err = m_VoEBase->LastError();
	}
	
	m_VoEHardware = VoEHardware::GetInterface(m_VoiceEngine);
}

void AudioAdaptor::GetAudioDevices(std::vector<std::string> &dev)
{
	int number;
	m_VoEHardware->GetNumOfPlayoutDevices(number);
	
	for (int i = 0; i < number; i++)
	{
		char strNameUTF8[128];
		char strGuidUTF8[128];
		
		m_VoEHardware->GetPlayoutDeviceName(i, strNameUTF8, strGuidUTF8);
		dev.push_back(strNameUTF8);
	}
}

AudioAdaptor::~AudioAdaptor()
{

}
