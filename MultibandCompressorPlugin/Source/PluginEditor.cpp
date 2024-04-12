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
    threshSliderLow.setRange(-96.0, 0.0);
    threshSliderLow.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    threshSliderLow.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    threshSliderLow.onValueChange = [this](){
         audioProcessor.threshChanged(threshSliderLow.getValue(), 0);
    };
    addAndMakeVisible(threshSliderLow);
    
    ratioSliderLow.setBounds(146, 20, 106, 106);
    ratioSliderLow.setRange(1.0, 20.0);
    ratioSliderLow.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    ratioSliderLow.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    ratioSliderLow.onValueChange = [this](){
        audioProcessor.ratioChanged(ratioSliderLow.getValue(), 0);
    };
    addAndMakeVisible(ratioSliderLow);
    
    attackSliderLow.setBounds(20, 146, 106, 106);
    attackSliderLow.setRange(0.0, 0.1);
    attackSliderLow.setSkewFactorFromMidPoint(0.001);
    attackSliderLow.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    attackSliderLow.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    attackSliderLow.onValueChange = [this](){
        audioProcessor.attackChanged(attackSliderLow.getValue(), 0);
    };
    addAndMakeVisible(attackSliderLow);
    
    releaseSliderLow.setBounds(146, 146, 106, 106);
    releaseSliderLow.setRange(0.0, 5.0);
    releaseSliderLow.setSkewFactorFromMidPoint(0.1);
    releaseSliderLow.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    releaseSliderLow.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    releaseSliderLow.onValueChange = [this](){
        audioProcessor.releaseChanged(releaseSliderLow.getValue(), 0);
    };
    addAndMakeVisible(releaseSliderLow);
    
    threshSliderMid.setBounds(292, 20, 106, 106);
    threshSliderMid.setRange(-20.0, 0.0);
    threshSliderMid.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    threshSliderMid.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    threshSliderMid.onValueChange = [this](){
        audioProcessor.threshChanged(threshSliderMid.getValue(), 1);
    };
    addAndMakeVisible(threshSliderMid);
    
    ratioSliderMid.setBounds(418, 20, 106, 106);
    ratioSliderMid.setRange(1.0, 20.0);
    ratioSliderMid.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    ratioSliderMid.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    ratioSliderMid.onValueChange = [this](){
        audioProcessor.ratioChanged(ratioSliderMid.getValue(), 1);
    };
    addAndMakeVisible(ratioSliderMid);
    
    attackSliderMid.setBounds(292, 146, 106, 106);
    attackSliderMid.setRange(0.0, 0.1);
    attackSliderMid.setSkewFactorFromMidPoint(0.001);
    attackSliderMid.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    attackSliderMid.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    attackSliderMid.onValueChange = [this](){
        audioProcessor.attackChanged(attackSliderMid.getValue(), 1);
    };
    addAndMakeVisible(attackSliderMid);
    
    releaseSliderMid.setBounds(418, 146, 106, 106);
    releaseSliderMid.setRange(0.0, 5.0);
    releaseSliderMid.setSkewFactorFromMidPoint(0.1);
    releaseSliderMid.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    releaseSliderMid.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    releaseSliderMid.onValueChange = [this](){
        audioProcessor.releaseChanged(releaseSliderMid.getValue(), 1);
    };
    addAndMakeVisible(releaseSliderMid);
    
    threshSliderHigh.setBounds(564, 20, 106, 106);
    threshSliderHigh.setRange(-20.0, 0.0);
    threshSliderHigh.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    threshSliderHigh.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    threshSliderHigh.onValueChange = [this](){
        audioProcessor.threshChanged(threshSliderHigh.getValue(), 2);
    };
    addAndMakeVisible(threshSliderHigh);
    
    ratioSliderHigh.setBounds(690, 20, 106, 106);
    ratioSliderHigh.setRange(1.0, 20.0);
    ratioSliderHigh.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    ratioSliderHigh.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    ratioSliderHigh.onValueChange = [this](){
        audioProcessor.ratioChanged(ratioSliderHigh.getValue(), 2);
    };
    addAndMakeVisible(ratioSliderHigh);
    
    attackSliderHigh.setBounds(564, 146, 106, 106);
    attackSliderHigh.setRange(0.0, 0.1);
    attackSliderHigh.setSkewFactorFromMidPoint(0.001);
    attackSliderHigh.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    attackSliderHigh.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    attackSliderHigh.onValueChange = [this](){
        audioProcessor.attackChanged(attackSliderHigh.getValue(), 2);
    };
    addAndMakeVisible(attackSliderHigh);
    
    releaseSliderHigh.setBounds(690, 146, 106, 106);
    releaseSliderHigh.setRange(0.0, 5.0);
    releaseSliderHigh.setSkewFactorFromMidPoint(0.1);
    releaseSliderHigh.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    releaseSliderHigh.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    releaseSliderHigh.onValueChange = [this](){
        audioProcessor.releaseChanged(releaseSliderHigh.getValue(), 2);
    };
    addAndMakeVisible(releaseSliderHigh);
    
    midBandWidthChange.setBounds(316, 262, 80, 80);
    midBandWidthChange.setRange(-0.5, 1.0);
    midBandWidthChange.setSkewFactorFromMidPoint(0.0);
    midBandWidthChange.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    midBandWidthChange.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    midBandWidthChange.onValueChange = [this](){
        audioProcessor.midBandWidthChanged(midBandWidthChange.getValue());
    };
    addAndMakeVisible(midBandWidthChange);
    
    progDependentButton.setBounds(428, 290, 100, 20);
    progDependentButton.setButtonText("AUTO");
    progDependentButton.setToggleState(false, juce::dontSendNotification);
    progDependentButton.onClick = [this]() {
        
        bool progDependState = progDependentButton.getToggleState();
        
        audioProcessor.progDependClicked(progDependState);
        
        attackSliderLow.setEnabled(!progDependState);
        attackSliderMid.setEnabled(!progDependState);
        attackSliderHigh.setEnabled(!progDependState);
        
        releaseSliderLow.setEnabled(!progDependState);
        releaseSliderMid.setEnabled(!progDependState);
        releaseSliderHigh.setEnabled(!progDependState);
        
    };
    addAndMakeVisible(progDependentButton);
    
    sliderAttachments.emplace_back(new SliderAttachment(audioProcessor.apvts, MultibandCompressorAudioProcessor::s_lowThresh, threshSliderLow));
    sliderAttachments.emplace_back(new SliderAttachment(audioProcessor.apvts, MultibandCompressorAudioProcessor::s_lowRatio, ratioSliderLow));
    sliderAttachments.emplace_back(new SliderAttachment(audioProcessor.apvts, MultibandCompressorAudioProcessor::s_lowAttack, attackSliderLow));
    sliderAttachments.emplace_back(new SliderAttachment(audioProcessor.apvts, MultibandCompressorAudioProcessor::s_lowRelease, releaseSliderLow));
    
    sliderAttachments.emplace_back(new SliderAttachment(audioProcessor.apvts, MultibandCompressorAudioProcessor::s_midThresh, threshSliderMid));
    sliderAttachments.emplace_back(new SliderAttachment(audioProcessor.apvts, MultibandCompressorAudioProcessor::s_midRatio, ratioSliderMid));
    sliderAttachments.emplace_back(new SliderAttachment(audioProcessor.apvts, MultibandCompressorAudioProcessor::s_midAttack, attackSliderMid));
    sliderAttachments.emplace_back(new SliderAttachment(audioProcessor.apvts, MultibandCompressorAudioProcessor::s_midRelease, releaseSliderMid));
    
    sliderAttachments.emplace_back(new SliderAttachment(audioProcessor.apvts, MultibandCompressorAudioProcessor::s_highThresh, threshSliderHigh));
    sliderAttachments.emplace_back(new SliderAttachment(audioProcessor.apvts, MultibandCompressorAudioProcessor::s_highRatio, ratioSliderHigh));
    sliderAttachments.emplace_back(new SliderAttachment(audioProcessor.apvts, MultibandCompressorAudioProcessor::s_highAttack, attackSliderHigh));
    sliderAttachments.emplace_back(new SliderAttachment(audioProcessor.apvts, MultibandCompressorAudioProcessor::s_highRelease, releaseSliderHigh));
    
    sliderAttachments.emplace_back(new SliderAttachment(audioProcessor.apvts, MultibandCompressorAudioProcessor::s_midBandWidth, midBandWidthChange));
    
    
    buttonAttachments.emplace_back(new ButtonAttachment(audioProcessor.apvts, MultibandCompressorAudioProcessor::s_progDepend, progDependentButton));
    
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
    g.fillRoundedRectangle(292, 20, 232, 326, 10);
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

