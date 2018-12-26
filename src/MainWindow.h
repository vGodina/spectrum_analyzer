#include <fltk/Fl.h>
#include <fltk/Fl_Box.h>
#include <fltk/Fl_Window.H>
#include <fltk/Fl_Button.h>
#include <fltk/Fl_Native_File_Chooser.h>
#include <fltk/Fl_Chart.H>
#include <fltk/Fl_Slider.H>
#include <audiofile/AudioFile.h>
#include <memory>
#include <math.h>

class MainWindow : public Fl_Window {
public:
	MainWindow(int w, int h, const char* title);
	~MainWindow();
private:
	std::unique_ptr<Fl_Button>OpenButton;
	std::unique_ptr<Fl_Box>FileInfo;
	std::unique_ptr<Fl_Native_File_Chooser>Chooser;
	std::unique_ptr<Fl_Chart>Chart;
	std::unique_ptr<Fl_Slider>Slider;
	std::unique_ptr<Fl_Button>ZoomInH;
	std::unique_ptr<Fl_Button>ZoomOutH;
	std::unique_ptr<Fl_Button>ZoomInV;
	std::unique_ptr<Fl_Button>ZoomOutV;
	std::unique_ptr<AudioFile<double>>AudioTrack;

	static void CbOpenButton(Fl_Widget*, void*);
	static void CbZoomInH(Fl_Widget*, void*);
	static void CbZoomOutH(Fl_Widget*, void*);
	static void CbZoomInV(Fl_Widget*, void*);
	static void CbZoomOutV(Fl_Widget*, void*);
	static void CbSlider(Fl_Widget*, void*);
	inline void ChooserShow();
	void ChartRedraw(float ZoomFactor);
	void VerticalScale(float VertFactor, bool ClearChart);
};