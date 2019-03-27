#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Menu.h"
#include "AudioFileMock.h"

using namespace testing;

/////////////////////////MenuTest fixture//////////////////////////////////////////

struct MenuTest : public Test
{
	MenuTest() :
		AudioTrack(new NiceMock<AudioFileMock<float>>),
		MainMenu(std::make_unique<Menu>())
	{
	}

	AudioFileMock<float>* AudioTrack;
	std::unique_ptr<Menu> MainMenu;

	void TearDown() override
	{
		delete AudioTrack;
	}
};