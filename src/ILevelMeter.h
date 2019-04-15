#ifndef ILEVELMETER
#define ILEVELMETER

#include "fltk/Fl_Widget.H"

// Interface of LevelMeter

struct ILevelMeter
{
	virtual ~ILevelMeter() = default;

	virtual void Set(double v) = 0;

	virtual Fl_Widget* GetImplWidget() = 0;

	virtual void SetGeometry(int x, int y, int w, int h) = 0;
};

#endif