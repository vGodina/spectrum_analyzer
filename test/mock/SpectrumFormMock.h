#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <fltk/Fl_Group.H>
#include "ISpectrum.h"

using namespace testing;

/////////////////////////SpectrumFormMock////////////////////////////////////////////////

struct SpectrumFormMock : public ISpectrum
{
	MOCK_METHOD0(getImplWidget, Fl_Widget*());
	MOCK_METHOD1(TakeAudioData, bool(const IAudioFile<float>::AudioBuffer &AudioData));
	MOCK_METHOD1(SetPosition, bool(int));
	Fl_Group StubGroup;

	SpectrumFormMock() : StubGroup(0, 0, 0, 0)
	{
		ON_CALL(*this, getImplWidget()).WillByDefault(Return(&StubGroup));
		StubGroup.end();
	}
};