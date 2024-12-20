#include "../JuceLibraryCode/JuceHeader.h"

#include "biquad.h"
#include "biquad_types.h"

#if JUCE_VERSION >= 0x050400
using Parameter = AudioProcessorValueTreeState::Parameter;
#endif

struct onParamChangeListener : AudioProcessorValueTreeState::Listener
{
    onParamChangeListener(biquadStackData* sd) : SD(sd)
    {
    }

    void parameterChanged (const String& parameterID, float newValue) override
    {
        const int idx = getParameterIndex(parameterID);
        onParamChangeCImpl(SD, idx, static_cast<double>(newValue));
    }
    
private:
    int getParameterIndex (const String& parameterID)
    {
        (void)parameterID;
    
        if (parameterID == "HS_FREQ") {
            return 0;
        }
        if (parameterID == "HS_Q") {
            return 1;
        }
        if (parameterID == "HS_GAIN") {
            return 2;
        }
        if (parameterID == "HMF_FREQ") {
            return 3;
        }
        if (parameterID == "HMF_Q") {
            return 4;
        }
        if (parameterID == "HMF_GAIN") {
            return 5;
        }
        if (parameterID == "LMF_FREQ") {
            return 6;
        }
        if (parameterID == "LMF_Q") {
            return 7;
        }
        if (parameterID == "LMF_GAIN") {
            return 8;
        }
        if (parameterID == "HPF_FREQ") {
            return 9;
        }
        if (parameterID == "HPF_Q") {
            return 10;
        }
        if (parameterID == "LPF_FREQ") {
            return 11;
        }
        if (parameterID == "LPF_Q") {
            return 12;
        }
        if (parameterID == "typeHMF") {
            return 13;
        }
        if (parameterID == "typeLMF") {
            return 14;
        }
        if (parameterID == "BYPASS_BIQUAD") {
            return 15;
        }
    
        return (-1);
    }    
    
    biquadStackData *SD;
};

