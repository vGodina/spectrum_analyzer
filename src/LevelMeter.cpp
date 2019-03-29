#include "LevelMeter.h"


LevelMeter::LevelMeter(std::unique_ptr<IChart> Chart) :
	Meter { std::move(Chart)}
{
	Meter->type(FL_BAR_CHART);
	Meter->color(FL_GREEN);
	Meter->bounds(-120.0, 0.0);
	Meter->add(-120);
}

void LevelMeter::Set(double value)
{
	Meter->clear();
	Meter->bounds(-120.0, 0.0);
	Meter->add(static_cast<float>(value));
}

Fl_Widget* LevelMeter::GetImplWidget()
{
	return Meter->GetImplWidget();
}