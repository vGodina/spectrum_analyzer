#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Menu.h"
#include "AudioFileMock.h"

using namespace testing;

/////////////////////////MenuTest fixture//////////////////////////////////////////

struct MenuTest : public Test
{
	MenuTest() :
		AudioTrack(new NiceMock<AudioFileMock<float>>)
		//MainMenu(std::make_unique<Menu>())
	{
		/*
		auto MenuGroup = std::make_unique<Fl_Group>(30, 30, 100, 30);
		auto FileChooser = std::make_unique<RFileChooser>();
		auto OpenMenuButton = std::make_unique<RButton>(30, 30, 100, 30, "Open .wav file");
		auto MainMenu = std::make_unique<Menu>(std::move(MenuGroup), std::move(FileChooser), std::move(OpenMenuButton));
		*/
	}

	AudioFileMock<float>* AudioTrack;
	//std::unique_ptr<Menu> MainMenu;

	void TearDown() override
	{
		delete AudioTrack;
	}
};