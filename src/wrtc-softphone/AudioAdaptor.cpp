#include "AudioAdaptor.h"

AudioAdaptor::AudioAdaptor()
{
	m_VoiceEngine = VoiceEngine::Create();

	m_VoEBase = VoEBase::GetInterface(m_VoiceEngine);
	m_VoEBase->Init();
}

AudioAdaptor::~AudioAdaptor()
{

}
