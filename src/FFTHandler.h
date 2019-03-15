#include <audiofft/AudioFFT.h>
#include <vector>

class FFTHandler
{
public:
	FFTHandler();
	void DoFFT (std::vector <float> AudioTrack, int FFTSize);
	double PassRMS();
	double PassAmpl(int);
	void SetCenterSample(int);
private:
	audiofft::AudioFFT FFT;
	double LogRMS;
	std::vector<float> Ampl;
	int CenterSample;
};