//==============================================================================
class biquadAudioProcessor  : public AudioProcessor
{
    //==============================================================================
#if JUCE_VERSION >= 0x050400
    const StringArray m_choices14;
    const StringArray m_choices15;
    const StringArray m_choices16;

public:
    biquadAudioProcessor()
        : paramListener(&mStackData),
          m_choices14({ "Band", "Peaking", "Notch" }),
          m_choices15({ "Band", "Peaking", "Notch" }),
          m_choices16({ "off", "on" }),
          parameters(*this, nullptr, "biquad", {
                std::make_unique<Parameter>("HS_FREQ", juce::String::fromUTF8(u8"HI SHLF"), juce::String::fromUTF8(u8"Hz"),
                    NormalisableRange<float>(1000.f,20000.f,[](float min, float max, float norm) {return min*powf(max/min,norm);}, [](float min, float max, float val) {return logf(val/min)/logf(max/min);}), 15000.f, [](float val) {return String(val, 3);}, nullptr),
                std::make_unique<Parameter>("HS_Q", juce::String::fromUTF8(u8"Q"), juce::String::fromUTF8(u8""),
                    NormalisableRange<float>(0.1f,10.f,[](float min, float max, float norm) {return min*powf(max/min,norm);}, [](float min, float max, float val) {return logf(val/min)/logf(max/min);}), 0.5f, [](float val) {return String(val, 3);}, nullptr),
                std::make_unique<Parameter>("HS_GAIN", juce::String::fromUTF8(u8"GAIN"), juce::String::fromUTF8(u8"dB"),
                    NormalisableRange<float>(-12.f,12.f), 0.f, [](float val) {return String(val, 3);}, nullptr),
                std::make_unique<Parameter>("HMF_FREQ", juce::String::fromUTF8(u8"HI-MID"), juce::String::fromUTF8(u8"Hz"),
                    NormalisableRange<float>(8000.f,12500.f,[](float min, float max, float norm) {return min*powf(max/min,norm);}, [](float min, float max, float val) {return logf(val/min)/logf(max/min);}), 8000.f, [](float val) {return String(val, 3);}, nullptr),
                std::make_unique<Parameter>("HMF_Q", juce::String::fromUTF8(u8"Q"), juce::String::fromUTF8(u8""),
                    NormalisableRange<float>(0.1f,10.f,[](float min, float max, float norm) {return min*powf(max/min,norm);}, [](float min, float max, float val) {return logf(val/min)/logf(max/min);}), 0.5f, [](float val) {return String(val, 3);}, nullptr),
                std::make_unique<Parameter>("HMF_GAIN", juce::String::fromUTF8(u8"GAIN"), juce::String::fromUTF8(u8"dB"),
                    NormalisableRange<float>(-12.f,12.f), 0.f, [](float val) {return String(val, 3);}, nullptr),
                std::make_unique<Parameter>("LMF_FREQ", juce::String::fromUTF8(u8"LO-MID"), juce::String::fromUTF8(u8"Hz"),
                    NormalisableRange<float>(200.f,8000.f,[](float min, float max, float norm) {return min*powf(max/min,norm);}, [](float min, float max, float val) {return logf(val/min)/logf(max/min);}), 500.f, [](float val) {return String(val, 3);}, nullptr),
                std::make_unique<Parameter>("LMF_Q", juce::String::fromUTF8(u8"Q"), juce::String::fromUTF8(u8""),
                    NormalisableRange<float>(0.1f,10.f,[](float min, float max, float norm) {return min*powf(max/min,norm);}, [](float min, float max, float val) {return logf(val/min)/logf(max/min);}), 0.5f, [](float val) {return String(val, 3);}, nullptr),
                std::make_unique<Parameter>("LMF_GAIN", juce::String::fromUTF8(u8"GAIN"), juce::String::fromUTF8(u8"dB"),
                    NormalisableRange<float>(-12.f,12.f), 0.f, [](float val) {return String(val, 3);}, nullptr),
                std::make_unique<Parameter>("HPF_FREQ", juce::String::fromUTF8(u8"HPF"), juce::String::fromUTF8(u8"Hz"),
                    NormalisableRange<float>(20.f,400.f,[](float min, float max, float norm) {return min*powf(max/min,norm);}, [](float min, float max, float val) {return logf(val/min)/logf(max/min);}), 30.f, [](float val) {return String(val, 3);}, nullptr),
                std::make_unique<Parameter>("HPF_Q", juce::String::fromUTF8(u8"Q"), juce::String::fromUTF8(u8""),
                    NormalisableRange<float>(0.1f,10.f,[](float min, float max, float norm) {return min*powf(max/min,norm);}, [](float min, float max, float val) {return logf(val/min)/logf(max/min);}), 0.5f, [](float val) {return String(val, 3);}, nullptr),
                std::make_unique<Parameter>("LPF_FREQ", juce::String::fromUTF8(u8"LPF"), juce::String::fromUTF8(u8"Hz"),
                    NormalisableRange<float>(2500.f,20000.f,[](float min, float max, float norm) {return min*powf(max/min,norm);}, [](float min, float max, float val) {return logf(val/min)/logf(max/min);}), 18000.f, [](float val) {return String(val, 3);}, nullptr),
                std::make_unique<Parameter>("LPF_Q", juce::String::fromUTF8(u8"Q"), juce::String::fromUTF8(u8""),
                    NormalisableRange<float>(0.1f,10.f,[](float min, float max, float norm) {return min*powf(max/min,norm);}, [](float min, float max, float val) {return logf(val/min)/logf(max/min);}), 0.5f, [](float val) {return String(val, 3);}, nullptr),
                std::make_unique<Parameter>("typeHMF", juce::String::fromUTF8(u8"typeHMF"), juce::String::fromUTF8(u8""),
                    NormalisableRange<float>(0.f, m_choices14.size()-1.f, 1.f), 0.f,
                    [=](float value) { return m_choices14[(int) (value + 0.5)]; },
                    [=](const String& text) { return (float) m_choices14.indexOf(text); }, false, true, true),
                std::make_unique<Parameter>("typeLMF", juce::String::fromUTF8(u8"typeLMF"), juce::String::fromUTF8(u8""),
                    NormalisableRange<float>(0.f, m_choices15.size()-1.f, 1.f), 0.f,
                    [=](float value) { return m_choices15[(int) (value + 0.5)]; },
                    [=](const String& text) { return (float) m_choices15.indexOf(text); }, false, true, true),
                std::make_unique<Parameter>("BYPASS_BIQUAD", juce::String::fromUTF8(u8"BYPASS_BIQUAD"), juce::String::fromUTF8(u8""),
                    NormalisableRange<float>(0.f, m_choices16.size()-1.f, 1.f), 0.f,
                    [=](float value) { return m_choices16[(int) (value + 0.5)]; },
                    [=](const String& text) { return (float) m_choices16.indexOf(text); }, false, true, true) })

