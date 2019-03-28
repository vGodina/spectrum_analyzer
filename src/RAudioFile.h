#ifndef R_AUDIOFILE_H
#define R_AUDIOFILE_H
#include <audiofile/AudioFile.h>
#include "IAudioFile.h"

template <typename T>
class RAudioFile : public IAudioFile<T> {
public:
	RAudioFile ();
	bool Load (std::string FileName) override;
	int GetLength () const override;
	const typename IAudioFile<T>::AudioBuffer& PassData() const override;
private:
	AudioFile<T> AudioTrack;
};
#endif R_AUDIOFILE_H
