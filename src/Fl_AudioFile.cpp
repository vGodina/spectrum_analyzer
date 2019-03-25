#include "Fl_AudioFile.h"

template <typename T>
Fl_AudioFile<T>::Fl_AudioFile() : AudioTrack() {}


template <typename T>
bool Fl_AudioFile<T>::Load(std::string FileName)
{
	Loaded = AudioTrack.load(FileName);
	return Loaded;
}

template <typename T>
bool Fl_AudioFile<T>::IsLoaded() const
{
	return Loaded;
}

template <typename T>
int Fl_AudioFile<T>::GetLength () const
{
	return AudioTrack.getNumSamplesPerChannel();
}

template <typename T>
const typename IAudioFile<T>::AudioBuffer& Fl_AudioFile<T>::PassData() const
{
	return AudioTrack.samples;
}

template class Fl_AudioFile<float>;
template class Fl_AudioFile<double>;