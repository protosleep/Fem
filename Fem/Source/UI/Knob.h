/*
  ==============================================================================

    Knob.h
    Created: 30 Dec 2024 2:17:44pm
    Author:  Terrence Barrow

  ==============================================================================
*/
#include "../JuceLibraryCode/JuceHeader.h"


#pragma once
namespace UI 
{
    class KnobListener : public juce::Slider::Listener
    {
    public:
        virtual void sliderValueChanged(juce::Slider* slider) override;
        std::function<void(double)> OnValueChanged;
    };


    class KnobLaF : public juce::LookAndFeel_V3
    {
    public:
        void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
            const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider& slider);
    };


    class Knob : public juce::Slider
    {
    public:
        void setup();
        std::function<void(double)> OnValueChanged;


    private:
        KnobLaF mLaf;
        KnobListener mListener;
    };

}

