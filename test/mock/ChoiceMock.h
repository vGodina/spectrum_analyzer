#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <fltk/Fl_Widget.H>
#include "IChoice.h"
#include <string_view>

using namespace testing;

/////////////////////////ChoiceMock////////////////////////////////////////////////////////

struct ChoiceMock : public IChoice
{
	MOCK_METHOD0(GetImplWidget, Fl_Widget* ());
	MOCK_METHOD2(callback, void (Fl_Callback*, void*));
	MOCK_CONST_METHOD0(value, int ());
	MOCK_METHOD1(value, int (int v));
	MOCK_METHOD1(add, int (std::string_view v));

	Fl_Widget* WidgetPtr;

	ChoiceMock()
	{
		ON_CALL(*this, GetImplWidget()).WillByDefault(Return(WidgetPtr));
	}
};