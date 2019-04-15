#include <fltk/Fl_Group.H>
#include "IAudioFile.h"
#include "IWaveForm.h"
#include "IChart.h"
#include "IButton.h"
#include "ICustomSlider.h"
#include "ISlider.h"

class Waveform : public IWaveForm {
public:
	Waveform(std::unique_ptr<IChart> Chart, std::unique_ptr <ICustomSlider> Slidr,
		std::unique_ptr<IButton> ZmInH, std::unique_ptr<IButton> ZmOutH,
		std::unique_ptr<IButton> ZmInV, std::unique_ptr<IButton> ZmOutV);

	using signal_t = boost::signals2::signal <bool (double)>;
	boost::signals2::connection connect(const signal_t::slot_type &slot) override;
	bool SetAudioData(const IAudioFile<float>::AudioBuffer&) override;
	Fl_Group* GetImplWidget() override;
	void SetGeometry(int x, int y, int w, int h) override;

private:
	Fl_Group Group;
	std::unique_ptr <IChart> WaveformChart;
	std::unique_ptr <ICustomSlider> Slider;
	std::unique_ptr <IButton> ZoomInH;
	std::unique_ptr <IButton> ZoomOutH;
	std::unique_ptr <IButton> ZoomInV;
	std::unique_ptr <IButton> ZoomOutV;

	static void CbSlider(Fl_Widget*, void*);
	static void CbZoomInH(Fl_Widget*, void*);
	static void CbZoomOutH(Fl_Widget*, void*);
	static void CbZoomInV(Fl_Widget*, void*);
	static void CbZoomOutV(Fl_Widget*, void*);

	std::vector<float> AudioVector;
	int CenterSample;
	int AudioLength;
	const IAudioFile<float>::AudioBuffer* AudioTrack;
	bool Draw(double ZoomFactor);
	void VerticalScale(double VertFactor, bool ClearChart);
};