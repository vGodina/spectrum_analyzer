#include "pch.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "AudioFileTest.h"


TEST_F(AudioFileTest, ExpectFileLoadCallByMenuSignal)
{
	auto result = Menu->signal("C:\\Users\\Vladimir_Godina\\source\\repos\\.git\\spectrum_analyzer\\TestData\\test.wav");
	EXPECT_TRUE(result.get());
};

TEST_F(AudioFileTest, ExpectFileNotLoadedByMenuSignal)
{
	auto result = Menu->signal("*.wav");
	EXPECT_FALSE(result.get());
};

TEST_F(AudioFileTest, IsLoadedTrueWhenFileLoaded)
{
	AudioTrack->Load("C:\\Users\\Vladimir_Godina\\source\\repos\\.git\\spectrum_analyzer\\TestData\\test.wav");
	EXPECT_TRUE(AudioTrack->IsLoaded());
};

TEST_F(AudioFileTest, IsLoadedFalseWhenFileNotLoaded)
{
	AudioTrack->Load("*.wav");
	EXPECT_FALSE(AudioTrack->IsLoaded());
};

TEST_F(AudioFileTest, GetLengthReturnsProperValue)
{
	AudioTrack->Load("C:\\Users\\Vladimir_Godina\\source\\repos\\.git\\spectrum_analyzer\\TestData\\test.wav");
	EXPECT_EQ(AudioTrack->GetLength(), AudioTrack->PassData()[0].size());
};

TEST_F(AudioFileTest, GetLengthReturnsZeroValue)
{
	EXPECT_EQ(AudioTrack->GetLength(), 0);
};