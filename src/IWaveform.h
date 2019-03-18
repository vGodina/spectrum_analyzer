#ifndef IWAVEFORM
#define IWAVEFORM
#include <boost/signals2.hpp>
#include "IAudioFile.h"

// Interface of Waveform

class IWaveForm
{
public:
	virtual ~IWaveForm() = default;
	using signal_t = boost::signals2::signal <void(double)>;
	virtual boost::signals2::connection connect(const signal_t::slot_type &slot) = 0;
	virtual bool GetAudio(const IAudioFile<float>::AudioBuffer& AudioData) = 0;
};
#endif IWAVEFORM