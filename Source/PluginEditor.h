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

    struct VstParameter {
      
      VstParameter(KnurEqAudioProcessorEditor* a_Editor, 
                   String a_ParameterID, 
                   String a_LabelText, 
                   AudioProcessorValueTreeState& a_ValueTreeState);

      ScopedPointer<Label> m_Label;
      ScopedPointer<Slider> m_Slider;
      ScopedPointer<SliderAttachment> m_Attachment;
    };
    KnurEqAudioProcessor& m_Processor;
    AudioProcessorValueTreeState& m_ValueTreeState;

    ScopedPointer<VstParameter> m_LowShelfGain;
    ScopedPointer<VstParameter> m_LowShelfFrequency;
    ScopedPointer<VstParameter> m_HighShelfGain;
    ScopedPointer<VstParameter> m_HighShelfFrequency;
    ScopedPointer<VstParameter> m_Parametric1Gain;
    ScopedPointer<VstParameter> m_Parametric1Frequency;
    ScopedPointer<VstParameter> m_Parametric1Q;
    ScopedPointer<VstParameter> m_Parametric2Gain;
    ScopedPointer<VstParameter> m_Parametric2Frequency;
    ScopedPointer<VstParameter> m_Parametric2Q;


  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KnurEqAudioProcessorEditor)
};
