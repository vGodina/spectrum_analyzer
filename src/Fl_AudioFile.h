#ifndef FL_AUDIOFILE
#define FL_AUDIOFILE
#include <audiofile/AudioFile.h>
#include "IAudioFile.h"

template <typename T>
class Fl_AudioFile : public IAudioFile<T> {
public:
	Fl_AudioFile ();
	bool load(std::string FileName) override;
	int GetLength () const override;
	IAudioFile<T>::AudioBuffer GetData() const override;
private:
	AudioFile<T> AudioTrack;
};
#endif FL_AUDIOFILE
