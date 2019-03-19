#include "MainWindow.h"
#include "Menu.h"
#include "Fl_AudioFile.h"
#include "Waveform.h"
#include "Spectrum.h"

int main()
{
	Menu MainMenu;
	Fl_AudioFile<float> AudioTrack;
	Waveform WaveFrm;
	Spectrum SpectrFrm;
	MainWindow BaseWindow(600, 600, "Spectrum Analyzer", &MainMenu, &AudioTrack, &WaveFrm, &SpectrFrm);
	BaseWindow.add(MainMenu);
	BaseWindow.add(WaveFrm);
	BaseWindow.add(SpectrFrm);
	BaseWindow.show();
	return Fl::run();
}