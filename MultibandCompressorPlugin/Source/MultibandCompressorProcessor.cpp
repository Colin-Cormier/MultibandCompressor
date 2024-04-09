/*
  ==============================================================================

    MultibandCompressorProcessor.cpp
    Created: 22 Feb 2024 8:29:27pm
    Author:  Colin Cormier

  ==============================================================================
*/

#include "MultibandCompressorProcessor.h"


float MultibandCompressorProcessor::processSample(float x, int channel){
    
    return multibandCompressor(x, Fs, threshold, ratio, attack, release, channel);
}

void MultibandCompressorProcessor::process(float *buffer, int numSamples, int channel){
    
    for(int i=0; i < numSamples; ++i){
        float x = buffer[i];
        processSample(x, channel);
        buffer[i] = x;
    }
    
}

float MultibandCompressorProcessor::multibandCompressor(float x, float Fs, float thresh[], float ratio[], float attack[], float release[], int channel){
    
    float bands[3] = {x};
    
    float y = 0;
    
    lowCrossOver = 2 * pow(10,lowExponent);
    highCrossOver = 2 * pow(10, highExponent);
    
    //  split bands using 4th order filters
    
    LF.setFilterType(Biquad::LPF);
    LF.setFreq(lowCrossOver);
    LF.setQ(0.7071);
    y = LF.processSample(x, channel);
    bands[0] = LF.processSample(y, channel);
    
    MF.setFilterType(Biquad::HPF);
    MF.setFreq(lowCrossOver);
    MF.setQ(0.7071);
    y = MF.processSample(x, channel);
    bands[1] = MF.processSample(y, channel);
    
    MF.setFilterType(Biquad::LPF);
    MF.setFreq(highCrossOver);
    y = MF.processSample(x, channel);
    bands[1] = MF.processSample(y, channel);
    
    HF.setFilterType(Biquad::HPF);
    HF.setFreq(highCrossOver);
    HF.setQ(0.7071);
    y = HF.processSample(x, channel);
    bands[2] = HF.processSample(y, channel);
    
    //  apply compression to each band
    
    float output = 0;
    
    for ( int i = 0; i < sizeof(bands); ++i ){
        
        float band = bands[i];
        
        compressor.setThreshold(thresh[i]);
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
