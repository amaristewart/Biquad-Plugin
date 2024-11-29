//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// biquad.cpp
//
// Code generation for function 'biquad'
//

// Include files
#include "biquad.h"
#include "biquad_types.h"
#include "biquad_types1.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <cmath>

// Type Definitions
class audioPlugin {
public:
  static void wormholeToConstructor_init(biquadStackData *SD);
};

// Function Declarations
namespace coder {
namespace internal {
static boolean_T b_strcmp(const array<char, 2U> &a);

static boolean_T c_strcmp(const array<char, 2U> &a);

static boolean_T d_strcmp(const array<char, 2U> &a);

static boolean_T e_strcmp(const array<char, 2U> &a);

static double minimum(const double x[2]);

} // namespace internal
static double mpower(double b);

} // namespace coder
static derivedAudioPlugin *getPluginInstance(biquadStackData *SD);

static void getPluginInstance_delete(biquadStackData *SD);

static void getPluginInstance_init(biquadStackData *SD);

static void getPluginInstance_new(biquadStackData *SD);

// Function Definitions
derivedAudioPlugin *derivedAudioPlugin::init(biquadStackData *SD)
{
  derivedAudioPlugin *plugin;
  plugin = this;
  plugin->PrivateLatency = 0;
  SD->pd->thisPtr_not_empty = true;
  return plugin;
}

double ParameterSmoother::step()
{
  double varargout_1;
  if (isInitialized != 1) {
    isInitialized = 1;
  }
  //  used to update parameter value incrementally each time the audio frame is
  //  processed Perform the smoothing
  varargout_1 =
      smoothingFactor * currentValue + (1.0 - smoothingFactor) * targetValue;
  currentValue = varargout_1;
  //  larger smooth val = slower ramp, smaller smooth val = faster ramp
  return varargout_1;
}

void audioPlugin::wormholeToConstructor_init(biquadStackData *SD)
{
  SD->pd->thisPtr_not_empty = false;
}

