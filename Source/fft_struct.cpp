
#include <complex>
#include "fft_struct.h"


void FFTStruct::SetSinAndCosTable()
{
	sin_table_ = new double[fft_length_ / 2];
	cos_table_ = new double[fft_length_ / 2];
	const	double C = (2 * 3.14) / fft_length_;
	for (int i = 0; i < fft_length_ / 2; ++i)
	{
		sin_table_[i] = sin(-i*C);
		cos_table_[i] = cos(-i*C);
	}
}

void FFTStruct::InitialiseWindiow()
{
	hanning_window_ = new double[fft_length_];
	for (int i = 0; i < fft_length_; ++i)
	{
		hanning_window_[i] = (0.54 - 0.46* cos(2*3.14*i / (fft_length_ - 1)));
	}
	
}

void FFTStruct::SwapRevBin()
{
	
	for (int i = 1; i < fft_length_/2; ++i)
	{

		int  j = reversed_indexs_[i];

			//used->add(temp );
			swap(real[i], real[j]);
			swap(imag[i], imag[j]);

		}
	
}

void FFTStruct::SwapRevBinWithModuleCalulation()
{
	for (int i = 0; i < fft_length_/2; ++i)
	{
		int  j = reversed_indexs_[i];
		
		//used->add(temp );
		swap(real[i], real[j]);
		swap(imag[i], imag[j]);
			//used->add(temp );
			real[i] = (real[i] * real[i] + imag[i] *imag[i])/fft_length_;
			imag[i] = 0;

			real[j] = (real[j] * real[j] + imag[j] * imag[j]) / fft_length_;
			imag[j] = 0;

		
	}
}

int FFTStruct::BinRev(int value, int size)
{
	switch (size)
	{
	case 1:  size = 1; break;
	case 2: size = 2; break;
	case 4: size = 3; break;
	default: size = int(floor(log2(size)));


	}

	int rev = 0;
	unsigned int mask = 1;
	unsigned int bit;

	int j = 0;
	for (int i = size - 1; i >= 0; --i)
	{
		bit = (mask << i) & value;
		bit >>= i;
		bit <<= j;
		rev += bit;
		++j;
	}


	return rev;
}


void FFTStruct::AddElement(float left, float right)
{
	
	int n = fft_length_  - elements_number_;
	real[n] = (left / 2 + right / 2)* (hanning_window_[n]);
	imag[n] = 0;
	++elements_number_;
}



void FFTStruct::CalculateFFT()
{
	//FFT(real, imag, fftLength,sinTable,cosTable);
	elements_number_ = 0;
	for(int i=0;i<fft_length_;++i)
	{
		imag_spectrum[i] = imag[i];
		real_spectrum_[i] = real[i];
	}
	for (int k = fft_length_ / 2, l = 1; k > 0; k /= 2, l *= 2)
	{

		int* usedIndex = new int[fft_length_];
		for (int n = 0; n < (fft_length_); ++n)
		{

			if (usedIndex[n] == 1)
			{
				continue;
			}
			usedIndex[n + k] = 1;

			int m = n*l % fft_length_;

			float tempRe1 = (real_spectrum_[n]);
			float tempIm1 = imag_spectrum[n];
			float tempRe2 = (real_spectrum_[n + k]);
			float tempIm2 = imag_spectrum[n + k];

			real_spectrum_[n] = tempRe1 + tempRe2;
			imag_spectrum[n] = tempIm1 + tempIm2;

			{
				real_spectrum_[n + k] = (tempRe1 - tempRe2) * (cos_table_[m]) + (tempIm2 - tempIm1)*(sin_table_[m]);
				imag_spectrum[n + k] = (tempIm1 - tempIm2) * (cos_table_[m]) + (tempRe1 - tempRe2)*(sin_table_[m]);
			}


		}
		delete[] usedIndex;
	}
	for (int i = 0; i<fft_length_; ++i)
	{
		int j = reversed_indexs_[i];
		double temp = spectrum[i];
		real_spectrum_[j] /= fft_length_;
		imag_spectrum[j] /= fft_length_;
		spectrum[i] = (real_spectrum_[j] * real_spectrum_[j] + imag_spectrum[j] * imag_spectrum[j]);
	}
    
}



float FFTStruct::GetSpectrumValue(int i)
{
	//int j = reversed_indexs_[i];
//	double temp = spectrum[i];
	//real_spectrum_[j] /= fft_length_;
//	imag_spectrum[j] /= fft_length_;
//	spectrum[i] = (real_spectrum_[j] * real_spectrum_[j] + imag_spectrum[j] * imag_spectrum[j]);
	//spectrum[i] = (spectrum[i] + temp)/numberOfTransforms;
	return  (spectrum[i]);
}

float FFTStruct::GetRealValue(int i)
{
	return real[i];
}



FFTStruct::FFTStruct()
{
	
}


//constructor and destructor

FFTStruct::FFTStruct(int size): fft_length_(size), elements_number_(0), number_of_transforms_(0)
{
	imag = new float[fft_length_];
	real = new float[fft_length_];
	imag_spectrum = new float[fft_length_];
	real_spectrum_ = new float[fft_length_];
	spectrum = new float[fft_length_];
	reversed_indexs_ = new int[fft_length_];


	for (int i = 0; i < fft_length_; ++i)
	{
		imag[i] = 0;
		real[i] = 0;
		imag_spectrum[i] = 0;
		real_spectrum_[i] = 0;
		spectrum[i] = 0;
		reversed_indexs_[i] = BinRev(i, fft_length_);
	}
	SetSinAndCosTable();
	InitialiseWindiow();
}


FFTStruct::~FFTStruct()
{
	/*
	delete sinTable;
	delete cosTable;
	delete[] imag;
	delete[] real;
	delete[] spectrum;
	delete[] hanningWindow;
	delete[] reversedIndexs;
	*/
}
