#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "MenuMock.h"
#include "WaveFormMock.h"
#include "SpectrumFormMock.h"
#include "Fl_AudioFile.h"

using namespace testing;

/////////////////////////AudioFileTest fixture//////////////////////////////////////////

class AudioFileTest : public Test {
public:
	AudioFileTest() :
		AudioTrack (std::make_unique<Fl_AudioFile<float>>()),
		Menu (std::make_unique<NiceMock<MenuMock>>()),
		Waveform ( std::make_unique<NiceMock<WaveFormMock>>()),
		Spectrum ( std::make_unique<NiceMock<SpectrumFormMock>>())
	{
		//auto MainMenu = std::make_unique<NiceMock<MenuMock>>();
		//auto WaveFrm = std::make_unique<NiceMock<WaveFormMock>>();
		//auto SpectrFrm = std::make_unique<NiceMock<SpectrumFormMock>>();

		//Menu = MainMenu.get();
		//Waveform = WaveFrm.get();
		//Spectrum = SpectrFrm.get();
	}

	std::unique_ptr <Fl_AudioFile<float>> AudioTrack;

	std::unique_ptr <NiceMock<MenuMock>> Menu;
	std::unique_ptr <NiceMock<WaveFormMock>> Waveform;
	std::unique_ptr < NiceMock<SpectrumFormMock>> Spectrum;
	/*
	NiceMock<MenuMock>* Menu;
	NiceMock<WaveFormMock>* Waveform;
	NiceMock<SpectrumFormMock>* Spectrum;
	

	MenuMock* Menu;
	WaveFormMock* Waveform;
	SpectrumFormMock* Spectrum;
	*/
	void TearDown() override
	{
		//delete Menu;
		//delete Waveform;
		//delete Spectrum;
	}
};



