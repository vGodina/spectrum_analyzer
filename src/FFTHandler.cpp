#include "FFTHandler.h"



FFTHandler::FFTHandler() : 
	FFT()
{

}

void FFTHandler::DoFFT(std::vector <float> AudioTrack, int CenterSample, int FFTSize)
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
	double RMS = 0.0F;
	double Ampl2 = 0.0; //square of Amplitude
	double Norm = 1 / pow(N, 2);

	for (int n = 0; n < N + 1; ++n)
	{
		//Calculating normalized square of amplitude Ak
		Ampl2 = (Re[n] * Re[n] + Im[n] * Im[n]) * Norm;
		RMS += Ampl2;
		// log scale of Ak.
		Ampl[n] = 10.0F * log10(Ampl2);
	}
	// showing RMS level at LevelMeter widget
	LogRMS = 10.0 * log10(RMS / 2);
}

double FFTHandler::PassRMS ()
{
	return LogRMS;
}

double FFTHandler::PassAmpl(int Index)
{
	return Ampl[Index];
}