#include "PluginProcessor.h"
#include "PluginEditor.h"

EchoCraftProcessor::EchoCraftProcessor()
    : AudioProcessor(BusesProperties().withInput("Input", juce::AudioChannelSet::stereo(), true)
        .withOutput("Output", juce::AudioChannelSet::stereo(), true)),
    delayBuffer(2, 44100), // Stereo delay buffer
    delayBufferWritePosition(0),
    delayBufferLength(44100), // 1 second delay buffer at 44100 sample rate
    smoothDelayTime(0.01),
    smoothFeedback(0.01),
    smoothMix(0.01),
    smoothToneControl(0.01)
{
    // Initialize parameters
    addParameter(delayTimeParam = new juce::AudioParameterFloat("delayTime", "Delay Time", 0.0f, 1.0f, 0.5f));
    addParameter(feedbackParam = new juce::AudioParameterFloat("feedback", "Feedback", 0.0f, 1.0f, 0.5f));
    addParameter(mixParam = new juce::AudioParameterFloat("mix", "Mix", 0.0f, 1.0f, 0.5f));
    addParameter(toneControlParam = new juce::AudioParameterFloat("toneControl", "Tone Control", 0.0f, 1.0f, 0.5f));
}

EchoCraftProcessor::~EchoCraftProcessor() {}

void EchoCraftProcessor::prepareToPlay(double sampleRate, int samplesPerBlock) {
    // Create the toneFilter here with the sample rate
    toneFilter = std::make_unique<juce::dsp::IIR::Filter<float>>(juce::dsp::IIR::Coefficients<float>::makeLowPass(sampleRate, 1000.0f));
}

void EchoCraftProcessor::releaseResources() {}

void EchoCraftProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer&) {
    auto numSamples = buffer.getNumSamples();
    

    // Update smoothed parameter values
    smoothDelayTime.setTargetValue(delayTimeParam->get());
    smoothFeedback.setTargetValue(feedbackParam->get());
    smoothMix.setTargetValue(mixParam->get());
    smoothToneControl.setTargetValue(toneControlParam->get());

    // Process each sample
    for (int sample = 0; sample < numSamples; ++sample)
    {
        // Get current smoothed parameter values
        auto smoothDelayTimeValue = smoothDelayTime.getNextValue();
        auto smoothFeedbackValue = smoothFeedback.getNextValue();
        auto smoothMixValue = smoothMix.getNextValue();
        auto smoothToneControlValue = smoothToneControl.getNextValue();

        for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
        {
            auto* channelData = buffer.getWritePointer(channel);

            // Apply delay
            auto delayedSample = delayBuffer.getSample(channel, delayBufferWritePosition);
            delayBuffer.setSample(channel, delayBufferWritePosition, channelData[sample]);
            auto outputSample = channelData[sample] + delayedSample * smoothFeedbackValue;

            // Apply tone control
            outputSample = toneFilter->processSample(outputSample * smoothToneControlValue);

            // Mix dry and wet signals
            channelData[sample] = outputSample * smoothMixValue + channelData[sample] * (1.0f - smoothMixValue);
        }

        // Update delay buffer write position
        delayBufferWritePosition = (delayBufferWritePosition + 1) % delayBufferLength;
    }
}
//==================================================================================//
juce::AudioProcessorEditor* EchoCraftProcessor::createEditor() {
    return new EchoCraftEditor(*this);
}

bool EchoCraftProcessor::hasEditor() const {
    return true;
}

const juce::String EchoCraftProcessor::getName() const {
    return "";
}
//------------------------------------------------------------------------------//
// -----------------------------------------------------------------------------//
//=====================================================
#ifndef JucePlugin_PreferredChannelConfigurations
bool EchoCraftProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
    ignoreUnused(layouts);
    return true;
#else
    
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    
#if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
#endif

    return true;
#endif
}
#endif

//=====================================================
bool EchoCraftProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool EchoCraftProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool EchoCraftProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double EchoCraftProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int EchoCraftProcessor::getNumPrograms()
{
    return 1;  
}

int EchoCraftProcessor::getCurrentProgram()
{
    return 0;
}

void EchoCraftProcessor::setCurrentProgram(int index)
{
}

const juce::String EchoCraftProcessor::getProgramName(int index)
{
    return "EchoCraft";
}

void EchoCraftProcessor::changeProgramName(int index, const juce::String& newName)
{
}



//=====================================================
void EchoCraftProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    
}

void EchoCraftProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    
}
// Implementation for the new member functions
void EchoCraftProcessor::setDelayTime(double value)
{
    // Ensure value is within valid range
    value = juce::jlimit(0.0, 1.0, value);

    // Set the delay time parameter
    smoothDelayTime.setTargetValue(value); 
}

void EchoCraftProcessor::setFeedback(double value)
{
    // Ensure value is within valid range
    value = juce::jlimit(0.0, 1.0, value);

    // Set the feedback parameter
    smoothFeedback.setTargetValue(value); 
}

void EchoCraftProcessor::setMix(double value)
{
    // Ensure value is within valid range
    value = juce::jlimit(0.0, 1.0, value);

    // Set the mix parameter
    smoothMix.setTargetValue(value); 
}

void EchoCraftProcessor::setToneControl(double value)
{
    // Ensure value is within valid range
    value = juce::jlimit(0.0, 1.0, value);

    // Set the tone control parameter
    smoothToneControl.setTargetValue(value); 
}


juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new EchoCraftProcessor();
}