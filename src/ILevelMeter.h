#ifndef ILEVELMETER
#define ILEVELMETER
#include "fltk/Fl_Widget.H"

// Interface of LevelMeter


struct ILevelMeter
{
	virtual ~ILevelMeter() = default;

	virtual void Set(double v) = 0;

	virtual Fl_Widget* GetImplWidget() = 0;
};
#endif ILEVELMETER