#include <iostream>

bool SlotFunction(std::string filepath)
{
	std::cout << filepath;
	return true;
}

void WFormSlotFunction(double SliderVal)
{
	std::cout << SliderVal;
}