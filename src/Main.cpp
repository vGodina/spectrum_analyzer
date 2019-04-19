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
	auto WinInjector = di::make_injector(
		di::bind<IMenu>.to<Menu>(),
		di::bind<IWaveForm>.to<Waveform>(),
		di::bind<ISpectrum>.to<Spectrum>(),
		di::bind<IAudioFile<float>>.to<RAudioFile<float>>(),
		di::bind<IFileChooser>.to<RFileChooser>(),
		di::bind<IButton>.to<RButton>(),
		di::bind<ISlider>.to <RSlider>(),
		di::bind<IChart>.to<RChart>(),
		di::bind<ICustomSlider>.to<CustomSlider>(),
		di::bind<IChoice>.to <RChoice>(),
		di::bind<IFFTHandler>.to<FFTHandler>(),
		di::bind<ILevelMeter>.to<LevelMeter>()
	);
	auto BaseWindow = di::create<MainWindow*>(WinInjector);
	BaseWindow->SetGeometry(50, 50, 600, 600);
	return Fl::run();
}