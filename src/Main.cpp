#include <memory>
#include <boost/di.hpp>
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

namespace di = boost::di;

int main()
{
	/*auto MenuInjector = di::make_injector(
		di::bind<IFileChooser>.to<RFileChooser>(),
		di::bind<IButton>.to<OpMenuButton>()
	);
	//auto MMenu = MenuInjector.create<std::unique_ptr<Menu>>();
	auto MMenu = di::create<std::unique_ptr<Menu>>(MenuInjector);	*/

	// Menu Widget forming
	auto FileChooser = std::make_unique<RFileChooser>();
	auto OpenMenuButton = std::make_unique<RButton>();
	auto MainMenu = std::make_unique<Menu>(std::move(FileChooser), std::move(OpenMenuButton));

	MainMenu->SetGeometry(30, 30, 100, 30);

	// Waveform Widget forming
	auto Slider = std::make_unique<RSlider>();
	auto CustomSlidr = std::make_unique<CustomSlider>(std::move(Slider));

	auto WaveformChart = std::make_unique<RChart>();
	auto ZoomInHButton = std::make_unique<RButton>();
	auto ZoomOutHButton = std::make_unique<RButton>();
	auto ZoomInVButton = std::make_unique<RButton>();
	auto ZoomOutVButton = std::make_unique<RButton>();

	auto WaveFrm = std::make_unique<Waveform>(
		std::move(WaveformChart), std::move(CustomSlidr), std::move(ZoomInHButton),
		std::move(ZoomOutHButton), std::move(ZoomInVButton), std::move(ZoomOutVButton));

	WaveFrm->SetGeometry(20, 100, 527, 247);

	// Spectrum Widget forming
	auto SpectrChart = std::make_unique<RChart>();
	auto SpectrChoice = std::make_unique<RChoice>();
	auto SpectrFFT = std::make_unique<FFTHandler>();
	auto MeterChart = std::make_unique<RChart>();
	auto SpectrLMeter = std::make_unique<LevelMeter>(std::move(MeterChart));

	auto SpectrFrm = std::make_unique<Spectrum>(
		std::move(SpectrChart), std::move(SpectrChoice), std::move(SpectrFFT), std::move(SpectrLMeter));

	SpectrFrm->SetGeometry(20, 360, 500, 222);

	auto AudioTrack = std::make_unique<RAudioFile<float>>();

	MainWindow BaseWindow(600, 600, "Spectrum Analyzer", std::move(MainMenu), std::move(WaveFrm), std::move(SpectrFrm), std::move(AudioTrack));
	return Fl::run();
}