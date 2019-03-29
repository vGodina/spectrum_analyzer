#include "Spectrum.h"

Spectrum::Spectrum (int x, int y, int w, int h,
	std::unique_ptr<IChart> Chart,
	std::unique_ptr<IChoice> Choice,
	std::unique_ptr <IFFTHandler> Fft,
	std::unique_ptr<ILevelMeter> Meter) :
		Group{ x, y, w, h },
		SpectrumChart { std::move(Chart) },
		FFTChoice { std::move(Choice) },
		FFT { std::move(Fft) },
		LMeter { std::move(Meter) }
{
	FFTChoice->callback(CbFFTChoice, this);
	SpectrumChart->color(FL_WHITE);
	SpectrumChart->type(FL_LINE_CHART);
	// Create a list of Choice widget's FFTSize values from 2^9 to 2^20 
	for (int i = 8; i < 20; i++)
		FFTChoice->add(std::to_string(2 << i).c_str());
	FFTChoice->value(0);
	FFTSize = 2 << (FFTChoice->value() + 8);
	
	Group.add(SpectrumChart->GetImplWidget());
	Group.add(FFTChoice->GetImplWidget());
	Group.add(LMeter->GetImplWidget());
	Group.end();
}

bool Spectrum::TakeAudioData(const IAudioFile<float>::AudioBuffer& AudioTrk)
{
	AudioTrack = &AudioTrk;
	CheckFFTSize();
	Draw();
	return true;
}

// Gets index of audio sample corresponding to the center of FFT window
bool Spectrum::SetPosition(int CentrSmpl)
{
	FFT->SetCenterSample(CentrSmpl);
	return true;
}

void Spectrum::CbFFTChoice(Fl_Widget*, void* Obj)
{
	static_cast<Spectrum*>(Obj)->CheckFFTSize();
	static_cast<Spectrum*>(Obj)->Draw();
}

// Check if choosed FFT Size is not bigger than audio length
void Spectrum::CheckFFTSize()
{
	unsigned int temp = 2 << (FFTChoice->value() + 8);
	while (AudioTrack != nullptr && temp > (*AudioTrack)[0].size()) {
		temp /= 2;
		FFTChoice->value(FFTChoice->value() - 1);
	}
	FFTSize = temp;
}

void Spectrum::Draw()
{
	SpectrumChart->clear();
	SpectrumChart->bounds(-120.0, 0.0);
	if (AudioTrack != nullptr) {
		FFT->DoFFT((*AudioTrack)[0], FFTSize);
		for (int n = 0; n <= FFTSize / 2; ++n)
			SpectrumChart->add(FFT->PassAmpl(n));
		LMeter->Set(FFT->PassRMS());
	}
}

Fl_Group* Spectrum::GetImplWidget()
{
	return &Group;
}