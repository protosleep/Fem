/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "UI/Knob.h"

//==============================================================================
/**
*/
class FemAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    FemAudioProcessorEditor (FemAudioProcessor&);
    ~FemAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    FemAudioProcessor& audioProcessor;
    UI::Knob mOutputGainKnob;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FemAudioProcessorEditor)
};
