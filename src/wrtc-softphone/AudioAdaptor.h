#include "voe_base.h"
using namespace webrtc;

class AudioAdaptor
{
public:
	AudioAdaptor();
	virtual ~AudioAdaptor();
	
private:
	VoiceEngine* m_VoiceEngine;
	VoEBase* m_VoEBase;
};
