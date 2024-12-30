/*
  ==============================================================================

    SynthVoice.cpp
    Created: 30 Dec 2024 2:56:12pm
    Author:  Terrence Barrow

  ==============================================================================
*/

#include "SynthVoice.h"
#include "SynthSound.h"

using namespace Engine;

bool SynthVoice::canPlaySound(juce::SynthesiserSound* sound)
{
    return dynamic_cast<SynthSound*>(sound) != nullptr;
}


void SynthVoice::startNote(int midiNoteNumber,
    float velocity,
    juce::SynthesiserSound* sound,
    int currentPitchWheelPosition)
{
    mADSR.noteOn();
    float noteFreq = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    mOsc->setFrequency(noteFreq);
   
}


void SynthVoice::stopNote(float velocity, bool allowTailOff)
{
    mADSR.noteOff();
}


void SynthVoice::controllerMoved(int controllerNumber, int newControllerValue)
{

}




void SynthVoice::pitchWheelMoved(int newPitchWheelValue)
{

}

void SynthVoice::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels)
{
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels;
    mSinOsc.prepare(spec);
    mSquOsc.prepare(spec);
    mSawOsc.prepare(spec);
    mOsc = &mSquOsc;

    mADSR.setSampleRate(sampleRate);
}


void SynthVoice::renderNextBlock(juce::AudioBuffer<float>& outputBuffer,
    int startSample,
    int numSamples)
{

    juce::dsp::AudioBlock<float> audioBlock(outputBuffer);
    mOsc->process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    mADSR.applyEnvelopeToBuffer(outputBuffer, startSample, numSamples);

    //mSawOsc.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    //mSinOsc.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
}