#include "Waveform.h"
#include <audiofile/AudioFile.h>

Waveform::Waveform() :
WaveformChart(20, 100, 500, 200),
Slider(20, 300, 500, 20),
ZoomOutH(20, 322, 25, 25, "-"),
ZoomInH(47, 322, 25, 25, "+"),
ZoomOutV(522, 127, 25, 25, "-"),
ZoomInV(522, 100, 25, 25, "+")
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
	Slider.slider_size(1);
	Slider.value(0.5);
}

Waveform::~Waveform() {}
/*
AudioFile <float>* Waveform::AudioPtr(Fl_Widget* Widget)
{
	// Get pointer to Window
	Fl_Double_Window* Window = static_cast<Fl_Double_Window*>(Widget->parent());
	Fl_AudioFile* AudioTrack = static_cast<Fl_AudioFile*>(Window->child(0));
	return AudioTrack->GetAudio();
}*/

void Waveform::CbZoomInH(Fl_Widget* ZoomIn, void* Obj)
{
	static_cast<Waveform*>(Obj)->ChartRedraw(0.5);
}

void Waveform::CbZoomOutH(Fl_Widget* ZoomOutH, void* Obj)
{
	Waveform* win = static_cast<Waveform*>(Obj);
	if (win->Slider.slider_size() < 1)
		win->ChartRedraw(2);
}

void Waveform::CbZoomInV(Fl_Widget* ZoomInV, void* Obj)
{
	Waveform* win = static_cast<Waveform*>(Obj);
	win->VerticalScale(0.5, 0);
	win->WaveformChart.redraw();
}

void Waveform::CbZoomOutV(Fl_Widget* ZoomOutV, void* Obj)
{
	Waveform* win = static_cast<Waveform*>(Obj);
	win->VerticalScale(2, 0);
	win->WaveformChart.redraw();
}

void Waveform::CbSlider(Fl_Widget* Slider, void* Obj)
{
	static_cast<Waveform*>(Obj)->ChartRedraw(1.0);
}

void Waveform::ChartRedraw(float ZoomFactor = 1.0)
{
	AudioFile<float>* AudioTrack(0); ///////////////////////////DUMMY!!!
	constexpr int ChartLength = 1024;
	float SliderSize = ZoomFactor * Slider.slider_size();
	float SliderValue = static_cast<float>(Slider.value());
	int AudioLength = AudioTrack->getNumSamplesPerChannel();
	// resize Slider size
	Slider.slider_size(SliderSize);
	if (Slider.slider_size() == 1) Slider.value(0.5);
	// keep Chart bounds with no changes
	VerticalScale(1.0, 1);
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
		WaveformChart.add(val);
	}
	//DoFFT();
}

void Waveform::VerticalScale(float VertFactor = 1.0, bool ClearChart = 1)
{
	double min, max;
	WaveformChart.bounds(&min, &max);
	if (ClearChart) WaveformChart.clear();
	WaveformChart.bounds(min * VertFactor, max * VertFactor);
}
/*
void Waveform::Redraw(AudioFile<float>* AudioTrack)
{
	Slider.slider_size(1);
	WaveformChart.clear();
	WaveformChart.bounds(-1, 1);
	ChartRedraw(AudioTrack);
}*/