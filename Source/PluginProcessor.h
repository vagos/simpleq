/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

enum Slope 
{
    Slope_12,
    Slope_24,
    Slope_36,
    Slope_48,
};

struct ChainSettings
{
    float peakFreq{0}, peakGainInDecibels{0}, peakQuality{1.f},
          lowCutFreq{0}, highCutFreq{0};
    Slope lowCutSlope{Slope::Slope_12}, highCutSlope{Slope::Slope_12};
};

ChainSettings getChainSettings(juce::AudioProcessorValueTreeState& apvts);

using Filter = juce::dsp::IIR::Filter<float>;
using CutFilter = juce::dsp::ProcessorChain<Filter, Filter, Filter, Filter>;
using MonoChain = juce::dsp::ProcessorChain<CutFilter, Filter, CutFilter>;

enum ChainPositions
{
    LowCut,
    Peak,
    HighCut
};

//==============================================================================
/**
*/
class SimpleEQAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    SimpleEQAudioProcessor();
    ~SimpleEQAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    static juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    juce::AudioProcessorValueTreeState apvts{*this, nullptr, "Parameters", createParameterLayout()};

private:
    
    MonoChain leftChain, rightChain;

    void updatePeakFilter(const ChainSettings& chainSettings);
    using Coefficients = Filter::CoefficientsPtr;
    static void updateCoefficients(Coefficients &old, const Coefficients &replacements);

    template<typename ChainType, typename CoefficientType>
    void updateCutFilter(ChainType& chain,
            const CoefficientType& cutCoefficients, 
            const Slope& slope)
    {

        chain.template setBypassed<0>(true);
        chain.template setBypassed<1>(true);
        chain.template setBypassed<2>(true);
        chain.template setBypassed<3>(true);

        switch (slope)
        {
            case Slope_12:
            {
                *chain.template get<0>().coefficients = *cutCoefficients[0];
                chain.template setBypassed<0>(false);
                break;
            }

            case Slope_24:
            {
                *chain.template get<0>().coefficients = *cutCoefficients[0];
                chain.template setBypassed<0>(false);
                *chain.template get<1>().coefficients = *cutCoefficients[1];
                chain.template setBypassed<1>(false);
                break;
            }

            case Slope_36:
            {

                *chain.template get<0>().coefficients = *cutCoefficients[0];
                chain.template setBypassed<0>(false);
                *chain.template get<1>().coefficients = *cutCoefficients[1];
                chain.template setBypassed<1>(false);
                *chain.template get<2>().coefficients = *cutCoefficients[2];
                chain.template setBypassed<2>(false);
                break;

            }
            case Slope_48:
            {

                *chain.template get<0>().coefficients = *cutCoefficients[0];
                chain.template setBypassed<0>(false);
                *chain.template get<1>().coefficients = *cutCoefficients[1];
                chain.template setBypassed<1>(false);
                *chain.template get<2>().coefficients = *cutCoefficients[2];
                chain.template setBypassed<2>(false);
                *chain.template get<3>().coefficients = *cutCoefficients[3];
                chain.template setBypassed<3>(false);
                break;
            }
                
        }

    }

    void updateLowCutFilter(const ChainSettings& chainSettings);
    void updateHighCutFilter(const ChainSettings& chainSettings);


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleEQAudioProcessor)
};
