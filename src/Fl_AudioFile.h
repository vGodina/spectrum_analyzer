#ifndef FL_AUDIOFILE
#define FL_AUDIOFILE

#include <audiofile/AudioFile.h>
#include <fltk/Fl_Box.H>

class Fl_AudioFile : public Fl_Box {
private:
	AudioFile<float> AudioTrack;
public:
	Fl_AudioFile();
	~Fl_AudioFile();
	AudioFile<float>* GetAudio();
};

#endif FL_AUDIOFILE