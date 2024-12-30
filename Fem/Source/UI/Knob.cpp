/*
  ==============================================================================

    Knob.cpp
    Created: 30 Dec 2024 2:17:44pm
    Author:  Terrence Barrow

  ==============================================================================
*/

#include "Knob.h"
using namespace juce;
using namespace UI;

void KnobListener::sliderValueChanged(Slider* slider)
{
    if (OnValueChanged != nullptr)
    {
        auto val = slider->getValue();
        OnValueChanged(val);
    }
}



void KnobLaF::drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
    const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider)
{
    const float radius = jmin(width / 2, height / 2) - 4.0f;
    const float centreX = x + width * 0.5f;
    const float centreY = y + height * 0.5f;
    const float rx = centreX - radius;
    const float ry = centreY - radius;
    const float rw = radius * 2.0f;
    const float angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);

    // fill
    g.setColour(Colours::darkgrey);
    g.fillEllipse(rx, ry, rw, rw);

    // outline
    g.setColour(Colours::red);
    g.drawEllipse(rx, ry, rw, rw, 1.0f);

    Path p;
    const float pointerLength = radius * 0.33f;
    const float pointerThickness = 2.0f;
    p.addRectangle(-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
    p.applyTransform(AffineTransform::rotation(angle).translated(centreX, centreY));

    // pointer
    g.setColour(Colours::yellow);
    g.fillPath(p);
}


void Knob::setup()
{
    this->setLookAndFeel(&mLaf);
    this->setSliderStyle(Slider::Rotary);
    this->setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    this->addListener(&mListener);
    mListener.OnValueChanged = [&](double val)
    {
        if (OnValueChanged != nullptr)
        {
            OnValueChanged(val);
        }
    };
}