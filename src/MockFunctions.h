#include <iostream>
#include "Fl_AudioFile.h"
//#include "Spectrum.h"

// AudioFileHandler is Mock function that creates Fl_AudioFile object and loads audiofile by received filepath
bool AudioFileHandler (std::string FilePath)
{
	Fl_AudioFile<float> AudioTrack;
	AudioTrack.Load(FilePath);
	if (AudioTrack.IsLoaded())
		std::cout << "\n AudioFile " << FilePath << " succesfully loaded to Fl_AudioFile widget \n\n";
	return AudioTrack.IsLoaded();
}

// SliderHandler is Mock function that tests passing of Slider Value 
void SliderHandler(double CenterValue)
{
	/*std::string FilePath = "C:\\Users\\Vladimir_Godina\\source\\repos\\.git\\spectrum_analyzer\\TestData\\test.wav";
	Fl_AudioFile<float> AudioTrack;
	AudioTrack.Load(FilePath);
	
	Spectrum SpectraFrm;
	int Length = 1000;
	int CenterSample = static_cast<int>(CenterValue * Length);
	if (SpectraFrm.SetPosition(CenterSample))*/
		std::cout << "\n Value " << CenterValue << " is set to Spectrum widget successfully \n\n";
}