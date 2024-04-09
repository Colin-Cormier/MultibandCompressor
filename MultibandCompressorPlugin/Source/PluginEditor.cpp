/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MultibandCompressorAudioProcessorEditor::MultibandCompressorAudioProcessorEditor (MultibandCompressorAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (816, 400);
    
    threshSliderLow.setBounds(20, 20, 106, 106);
    threshSliderLow.setRange(-20.0, 0.0);
    threshSliderLow.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    threshSliderLow.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    addAndMakeVisible(threshSliderLow);
    threshSliderLow.addListener(this);
    
    ratioSliderLow.setBounds(146, 20, 106, 106);
    ratioSliderLow.setRange(1.0, 20.0);
    ratioSliderLow.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    ratioSliderLow.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    addAndMakeVisible(ratioSliderLow);
    ratioSliderLow.addListener(this);
    
    attackSliderLow.setBounds(20, 146, 106, 106);
    attackSliderLow.setRange(0, 0.1);
    attackSliderLow.setSkewFactorFromMidPoint(0.001);
    attackSliderLow.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    attackSliderLow.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    addAndMakeVisible(attackSliderLow);
    attackSliderLow.addListener(this);
    
    releaseSliderLow.setBounds(146, 146, 106, 106);
    releaseSliderLow.setRange(0, 5);
    releaseSliderLow.setSkewFactorFromMidPoint(0.1);
    releaseSliderLow.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    releaseSliderLow.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    addAndMakeVisible(releaseSliderLow);
    releaseSliderLow.addListener(this);
    
    threshSliderMid.setBounds(292, 20, 106, 106);
    threshSliderMid.setRange(-20.0, 0.0);
    threshSliderMid.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    threshSliderMid.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    addAndMakeVisible(threshSliderMid);
    threshSliderMid.addListener(this);
    
    ratioSliderMid.setBounds(418, 20, 106, 106);
    ratioSliderMid.setRange(1.0, 20.0);
    ratioSliderMid.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    ratioSliderMid.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    addAndMakeVisible(ratioSliderMid);
    ratioSliderMid.addListener(this);
    
    attackSliderMid.setBounds(292, 146, 106, 106);
    attackSliderMid.setRange(0, 0.1);
    attackSliderMid.setSkewFactorFromMidPoint(0.001);
    attackSliderMid.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    attackSliderMid.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    addAndMakeVisible(attackSliderMid);
    attackSliderMid.addListener(this);
    
    releaseSliderMid.setBounds(418, 146, 106, 106);
    releaseSliderMid.setRange(0, 5);
    releaseSliderMid.setSkewFactorFromMidPoint(0.1);
    releaseSliderMid.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    releaseSliderMid.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    addAndMakeVisible(releaseSliderMid);
    releaseSliderMid.addListener(this);
    
    threshSliderHigh.setBounds(564, 20, 106, 106);
    threshSliderHigh.setRange(-20.0, 0.0);
    threshSliderHigh.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    threshSliderHigh.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    addAndMakeVisible(threshSliderHigh);
    threshSliderHigh.addListener(this);
    
    ratioSliderHigh.setBounds(690, 20, 106, 106);
    ratioSliderHigh.setRange(1.0, 20.0);
    ratioSliderHigh.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    ratioSliderHigh.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    addAndMakeVisible(ratioSliderHigh);
    ratioSliderHigh.addListener(this);
    
    attackSliderHigh.setBounds(564, 146, 106, 106);
    attackSliderHigh.setRange(0, 0.1);
    attackSliderHigh.setSkewFactorFromMidPoint(0.001);
    attackSliderHigh.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    attackSliderHigh.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    addAndMakeVisible(attackSliderHigh);
    attackSliderHigh.addListener(this);
    
    releaseSliderHigh.setBounds(690, 146, 106, 106);
    releaseSliderHigh.setRange(0, 5);
    releaseSliderHigh.setSkewFactorFromMidPoint(0.1);
    releaseSliderHigh.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    releaseSliderHigh.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    addAndMakeVisible(releaseSliderHigh);
    releaseSliderHigh.addListener(this);
    
    progDependentButton.setBounds(375, 300, 100, 20);
    progDependentButton.setButtonText("AUTO");
    progDependentButton.setToggleState(false, juce::dontSendNotification);
    addAndMakeVisible(progDependentButton);
    progDependentButton.addListener(this);
    
}

