#ifndef IAUDIOFILE
#define IAUDIOFILE
#include <vector>
// Interface of AudioFile
template <typename T>
struct IAudioFile
{
	virtual ~IAudioFile() = default;
	using AudioBuffer = std::vector<std::vector<T> >;
	virtual bool Load (std::string FileName) = 0;
	virtual int GetLength () const = 0;
	virtual const AudioBuffer& PassData () const = 0;
};

#endif IAUDIOFILE