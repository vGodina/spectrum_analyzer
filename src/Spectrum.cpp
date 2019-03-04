#include <audiofile/AudioFile.h>
#include <string>
#include <vector>
#include "Spectrum.h"

Spectrum::Spectrum():
	SpectrumChart(20, 360, 500, 200),
	LevelMeter(520, 360, 10, 200),
	FFTChoice(420, 560, 100, 22, "FFT Size:"),
	FFT()
{
	FFTChoice.callback(CbFFTChoice, this);
	// Initialize widgets
	SpectrumChart.color(FL_WHITE);
	SpectrumChart.type(FL_LINE_CHART);
	LevelMeter.type(FL_BAR_CHART);
	LevelMeter.color(FL_GREEN);
	LevelMeter.bounds(-120.0, 0.0);
	LevelMeter.add(-120);
	//creating list of FFTSize values of choice widget
	for (int i = 8; i < 20; i++)
	{
		std::string Length = std::to_string(2 << i);
		FFTChoice.add(Length.c_str());
	}
	FFTChoice.value(0);
	FFTSize = 2 << (FFTChoice.value() + 8);
}

void Spectrum::CbFFTChoice(Fl_Widget* SizeFFT, void* Obj)
{
	static_cast<Spectrum*>(Obj)->InitFFT();
	static_cast<Spectrum*>(Obj)->Draw();
}

void Spectrum::Show(const AudioFile<float>& AudioTrk)
{
	AudioTrack = &AudioTrk;
	InitFFT();
	Draw();
}

void Spectrum::InitFFT()
{
	// Verify FFTChoice, initialize FFT object and reassign FFTSize
	if (AudioTrack)
	{
		int temp = 2 << (FFTChoice.value() + 8);
		while (temp > AudioTrack->getNumSamplesPerChannel())
		{
			temp /= 2;
			FFTChoice.value(FFTChoice.value() - 1);
		}
		FFTSize = temp;
		FFT.init(FFTSize);
	}
}

void Spectrum::Draw()
{
	if (AudioTrack)
	{
		SpectrumChart.clear();
		SpectrumChart.bounds(-120.0, 0.0);
		int N = FFTSize / 2;
		// Finding start sample from which FFT will be performed.  
		// Center of selection to be FFT-ed matches the center of waveform slider
		//float SliderSize = 0.5; // Slider->slider_size();
		//float SliderValue = static_cast<float>(0.5);// (Slider->value());
		int AudioLength = AudioTrack->getNumSamplesPerChannel();
		float Center = SliderValue - SliderValue * SliderSize + SliderSize / 2;
		int StartSample = Center * AudioLength - FFTSize / 2;
		// Limiting StartSample addressing to file size
		if (StartSample < 0)
			StartSample = 0;
		if (StartSample > (AudioLength - FFTSize))
			StartSample = AudioLength - FFTSize;

		std::vector<float> Re(N + 1);
		std::vector<float> Im(N + 1);
		std::vector<float> Ampl(N + 1);
		FFT.fft(&AudioTrack->samples[0][StartSample], Re.data(), Im.data());

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
			SpectrumChart.add(Ampl[n]);
		}
		// showing RMS level at LevelMeter widget
		RMS = 10.0 * log10(RMS / 2);
		LevelMeter.clear();
		LevelMeter.bounds(-120.0, 0.0);
		LevelMeter.add(RMS);
	}
}

void Spectrum::SetSliderSize(double SliderSz)
{
	SliderSize = SliderSz;
}

void Spectrum::SetSliderValue(double SliderVal)
{
	SliderValue = SliderVal;
}