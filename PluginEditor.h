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
class Flanger1AudioProcessorEditor  : public AudioProcessorEditor
{
public:
    Flanger1AudioProcessorEditor (Flanger1AudioProcessor&);
    ~Flanger1AudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

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

    Label pluginName_label;

    Font* pluginNameFont;
    Font* labelFont;

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
