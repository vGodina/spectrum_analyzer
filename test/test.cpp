#include "pch.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <boost/signals2.hpp>
#include <audiofile/AudioFile.h>
#include "Waveform.h"
#include "Fl_AudioFile.h"
#include "MockFunctions.h"
#include "IAudioFile.h"
#include "IMenu.h"
#include "IWaveForm.h"
#include "ISpectrum.h"

using namespace testing;

/////////////////////////AudioFileMock//////////////////////////////////////////////////

template <typename T>
class AudioFileMock : public IAudioFile<T> {
public:
	AudioFileMock() : IAudioFile<T>::IAudioFile() {}
	MOCK_METHOD0_T(IsLoaded, bool());
	MOCK_METHOD1_T(Load, bool(std::string FileName));
	MOCK_CONST_METHOD0_T(GetLength, int());
	MOCK_CONST_METHOD0_T(PassData, IAudioFile<T>::AudioBuffer&());
};

// Testing Waveform with AudioFile Mock
TEST(Waveform, LoadAudio) {
	int NumCh = 1;
	int Length = 10000;
	std::vector<std::vector<float>> AudioBuf (NumCh, std::vector<float>(Length));
	Waveform WForm;
	AudioFileMock<float> Mock;
	EXPECT_CALL(Mock, PassData()).WillOnce(ReturnRef(AudioBuf));
	EXPECT_EQ(WForm.TakeAudioData(Mock.PassData()), true);
}

/////////////////////////MenuMock///////////////////////////////////////////////////////

class MenuMock : public IMenu {
public:
	MOCK_METHOD1(connect, boost::signals2::connection(const signal_t::slot_type &slot));
};

TEST(AudioFileMock, Load) {
	MenuMock Menu;
	std::string FilePath = "C:\\Users\\Vladimir_Godina\\source\\repos\\.git\\spectrum_analyzer\\TestData\\test.wav";
	MenuMock::signal_t MenuSignal;
	EXPECT_CALL(Menu, connect(_)).WillOnce(Return(MenuSignal.connect(AudioFileHandler)));
	Menu.connect(AudioFileHandler);
	MenuSignal(FilePath);
}

/////////////////////////WaveFormMock///////////////////////////////////////////////////

class WaveFormMock : public IWaveForm {
public:
	MOCK_METHOD1(connect, boost::signals2::connection (const signal_t::slot_type &slot));
	MOCK_METHOD1(TakeAudioData, bool (const IAudioFile<float>::AudioBuffer &AudioData));
};

TEST(AudioFileMock, TestWaveForm) {
	WaveFormMock WFormMock;
	double SliderValue = 0.5;
	WaveFormMock::signal_t SliderSignal;
	EXPECT_CALL(WFormMock, connect(_)).WillOnce(Return(SliderSignal.connect(SliderHandler)));
	WFormMock.connect(SliderHandler);
	SliderSignal(SliderValue);
}

/////////////////////////SpectrumFormMock///////////////////////////////////////////////

class SpectrumFormMock : public ISpectrum {
public:
	MOCK_METHOD1(TakeAudioData, bool(const IAudioFile<float>::AudioBuffer &AudioData));
	MOCK_METHOD1(GetPosition, bool(int));
};

/////////////////////////main///////////////////////////////////////////////////////////
int main(int argc, char **argv) {
	testing::InitGoogleMock(&argc, argv);
	return RUN_ALL_TESTS();
}


/* Testing Spectrum with AudioFile Mock
TEST(Spectrum, LoadAudio) {
	int NumCh = 1;
	int Length = 10000;
	std::vector<std::vector<float>> AudioBuf(NumCh, std::vector<float>(Length));
	Spectrum SpectrForm;
	AudioFileMock<float> Mock;

	EXPECT_CALL(Mock, PassData()).WillOnce(::testing::Return(&AudioBuf));
	// This test covers Waveform methods: Pass, Draw, VerticalScale
	EXPECT_EQ(SpectrForm.TakeAudioData(Mock.PassData()), true);
}
*/

/* Version with real Audio data. Preparing test data from real audiofile
std::string FilePath = "C:\\Users\\Vladimir_Godina\\source\\repos\\.git\\spectrum_analyzer\\TestData\\test.wav";
AudioFile<float> Audio;
Audio.load(FilePath);
int Length = Audio.getNumSamplesPerChannel();
int NumCh = Audio.getNumChannels();
AudioFileMock<float>::AudioBuffer AudioBuf (NumCh, std::vector<float>(Length)); // Create AudioBuffer
AudioBuf[0] = Audio.samples[0]; // Initialize AudioBuffer with data from AudioFile
*/

/* Unused stuff
EXPECT_CALL(Mock, load(FilePath)).WillOnce(::testing::Return(true));
EXPECT_CALL(Mock, GetLength()).WillOnce(::testing::Return(Length));
EXPECT_TRUE(Mock.load(FilePath));
EXPECT_EQ(Mock.GetLength(), Length);
*/