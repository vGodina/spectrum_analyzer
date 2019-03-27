#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <fltk/Fl_Group.H>
#include "IMenu.h"

using namespace testing;

/////////////////////////MenuMock////////////////////////////////////////////////////////

struct MenuMock : public IMenu
{
	MOCK_METHOD0(getImplWidget, Fl_Group*());
	MOCK_METHOD1(connect, boost::signals2::connection(const signal_t::slot_type &slot));

	Fl_Group StubGroup;
	signal_t signal;

	MenuMock() : StubGroup(0, 0, 0, 0)
	{
		ON_CALL(*this, getImplWidget()).WillByDefault(Return(&StubGroup));
		ON_CALL(*this, connect(_)).WillByDefault(Invoke([this](const signal_t::slot_type &s) { return signal.connect(s); }));
		StubGroup.end();
	}
};