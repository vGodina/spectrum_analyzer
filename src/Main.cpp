#include "MainWindow.h"
#include "Menu.h"

int main()
{
	Menu menu;
	MainWindow BaseWindow(600, 600, "Spectrum Analyzer", &menu);
	BaseWindow.add(menu);
	BaseWindow.show();
	return Fl::run();
}