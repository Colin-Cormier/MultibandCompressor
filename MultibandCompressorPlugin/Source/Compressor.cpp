/*
  ==============================================================================

    CompressorProcessor.cpp
    Created: 29 Feb 2024 6:56:27pm
    Author:  Colin Cormier

  ==============================================================================
*/

#include "Compressor.h"

#import <JuceHeader.h>

float Compressor::processSample(float x, float Fs, int channel){
    
    float x_abs = abs(x);
    float x_dB = 20 * log10(x_abs);
    float gain = 0;
    float linearAmp;
    float alphaAttack = exp(-log(9)/Fs * attack);
    float alphaRelease = exp(-log(9)/Fs * release);
    float gainSmooth = 0;
    
    if(x_dB < -96)
        x_dB = -96;
    
    if(x_dB > threshold)
        gain = threshold + ( (x_dB - threshold)/ratio );\
    else
        gain = x_dB;
    
    float gainChange = gain - x_dB;
    
    if(progDependent){
        attack = 1.f / (-gainSmoothPrev[channel] + 0.5f);
        alphaAttack = exp(-log(9.f) / (Fs * attack));
        
        release = 1.f / (-gainSmoothPrev[channel] + 0.2f);
        alphaRelease = exp(-log(9.f) / (Fs * release));
    }
    
    
    if(gainChange < gainSmoothPrev[channel])
        
        gainSmooth = ( (1-alphaAttack) * gainChange ) + (alphaAttack * gainSmoothPrev[channel]);
    
    else
        
        gainSmooth = ( (1-alphaRelease) * gainChange ) + (alphaRelease * gainSmoothPrev[channel]);
    
    
    linearAmp = (float) pow(10, (double) gainSmooth/20);
    
    gainSmoothPrev[channel] = gainSmooth;
    
    return linearAmp * x;
}

void Compressor::process(float *buffer, int numSamples, float Fs, int channel){
    
    for(int i=0; i < numSamples; ++i){
        float x = buffer[i];
        buffer[i] = processSample(x, Fs, channel);
    }
}

void Compressor::setThreshold(float x){
    threshold = x;
}

void Compressor::setRatio(float x){
    ratio = x;
}

void Compressor::setAttack(float x){
    attack = x;
}

void Compressor::setRelease(float x){
    release = x;
}
