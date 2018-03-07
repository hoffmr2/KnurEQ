/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
//==============================================================================
/**
*/
class KnurEqAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    KnurEqAudioProcessorEditor (KnurEqAudioProcessor&, AudioProcessorValueTreeState&);
    ~KnurEqAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    KnurEqAudioProcessor& m_Processor;
    AudioProcessorValueTreeState& m_ValueTreeState;

    ScopedPointer<Label> m_LowShelfGainLAbel;
    ScopedPointer<Slider> m_LowShelfGainSlider;
    ScopedPointer<SliderAttachment> m_LowShelfGainAttachment;

    ScopedPointer<Label> m_LowShelfFrequencyLAbel;
    ScopedPointer<Slider> m_LowShelfFrequencySlider;
    ScopedPointer<SliderAttachment> m_LowShelfFrequencyAttachment;


  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KnurEqAudioProcessorEditor)
};
