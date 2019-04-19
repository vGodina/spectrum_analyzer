#ifndef RCHART_H
#define RCHART_H

#include "IChart.h"
#include <fltk/Fl_Chart.H>

class RChart : public IChart
{
public:
	RChart();
	void color(Fl_Color bg) override;

	void type(uchar t) override;

	void clear() override;

	void bounds(double min, double max) override;
	void bounds(double* min, double* max) override;

	void add(double val) override;

	void SetGeometry(int x, int y, int w, int h) override;
	
	Fl_Widget* GetImplWidget() override;
private:
	Fl_Chart Chart;
};

#endif