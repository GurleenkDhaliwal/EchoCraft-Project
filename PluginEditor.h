#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class EchoCraftEditor : public juce::AudioProcessorEditor,
    public juce::Slider::Listener // Inherit from Slider Listener
{
public:
    EchoCraftEditor(EchoCraftProcessor&);
    ~EchoCraftEditor();

    void paint(juce::Graphics&) override;
    void resized() override;

    

private:
    // Knobs
    juce::Slider delayTimeSlider;
    juce::Slider feedbackSlider;
    juce::Slider mixSlider;
    juce::Slider toneControlSlider;
    juce::Label delayTimeSlider1;
    juce::Label feedbackSlider1;
    juce::Label mixSlider1;
    juce::Label toneControlSlider1;
    // Colours
    juce::Colour backgroundColor;
    juce::Colour knobColor;
    juce::Colour textColor;

    EchoCraftProcessor& processor;
   

    // Slider Listener callback
    void sliderValueChanged(juce::Slider* slider) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EchoCraftEditor)
};