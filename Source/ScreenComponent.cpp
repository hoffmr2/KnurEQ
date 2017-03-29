/*
  ==============================================================================

    ScreenComponent.cpp
    Created: 3 Mar 2017 12:32:15pm
    Author:  MHofffmann

  ==============================================================================
*/


#include "ScreenComponent.h"
//==============================================================================
ScreenComponent::ScreenComponent() : fft_struct_(FFT_LENGTH), IsFFTbussy_(false), sample_rate_(0)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

ScreenComponent::~ScreenComponent()
{
}

void ScreenComponent::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */
	PaintFilterSpectrum(g);
	PaintFFTResult(g);
}

void ScreenComponent::PaintFilterSpectrum(Graphics& g) const
{
	g.setColour(Colours::aqua);
	int startY = getHeight() / 2;
	for (int i = 1; i < getWidth(); ++i)
	{
		Line<float> line(
			i-1,
			filter_spectrum_[i - 1] + float(startY),
			i,
			filter_spectrum_[i] + float(startY));
		g.drawLine(line, 2);
	}
}

void ScreenComponent::PaintFFTResult(Graphics& g)
{
	int startX = 0;
	int startY = getHeight() / 2;
	int spectrumMax = getHeight() /2;
	int width = getWidth()/3;


	for (int i = 2; i < FFT_LENGTH / 2 && (i*sample_rate_ / FFT_LENGTH) < 20000; ++i)
	{
		g.setColour(Colours::lightseagreen);
		float spectrum_value_1 = -10*log10 (fft_struct_.spectrum[i-1]);
		float Yvalue1 = (spectrum_value_1 < spectrumMax) ? spectrum_value_1 : spectrumMax;
		float spectrum_value_2 = -10 * log10(fft_struct_.spectrum[i]);
		float Yvalue2 = (spectrum_value_2 < spectrumMax) ? spectrum_value_2 : spectrumMax;
		Line <float> l(startX + fft_x_axis[i-1], startY + Yvalue1,
			startX + fft_x_axis[i], startY + Yvalue2);
		g.drawLine(l, 2);

	}
}

void ScreenComponent::InitFilterSpectrumXAxis()
{

	assert(sample_rate_ != 0);
	filter_x_axis_.clear();
	int width = getWidth();
	double segment_width = width / 3.0;

	for (auto i = 0; i < width; ++i)
		filter_x_axis_.add( double(pow(10, ((i) / double(segment_width)) + 1.3) / sample_rate_));
}

void ScreenComponent::InitFFTXAxis()
{
  auto width = getWidth() / 3;
  for (int i = 0; i < FFT_LENGTH / 2 && (i*sample_rate_ / FFT_LENGTH) < 20000; ++i)
  {
    auto val = width*(log10(i*sample_rate_ / FFT_LENGTH) - 1.3);
      fft_x_axis.add(val);
  }
}

void ScreenComponent::ClearFilterSpectrum()
{
	filter_spectrum_.clear();
}

double ScreenComponent::GetFilterSpectrumXAxis(int index) const
{
	return filter_x_axis_[index];
}

void ScreenComponent::SetSampleRate(double sample_rate)
{
	sample_rate_ = sample_rate;
}

void ScreenComponent::AddDigitalFilterPt(HoffFilters::IIRHighShelfFilter* high_shelf_filter, HoffFilters::IIRLowShelfFilter* low_shelf_filter, HoffFilters::IIRParametricBandPassFilter* parametric_band_pass_filter_1, HoffFilters::IIRParametricBandPassFilter* parametric_band_pass_filter_2)
{
	this->iir_high_shelf_filter_ = high_shelf_filter;
	this->iir_low_shelf_filter_ = low_shelf_filter;
	this->iir_parametric_band_pass_filter_1_ = parametric_band_pass_filter_1;
	this->iir_parametric_band_pass_filter_2_ = parametric_band_pass_filter_2;

}

void ScreenComponent::SetFilterSpectrum(double value)
{
	value = -80 * log10(value);
	filter_spectrum_.add(value);
}


void ScreenComponent::changeListenerCallback(ChangeBroadcaster* source)
{
	static int counter = 0;
	if (fft_struct_.IsFull())
	{
			IsFFTbussy_ = true;
			fft_struct_.CalculateFFT();
      repaint();
      IsFFTbussy_ = false;
      return;
	}
	repaint();
	
}



void ScreenComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
