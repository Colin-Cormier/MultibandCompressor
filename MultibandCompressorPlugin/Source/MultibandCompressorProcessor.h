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
    
    void setHighExponent(double x);
    double getHighExponent();
    
    void setLowExponent(double x);
    double getLowExponent();
    
    void setFs(float sampleRate) { Fs = sampleRate; }
    
    void setMidBandWidthChange(double x);
    double getMidBandWidthChange() { return midBandWidthChange; }
    
    Compressor compressor;
    
    double midBandWidthChange = 0.0; // -0.5 - 1.0
    
private:
    
    float Fs = 48000.f;
    
    float threshold[3] = {0.f};
    float ratio[3];
    float attack[3] = {0.f};
    float release[3] = {0.f};
    
    Biquad LF1, LF2, MF1, MF2, MF3, MF4, HF1, HF2;
    
    double lowExponent = 2.0;  // >=1, <=4
    double highExponent = 3.0; // >=1, <=4
    
    float lowCrossOver = 20.f;
    float highCrossOver = 2000.f;
    
};
