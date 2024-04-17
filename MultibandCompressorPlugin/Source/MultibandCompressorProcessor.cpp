/*
  ==============================================================================

    MultibandCompressorProcessor.cpp
    Created: 22 Feb 2024 8:29:27pm
    Author:  Colin Cormier

  ==============================================================================
*/

#include "MultibandCompressorProcessor.h"


void MultibandCompressorProcessor::process(float *buffer, int numSamples, int channel){
    
    for(int i = 0; i < numSamples; ++i){
        
        float x = buffer[i];
        
        lowCrossOver = (float) (2.0 * pow(10.0,lowExponent));
        highCrossOver = (float) (2.0 * pow(10.0,highExponent));
        
        buffer[i] = processSample(x, channel);
    }
    
}

float MultibandCompressorProcessor::processSample(float x, int channel){
    
    int numBands = 3;
    
    float bands[numBands];
    
    for(int i=0; i < numBands; ++i){
        bands[i] = x;
    }
    
    float a = 0;
    float b = 0;
    float c = 0;
    
    //  split bands using 4th order filters
    
        // Splits Low Band
        
        LF1.setFilterType(Biquad::LPF);
        LF1.setFreq(lowCrossOver);
        LF1.setQ(0.7071);
        a = LF1.processSample(x, channel);
        
        LF2.setFilterType(Biquad::LPF);
        LF2.setFreq(lowCrossOver);
        LF2.setQ(0.7071);
        bands[0] = LF2.processSample(a, channel);
    
        // Splits Mid Band
        
        MF1.setFilterType(Biquad::HPF);
        MF1.setFreq(lowCrossOver);
        MF1.setQ(0.7071);
        a = MF1.processSample(x, channel);
        
        MF2.setFilterType(Biquad::HPF);
        MF2.setFreq(lowCrossOver);
        MF2.setQ(0.7071);
        b = MF2.processSample(a, channel);
        
        MF3.setFilterType(Biquad::LPF);
        MF3.setFreq(highCrossOver);
        MF3.setQ(0.7071);
        c = MF3.processSample(b, channel);
        
        MF4.setFilterType(Biquad::LPF);
        MF4.setFreq(highCrossOver);
        MF4.setQ(0.7071);
        bands[1] = MF4.processSample(c, channel);
    
        // Splits High Band
        
        HF1.setFilterType(Biquad::HPF);
        HF1.setFreq(highCrossOver);
        HF1.setQ(0.7071);
        a = HF1.processSample(x, channel);
        
        HF2.setFilterType(Biquad::HPF);
        HF2.setFreq(highCrossOver);
        HF2.setQ(0.7071);
        bands[2] = HF2.processSample(a, channel);
    
    //  apply compression to each band
    
    float output = 0;
    
    for ( int i = 0; i < numBands; ++i ){
        
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
void MultibandCompressorProcessor::setHighExponent(double x){
    highExponent = x;
}

void MultibandCompressorProcessor::setLowExponent(double x){
    lowExponent = x;
}

void MultibandCompressorProcessor::setMidBandWidthChange(double x){
    
    midBandWidthChange = x;
    setLowExponent(lowExponent - x);
    setHighExponent(highExponent + x);
    
}
