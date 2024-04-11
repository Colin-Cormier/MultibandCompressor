/*
  ==============================================================================

    MultibandCompressorProcessor.cpp
    Created: 22 Feb 2024 8:29:27pm
    Author:  Colin Cormier

  ==============================================================================
*/

#include "MultibandCompressorProcessor.h"


float MultibandCompressorProcessor::processSample(float x, int channel){
    
    return multibandCompressor(x, channel);
}

void MultibandCompressorProcessor::process(float *buffer, int numSamples, int channel){
    
    for(int i = 0; i < numSamples; ++i){
        float x = buffer[i];
        buffer[i] = processSample(x, channel);
    }
    
}

float MultibandCompressorProcessor::multibandCompressor(float x, int channel){
    
    float bands[3] = {x};
    
    float y = 0;
    
    lowCrossOver = 2 * pow(10,lowExponent);
    highCrossOver = 2 * pow(10, highExponent);
    
    //  split bands using 4th order filters
    
        // Splits Low Band
        
        LF1.setFilterType(Biquad::LPF);
        LF1.setFreq(lowCrossOver);
        LF1.setQ(0.7071);
        y = LF1.processSample(x, channel);
        
        LF2.setFilterType(Biquad::LPF);
        LF2.setFreq(lowCrossOver);
        LF2.setQ(0.7071);
        bands[0] = LF2.processSample(y, channel);\
    
        // Splits Mid Band
        
        MF1.setFilterType(Biquad::HPF);
        MF1.setFreq(lowCrossOver);
        MF1.setQ(0.7071);
        y = MF1.processSample(x, channel);
        
        MF2.setFilterType(Biquad::HPF);
        MF2.setFreq(lowCrossOver);
        MF2.setQ(0.7071);
        bands[1] = MF2.processSample(y, channel);
        
        MF1.setFilterType(Biquad::LPF);
        MF1.setFreq(highCrossOver);
        MF1.setQ(0.7071);
        y = MF1.processSample(x, channel);
        
        MF2.setFilterType(Biquad::LPF);
        MF2.setFreq(highCrossOver);
        MF2.setQ(0.7071);
        bands[1] = MF2.processSample(y, channel);
    
        // Splits High Band
        
        HF1.setFilterType(Biquad::HPF);
        HF1.setFreq(highCrossOver);
        HF1.setQ(0.7071);
        y = HF1.processSample(x, channel);
        
        HF2.setFilterType(Biquad::HPF);
        HF2.setFreq(highCrossOver);
        HF2.setQ(0.7071);
        bands[2] = HF2.processSample(y, channel);
    
    //  apply compression to each band
    
    float output = 0;
    
    for ( int i = 0; i < sizeof(bands); ++i ){
        
        float band = bands[i];
        
        compressor.setThreshold(threshold[i]);
        compressor.setRatio(ratio[i]);
        compressor.setAttack(attack[i]);
        compressor.setRelease(release[i]);
        
        output += compressor.processSample(band, Fs, channel);
        
    }
    
    return output;
}

// Get and Set Methods

void MultibandCompressorProcessor::setThreshold(float x, int channel){
    threshold[channel] = x;
}
float MultibandCompressorProcessor::getThreshold(int channel){
    return threshold[channel];
}

void MultibandCompressorProcessor::setRatio(float x, int channel){
    ratio[channel] = x;
}
float MultibandCompressorProcessor::getRatio(int channel){
    return ratio[channel];
}

void MultibandCompressorProcessor::setAttack(float x, int channel){
    attack[channel] = x;
}
float MultibandCompressorProcessor::getAttack(int channel){
    return attack[channel];
}

void MultibandCompressorProcessor::setRelease(float x, int channel){
    release[channel] = x;
}
float MultibandCompressorProcessor::getRelease(int channel){
    return release[channel];
}

void MultibandCompressorProcessor::setHighCrossOver(float x){
    highCrossOver = x;
}
float MultibandCompressorProcessor::getHighCrossOver(){
    return highCrossOver;
}

void MultibandCompressorProcessor::setLowCrossOver(float x){
    lowCrossOver = x;
}
float MultibandCompressorProcessor::getLowCrossOver(){
    return lowCrossOver;
}
void MultibandCompressorProcessor::setHighExponent(float x){
    highExponent = x;
}

void MultibandCompressorProcessor::setLowExponent(float x){
    lowExponent = x;
}

void MultibandCompressorProcessor::setMidBandWidthChange(float x){
    midBandWidthChange = x;
    setLowExponent(lowExponent - x);
    setHighExponent(highExponent + x);
}
