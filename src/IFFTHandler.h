#ifndef IFFTHANDLER
#define IFFTHANDLER

#include <vector>

struct IFFTHandler
{
	virtual ~IFFTHandler() = default;

	virtual void DoFFT(std::vector <float> AudioTrack, int FFTSize) = 0;

	virtual double GetRMS() const = 0;

	virtual double GetAmpl(int Index) const = 0;

	virtual void SetCenterSample(int CentreSample) = 0;
};

#endif