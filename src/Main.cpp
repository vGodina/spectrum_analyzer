#include <memory>
#include "MainWindow.h"
#include "Menu.h"
#include "Waveform.h"
#include "Spectrum.h"
#include "RAudioFile.h"
#include "RButton.h"
#include "RFileChooser.h"

int main()
{
	// Menu Widget forming
	auto MenuGroup = std::make_unique<Fl_Group>(30, 30, 100, 30);
	auto FileChooser = std::make_unique<RFileChooser>();
	auto OpenMenuButton = std::make_unique<RButton>(30, 30, 100, 30, "Open .wav file");
	auto MainMenu = std::make_unique<Menu>(std::move(MenuGroup),std::move(FileChooser), std::move(OpenMenuButton));

	// Waveform Widget forming
	auto WaveformGroup = std::make_unique<Fl_Group>(20, 100, 527, 247);
	auto WaveFrm = std::make_unique<Waveform>(std::move(WaveformGroup));

	// Spectrum Widget forming
	auto SpectrumGroup = std::make_unique<Fl_Group>(20, 360, 500, 222);
	auto SpectrFrm = std::make_unique<Spectrum>(std::move(SpectrumGroup));

	auto AudioTrack = std::make_unique<RAudioFile<float>>();

	MainWindow BaseWindow(600, 600, "Spectrum Analyzer", std::move(MainMenu), std::move(WaveFrm), std::move(SpectrFrm), std::move(AudioTrack));
	return Fl::run();
}