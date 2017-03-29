#pragma once

//#include "fft.h"
#include <cstdlib>
using namespace std;
//using namespace my;
class FFTStruct
{
private:
	// var
	float* imag;
	float* real;
	float* imag_spectrum;
	float* real_spectrum_;
	int*   reversed_indexs_;
	int fft_length_;
	int elements_number_;
	int number_of_transforms_;

	double* sin_table_;
	double* cos_table_;
	double* hanning_window_;
	// functions
	void SetSinAndCosTable();
	void InitialiseWindiow();

public:
  float* spectrum;
	FFTStruct();
	explicit FFTStruct(int size);
	~FFTStruct();
	void SwapRevBin();
	void SwapRevBinWithModuleCalulation();
	int BinRev(int value, int size);
	bool IsFull() const { return elements_number_ >= fft_length_; }
	void AddElement(float left, float right);
	int GetNumElements() const { return elements_number_; }
	void CalculateFFT();
	float GetSpectrumValue(int i);
	float GetRealValue(int i);	
	int GetFFTLength() const { return fft_length_; }
};