    {
        mStackData.pd = &mPersistentData;
        
        biquad_initialize(&mStackData);

        createPluginInstance(&mStackData, reinterpret_cast<unsigned long long>(this));

        parameters.addParameterListener("HS_FREQ", &paramListener);
        parameters.addParameterListener("HS_Q", &paramListener);
        parameters.addParameterListener("HS_GAIN", &paramListener);
        parameters.addParameterListener("HMF_FREQ", &paramListener);
        parameters.addParameterListener("HMF_Q", &paramListener);
        parameters.addParameterListener("HMF_GAIN", &paramListener);
        parameters.addParameterListener("LMF_FREQ", &paramListener);
        parameters.addParameterListener("LMF_Q", &paramListener);
        parameters.addParameterListener("LMF_GAIN", &paramListener);
        parameters.addParameterListener("HPF_FREQ", &paramListener);
        parameters.addParameterListener("HPF_Q", &paramListener);
        parameters.addParameterListener("LPF_FREQ", &paramListener);
        parameters.addParameterListener("LPF_Q", &paramListener);
        parameters.addParameterListener("typeHMF", &paramListener);
        parameters.addParameterListener("typeLMF", &paramListener);
        parameters.addParameterListener("BYPASS_BIQUAD", &paramListener);

    }
    //==============================================================================
#else // For JUCE prior to 5.4.0
public:
    biquadAudioProcessor()
    :   paramListener(&mStackData), parameters (*this, nullptr)
    {
        mStackData.pd = &mPersistentData;
        
        biquad_initialize(&mStackData);

        createPluginInstance(&mStackData, reinterpret_cast<unsigned long long>(this));

        //
        // Parameter property HS_FREQ
        //
        parameters.createAndAddParameter ("HS_FREQ", juce::String::fromUTF8(u8"HI SHLF"), juce::String::fromUTF8(u8"Hz"),
            NormalisableRange<float>(1000.f, 20000.f, 
                [](float min, float max, float norm) {return min * powf(max/min, norm);},
                [](float min, float max, float val) {return logf(val/min)/logf(max/min);} ),
            15000.f,
            [](float val) {return String(val, 3);},
            nullptr);
        parameters.addParameterListener("HS_FREQ", &paramListener);

        //
        // Parameter property HS_Q
        //
        parameters.createAndAddParameter ("HS_Q", juce::String::fromUTF8(u8"Q"), juce::String::fromUTF8(u8""),
            NormalisableRange<float>(0.1f, 10.f, 
                [](float min, float max, float norm) {return min * powf(max/min, norm);},
                [](float min, float max, float val) {return logf(val/min)/logf(max/min);} ),
            0.5f,
            [](float val) {return String(val, 3);},
            nullptr);
        parameters.addParameterListener("HS_Q", &paramListener);

        //
        // Parameter property HS_GAIN
        //
        parameters.createAndAddParameter ("HS_GAIN", juce::String::fromUTF8(u8"GAIN"), juce::String::fromUTF8(u8"dB"),
            NormalisableRange<float>(-12.f, 12.f), 0.f,
            [](float val) {return String(val, 3);},
            nullptr);
        parameters.addParameterListener("HS_GAIN", &paramListener);

        //
        // Parameter property HMF_FREQ
        //
        parameters.createAndAddParameter ("HMF_FREQ", juce::String::fromUTF8(u8"HI-MID"), juce::String::fromUTF8(u8"Hz"),
            NormalisableRange<float>(8000.f, 12500.f, 
                [](float min, float max, float norm) {return min * powf(max/min, norm);},
                [](float min, float max, float val) {return logf(val/min)/logf(max/min);} ),
            8000.f,
            [](float val) {return String(val, 3);},
            nullptr);
        parameters.addParameterListener("HMF_FREQ", &paramListener);

        //
        // Parameter property HMF_Q
        //
        parameters.createAndAddParameter ("HMF_Q", juce::String::fromUTF8(u8"Q"), juce::String::fromUTF8(u8""),
            NormalisableRange<float>(0.1f, 10.f, 
                [](float min, float max, float norm) {return min * powf(max/min, norm);},
                [](float min, float max, float val) {return logf(val/min)/logf(max/min);} ),
            0.5f,
            [](float val) {return String(val, 3);},
            nullptr);
        parameters.addParameterListener("HMF_Q", &paramListener);

        //
        // Parameter property HMF_GAIN
        //
        parameters.createAndAddParameter ("HMF_GAIN", juce::String::fromUTF8(u8"GAIN"), juce::String::fromUTF8(u8"dB"),
            NormalisableRange<float>(-12.f, 12.f), 0.f,
            [](float val) {return String(val, 3);},
            nullptr);
        parameters.addParameterListener("HMF_GAIN", &paramListener);

        //
        // Parameter property LMF_FREQ
        //
        parameters.createAndAddParameter ("LMF_FREQ", juce::String::fromUTF8(u8"LO-MID"), juce::String::fromUTF8(u8"Hz"),
            NormalisableRange<float>(200.f, 8000.f, 
                [](float min, float max, float norm) {return min * powf(max/min, norm);},
                [](float min, float max, float val) {return logf(val/min)/logf(max/min);} ),
            500.f,
            [](float val) {return String(val, 3);},
            nullptr);
        parameters.addParameterListener("LMF_FREQ", &paramListener);

        //
        // Parameter property LMF_Q
        //
        parameters.createAndAddParameter ("LMF_Q", juce::String::fromUTF8(u8"Q"), juce::String::fromUTF8(u8""),
            NormalisableRange<float>(0.1f, 10.f, 
                [](float min, float max, float norm) {return min * powf(max/min, norm);},
                [](float min, float max, float val) {return logf(val/min)/logf(max/min);} ),
            0.5f,
            [](float val) {return String(val, 3);},
            nullptr);
        parameters.addParameterListener("LMF_Q", &paramListener);

        //
        // Parameter property LMF_GAIN
        //
        parameters.createAndAddParameter ("LMF_GAIN", juce::String::fromUTF8(u8"GAIN"), juce::String::fromUTF8(u8"dB"),
            NormalisableRange<float>(-12.f, 12.f), 0.f,
            [](float val) {return String(val, 3);},
            nullptr);
        parameters.addParameterListener("LMF_GAIN", &paramListener);

        //
        // Parameter property HPF_FREQ
        //
        parameters.createAndAddParameter ("HPF_FREQ", juce::String::fromUTF8(u8"HPF"), juce::String::fromUTF8(u8"Hz"),
            NormalisableRange<float>(20.f, 400.f, 
                [](float min, float max, float norm) {return min * powf(max/min, norm);},
                [](float min, float max, float val) {return logf(val/min)/logf(max/min);} ),
            30.f,
            [](float val) {return String(val, 3);},
            nullptr);
        parameters.addParameterListener("HPF_FREQ", &paramListener);

        //
        // Parameter property HPF_Q
        //
        parameters.createAndAddParameter ("HPF_Q", juce::String::fromUTF8(u8"Q"), juce::String::fromUTF8(u8""),
            NormalisableRange<float>(0.1f, 10.f, 
                [](float min, float max, float norm) {return min * powf(max/min, norm);},
                [](float min, float max, float val) {return logf(val/min)/logf(max/min);} ),
            0.5f,
            [](float val) {return String(val, 3);},
            nullptr);
        parameters.addParameterListener("HPF_Q", &paramListener);

        //
        // Parameter property LPF_FREQ
        //
        parameters.createAndAddParameter ("LPF_FREQ", juce::String::fromUTF8(u8"LPF"), juce::String::fromUTF8(u8"Hz"),
            NormalisableRange<float>(2500.f, 20000.f, 
                [](float min, float max, float norm) {return min * powf(max/min, norm);},
                [](float min, float max, float val) {return logf(val/min)/logf(max/min);} ),
            18000.f,
            [](float val) {return String(val, 3);},
            nullptr);
        parameters.addParameterListener("LPF_FREQ", &paramListener);

        //
        // Parameter property LPF_Q
        //
        parameters.createAndAddParameter ("LPF_Q", juce::String::fromUTF8(u8"Q"), juce::String::fromUTF8(u8""),
            NormalisableRange<float>(0.1f, 10.f, 
                [](float min, float max, float norm) {return min * powf(max/min, norm);},
                [](float min, float max, float val) {return logf(val/min)/logf(max/min);} ),
            0.5f,
            [](float val) {return String(val, 3);},
            nullptr);
        parameters.addParameterListener("LPF_Q", &paramListener);

        //
        // Parameter property typeHMF
        //
        const StringArray choices14({ "Band", "Peaking", "Notch" });
        parameters.createAndAddParameter ("typeHMF", juce::String::fromUTF8(u8"typeHMF"), juce::String::fromUTF8(u8""),
            NormalisableRange<float>(0.f, choices14.size()-1.f, 1.f), 0.f,
            [=](float value) { return choices14[(int) (value + 0.5)]; },
            [=](const String& text) { return (float) choices14.indexOf(text); },
            false, true, true);
        parameters.addParameterListener("typeHMF", &paramListener);

        //
        // Parameter property typeLMF
        //
        const StringArray choices15({ "Band", "Peaking", "Notch" });
        parameters.createAndAddParameter ("typeLMF", juce::String::fromUTF8(u8"typeLMF"), juce::String::fromUTF8(u8""),
            NormalisableRange<float>(0.f, choices15.size()-1.f, 1.f), 0.f,
            [=](float value) { return choices15[(int) (value + 0.5)]; },
            [=](const String& text) { return (float) choices15.indexOf(text); },
            false, true, true);
        parameters.addParameterListener("typeLMF", &paramListener);

        //
        // Parameter property BYPASS_BIQUAD
        //
        const StringArray choices16({ "off", "on" });
        parameters.createAndAddParameter ("BYPASS_BIQUAD", juce::String::fromUTF8(u8"BYPASS_BIQUAD"), juce::String::fromUTF8(u8""),
            NormalisableRange<float>(0.f, choices16.size()-1.f, 1.f), 0.f,
            [=](float value) { return choices16[(int) (value + 0.5)]; },
            [=](const String& text) { return (float) choices16.indexOf(text); },
            false, true, true);
        parameters.addParameterListener("BYPASS_BIQUAD", &paramListener);

        parameters.state = ValueTree(Identifier("biquad"));
    }
#endif

