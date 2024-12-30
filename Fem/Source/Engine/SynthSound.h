/*
  ==============================================================================

    SynthSound.h
    Created: 30 Dec 2024 2:56:30pm
    Author:  Terrence Barrow

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

namespace Engine
{
    class SynthSound : public juce::SynthesiserSound
    {
        public:
            virtual bool appliesToNote(int midiNoteNumber) override { return true; }
            virtual bool appliesToChannel(int midiChannel) override { return true; }
    };
}