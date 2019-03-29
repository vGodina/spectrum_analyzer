#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <fltk/Fl_Widget.H>
#include "ICustomSlider.h"

using namespace testing;

/////////////////////////ButtonMock////////////////////////////////////////////////////////

struct CustomSliderMock : public ICustomSlider
{
	MOCK_METHOD1 (connect, boost::signals2::connection(const signal_t::slot_type &slot));
	MOCK_METHOD0 (GetImplWidget, Fl_Widget*());
	MOCK_METHOD2 (callback, void(Fl_Callback*, void*));
	MOCK_METHOD0 (Reset, void());
	MOCK_METHOD1 (Resize, void(double ZoomFactor));
	MOCK_METHOD0 (EmitSignal, void());
	MOCK_METHOD0 (slider_size, float());
	MOCK_METHOD0 (GetStartValue, double());

	Fl_Widget* WidgetPtr;
	signal_t signal;

	CustomSliderMock()
	{
		ON_CALL(*this, GetImplWidget()).WillByDefault(Return(WidgetPtr));
		ON_CALL(*this, connect(_)).WillByDefault(Invoke([this](const signal_t::slot_type &s) { return signal.connect(s); }));
	}
};