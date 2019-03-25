#include "pch.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
//#include <boost/signals2.hpp>
#include "MainWindow.h"
#include "IAudioFile.h"
#include "IMenu.h"
#include "IWaveForm.h"
#include "ISpectrum.h"

using namespace testing;

/////////////////////////AudioFileMock//////////////////////////////////////////////////

template <typename T>
class AudioFileMock : public IAudioFile<T> {
public:
	MOCK_CONST_METHOD0_T(IsLoaded, bool());
	MOCK_METHOD1_T(Load, bool(std::string FileName));
	MOCK_CONST_METHOD0_T(GetLength, int());
	MOCK_CONST_METHOD0_T(PassData, IAudioFile<T>::AudioBuffer&());

	IAudioFile<T>::AudioBuffer stubBuffer;

	AudioFileMock() {
		ON_CALL(*this, PassData()).WillByDefault(ReturnRef(stubBuffer));
	}
};

/////////////////////////MenuMock///////////////////////////////////////////////////////

class MenuMock : public IMenu {
public:
	MOCK_METHOD0(getImplWidget, Fl_Group*());
	MOCK_METHOD1(connect, boost::signals2::connection(const signal_t::slot_type &slot));

	Fl_Group StubGroup;
	signal_t signal;

	MenuMock() : StubGroup(0, 0, 0, 0) {
		ON_CALL(*this, getImplWidget()).WillByDefault(Return(&StubGroup));
		ON_CALL(*this, connect(_)).WillByDefault(Invoke([this](const signal_t::slot_type &s) { return signal.connect(s); }));

	}
};

/////////////////////////WaveFormMock///////////////////////////////////////////////////

class WaveFormMock : public IWaveForm {
public:
	MOCK_METHOD0(getImplWidget, Fl_Widget*());
	MOCK_METHOD1(connect, boost::signals2::connection (const signal_t::slot_type &slot));
	MOCK_METHOD1(TakeAudioData, bool (const IAudioFile<float>::AudioBuffer &AudioData));

	Fl_Group StubGroup;
	signal_t signal;

	WaveFormMock() : StubGroup(0, 0, 0, 0) {
		ON_CALL(*this, getImplWidget()).WillByDefault(Return(&StubGroup));
		ON_CALL(*this, connect(_)).WillByDefault(Invoke([this](const signal_t::slot_type &s) { return signal.connect(s); }));
	}
};

/////////////////////////SpectrumFormMock///////////////////////////////////////////////

class SpectrumFormMock : public ISpectrum {
public:
	MOCK_METHOD0(getImplWidget, Fl_Widget*());
	MOCK_METHOD1(TakeAudioData, bool(const IAudioFile<float>::AudioBuffer &AudioData));
	MOCK_METHOD1(SetPosition, bool(int));
	Fl_Group StubGroup;

	SpectrumFormMock() : StubGroup(0, 0, 0, 0) {
		ON_CALL(*this, getImplWidget()).WillByDefault(Return(&StubGroup));
	}
};
/*
class MainWindowTest : public Test {
public:
	void SetUp() {
		auto MainMenu = std::make_unique<NiceMock<MenuMock>>();
		auto WaveFrm = std::make_unique<NiceMock<WaveFormMock>>();
		auto SpectrFrm = std::make_unique<NiceMock<SpectrumFormMock>>();
		auto AudioTrack = std::make_unique<NiceMock<AudioFileMock<float>>>();

		auto mm = MainMenu.get();
		auto at = AudioTrack.get();
		auto wf = WaveFrm.get();
		auto sf = SpectrFrm.get();

		MainWindow BaseWindow(600, 600, "Spectrum Analyzer", std::move(MainMenu), std::move(WaveFrm), std::move(SpectrFrm), std::move(AudioTrack));
	}
	MainWindow* BaseWindow;
	MenuMock* mm;
	WaveFormMock* wf;
	SpectrumFormMock* sf;
	AudioFileMock<float>* af;
};
*/
TEST(MainWindow, ShouldLoadFileByMenuSignal) {
	// Arrange

	auto MainMenu = std::make_unique<NiceMock<MenuMock>>();
	auto WaveFrm = std::make_unique<NiceMock<WaveFormMock>>();
	auto SpectrFrm = std::make_unique<NiceMock<SpectrumFormMock>>();
	auto AudioTrack = std::make_unique<NiceMock<AudioFileMock<float>>>();

	auto mm = MainMenu.get();
	auto at = AudioTrack.get();
	auto wf = WaveFrm.get();
	auto sf = SpectrFrm.get();

	MainWindow BaseWindow(600, 600, "Spectrum Analyzer", std::move(MainMenu), std::move(WaveFrm), std::move(SpectrFrm), std::move(AudioTrack));

	EXPECT_CALL(*at, Load("test.wav"));

	// Act
	mm->signal("test.wav");
	// Assert
}

