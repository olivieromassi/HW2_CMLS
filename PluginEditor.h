/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class OtherLookAndFeel : public LookAndFeel_V4
{
public:
    OtherLookAndFeel()
    {
        setColour(Slider::thumbColourId, Colours::black);
    }

    void drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
        const float rotaryStartAngle, const float rotaryEndAngle, Slider&) override
    {
        auto radius = jmin(width / 2, height / 2) - 4.0f;
        auto centreX = x + width * 0.5f;
        auto centreY = y + height * 0.5f;
        auto rx = centreX - radius;
        auto ry = centreY - radius;
        auto rw = radius * 2.0f;
        auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);

        // fill
        g.setColour(Colour(150, 20, 120));
        g.fillEllipse(rx, ry, rw, rw);

        // outline
        g.setColour(Colours::black);
        g.drawEllipse(rx, ry, rw, rw, 3.0f);

        Path p;
        auto pointerLength = radius * 0.5f;
        auto pointerThickness = 4.0f;
        p.addRectangle(-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
        p.applyTransform(AffineTransform::rotation(angle).translated(centreX, centreY));

        // pointer
        g.setColour(Colours::black);
        g.fillPath(p);
    }
};

class Flanger1AudioProcessorEditor  : public AudioProcessorEditor
{
public:
    Flanger1AudioProcessorEditor (Flanger1AudioProcessor&);
    ~Flanger1AudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

    OtherLookAndFeel otherLookAndFeel;

    Slider freqLFO_slider;
    Slider wet_slider;
    Slider feedback_slider;
    Slider width_slider;
    Slider waveform_slider;

    ToggleButton stereo_button;

    Label freqLFO_label;
    Label wet_label;
    Label feedback_label;
    Label width_label;
    Label waveform_label;
    Label stereo_label;

    Label sine_label;
    Label triang_label;
    Label saw_label;

    Label pluginName_label;
    Label signature;

    Font* pluginNameFont;
    Font* labelFont;
    Font* waveformFont;

private:
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Flanger1AudioProcessor& processor;

public:
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> widthVal;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> wetVal;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> freqLFOVal;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> feedbackVal;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> waveformVal;
    std::unique_ptr<AudioProcessorValueTreeState::ButtonAttachment> stereoVal;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Flanger1AudioProcessorEditor)
};
