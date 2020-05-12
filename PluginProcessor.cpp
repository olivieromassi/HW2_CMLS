/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#ifndef M_PI
#define M_PI  (3.14159265) 
#endif

//==============================================================================
Flanger1AudioProcessor::Flanger1AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

Flanger1AudioProcessor::~Flanger1AudioProcessor()
{
}

//==============================================================================
const String Flanger1AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Flanger1AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Flanger1AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Flanger1AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Flanger1AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Flanger1AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Flanger1AudioProcessor::getCurrentProgram()
{
    return 0;
}

void Flanger1AudioProcessor::setCurrentProgram (int index)
{
}

const String Flanger1AudioProcessor::getProgramName (int index)
{
    return {};
}

void Flanger1AudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void Flanger1AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    dbuf.setSize(getTotalNumOutputChannels(), 100000);
    dbuf.clear();
    dw = 0;
    dr = 1;
    M = 3000;
}

void Flanger1AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Flanger1AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void Flanger1AudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    int numSamples = buffer.getNumSamples();
    float* channelOutDataL = buffer.getWritePointer(0);
    float* channelOutDataR = buffer.getWritePointer(1);
    const float* channelInData = buffer.getReadPointer(0);
    for (int i = 0; i < numSamples; ++i)
    {
        //evaluate current distance between pointers (in seconds)
        float currentDelay = 0.001 * width * (0.5 + 0.5 * sinf(phase));
        //get fractional read pointer
        float dpr = fmodf((float)dw - (float)(currentDelay * getSampleRate()) + (float)M - 3.0, (float)M);
        //decompose read pointer in integer part and fractional part, get previous and next integer pointers
        float fraction = dpr - floorf(dpr);
        int previousSample = (int)floorf(dpr);
        int nextSample = (previousSample + 1) % M;
        //interpolate between previous Sample and next sample using the fraction
        float interpolatedSample = fraction * dbuf.getSample(0, nextSample) + (1.0f - fraction) * dbuf.getSample(0, previousSample);
        //feedback
        dbuf.setSample(0, dw, channelInData[i] + feedback * interpolatedSample);
        //output
        channelOutDataL[i] = interpolatedSample * wet + channelInData[i] * (1 - wet);
        channelOutDataR[i] = interpolatedSample * wet + channelInData[i] * (1 - wet);
        //increment pointers
        dw = (dw + 1) % M;
        dr = (dr + 1) % M;
        //LOW FREQUENCY OSCILLATOR
        phase += freqLFO * 2 * M_PI / getSampleRate();
        if (phase >= 2 * M_PI) { phase -= 2 * M_PI; }
    }
}

//==============================================================================
bool Flanger1AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* Flanger1AudioProcessor::createEditor()
{
    return new Flanger1AudioProcessorEditor (*this);
}

//==============================================================================
void Flanger1AudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void Flanger1AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Flanger1AudioProcessor();
}

