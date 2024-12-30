/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
FemAudioProcessor::FemAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

FemAudioProcessor::~FemAudioProcessor()
{
}

//==============================================================================
const juce::String FemAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool FemAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool FemAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool FemAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double FemAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int FemAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int FemAudioProcessor::getCurrentProgram()
{
    return 0;
}

void FemAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String FemAudioProcessor::getProgramName (int index)
{
    return {};
}

void FemAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void FemAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = getTotalNumOutputChannels();
    mSinOsc.prepare(spec);
    mSquOsc.prepare(spec);
    mSawOsc.prepare(spec);
    mSinOsc.setFrequency(440.0f);
    mSquOsc.setFrequency(440.0f);
    mSawOsc.setFrequency(440.0f);

    mOutputGain.prepare(spec);
    mOutputGain.setGainLinear(0.4f);

    
    
}

void FemAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool FemAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
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

void FemAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();


    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    juce::dsp::AudioBlock<float> audioBlock(buffer);
    mSquOsc.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    //mSawOsc.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    //mSinOsc.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));

    mOutputGain.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));

}


void FemAudioProcessor::setOutputGain(double val)
{
    mOutputGain.setGainLinear(static_cast<float>(val));
}

//==============================================================================
bool FemAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* FemAudioProcessor::createEditor()
{
    return new FemAudioProcessorEditor (*this);
}

//==============================================================================
void FemAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void FemAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new FemAudioProcessor();
}
