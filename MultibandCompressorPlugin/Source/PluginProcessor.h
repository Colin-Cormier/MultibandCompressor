/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "MultibandCompressorProcessor.h"

//==============================================================================
/**
*/
class MultibandCompressorAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    MultibandCompressorAudioProcessor();
    ~MultibandCompressorAudioProcessor() override;

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

    juce::AudioProcessorValueTreeState apvts;
    
    static const juce::StringRef s_lowThresh;
    
    static const juce::StringRef s_lowRatio;
    
    static const juce::StringRef s_lowAttack;
    
    static const juce::StringRef s_lowRelease;
    
    static const juce::StringRef s_midThresh;
    
    static const juce::StringRef s_midRatio;
    
    static const juce::StringRef s_midAttack;
    
    static const juce::StringRef s_midRelease;
    
    static const juce::StringRef s_midBandWidth;
    
    static const juce::StringRef s_highThresh;
    
    static const juce::StringRef s_highRatio;
    
    static const juce::StringRef s_highAttack;
    
    static const juce::StringRef s_highRelease;
    
    static const juce::StringRef s_progDepend;
    
    
    void threshChanged(float value, int channel);
    void ratioChanged(float value, int channel);
    void attackChanged(float value, int channel);
    void releaseChanged(float value, int channel);
    void midBandWidthChanged(float value);
    void progDependClicked(bool value);
    
    MultibandCompressorProcessor multibandCompressor;

private:
    
    juce::AudioProcessorValueTreeState::ParameterLayout createParams();
    
    int ParameterVersionHint = 1;
    
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MultibandCompressorAudioProcessor)
};
