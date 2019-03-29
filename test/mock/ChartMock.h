#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <fltk/Fl_Widget.H>
#include "IChart.h"

using namespace testing;

/////////////////////////ButtonMock////////////////////////////////////////////////////////

struct ChartMock : public IChart
{
	MOCK_METHOD0(GetImplWidget, Fl_Widget*());
	MOCK_METHOD1(color, void(Fl_Color bg));
	MOCK_METHOD1(type, void(uchar t));
	MOCK_METHOD0(clear, void());
	MOCK_METHOD2(bounds, void(double min, double max));
	MOCK_METHOD2(bounds, void(double* min, double* max));
	MOCK_METHOD1(add, void(double val));

	Fl_Widget* WidgetPtr;

	ChartMock()
	{
		ON_CALL(*this, GetImplWidget()).WillByDefault(Return(WidgetPtr));
	}
};