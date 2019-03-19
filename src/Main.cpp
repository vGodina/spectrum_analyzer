#include "MainWindow.h"
#include "Menu.h"
#include "Fl_AudioFile.h"
#include "Waveform.h"
#include "Spectrum.h"

#include <memory>

int main()
{
	//std::unique_ptr<Menu> MainMenu;
	auto MainMenu = std::make_unique<Menu>();
	auto WaveFrm = std::make_unique<Waveform>();
	auto SpectrFrm = std::make_unique<Spectrum>();
	Fl_AudioFile<float> AudioTrack;
	MainWindow BaseWindow(600, 600, "Spectrum Analyzer", &AudioTrack, std::move(MainMenu), std::move(WaveFrm), std::move(SpectrFrm));
	return Fl::run();
}