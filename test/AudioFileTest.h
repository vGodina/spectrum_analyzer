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
		MenuConnection = Menu->connect(boost::bind(&AudioFileTest::MenuSignalHandler, this, _1));
		SliderInteraction = Waveform->connect(boost::bind(&AudioFileTest::SliderSignalHandler, this, _1));
	}

	std::unique_ptr <Fl_AudioFile<float>> AudioTrack;

	std::unique_ptr <NiceMock<MenuMock>> Menu;
	std::unique_ptr <NiceMock<WaveFormMock>> Waveform;
	std::unique_ptr <NiceMock<SpectrumFormMock>> Spectrum;

	boost::signals2::connection  MenuConnection;
	boost::signals2::connection SliderInteraction;

	bool MenuSignalHandler(std::string FilePath)
	{
		return AudioTrack->Load(FilePath);
	}

	bool SliderSignalHandler(double Value)
	{
		return true;
	}

	void TearDown() override { }
};



