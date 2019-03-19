#ifndef ISPECTRUM
#define ISPECTRUM
#include <boost/signals2.hpp>
#include "IAudioFile.h"

// Interface of Spectrum

class ISpectrum
{
public:
	virtual ~ISpectrum() = default;
	virtual bool TakeAudioData(const IAudioFile<float>::AudioBuffer& AudioData) = 0;
	virtual bool GetPosition(int) = 0;
};
#endif ISPECTRUM