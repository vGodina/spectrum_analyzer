#ifndef FL_AUDIOFILE
#define FL_AUDIOFILE
#include <audiofile/AudioFile.h>
#include "IAudioFile.h"

template <typename T>
class Fl_AudioFile : public IAudioFile<T> {
public:
	Fl_AudioFile ();
	bool Load (std::string FileName) override;
	int GetLength () const override;
	const typename IAudioFile<T>::AudioBuffer& PassData() const override;
private:
	AudioFile<T> AudioTrack;
};
#endif FL_AUDIOFILE
