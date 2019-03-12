#include "pch.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "IAudioFile.h"
#include "Waveform.h"

template <typename T>
class AudioFileMock : public IAudioFile<T> {
public:
	AudioFileMock() : IAudioFile<T>::IAudioFile() {}
	MOCK_CONST_METHOD0_T(GetLength, int());
	MOCK_CONST_METHOD0_T(GetData, IAudioFile<T>::AudioBuffer*());
	MOCK_METHOD1_T(load, bool(std::string FileName));
};

TEST(Waveform, PassData) {
	// Prepare test data from real audiofile
	std::string FilePath = "C:\\Users\\Vladimir_Godina\\source\\repos\\.git\\spectrum_analyzer\\TestData\\test.wav";
	AudioFile<float> Audio;
	Audio.load(FilePath);
	int Length = Audio.getNumSamplesPerChannel();
	int NumCh = Audio.getNumChannels();
	//AudioFileMock<float>::AudioBuffer is std::vector<std::vector<float>> . Both work with .Pass method
	AudioFileMock<float>::AudioBuffer AudioBuf (NumCh, std::vector<float>(Length));
	AudioBuf[0] = Audio.samples[0];
	// Making mock 
	AudioFileMock<float> Mock;
	//EXPECT_CALL(Mock, load(FilePath)).WillOnce(::testing::Return(true));
	//EXPECT_CALL(Mock, GetLength()).WillOnce(::testing::Return(Length));
	//EXPECT_TRUE(Mock.load(FilePath));
	//EXPECT_EQ(Mock.GetLength(), Length);
	EXPECT_CALL(Mock, GetData()).WillOnce(::testing::Return(&AudioBuf));
	Waveform WForm;
	// Check if Waveform object passes AudioBuffer from Mock object
	EXPECT_EQ(WForm.Pass(Mock.GetData()), Length);
}

int main(int argc, char **argv) {
	
	testing::InitGoogleMock(&argc, argv);
	return RUN_ALL_TESTS();
}