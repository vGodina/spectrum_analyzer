#ifndef IFFTHANDLER
#define IFFTHANDLER
#include <vector>

struct IFFTHandler
{
	virtual ~IFFTHandler() = default;

	virtual void DoFFT (std::vector <float> AudioTrack, int FFTSize) = 0;
	virtual double PassRMS() = 0;
	virtual double PassAmpl(int Index) = 0;
	virtual void SetCenterSample(int CentreSample) = 0;
	//virtual Fl_Widget* GetImplWidget() = 0;
};
#endif IFFTHANDLER