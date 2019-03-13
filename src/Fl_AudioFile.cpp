#include "Fl_AudioFile.h"

Fl_AudioFile<float>::Fl_AudioFile() : AudioTrack() {}
Fl_AudioFile<double>::Fl_AudioFile() : AudioTrack() {}

bool Fl_AudioFile<float>::load(std::string FileName)
{
	bool flag = AudioTrack.load(FileName);
	Fl_AudioFile::samples = AudioTrack.samples;
	return flag;
}

bool Fl_AudioFile<double>::load(std::string FileName)
{
	bool flag = AudioTrack.load(FileName);
	Fl_AudioFile::samples = AudioTrack.samples;
	return flag;
}

int Fl_AudioFile<float>::GetLength () const
{
	return AudioTrack.getNumSamplesPerChannel();
}

int Fl_AudioFile<double>::GetLength () const
{
	return AudioTrack.getNumSamplesPerChannel();
}

IAudioFile<float>::AudioBuffer* Fl_AudioFile<float>::PassData() const
{
	return Fl_AudioFile<float>::SamplesPtr;
}

IAudioFile<double>::AudioBuffer* Fl_AudioFile<double>::PassData() const
{
	return Fl_AudioFile<double>::SamplesPtr;
}