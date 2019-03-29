#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <fltk/Fl_Widget.H>
#include "IButton.h"

using namespace testing;

/////////////////////////ButtonMock////////////////////////////////////////////////////////

struct ButtonMock : public IButton
{
	MOCK_METHOD0(GetImplWidget, Fl_Widget*());
	MOCK_METHOD2(callback, void(Fl_Callback*, void*));

	Fl_Widget* WidgetPtr;

	ButtonMock()
	{
		ON_CALL(*this, GetImplWidget()).WillByDefault(Return(WidgetPtr));
	}
};