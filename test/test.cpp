#include "pch.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "IAudioFile.h"
#include "Waveform.h"
#include "Spectrum.h"

template <typename T>
class AudioFileMock : public IAudioFile<T> {
public:
	AudioFileMock() : IAudioFile<T>::IAudioFile() {}
	MOCK_CONST_METHOD0_T(GetLength, int());
	MOCK_CONST_METHOD0_T(PassData, IAudioFile<T>::AudioBuffer*());
	MOCK_METHOD1_T(load, bool(std::string FileName));
};

// Testing Waveform with AudioFile Mock
TEST(Waveform, LoadAudio) {
	int NumCh = 1;
	int Length = 10000;
	std::vector<std::vector<float>> AudioBuf (NumCh, std::vector<float>(Length));
	Waveform WForm;
	AudioFileMock<float> Mock;

	EXPECT_CALL(Mock, PassData()).WillOnce(::testing::Return(&AudioBuf));
	// This test covers Waveform methods: Pass, Draw, VerticalScale
	EXPECT_EQ(WForm.GetAudio(Mock.PassData()), true);
}
// Testing Spectrum with AudioFile Mock
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

int main(int argc, char **argv) {
	testing::InitGoogleMock(&argc, argv);
	return RUN_ALL_TESTS();
}

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