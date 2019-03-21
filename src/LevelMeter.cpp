#include "LevelMeter.h"

LevelMeter::LevelMeter() :
	Meter { 520, 360, 10, 200 }
{
	Meter.type(FL_BAR_CHART);
	Meter.color(FL_GREEN);
	Meter.bounds(-120.0, 0.0);
	Meter.add(-120);
}

void LevelMeter::Set(double value)
{
	Meter.clear();
	Meter.bounds(-120.0, 0.0);
	Meter.add(static_cast<float>(value));
}