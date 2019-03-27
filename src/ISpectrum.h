#ifndef ISPECTRUM
#define ISPECTRUM
#include <boost/signals2.hpp>
#include "IAudioFile.h"

// Interface of Spectrum

struct ISpectrum
{
	virtual ~ISpectrum() = default;
	virtual bool TakeAudioData(const IAudioFile<float>::AudioBuffer& AudioData) = 0;
	virtual bool SetPosition(int) = 0;
	virtual Fl_Widget* getImplWidget() = 0;
};
#endif ISPECTRUM