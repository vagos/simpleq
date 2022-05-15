/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================

CustomRotarySlider::CustomRotarySlider()
{
    setSliderStyle (juce::Slider::SliderStyle::RotaryHorizontalDrag);
    setTextBoxStyle (juce::Slider::TextBoxBelow, true, 0, 0);
    setLookAndFeel (&customLookAndFeel);
    setColour (juce::Slider::rotarySliderFillColourId, blue);
    setColour (juce::Slider::textBoxTextColourId, blackGrey);
    setColour (juce::Slider::textBoxOutlineColourId, grey);
    setVelocityBasedMode (true);
    setVelocityModeParameters (0.5, 1, 0.09, false);
    setRotaryParameters (juce::MathConstants<float>::pi * 1.25f,
                         juce::MathConstants<float>::pi * 2.75f,
                         true);
    setWantsKeyboardFocus (true);
}

CustomRotarySlider::~CustomRotarySlider()
{
    setLookAndFeel(nullptr);
}

void CustomRotarySlider::paint (juce::Graphics& g)
{
    juce::Slider::paint (g);

    if (hasKeyboardFocus (false))
    {
        auto length = getHeight() > 15 ? 5.0f : 4.0f;
        auto thick  = getHeight() > 15 ? 3.0f : 2.5f;

        g.setColour (findColour (juce::Slider::textBoxOutlineColourId));

        //          fromX       fromY        toX                  toY
        g.drawLine (0,          0,           0,                   length,               thick);
        g.drawLine (0,          0,           length,              0,                    thick);
        g.drawLine (0,          getHeight(), 0,                   getHeight() - length, thick);
        g.drawLine (0,          getHeight(), length,              getHeight(),          thick);
        g.drawLine (getWidth(), getHeight(), getWidth() - length, getHeight(),          thick);
        g.drawLine (getWidth(), getHeight(), getWidth(),          getHeight() - length, thick);
        g.drawLine (getWidth(), 0,           getWidth() - length, 0,                    thick);
        g.drawLine (getWidth(), 0,           getWidth(),          length,               thick);
    }
}

void CustomRotarySlider::mouseDown (const juce::MouseEvent& event)
{
    juce::Slider::mouseDown (event);

    // setMouseCursor (juce::MouseCursor::NoCursor);
}

void CustomRotarySlider::mouseUp (const juce::MouseEvent& event)
{
    juce::Slider::mouseUp (event);

    // juce::Desktop::getInstance().getMainMouseSource().setScreenPosition (event.source.getLastMouseDownPosition());
    // setMouseCursor (juce::MouseCursor::NormalCursor);
}

SimpleEQAudioProcessorEditor::SimpleEQAudioProcessorEditor (SimpleEQAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p),
    peakFreqSliderAttachment(audioProcessor.apvts, "Peak Freq", peakFreqSlider),
    peakGainSliderAttachment(audioProcessor.apvts, "Peak Gain", peakGainSlider),
    peakQualitySliderAttachment(audioProcessor.apvts, "Peak Quality", peakQualitySlider),
    lowCutFreqSliderAttachment(audioProcessor.apvts, "LowCut Freq", lowCutFreqSlider),
    highCutFreqSliderAttachment(audioProcessor.apvts, "HighCut Freq", highCutFreqSlider)

{
    setWantsKeyboardFocus (true);

    juce::LookAndFeel::getDefaultLookAndFeel().setDefaultSansSerifTypefaceName ("Source Code Pro");

    peakFreqLabel.setText("peak (Hz)", juce::NotificationType::dontSendNotification);
    peakFreqLabel.attachToComponent(&peakFreqSlider, false);
    lowCutFreqLabel.setText("high (Hz)", juce::NotificationType::dontSendNotification);
    lowCutFreqLabel.attachToComponent(&lowCutFreqSlider, false);
    highCutFreqLabel.setText("low (Hz)", juce::NotificationType::dontSendNotification);
    highCutFreqLabel.attachToComponent(&highCutFreqSlider, false);

    addAndMakeVisible(peakFreqSlider);
    addAndMakeVisible(peakGainSlider);
    addAndMakeVisible(peakQualitySlider);
    addAndMakeVisible(lowCutFreqSlider);
    addAndMakeVisible(highCutFreqSlider);

    setLookAndFeel(&customLookAndFeel);

    setSize (500, 250);
}

SimpleEQAudioProcessorEditor::~SimpleEQAudioProcessorEditor()
{
}

//==============================================================================
void SimpleEQAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::black);
    g.setFont (30);
    g.setColour (juce::Colours::white);
    g.drawText ("Simple EQ", 150, 0, getWidth(), getHeight() / 2, juce::Justification::centred);
}

void SimpleEQAudioProcessorEditor::resized()
{

    float y_gap = 70;
    float y_begin = 30;
    float size = 70;
    float size_small = 50;

    lowCutFreqSlider.setBounds (30, y_begin, size, size);
    peakFreqSlider.setBounds (125, y_begin, size, size);
    peakGainSlider.setBounds (125, y_begin + y_gap, size, size);
    peakQualitySlider.setBounds (125, y_begin + y_gap * 2, size, size);
    highCutFreqSlider.setBounds (220, y_begin, size, size);

}
