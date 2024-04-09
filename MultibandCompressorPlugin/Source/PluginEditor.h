/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class MultibandCompressorAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                                    public juce::Slider::Listener,
                                                    public juce::Button::Listener
    
{
public:
    MultibandCompressorAudioProcessorEditor (MultibandCompressorAudioProcessor&);
    ~MultibandCompressorAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
    void sliderValueChanged(juce::Slider* slider) override;
    void buttonClicked(juce::Button *button) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MultibandCompressorAudioProcessor& audioProcessor;
    
    juce::Slider ratioSliderLow;
    juce::Slider ratioSliderMid;
    juce::Slider ratioSliderHigh;
    
    juce::Slider threshSliderLow;
    juce::Slider threshSliderMid;
    juce::Slider threshSliderHigh;
    
    juce::Slider attackSliderLow;
    juce::Slider attackSliderMid;
    juce::Slider attackSliderHigh;
    
    juce::Slider releaseSliderLow;
    juce::Slider releaseSliderMid;
    juce::Slider releaseSliderHigh;
    
    juce::ToggleButton progDependentButton;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MultibandCompressorAudioProcessorEditor)
};
