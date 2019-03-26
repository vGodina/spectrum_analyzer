////////////////////////alternative to MainWindowTest fixture////////////////////////////
struct MWHarness {
	MenuMock* Menu;
	WaveFormMock* Waveform;
	SpectrumFormMock* Spectrum;
	AudioFileMock<float>* AudioTrack;
	std::unique_ptr<MainWindow> BaseWindow;
};

MWHarness CreateHarness()
{
	MWHarness h;

	auto mm = std::make_unique<NiceMock<MenuMock>>();
	auto wf = std::make_unique<NiceMock<WaveFormMock>>();
	auto sf = std::make_unique<NiceMock<SpectrumFormMock>>();
	auto at = std::make_unique<NiceMock<AudioFileMock<float>>>();

	h.Menu = mm.get();
	h.Waveform = wf.get();
	h.Spectrum = sf.get();
	h.AudioTrack = at.get();

	h.BaseWindow = std::make_unique<MainWindow>
		(600, 600, "Spectrum Analyzer", std::move(mm), std::move(wf), std::move(sf), std::move(at));
	return h;
}