    //==============================================================================
    ~biquadAudioProcessor()
    {
        biquad_terminate(&mStackData);
    }
    
    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override
    {
        (void)samplesPerBlock;
        resetCImpl(&mStackData, sampleRate);
        setLatencySamples(getLatencyInSamplesCImpl(&mStackData));
    }

    void releaseResources() override                { }
    
    
    void processBlock (AudioBuffer<double>& buffer, MidiBuffer&) override
    {
        ScopedNoDenormals noDenormals;
        const int nSamples = buffer.getNumSamples();
        const int nChannels = buffer.getNumChannels();
        const double* const* pin = buffer.getArrayOfReadPointers();
        double* const* pout = buffer.getArrayOfWritePointers();
        std::vector<const double*> inputs(pin,pin+nChannels);
        std::vector<double*> outputs(pout,pout+nChannels);
        int i_;

        biquadStackData *SD = &mStackData;

        if (nChannels < 2) {
            const int numExtraChannels = 2 - nChannels;
            tempBuffer.setSize(numExtraChannels, nSamples);
            if (nChannels < 2) {
                tempBuffer.clear(0, nSamples);
                const double* const* p = tempBuffer.getArrayOfReadPointers();
                std::copy(p, p+numExtraChannels, std::back_inserter(inputs));
            }
            if (nChannels < 2) {
                double* const* p = tempBuffer.getArrayOfWritePointers();
                std::copy(p, p+numExtraChannels, std::back_inserter(outputs));
            }
        }

        int osz0_;
        int osz1_;
        if (nSamples <= MAX_SAMPLES_PER_FRAME) {
            /* Fast path for common frame sizes. */
            const int isz0_ = nSamples;
            const int isz1_ = nSamples;
            processEntryPoint(SD, (double)nSamples,
                    inputs[0], &isz0_,
                    inputs[1], &isz1_,
                    outputs[0], &osz0_,
                    outputs[1], &osz1_);
        } else {
            /* Fallback for unusually large frames. */
            int isz0_ = MAX_SAMPLES_PER_FRAME;
            int isz1_ = MAX_SAMPLES_PER_FRAME;
            int n = MAX_SAMPLES_PER_FRAME;
            for (i_ = 0; i_ < nSamples; i_ += MAX_SAMPLES_PER_FRAME) {
                if (i_ + MAX_SAMPLES_PER_FRAME > nSamples) {
                    n = nSamples - i_;
                    isz0_ = nSamples - i_;
                    isz1_ = nSamples - i_;
                }
                processEntryPoint(SD, (double)n,
                        inputs[0]+i_, &isz0_,
                        inputs[1]+i_, &isz1_,
                        outputs[0]+i_, &osz0_,
                        outputs[1]+i_, &osz1_);
            }
        }

    }
    
