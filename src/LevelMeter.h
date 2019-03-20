#include <fltk/Fl_Chart.H>

class LevelMeter
{
public:
	LevelMeter();
	void Set(double);
private:
	Fl_Chart Meter;
};

