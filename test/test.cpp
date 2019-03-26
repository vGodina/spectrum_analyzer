#include "pch.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "MainWindowTest.h"

using namespace testing;

////////////////////////AudioHandler/////////////////////////////////////////////////////

TEST_F(MainWindowTest, AudioTrackLoadCalledByMenuSignal)
{
	// Arrange
	EXPECT_CALL(*AudioTrack, Load(_));

	//Act
	Menu->signal("test.wav");

	//Assert
};

TEST_F(MainWindowTest, AudioTrackReceivedProperNameFromMenuSignal)
{
	
	// Arrange
	EXPECT_CALL(*AudioTrack, Load("test.wav"));

	//Act
	Menu->signal("test.wav");
};

TEST_F(MainWindowTest, SignalsIfReceivedImproperNameFromMenuSignal)
{
	// Arrange

	EXPECT_CALL(*AudioTrack, Load(Matcher<std::string>(Ne("test.wav")))).Times(1);

	//Act
	Menu->signal("test1.wav");
};

TEST_F(MainWindowTest, ShouldReportTrueWhenFileIsLoaded)
{
	ON_CALL(*AudioTrack, Load(_)).WillByDefault(Return(true));
	
	auto result = Menu->signal("test.wav");
	EXPECT_TRUE(result.get());
}

TEST_F(MainWindowTest, ShouldReportFalseWhenFileNotLoaded)
{
	ON_CALL(*AudioTrack, Load(_)).WillByDefault(Return(false));

	auto result = Menu->signal("test.wav");
	EXPECT_FALSE(result.get());
}

TEST_F(MainWindowTest, WaveformCalledFromAudioHandler)
{
	ON_CALL(*AudioTrack, Load(_)).WillByDefault(Return(true));
	EXPECT_CALL(*Waveform, TakeAudioData(_));

	Menu->signal("test.wav");
}

TEST_F(MainWindowTest, WaveformTakesProperAudioBuffer)
{
	ON_CALL(*AudioTrack, Load(_)).WillByDefault(Return(true));
	EXPECT_CALL(*Waveform, TakeAudioData(AudioTrack->stubBuffer));

	Menu->signal("test.wav");
}

TEST_F(MainWindowTest, SliderHandlerCalledFromAudioHandler)
{
	ON_CALL(*AudioTrack, Load(_)).WillByDefault(Return(true));
	EXPECT_CALL(*AudioTrack, IsLoaded());

	Menu->signal("test.wav");
}

TEST_F(MainWindowTest, SliderHandlerNotCalledFromAudioHandler)
{
	ON_CALL(*AudioTrack, Load(_)).WillByDefault(Return(false));
	EXPECT_CALL(*AudioTrack, IsLoaded()).Times(0);

	Menu->signal("test.wav");
}

////////////////////////SliderHandler////////////////////////////////////////////////////

TEST_F(MainWindowTest, ShouldReturnTrueIfSliderHandlerCalledByWaveformSignal)
{
	ON_CALL(*AudioTrack, IsLoaded()).WillByDefault(Return(true));

	auto result = Waveform->signal(0.5);
	EXPECT_TRUE(result.get());
};

TEST_F(MainWindowTest, ShouldReturnFalseIfSliderHandlerNotCalledByWaveformSignal)
{
	ON_CALL(*AudioTrack, IsLoaded()).WillByDefault(Return(false));

	auto result = Waveform->signal(0.5);
	EXPECT_FALSE(result.get());
};

TEST_F(MainWindowTest, SliderPositionReceivesRightValue)
{	
	ON_CALL(*AudioTrack, IsLoaded()).WillByDefault(Return(true));
	EXPECT_CALL(*AudioTrack, GetLength()).WillOnce(Return(100));
	EXPECT_CALL(*Spectrum, SetPosition(60));

	Waveform->signal(0.6);
}

TEST_F(MainWindowTest, SliderPositionReceivesWrongValue)
{	
	ON_CALL(*AudioTrack, IsLoaded()).WillByDefault(Return(true));
	EXPECT_CALL(*AudioTrack, GetLength()).WillOnce(Return(0));
	EXPECT_CALL(*Spectrum, SetPosition(Matcher<int>(Ne(60))));

	Waveform->signal(0.6);
}

/////////////////////////main///////////////////////////////////////////////////////////
int main(int argc, char **argv) {
	testing::InitGoogleMock(&argc, argv);
	return RUN_ALL_TESTS();
}
