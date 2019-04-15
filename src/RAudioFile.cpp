#include "RAudioFile.h"

template <typename T>
RAudioFile<T>::RAudioFile() : AudioTrack() {}

template <typename T>
bool RAudioFile<T>::Load(std::string FileName)
{
	return AudioTrack.load(FileName);
}


template <typename T>
int RAudioFile<T>::GetLength () const
{
	return AudioTrack.getNumSamplesPerChannel();
}


template <typename T>
const typename IAudioFile<T>::AudioBuffer& RAudioFile<T>::GetData() const
{
	return AudioTrack.samples;
}

template class RAudioFile<float>;
template class RAudioFile<double>;