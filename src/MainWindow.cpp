#include "MainWindow.h"
#include <string>

MainWindow::MainWindow(int w, int h, const char* title) : Fl_Window(w, h, title),
	OpenButton(std::make_unique<Fl_Button>(30, 30, 100, 30, "Open .wav file")),
	FileInfo(std::make_unique<Fl_Box>(200, 30, 220, 30, "000")),
	Chooser(std::make_unique<Fl_Native_File_Chooser>()),
	WaveformChart(std::make_unique<Fl_Chart>(20, 100, 500, 200)),
	SpectrumChart(std::make_unique<Fl_Chart>(20, 360, 500, 200)),
	LevelMeter(std::make_unique<Fl_Chart>(520, 360, 10,200)),
	SizeFFT(std::make_unique<Fl_Choice>(420, 560, 100, 22, "FFT Size:")),
	Slider(std::make_unique<Fl_Slider>(20,300,500,20)),
	ZoomOutH(std::make_unique<Fl_Button>(20, 322, 25, 25, "-")),
	ZoomInH(std::make_unique<Fl_Button>(47, 322, 25, 25, "+")),
	ZoomOutV(std::make_unique<Fl_Button>(522, 127, 25, 25, "-")),
	ZoomInV(std::make_unique<Fl_Button>(522, 100, 25, 25, "+")),
	AudioTrack(std::make_unique<AudioFile<float>>()),
	FFT(std::make_unique<audiofft::AudioFFT>())
{
	begin();
	OpenButton->callback(CbOpenButton, this);
	ZoomInH->callback(CbZoomInH, this);
	ZoomOutH->callback(CbZoomOutH, this);
	Slider->callback(CbSlider, this);
	ZoomInV->callback(CbZoomInV, this);
	ZoomOutV->callback(CbZoomOutV, this);
	SizeFFT->callback(CbSizeFFT, this);

	// Initialization of  widgets
	WaveformChart->color(FL_WHITE);
	WaveformChart->type(FL_LINE_CHART);
	SpectrumChart->color(FL_WHITE);
	SpectrumChart->type(FL_LINE_CHART);
	LevelMeter->type(FL_BAR_CHART);
	LevelMeter->color(FL_GREEN);
	LevelMeter->bounds(-120.0, 0.0);
	LevelMeter->add(-120);
	Chooser->filter("*.wav");
	Slider->type(FL_HORIZONTAL);
	Slider->slider_size(1);
	Slider->value(0.5);

	for (int i = 8; i < 20; i++)
	{
		std::string Length = std::to_string(2<<i);
		SizeFFT->add(Length.c_str());
	}
	SizeFFT->value(0);
	end();
	resizable(this);
	show();
}

MainWindow::~MainWindow() {}

void MainWindow::CbOpenButton(Fl_Widget* OpenButton, void* Obj)
{
	static_cast<MainWindow*>(Obj)->ChooserShow();
}

void MainWindow::VerticalScale(float VertFactor = 1.0, bool ClearChart = TRUE)
{
	double min, max;
	WaveformChart->bounds(&min, &max);
	if (ClearChart) WaveformChart->clear();
	WaveformChart->bounds(min * VertFactor, max * VertFactor);
}

void MainWindow::ChartRedraw(float ZoomFactor = 1.0)
{
	constexpr int ChartLength = 1024;
	float SliderSize = ZoomFactor * Slider->slider_size();
	float SliderValue = static_cast<float>(Slider->value());
	int AudioLength = AudioTrack->getNumSamplesPerChannel();
	// resize Slider size
	Slider->slider_size(SliderSize);
	if (Slider->slider_size() == 1) Slider->value(0.5);
	// keep Chart bounds with no changes
	VerticalScale();
	// Center value of Slider
	float Center = SliderValue - SliderValue * SliderSize + SliderSize / 2;
	int VisibleSamples = AudioLength * SliderSize;

	int StartSample = Center * AudioLength - VisibleSamples / 2;
	int Delta = VisibleSamples;
	int Decimation = 1;
	if (VisibleSamples > ChartLength)
	{
		Delta = ChartLength;
		Decimation = VisibleSamples / ChartLength;
	}
	for (int i = 0; i < Delta; i++)
	{
		double val = AudioTrack->samples[0][StartSample + i * Decimation];
		WaveformChart->add(val);
	}
	DoFFT();
}

