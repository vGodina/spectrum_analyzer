#include "RChart.h"

RChart::RChart(int x, int y, int w, int h, std::string_view L) : Chart(x, y, w, h, std::data(L))  { }

void RChart::color(Fl_Color bg)
{
	Chart.color(bg);
}

void RChart::type(uchar t)
{
	Chart.type(t);
}

void RChart::clear()
{
	Chart.clear();
}

void RChart::bounds(double min, double max)
{
	Chart.bounds(min, max);
}

void RChart::bounds(double* min, double* max)
{
	Chart.bounds(min, max);
}

void RChart::add(double val)
{
	Chart.add(val);
}


Fl_Widget* RChart::GetImplWidget()
{
	return &Chart;
}

