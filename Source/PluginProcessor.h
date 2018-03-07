/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#ifndef PLUGIN_PROCESSOR_H
#define PLUGIN_PROCESSOR_H

#include "digital_filters.h"
#include "../JuceLibraryCode/JuceHeader.h"

using HoffFilters::IIRParametricBandPassFilter;
using HoffFilters::IIRLowShelfFilter;
using HoffFilters::IIRHighShelfFilter;


//==============================================================================
/**
*/
class KnurEqAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    KnurEqAudioProcessor();
    ~KnurEqAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect () const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

private:

    AudioProcessorValueTreeState m_Parameters;

    ScopedPointer<IIRLowShelfFilter> m_IIRLowShelfFilter;
    ScopedPointer<IIRHighShelfFilter> m_IIRHighShelfFilter;
    ScopedPointer<IIRParametricBandPassFilter> m_IIRParametricBandpassFilter1;
    ScopedPointer<IIRParametricBandPassFilter> m_IIRParametricBandpassFilter2;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KnurEqAudioProcessor)
};

#endif // PLUGIN_PROCESSOR
