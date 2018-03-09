/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "../Include/fftw3.h"

#if JUCE_WINDOWS
  #ifdef JUCE_DEBUG
    #pragma comment (lib, "..\\..\\Lib\\libfftw3.lib")     // ICU Core Lib debug
  #else
    #pragma comment (lib, "../Lib/libfftw3.lib")      // ICU Core Lib release
  #endif
#endif


//==============================================================================
KnurEqAudioProcessor::KnurEqAudioProcessor()

#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ),
#endif

       m_Parameters(*this, nullptr)
{
  m_Parameters.createAndAddParameter("p1_gain",
    "Parametric 1 Gain",
    String("dB"),
    NormalisableRange<float>(-24.0f, 24.0f),
    0.0f,
    nullptr,
    nullptr);

  m_Parameters.createAndAddParameter("p1_frequency",
    "Parametric 1 Frequency", 
    String("Hz"),
    NormalisableRange<float>(20.0f, 20000.0f),
    1000.0f,
    nullptr,
    nullptr);

  m_Parameters.createAndAddParameter("p1_q",
    "Parametric 1 Q",
    String(),
    NormalisableRange<float>(0.0001f, 10.0f),
    0.01f,
    nullptr,
    nullptr);

  m_Parameters.createAndAddParameter("p2_gain",
    "Parametric 2 Gain",
    String("dB"),
    NormalisableRange<float>(-24.0f, 24.0f),
    0.0f,
    nullptr,
    nullptr);

  m_Parameters.createAndAddParameter("p2_frequency",
    "Parametric 2 Frequency",
    String("Hz"),
    NormalisableRange<float>(20.0f, 20000.0f),
    1000.0f,
    nullptr,
    nullptr);

  m_Parameters.createAndAddParameter("p2_q",
    "Parametric 2 Q",
    String(),
    NormalisableRange<float>(0.0001f, 10.0f),
    0.01f,
    nullptr,
    nullptr);

  m_Parameters.createAndAddParameter("ls_gain",
    "Low Shelf Gain",
    String("dB"),
    NormalisableRange<float>(-24.0f, 24.0f),
    0.0f,
    nullptr,
    nullptr);

  m_Parameters.createAndAddParameter("ls_frequency",
    "Low Shelf Frequency",
    String("Hz"),
    NormalisableRange<float>(20.0f, 20000.0f),
    1000.0f,
    nullptr,
    nullptr);

  m_Parameters.createAndAddParameter("hs_gain",
    "High Shelf Gain",
    String("dB"),
    NormalisableRange<float>(-24.0f, 24.0f),
    0.0f,
    nullptr,
    nullptr);

  m_Parameters.createAndAddParameter("hs_frequency",
    "High Shelf Frequency",
    String("Hz"),
    NormalisableRange<float>(20.0f, 20000.0f),
    1000.0f,
    nullptr,
    nullptr);

  m_Parameters.state = ValueTree(Identifier("KnurEQPArameters"));
}

KnurEqAudioProcessor::~KnurEqAudioProcessor()
{
}

//==============================================================================
const String KnurEqAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool KnurEqAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool KnurEqAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool KnurEqAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double KnurEqAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int KnurEqAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int KnurEqAudioProcessor::getCurrentProgram()
{
    return 0;
}

void KnurEqAudioProcessor::setCurrentProgram (int index)
{
}

const String KnurEqAudioProcessor::getProgramName (int index)
{
    return {};
}

void KnurEqAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void KnurEqAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
  m_IIRHighShelfFilter = new IIRHighShelfFilter(*m_Parameters.getRawParameterValue("hs_frequency"),
                                                 sampleRate, 
                                                *m_Parameters.getRawParameterValue("hs_gain"));
  m_IIRLowShelfFilter = new IIRLowShelfFilter(*m_Parameters.getRawParameterValue("ls_frequency"),
                                               sampleRate, 
                                               *m_Parameters.getRawParameterValue("ls_gain"));
  m_IIRParametricBandpassFilter1 = new IIRParametricBandPassFilter(*m_Parameters.getRawParameterValue("p1_frequency"),
                                                                    sampleRate, 
                                                                   *m_Parameters.getRawParameterValue("p1_gain"), 
                                                                   *m_Parameters.getRawParameterValue("p1_q"));
  m_IIRParametricBandpassFilter2 = new IIRParametricBandPassFilter(*m_Parameters.getRawParameterValue("p2_frequency"),
                                                                    sampleRate,
                                                                   *m_Parameters.getRawParameterValue("p2_gain"),
                                                                   *m_Parameters.getRawParameterValue("p2_q"));
}

void KnurEqAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool KnurEqAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void KnurEqAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    const int totalNumInputChannels  = getTotalNumInputChannels();
    const int totalNumOutputChannels = getTotalNumOutputChannels();

    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    m_IIRLowShelfFilter->ChangeCutoffFrequency(*m_Parameters.getRawParameterValue("ls_frequency"));
    m_IIRLowShelfFilter->SetGainDb(*m_Parameters.getRawParameterValue("ls_gain"));

    m_IIRHighShelfFilter->ChangeCutoffFrequency(*m_Parameters.getRawParameterValue("hs_frequency"));
    m_IIRHighShelfFilter->SetGainDb(*m_Parameters.getRawParameterValue("hs_gain"));

    m_IIRParametricBandpassFilter1->ChangeCutoffFrequency(*m_Parameters.getRawParameterValue("p1_frequency"));
    m_IIRParametricBandpassFilter1->SetGainDb(*m_Parameters.getRawParameterValue("p1_gain"));
    m_IIRParametricBandpassFilter1->ChangeQFactor(*m_Parameters.getRawParameterValue("p1_q"));

    m_IIRParametricBandpassFilter2->ChangeCutoffFrequency(*m_Parameters.getRawParameterValue("p2_frequency"));
    m_IIRParametricBandpassFilter2->SetGainDb(*m_Parameters.getRawParameterValue("p2_gain"));
    m_IIRParametricBandpassFilter2->ChangeQFactor(*m_Parameters.getRawParameterValue("p2_q"));


      float* channelLeft = buffer.getWritePointer (0);
      float* channelRight = buffer.getWritePointer(1);
      for(size_t sample = 0; sample < buffer.getNumSamples(); ++sample) {
          
        channelLeft[sample] = m_IIRLowShelfFilter->FilterOutputLeft(channelLeft[sample]);
        channelLeft[sample] = m_IIRLowShelfFilter->FilterOutputLeft(channelLeft[sample]);
        channelLeft[sample] = m_IIRParametricBandpassFilter1->FilterOutputLeft(channelLeft[sample]);
        channelLeft[sample] = m_IIRParametricBandpassFilter2->FilterOutputLeft(channelLeft[sample]);

        channelRight[sample] = m_IIRLowShelfFilter->FilterOutputRight(channelRight[sample]);
        channelRight[sample] = m_IIRLowShelfFilter->FilterOutputRight(channelRight[sample]);
        channelRight[sample] = m_IIRParametricBandpassFilter1->FilterOutputRight(channelRight[sample]);
        channelRight[sample] = m_IIRParametricBandpassFilter2->FilterOutputRight(channelRight[sample]);
      }

}

//==============================================================================
bool KnurEqAudioProcessor::hasEditor() const
{
    return true;
}

AudioProcessorEditor* KnurEqAudioProcessor::createEditor()
{
    return new KnurEqAudioProcessorEditor (*this, m_Parameters);
}

//==============================================================================
void KnurEqAudioProcessor::getStateInformation (MemoryBlock& destData)
{
  ScopedPointer<XmlElement> xml(m_Parameters.state.createXml());
  copyXmlToBinary(*xml, destData);
}

void KnurEqAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
  ScopedPointer<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
  if (xmlState != nullptr)
    if (xmlState->hasTagName(m_Parameters.state.getType()))
      m_Parameters.state = ValueTree::fromXml(*xmlState);
}

float KnurEqAudioProcessor::getFilterstransmitance(double a_Frequency) const {

  if((m_IIRHighShelfFilter == nullptr) ||
     (m_IIRLowShelfFilter == nullptr) ||
     (m_IIRParametricBandpassFilter1 == nullptr) ||
     (m_IIRParametricBandpassFilter2 == nullptr)) {
    
    return 1;
  }

  auto sample = m_IIRLowShelfFilter->Spectrum(a_Frequency);
  sample *= m_IIRHighShelfFilter->Spectrum(a_Frequency);
  sample *= m_IIRParametricBandpassFilter1->Spectrum(a_Frequency);
  sample *= m_IIRParametricBandpassFilter2->Spectrum(a_Frequency);

  return sample;
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new KnurEqAudioProcessor();
}
