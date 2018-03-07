/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
KnurEqAudioProcessorEditor::KnurEqAudioProcessorEditor (KnurEqAudioProcessor& a_Processor, AudioProcessorValueTreeState& a_ValueTreeState)
    : AudioProcessorEditor (&a_Processor), 
      m_Processor (a_Processor),
      m_ValueTreeState(a_ValueTreeState)
{
  m_LowShelfGainLAbel = new Label();
  m_LowShelfGainLAbel->setText("LowShelf Gain dB", dontSendNotification);
  addAndMakeVisible(m_LowShelfGainLAbel);
  m_LowShelfGainSlider = new Slider();
  addAndMakeVisible(m_LowShelfGainSlider);
  m_LowShelfGainSlider->setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxLeft, true, 50,20);
  m_LowShelfGainSlider->setSliderStyle(Slider::Rotary);
  m_LowShelfGainAttachment = new SliderAttachment(m_ValueTreeState, "ls_gain", *m_LowShelfGainSlider);

  m_LowShelfFrequencyLAbel = new Label();
  m_LowShelfFrequencyLAbel->setText("LowShelf Frequency dB", dontSendNotification);
  addAndMakeVisible(m_LowShelfFrequencyLAbel);
  m_LowShelfFrequencySlider = new Slider();
  addAndMakeVisible(m_LowShelfFrequencySlider);
  m_LowShelfFrequencySlider->setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxLeft, true, 50, 20);
  m_LowShelfFrequencySlider->setSliderStyle(Slider::Rotary);
  m_LowShelfFrequencyAttachment = new SliderAttachment(m_ValueTreeState, "ls_frequency", *m_LowShelfFrequencySlider);
    setSize (400, 300);
}

KnurEqAudioProcessorEditor::~KnurEqAudioProcessorEditor()
{
}

//==============================================================================
void KnurEqAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);
}

void KnurEqAudioProcessorEditor::resized()
{
    auto labelWidth = getWidth() * 0.35;
    auto labelHeight = getHeight() * 0.1;
    auto sliderWidth = getWidth() * 0.35;
    auto sliderHeight = getHeight() * 0.15;
    m_LowShelfGainLAbel->setBounds(10, 240, labelWidth, labelHeight);
    m_LowShelfGainSlider->setBounds(10, 262, sliderWidth, sliderHeight);

    m_LowShelfFrequencyLAbel->setBounds(10, 185, labelWidth, labelHeight);
    m_LowShelfFrequencySlider->setBounds(10, 207, sliderWidth, sliderHeight);
}
