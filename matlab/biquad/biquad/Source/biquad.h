//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// biquad.h
//
// Code generation for function 'biquad'
//

#ifndef BIQUAD_H
#define BIQUAD_H

// Include files
#include "biquad_types1.h"
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Type Declarations
struct biquadStackData;

// Type Definitions
class ParameterSmoother {
public:
  double step();
  ParameterSmoother();
  ~ParameterSmoother();
  int isInitialized;
  double smoothingFactor;
  double currentValue;
  double targetValue;
};

class derivedAudioPlugin {
public:
  derivedAudioPlugin *init(biquadStackData *SD);
  derivedAudioPlugin();
  ~derivedAudioPlugin();
  boolean_T matlabCodegenIsDeleted;
  double PrivateSampleRate;
  int PrivateLatency;
  double HS_FREQ;
  double HS_GAIN;
  double HS_Q;
  double HMF_FREQ;
  double HMF_GAIN;
  double HMF_Q;
  double LMF_FREQ;
  double LMF_GAIN;
  double LMF_Q;
  double HPF_FREQ;
  double HPF_Q;
  double LPF_FREQ;
  double LPF_Q;
  double fs;
  coder::array<char, 2U> typeHMF;
  coder::array<char, 2U> typeLMF;
  coder::array<char, 2U> BYPASS_BIQUAD;
  struct_T filter_HS;
  struct_T filter_HMF;
  struct_T filter_LMF;
  struct_T filter_HPF;
  struct_T filter_LPF;
  ParameterSmoother hsFreqSmoother;
  ParameterSmoother hmfFreqSmoother;
  ParameterSmoother lmfFreqSmoother;
  ParameterSmoother hpfFreqSmoother;
  ParameterSmoother lpfFreqSmoother;
  ParameterSmoother hsGainSmoother;
  ParameterSmoother hmfGainSmoother;
  ParameterSmoother lmfGainSmoother;
  ParameterSmoother hsQSmoother;
  ParameterSmoother hmfQSmoother;
  ParameterSmoother lmfQSmoother;
  ParameterSmoother hpfQSmoother;
  ParameterSmoother lpfQSmoother;
};

// Function Declarations
extern void biquad_initialize(biquadStackData *SD);

extern void biquad_terminate(biquadStackData *SD);

extern void createPluginInstance(biquadStackData *SD, unsigned long thisPtr);

extern int getLatencyInSamplesCImpl(biquadStackData *SD);

extern void onParamChangeCImpl(biquadStackData *SD, int paramIdx,
                               double b_value);

extern void processEntryPoint(biquadStackData *SD, double samplesPerFrame,
                              const double i1_data[], const int i1_size[1],
                              const double i2_data[], const int i2_size[1],
                              double o1_data[], int o1_size[1],
                              double o2_data[], int o2_size[1]);

extern void resetCImpl(biquadStackData *SD, double rate);

#endif
// End of code generation (biquad.h)
