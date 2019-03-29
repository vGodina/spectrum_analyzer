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
private:
	std::unique_ptr<IChart> Meter;
};
#endif LEVELMETER_H