/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Flanger1AudioProcessorEditor::Flanger1AudioProcessorEditor (Flanger1AudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (500, 500);
    
    freqLFO_slider.setSliderStyle(Slider::LinearBarVertical);
    freqLFO_slider.setRange(1.0, 10.0);
    freqLFO_slider.setVisible(true);
    freqLFO_slider.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    freqLFO_slider.setPopupDisplayEnabled (true, false, this);
    freqLFO_slider.setTextValueSuffix (" LFO frequency");
    freqLFO_slider.setValue(0);
    addAndMakeVisible (&freqLFO_slider);

    wet_slider.setSliderStyle(Slider::LinearBarVertical);
    wet_slider.setRange(0.0, 1.0);
    wet_slider.setVisible(true);
    wet_slider.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    wet_slider.setPopupDisplayEnabled(true, false, this);
    wet_slider.setTextValueSuffix(" Ratio");
    wet_slider.setValue(0);
    addAndMakeVisible(&wet_slider);

    feedback_slider.setSliderStyle(Slider::LinearBarVertical);
    feedback_slider.setRange(0.0, 1.0);
    feedback_slider.setVisible(true);
    feedback_slider.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    feedback_slider.setPopupDisplayEnabled(true, false, this);
    feedback_slider.setTextValueSuffix(" Feedback");
    feedback_slider.setValue(0);
    addAndMakeVisible(&feedback_slider);

    width_slider.setSliderStyle(Slider::LinearBarVertical);
    width_slider.setRange(0.0, 5.0);
    width_slider.setVisible(true);
    width_slider.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    width_slider.setPopupDisplayEnabled(true, false, this);
    width_slider.setTextValueSuffix(" Width");
    width_slider.setValue(0);
    addAndMakeVisible(&width_slider);

    freqLFO_slider.addListener(this);
    wet_slider.addListener(this);
    feedback_slider.addListener(this);
    width_slider.addListener(this);

}

Flanger1AudioProcessorEditor::~Flanger1AudioProcessorEditor()
{
}

//==============================================================================
void Flanger1AudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (Colours::white);
    g.setColour (Colours::black);
}

void Flanger1AudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    freqLFO_slider.setBounds(40, 30, 20, getHeight() - 60);
    wet_slider.setBounds(80, 30, 20, getHeight() - 60);
    feedback_slider.setBounds(120, 30, 20, getHeight() - 60);
    width_slider.setBounds(160, 30, 20, getHeight() - 60);
}

void Flanger1AudioProcessorEditor::sliderValueChanged(Slider* slider) {
    processor.freqLFO = freqLFO_slider.getValue();
    processor.wet = wet_slider.getValue();
    processor.feedback = feedback_slider.getValue();
    processor.width = width_slider.getValue();
}
