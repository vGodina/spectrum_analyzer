#include "Waveform.h"
#include <vector>

Waveform::Waveform() :
WaveformChart(20, 100, 500, 200),
Slider(20, 300, 500, 20),
ZoomInH(47, 322, 25, 25, "+"),
ZoomOutH(20, 322, 25, 25, "-"),
ZoomInV(522, 100, 25, 25, "+"),
ZoomOutV(522, 127, 25, 25, "-")
{
	Slider.callback(CbSlider, this);
	ZoomInH.callback(CbZoomInH, this);
	ZoomOutH.callback(CbZoomOutH, this);
	ZoomInV.callback(CbZoomInV, this);
	ZoomOutV.callback(CbZoomOutV, this);
	// Initialization of  widgets
	WaveformChart.color(FL_WHITE);
	WaveformChart.type(FL_LINE_CHART);
	Slider.type(FL_HORIZONTAL);
	Slider.slider_size(1.0);
	Slider.value(0.5);
}

bool Waveform::GetAudio(const IAudioFile<float>::AudioBuffer& AudioTrk)
{
	AudioTrack = &AudioTrk;
	AudioLength = (*AudioTrack)[0].size();
	float bound = 0.0f;
	for (int i = 0; i < AudioLength; ++i) {
		float temp = (*AudioTrack)[0][i];
		if (temp < 0) temp = -temp;
		if (bound < temp) bound = temp;
	}
	WaveformChart.bounds(-bound, bound);
	Slider.slider_size(1.0);
	Slider.value(0.5);
	Draw(1.0);
	return true;
}

boost::signals2::connection Waveform::connect(const signal_t::slot_type &subscriber)
{
	return SliderSignal.connect(subscriber);
}

// Signal passes the index of audio sample corresponding to the center of Slider
void Waveform::EmitSignal()
{
	SliderSignal(Waveform::CenterSample);
}

void Waveform::CbSlider(Fl_Widget* Slider, void* Obj)
{
	static_cast<Waveform*>(Obj)->Draw(1.0);
	static_cast<Waveform*>(Obj)->EmitSignal();
}

bool Waveform::Draw(double ZoomFactor = 1.0)
{
	VerticalScale(1.0, true);
	Slider.slider_size(Slider.slider_size() / ZoomFactor);
	double Center = Slider.value() - Slider.slider_size() * (Slider.value() - 0.5);
	Waveform::CenterSample = static_cast<int>(Center * AudioLength);
	int VisibleSamples = AudioLength * Slider.slider_size();
	int StartSample = Waveform::CenterSample - VisibleSamples / 2;
	int ChartLength = 700;
	int Decimation = VisibleSamples / ChartLength;
	if (VisibleSamples < ChartLength) {
		Decimation = 1;
		ChartLength = VisibleSamples;
	}
	if (AudioTrack != nullptr) {
		for (int i = 0; i < ChartLength; ++i)
			WaveformChart.add((*AudioTrack)[0][StartSample + i * Decimation]);
		return true;
	}
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

void Waveform::CbZoomInH(Fl_Widget* ZoomIn, void* Obj)
{
	static_cast<Waveform*>(Obj)->Draw(2.0);
}

void Waveform::CbZoomOutH(Fl_Widget* ZoomOutH, void* Obj)
{
	Waveform* Widget = static_cast<Waveform*>(Obj);
	if (Widget->Slider.slider_size() == 1.0) Widget->Slider.value(0.5);
	Widget->Draw(0.5);
}

void Waveform::CbZoomInV(Fl_Widget* ZoomInV, void* Obj)
{
	static_cast<Waveform*>(Obj)->VerticalScale(2.0, false);
}

void Waveform::CbZoomOutV(Fl_Widget* ZoomOutV, void* Obj)
{
	static_cast<Waveform*>(Obj)->VerticalScale(0.5, false);
}