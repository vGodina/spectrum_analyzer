#ifndef FL_AUDIOFILE
#define FL_AUDIOFILE

#include <audiofile/AudioFile.h>
#include <fltk/Fl_Box.H>

class Fl_AudioFile : public Fl_Box, public AudioFile<float> {
public:
	Fl_AudioFile();
	~Fl_AudioFile();
private:
	
};

#endif FL_AUDIOFILE