#ifndef AUDIOFILEMOCK
#define AUDIOFILEMOCK

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "IAudioFile.h"

using namespace testing;

/////////////////////////AudioFileMock///////////////////////////////////////////////////

template <typename T>
class AudioFileMock : public IAudioFile<T> {
public:
	MOCK_CONST_METHOD0_T(IsLoaded, bool());
	MOCK_METHOD1_T(Load, bool(std::string FileName));
	MOCK_CONST_METHOD0_T(GetLength, int());
	MOCK_CONST_METHOD0_T(PassData, IAudioFile<T>::AudioBuffer&());

	IAudioFile<T>::AudioBuffer stubBuffer;

	AudioFileMock() {
		ON_CALL(*this, PassData()).WillByDefault(ReturnRef(stubBuffer));
	}
};

#endif AUDIOFILEMOCK