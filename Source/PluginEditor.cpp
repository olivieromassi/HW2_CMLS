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
    setSize (600, 250);

    // Choosing the font to be used into the labels
    labelFont = new Font("Broadway", 20.0f, 1);
    
    // Setting the properties of the LFO rate slider
    freqLFO_slider.setSliderStyle(Slider::Rotary);
    freqLFO_slider.setLookAndFeel(&otherLookAndFeel);
    freqLFO_slider.setSize(100, 100);
    freqLFO_slider.setRange(0.1, 10.0, 0.1);
    freqLFO_slider.setVisible(true);
    freqLFO_slider.setTextBoxStyle(Slider::TextBoxBelow, true, 80, 20);
    freqLFO_slider.setPopupDisplayEnabled (true, false, this);
    freqLFO_slider.setTextValueSuffix (" Hz ");
    freqLFO_slider.setValue(0);
    addAndMakeVisible (&freqLFO_slider);

    // Setting the properties of the LFO rate label
    freqLFO_label.setFont(*labelFont);
    freqLFO_label.setText("LFO Rate", dontSendNotification);
    freqLFO_label.setSize(80, 20);
    addAndMakeVisible(&freqLFO_label);

    // Assigning the Slider to the processor parameter
    freqLFOVal = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.parameters, "FreqLFO", freqLFO_slider);

    // Setting the properties of the Depth/Wet slider
    wet_slider.setSliderStyle(Slider::Rotary);
    wet_slider.setLookAndFeel(&otherLookAndFeel);
    wet_slider.setSize(100, 100);
    wet_slider.setRange(0.0, 1.0, 0.01);
    wet_slider.setVisible(true);
    wet_slider.setTextBoxStyle(Slider::TextBoxBelow, true, 80, 20);
    wet_slider.setPopupDisplayEnabled(true, false, this);
    wet_slider.setValue(0);
    addAndMakeVisible(&wet_slider);

    // Setting the properties of the Depth/Wet label
    wet_label.setFont(*labelFont);
    wet_label.setText("Depth", dontSendNotification);
    wet_label.setSize(80, 20);
    addAndMakeVisible(&wet_label);

    // Assigning the Slider to the processor parameter
    wetVal = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.parameters, "Wet", wet_slider);

    // Setting the properties of the Feedback slider
    feedback_slider.setSliderStyle(Slider::Rotary);
    feedback_slider.setLookAndFeel(&otherLookAndFeel);
    feedback_slider.setSize(100, 100);
    feedback_slider.setRange(0.0, 0.99, 0.01);
    feedback_slider.setVisible(true);
    feedback_slider.setTextBoxStyle(Slider::TextBoxBelow, true, 80, 20);
    feedback_slider.setPopupDisplayEnabled(true, false, this);
    feedback_slider.setValue(0);
    addAndMakeVisible(&feedback_slider);

    // Setting the properties of the Feedback slider
    feedback_label.setFont(*labelFont);
    feedback_label.setText("Feedback", dontSendNotification);
    feedback_label.setSize(100, 20);
    addAndMakeVisible(&feedback_label);

    // Assigning the Slider to the processor parameter
    feedbackVal = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.parameters, "Feedback", feedback_slider);

    // Setting the properties of the Width slider
    width_slider.setSliderStyle(Slider::Rotary);
    width_slider.setLookAndFeel(&otherLookAndFeel);
    width_slider.setSize(100, 100);    
    width_slider.setRange(1.0, 20.0);
    width_slider.setVisible(true);
    width_slider.setTextBoxStyle(Slider::TextBoxBelow, true, 80, 20);
    width_slider.setPopupDisplayEnabled(true, false, this);
    width_slider.setTextValueSuffix(" ms ");
    width_slider.setValue(0);
    addAndMakeVisible(&width_slider);

    // Setting the properties of the Width label
    width_label.setFont(*labelFont);
    width_label.setText("Width", dontSendNotification);
    width_label.setSize(80, 20);
    addAndMakeVisible(&width_label);

    // Assigning the Slider to the processor parameter
    widthVal = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.parameters, "Width", width_slider);

    // Setting the properties of the Waveform slider
    waveform_slider.setSliderStyle(Slider::LinearVertical);
    waveform_slider.setLookAndFeel(&otherLookAndFeel);
    waveform_slider.setSize(100, 90);
    waveform_slider.setRange(0, 2);
    waveform_slider.setVisible(true);
    waveform_slider.setTextBoxStyle(Slider::NoTextBox, true, 80, 20);
    waveform_slider.setPopupDisplayEnabled(false, false, this);
    waveform_slider.setValue(0);
    addAndMakeVisible(&waveform_slider);

    // Setting the properties of the Waveform label
    waveform_label.setFont(*labelFont);
    waveform_label.setText("Waveform", dontSendNotification);
    waveform_label.setSize(100, 20);
    addAndMakeVisible(&waveform_label);

    waveformFont = new Font("Broadway", 12.0f, 1);
    
    // Setting the properties of the Sinusoidal waveform label
    sine_label.setText("Sine", dontSendNotification);
    sine_label.setFont(*waveformFont);
    sine_label.setColour(Label::ColourIds::textColourId, Colours::black);

    // Setting the properties of the Triangular waveform label
    triang_label.setText("Triangular", dontSendNotification);
    triang_label.setFont(*waveformFont);
    triang_label.setColour(Label::ColourIds::textColourId, Colours::black);

    // Setting the properties of the Sawtooth waveform label
    saw_label.setText("SawTooth", dontSendNotification);
    saw_label.setFont(*waveformFont);
    saw_label.setColour(Label::ColourIds::textColourId, Colours::black);

    addAndMakeVisible(&sine_label);
    addAndMakeVisible(&triang_label);
    addAndMakeVisible(&saw_label);

    // Assigning the Slider to the processor parameter
    waveformVal = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.parameters, "Waveform", waveform_slider);

    // Choosing the font to be used in the Title label
    pluginNameFont = new Font("Broadway", 40.0f, 1);

    // Setting the properties of the Plugin Name label
    pluginName_label.setText("FlangerONE", dontSendNotification);
    pluginName_label.setSize(500, 40);
    pluginName_label.setColour(Label::ColourIds::textColourId, Colours::black);
    pluginName_label.setFont(*pluginNameFont);
    addAndMakeVisible(&pluginName_label);

    // Setting the properties of the Signature label
    signature.setFont(*labelFont);
    signature.setText("Group 15", dontSendNotification);
    signature.setSize(80, 20);
    addAndMakeVisible(&signature);
    

    // Setting the properties of the Stereo button
    stereo_button.setSize(20, 20);
    addAndMakeVisible(&stereo_button);

    // Setting the properties of the Stereo label
    stereo_label.setFont(*labelFont);
    stereo_label.setText("Stereo", dontSendNotification);
    stereo_label.setSize(80, 20);
    addAndMakeVisible(&stereo_label);

    // Assigning the Button to the processor parameter
    stereoVal = std::make_unique<AudioProcessorValueTreeState::ButtonAttachment>(processor.parameters, "Stereo", stereo_button);

}

