/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

const juce::StringRef MultibandCompressorAudioProcessor::s_lowThresh = "low_KNOB1";
const juce::StringRef MultibandCompressorAudioProcessor::s_lowRatio = "low_KNOB2";
const juce::StringRef MultibandCompressorAudioProcessor::s_lowAttack = "low_KNOB3";
const juce::StringRef MultibandCompressorAudioProcessor::s_lowRelease = "low_KNOB4";

const juce::StringRef MultibandCompressorAudioProcessor::s_midThresh = "mid_KNOB1";
const juce::StringRef MultibandCompressorAudioProcessor::s_midRatio = "mid_KNOB2";
const juce::StringRef MultibandCompressorAudioProcessor::s_midAttack = "mid_KNOB3";
const juce::StringRef MultibandCompressorAudioProcessor::s_midRelease = "mid_KNOB4";
const juce::StringRef MultibandCompressorAudioProcessor::s_midBandWidth = "mid_KNOB5";

const juce::StringRef MultibandCompressorAudioProcessor::s_highThresh = "high_KNOB1";
const juce::StringRef MultibandCompressorAudioProcessor::s_highRatio = "high_KNOB2";
const juce::StringRef MultibandCompressorAudioProcessor::s_highAttack = "high_KNOB3";
const juce::StringRef MultibandCompressorAudioProcessor::s_highRelease = "high_KNOB4";

const juce::StringRef MultibandCompressorAudioProcessor::s_progDepend = "BUTTON1";

//==============================================================================
MultibandCompressorAudioProcessor::MultibandCompressorAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
#endif
apvts(*this, nullptr, "Params", createParams())
{
}

MultibandCompressorAudioProcessor::~MultibandCompressorAudioProcessor()
{
}

juce::AudioProcessorValueTreeState::ParameterLayout MultibandCompressorAudioProcessor::createParams()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
    
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{s_lowThresh, ParameterVersionHint}, "Low Threshold", -96.f, 0.f, 0.f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{s_lowRatio, ParameterVersionHint}, "Low Ratio", 1.f, 20.f, 1.f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{s_lowAttack, ParameterVersionHint}, "Low Attack", 0.f, 0.1f, 0.f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{s_lowRelease, ParameterVersionHint}, "Low Release", 0.f, 5.f, 0.f));
    
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{s_midThresh, ParameterVersionHint}, "Mid Threshold", -96.f, 0.f, 0.f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{s_midRatio, ParameterVersionHint}, "Mid Ratio", 1.f, 20.f, 1.f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{s_midAttack, ParameterVersionHint}, "Mid Attack", 0.f, 0.1f, 0.f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{s_midRelease, ParameterVersionHint}, "Mid Release", 0.f, 5.f, 0.f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{s_midBandWidth, ParameterVersionHint}, "Mid Bandwidth", -0.5f, 1.f, 0.f));
    
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{s_highThresh, ParameterVersionHint}, "High Threshold", -96.f, 0.f, 0.f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{s_highRatio, ParameterVersionHint}, "High Ratio", 1.f, 20.f, 1.f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{s_highAttack, ParameterVersionHint}, "High Attack", 0.f, 0.1f, 0.f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{s_highRelease, ParameterVersionHint}, "High Release", 0.f, 5.f, 0.f));
    
    params.push_back(std::make_unique<juce::AudioParameterBool>(juce::ParameterID{s_progDepend, ParameterVersionHint}, "Auto", false));
    
    return {params.begin(), params.end()};
    
}


//==============================================================================
const juce::String MultibandCompressorAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MultibandCompressorAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MultibandCompressorAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool MultibandCompressorAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double MultibandCompressorAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MultibandCompressorAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MultibandCompressorAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MultibandCompressorAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String MultibandCompressorAudioProcessor::getProgramName (int index)
{
    return {};
}

void MultibandCompressorAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void MultibandCompressorAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void MultibandCompressorAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MultibandCompressorAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void MultibandCompressorAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();


    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    //float knobVal = *apvts.getRawParameterValue(s_lowThresh);
    
    //bool buttonVal = *apvts.getRawParameterValue(s_progDepend) > 0.5f ? true : false;

    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
        
        multibandCompressor.process(channelData, buffer.getNumSamples(), channel);
    }
     
}

//==============================================================================
bool MultibandCompressorAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* MultibandCompressorAudioProcessor::createEditor()
{
    return new MultibandCompressorAudioProcessorEditor (*this);
}

//==============================================================================
void MultibandCompressorAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void MultibandCompressorAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}




void MultibandCompressorAudioProcessor::threshChanged(float value, int channel){
    multibandCompressor.setThreshold(value, channel);
}

void MultibandCompressorAudioProcessor::ratioChanged(float value, int channel){
    multibandCompressor.setRatio(value, channel);
}

void MultibandCompressorAudioProcessor::attackChanged(float value, int channel){
    multibandCompressor.setAttack(value, channel);
}

void MultibandCompressorAudioProcessor::releaseChanged(float value, int channel){
    multibandCompressor.setRelease(value, channel);
}

void MultibandCompressorAudioProcessor::midBandWidthChanged(float value){
    multibandCompressor.setMidBandWidthChange(value);
}

void MultibandCompressorAudioProcessor::progDependClicked(bool value){
    multibandCompressor.compressor.progDependent = value;
    
}




juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MultibandCompressorAudioProcessor();
}
