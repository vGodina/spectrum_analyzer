#include "MainWindow.h"
#include <string>

MainWindow::MainWindow(int w, int h, const char* title) : Fl_Window(w, h, title),
	OpenButton(std::make_unique<Fl_Button>(30, 30, 100, 30, "Open .wav file")),
	FileInfo(std::make_unique<Fl_Box>(200, 30, 220, 30, "000")),
	Chooser(std::make_unique<Fl_Native_File_Chooser>()),
	Chart(std::make_unique<Fl_Chart>(20, 100, 400, 200, "Waveform")),
	Slider(std::make_unique<Fl_Slider>(20,300,400,20)),
	ZoomOutH(std::make_unique<Fl_Button>(20, 322, 25, 25, "-")),
	ZoomInH(std::make_unique<Fl_Button>(47, 322, 25, 25, "+")),
	ZoomOutV(std::make_unique<Fl_Button>(422, 127, 25, 25, "-")),
	ZoomInV(std::make_unique<Fl_Button>(422, 100, 25, 25, "+")),
	AudioTrack(std::make_unique<AudioFile<double>>())
{
	begin();
	OpenButton->callback(CbOpenButton, this);
	ZoomInH->callback(CbZoomInH, this);
	ZoomOutH->callback(CbZoomOutH, this);
	Slider->callback(CbSlider, this);
	ZoomInV->callback(CbZoomInV, this);
	ZoomOutV->callback(CbZoomOutV, this);

	// Initialization of  widgets
	Chart->color(FL_WHITE);
	Chart->type(FL_LINE_CHART);
	Chooser->filter("*.wav");
	Slider->type(FL_HORIZONTAL);
	Slider->slider_size(1);
	Slider->value(0.5);
	
	end();
	resizable(this);
	show();
}

MainWindow::~MainWindow() {}

void MainWindow::CbOpenButton(Fl_Widget* OpenButton, void* Obj)
{
	static_cast<MainWindow*>(Obj)->ChooserShow();
}

void MainWindow::VerticalScale(float VertFactor = 1.0, bool ClearChart = TRUE)
{
	double* min = new double;
	double* max = new double;
	Chart->bounds(min, max);
	if (ClearChart) Chart->clear();
	Chart->bounds((*min) * VertFactor, (*max) * VertFactor);
	delete[] min, max;
}

void MainWindow::ChartRedraw(float ZoomFactor = 1.0)
{
	constexpr int ChartLength = 1000;
	float SliderSize = ZoomFactor * Slider->slider_size();
	float SliderValue = static_cast<float>(Slider->value());
	int AudioLength = AudioTrack->getNumSamplesPerChannel();
	// resize Slider size
	Slider->slider_size(SliderSize);
	if (Slider->slider_size() == 1) Slider->value(0.5);
	// keep Chart bounds with no changes
	VerticalScale();
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
		Chart->add(val);
	}
}

void MainWindow::CbZoomInH(Fl_Widget* ZoomIn, void* Obj)
{
	static_cast<MainWindow*>(Obj)->ChartRedraw(0.5);
}

void MainWindow::CbZoomOutH(Fl_Widget* ZoomOutH, void* Obj)
{
	static_cast<MainWindow*>(Obj)->ChartRedraw(2);
}

void MainWindow::CbZoomInV(Fl_Widget* ZoomInV, void* Obj)
{
	MainWindow* win = static_cast<MainWindow*>(Obj);
	win->VerticalScale(0.5, FALSE);
	win->Chart->redraw();
}

void MainWindow::CbZoomOutV(Fl_Widget* ZoomOutV, void* Obj)
{
	MainWindow* win = static_cast<MainWindow*>(Obj);
	win->VerticalScale(2, FALSE);
	win->Chart->redraw();
}

void MainWindow::CbSlider(Fl_Widget* ZoomOut, void* Obj)
{
	static_cast<MainWindow*>(Obj)->ChartRedraw();
}

void MainWindow::ChooserShow()
{
	Chooser->show();
	AudioTrack->load(Chooser->filename());

	std::string FileDuration = std::to_string(AudioTrack->getLengthInSeconds());
	std::string LabelMessage = "File duration: " + FileDuration + " seconds";
	FileInfo->copy_label(LabelMessage.c_str());
	FileInfo->redraw();

	Slider->slider_size(1);
	Chart->clear();
	Chart->bounds(-1, 1);
	ChartRedraw();
}