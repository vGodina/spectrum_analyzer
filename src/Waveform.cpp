#include <fltk/Fl_Double_Window.H>
#include "Fl_AudioFile.h"
#include "Waveform.h"

Waveform::Waveform() : 
WaveformChart(std::make_unique<Fl_Chart>(20, 100, 500, 200)),
Slider(std::make_unique<Fl_Slider>(20, 300, 500, 20)),
ZoomOutH(std::make_unique<Fl_Button>(20, 322, 25, 25, "-")),
ZoomInH(std::make_unique<Fl_Button>(47, 322, 25, 25, "+")),
ZoomOutV(std::make_unique<Fl_Button>(522, 127, 25, 25, "-")),
ZoomInV(std::make_unique<Fl_Button>(522, 100, 25, 25, "+"))
{
	ZoomInH->callback(CbZoomInH, this);
	ZoomOutH->callback(CbZoomOutH, this);
	Slider->callback(CbSlider, this);
	ZoomInV->callback(CbZoomInV, this);
	ZoomOutV->callback(CbZoomOutV, this);
		// Initialization of  widgets
	WaveformChart->color(FL_WHITE);
	WaveformChart->type(FL_LINE_CHART);
	Slider->type(FL_HORIZONTAL);
	Slider->slider_size(1);
	Slider->value(0.5);
}

Waveform::~Waveform() {}

AudioFile <float>* Waveform::AudioPtr(Fl_Widget* Widget)
{
	// Get pointer to Window
	Fl_Double_Window* Window = static_cast<Fl_Double_Window*>(Widget->parent());
	Fl_AudioFile* AudioTrack = static_cast<Fl_AudioFile*>(Window->child(0));
	return AudioTrack->GetAudio();
}

void Waveform::CbZoomInH(Fl_Widget* ZoomIn, void* Obj)
{
	static_cast<Waveform*>(Obj)->ChartRedraw(AudioPtr(ZoomIn), 0.5);
}

void Waveform::CbZoomOutH(Fl_Widget* ZoomOutH, void* Obj)
{
	Waveform* win = static_cast<Waveform*>(Obj);
	if (win->Slider->slider_size() < 1)
		win->ChartRedraw(AudioPtr(ZoomOutH), 2);
}

void Waveform::CbZoomInV(Fl_Widget* ZoomInV, void* Obj)
{
	Waveform* win = static_cast<Waveform*>(Obj);
	win->VerticalScale(0.5, 0);
	win->WaveformChart->redraw();
}

void Waveform::CbZoomOutV(Fl_Widget* ZoomOutV, void* Obj)
{
	Waveform* win = static_cast<Waveform*>(Obj);
	win->VerticalScale(2, 0);
	win->WaveformChart->redraw();
}

void Waveform::CbSlider(Fl_Widget* Slider, void* Obj)
{
	static_cast<Waveform*>(Obj)->ChartRedraw(AudioPtr(Slider), 1.0);
}

void Waveform::ChartRedraw(AudioFile<float>* AudioTrack, float ZoomFactor = 1.0)
{
	constexpr int ChartLength = 1024;
	float SliderSize = ZoomFactor * Slider->slider_size();
	float SliderValue = static_cast<float>(Slider->value());
	int AudioLength = AudioTrack->getNumSamplesPerChannel();
	// resize Slider size
	Slider->slider_size(SliderSize);
	if (Slider->slider_size() == 1) Slider->value(0.5);
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
		WaveformChart->add(val);
	}
	//DoFFT();
}

void Waveform::VerticalScale(float VertFactor = 1.0, bool ClearChart = 1)
{
	double min, max;
	WaveformChart->bounds(&min, &max);
	if (ClearChart) WaveformChart->clear();
	WaveformChart->bounds(min * VertFactor, max * VertFactor);
}