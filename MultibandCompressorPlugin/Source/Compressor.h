/*
  ==============================================================================

    CompressorProcessor.h
    Created: 29 Feb 2024 6:56:27pm
    Author:  Colin Cormier

  ==============================================================================
*/

#pragma once

class Compressor {
    
public:
    
    float processSample(float x, float Fs, int channel);
    
    void process(float * buffer, int numSamples, float Fs, int channel);
    
    void setThreshold(float x);
    
    void setRatio(float x);
    
    void setAttack(float x);
    
    void setRelease(float x);
    
    bool progDependent = false;
    
private:
    
    float threshold = -10.f;
    float ratio;
    float attack;
    float release;
    float gainSmoothPrev[2] = {0.f};
    
};
