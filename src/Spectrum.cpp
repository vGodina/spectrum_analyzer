#include "Spectrum.h"

Spectrum::Spectrum(
	std::unique_ptr<IChart> Chart,
	std::unique_ptr<IChoice> Choice,
	std::unique_ptr <IFFTHandler> Fft,
	std::unique_ptr<ILevelMeter> Meter) :
		Group{ 0, 0, 0, 0 },
		SpectrumChart{ std::move(Chart) },
		FFTChoice{ std::move(Choice) },
		FFT{ std::move(Fft) },
		LMeter{ std::move(Meter) },
		FFTMinSizePower { 8 },
		FFTMaxSizePower { 20 },
		LevelFloor { -120.0 }
{
	SpectrumChart->color(FL_WHITE);
	SpectrumChart->type(FL_LINE_CHART);

	FFTChoice->callback(CbFFTChoice, this);
	// Create a list of Choice widget's FFTSize values from 2^9 to 2^20
	for (int i = FFTMinSizePower; i < FFTMaxSizePower; i++)
		FFTChoice->add(std::to_string(2 << i).data());
	FFTChoice->value(0);
	FFTSize = 2 << (FFTChoice->value() + FFTMinSizePower);
	
	Group.add(SpectrumChart->GetImplWidget());
	Group.add(FFTChoice->GetImplWidget());
	Group.add(LMeter->GetImplWidget());
	Group.end();
}

bool Spectrum::SetAudioData(const IAudioFile<float>::AudioBuffer& AudioTrk)
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
	auto SpectrWidget = static_cast<Spectrum*>(Obj);

	if (SpectrWidget->AudioTrack != nullptr)
	{
		SpectrWidget->CheckFFTSize();
		SpectrWidget->Draw();
	}
}

// Check if choosed FFT Size is not bigger than audio length
void Spectrum::CheckFFTSize()
{
	unsigned int temp = 2 << (FFTChoice->value() + FFTMinSizePower);
	while (temp > (*AudioTrack)[0].size()) {
		temp /= 2;
		FFTChoice->value(FFTChoice->value() - 1);
	}
	FFTSize = temp;
}

void Spectrum::Draw()
{
	SpectrumChart->clear();
	SpectrumChart->bounds(LevelFloor, 0.0);
	FFT->DoFFT((*AudioTrack)[0], FFTSize);
	//for (int n = 0; n <= FFTSize / 2; ++n) SpectrumChart->add(FFT->GetAmpl(n));
	LMeter->Set(FFT->GetRMS());
}

Fl_Group* Spectrum::GetImplWidget()
{
	return &Group;
}

void Spectrum::SetGeometry(int x, int y, int w, int h)
{
	constexpr int ChoiceW = 100;
	constexpr int ChoiceH = 22;
	constexpr int LMeterW = 10;

	Group.resize(x, y, w, h);

	SpectrumChart->SetGeometry(x, y, w, h - ChoiceH);

	FFTChoice->SetGeometry(x + w - ChoiceW, y + h - ChoiceH, ChoiceW, ChoiceH);
	FFTChoice->SetCaption("FFT Size:");

	LMeter->SetGeometry(x+w, y, LMeterW, h - ChoiceH);
}