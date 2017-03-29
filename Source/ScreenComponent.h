#pragma once
/*
  ==============================================================================

    ScreenComponent.h
    Created: 3 Mar 2017 12:32:14pm
    Author:  MHofffmann

  ==============================================================================
*/

#ifndef SCREENCOMPONENT_H_INCLUDED
#define SCREENCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "digital_filters.h"
#include "fft_struct.h"

#define FFT_LENGTH 4096
#define FFT_FULL "fft is full"


//==============================================================================
/*
*/
class ScreenComponent    : public Component,
						               public ChangeListener


{
public:
    ScreenComponent();
	~ScreenComponent();

	FFTStruct fft_struct_;
	bool IsFFTbussy_;
	//Draw methods
	//========================================
    void paint (Graphics&) override;
	void PaintFilterSpectrum(Graphics& g) const;
	void PaintFFTResult(Graphics& g);
	void InitFilterSpectrumXAxis();
  void InitFFTXAxis();
	void ClearFilterSpectrum();
	//=======================================
	
	//Get methods
	double GetFilterSpectrumXAxis(int index) const;

	//Set methods
	void SetSampleRate(double sample_rate);
	void AddDigitalFilterPt(HoffFilters::IIRHighShelfFilter* high_shelf_filter, 
							HoffFilters::IIRLowShelfFilter* low_shelf_filter,
							HoffFilters::IIRParametricBandPassFilter* parametric_band_pass_filter_1,
							HoffFilters::IIRParametricBandPassFilter* parametric_band_pass_filter_2);
	void SetFilterSpectrum(double value);

	void changeListenerCallback(ChangeBroadcaster* source) override;
    void resized() override;

private:
	Array<double> filter_x_axis_;
	Array<double> filter_spectrum_; 
  Array<double> fft_x_axis;

	HoffFilters::IIRHighShelfFilter* iir_high_shelf_filter_;
	HoffFilters::IIRLowShelfFilter* iir_low_shelf_filter_;
	HoffFilters::IIRParametricBandPassFilter* iir_parametric_band_pass_filter_1_;
	HoffFilters::IIRParametricBandPassFilter* iir_parametric_band_pass_filter_2_;

	double sample_rate_;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ScreenComponent)
};


#endif  // SCREENCOMPONENT_H_INCLUDED
