#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <fltk/Fl_Group.H>
#include "IMenu.h"

using namespace testing;

/////////////////////////MenuMock////////////////////////////////////////////////////////

struct MenuMock : public IMenu
{
	MOCK_METHOD0(GetImplWidget, Fl_Group*());
	MOCK_METHOD1(connect, boost::signals2::connection(const signal_t::slot_type &slot));
	MOCK_METHOD4(SetGeometry, void(int x, int y, int w, int h));
	Fl_Group StubGroup;
	signal_t signal;

	MenuMock() : StubGroup(0, 0, 0, 0)
	{
		ON_CALL(*this, GetImplWidget()).WillByDefault(Return(&StubGroup));
		ON_CALL(*this, connect(_)).WillByDefault(Invoke([this](const signal_t::slot_type &s) { return signal.connect(s); }));
		StubGroup.end();
	}
};