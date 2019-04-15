#ifndef LEVELMETER_H
#define LEVELMETER_H

#include <memory>
#include "ILevelMeter.h"
#include "IChart.H"

class LevelMeter : public ILevelMeter
{
public:
	LevelMeter(std::unique_ptr<IChart> Chart);

	void Set(double) override;

	Fl_Widget* GetImplWidget() override;

	void SetGeometry(int x, int y, int w, int h) override;
private:
	std::unique_ptr<IChart> Meter;
};

#endif