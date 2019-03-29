#include <audiofft/AudioFFT.h>
#include "IFFTHandler.h"

class FFTHandler : public IFFTHandler
{
public:
	FFTHandler();
	void DoFFT (std::vector <float> AudioTrack, int FFTSize) override;
	double PassRMS() override;
	double PassAmpl(int Index) override;
	void SetCenterSample(int CentreSample) override;
private:
	audiofft::AudioFFT FFT;
	double LogRMS;
	std::vector<float> Ampl;
	int CenterSample;
};