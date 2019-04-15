#include <thread>
#include "FFTHandler.h"

FFTHandler::FFTHandler() : FFT() { }

void FFTHandler::DoFFT(std::vector <float> AudioTrack, int FFTSize)
{
	FFT.init(FFTSize);
	int N = FFTSize / 2;
	// Finding start sample from which FFT will be performed.  
	// CenterSample corresponds to the center of FFT selection
	int AudioLength = AudioTrack.size();
	int StartSample = (CenterSample - N);
	// Limiting StartSample addressing to file size
	if (StartSample < 0)
		StartSample = 0;
	if (StartSample > (AudioLength - FFTSize))
		StartSample = AudioLength - FFTSize;

	std::vector<float> Re(N + 1);
	std::vector<float> Im(N + 1);
	Ampl.resize(N + 1);

	FFT.fft(&AudioTrack[StartSample], Re.data(), Im.data());

	 //square of Amplitude
	float Norm = 1 / pow(static_cast<float>(N), 2);

	double RMS1 = 0.0F;
	double RMS2 = 0.0F;

	std::thread Thread1([Re, Im, N, Norm, &RMS1, this] () {
		float Ampl1 = 0.0F;
		for (int n = 0; n < N / 2 + 1; ++n)
		{
			//Calculating normalized square of amplitude Ak
			Ampl1 = (Re[n] * Re[n] + Im[n] * Im[n]) * Norm;
			RMS1 += Ampl1;
			// log scale of Ak.
			Ampl[n] = 10.0F * log10f(Ampl1);
		}
	});
	
	std::thread Thread2([Re, Im, N, Norm, &RMS2, this]() {
		float Ampl2 = 0.0F;
		for (int n = N / 2 + 1; n < N + 1; ++n)
		{
			Ampl2 = (Re[n] * Re[n] + Im[n] * Im[n]) * Norm;
			RMS2 += Ampl2;

			Ampl[n] = 10.0F * log10f(Ampl2);
		}
	});

	Thread1.join();
	Thread2.join();

	// showing RMS level at LevelMeter widget
	LogRMS = 10.0 * log10(0.5*(RMS1 + RMS2));
}

double FFTHandler::GetRMS () const
{
	return LogRMS;
}

double FFTHandler::GetAmpl (int Index) const
{
	return Ampl[Index];
}

void FFTHandler::SetCenterSample(int CentreSample)
{
	CenterSample = CentreSample;
}