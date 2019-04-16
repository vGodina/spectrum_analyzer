#include <thread>
#include "FFTHandler.h"
#include <chrono>
#include <iostream>

FFTHandler::FFTHandler() : FFT() { }

void FFTHandler::DoFFT(std::vector <float> AudioTrack, int FFTSize)
{
	FFT.init(FFTSize);
	int N = FFTSize / 2;
	// Finding start sample from which FFT will be performed.  
	// CenterSample corresponds to the center of FFT selection
	int AudioLength = AudioTrack.size();
	int StartSample = (CenterSample - N);
	// Limiting StartSample to file size
	if (StartSample < 0)
		StartSample = 0;
	if (StartSample > (AudioLength - FFTSize))
		StartSample = AudioLength - FFTSize;

	std::vector<float> Re(N + 1);
	std::vector<float> Im(N + 1);
	Ampl.resize(N + 1);

	FFT.fft(&AudioTrack[StartSample], Re.data(), Im.data());

	float Norm = 1 / pow(static_cast<float>(N), 2);
	
	auto start = std::chrono::system_clock::now();
	///////////////// multithread //////////////////
	unsigned ThreadsNumber = std::thread::hardware_concurrency() - 1;
	std::vector <double> RMS (ThreadsNumber, 0.0);
	std::vector <std::thread> ThreadList;
	double SumRMS = 0.0;

	for (int i = 0; i < ThreadsNumber; ++i)
	{
		int Start = i * N / ThreadsNumber + 1;
		int End = (i + 1) * N / ThreadsNumber + 1;
		ThreadList.push_back(std::thread([Re, Im, N, Norm, &RMS, this, i, Start, End]() {
			float Ampl1 = 0.0F;
			for (int n = Start; n < End; ++n)
			{
				//Calculating normalized square of amplitude Ak
				Ampl1 = (Re[n] * Re[n] + Im[n] * Im[n]) * Norm;
				RMS[i] += Ampl1;
				// log scale of Ak.
				Ampl[n] = 10.0F * log10f(Ampl1);
			}
			
		}));
		SumRMS += RMS[i];
	}
	
	for (int i = 0; i < ThreadsNumber; ++i)
		ThreadList[i].join();	

	LogRMS = 10.0 * log10(0.5*(SumRMS));
	
	/* /////////////////// single thread //////////
	double RMS = 0.0F;
	float Ampl2 = 0.0F; //square of Amplitude

	for (int n = 0; n < N + 1; ++n)
	{
		//Calculating normalized square of amplitude Ak
		Ampl2 = (Re[n] * Re[n] + Im[n] * Im[n]) * Norm;
		RMS += Ampl2;
		// log scale of Ak.
		Ampl[n] = 10.0F * log10f(Ampl2);
	}
	// showing RMS level at LevelMeter widget
	LogRMS = 10.0 * log10(RMS / 2);
	*/
	
	///////////////////////////////////////////
	auto end = std::chrono::system_clock::now();
	auto elapsed = end - start;
	++Iteration;
	SumTime += elapsed.count();
	double T = static_cast<double>(SumTime) / static_cast<double>(Iteration);
	std::cout << T <<'\n';
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