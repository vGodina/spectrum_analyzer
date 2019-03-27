#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "MainWindow.h"
#include "MenuMock.h"
#include "WaveFormMock.h"
#include "SpectrumFormMock.h"
#include "AudioFileMock.h"

using namespace testing;

/////////////////////////MainWindowTest fixture//////////////////////////////////////////

struct MainWindowTest : public Test
{
	MainWindowTest()
	{
		auto MainMenu = std::make_unique<NiceMock<MenuMock>>();
		auto WaveFrm = std::make_unique<NiceMock<WaveFormMock>>();
		auto SpectrFrm = std::make_unique<NiceMock<SpectrumFormMock>>();
		auto AudioTr = std::make_unique<NiceMock<AudioFileMock<float>>>();

		Menu = MainMenu.get();
		Waveform = WaveFrm.get();
		Spectrum = SpectrFrm.get();
		AudioTrack = AudioTr.get();

		BaseWindow = std::make_unique<MainWindow>(600, 600, "Spectrum Analyzer", std::move(MainMenu), std::move(WaveFrm), std::move(SpectrFrm), std::move(AudioTr));
	}

	MenuMock* Menu;
	WaveFormMock* Waveform;
	SpectrumFormMock* Spectrum;
	AudioFileMock<float>* AudioTrack;

	std::unique_ptr<MainWindow> BaseWindow;
};