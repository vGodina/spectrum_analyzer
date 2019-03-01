#include "Fl_AudioFile.h"

Fl_AudioFile::Fl_AudioFile() :
	Fl_Box(0, 0, 0, 0),
	AudioTrack(AudioFile<float>())
{}

Fl_AudioFile::~Fl_AudioFile() {}

AudioFile<float>* Fl_AudioFile::GetAudio()
{
	return &AudioTrack;
}