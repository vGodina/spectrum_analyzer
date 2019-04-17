#include "FFTHandler.h"
#include <algorithm>

FFTHandler::FFTHandler() : FFT() { }

void FFTHandler::DoFFT(std::vector <float> AudioTrack, int FFTSize)
{
	FFT.init(FFTSize);
	int N = FFTSize / 2;

	unsigned int StartSample = std::clamp(CenterSample - N, 0U, AudioTrack.size() - FFTSize);

	std::vector<float> Re(N + 1);
	std::vector<float> Im(N + 1);
	Ampl.resize(N + 1);

	FFT.fft(&AudioTrack[StartSample], Re.data(), Im.data());

	float Norm = pow(static_cast<float>(N), -2);

	double RMS = 0.0;
	float AmplSquare = 0.0F;

	for (int n = 0; n < N + 1; ++n)
	{
		//Calculating normalized square of amplitude Ak
		AmplSquare = (Re[n] * Re[n] + Im[n] * Im[n]) * Norm;
		RMS += AmplSquare;
		Ampl[n] = 10.0F * log10(AmplSquare);
	}

	LogRMS = 10.0 * log10(RMS / 2);
}

double FFTHandler::GetRMS () const
{
	return LogRMS;
}

double FFTHandler::GetAmpl (int Index) const
{
	return Ampl[Index];
}

void FFTHandler::SetCenterSample(unsigned int CentreSample)
{
	CenterSample = CentreSample;
}