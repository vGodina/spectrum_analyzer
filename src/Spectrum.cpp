#include <string>
#include <vector>
#include "Spectrum.h"

Spectrum::Spectrum():
	SpectrumChart(20, 360, 500, 200),
	FFTChoice(420, 560, 100, 22, "FFT Size:"),
	FFT(),
	LMeter()
{
	FFTChoice.callback(CbFFTChoice, this);
	// Initialize widgets
	SpectrumChart.color(FL_WHITE);
	SpectrumChart.type(FL_LINE_CHART);
	// Generating list of Choice widget's FFTSize values from 2^8 to 2^20 
	for (int i = 8; i < 20; i++)
	{
		std::string Length = std::to_string(2 << i);
		FFTChoice.add(Length.c_str());
	}
	FFTChoice.value(0);
	FFTSize = 2 << (FFTChoice.value() + 8);
	Spectrum::CenterSample = 0;
}

void Spectrum::CbFFTChoice(Fl_Widget* SizeFFT, void* Obj)
{
	static_cast<Spectrum*>(Obj)->InitFFT();
	static_cast<Spectrum*>(Obj)->Draw();
}

int Spectrum::GetAudio(const IAudioFile<float>::AudioBuffer* AudioTrk)
{
	AudioTrack = AudioTrk;
	InitFFT();
	Draw();
	return (*AudioTrack)[0].size();
}

void Spectrum::InitFFT()
{
	// Verify FFTChoice, initialize FFT object and reassign FFTSize
	int temp = 2 << (FFTChoice.value() + 8);
	while (temp > (*AudioTrack)[0].size())
	{
		temp /= 2;
		FFTChoice.value(FFTChoice.value() - 1);
	}
	FFTSize = temp;
	//FFT.init(FFTSize);
}

void Spectrum::Draw()
{
	SpectrumChart.clear();
	SpectrumChart.bounds(-120.0, 0.0);
	FFT.DoFFT((*AudioTrack)[0], CenterSample, FFTSize);
	for (int n = 0; n <= FFTSize / 2; ++n)
		SpectrumChart.add(FFT.PassAmpl(n));
	LMeter.Set(FFT.PassRMS());
}
// Gets index of audio sample corresponding to the center of FFT window
void Spectrum::GetPosition(int CentrSmpl)
{
	Spectrum::CenterSample = CentrSmpl;
}