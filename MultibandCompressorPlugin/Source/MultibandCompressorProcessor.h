/*
  ==============================================================================

    MultibandCompressorProcessor.h
    Created: 22 Feb 2024 8:29:27pm
    Author:  Colin Cormier

  ==============================================================================
*/

#pragma once
#include "Biquad.h"
#include "Compressor.h"

class MultibandCompressorProcessor {
    
public:
    
    float processSample(float x, int channel);
    
    void process(float * buffer, int numSamples, int channel);
    
    void setThreshold(float x, int channel);
    float getThreshold(int channel);
    
    void setRatio(float x, int channel);
    float getRatio(int channel);
    
    void setAttack(float x, int channel);
    float getAttack(int channel);
    
    void setRelease(float x, int channel);
    float getRelease(int channel);
    
    void setHighCrossOver(float x);
    float getHighCrossOver();
    
    void setLowCrossOver(float x);
    float getLowCrossOver();
    
    void setHighExponent(float x);
    float getHighExponent();
    
    void setLowExponent(float x);
    float getLowExponent();
    
    void setMidBandWidthChange(float x);
    float getMidBandWidthChange() { return midBandWidthChange; }
    
    Compressor compressor;
    
private:
    
    float Fs = 48000.f;
    
    float threshold[3];
    float ratio[3];
    float attack[3];
    float release[3];
    
    float multibandCompressor(float x, float Fs, float thresh[], float ratio[], float attack[], float release[], int channel);
    
    Biquad LF; Biquad MF; Biquad HF;
    
    float lowExponent = 2;  // >=1, <=4
    float highExponent = 3; // >=1, <=4
    
    float midBandWidthChange = 0;
    
    float lowCrossOver;
    float highCrossOver;
    
};