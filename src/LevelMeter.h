#include <fltk/Fl_Chart.H>

class LevelMeter
{
public:
	LevelMeter();
	void Set(float);
private:
	Fl_Chart Meter;
};

