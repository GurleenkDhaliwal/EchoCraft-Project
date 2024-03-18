#pragma once

#include <JuceHeader.h>
#include <juce_dsp/juce_dsp.h>
#include <cmath>
#include <math.h>
#define _USE_MATH_DEFINES

class EchoCraftProcessor : public juce::AudioProcessor
{
public:
    EchoCraftProcessor();
    ~EchoCraftProcessor() override;

    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    void processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;
    // New member functions to set parameter values
    void setDelayTime(double value);
    void setFeedback(double value);
    void setMix(double value);
    void setToneControl(double value);

    const juce::String getName() const override;
#ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported(const BusesLayout& layouts) const override;
#endif



    //==============================================================================


    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram(int index) override;
    const juce::String getProgramName(int index) override;
    void changeProgramName(int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation(juce::MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;


private:
    // Parameters
    juce::AudioParameterFloat* delayTimeParam;
    juce::AudioParameterFloat* feedbackParam;
    juce::AudioParameterFloat* mixParam;
    juce::AudioParameterFloat* toneControlParam;

    // Smoothed parameters
    juce::SmoothedValue<float> smoothDelayTime;
    juce::SmoothedValue<float> smoothFeedback;
    juce::SmoothedValue<float> smoothMix;
    juce::SmoothedValue<float> smoothToneControl;

    // Digital Delay Line
    juce::AudioBuffer<float> delayBuffer;
    int delayBufferWritePosition;
    int delayBufferLength;

    // Filter
    std::unique_ptr<juce::dsp::IIR::Filter<float>> toneFilter;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EchoCraftProcessor)
};