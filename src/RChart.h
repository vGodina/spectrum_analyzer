#ifndef RCHART
#define RCHART
#include "IChart.h"
#include "fltk/Fl_Chart.h"
#include <memory>
#include <string_view>

class RChart : public IChart
{
public:
	RChart(int x, int y, int w, int h, std::string_view L);
	void color(Fl_Color bg) override;
	void type(uchar t) override;
	void clear() override;
	void bounds(double min, double max) override;
	void bounds(double* min, double* max) override;
	void add(double val) override;
	
	Fl_Widget* GetImplWidget() override;
	//virtual void () override;
private:
	Fl_Chart Chart;
};
#endif RCHART