/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
FemAudioProcessorEditor::FemAudioProcessorEditor (FemAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    addAndMakeVisible(mOutputGainKnob);
    mOutputGainKnob.setup();
    mOutputGainKnob.setRange(0.0, 1.0);
        ;    mOutputGainKnob.OnValueChanged = [&](double val)
    {
        audioProcessor.setOutputGain(val);
    };

    setSize (400, 300);
}

FemAudioProcessorEditor::~FemAudioProcessorEditor()
{
}

//==============================================================================
void FemAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void FemAudioProcessorEditor::resized()
{
    mOutputGainKnob.setBounds(10, 10, 120, 120);
}
