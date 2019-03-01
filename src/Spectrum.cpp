#include <fltk/Fl_Double_Window.H>
#include "Fl_AudioFile.h"
#include "Spectrum.h"

Spectrum::Spectrum():
	SpectrumChart(std::make_unique<Fl_Chart>(20, 360, 500, 200)),
	LevelMeter(std::make_unique<Fl_Chart>(520, 360, 10, 200)),
	SizeFFT(std::make_unique<Fl_Choice>(420, 560, 100, 22, "FFT Size:")),
	FFT(std::make_unique<audiofft::AudioFFT>())
{

	SizeFFT->callback(CbSizeFFT, this);
	SpectrumChart->color(FL_WHITE);
	SpectrumChart->type(FL_LINE_CHART);
	LevelMeter->type(FL_BAR_CHART);
	LevelMeter->color(FL_GREEN);
	LevelMeter->bounds(-120.0, 0.0);
	LevelMeter->add(-120);
	for (int i = 8; i < 20; i++)
	{
		std::string Length = std::to_string(2 << i);
		SizeFFT->add(Length.c_str());
	}
	SizeFFT->value(0);
}

Spectrum::~Spectrum() {}

void Spectrum::CbSizeFFT(Fl_Widget* SizeFFT, void* Obj)
{
	// Get pointer to Group and Window
	Fl_Widget* Widget = static_cast<Fl_Widget*>(SizeFFT);
	Fl_Double_Window* Window = static_cast<Fl_Double_Window*>(Widget->parent());
	Fl_AudioFile* AudioTrack = static_cast<Fl_AudioFile*>(Window->child(0));
	static_cast<Spectrum*>(Obj)->DoFFT(AudioTrack->GetAudio());
}

void Spectrum::DoFFT(std::shared_ptr<AudioFile<float>> AudioTrack)
{
	SpectrumChart->clear();
	SpectrumChart->bounds(-120.0, 0.0);
	// Get FFT size from Fl_Choice widget
	int FFTSize = 2 << (SizeFFT->value() + 8);
	// Set choosed FFT size lower than file size and set Chooser to actual
	while (FFTSize > AudioTrack->getNumSamplesPerChannel())
	{
		FFTSize /= 2;
		SizeFFT->value(SizeFFT->value() - 1);
	}

	int N = FFTSize / 2;

	FFT->init(FFTSize);
	// Finding start sample from which FFT will be performed.  
	// Center of selection to be FFT-ed matches the center of waveform slider
	float SliderSize = 0.5; // Slider->slider_size();
	float SliderValue = static_cast<float>(0.5);// (Slider->value());
	int AudioLength = AudioTrack->getNumSamplesPerChannel();
	float Center = SliderValue - SliderValue * SliderSize + SliderSize / 2;
	int StartSample = Center * AudioLength - FFTSize / 2;
	// Limiting StartSample addressing to file size
	if (StartSample < 0) StartSample = 0;
	if (StartSample > (AudioLength - FFTSize)) StartSample = AudioLength - FFTSize;

	std::vector<float> Re(N + 1);
	std::vector<float> Im(N + 1);
	std::vector<float> Ampl(N + 1);
	FFT->fft(&AudioTrack->samples[0][StartSample], Re.data(), Im.data());

	float RMS = 0.0F;
	float Ampl2 = 0.0F; //square of Amplitude
	float Norm = 1 / pow(N, 2);
	for (int n = 0; n < N + 1; n++)
	{
		//Calculating normalized square of amplitude Ak
		Ampl2 = (Re[n] * Re[n] + Im[n] * Im[n]) * Norm;
		RMS += Ampl2;
		// log scale of Ak.
		Ampl[n] = 10.0F * log10(Ampl2);
		SpectrumChart->add(Ampl[n]);
	}
	// showing RMS level at LevelMeter widget
	RMS = 10 * log10(RMS / 2);
	LevelMeter->clear();
	LevelMeter->bounds(-120.0, 0.0);
	LevelMeter->add(RMS);
}