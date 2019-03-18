#include "pch.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <boost/signals2.hpp>
#include "IAudioFile.h"
#include "IMenu.h"
#include "IWaveForm.h"
#include "Waveform.h"
#include "Spectrum.h"
#include <audiofile/AudioFile.h>
#include "SlotFunction.h"

using namespace testing;
//////////////////////////////////////////////////////////////////////////////////////////
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
	// This test covers Waveform methods: Pass, Draw, VerticalScale
	EXPECT_EQ(WForm.GetAudio(Mock.PassData()), true);
}
////////////////////////////////////////////////////////////////////////////////////////////
class MenuMock : public IMenu {
public:
	MOCK_METHOD1(connect, boost::signals2::connection(const signal_t::slot_type &slot));
};

TEST(AudioFileMock, Load) {
	AudioFileMock<float> MockAudio;
	std::string FilePath = "C:\\Users\\Vladimir_Godina\\source\\repos\\.git\\spectrum_analyzer\\TestData\\test.wav";
	MenuMock Menu;
	boost::signals2::connection Connection;
	MenuMock::signal_t MenuSignal;
	EXPECT_CALL(Menu, connect(_)).WillOnce(Return(MenuSignal.connect(SlotFunction)));
	Menu.connect(SlotFunction);
	MenuSignal(FilePath);
}
//////////////////////////////////////////////////////////////////////////////////////////
class WaveFormMock : public IWaveForm {
public:
	MOCK_METHOD1(connect, boost::signals2::connection (const signal_t::slot_type &slot));
	MOCK_METHOD1(GetAudio, bool (const IAudioFile<float>::AudioBuffer &AudioData));
};

TEST(AudioFileMock, TestWaveForm) {
	AudioFileMock<float> MockAudio;
	std::string FilePath = "C:\\Users\\Vladimir_Godina\\source\\repos\\.git\\spectrum_analyzer\\TestData\\test.wav";
	WaveFormMock WFormMock;
	double SliderValue = 0.5;
	boost::signals2::connection Connection;
	WaveFormMock::signal_t WFormSignal;
	EXPECT_CALL(WFormMock, connect(_)).WillOnce(Return(WFormSignal.connect(WFormSlotFunction)));
	WFormMock.connect(WFormSlotFunction);
	WFormSignal(SliderValue);
}

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
	EXPECT_EQ(SpectrForm.GetAudio(Mock.PassData()), true);
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