void MainWindow::DoFFT()
{
	constexpr int ChartLength = 1024;
	SpectrumChart->clear();
	SpectrumChart->bounds(-120.0, 0.0); 
	// Get FFT size from Fl_Choice widget
	int FFTSize = 2 << (SizeFFT->value() + 8);
	// Set choosed FFT size lower than file size and set Fl_Widget to actual
	while (FFTSize > AudioTrack->getNumSamplesPerChannel())
	{
		FFTSize /= 2;
		SizeFFT->value(SizeFFT->value() - 1);
	}
	
	int N = FFTSize / 2;
	
	FFT->init(FFTSize);
	// Finding start sample from which FFT will be performed.  
	// Center of selection to be FFT-ed matches the center of waveform slider
	float SliderSize = Slider->slider_size();
	float SliderValue = static_cast<float>(Slider->value());
	int AudioLength = AudioTrack->getNumSamplesPerChannel();
	float Center = SliderValue - SliderValue * SliderSize + SliderSize / 2;
	int StartSample = Center * AudioLength - FFTSize / 2;
	// Limiting StartSample addressing to file size
	if (StartSample < 0) StartSample = 0;
	if (StartSample > (AudioLength - FFTSize)) StartSample = AudioLength - FFTSize;
	
	/*
	std::unique_ptr<float[]> Input = std::make_unique<float[]>(FFTSize);
	std::unique_ptr<float[]> Re = std::make_unique<float[]>(N + 1);
	std::unique_ptr<float[]> Im = std::make_unique<float[]>(N + 1);
	*/

	float* Input = new float[FFTSize];
	float* Re = new float[N + 1];
	float* Im = new float[N + 1];
	
	for (unsigned int i = 0; i < FFTSize; i++)
	{
		Input[i] = static_cast<float>(AudioTrack->samples[0][i + StartSample]);
	}
	
	FFT->fft(Input, Re, Im);

	float* Ampl = new float[N + 1];
	float RMS = 0.0F;
	float tAmpl2 = 0.0F; //square of Amplitude
	float Norm = 1 / pow(static_cast<float>(N), 2);
	/*int Decimation = 1;
	if (FFTSize > ChartLength) Decimation = FFTSize / ChartLength;*/
	for (unsigned int n = 0, i = 0; n < N + 1; n++)	
	{
		//Calculating normalized square of amplitude Ak
		tAmpl2 = (Re[n] * Re[n] + Im[n] * Im[n]) * Norm;
		RMS += tAmpl2;
		// log scale of Ak.
		Ampl[n] = 10 * log10(tAmpl2);
		/* 
		i++;
		i %= Decimation;
		if (i == 0)*/
		SpectrumChart->add(Ampl[n]);
	}

	// showing RMS level at LevelMeter widget
	RMS = 10 * log10(RMS / 2);
	LevelMeter->clear();
	LevelMeter->bounds(-120.0, 0.0);
	LevelMeter->add(RMS);
	delete[] Input;
	delete[] Re;
	delete[] Im;
	delete[] Ampl;
}

void MainWindow::CbZoomInH(Fl_Widget* ZoomIn, void* Obj)
{
	static_cast<MainWindow*>(Obj)->ChartRedraw(0.5);
}

void MainWindow::CbZoomOutH(Fl_Widget* ZoomOutH, void* Obj)
{
	MainWindow* win = static_cast<MainWindow*>(Obj);
	if (win->Slider->slider_size() < 1) win->ChartRedraw(2);
}

void MainWindow::CbZoomInV(Fl_Widget* ZoomInV, void* Obj)
{
	MainWindow* win = static_cast<MainWindow*>(Obj);
	win->VerticalScale(0.5, FALSE);
	win->WaveformChart->redraw();
}

void MainWindow::CbZoomOutV(Fl_Widget* ZoomOutV, void* Obj)
{
	MainWindow* win = static_cast<MainWindow*>(Obj);
	win->VerticalScale(2, FALSE);
	win->WaveformChart->redraw();
}

void MainWindow::CbSizeFFT(Fl_Widget* SizeFFT, void* Obj)
{
	MainWindow* win = static_cast<MainWindow*>(Obj);
	win->DoFFT();
}

void MainWindow::CbSlider(Fl_Widget* ZoomOut, void* Obj)
{
	static_cast<MainWindow*>(Obj)->ChartRedraw();
}

void MainWindow::ChooserShow()
{
	Chooser->show();
	AudioTrack->load(Chooser->filename());

	std::string FileDuration = std::to_string(AudioTrack->getLengthInSeconds());
	std::string LabelMessage = "File duration: " + FileDuration + " seconds";
	FileInfo->copy_label(LabelMessage.c_str());
	FileInfo->redraw();

	Slider->slider_size(1);
	WaveformChart->clear();
	WaveformChart->bounds(-1, 1);
	SpectrumChart->clear();
	ChartRedraw();
}