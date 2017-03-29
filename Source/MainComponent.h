/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 4.3.0

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

#ifndef __JUCE_HEADER_9002020A4DD09B20__
#define __JUCE_HEADER_9002020A4DD09B20__

//[Headers]     -- You can add your own extra header files here --


#include "../JuceLibraryCode/JuceHeader.h"
#include <string>
#include "ScreenComponent.h"
#include "LookAndFeelCustom.h"
#define LOW_SHELF_FILTER_DEFAULT_CUTOFF_FREQUENCY 100
#define HIGH_SHELF_FILTER_DEFAULT_CUTOFF_FREQUENCY 5000
#define PARAMETRIC_FILTER_DEFAULT_CUTOFF_FREQUENCY 500
#define FILTER_DEFAULT_GAIN 0
#define PARAMETRIC_FILTER_DEFAULT_Q 0.001

enum TransportState
{
	Stopped,
	Starting,
	Playing,
	Pausing,
	Paused,
	Moving,
	Stopping
};
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class MainComponent  : public AudioAppComponent,
                       public ChangeListener,
                       public Timer,
                       public ChangeBroadcaster,
                       public ButtonListener,
                       public SliderListener
{
public:
    //==============================================================================
    MainComponent ();
    ~MainComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.

	//Playback methods
	//==========================================================================
	void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
	void FilterLeftChannel(float& sample) const;
	void FilterRightChannel(float& sample);
	void AudioProcessing(const AudioSourceChannelInfo& bufferToFill);
	void getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) override;
	void releaseResources() override;
	//==========================================================================

	void timerCallback() override;
	void SetScreenComponentFiltersPointers();
	void SetScreenComponentFiltersSpectrum();
	void SetVeliocityBasedModeToFiltersSliders();

	//Playback form file methods
	//=============================================================================
	void ChangeState(TransportState new_state);
	void changeListenerCallback(ChangeBroadcaster* source) override;
	void OpenTextButtonClicked();
	void startTextButtonCklicked();
	void pauseTextButtonCklicked();
	void stopTextButtonCklicked();
	double GetAudioFileVolume();
	//============================================================================

	//Time slider methods
	//==============================================================================
	void SetTimeSliderPosition(double fullLength, double currentPosition);
	double GetDestinyAudioFilePosition() const;
	void sliderDragEnded(Slider * movedSlider) override;
	void ConvertCurrentPositionToSecondsAndMinutes(int currentPosition, std::string& s_seconds, std::string& minutes);
	void SetTimeLabelText();

	//============================================================================

	//Filters methods
	//============================================================================
	void InitFiltersWithNullptr();
	void InitFilters(double sample_rate);
	void InitHighShelfFilter(double sample_rate);
	void InitLowShelfFilter(double sample_rate);
	void InitParametric1Filter(double sample_rate);
	void InitParametric2Filter(double sample_rate);
	void DeleteHighShelfFilter();
	void DeleteLowShelfFilter();
	void DeleteParametric1Filter();
	void DeleteParametric2Filter();
	void DeleteFilters();
	void GetFiltersTransmittance(double frequency, double& sample);
	//============================================================================


    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void buttonClicked (Button* buttonThatWasClicked) override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;

    // Binary resources:
    static const char* spectrogram_png;
    static const int spectrogram_pngSize;


private:
    //[UserVariables]   -- You can add your own custom variables in this section.

	LookAndFeelCustom* look_and_feel_custom_;
//	ScreenComponent* screen_component_;

	//File playback
	//==============================================================================
	AudioFormatManager format_manager_;
	ScopedPointer<AudioFormatReaderSource> reader_source_;
	AudioTransportSource transport_source_;
	TransportState state_;
	//==============================================================================


	//Filters
	//==============================================================================
	HoffFilters::IIRLowShelfFilter* iir_low_shelf_filter_;
	HoffFilters::IIRHighShelfFilter* iir_high_shelf_filter_;
	HoffFilters::IIRParametricBandPassFilter* iir_parametric_band_pass_filter_1_;
	HoffFilters::IIRParametricBandPassFilter* iir_parametric_band_pass_filter_2_;

	//==============================================================================

    //[/UserVariables]

    //==============================================================================
    ScopedPointer<GroupComponent> groupComponent;
    ScopedPointer<Label> file_name_label;
    ScopedPointer<TextButton> open_text_button;
    ScopedPointer<TextButton> play_text_button;
    ScopedPointer<TextButton> pause_text_button;
    ScopedPointer<TextButton> stop_text_button;
    ScopedPointer<Slider> volume_slider;
    ScopedPointer<Slider> time_slider;
    ScopedPointer<Label> volumeLabel;
    ScopedPointer<Label> time_label;
    ScopedPointer<Slider> parametric_1_gain_slider_;
    ScopedPointer<Slider> parametric_1_frequency_slider_;
    ScopedPointer<Slider> parametric_1_q_slider_;
    ScopedPointer<Slider> parametric_2_gain_slider_;
    ScopedPointer<Slider> parametric_2_frequency_slider_;
    ScopedPointer<Slider> parametric_2_q_slider_;
    ScopedPointer<Slider> high_shelf_gain_slider_;
    ScopedPointer<Slider> high_shelf_frequency_slider_;
    ScopedPointer<Slider> low_shelf_gain_slider_;
    ScopedPointer<Slider> low_shelf_frequency_slider_;
    ScopedPointer<ScreenComponent> screen_component_;
    Image cachedImage_spectrogram_png_1;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};

//[EndFile] You can add extra defines here...
Component* createMainContentComponent() { return new MainComponent(); }
//[/EndFile]

#endif   // __JUCE_HEADER_9002020A4DD09B20__
