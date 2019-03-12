#define TESTING_PROCEDURE
#include "pch.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "IAudioFile.h"
#include "Waveform.h"

template <typename T>
class AudioFileMock : public IAudioFile<T> {
public:
	AudioFileMock() : IAudioFile() {}
	MOCK_CONST_METHOD0_T(GetLength, int());
	MOCK_CONST_METHOD0_T(GetData, IAudioFile<T>::AudioBuffer());
	MOCK_METHOD1_T(load, bool(std::string FileName));
};

TEST(Waveform, PassData) {
	AudioFileMock<float> Mock;
	Waveform Test;
	Test.Pass(Mock.GetData());
}

int main(int argc, char **argv) {
	
	testing::InitGoogleMock(&argc, argv);
	return RUN_ALL_TESTS();
}