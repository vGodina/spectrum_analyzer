#include <memory>
#include "MainWindow.h"
#include "Menu.h"
#include "Waveform.h"
#include "Spectrum.h"
#include "RAudioFile.h"
#include "RButton.h"
#include "RFileChooser.h"
#include "RChart.h"
#include "RChoice.h"
#include "RSlider.h"
#include "CustomSlider.h"
#include "LevelMeter.h"
#include "FFTHandler.h"

int main()
{
	// Menu Widget forming
	//auto MenuGroup = std::make_unique<Fl_Group>(30, 30, 100, 30);
	auto FileChooser = std::make_unique<RFileChooser>();
	auto OpenMenuButton = std::make_unique<RButton>(30, 30, 100, 30, "Open .wav file");

	auto MainMenu = std::make_unique<Menu>(30, 30, 100, 30, std::move(FileChooser), std::move(OpenMenuButton));

	// Waveform Widget forming  std::unique_ptr<ISlider> Slidr
	//auto WaveformGroup = std::make_unique<Fl_Group>(20, 100, 527, 247);
	auto WaveformChart = std::make_unique<RChart>(20, 100, 500, 200, "");
	auto Slider = std::make_unique<RSlider>(20, 300, 500, 20, "");
	auto CustomSlidr = std::make_unique<CustomSlider>(std::move(Slider));
	auto ZoomInHButton = std::make_unique<RButton>(47, 322, 25, 25, "+");
	auto ZoomOutHButton = std::make_unique<RButton>(20, 322, 25, 25, "-");
	auto ZoomInVButton = std::make_unique<RButton>(522, 100, 25, 25, "+");
	auto ZoomOutVButton = std::make_unique<RButton>(522, 127, 25, 25, "-");

	auto WaveFrm = std::make_unique<Waveform>(20, 100, 527, 247,
		std::move(WaveformChart), std::move(CustomSlidr),
		std::move(ZoomInHButton), std::move(ZoomOutHButton), std::move(ZoomInVButton), std::move(ZoomOutVButton));

	// Spectrum Widget forming
	//auto SpectrumGroup = std::make_unique<Fl_Group>(20, 360, 500, 222);
	//Meter{	520, 360, 10, 200
	auto SpectrChart = std::make_unique<RChart>(20, 360, 500, 200, "");
	auto SpectrChoice = std::make_unique<RChoice>(420, 560, 100, 22, "FFT Size:");
	auto SpectrFFT = std::make_unique<FFTHandler>();
	auto MeterChart = std::make_unique<RChart>(520, 360, 10, 200, "");
	auto SpectrLMeter = std::make_unique<LevelMeter>(std::move(MeterChart));
	auto SpectrFrm = std::make_unique<Spectrum>(20, 360, 500, 222,
		std::move(SpectrChart), std::move(SpectrChoice), std::move(SpectrFFT), std::move(SpectrLMeter));

	auto AudioTrack = std::make_unique<RAudioFile<float>>();

	MainWindow BaseWindow(600, 600, "Spectrum Analyzer", std::move(MainMenu), std::move(WaveFrm), std::move(SpectrFrm), std::move(AudioTrack));
	return Fl::run();
}