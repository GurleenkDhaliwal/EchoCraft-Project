# EchoCraft - A JUCE Audio Plugin

## Submission by: Gurleen Dhaliwal

## CS 510 - SOUND/MUSIC


### Description
EchoCraft is an audio processing plugin designed to add audio experiences with its unique echo effects. I built it using the JUCE framework, EchoCraft is unique because of its ability to add some depth and dimension.

The core functionality of EchoCraft revolves around its echo processing algorithm. It can be easily integrated into any digital audio workstation (DAW) that supports VST3, AU, or AAX plugin formats. The plugin features a user-friendly interface that allows users to control some parameters, including echo delay, feedback, and wet/dry mix, providing a range of sounds.


### Build and Run
To build and run EchoCraft, ensure you have the JUCE framework and an appropriate C++ compiler installed on your system. Follow these steps:

- Clone the repository to your local machine.
- Open the project in Projucer, which is part of the JUCE framework.
- Set your target formats (VST3, AU, AAX) and your development paths.
- Save and open the project in your preferred IDE (Visual Studio, Xcode, etc.).
- Build the project to generate the plugin binaries.
- Copy the generated binaries to your DAW's plugin folder.
- Open your DAW and scan for new plugins, EchoCraft should now be available in your plugin list.

### Testing
I conducted testing using a variety of audio sources, including vocals, and guitars to ensure the plugin's performance across different sound types. The automated unit tests were implemented to validate the core audio processing algorithms. Some user feedback was also incorporated.

### Example
A simple usage example of EchoCraft could involve applying it to a dry vocal track to add depth and warmth. By adjusting the delay time to 300ms, setting the feedback to 40%, and blending in the effect with a 50% wet mix, the vocal track gains a more spacious quality that improves the overall mix.

### Reflections
Creating this plugin was both challenging and rewarding. After achieving the desired audio quality, it required extensive testing and refinement. While I am satisfied with the current state of the plugin, a future plan is to introduce more advanced features, such as tempo sync and modulation effects.
