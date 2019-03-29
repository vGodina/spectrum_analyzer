#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>
#include "IFFTHandler.h"

using namespace testing;

/////////////////////////ButtonMock////////////////////////////////////////////////////////

struct FFTHandlerMock : public IFFTHandler
{
	MOCK_METHOD2(DoFFT, void(std::vector <float> AudioTrack, int FFTSize));
	MOCK_METHOD0(PassRMS, double());
	MOCK_METHOD1(PassAmpl, double(int Index));
	MOCK_METHOD1(SetCenterSample, void(int CentreSample));

	FFTHandlerMock()
	{
		
	}
};