TEST(MainWindow, ShouldReportTrueWhenFileIsLoaded) {
	// Arrange

	auto MainMenu = std::make_unique<NiceMock<MenuMock>>();
	auto WaveFrm = std::make_unique<NiceMock<WaveFormMock>>();
	auto SpectrFrm = std::make_unique<NiceMock<SpectrumFormMock>>();
	auto AudioTrack = std::make_unique<NiceMock<AudioFileMock<float>>>();

	auto mm = MainMenu.get();
	auto at = AudioTrack.get();
	auto wf = WaveFrm.get();
	auto sf = SpectrFrm.get();

	MainWindow BaseWindow(600, 600, "Spectrum Analyzer", std::move(MainMenu), std::move(WaveFrm), std::move(SpectrFrm), std::move(AudioTrack));

	ON_CALL(*at, Load(_)).WillByDefault(Return(true));

	// Act
	auto result = mm->signal("test.wav");

	// Assert
	ASSERT_TRUE(result.get());
}

TEST(MainWindow, ShouldReportFalseWhenFileIsNotLoaded) {
	// Arrange

	auto MainMenu = std::make_unique<NiceMock<MenuMock>>();
	auto WaveFrm = std::make_unique<NiceMock<WaveFormMock>>();
	auto SpectrFrm = std::make_unique<NiceMock<SpectrumFormMock>>();
	auto AudioTrack = std::make_unique<NiceMock<AudioFileMock<float>>>();

	auto mm = MainMenu.get();
	auto at = AudioTrack.get();
	auto wf = WaveFrm.get();
	auto sf = SpectrFrm.get();

	MainWindow BaseWindow(600, 600, "Spectrum Analyzer", std::move(MainMenu), std::move(WaveFrm), std::move(SpectrFrm), std::move(AudioTrack));

	ON_CALL(*at, Load(_)).WillByDefault(Return(false));

	// Act
	auto result = mm->signal("test.wav");

	// Assert
	ASSERT_FALSE(result.get());
}

TEST(MainWindow, ShouldReportTrueWhenBufferPassedToWaveform) {
	// Arrange

	auto MainMenu = std::make_unique<NiceMock<MenuMock>>();
	auto WaveFrm = std::make_unique<NiceMock<WaveFormMock>>();
	auto SpectrFrm = std::make_unique<NiceMock<SpectrumFormMock>>();
	auto AudioTrack = std::make_unique<NiceMock<AudioFileMock<float>>>();

	auto mm = MainMenu.get();
	auto at = AudioTrack.get();
	auto wf = WaveFrm.get();
	auto sf = SpectrFrm.get();

	MainWindow BaseWindow(600, 600, "Spectrum Analyzer", std::move(MainMenu), std::move(WaveFrm), std::move(SpectrFrm), std::move(AudioTrack));

	ON_CALL(*at, Load(_)).WillByDefault(Return(true));
	EXPECT_CALL(*wf, TakeAudioData(at->stubBuffer));
	// Act

	mm->signal("test.wav");
	// Assert
}

