#include "Fl_AudioFile.h"

Fl_AudioFile::Fl_AudioFile() :
	Fl_Box(0, 0, 0, 0),
	AudioTrack(std::make_unique<AudioFile<float>>())
{}

Fl_AudioFile::~Fl_AudioFile() {}

std::shared_ptr<AudioFile<float>> Fl_AudioFile::GetAudio()
{
	return AudioTrack;
}