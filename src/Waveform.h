#include <boost/signals2.hpp>
#include <fltk/Fl_Button.h>
#include <fltk/Fl_Chart.H>
#include <fltk/Fl_Group.H>
#include "IAudioFile.h"
#include "IWaveForm.h"
#include "CustomSlider.h"

class Waveform : public Fl_Group, public IWaveForm {
public:
	Waveform();
	using signal_t = boost::signals2::signal <void(double)>;
	// Method signal from Slider to slot
	boost::signals2::connection connect(const signal_t::slot_type &slot) override;
	bool TakeAudioData(const IAudioFile<float>::AudioBuffer&) override;
	Fl_Group* getImplementatioWidget() override;

private:
	Fl_Chart WaveformChart;
	CustomSlider Slider;
	Fl_Button ZoomInH;
	Fl_Button ZoomOutH;
	Fl_Button ZoomInV;
	Fl_Button ZoomOutV;

	static void CbSlider(Fl_Widget*, void*);
	static void CbZoomInH(Fl_Widget*, void*);
	static void CbZoomOutH(Fl_Widget*, void*);
	static void CbZoomInV(Fl_Widget*, void*);
	static void CbZoomOutV(Fl_Widget*, void*);

	int CenterSample;
	int AudioLength;
	const IAudioFile<float>::AudioBuffer* AudioTrack;
	bool Draw(double ZoomFactor);
	void VerticalScale(double VertFactor, bool ClearChart);
};