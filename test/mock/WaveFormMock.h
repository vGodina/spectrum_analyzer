#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <fltk/Fl_Group.H>
#include "IWaveForm.h"

using namespace testing;

/////////////////////////WaveFormMock////////////////////////////////////////////////////

struct WaveFormMock : public IWaveForm
{
	MOCK_METHOD0(GetImplWidget, Fl_Widget*());
	MOCK_METHOD1(connect, boost::signals2::connection(const signal_t::slot_type &slot));
	MOCK_METHOD1(TakeAudioData, bool(const IAudioFile<float>::AudioBuffer &AudioData));

	Fl_Group StubGroup;
	signal_t signal;

	WaveFormMock() : StubGroup(0, 0, 0, 0)
	{
		ON_CALL(*this, GetImplWidget()).WillByDefault(Return(&StubGroup));
		ON_CALL(*this, connect(_)).WillByDefault(Invoke([this](const signal_t::slot_type &s) { return signal.connect(s); }));
		StubGroup.end();
	}
};