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
class Flanger1AudioProcessorEditor  : public AudioProcessorEditor, private Slider::Listener, private Button::Listener
{
public:
    Flanger1AudioProcessorEditor (Flanger1AudioProcessor&);
    ~Flanger1AudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    void sliderValueChanged(Slider* slider) override;
    void buttonClicked(Button* button) override;

    Slider freqLFO_slider;
    Slider wet_slider;
    Slider feedback_slider;
    Slider width_slider;
    TextButton waveform_button;

private:
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Flanger1AudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Flanger1AudioProcessorEditor)
};