namespace coder {
namespace internal {
static boolean_T b_strcmp(const array<char, 2U> &a)
{
  static const char cv[2]{'o', 'n'};
  boolean_T b_bool;
  b_bool = false;
  if (a.size(1) == 2) {
    int kstr;
    kstr = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (kstr < 2) {
        if (a[kstr] != cv[kstr]) {
          exitg1 = 1;
        } else {
          kstr++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }
  return b_bool;
}

static boolean_T c_strcmp(const array<char, 2U> &a)
{
  static const char cv[4]{'B', 'a', 'n', 'd'};
  boolean_T b_bool;
  b_bool = false;
  if (a.size(1) == 4) {
    int kstr;
    kstr = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (kstr < 4) {
        if (a[kstr] != cv[kstr]) {
          exitg1 = 1;
        } else {
          kstr++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }
  return b_bool;
}

static boolean_T d_strcmp(const array<char, 2U> &a)
{
  static const char cv[7]{'P', 'e', 'a', 'k', 'i', 'n', 'g'};
  boolean_T b_bool;
  b_bool = false;
  if (a.size(1) == 7) {
    int kstr;
    kstr = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (kstr < 7) {
        if (a[kstr] != cv[kstr]) {
          exitg1 = 1;
        } else {
          kstr++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }
  return b_bool;
}

static boolean_T e_strcmp(const array<char, 2U> &a)
{
  static const char cv[5]{'N', 'o', 't', 'c', 'h'};
  boolean_T b_bool;
  b_bool = false;
  if (a.size(1) == 5) {
    int kstr;
    kstr = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (kstr < 5) {
        if (a[kstr] != cv[kstr]) {
          exitg1 = 1;
        } else {
          kstr++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }
  return b_bool;
}

static double minimum(const double x[2])
{
  double ex;
  if (x[0] > x[1]) {
    ex = x[1];
  } else {
    ex = x[0];
  }
  return ex;
}

} // namespace internal
static double mpower(double b)
{
  double c;
  if (std::isnan(b)) {
    c = rtNaN;
  } else {
    c = std::abs(b);
    if (std::isinf(b)) {
      if (b > 0.0) {
        c = rtInf;
      } else {
        c = 0.0;
      }
    } else if (c == 0.0) {
      c = 1.0;
    } else if (c == 1.0) {
      if (b > 0.0) {
        c = 10.0;
      } else {
        c = 0.1;
      }
    } else if (b == 2.0) {
      c = 100.0;
    } else if (b == 0.5) {
      c = 3.1622776601683795;
    } else {
      c = std::pow(10.0, b);
    }
  }
  return c;
}

} // namespace coder
static derivedAudioPlugin *getPluginInstance(biquadStackData *SD)
{
  derivedAudioPlugin *plugin;
  if (!SD->pd->plugin_not_empty) {
    double initialValue;
    //  Pass constructor args to plugin.
    SD->pd->plugin.HS_FREQ = 15000.0;
    SD->pd->plugin.HS_GAIN = 0.0;
    SD->pd->plugin.HS_Q = 0.5;
    SD->pd->plugin.HMF_FREQ = 8000.0;
    SD->pd->plugin.HMF_GAIN = 0.0;
    SD->pd->plugin.HMF_Q = 0.5;
    SD->pd->plugin.LMF_FREQ = 500.0;
    SD->pd->plugin.LMF_GAIN = 0.0;
    SD->pd->plugin.LMF_Q = 0.5;
    SD->pd->plugin.HPF_FREQ = 30.0;
    SD->pd->plugin.HPF_Q = 0.5;
    SD->pd->plugin.LPF_FREQ = 18000.0;
    SD->pd->plugin.LPF_Q = 0.5;
    SD->pd->plugin.fs = 44100.0;
    SD->pd->plugin.typeHMF.set_size(1, 4);
    SD->pd->plugin.typeLMF.set_size(1, 4);
    SD->pd->plugin.typeHMF[0] = 'B';
    SD->pd->plugin.typeLMF[0] = 'B';
    SD->pd->plugin.typeHMF[1] = 'a';
    SD->pd->plugin.typeLMF[1] = 'a';
    SD->pd->plugin.typeHMF[2] = 'n';
    SD->pd->plugin.typeLMF[2] = 'n';
    SD->pd->plugin.typeHMF[3] = 'd';
    SD->pd->plugin.typeLMF[3] = 'd';
    SD->pd->plugin.BYPASS_BIQUAD.set_size(1, 3);
    SD->pd->plugin.BYPASS_BIQUAD[0] = 'o';
    SD->pd->plugin.BYPASS_BIQUAD[1] = 'f';
    SD->pd->plugin.BYPASS_BIQUAD[2] = 'f';
    SD->pd->plugin.filter_HMF.a0 = 1.0;
    SD->pd->plugin.filter_HMF.a1 = 0.0;
    SD->pd->plugin.filter_HMF.a2 = 0.0;
    SD->pd->plugin.filter_HMF.b0 = 1.0;
    SD->pd->plugin.filter_HMF.b1 = 0.0;
    SD->pd->plugin.filter_HMF.b2 = 0.0;
    SD->pd->plugin.filter_HMF.w[0] = 0.0;
    SD->pd->plugin.filter_LMF.w[0] = 0.0;
    SD->pd->plugin.filter_HMF.w[1] = 0.0;
    SD->pd->plugin.filter_LMF.w[1] = 0.0;
    SD->pd->plugin.filter_HMF.w[2] = 0.0;
    SD->pd->plugin.filter_LMF.w[2] = 0.0;
    SD->pd->plugin.filter_HMF.w[3] = 0.0;
    SD->pd->plugin.filter_LMF.w[3] = 0.0;
    SD->pd->plugin.filter_LMF.a0 = 1.0;
    SD->pd->plugin.filter_LMF.a1 = 0.0;
    SD->pd->plugin.filter_LMF.a2 = 0.0;
    SD->pd->plugin.filter_LMF.b0 = 1.0;
    SD->pd->plugin.filter_LMF.b1 = 0.0;
    SD->pd->plugin.filter_LMF.b2 = 0.0;
    plugin = SD->pd->plugin.init(SD);
    //  Initialize smoothers with default values
    initialValue = plugin->HS_FREQ;
    plugin->hsFreqSmoother.isInitialized = 0;
    //  constructor
    plugin->hsFreqSmoother.currentValue = initialValue;
    //  gradually updated each time the audio frame is processed
    plugin->hsFreqSmoother.targetValue = initialValue;
    //  will incrementally adjust currentValue towards targetValue
    plugin->hsFreqSmoother.smoothingFactor = 0.9;
    //  rate at which the currentValue approaches the targetValue
    initialValue = plugin->HMF_FREQ;
    plugin->hmfFreqSmoother.isInitialized = 0;
    //  constructor
    plugin->hmfFreqSmoother.currentValue = initialValue;
    //  gradually updated each time the audio frame is processed
    plugin->hmfFreqSmoother.targetValue = initialValue;
    //  will incrementally adjust currentValue towards targetValue
    plugin->hmfFreqSmoother.smoothingFactor = 0.9;
    //  rate at which the currentValue approaches the targetValue
    initialValue = plugin->LMF_FREQ;
    plugin->lmfFreqSmoother.isInitialized = 0;
    //  constructor
    plugin->lmfFreqSmoother.currentValue = initialValue;
    //  gradually updated each time the audio frame is processed
    plugin->lmfFreqSmoother.targetValue = initialValue;
    //  will incrementally adjust currentValue towards targetValue
    plugin->lmfFreqSmoother.smoothingFactor = 0.9;
    //  rate at which the currentValue approaches the targetValue
    initialValue = plugin->HPF_FREQ;
    plugin->hpfFreqSmoother.isInitialized = 0;
    //  constructor
    plugin->hpfFreqSmoother.currentValue = initialValue;
    //  gradually updated each time the audio frame is processed
    plugin->hpfFreqSmoother.targetValue = initialValue;
    //  will incrementally adjust currentValue towards targetValue
    plugin->hpfFreqSmoother.smoothingFactor = 0.9;
    //  rate at which the currentValue approaches the targetValue
    initialValue = plugin->LPF_FREQ;
    plugin->lpfFreqSmoother.isInitialized = 0;
    //  constructor
    plugin->lpfFreqSmoother.currentValue = initialValue;
    //  gradually updated each time the audio frame is processed
    plugin->lpfFreqSmoother.targetValue = initialValue;
    //  will incrementally adjust currentValue towards targetValue
    plugin->lpfFreqSmoother.smoothingFactor = 0.9;
    //  rate at which the currentValue approaches the targetValue
    initialValue = plugin->HS_GAIN;
    plugin->hsGainSmoother.isInitialized = 0;
    //  constructor
    plugin->hsGainSmoother.currentValue = initialValue;
    //  gradually updated each time the audio frame is processed
    plugin->hsGainSmoother.targetValue = initialValue;
    //  will incrementally adjust currentValue towards targetValue
    plugin->hsGainSmoother.smoothingFactor = 0.9;
    //  rate at which the currentValue approaches the targetValue
    initialValue = plugin->HMF_GAIN;
    plugin->hmfGainSmoother.isInitialized = 0;
    //  constructor
    plugin->hmfGainSmoother.currentValue = initialValue;
    //  gradually updated each time the audio frame is processed
    plugin->hmfGainSmoother.targetValue = initialValue;
    //  will incrementally adjust currentValue towards targetValue
    plugin->hmfGainSmoother.smoothingFactor = 0.9;
    //  rate at which the currentValue approaches the targetValue
    initialValue = plugin->LMF_GAIN;
    plugin->lmfGainSmoother.isInitialized = 0;
    //  constructor
    plugin->lmfGainSmoother.currentValue = initialValue;
    //  gradually updated each time the audio frame is processed
    plugin->lmfGainSmoother.targetValue = initialValue;
    //  will incrementally adjust currentValue towards targetValue
    plugin->lmfGainSmoother.smoothingFactor = 0.9;
    //  rate at which the currentValue approaches the targetValue
    initialValue = plugin->HS_Q;
    plugin->hsQSmoother.isInitialized = 0;
    //  constructor
    plugin->hsQSmoother.currentValue = initialValue;
    //  gradually updated each time the audio frame is processed
    plugin->hsQSmoother.targetValue = initialValue;
    //  will incrementally adjust currentValue towards targetValue
    plugin->hsQSmoother.smoothingFactor = 0.9;
    //  rate at which the currentValue approaches the targetValue
    initialValue = plugin->HMF_Q;
    plugin->hmfQSmoother.isInitialized = 0;
    //  constructor
    plugin->hmfQSmoother.currentValue = initialValue;
    //  gradually updated each time the audio frame is processed
    plugin->hmfQSmoother.targetValue = initialValue;
    //  will incrementally adjust currentValue towards targetValue
    plugin->hmfQSmoother.smoothingFactor = 0.9;
    //  rate at which the currentValue approaches the targetValue
    initialValue = plugin->LMF_Q;
    plugin->lmfQSmoother.isInitialized = 0;
    //  constructor
    plugin->lmfQSmoother.currentValue = initialValue;
    //  gradually updated each time the audio frame is processed
    plugin->lmfQSmoother.targetValue = initialValue;
    //  will incrementally adjust currentValue towards targetValue
    plugin->lmfQSmoother.smoothingFactor = 0.9;
    //  rate at which the currentValue approaches the targetValue
    initialValue = plugin->HPF_Q;
    plugin->hpfQSmoother.isInitialized = 0;
    //  constructor
    plugin->hpfQSmoother.currentValue = initialValue;
    //  gradually updated each time the audio frame is processed
    plugin->hpfQSmoother.targetValue = initialValue;
    //  will incrementally adjust currentValue towards targetValue
    plugin->hpfQSmoother.smoothingFactor = 0.9;
    //  rate at which the currentValue approaches the targetValue
    initialValue = plugin->LPF_Q;
    plugin->lpfQSmoother.isInitialized = 0;
    //  constructor
    plugin->lpfQSmoother.currentValue = initialValue;
    //  gradually updated each time the audio frame is processed
    plugin->lpfQSmoother.targetValue = initialValue;
    //  will incrementally adjust currentValue towards targetValue
    plugin->lpfQSmoother.smoothingFactor = 0.9;
    //  rate at which the currentValue approaches the targetValue
    plugin->matlabCodegenIsDeleted = false;
    SD->pd->plugin_not_empty = true;
  }
  return &SD->pd->plugin;
}

static void getPluginInstance_delete(biquadStackData *SD)
{
  if (!SD->pd->plugin.matlabCodegenIsDeleted) {
    SD->pd->plugin.matlabCodegenIsDeleted = true;
  }
}

static void getPluginInstance_init(biquadStackData *SD)
{
  SD->pd->plugin_not_empty = false;
}

static void getPluginInstance_new(biquadStackData *SD)
{
  SD->pd->plugin.matlabCodegenIsDeleted = true;
}

ParameterSmoother::ParameterSmoother() = default;

ParameterSmoother::~ParameterSmoother() = default;

derivedAudioPlugin::derivedAudioPlugin() = default;

derivedAudioPlugin::~derivedAudioPlugin() = default;

void biquad_initialize(biquadStackData *SD)
{
  getPluginInstance_new(SD);
  getPluginInstance_init(SD);
  audioPlugin::wormholeToConstructor_init(SD);
}

void biquad_terminate(biquadStackData *SD)
{
  getPluginInstance_delete(SD);
}

void createPluginInstance(biquadStackData *SD, unsigned long)
{
  SD->pd->thisPtr_not_empty = true;
  getPluginInstance(SD);
}

int getLatencyInSamplesCImpl(biquadStackData *SD)
{
  derivedAudioPlugin *plugin;
  plugin = getPluginInstance(SD);
  return plugin->PrivateLatency;
}

void onParamChangeCImpl(biquadStackData *SD, int paramIdx, double b_value)
{
  static const char cv[7]{'P', 'e', 'a', 'k', 'i', 'n', 'g'};
  static const char cv1[5]{'N', 'o', 't', 'c', 'h'};
  derivedAudioPlugin *plugin;
  plugin = getPluginInstance(SD);
  switch (paramIdx) {
  case 0:
    plugin->HS_FREQ = b_value;
    //  setter
    plugin->hsFreqSmoother.targetValue = b_value;
    break;
  case 1:
    plugin->HS_Q = b_value;
    //  setter
    plugin->hsQSmoother.targetValue = b_value;
    break;
  case 2:
    plugin->HS_GAIN = b_value;
    //  setter
    plugin->hsGainSmoother.targetValue = b_value;
    break;
  case 3:
    plugin->HMF_FREQ = b_value;
    //  setter
    plugin->hmfFreqSmoother.targetValue = b_value;
    break;
  case 4:
    plugin->HMF_Q = b_value;
    //  setter
    plugin->hmfQSmoother.targetValue = b_value;
    break;
  case 5:
    plugin->HMF_GAIN = b_value;
    //  setter
    plugin->hmfGainSmoother.targetValue = b_value;
    break;
  case 6:
    plugin->LMF_FREQ = b_value;
    //  setter
    plugin->lmfFreqSmoother.targetValue = b_value;
    break;
  case 7:
    plugin->LMF_Q = b_value;
    //  setter
    plugin->lmfQSmoother.targetValue = b_value;
    break;
  case 8:
    plugin->LMF_GAIN = b_value;
    //  setter
    plugin->lmfGainSmoother.targetValue = b_value;
    break;
  case 9:
    plugin->HPF_FREQ = b_value;
    //  setter
    plugin->hpfFreqSmoother.targetValue = b_value;
    break;
  case 10:
    plugin->HPF_Q = b_value;
    //  setter
    plugin->hpfQSmoother.targetValue = b_value;
    break;
  case 11:
    plugin->LPF_FREQ = b_value;
    //  setter
    plugin->lpfFreqSmoother.targetValue = b_value;
    break;
  case 12:
    plugin->LPF_Q = b_value;
    //  setter
    plugin->lpfQSmoother.targetValue = b_value;
    break;
  case 13:
    switch (static_cast<int>(b_value)) {
    case 0:
      plugin->typeHMF.set_size(1, 4);
      plugin->typeHMF[0] = 'B';
      plugin->typeHMF[1] = 'a';
      plugin->typeHMF[2] = 'n';
      plugin->typeHMF[3] = 'd';
      break;
    case 1:
      plugin->typeHMF.set_size(1, 7);
      for (int i{0}; i < 7; i++) {
        plugin->typeHMF[i] = cv[i];
      }
      break;
    case 2:
      plugin->typeHMF.set_size(1, 5);
      for (int i{0}; i < 5; i++) {
        plugin->typeHMF[i] = cv1[i];
      }
      break;
    }
    break;
  case 14:
    switch (static_cast<int>(b_value)) {
    case 0:
      plugin->typeLMF.set_size(1, 4);
      plugin->typeLMF[0] = 'B';
      plugin->typeLMF[1] = 'a';
      plugin->typeLMF[2] = 'n';
      plugin->typeLMF[3] = 'd';
      break;
    case 1:
      plugin->typeLMF.set_size(1, 7);
      for (int i{0}; i < 7; i++) {
        plugin->typeLMF[i] = cv[i];
      }
      break;
    case 2:
      plugin->typeLMF.set_size(1, 5);
      for (int i{0}; i < 5; i++) {
        plugin->typeLMF[i] = cv1[i];
      }
      break;
    }
    break;
  case 15:
    switch (static_cast<int>(b_value)) {
    case 0:
      plugin->BYPASS_BIQUAD.set_size(1, 3);
      plugin->BYPASS_BIQUAD[0] = 'o';
      plugin->BYPASS_BIQUAD[1] = 'f';
      plugin->BYPASS_BIQUAD[2] = 'f';
      break;
    case 1:
      plugin->BYPASS_BIQUAD.set_size(1, 2);
      plugin->BYPASS_BIQUAD[0] = 'o';
      plugin->BYPASS_BIQUAD[1] = 'n';
      break;
    }
    break;
  }
}

void processEntryPoint(biquadStackData *SD, double samplesPerFrame,
                       const double i1_data[], const int i1_size[1],
                       const double i2_data[], const int i2_size[1],
                       double o1_data[], int o1_size[1], double o2_data[],
                       int o2_size[1])
{
  derivedAudioPlugin *plugin;
  coder::array<double, 2U> out1;
  coder::array<double, 2U> result;
  coder::array<double, 2U> t1;
  double b_x_data[4096];
  double c_x_data[4096];
  double d_x_data[4096];
  double e_x_data[4096];
  double x_data[4096];
  double dv[2];
  double A;
  double Q;
  double f0;
  double filt_b1;
  double filt_b2;
  double gain;
  double w0;
  int b_loop_ub;
  int i;
  int loop_ub;
  int w1_tmp;
  plugin = getPluginInstance(SD);
  loop_ub = i1_size[0];
  result.set_size(i1_size[0], 2);
  for (i = 0; i < loop_ub; i++) {
    result[i] = i1_data[i];
  }
  b_loop_ub = i2_size[0];
  for (i = 0; i < b_loop_ub; i++) {
    result[i + result.size(0)] = i2_data[i];
  }
  dv[0] = result.size(0);
  dv[1] = 2.0;
  b_loop_ub = result.size(0);
  out1.set_size(b_loop_ub, 2);
  t1.set_size(b_loop_ub, 2);
  //  Smooth values
  Q = plugin->hmfQSmoother.step();
  f0 = plugin->hmfFreqSmoother.step();
  gain = plugin->hmfGainSmoother.step();
  w0 = 6.2831853071795862 * f0 / plugin->fs;
  f0 = std::sin(w0) / (2.0 * Q);
  // A = sqrt(db2mag(gain));
  A = coder::mpower(gain / 40.0);
  if (std::abs(gain) < 0.001) {
    plugin->filter_HMF.a0 = 1.0;
    plugin->filter_HMF.a1 = 0.0;
    plugin->filter_HMF.a2 = 0.0;
    plugin->filter_HMF.b0 = 1.0;
    plugin->filter_HMF.b1 = 0.0;
    plugin->filter_HMF.b2 = 0.0;
  } else if (coder::internal::c_strcmp(plugin->typeHMF)) {
    plugin->filter_HMF.a0 = f0 * A;
    plugin->filter_HMF.a1 = 0.0;
    plugin->filter_HMF.a2 = -f0 * A;
    plugin->filter_HMF.b0 = f0 + 1.0;
    plugin->filter_HMF.b1 = -2.0 * std::cos(w0);
    plugin->filter_HMF.b2 = 1.0 - f0;
  } else if (coder::internal::d_strcmp(plugin->typeHMF)) {
    filt_b1 = f0 * A;
    plugin->filter_HMF.a0 = filt_b1 + 1.0;
    filt_b2 = std::cos(w0);
    plugin->filter_HMF.a1 = -2.0 * filt_b2;
    plugin->filter_HMF.a2 = 1.0 - filt_b1;
    filt_b1 = f0 / A;
    plugin->filter_HMF.b0 = filt_b1 + 1.0;
    plugin->filter_HMF.b1 = -2.0 * filt_b2;
    plugin->filter_HMF.b2 = 1.0 - filt_b1;
  } else if (coder::internal::e_strcmp(plugin->typeHMF)) {
    plugin->filter_HMF.a0 = 1.0;
    filt_b1 = std::cos(w0);
    plugin->filter_HMF.a1 = -2.0 * filt_b1;
    plugin->filter_HMF.a2 = 1.0;
    plugin->filter_HMF.b0 = f0 + 1.0;
    plugin->filter_HMF.b1 = -2.0 * filt_b1;
    plugin->filter_HMF.b2 = 1.0 - f0;
  }
  Q = plugin->lmfQSmoother.step();
  f0 = plugin->lmfFreqSmoother.step();
  gain = plugin->lmfGainSmoother.step();
  w0 = 6.2831853071795862 * f0 / plugin->fs;
  f0 = std::sin(w0) / (2.0 * Q);
  // A = sqrt(db2mag(gain));
  A = coder::mpower(gain / 40.0);
  if (std::abs(gain) < 0.001) {
    plugin->filter_LMF.a0 = 1.0;
    plugin->filter_LMF.a1 = 0.0;
    plugin->filter_LMF.a2 = 0.0;
    plugin->filter_LMF.b0 = 1.0;
    plugin->filter_LMF.b1 = 0.0;
    plugin->filter_LMF.b2 = 0.0;
  } else if (coder::internal::c_strcmp(plugin->typeLMF)) {
    plugin->filter_LMF.a0 = f0 * A;
    plugin->filter_LMF.a1 = 0.0;
    plugin->filter_LMF.a2 = -f0 * A;
    plugin->filter_LMF.b0 = f0 + 1.0;
    plugin->filter_LMF.b1 = -2.0 * std::cos(w0);
    plugin->filter_LMF.b2 = 1.0 - f0;
  } else if (coder::internal::d_strcmp(plugin->typeLMF)) {
    filt_b1 = f0 * A;
    plugin->filter_LMF.a0 = filt_b1 + 1.0;
    filt_b2 = std::cos(w0);
    plugin->filter_LMF.a1 = -2.0 * filt_b2;
    plugin->filter_LMF.a2 = 1.0 - filt_b1;
    filt_b1 = f0 / A;
    plugin->filter_LMF.b0 = filt_b1 + 1.0;
    plugin->filter_LMF.b1 = -2.0 * filt_b2;
    plugin->filter_LMF.b2 = 1.0 - filt_b1;
  } else if (coder::internal::e_strcmp(plugin->typeLMF)) {
    plugin->filter_LMF.a0 = 1.0;
    filt_b1 = std::cos(w0);
    plugin->filter_LMF.a1 = -2.0 * filt_b1;
    plugin->filter_LMF.a2 = 1.0;
    plugin->filter_LMF.b0 = f0 + 1.0;
    plugin->filter_LMF.b1 = -2.0 * filt_b1;
    plugin->filter_LMF.b2 = 1.0 - f0;
  }
  f0 = plugin->hpfFreqSmoother.step();
  Q = plugin->hpfQSmoother.step();
  w0 = 6.2831853071795862 * f0 / plugin->fs;
  f0 = std::sin(w0) / (2.0 * Q);
  filt_b1 = std::cos(w0);
  filt_b2 = (filt_b1 + 1.0) / 2.0;
  plugin->filter_HPF.a0 = filt_b2;
  plugin->filter_HPF.a1 = -(filt_b1 + 1.0);
  plugin->filter_HPF.a2 = filt_b2;
  plugin->filter_HPF.b0 = f0 + 1.0;
  plugin->filter_HPF.b1 = -2.0 * filt_b1;
  plugin->filter_HPF.b2 = 1.0 - f0;
  f0 = plugin->lpfFreqSmoother.step();
  Q = plugin->lpfQSmoother.step();
  w0 = 6.2831853071795862 * f0 / plugin->fs;
  f0 = std::sin(w0) / (2.0 * Q);
  filt_b1 = std::cos(w0);
  filt_b2 = (1.0 - filt_b1) / 2.0;
  plugin->filter_LPF.a0 = filt_b2;
  plugin->filter_LPF.a1 = 1.0 - filt_b1;
  plugin->filter_LPF.a2 = filt_b2;
  plugin->filter_LPF.b0 = f0 + 1.0;
  plugin->filter_LPF.b1 = -2.0 * filt_b1;
  plugin->filter_LPF.b2 = 1.0 - f0;
  f0 = plugin->hsFreqSmoother.step();
  Q = plugin->hsQSmoother.step();
  gain = plugin->hsGainSmoother.step();
  w0 = 6.2831853071795862 * f0 / plugin->fs;
  // A = sqrt(db2mag(gain));
  A = coder::mpower(gain / 40.0);
  if (std::abs(gain) < 0.001) {
    plugin->filter_HS.a0 = 1.0;
    plugin->filter_HS.a1 = 0.0;
    plugin->filter_HS.a2 = 0.0;
    plugin->filter_HS.b0 = 1.0;
    plugin->filter_HS.b1 = 0.0;
    plugin->filter_HS.b2 = 0.0;
  } else {
    filt_b1 = std::cos(w0);
    filt_b2 = (A - 1.0) * filt_b1;
    gain = (A + 1.0) + filt_b2;
    f0 = 2.0 * std::sqrt(A) * (std::sin(w0) / (2.0 * Q));
    plugin->filter_HS.a0 = A * (gain + f0);
    filt_b1 *= A + 1.0;
    plugin->filter_HS.a1 = -2.0 * A * ((A - 1.0) + filt_b1);
    plugin->filter_HS.a2 = A * (gain - f0);
    filt_b2 = (A + 1.0) - filt_b2;
    plugin->filter_HS.b0 = filt_b2 + f0;
    plugin->filter_HS.b1 = 2.0 * ((A - 1.0) - filt_b1);
    plugin->filter_HS.b2 = filt_b2 - f0;
  }
  i = static_cast<int>(coder::internal::minimum(dv));
  for (int ch{0}; ch < i; ch++) {
    double filt_w[4];
    double w2;
    double wn;
    //  iterates over # of channels on the input
    //  creates pointer to channel
    filt_w[0] = plugin->filter_HS.w[0];
    filt_w[1] = plugin->filter_HS.w[1];
    filt_w[2] = plugin->filter_HS.w[2];
    filt_w[3] = plugin->filter_HS.w[3];
    f0 = plugin->filter_HS.a0;
    gain = plugin->filter_HS.a1;
    Q = plugin->filter_HS.a2;
    w0 = plugin->filter_HS.b0;
    filt_b1 = plugin->filter_HS.b1;
    filt_b2 = plugin->filter_HS.b2;
    //  Number of input samples
    //  Output vector of zeroes
    //  Filter coefficients
    //  Get initial state
    w1_tmp = ch << 1;
    A = filt_w[w1_tmp];
    w2 = filt_w[w1_tmp + 1];
    //  Difference equations
    for (int n{0}; n < loop_ub; n++) {
      //  Loop through each sample in x
      wn = (result[n + result.size(0) * ch] - filt_b1 / w0 * A) -
           filt_b2 / w0 * w2;
      x_data[n] = (f0 / w0 * wn + gain / w0 * A) + Q / w0 * w2;
      w2 = A;
      //  w[n-2] = w[n-1]
      A = wn;
      //  w[n-1] = w[n]
    }
    //  filt.w(:, ch) = [w1; w2];
    plugin->filter_HS.w[w1_tmp] = A;
    plugin->filter_HS.w[w1_tmp + 1] = w2;
    //  passes the filter object containing filter state and filter
    //  coeffiecients
    filt_w[0] = plugin->filter_HMF.w[0];
    filt_w[1] = plugin->filter_HMF.w[1];
    filt_w[2] = plugin->filter_HMF.w[2];
    filt_w[3] = plugin->filter_HMF.w[3];
    f0 = plugin->filter_HMF.a0;
    gain = plugin->filter_HMF.a1;
    Q = plugin->filter_HMF.a2;
    w0 = plugin->filter_HMF.b0;
    filt_b1 = plugin->filter_HMF.b1;
    filt_b2 = plugin->filter_HMF.b2;
    //  Number of input samples
    //  Output vector of zeroes
    //  Filter coefficients
    //  Get initial state
    A = filt_w[w1_tmp];
    w2 = filt_w[w1_tmp + 1];
    //  Difference equations
    for (int n{0}; n < loop_ub; n++) {
      //  Loop through each sample in x
      wn = (x_data[n] - filt_b1 / w0 * A) - filt_b2 / w0 * w2;
      b_x_data[n] = (f0 / w0 * wn + gain / w0 * A) + Q / w0 * w2;
      w2 = A;
      //  w[n-2] = w[n-1]
      A = wn;
      //  w[n-1] = w[n]
    }
    //  filt.w(:, ch) = [w1; w2];
    plugin->filter_HMF.w[w1_tmp] = A;
    plugin->filter_HMF.w[w1_tmp + 1] = w2;
    filt_w[0] = plugin->filter_LMF.w[0];
    filt_w[1] = plugin->filter_LMF.w[1];
    filt_w[2] = plugin->filter_LMF.w[2];
    filt_w[3] = plugin->filter_LMF.w[3];
    f0 = plugin->filter_LMF.a0;
    gain = plugin->filter_LMF.a1;
    Q = plugin->filter_LMF.a2;
    w0 = plugin->filter_LMF.b0;
    filt_b1 = plugin->filter_LMF.b1;
    filt_b2 = plugin->filter_LMF.b2;
    //  Number of input samples
    //  Output vector of zeroes
    //  Filter coefficients
    //  Get initial state
    A = filt_w[w1_tmp];
    w2 = filt_w[w1_tmp + 1];
    //  Difference equations
    for (int n{0}; n < loop_ub; n++) {
      //  Loop through each sample in x
      wn = (b_x_data[n] - filt_b1 / w0 * A) - filt_b2 / w0 * w2;
      c_x_data[n] = (f0 / w0 * wn + gain / w0 * A) + Q / w0 * w2;
      w2 = A;
      //  w[n-2] = w[n-1]
      A = wn;
      //  w[n-1] = w[n]
    }
    //  filt.w(:, ch) = [w1; w2];
    plugin->filter_LMF.w[w1_tmp] = A;
    plugin->filter_LMF.w[w1_tmp + 1] = w2;
    filt_w[0] = plugin->filter_HPF.w[0];
    filt_w[1] = plugin->filter_HPF.w[1];
    filt_w[2] = plugin->filter_HPF.w[2];
    filt_w[3] = plugin->filter_HPF.w[3];
    f0 = plugin->filter_HPF.a0;
    gain = plugin->filter_HPF.a1;
    Q = plugin->filter_HPF.a2;
    w0 = plugin->filter_HPF.b0;
    filt_b1 = plugin->filter_HPF.b1;
    filt_b2 = plugin->filter_HPF.b2;
    //  Number of input samples
    //  Output vector of zeroes
    //  Filter coefficients
    //  Get initial state
    A = filt_w[w1_tmp];
    w2 = filt_w[w1_tmp + 1];
    //  Difference equations
    for (int n{0}; n < loop_ub; n++) {
      //  Loop through each sample in x
      wn = (c_x_data[n] - filt_b1 / w0 * A) - filt_b2 / w0 * w2;
      d_x_data[n] = (f0 / w0 * wn + gain / w0 * A) + Q / w0 * w2;
      w2 = A;
      //  w[n-2] = w[n-1]
      A = wn;
      //  w[n-1] = w[n]
    }
    //  filt.w(:, ch) = [w1; w2];
    plugin->filter_HPF.w[w1_tmp] = A;
    plugin->filter_HPF.w[w1_tmp + 1] = w2;
    filt_w[0] = plugin->filter_LPF.w[0];
    filt_w[1] = plugin->filter_LPF.w[1];
    filt_w[2] = plugin->filter_LPF.w[2];
    filt_w[3] = plugin->filter_LPF.w[3];
    f0 = plugin->filter_LPF.a0;
    gain = plugin->filter_LPF.a1;
    Q = plugin->filter_LPF.a2;
    w0 = plugin->filter_LPF.b0;
    filt_b1 = plugin->filter_LPF.b1;
    filt_b2 = plugin->filter_LPF.b2;
    //  Number of input samples
    //  Output vector of zeroes
    //  Filter coefficients
    //  Get initial state
    A = filt_w[w1_tmp];
    w2 = filt_w[w1_tmp + 1];
    //  Difference equations
    for (int n{0}; n < loop_ub; n++) {
      //  Loop through each sample in x
      wn = (d_x_data[n] - filt_b1 / w0 * A) - filt_b2 / w0 * w2;
      e_x_data[n] = (f0 / w0 * wn + gain / w0 * A) + Q / w0 * w2;
      w2 = A;
      //  w[n-2] = w[n-1]
      A = wn;
      //  w[n-1] = w[n]
    }
    //  filt.w(:, ch) = [w1; w2];
    plugin->filter_LPF.w[w1_tmp] = A;
    plugin->filter_LPF.w[w1_tmp + 1] = w2;
    if (coder::internal::b_strcmp(plugin->BYPASS_BIQUAD)) {
      for (w1_tmp = 0; w1_tmp < b_loop_ub; w1_tmp++) {
        out1[w1_tmp + out1.size(0) * ch] = result[w1_tmp + result.size(0) * ch];
      }
    } else {
      for (w1_tmp = 0; w1_tmp < b_loop_ub; w1_tmp++) {
        out1[w1_tmp + out1.size(0) * ch] = e_x_data[w1_tmp];
      }
    }
  }
  for (i = 0; i < 2; i++) {
    for (w1_tmp = 0; w1_tmp < b_loop_ub; w1_tmp++) {
      t1[w1_tmp + t1.size(0) * i] = out1[w1_tmp + out1.size(0) * i];
    }
  }
  if (samplesPerFrame < 1.0) {
    w1_tmp = 0;
  } else {
    w1_tmp = static_cast<int>(samplesPerFrame);
  }
  o1_size[0] = w1_tmp;
  for (i = 0; i < w1_tmp; i++) {
    o1_data[i] = t1[i];
  }
  o2_size[0] = w1_tmp;
  for (i = 0; i < w1_tmp; i++) {
    o2_data[i] = t1[i + t1.size(0)];
  }
}

void resetCImpl(biquadStackData *SD, double rate)
{
  derivedAudioPlugin *plugin;
  double b_rate;
  plugin = getPluginInstance(SD);
  plugin->PrivateSampleRate = rate;
  b_rate = plugin->PrivateSampleRate;
  plugin->fs = b_rate;
  plugin->filter_HS.w[0] = 0.0;
  plugin->filter_HMF.w[0] = 0.0;
  plugin->filter_LMF.w[0] = 0.0;
  plugin->filter_HPF.w[0] = 0.0;
  plugin->filter_LPF.w[0] = 0.0;
  plugin->filter_HS.w[1] = 0.0;
  plugin->filter_HMF.w[1] = 0.0;
  plugin->filter_LMF.w[1] = 0.0;
  plugin->filter_HPF.w[1] = 0.0;
  plugin->filter_LPF.w[1] = 0.0;
  plugin->filter_HS.w[2] = 0.0;
  plugin->filter_HMF.w[2] = 0.0;
  plugin->filter_LMF.w[2] = 0.0;
  plugin->filter_HPF.w[2] = 0.0;
  plugin->filter_LPF.w[2] = 0.0;
  plugin->filter_HS.w[3] = 0.0;
  plugin->filter_HMF.w[3] = 0.0;
  plugin->filter_LMF.w[3] = 0.0;
  plugin->filter_HPF.w[3] = 0.0;
  plugin->filter_LPF.w[3] = 0.0;
}

// End of code generation (biquad.cpp)
