/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

#define _USE_MATH_DEFINES
#include<math.h>

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
                       ), parameters(*this, nullptr, "Parameters", createParameters())
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
    const int numInputChannels = getTotalNumInputChannels();
    delayBufferSize = (int)sampleRate;

    delayBuffer.setSize(numInputChannels, delayBufferSize);
    delayBuffer.clear();

    // Initializing member variables
    delayWritePosition = 0;
    lfoPhase = 0.0f;
    inverseSampleRate = 1.0f / (float)sampleRate;
    twoPi = (float)(2.0f * M_PI);
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

void Flanger1AudioProcessor::processBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    const int numInputChannels = getTotalNumInputChannels();
    const int numOutputChannels = getTotalNumOutputChannels();
    const int numSamples = buffer.getNumSamples();

    for (auto i = numInputChannels; i < numOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());

    // Getting the values of the parameters that can be set through the UI
    auto width = parameters.getRawParameterValue("Width");
    auto freqLFO = parameters.getRawParameterValue("FreqLFO");
    auto wet = parameters.getRawParameterValue("Wet");
    auto feedback = parameters.getRawParameterValue("Feedback");
    auto waveform = parameters.getRawParameterValue("Waveform");

    // Initializing local variables
    int localWritePosition = 0;
    float phase = 0.0f;
    float phaseMain = 0.0f;

    for (int channel = 0; channel < numInputChannels; ++channel)
    {
        float* channelData = buffer.getWritePointer(channel);
        float* delayData = delayBuffer.getWritePointer(channel);
        localWritePosition = delayWritePosition;
        phase = lfoPhase;

        // Putting the phase of the right channel in quadrature with the left channel
        if (channel != 0)
            phase = fmodf(phase + 0.25f, 1.0f);

        for (int i = 0; i < numSamples; ++i)
        {
            const float in = channelData[i];
            float interpolatedSample = 0.0f;
            // Evaluate current distance between pointers (in seconds)
            float localDelayTime = (*width * 0.001f) * lfo(phase, (int)(*waveform));

            // Get the read pointer from the write pointer considering the actual delay
            float dpr = fmodf((float)localWritePosition
                - (float)(localDelayTime * getSampleRate())
                + (float)delayBufferSize - 3.0f,
                (float)delayBufferSize);

            // Extract the previous and the next sample from the integer and fractional part of the index
            int previousSample = (int)floorf(dpr);
            float fraction = dpr - (float)previousSample;
            int nextSample = (previousSample + 1) % delayBufferSize;

            // Get the interpolated value of the sample using Linear Interpolation
            interpolatedSample = fraction * delayData[nextSample] + (1.0f - fraction) * delayData[previousSample];

            // Computing the value of the output
            channelData[i] = in + (interpolatedSample * (*wet));

            // Computing the value of the sample to be used in feedback
            delayData[localWritePosition] = in + (interpolatedSample * (*feedback));

            // Increasing the pointer at constant rate
            if (++localWritePosition >= delayBufferSize)
                localWritePosition = 0;

            // Updating the phase of the Oscillator, keeping it between 0-1
            phase += (*freqLFO) * inverseSampleRate;
            if (phase >= 1.0f)
                phase -= 1.0f;
        }
        if (channel == 0)
            phaseMain = phase;
    }
    // Restoring the values of the index and the phase for a new block
    delayWritePosition = localWritePosition;
    lfoPhase = phaseMain;

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
    auto state = parameters.copyState();
    std::unique_ptr<XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void Flanger1AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName(parameters.state.getType()))
            parameters.replaceState(ValueTree::fromXml(*xmlState));
}

float Flanger1AudioProcessor::lfo(float phase, int waveform)
{
    float out = 0.0f;

    switch (waveform) {
        // Sinusoidal Oscillator
        case 0: {
            out = 0.5f + 0.5f * sinf(twoPi * phase);
            break;
        }
        // Triangular Oscillator
        case 1: {
            if (phase < 0.25f)
                out = 0.5f + 2.0f * phase;
            else if (phase < 0.75f)
                out = 1.0f - 2.0f * (phase - 0.25f);
            else
                out = 2.0f * (phase - 0.75f);
            break;
        }
        // Sawtooth Oscillator
        case 2: {
            if (phase < 0.5f)
                out = 0.5f + phase;
            else
                out = phase - 0.5f;
            break;
        }
    }
    return out;
}

AudioProcessorValueTreeState::ParameterLayout Flanger1AudioProcessor::createParameters()
{
    std::vector<std::unique_ptr<RangedAudioParameter>> params;

    params.push_back(std::make_unique<AudioParameterFloat>("Wet", "wet", 0.0f, 1.0f, 0.0f));
    params.push_back(std::make_unique<AudioParameterFloat>("Feedback", "feedback", 0.0f, 1.0f, 0.0f));
    params.push_back(std::make_unique<AudioParameterFloat>("FreqLFO", "freqLFO", 0.1f, 10.0f, 0.0f));
    params.push_back(std::make_unique<AudioParameterFloat>("Width", "width", 1.0f, 20.0f, 0.0f));
    params.push_back(std::make_unique<AudioParameterInt>("Waveform", "waveform", 0, 2, 0));

    return { params.begin(), params.end() };
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Flanger1AudioProcessor();
}

