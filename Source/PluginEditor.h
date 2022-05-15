/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "CustomLookAndFeel.h"

//==============================================================================

struct CustomRotarySlider : juce::Slider
{
    CustomRotarySlider();
    ~CustomRotarySlider() override;

    void paint (juce::Graphics& g) override;

    void mouseDown (const juce::MouseEvent& event) override;
    void mouseUp (const juce::MouseEvent& event) override;

private:
    CustomLookAndFeel customLookAndFeel;

    juce::Colour blue      = juce::Colour::fromFloatRGBA (0.43f, 0.83f, 1.0f, 1.0f);
    juce::Colour grey      = juce::Colour::fromFloatRGBA (0.42f, 0.42f, 0.42f, 1.0f);
    juce::Colour blackGrey = juce::Colour::fromFloatRGBA (0.2f,  0.2f,  0.2f, 1.0f);
    juce::Colour offWhite  = juce::Colour::fromFloatRGBA (0.83f, 0.84f, 0.9f, 1.f);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CustomRotarySlider)
};

class CustomLabel  : public juce::Label
{
public:
	CustomLabel()
	{
		setFont (15.0f);
		setColour (juce::Label::textColourId, grey);
		setJustificationType (juce::Justification::centred);
	}

	~CustomLabel(){}

private:
	juce::Colour grey = juce::Colour::fromFloatRGBA (0.42f, 0.42f, 0.42f, 1.0f);

};

class SimpleEQAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    SimpleEQAudioProcessorEditor (SimpleEQAudioProcessor&);
    ~SimpleEQAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SimpleEQAudioProcessor& audioProcessor;

    CustomRotarySlider peakFreqSlider, 
        peakGainSlider, 
        peakQualitySlider,
        lowCutFreqSlider, 
        highCutFreqSlider;

    CustomLabel peakFreqLabel, 
        peakGainLabel, 
        peakQualityLabel,
        lowCutFreqLabel, 
        highCutFreqLabel;

    using APVTS = juce::AudioProcessorValueTreeState;
    using Attachment = APVTS::SliderAttachment;

    Attachment peakFreqSliderAttachment, 
        peakGainSliderAttachment, 
        peakQualitySliderAttachment,
        lowCutFreqSliderAttachment, 
        highCutFreqSliderAttachment;

    CustomLookAndFeel customLookAndFeel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleEQAudioProcessorEditor)
};
