#include "AudioFile.h"

int main()
{
	AudioFile<float> audioFile;
	audioFile.load("test.wav");
	audioFile.printSummary();
	std::cin.get();
}