MultibandCompressorAudioProcessorEditor::~MultibandCompressorAudioProcessorEditor()
{
}

//==============================================================================
void MultibandCompressorAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (30.0f);
    //g.drawFittedText ("Multiband Compressor", getLocalBounds(), juce::Justification::centredTop, 1);
    g.fillAll(juce::Colours::steelblue);
    
    g.setColour(juce::Colours::black);
    g.fillRect(269, 0, 6, 400);
    g.fillRect(541, 0, 6, 400);
    g.fillRect(0, 0, 4, 400);
    g.fillRect(812, 0, 4, 400);
    g.fillRect(0, 396, 816, 4);
    g.fillRect(0, 0, 816, 4);

    g.setColour(juce::Colours::whitesmoke);
    g.drawRoundedRectangle(10, 10, 252, 380, 20, 5);
    g.drawRoundedRectangle(282, 10, 252, 380, 20, 5);
    g.drawRoundedRectangle(554, 10, 252, 380, 20, 5);
    
    g.setColour(juce::Colours::grey);
    g.setOpacity(0.4);
    g.fillRoundedRectangle(20, 20, 232, 243, 10);
    g.fillRoundedRectangle(292, 20, 232, 243, 10);
    g.fillRoundedRectangle(564, 20, 232, 243, 10);
    
    g.setColour(juce::Colours::white);
    g.drawText("LOWs", 96, 350, 80, 20, juce::Justification::centred);
    g.drawText("MIDs", 368, 350, 80, 20, juce::Justification::centred);
    g.drawText("HIGHs", 640, 350, 80, 20, juce::Justification::centred);
  
}

void MultibandCompressorAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

void MultibandCompressorAudioProcessorEditor::sliderValueChanged(juce::Slider *slider)
{
    if(slider == &ratioSliderLow)
        audioProcessor.multibandCompressor.setRatio(ratioSliderLow.getValue(), 0);
    
    if(slider == &ratioSliderMid)
        audioProcessor.multibandCompressor.setRatio(ratioSliderMid.getValue(), 1);
    
    if(slider == &ratioSliderHigh)
        audioProcessor.multibandCompressor.setRatio(ratioSliderHigh.getValue(), 2);
    
    
    
    if(slider == &threshSliderLow)
        audioProcessor.multibandCompressor.setThreshold(threshSliderLow.getValue(), 0);
    
    if(slider == &threshSliderMid)
        audioProcessor.multibandCompressor.setThreshold(threshSliderMid.getValue(), 1);
    
    if(slider == &threshSliderHigh)
        audioProcessor.multibandCompressor.setThreshold(threshSliderHigh.getValue(), 2);
    
    
    
    if(slider == &attackSliderLow)
        audioProcessor.multibandCompressor.setAttack(attackSliderLow.getValue(), 0);
    
    if(slider == &attackSliderMid)
        audioProcessor.multibandCompressor.setAttack(attackSliderMid.getValue(), 1);
    
    if(slider == &attackSliderHigh)
        audioProcessor.multibandCompressor.setAttack(attackSliderHigh.getValue(), 2);
    
    
    
    if(slider == &releaseSliderLow)
        audioProcessor.multibandCompressor.setRelease(releaseSliderLow.getValue(), 0);
    
    if(slider == &releaseSliderMid)
        audioProcessor.multibandCompressor.setRelease(releaseSliderMid.getValue(), 1);
    
    if(slider == &releaseSliderHigh)
        audioProcessor.multibandCompressor.setRelease(releaseSliderHigh.getValue(), 2);
    
}

void MultibandCompressorAudioProcessorEditor::buttonClicked(juce::Button *button)
{
    if ( button == &progDependentButton){
        audioProcessor.multibandCompressor.compressor.progDependent = progDependentButton.getToggleState();
        attackSliderLow.setEnabled(audioProcessor.multibandCompressor.compressor.progDependent);
    }
}
