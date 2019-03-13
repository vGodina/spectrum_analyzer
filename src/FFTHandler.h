#include <audiofft/AudioFFT.h>
#include <vector>

class FFTHandler
{
public:
	FFTHandler();
	void DoFFT (std::vector <float> AudioTrack, int CenterSample, int FFTSize);
	double PassRMS();
	double PassAmpl(int);
private:
	audiofft::AudioFFT FFT;
	double LogRMS;
	std::vector<float> Ampl;
};

