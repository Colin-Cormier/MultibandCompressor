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
class MultibandCompressorAudioProcessorEditor  : public juce::AudioProcessorEditor
                                                   
    
{
public:
    MultibandCompressorAudioProcessorEditor (MultibandCompressorAudioProcessor&);
    ~MultibandCompressorAudioProcessorEditor() override;
    
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    
    using ButtonAttachment = juce::AudioProcessorValueTreeState::ButtonAttachment;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    

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
    
    juce::Slider midBandWidthChange;
    
    juce::ToggleButton progDependentButton;
    
    std::vector <std::unique_ptr <SliderAttachment>> sliderAttachments;
    std::vector <std::unique_ptr <ButtonAttachment>> buttonAttachments;
                                 
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MultibandCompressorAudioProcessorEditor)
};
