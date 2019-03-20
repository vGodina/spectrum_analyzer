#include <memory>
#include "MainWindow.h"
#include "Menu.h"
#include "Waveform.h"
#include "Spectrum.h"
#include "Fl_AudioFile.h"

int main()
{
	auto MainMenu = std::make_unique<Menu>();
	auto WaveFrm = std::make_unique<Waveform>();
	auto SpectrFrm = std::make_unique<Spectrum>();
	auto AudioTrack = std::make_unique<Fl_AudioFile<float>>();
	MainWindow BaseWindow(600, 600, "Spectrum Analyzer", std::move(MainMenu), std::move(WaveFrm), std::move(SpectrFrm), std::move(AudioTrack));
	return Fl::run();
}