TEST(MainWindow, ShouldReportFalseWhenBufferNotPassedToWaveform) {
	// Arrange

	auto MainMenu = std::make_unique<NiceMock<MenuMock>>();
	auto WaveFrm = std::make_unique<NiceMock<WaveFormMock>>();
	auto SpectrFrm = std::make_unique<NiceMock<SpectrumFormMock>>();
	auto AudioTrack = std::make_unique<NiceMock<AudioFileMock<float>>>();

	auto mm = MainMenu.get();
	auto at = AudioTrack.get();
	auto wf = WaveFrm.get();
	auto sf = SpectrFrm.get();

	MainWindow BaseWindow(600, 600, "Spectrum Analyzer", std::move(MainMenu), std::move(WaveFrm), std::move(SpectrFrm), std::move(AudioTrack));

	ON_CALL(*at, Load(_)).WillByDefault(Return(false));
	EXPECT_CALL(*wf, TakeAudioData(_)).Times(0);
	// Act

	mm->signal("test.wav");
	// Assert
}



TEST(MainWindow, SliderHandlerIsCalled) {
	// Arrange

	auto MainMenu = std::make_unique<NiceMock<MenuMock>>();
	auto WaveFrm = std::make_unique<NiceMock<WaveFormMock>>();
	auto SpectrFrm = std::make_unique<NiceMock<SpectrumFormMock>>();
	auto AudioTrack = std::make_unique<NiceMock<AudioFileMock<float>>>();

	auto at = AudioTrack.get();
	auto wf = WaveFrm.get();

	MainWindow BaseWindow(600, 600, "Spectrum Analyzer", std::move(MainMenu), std::move(WaveFrm), std::move(SpectrFrm), std::move(AudioTrack));

	EXPECT_CALL(*at, IsLoaded());
	// Act
	wf->signal(0.0);
	// Assert
}

TEST(MainWindow, SliderPositionReceivesRightValue) {
	// Arrange

	auto MainMenu = std::make_unique<NiceMock<MenuMock>>();
	auto WaveFrm = std::make_unique<NiceMock<WaveFormMock>>();
	auto SpectrFrm = std::make_unique<NiceMock<SpectrumFormMock>>();
	auto AudioTrack = std::make_unique<NiceMock<AudioFileMock<float>>>();

	auto at = AudioTrack.get();
	auto wf = WaveFrm.get();
	auto sf = SpectrFrm.get();

	MainWindow BaseWindow(600, 600, "Spectrum Analyzer", std::move(MainMenu), std::move(WaveFrm), std::move(SpectrFrm), std::move(AudioTrack));
	
	ON_CALL(*at, IsLoaded()).WillByDefault(Return(true));
	EXPECT_CALL(*at, GetLength()).WillOnce(Return(100));
	EXPECT_CALL(*sf, SetPosition(60));
	// Act
	wf->signal(0.6);
	// Assert
}

TEST(MainWindow, SliderPositionReceivesWrongValue) {
	// Arrange

	auto MainMenu = std::make_unique<NiceMock<MenuMock>>();
	auto WaveFrm = std::make_unique<NiceMock<WaveFormMock>>();
	auto SpectrFrm = std::make_unique<NiceMock<SpectrumFormMock>>();
	auto AudioTrack = std::make_unique<NiceMock<AudioFileMock<float>>>();

	auto at = AudioTrack.get();
	auto wf = WaveFrm.get();
	auto sf = SpectrFrm.get();

	MainWindow BaseWindow(600, 600, "Spectrum Analyzer", std::move(MainMenu), std::move(WaveFrm), std::move(SpectrFrm), std::move(AudioTrack));

	ON_CALL(*at, IsLoaded()).WillByDefault(Return(true));
	EXPECT_CALL(*at, GetLength()).WillOnce(Return(0));
	EXPECT_CALL(*sf, SetPosition(Matcher<int>(Ne(60))));
	// Act
	wf->signal(0.6);
	// Assert
}

/////////////////////////main///////////////////////////////////////////////////////////
int main(int argc, char **argv) {
	testing::InitGoogleMock(&argc, argv);
	return RUN_ALL_TESTS();
}