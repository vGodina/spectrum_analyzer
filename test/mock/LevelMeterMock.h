#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <fltk/Fl_Widget.H>
#include "ILevelMeter.h"

using namespace testing;

/////////////////////////ButtonMock////////////////////////////////////////////////////////

struct LevelMeterMock : public ILevelMeter
{
	MOCK_METHOD0(GetImplWidget, Fl_Widget*());
	MOCK_METHOD1(Set, void(double v));

	Fl_Widget* WidgetPtr;

	LevelMeterMock()
	{
		ON_CALL(*this, GetImplWidget()).WillByDefault(Return(WidgetPtr));
	}
};