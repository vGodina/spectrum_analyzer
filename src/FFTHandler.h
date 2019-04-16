#include <audiofft/AudioFFT.h>
#include "IFFTHandler.h"

class FFTHandler : public IFFTHandler
{
public:
	FFTHandler();

	void DoFFT (std::vector <float> AudioTrack, int FFTSize) override;

	double GetRMS() const override;

	double GetAmpl (int Index) const override;

	void SetCenterSample (int CentreSample) override;
private:
	audiofft::AudioFFT FFT;
	double LogRMS;
	std::vector<float> Ampl;
	int CenterSample;

	long Iteration;
	long long SumTime;
};