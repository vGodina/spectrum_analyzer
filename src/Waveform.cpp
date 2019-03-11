#include "Waveform.h"

Waveform::Waveform() :
WaveformChart(20, 100, 500, 200),
Slider(20, 300, 500, 20),
ZoomInH(47, 322, 25, 25, "+"),
ZoomOutH(20, 322, 25, 25, "-"),
ZoomInV(522, 100, 25, 25, "+"),
ZoomOutV(522, 127, 25, 25, "-")
{

	ZoomInH.callback(CbZoomInH, this);
	ZoomOutH.callback(CbZoomOutH, this);
	Slider.callback(CbSlider, this);
	ZoomInV.callback(CbZoomInV, this);
	ZoomOutV.callback(CbZoomOutV, this);
		// Initialization of  widgets
	WaveformChart.color(FL_WHITE);
	WaveformChart.type(FL_LINE_CHART);
	Slider.type(FL_HORIZONTAL);
	Slider.slider_size(1.0);
	Slider.value(0.5);
}

void Waveform::CbSlider(Fl_Widget* Slider, void* Obj)
{
	static_cast<Waveform*>(Obj)->Draw(1.0);
	static_cast<Waveform*>(Obj)->EmitSignal();
}

void Waveform::EmitSignal()
{
	SliderSignal(Slider.slider_size(), Slider.value());
}

boost::signals2::connection Waveform::connect(const signal_t::slot_type &subscriber)
{
	return SliderSignal.connect(subscriber);
}

void Waveform::Pass(const IAudioFile<float>::AudioBuffer AudioTrk)
{
	AudioTrack = AudioTrk;
	Slider.slider_size(1.0);
	Slider.value(0.5);
	Draw(1.0);
}

void Waveform::Draw(double ZoomFactor = 1.0)
{
		constexpr int ChartLength = 1024;
		// resize Slider size
		Slider.slider_size(Slider.slider_size() / ZoomFactor);
		if (Slider.slider_size() == 1.0)
			Slider.value(0.5);
		// reset Chart and keep its bounds with no changes
		VerticalScale(1.0, true);
		// Center value of Slider
		int Length = AudioTrack[0].size();
		double Center = Slider.value() - Slider.slider_size() * (Slider.value() - 0.5);
		int VisibleSamples = Length * Slider.slider_size();
		int StartSample = Center * Length - VisibleSamples / 2;
		int Delta = VisibleSamples;
		int Decimation = 1;
		if (VisibleSamples > ChartLength)
		{
			Delta = ChartLength;
			Decimation = VisibleSamples / ChartLength;
		}
		for (int i = 0; i < Delta; i++)
		{
			//Fl_AudioFile<float>::AudioBuffer& Copy = *AudioTrack;
			WaveformChart.add(AudioTrack[0][StartSample + i * Decimation]);
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
	static_cast<Waveform*>(Obj)->Draw(0.5);
}

void Waveform::CbZoomInV(Fl_Widget* ZoomInV, void* Obj)
{
	Waveform* Widget = static_cast<Waveform*>(Obj);
	Widget->VerticalScale(2.0, false);
	Widget->WaveformChart.redraw();
}

void Waveform::CbZoomOutV(Fl_Widget* ZoomOutV, void* Obj)
{
	Waveform* Widget = static_cast<Waveform*>(Obj);
	Widget->VerticalScale(0.5, false);
	Widget->WaveformChart.redraw();
}