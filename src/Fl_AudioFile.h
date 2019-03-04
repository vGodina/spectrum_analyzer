#ifndef FL_AUDIOFILE
#define FL_AUDIOFILE

#include <audiofile/AudioFile.h>
#include <fltk/Fl_Box.H>

class Fl_AudioFile : public Fl_Box {
private:
	
public:
	AudioFile<float> AudioTrack;
	Fl_AudioFile();
	~Fl_AudioFile();
	AudioFile<float>* GetAudio();
};

#endif FL_AUDIOFILE