Flanger1AudioProcessorEditor::~Flanger1AudioProcessorEditor()
{
}

//==============================================================================
void Flanger1AudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (Colours::darkmagenta);
    g.setColour (Colours::black);

    // Draw a black border rectangle
    auto centralArea = getLocalBounds().toFloat().reduced(10.0f); 
    g.drawRoundedRectangle(centralArea, 5.0f, 3.0f); 

    // Draw a black border around the title
    auto colourArea = centralArea.reduced(10.0f).withHeight(40.0f); 
    g.drawRoundedRectangle(colourArea, 5.0f, 3.0f);
    
    // Setting the Title background
    Colour titleBackgroung = Colour(150, 20, 120);
    g.setColour(titleBackgroung);
    g.fillRect(colourArea);
}

void Flanger1AudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor...

    // The following integer represents the step in which the GUI space is divided
    int section = (int)((getWidth() - 20.0) / 5);

    // Placing the Title 
    pluginName_label.setBounds(180, 20, 500, 40);

    // Placing the Width Slider and its corresponding Label
    width_slider.setBounds(10, getHeight() - 140, 500, getHeight() - 60);
    width_label.setBounds(24, getHeight() - 170, 80, 20);

    // Placing the Wet Slider and its corresponding Label
    wet_slider.setBounds(section + 3, getHeight() - 140, 0, getHeight() - 60);
    wet_label.setBounds(section + 18, getHeight() - 170, 80, 20);

    // Placing the Feedback Slider and its corresponding Label
    feedback_slider.setBounds(2 * section + 3, getHeight() - 140, 100, getHeight() - 60);
    feedback_label.setBounds(2 * section + 6, getHeight() - 170, 80, 20);

    // Placing the FreqLFO Slider and its corresponding Label
    freqLFO_slider.setBounds(3 * section + 3, getHeight() - 140, getWidth() + 100, getHeight() - 60);
    freqLFO_label.setBounds(3 * section + 15, getHeight() - 170, 80, 20);

    // Placing the Waveform Slider and its corresponding Label
    waveform_slider.setBounds(4 * section - 20, getHeight() - 135, getWidth() + 100, getHeight() - 60);
    waveform_label.setBounds(4 * section + 6, getHeight() - 170, 80, 20);

    // Placing the Stereo Button and its corresponding Label
    stereo_button.setBounds(520, 30, 20, 20);
    stereo_label.setBounds(450, 30, 20, 20);

    // Placing the Signature label
    signature.setBounds(505, getHeight() - 35, 80, 20);


    sine_label.setBounds(getWidth() - 90, getHeight() - 78, 80, 33);
    triang_label.setBounds(getWidth() - 90, getHeight() - 108, 80, 33);
    saw_label.setBounds(getWidth() - 90, getHeight() - 137, 80, 33);
}