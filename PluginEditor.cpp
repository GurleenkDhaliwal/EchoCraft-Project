#include "PluginEditor.h"

EchoCraftEditor::EchoCraftEditor(EchoCraftProcessor& p)
    : AudioProcessorEditor(&p),
    processor(p)
{
    // Set colors
    backgroundColor = juce::Colour(0xff323e44);
    knobColor = juce::Colour(0xff6e8094);
    textColor = juce::Colours::white;

    // Initialize delayTimeSlider
    addAndMakeVisible(delayTimeSlider);
    delayTimeSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    delayTimeSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    delayTimeSlider.setRange(0.0, 1.0);
    delayTimeSlider.setValue(0.0);
    delayTimeSlider.setColour(juce::Slider::thumbColourId, knobColor);
    delayTimeSlider.setColour(juce::Slider::rotarySliderFillColourId, backgroundColor);
    delayTimeSlider.setColour(juce::Slider::textBoxTextColourId, textColor);
    delayTimeSlider.setTextValueSuffix(" Delay Time");
    delayTimeSlider.addListener(this);
    delayTimeSlider1.attachToComponent(&delayTimeSlider, true);

    // Initialize feedbackSlider
    addAndMakeVisible(feedbackSlider);
    feedbackSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    feedbackSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    feedbackSlider.setRange(0.0, 1.0);
    feedbackSlider.setValue(0.0);
    feedbackSlider.setColour(juce::Slider::thumbColourId, knobColor);
    feedbackSlider.setColour(juce::Slider::rotarySliderFillColourId, backgroundColor);
    feedbackSlider.setColour(juce::Slider::textBoxTextColourId, textColor);
    feedbackSlider.setTextValueSuffix(" Feedback");
    feedbackSlider.addListener(this);
    feedbackSlider1.attachToComponent(&feedbackSlider, true);

    // Initialize mixSlider
    addAndMakeVisible(mixSlider);
    mixSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    mixSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    mixSlider.setRange(0.0, 1.0);
    mixSlider.setValue(0.0);
    mixSlider.setColour(juce::Slider::thumbColourId, knobColor);
    mixSlider.setColour(juce::Slider::rotarySliderFillColourId, backgroundColor);
    mixSlider.setColour(juce::Slider::textBoxTextColourId, textColor);
    mixSlider.setTextValueSuffix(" Mix");
    mixSlider.addListener(this);
    mixSlider1.attachToComponent(&mixSlider, true);

    // Initialize toneControlSlider
    addAndMakeVisible(toneControlSlider);
    toneControlSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    toneControlSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    toneControlSlider.setRange(0.0, 1.0);
    toneControlSlider.setValue(0.0);
    toneControlSlider.setColour(juce::Slider::thumbColourId, knobColor);
    toneControlSlider.setColour(juce::Slider::rotarySliderFillColourId, backgroundColor);
    toneControlSlider.setColour(juce::Slider::textBoxTextColourId, textColor);
    toneControlSlider.setTextValueSuffix(" Tone Control");
    toneControlSlider.addListener(this);
    toneControlSlider1.attachToComponent(&toneControlSlider, true);

    // Set background color
    setColour(juce::Label::backgroundColourId, backgroundColor);

    setSize(600, 300);
}



EchoCraftEditor::~EchoCraftEditor() {}

void EchoCraftEditor::paint(juce::Graphics& g)
{
    g.fillAll(backgroundColor); // Fill background with the chosen color
}

void EchoCraftEditor::resized()
{
    // Position sliders
    delayTimeSlider.setBounds(10, 10, 100, 100);
    feedbackSlider.setBounds(120, 10, 100, 100);
    mixSlider.setBounds(230, 10, 100, 100);
    toneControlSlider.setBounds(340, 10, 100, 100);
}

void EchoCraftEditor::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &delayTimeSlider) {
        processor.setDelayTime(delayTimeSlider.getValue()); // Assuming a setDelayTime function exists in EchoCraftProcessor
    }
    else if (slider == &feedbackSlider) {
        processor.setFeedback(feedbackSlider.getValue()); // Assuming a setFeedback function exists in EchoCraftProcessor
    }
    else if (slider == &mixSlider) {
        processor.setMix(mixSlider.getValue()); // Assuming a setMix function exists in EchoCraftProcessor
    }
    else if (slider == &toneControlSlider) {
        processor.setToneControl(toneControlSlider.getValue()); // Assuming a setToneControl function exists in EchoCraftProcessor
    }
}