//void MultibandCompressorAudioProcessorEditor::sliderValueChanged(juce::Slider *slider)
//{
//    if(slider == &ratioSliderLow)
//        audioProcessor.multibandCompressor.setRatio(ratioSliderLow.getValue(), 0);
//    
//    if(slider == &ratioSliderMid)
//        audioProcessor.multibandCompressor.setRatio(ratioSliderMid.getValue(), 1);
//    
//    if(slider == &ratioSliderHigh)
//        audioProcessor.multibandCompressor.setRatio(ratioSliderHigh.getValue(), 2);
//    
//    
//    
//    if(slider == &threshSliderLow)
//        audioProcessor.multibandCompressor.setThreshold(threshSliderLow.getValue(), 0);
//    
//    if(slider == &threshSliderMid)
//        audioProcessor.multibandCompressor.setThreshold(threshSliderMid.getValue(), 1);
//    
//    if(slider == &threshSliderHigh)
//        audioProcessor.multibandCompressor.setThreshold(threshSliderHigh.getValue(), 2);
//    
//    
//    
//    if(slider == &attackSliderLow)
//        audioProcessor.multibandCompressor.setAttack(attackSliderLow.getValue(), 0);
//    
//    if(slider == &attackSliderMid)
//        audioProcessor.multibandCompressor.setAttack(attackSliderMid.getValue(), 1);
//    
//    if(slider == &attackSliderHigh)
//        audioProcessor.multibandCompressor.setAttack(attackSliderHigh.getValue(), 2);
//    
//    
//    
//    if(slider == &releaseSliderLow)
//        audioProcessor.multibandCompressor.setRelease(releaseSliderLow.getValue(), 0);
//    
//    if(slider == &releaseSliderMid)
//        audioProcessor.multibandCompressor.setRelease(releaseSliderMid.getValue(), 1);
//    
//    if(slider == &releaseSliderHigh)
//        audioProcessor.multibandCompressor.setRelease(releaseSliderHigh.getValue(), 2);
//    
//    if(slider == &midBandWidthChange)
//        audioProcessor.multibandCompressor.setMidBandWidthChange(midBandWidthChange.getValue());
//    
//}
//
//void MultibandCompressorAudioProcessorEditor::buttonClicked(juce::Button *button)
//{
//    if ( button == &progDependentButton){
//        audioProcessor.multibandCompressor.compressor.progDependent = progDependentButton.getToggleState();
//        
//        attackSliderLow.setEnabled(!audioProcessor.multibandCompressor.compressor.progDependent);
//        releaseSliderLow.setEnabled(!audioProcessor.multibandCompressor.compressor.progDependent);
//        
//        attackSliderMid.setEnabled(!audioProcessor.multibandCompressor.compressor.progDependent);
//        releaseSliderMid.setEnabled(!audioProcessor.multibandCompressor.compressor.progDependent);
//        
//        attackSliderHigh.setEnabled(!audioProcessor.multibandCompressor.compressor.progDependent);
//        releaseSliderHigh.setEnabled(!audioProcessor.multibandCompressor.compressor.progDependent);
//        
//    }
//}
