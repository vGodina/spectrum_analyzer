#include "Waveform.h"

Waveform::Waveform (std::unique_ptr<IChart> Chart, std::unique_ptr <ICustomSlider> Slidr,
	std::unique_ptr<IButton> ZmInH, std::unique_ptr<IButton> ZmOutH,
	std::unique_ptr<IButton> ZmInV, std::unique_ptr<IButton> ZmOutV) :
	Group{ 0, 0, 0, 0 },
	WaveformChart { std::move(Chart) },
	Slider { std::move(Slidr) },
	ZoomInH { std::move(ZmInH) },
	ZoomOutH { std::move(ZmOutH) },
	ZoomInV { std::move(ZmInV) },
	ZoomOutV { std::move(ZmOutV) },
	AudioTrack {nullptr}
{
	// callbacks
	
	ZoomInH->callback( [](Fl_Widget*, void* Obj) {static_cast<Waveform*>(Obj)->Draw(2.0); }, this);
	ZoomOutH->callback( [](Fl_Widget*, void* Obj) {static_cast<Waveform*>(Obj)->Draw(0.5); }, this);
	
	ZoomInV->callback( [](Fl_Widget*, void* Obj) {static_cast<Waveform*>(Obj)->VerticalScale(2.0, false); }, this);
	ZoomOutV->callback( [](Fl_Widget*, void* Obj) {static_cast<Waveform*>(Obj)->VerticalScale(0.5, false); }, this);
	
	Slider->callback([](Fl_Widget*, void* Obj) {
		static_cast<Waveform*>(Obj)->Draw(1.0);
		static_cast<Waveform*>(Obj)->Slider->EmitSignal();
	}, this);

	// Initialization of  widgets
	WaveformChart->color(FL_WHITE);
	WaveformChart->type(FL_LINE_CHART);

	Group.add(WaveformChart->GetImplWidget());
	Group.add(Slider->GetImplWidget());
	Group.add(ZoomInH->GetImplWidget());
	Group.add(ZoomOutH->GetImplWidget());
	Group.add(ZoomInV->GetImplWidget());
	Group.add(ZoomOutV->GetImplWidget());
	Group.end();
}

bool Waveform::SetAudioData(const IAudioFile<float>::AudioBuffer& AudioTrk)
{
	AudioTrack = &AudioTrk;
	AudioVector = (*AudioTrack)[0];
	WaveformChart->bounds(-1.0, 1.0);
	Slider->Reset();
	Draw(1.0);
	return true;
}

boost::signals2::connection Waveform::connect(const signal_t::slot_type &slot)
{
	return Slider->connect(slot);
}

bool Waveform::Draw(double ZoomFactor)
{
	int ChartLength = 1000;
	VerticalScale(1.0, true); // Clear Chart and hold bounds with no change
	Slider->Resize(ZoomFactor);
	int VisibleSamples = static_cast<int>(round(Slider->slider_size() * AudioVector.size()));
	int StartSample = static_cast<int>(round(Slider->GetStartValue() * AudioVector.size()));
	int Decimation = VisibleSamples / ChartLength;
	if (VisibleSamples < ChartLength) {
		Decimation = 1;
		ChartLength = VisibleSamples;
	}
	//for (int i = 0; i < ChartLength; ++i) WaveformChart->add(AudioVector[StartSample + i * Decimation]);
	return (ChartLength == 0) ? false : true;
}

void Waveform::VerticalScale(double VertFactor, bool ClearChart = false)
{
	double min, max;
	WaveformChart->bounds(&min, &max);
	if (ClearChart)
		WaveformChart->clear();
	WaveformChart->bounds(min / VertFactor, max / VertFactor);
}

Fl_Group* Waveform::GetImplWidget()
{
	return &Group;
}

void Waveform::SetGeometry(int x, int y, int w, int h)
{ 
	constexpr int BtnW = 25;
	constexpr int BtnH = 25;
	constexpr int SliderH = 20;
	constexpr int Gap = 2;

	Group.resize(x, y, w, h);

	ZoomInH->SetGeometry(x + BtnW + Gap, y + h - BtnH, BtnW, BtnH);
	ZoomInH->SetCaption("+");

	ZoomOutH->SetGeometry(x, y + h - BtnH, BtnW, BtnH);
	ZoomOutH->SetCaption("-");

	ZoomInV->SetGeometry(x + w - BtnW, y, BtnW, BtnH);
	ZoomInV->SetCaption("+");

	ZoomOutV->SetGeometry(x + w - BtnW, y + BtnH + Gap, BtnW, BtnH);
	ZoomOutV->SetCaption("-");

	WaveformChart->SetGeometry(x, y, w - BtnW - Gap, h - BtnH - SliderH - Gap);

	Slider->SetGeometry(x, y + h - BtnH - SliderH - Gap, w - BtnW - Gap, SliderH);
}