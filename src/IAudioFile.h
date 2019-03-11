#ifndef IAUDIOFILE
#define IAUDIOFILE
#include <vector>
// Interface of AudioFile
template <typename T>
class IAudioFile
{
public:
	using AudioBuffer = std::vector<std::vector<T>>;
	virtual bool load (std::string FileName) = 0;
	virtual int GetLength () const = 0;
	virtual AudioBuffer GetData () const = 0;
protected:
	// A vector of vectors of audio samples: samples[channel][sampleIndex]
	AudioBuffer samples;
};

#endif IAUDIOFILE