    void processBlock (AudioBuffer<float>& buffer,  MidiBuffer& midiMessages) override
    {
        AudioBuffer<double> doubleBuffer;
        doubleBuffer.makeCopyOf(buffer);
        processBlock(doubleBuffer, midiMessages);
        buffer.makeCopyOf(doubleBuffer);
    }
    
    //==============================================================================
    bool hasEditor() const override                 { return true; }
    AudioProcessorEditor* createEditor() override;
    
    //==============================================================================
    const String getName() const override           { return JucePlugin_Name; }

    bool acceptsMidi() const override               { return false; }
    bool producesMidi() const override              { return false; }
    bool isMidiEffect () const override             { return false; }
    double getTailLengthSeconds() const override    { return 0.0;   }

    //==============================================================================
    // NB: some hosts don't cope very well if you tell them there are 0 programs,
    // so this should be at least 1, even if you're not really implementing programs.
    int getNumPrograms() override                       { return 1;  }
    int getCurrentProgram() override                    { return 0;  }
    void setCurrentProgram (int index) override         { (void) index; }
    const String getProgramName (int index) override    { (void) index; return {}; }
    void changeProgramName (int index, const String& newName) override  { (void) index; (void) newName; }
    
    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override
    {
        auto xml (parameters.state.createXml());
        copyXmlToBinary (*xml, destData);
    }
    
    void setStateInformation (const void* data, int sizeInBytes) override
    {
        auto xmlState (getXmlFromBinary (data, sizeInBytes));
        if (xmlState != nullptr)
            if (xmlState->hasTagName (parameters.state.getType()))
                parameters.state = ValueTree::fromXml (*xmlState);
    }
    
    bool supportsDoublePrecisionProcessing() const override  { return true; }
    
private:
    //==============================================================================
    static const int MAX_SAMPLES_PER_FRAME = 4096;

    biquadStackData mStackData;
    biquadPersistentData mPersistentData;
    onParamChangeListener paramListener;
    AudioBuffer<double> tempBuffer;
    
    //==============================================================================
    AudioProcessorValueTreeState parameters;
 
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (biquadAudioProcessor)
};

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new biquadAudioProcessor();
}

#include "biquadPluginEditor.h"

AudioProcessorEditor* biquadAudioProcessor::createEditor()
{
    return new biquadAudioProcessorEditor(*this, parameters);
}

