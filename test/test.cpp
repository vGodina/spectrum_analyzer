#include "pch.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "MainWindowTest.h"

using namespace testing;

////////////////////////TESTS////////////////////////////////////////////////////////////

TEST_F(MainWindowTest, ShouldLoadFileByMenuSignal)
{
	// Arrange
	EXPECT_CALL(*AudioTrack, Load("test.wav"));
	//Act
	Menu->signal("test.wav");
};

TEST_F(MainWindowTest, ShouldReportTrueWhenFileIsLoaded)
{
	// Arrange
	ON_CALL(*AudioTrack, Load(_)).WillByDefault(Return(true));

	// Act
	auto result = Menu->signal("test.wav");

	// Assert
	ASSERT_TRUE(result.get());
}

TEST_F(MainWindowTest, ShouldReportFalseWhenFileIsNotLoaded)
{
	// Arrange
	ON_CALL(*AudioTrack, Load(_)).WillByDefault(Return(false));

	// Act
	auto result = Menu->signal("test.wav");

	// Assert
	ASSERT_FALSE(result.get());
}

TEST_F(MainWindowTest, ShouldReportTrueWhenBufferPassedToWaveform)
{
	// Arrange
	ON_CALL(*AudioTrack, Load(_)).WillByDefault(Return(true));
	EXPECT_CALL(*Waveform, TakeAudioData(AudioTrack->stubBuffer));

	// Act
	Menu->signal("test.wav");
}

TEST_F(MainWindowTest, ShouldReportFalseWhenBufferNotPassedToWaveform)
{	
	// Arrange
	ON_CALL(*AudioTrack, Load(_)).WillByDefault(Return(false));
	EXPECT_CALL(*Waveform, TakeAudioData(_)).Times(0);
	
	// Act
	Menu->signal("test.wav");
}

TEST_F(MainWindowTest, SliderHandlerIsCalled)
{	
	// Arrange
	EXPECT_CALL(*AudioTrack, IsLoaded());

	// Act
	Waveform->signal(0.0);
}

TEST_F(MainWindowTest, SliderPositionReceivesRightValue)
{	
	// Arrange
	ON_CALL(*AudioTrack, IsLoaded()).WillByDefault(Return(true));
	EXPECT_CALL(*AudioTrack, GetLength()).WillOnce(Return(100));
	EXPECT_CALL(*Spectrum, SetPosition(60));

	// Act
	Waveform->signal(0.6);
}

TEST_F(MainWindowTest, SliderPositionReceivesWrongValue)
{	
	// Arrange
	ON_CALL(*AudioTrack, IsLoaded()).WillByDefault(Return(true));
	EXPECT_CALL(*AudioTrack, GetLength()).WillOnce(Return(0));
	EXPECT_CALL(*Spectrum, SetPosition(Matcher<int>(Ne(60))));

	// Act
	Waveform->signal(0.6);
}

/////////////////////////main///////////////////////////////////////////////////////////
int main(int argc, char **argv) {
	testing::InitGoogleMock(&argc, argv);
	return RUN_ALL_TESTS();
}