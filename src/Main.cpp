#include "MainWindow.h"
#include "Menu.h"

int main()
{
	MainWindow BaseWindow(600, 600, "Spectrum Analyzer");
	BaseWindow.MainMenu = new Menu;
	BaseWindow.Init();
	BaseWindow.show();
	return Fl::run();
}