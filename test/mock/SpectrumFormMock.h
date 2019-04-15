#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <fltk/Fl_Group.H>
#include "ISpectrum.h"

using namespace testing;

/////////////////////////SpectrumFormMock////////////////////////////////////////////////

struct SpectrumFormMock : public ISpectrum
{
	MOCK_METHOD0(GetImplWidget, Fl_Widget*());
	MOCK_METHOD1(SetAudioData, bool(const IAudioFile<float>::AudioBuffer &AudioData));
	MOCK_METHOD1(SetPosition, bool(int));
	Fl_Group StubGroup;

	SpectrumFormMock() : StubGroup(0, 0, 0, 0)
	{
		ON_CALL(*this, GetImplWidget()).WillByDefault(Return(&StubGroup));
		StubGroup.end();
	}
};