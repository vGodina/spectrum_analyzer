#include "LevelMeter.h"


LevelMeter::LevelMeter(std::unique_ptr<IChart> Chart) :
	Meter { std::move(Chart)},
	LevelFloor { -120.0 },
	LevelCeil { 0.0 }
{
	Meter->type(FL_BAR_CHART);
	Meter->color(FL_GREEN);
	Meter->bounds(LevelFloor, LevelCeil);
	Meter->add(LevelFloor);
}

void LevelMeter::Set(double value)
{
	Meter->clear();
	Meter->bounds(LevelFloor, LevelCeil);
	Meter->add(static_cast<float>(value));
}

Fl_Widget* LevelMeter::GetImplWidget()
{
	return Meter->GetImplWidget();
}

void LevelMeter::SetGeometry(int x, int y, int w, int h)
{
	Meter->SetGeometry(x, y, w, h);
}