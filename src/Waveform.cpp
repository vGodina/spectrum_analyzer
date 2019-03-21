#include "Waveform.h"

Waveform::Waveform() : Fl_Group{ 20, 100, 527, 247 },
WaveformChart { 20, 100, 500, 200 },
Slider { 20, 300, 500, 20 },
ZoomInH { 47, 322, 25, 25, "+" },
ZoomOutH { 20, 322, 25, 25, "-" },
ZoomInV { 522, 100, 25, 25, "+" },
ZoomOutV { 522, 127, 25, 25, "-" },
AudioTrack {nullptr}, 
AudioLength {0}
{
	Slider.callback(CbSlider, this);
	ZoomInH.callback(CbZoomInH, this);
	ZoomOutH.callback(CbZoomOutH, this);
	ZoomInV.callback(CbZoomInV, this);
	ZoomOutV.callback(CbZoomOutV, this);
	// Initialization of  widgets
	WaveformChart.color(FL_WHITE);
	WaveformChart.type(FL_LINE_CHART);
}

bool Waveform::TakeAudioData(const IAudioFile<float>::AudioBuffer& AudioTrk)
{
	AudioTrack = &AudioTrk;
	AudioLength = (*AudioTrack)[0].size();
	float bound = 0.0f;
	auto p = (*AudioTrack)[0];
	for (int i = 0; i < AudioLength; ++i) {
		float temp = p[i];
		if (temp < 0) temp = -temp;
		if (bound < temp) bound = temp;
	}
	WaveformChart.bounds(-bound, bound);
	Slider.Reset();
	Draw(1.0);
	return true;
}

boost::signals2::connection Waveform::connect(const signal_t::slot_type &slot)
{
	return Slider.connect(slot);
}

void Waveform::CbSlider(Fl_Widget* Slider, void* Obj)
{
	static_cast<Waveform*>(Obj)->Draw(1.0);
	static_cast<CustomSlider*>(Slider)->EmitSignal();
}

bool Waveform::Draw(double ZoomFactor = 1.0)
{
	int ChartLength = 1000;
	VerticalScale(1.0, true); // It holds Chart's bounds with no change after clear
	Slider.Resize(ZoomFactor);
	int VisibleSamples = static_cast<int>(round(Slider.slider_size() * AudioLength));
	int StartSample = static_cast<int>(round(Slider.GetStartValue() * AudioLength));
	int Decimation = VisibleSamples / ChartLength;
	if (VisibleSamples < ChartLength) {
		Decimation = 1;
		ChartLength = VisibleSamples;
	}
	auto p = (*AudioTrack)[0];
	for (int i = 0; i < ChartLength; ++i)
		WaveformChart.add(p[StartSample + i * Decimation]);
	return (ChartLength == 0) ? false : true;
}

void Waveform::VerticalScale(double VertFactor = 1.0, bool ClearChart = false)
{
	double min, max;
	WaveformChart.bounds(&min, &max);
	if (ClearChart)
		WaveformChart.clear();
	min /= VertFactor;
	max /= VertFactor;
	WaveformChart.bounds(min, max);
}

void Waveform::CbZoomInH(Fl_Widget*, void* Obj)
{
	static_cast<Waveform*>(Obj)->Draw(2.0);
}

void Waveform::CbZoomOutH(Fl_Widget*, void* Obj)
{
	static_cast<Waveform*>(Obj)->Draw(0.5);
}

void Waveform::CbZoomInV(Fl_Widget*, void* Obj)
{
	static_cast<Waveform*>(Obj)->VerticalScale(2.0, false);
}

void Waveform::CbZoomOutV(Fl_Widget*, void* Obj)
{
	static_cast<Waveform*>(Obj)->VerticalScale(0.5, false);
}

Fl_Group* Waveform::getImplementatioWidget()
{
	return this;
}