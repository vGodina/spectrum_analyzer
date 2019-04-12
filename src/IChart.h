#ifndef ICHART
#define ICHART
#include "fltk/Fl_Chart.H"

// Interface of Chart

struct IChart
{
	virtual ~IChart() = default;

	virtual void color (Fl_Color bg)= 0;
	virtual void type (uchar t) = 0;
	virtual void clear () = 0;
	virtual void bounds (double min, double max) = 0;
	virtual void bounds (double* min, double* max) = 0;
	virtual void add (double val) = 0;
	virtual Fl_Widget* GetImplWidget() = 0;
	virtual void SetGeometry(int x, int y, int w, int h) = 0;
};
#endif ICHART