/*
  ==============================================================================

    SynthVoice.h
    Created: 30 Dec 2024 2:56:12pm
    Author:  Terrence Barrow

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "SynthSound.h"

namespace Engine
{
    class SynthVoice : public juce::SynthesiserVoice
    {
    public:
        virtual bool canPlaySound(juce::SynthesiserSound*) override;

        virtual void startNote(int midiNoteNumber,
            float velocity,
            juce::SynthesiserSound* sound,
            int currentPitchWheelPosition) override;

        virtual void stopNote(float velocity, bool allowTailOff) override;

        virtual void controllerMoved(int controllerNumber, int newControllerValue) override;

        virtual void renderNextBlock(juce::AudioBuffer<float>& outputBuffer,
            int startSample,
            int numSamples) override;

        virtual void pitchWheelMoved(int newPitchWheelValue) override;

        void prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels);


    private:
        juce::dsp::Oscillator<float> mSinOsc{ [](float x) { return std::sin(x); } };
        juce::dsp::Oscillator<float> mSawOsc{ [](float x) { return x / juce::MathConstants<float>::pi; } };
        juce::dsp::Oscillator<float> mSquOsc{ [](float x) { return x < 0.0F ? -1.0f : 1.0f; } };
        juce::dsp::Oscillator<float>* mOsc = nullptr;

        juce::ADSR mADSR;
        juce::ADSR::Parameters mADSRParams;
    };
}

