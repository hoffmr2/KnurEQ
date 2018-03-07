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
  // low shelf filter slider and label
  m_LowShelfGain = new VstParameter(this, "ls_gain", "LowShelf Gain dB", m_ValueTreeState);
  m_LowShelfFrequency = new VstParameter(this, "ls_frequency", "LowShelf Frequency", m_ValueTreeState);
  m_HighShelfGain = new VstParameter(this, "hs_gain", "HighShelf Gain dB", m_ValueTreeState);
  m_HighShelfFrequency = new VstParameter(this, "hs_frequency", "HighShelf Frequency", m_ValueTreeState);
  m_Parametric1Gain = new VstParameter(this, "p1_gain", "Parametric Gain", m_ValueTreeState);
  m_Parametric1Frequency = new VstParameter(this, "p1_frequency", "Parametric Frequency", m_ValueTreeState);
  m_Parametric1Q = new VstParameter(this, "p1_q", "Parametric Q", m_ValueTreeState);
  m_Parametric2Gain = new VstParameter(this, "p2_gain", "Parametric Gain", m_ValueTreeState);
  m_Parametric2Frequency = new VstParameter(this, "p2_frequency", "Parametric Frequency", m_ValueTreeState);
  m_Parametric2Q = new VstParameter(this, "p2_q", "Parametric Q", m_ValueTreeState);
    setSize (700, 300);
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
    auto labelWidth = getWidth() * 0.32;
    auto labelHeight = getHeight() * 0.1;
    auto sliderWidth = getWidth() * 0.15;
    auto sliderHeight = getHeight() * 0.15;
    m_LowShelfGain->m_Label->setBounds(150, 185, labelWidth, labelHeight);
    m_LowShelfGain->m_Slider->setBounds(160, 207, sliderWidth, sliderHeight);

    m_LowShelfFrequency->m_Label->setBounds(10, 185, labelWidth, labelHeight);
    m_LowShelfFrequency->m_Slider->setBounds(20, 207, sliderWidth, sliderHeight);

    m_HighShelfGain->m_Label->setBounds(150, 240, labelWidth, labelHeight);
    m_HighShelfGain->m_Slider->setBounds(160, 262, sliderWidth, sliderHeight);

    m_HighShelfFrequency->m_Label->setBounds(10, 240, labelWidth, labelHeight);
    m_HighShelfFrequency->m_Slider->setBounds(20, 262, sliderWidth, sliderHeight);

    m_Parametric1Gain->m_Label->setBounds(290, 185, labelWidth, labelHeight);
    m_Parametric1Gain->m_Slider->setBounds(300, 207, sliderWidth, sliderHeight);

    m_Parametric1Frequency->m_Label->setBounds(430, 185, labelWidth, labelHeight);
    m_Parametric1Frequency->m_Slider->setBounds(440, 207, sliderWidth, sliderHeight);

    m_Parametric1Q->m_Label->setBounds(580, 185, labelWidth, labelHeight);
    m_Parametric1Q->m_Slider->setBounds(590, 207, sliderWidth, sliderHeight);

    m_Parametric2Gain->m_Label->setBounds(290, 240, labelWidth, labelHeight);
    m_Parametric2Gain->m_Slider->setBounds(300, 262, sliderWidth, sliderHeight);

    m_Parametric2Frequency->m_Label->setBounds(430, 240, labelWidth, labelHeight);
    m_Parametric2Frequency->m_Slider->setBounds(440, 262, sliderWidth, sliderHeight);

    m_Parametric2Q->m_Label->setBounds(580, 240, labelWidth, labelHeight);
    m_Parametric2Q->m_Slider->setBounds(590, 262, sliderWidth, sliderHeight);
}

KnurEqAudioProcessorEditor::VstParameter::VstParameter(KnurEqAudioProcessorEditor* a_Editor,
                                                       String a_ParameterID,
                                                       String a_LabelText,
                                                       AudioProcessorValueTreeState& a_ValueTreeState) {

  m_Label = new Label();
  m_Label->setText(a_LabelText, dontSendNotification);
  a_Editor->addAndMakeVisible(m_Label);
  m_Slider = new Slider();
  a_Editor->addAndMakeVisible(m_Slider);
  m_Slider->setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxLeft, true, 50, 20);
  m_Slider->setSliderStyle(Slider::Rotary);
  m_Attachment = new SliderAttachment(a_ValueTreeState, a_ParameterID, *m_Slider);


}
