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

// Function Declarations
namespace coder {
namespace internal {
static boolean_T b_strcmp(const array<char, 2U> &a);

static boolean_T c_strcmp(const array<char, 2U> &a);

static boolean_T d_strcmp(const array<char, 2U> &a);

static double minimum(const double x[2]);

} // namespace internal
} // namespace coder
static derivedAudioPlugin *getPluginInstance(biquadStackData *SD);

static void getPluginInstance_delete(biquadStackData *SD);

static void getPluginInstance_init(biquadStackData *SD);

static void minus(coder::array<double, 2U> &in1,
                  const coder::array<double, 2U> &in2);

static double rt_powd_snf(double u0, double u1);

// Function Definitions
namespace coder {
void compressor::setupTimingParameters()
{
  double Fs;
  Fs = pSampleRateDialog;
  if (AttackTime != 0.0) {
    pAlphaA = std::exp(-2.1972245773362196 / (AttackTime * Fs));
  } else {
    pAlphaA = 0.0;
  }
  if (ReleaseTime != 0.0) {
    pAlphaR = std::exp(-2.1972245773362196 / (ReleaseTime * Fs));
  } else {
    pAlphaR = 0.0;
  }
}

void compressor::step(const array<double, 2U> &varargin_1,
                      array<double, 2U> &varargout_1)
{
  array<double, 2U> G;
  array<double, 2U> b;
  array<double, 2U> y;
  array<double, 2U> yG;
  double R;
  double T;
  double W;
  double alphaR;
  int acoef;
  int bcoef;
  int i;
  int k;
  int loop_ub;
  short inSize[8];
  boolean_T exitg1;
  if (isInitialized != 1) {
    isSetupComplete = false;
    isInitialized = 1;
    inputVarSize[0].f1[0] = static_cast<unsigned int>(varargin_1.size(0));
    inputVarSize[0].f1[1] = 2U;
    for (i = 0; i < 6; i++) {
      inputVarSize[0].f1[i + 2] = 1U;
    }
    setupTimingParameters();
    pNumChannels = 2.0;
    pMakeUpGain = MakeUpGain;
    isSetupComplete = true;
    TunablePropsChanged = false;
    pLevelDetectionState[0] = 0.0;
    pLevelDetectionState[1] = 0.0;
    setupTimingParameters();
  }
  if (TunablePropsChanged) {
    TunablePropsChanged = false;
    setupTimingParameters();
    pMakeUpGain = MakeUpGain;
  }
  inSize[0] = static_cast<short>(varargin_1.size(0));
  inSize[1] = 2;
  for (i = 0; i < 6; i++) {
    inSize[i + 2] = 1;
  }
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k < 8)) {
    if (inputVarSize[0].f1[k] != static_cast<unsigned int>(inSize[k])) {
      for (i = 0; i < 8; i++) {
        inputVarSize[0].f1[i] = static_cast<unsigned int>(inSize[i]);
      }
      exitg1 = true;
    } else {
      k++;
    }
  }
  loop_ub = varargin_1.size(0) << 1;
  G.set_size(varargin_1.size(0), 2);
  for (k = 0; k < loop_ub; k++) {
    G[k] = std::abs(varargin_1[k]);
  }
  G.set_size(G.size(0), 2);
  for (i = 0; i < loop_ub; i++) {
    R = G[i];
    G[i] = std::fmax(R, 2.2204460492503131E-16);
  }
  for (k = 0; k < loop_ub; k++) {
    G[k] = std::log10(G[k]);
  }
  G.set_size(G.size(0), 2);
  for (i = 0; i < loop_ub; i++) {
    G[i] = 20.0 * G[i];
  }
  W = KneeWidth;
  R = Ratio;
  T = Threshold;
  yG.set_size(G.size(0), 2);
  for (i = 0; i < loop_ub; i++) {
    yG[i] = G[i];
  }
  acoef = loop_ub - 1;
  for (bcoef = 0; bcoef <= acoef; bcoef++) {
    alphaR = G[bcoef] - T;
    if (2.0 * alphaR > W) {
      yG[bcoef] = T + alphaR / R;
    }
  }
  if (W != 0.0) {
    b.set_size(G.size(0), 2);
    for (k = 0; k < loop_ub; k++) {
      b[k] = std::abs(G[k] - T);
    }
    alphaR = 1.0 / R - 1.0;
    for (bcoef = 0; bcoef <= acoef; bcoef++) {
      if (2.0 * b[bcoef] <= W) {
        R = (G[bcoef] - T) + W / 2.0;
        yG[bcoef] = G[bcoef] + alphaR * (R * R) / (2.0 * W);
      }
    }
  }
  if (yG.size(0) == G.size(0)) {
    yG.set_size(yG.size(0), 2);
    for (i = 0; i < loop_ub; i++) {
      yG[i] = yG[i] - G[i];
    }
  } else {
    minus(yG, G);
  }
  y.set_size(yG.size(0) + 1, 2);
  loop_ub = (yG.size(0) + 1) << 1;
  for (i = 0; i < loop_ub; i++) {
    y[i] = 0.0;
  }
  y[0] = pLevelDetectionState[0];
  y[y.size(0)] = pLevelDetectionState[1];
  R = pAlphaA;
  alphaR = pAlphaR;
  i = yG.size(0);
  for (bcoef = 0; bcoef < i; bcoef++) {
    if (yG[bcoef] <= y[bcoef]) {
      y[bcoef + 1] = R * y[bcoef] + (1.0 - R) * yG[bcoef];
    } else {
      y[bcoef + 1] = alphaR * y[bcoef] + (1.0 - alphaR) * yG[bcoef];
    }
    if (yG[bcoef + yG.size(0)] <= y[bcoef + y.size(0)]) {
      y[(bcoef + y.size(0)) + 1] =
          R * y[bcoef + y.size(0)] + (1.0 - R) * yG[bcoef + yG.size(0)];
    } else {
      y[(bcoef + y.size(0)) + 1] = alphaR * y[bcoef + y.size(0)] +
                                   (1.0 - alphaR) * yG[bcoef + yG.size(0)];
    }
  }
  G.set_size(yG.size(0), 2);
  acoef = yG.size(0) << 1;
  for (i = 0; i < acoef; i++) {
    G[i] = 0.0;
  }
  i = (y.size(0) >= 2);
  loop_ub = yG.size(0);
  for (bcoef = 0; bcoef < 2; bcoef++) {
    for (k = 0; k < loop_ub; k++) {
      G[k + G.size(0) * bcoef] = y[(i + k) + y.size(0) * bcoef];
    }
    pLevelDetectionState[bcoef] = y[(y.size(0) + y.size(0) * bcoef) - 1];
  }
  G.set_size(G.size(0), 2);
  for (i = 0; i < acoef; i++) {
    G[i] = G[i] + pMakeUpGain;
  }
  G.set_size(G.size(0), 2);
  for (i = 0; i < acoef; i++) {
    R = G[i] / 20.0;
    G[i] = rt_powd_snf(10.0, R);
  }
  if (G.size(0) == 1) {
    i = static_cast<short>(varargin_1.size(0));
  } else if (varargin_1.size(0) == 1) {
    i = static_cast<short>(G.size(0));
  } else if (varargin_1.size(0) == G.size(0)) {
    i = static_cast<short>(varargin_1.size(0));
  } else if (G.size(0) < varargin_1.size(0)) {
    i = static_cast<short>(G.size(0));
  } else {
    i = static_cast<short>(varargin_1.size(0));
  }
  varargout_1.set_size(i, 2);
  if (i != 0) {
    acoef = (varargin_1.size(0) != 1);
    bcoef = (G.size(0) != 1);
    for (k = 0; k < 2; k++) {
      i = varargout_1.size(0) - 1;
      for (loop_ub = 0; loop_ub <= i; loop_ub++) {
        varargout_1[loop_ub + varargout_1.size(0) * k] =
            varargin_1[acoef * loop_ub + varargin_1.size(0) * k] *
            G[bcoef * loop_ub + G.size(0) * k];
      }
    }
  }
}

namespace internal {
static boolean_T b_strcmp(const array<char, 2U> &a)
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

static boolean_T c_strcmp(const array<char, 2U> &a)
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

static boolean_T d_strcmp(const array<char, 2U> &a)
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
  if ((x[0] > x[1]) || (std::isnan(x[0]) && (!std::isnan(x[1])))) {
    ex = x[1];
  } else {
    ex = x[0];
  }
  return ex;
}

} // namespace internal
} // namespace coder
static derivedAudioPlugin *getPluginInstance(biquadStackData *SD)
{
  coder::compressor *obj_tmp;
  if (!SD->pd->plugin_not_empty) {
    double initialValue;
    boolean_T flag;
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
    SD->pd->plugin.BYPASS_BIQUAD.set_size(1, 2);
    SD->pd->plugin.GAIN_DB = 0.0;
    SD->pd->plugin.ATTACK = 10.0;
    SD->pd->plugin.RELEASE = 50.0;
    SD->pd->plugin.RATIO = 2.0;
    SD->pd->plugin.THRESHOLD = -10.0;
    SD->pd->plugin.BYPASS_COMPRESSOR.set_size(1, 2);
    SD->pd->plugin.BYPASS_BIQUAD[0] = 'o';
    SD->pd->plugin.BYPASS_COMPRESSOR[0] = 'o';
    SD->pd->plugin.BYPASS_BIQUAD[1] = 'n';
    SD->pd->plugin.BYPASS_COMPRESSOR[1] = 'n';
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
    SD->pd->plugin.PrivateLatency = 0;
    //  Initialize smoothers with default values
    initialValue = SD->pd->plugin.HS_FREQ;
    SD->pd->plugin.hsFreqSmoother.isInitialized = 0;
    //  constructor
    SD->pd->plugin.hsFreqSmoother.currentValue = initialValue;
    //  gradually updated each time the audio frame is processed
    SD->pd->plugin.hsFreqSmoother.targetValue = initialValue;
    //  will incrementally adjust currentValue towards targetValue
    SD->pd->plugin.hsFreqSmoother.smoothingFactor = 0.9;
    //  rate at which the currentValue approaches the targetValue
    initialValue = SD->pd->plugin.HMF_FREQ;
    SD->pd->plugin.hmfFreqSmoother.isInitialized = 0;
    //  constructor
    SD->pd->plugin.hmfFreqSmoother.currentValue = initialValue;
    //  gradually updated each time the audio frame is processed
    SD->pd->plugin.hmfFreqSmoother.targetValue = initialValue;
    //  will incrementally adjust currentValue towards targetValue
    SD->pd->plugin.hmfFreqSmoother.smoothingFactor = 0.9;
    //  rate at which the currentValue approaches the targetValue
    initialValue = SD->pd->plugin.LMF_FREQ;
    SD->pd->plugin.lmfFreqSmoother.isInitialized = 0;
    //  constructor
    SD->pd->plugin.lmfFreqSmoother.currentValue = initialValue;
    //  gradually updated each time the audio frame is processed
    SD->pd->plugin.lmfFreqSmoother.targetValue = initialValue;
    //  will incrementally adjust currentValue towards targetValue
    SD->pd->plugin.lmfFreqSmoother.smoothingFactor = 0.9;
    //  rate at which the currentValue approaches the targetValue
    initialValue = SD->pd->plugin.HPF_FREQ;
    SD->pd->plugin.hpfFreqSmoother.isInitialized = 0;
    //  constructor
    SD->pd->plugin.hpfFreqSmoother.currentValue = initialValue;
    //  gradually updated each time the audio frame is processed
    SD->pd->plugin.hpfFreqSmoother.targetValue = initialValue;
    //  will incrementally adjust currentValue towards targetValue
    SD->pd->plugin.hpfFreqSmoother.smoothingFactor = 0.9;
    //  rate at which the currentValue approaches the targetValue
    initialValue = SD->pd->plugin.LPF_FREQ;
    SD->pd->plugin.lpfFreqSmoother.isInitialized = 0;
    //  constructor
    SD->pd->plugin.lpfFreqSmoother.currentValue = initialValue;
    //  gradually updated each time the audio frame is processed
    SD->pd->plugin.lpfFreqSmoother.targetValue = initialValue;
    //  will incrementally adjust currentValue towards targetValue
    SD->pd->plugin.lpfFreqSmoother.smoothingFactor = 0.9;
    //  rate at which the currentValue approaches the targetValue
    initialValue = SD->pd->plugin.HS_GAIN;
    SD->pd->plugin.hsGainSmoother.isInitialized = 0;
    //  constructor
    SD->pd->plugin.hsGainSmoother.currentValue = initialValue;
    //  gradually updated each time the audio frame is processed
    SD->pd->plugin.hsGainSmoother.targetValue = initialValue;
    //  will incrementally adjust currentValue towards targetValue
    SD->pd->plugin.hsGainSmoother.smoothingFactor = 0.9;
    //  rate at which the currentValue approaches the targetValue
    initialValue = SD->pd->plugin.HMF_GAIN;
    SD->pd->plugin.hmfGainSmoother.isInitialized = 0;
    //  constructor
    SD->pd->plugin.hmfGainSmoother.currentValue = initialValue;
    //  gradually updated each time the audio frame is processed
    SD->pd->plugin.hmfGainSmoother.targetValue = initialValue;
    //  will incrementally adjust currentValue towards targetValue
    SD->pd->plugin.hmfGainSmoother.smoothingFactor = 0.9;
    //  rate at which the currentValue approaches the targetValue
    SD->pd->plugin.lmfGainSmoother.isInitialized = 0;
    //  constructor
    //  gradually updated each time the audio frame is processed
    //  will incrementally adjust currentValue towards targetValue
    //  rate at which the currentValue approaches the targetValue
    initialValue = SD->pd->plugin.HS_Q;
    SD->pd->plugin.hsQSmoother.isInitialized = 0;
    //  constructor
    SD->pd->plugin.hsQSmoother.currentValue = initialValue;
    //  gradually updated each time the audio frame is processed
    SD->pd->plugin.hsQSmoother.targetValue = initialValue;
    //  will incrementally adjust currentValue towards targetValue
    SD->pd->plugin.hsQSmoother.smoothingFactor = 0.9;
    //  rate at which the currentValue approaches the targetValue
    initialValue = SD->pd->plugin.HMF_Q;
    SD->pd->plugin.hmfQSmoother.isInitialized = 0;
    //  constructor
    SD->pd->plugin.hmfQSmoother.currentValue = initialValue;
    //  gradually updated each time the audio frame is processed
    SD->pd->plugin.hmfQSmoother.targetValue = initialValue;
    //  will incrementally adjust currentValue towards targetValue
    SD->pd->plugin.hmfQSmoother.smoothingFactor = 0.9;
    //  rate at which the currentValue approaches the targetValue
    initialValue = SD->pd->plugin.LMF_Q;
    SD->pd->plugin.lmfQSmoother.isInitialized = 0;
    //  constructor
    SD->pd->plugin.lmfQSmoother.currentValue = initialValue;
    //  gradually updated each time the audio frame is processed
    SD->pd->plugin.lmfQSmoother.targetValue = initialValue;
    //  will incrementally adjust currentValue towards targetValue
    SD->pd->plugin.lmfQSmoother.smoothingFactor = 0.9;
    //  rate at which the currentValue approaches the targetValue
    initialValue = SD->pd->plugin.HPF_Q;
    SD->pd->plugin.hpfQSmoother.isInitialized = 0;
    //  constructor
    SD->pd->plugin.hpfQSmoother.currentValue = initialValue;
    //  gradually updated each time the audio frame is processed
    SD->pd->plugin.hpfQSmoother.targetValue = initialValue;
    //  will incrementally adjust currentValue towards targetValue
    SD->pd->plugin.hpfQSmoother.smoothingFactor = 0.9;
    //  rate at which the currentValue approaches the targetValue
    initialValue = SD->pd->plugin.LPF_Q;
    SD->pd->plugin.lpfQSmoother.isInitialized = 0;
    //  constructor
    SD->pd->plugin.lpfQSmoother.currentValue = initialValue;
    //  gradually updated each time the audio frame is processed
    SD->pd->plugin.lpfQSmoother.targetValue = initialValue;
    //  will incrementally adjust currentValue towards targetValue
    SD->pd->plugin.lpfQSmoother.smoothingFactor = 0.9;
    //  rate at which the currentValue approaches the targetValue
    SD->pd->plugin.b_compressor.KneeWidth = 0.0;
    SD->pd->plugin.b_compressor.MakeUpGain = 0.0;
    SD->pd->plugin.b_compressor.pSampleRateDialog = 44100.0;
    SD->pd->plugin.b_compressor.pNumChannels = -1.0;
    SD->pd->plugin.b_compressor.isInitialized = 0;
    SD->pd->plugin.b_compressor.matlabCodegenIsDeleted = false;
    flag = (SD->pd->plugin.b_compressor.isInitialized == 1);
    if (flag) {
      SD->pd->plugin.b_compressor.TunablePropsChanged = true;
    }
    initialValue = SD->pd->plugin.THRESHOLD;
    SD->pd->plugin.b_compressor.Threshold = initialValue;
    flag = (SD->pd->plugin.b_compressor.isInitialized == 1);
    if (flag) {
      SD->pd->plugin.b_compressor.TunablePropsChanged = true;
    }
    obj_tmp = &SD->pd->plugin.b_compressor;
    initialValue = SD->pd->plugin.RATIO;
    obj_tmp->Ratio = initialValue;
    flag = (SD->pd->plugin.b_compressor.isInitialized == 1);
    if (flag) {
      SD->pd->plugin.b_compressor.TunablePropsChanged = true;
    }
    initialValue = SD->pd->plugin.ATTACK / 1000.0;
    obj_tmp->AttackTime = initialValue;
    flag = (SD->pd->plugin.b_compressor.isInitialized == 1);
    if (flag) {
      SD->pd->plugin.b_compressor.TunablePropsChanged = true;
    }
    initialValue = SD->pd->plugin.RELEASE / 1000.0;
    obj_tmp->ReleaseTime = initialValue;
    SD->pd->plugin.matlabCodegenIsDeleted = false;
    SD->pd->plugin_not_empty = true;
  }
  return &SD->pd->plugin;
}

static void getPluginInstance_delete(biquadStackData *SD)
{
  coder::compressor *obj;
  if (!SD->pd->plugin.matlabCodegenIsDeleted) {
    SD->pd->plugin.matlabCodegenIsDeleted = true;
  }
  obj = &SD->pd->plugin.b_compressor;
  if (!obj->matlabCodegenIsDeleted) {
    obj->matlabCodegenIsDeleted = true;
    if (obj->isInitialized == 1) {
      obj->isInitialized = 2;
      if (obj->isSetupComplete) {
        obj->pNumChannels = -1.0;
      }
    }
  }
}

static void getPluginInstance_init(biquadStackData *SD)
{
  SD->pd->plugin.b_compressor.matlabCodegenIsDeleted = true;
  SD->pd->plugin.matlabCodegenIsDeleted = true;
  SD->pd->plugin_not_empty = false;
}

static void minus(coder::array<double, 2U> &in1,
                  const coder::array<double, 2U> &in2)
{
  coder::array<double, 2U> b_in1;
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  if (in2.size(0) == 1) {
    loop_ub = in1.size(0);
  } else {
    loop_ub = in2.size(0);
  }
  b_in1.set_size(loop_ub, 2);
  stride_0_0 = (in1.size(0) != 1);
  stride_1_0 = (in2.size(0) != 1);
  for (int i{0}; i < 2; i++) {
    for (int i1{0}; i1 < loop_ub; i1++) {
      b_in1[i1 + b_in1.size(0) * i] = in1[i1 * stride_0_0 + in1.size(0) * i] -
                                      in2[i1 * stride_1_0 + in2.size(0) * i];
    }
  }
  in1.set_size(b_in1.size(0), 2);
  loop_ub = b_in1.size(0);
  for (int i{0}; i < 2; i++) {
    for (int i1{0}; i1 < loop_ub; i1++) {
      in1[i1 + in1.size(0) * i] = b_in1[i1 + b_in1.size(0) * i];
    }
  }
}

static double rt_powd_snf(double u0, double u1)
{
  double y;
  if (std::isnan(u0) || std::isnan(u1)) {
    y = rtNaN;
  } else {
    double d;
    double d1;
    d = std::abs(u0);
    d1 = std::abs(u1);
    if (std::isinf(u1)) {
      if (d == 1.0) {
        y = 1.0;
      } else if (d > 1.0) {
        if (u1 > 0.0) {
          y = rtInf;
        } else {
          y = 0.0;
        }
      } else if (u1 > 0.0) {
        y = 0.0;
      } else {
        y = rtInf;
      }
    } else if (d1 == 0.0) {
      y = 1.0;
    } else if (d1 == 1.0) {
      if (u1 > 0.0) {
        y = u0;
      } else {
        y = 1.0 / u0;
      }
    } else if (u1 == 2.0) {
      y = u0 * u0;
    } else if ((u1 == 0.5) && (u0 >= 0.0)) {
      y = std::sqrt(u0);
    } else if ((u0 < 0.0) && (u1 > std::floor(u1))) {
      y = rtNaN;
    } else {
      y = std::pow(u0, u1);
    }
  }
  return y;
}

ParameterSmoother::ParameterSmoother() = default;

ParameterSmoother::~ParameterSmoother() = default;

b_ParameterSmoother::b_ParameterSmoother() = default;

b_ParameterSmoother::~b_ParameterSmoother() = default;

namespace coder {
compressor::compressor() = default;

compressor::~compressor() = default;

} // namespace coder
derivedAudioPlugin::derivedAudioPlugin() = default;

derivedAudioPlugin::~derivedAudioPlugin() = default;

void biquad_initialize(biquadStackData *SD)
{
  getPluginInstance_init(SD);
}

void biquad_terminate(biquadStackData *SD)
{
  getPluginInstance_delete(SD);
}

void createPluginInstance(biquadStackData *SD, unsigned long)
{
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
    plugin->GAIN_DB = b_value;
    break;
  case 1: {
    double c_value;
    boolean_T flag;
    plugin->ATTACK = b_value;
    flag = (plugin->b_compressor.isInitialized == 1);
    if (flag) {
      plugin->b_compressor.TunablePropsChanged = true;
    }
    c_value = plugin->THRESHOLD;
    plugin->b_compressor.Threshold = c_value;
    flag = (plugin->b_compressor.isInitialized == 1);
    if (flag) {
      plugin->b_compressor.TunablePropsChanged = true;
    }
    c_value = plugin->RATIO;
    plugin->b_compressor.Ratio = c_value;
    flag = (plugin->b_compressor.isInitialized == 1);
    if (flag) {
      plugin->b_compressor.TunablePropsChanged = true;
    }
    c_value = plugin->ATTACK / 1000.0;
    plugin->b_compressor.AttackTime = c_value;
    flag = (plugin->b_compressor.isInitialized == 1);
    if (flag) {
      plugin->b_compressor.TunablePropsChanged = true;
    }
    c_value = plugin->RELEASE / 1000.0;
    plugin->b_compressor.ReleaseTime = c_value;
  } break;
  case 2: {
    double c_value;
    boolean_T flag;
    plugin->RELEASE = b_value;
    flag = (plugin->b_compressor.isInitialized == 1);
    if (flag) {
      plugin->b_compressor.TunablePropsChanged = true;
    }
    c_value = plugin->THRESHOLD;
    plugin->b_compressor.Threshold = c_value;
    flag = (plugin->b_compressor.isInitialized == 1);
    if (flag) {
      plugin->b_compressor.TunablePropsChanged = true;
    }
    c_value = plugin->RATIO;
    plugin->b_compressor.Ratio = c_value;
    flag = (plugin->b_compressor.isInitialized == 1);
    if (flag) {
      plugin->b_compressor.TunablePropsChanged = true;
    }
    c_value = plugin->ATTACK / 1000.0;
    plugin->b_compressor.AttackTime = c_value;
    flag = (plugin->b_compressor.isInitialized == 1);
    if (flag) {
      plugin->b_compressor.TunablePropsChanged = true;
    }
    c_value = plugin->RELEASE / 1000.0;
    plugin->b_compressor.ReleaseTime = c_value;
  } break;
  case 3: {
    double c_value;
    boolean_T flag;
    plugin->THRESHOLD = b_value;
    flag = (plugin->b_compressor.isInitialized == 1);
    if (flag) {
      plugin->b_compressor.TunablePropsChanged = true;
    }
    c_value = plugin->THRESHOLD;
    plugin->b_compressor.Threshold = c_value;
    flag = (plugin->b_compressor.isInitialized == 1);
    if (flag) {
      plugin->b_compressor.TunablePropsChanged = true;
    }
    c_value = plugin->RATIO;
    plugin->b_compressor.Ratio = c_value;
    flag = (plugin->b_compressor.isInitialized == 1);
    if (flag) {
      plugin->b_compressor.TunablePropsChanged = true;
    }
    c_value = plugin->ATTACK / 1000.0;
    plugin->b_compressor.AttackTime = c_value;
    flag = (plugin->b_compressor.isInitialized == 1);
    if (flag) {
      plugin->b_compressor.TunablePropsChanged = true;
    }
    c_value = plugin->RELEASE / 1000.0;
    plugin->b_compressor.ReleaseTime = c_value;
  } break;
  case 4: {
    double c_value;
    boolean_T flag;
    plugin->RATIO = b_value;
    flag = (plugin->b_compressor.isInitialized == 1);
    if (flag) {
      plugin->b_compressor.TunablePropsChanged = true;
    }
    c_value = plugin->THRESHOLD;
    plugin->b_compressor.Threshold = c_value;
    flag = (plugin->b_compressor.isInitialized == 1);
    if (flag) {
      plugin->b_compressor.TunablePropsChanged = true;
    }
    c_value = plugin->RATIO;
    plugin->b_compressor.Ratio = c_value;
    flag = (plugin->b_compressor.isInitialized == 1);
    if (flag) {
      plugin->b_compressor.TunablePropsChanged = true;
    }
    c_value = plugin->ATTACK / 1000.0;
    plugin->b_compressor.AttackTime = c_value;
    flag = (plugin->b_compressor.isInitialized == 1);
    if (flag) {
      plugin->b_compressor.TunablePropsChanged = true;
    }
    c_value = plugin->RELEASE / 1000.0;
    plugin->b_compressor.ReleaseTime = c_value;
  } break;
  case 5:
    switch (static_cast<int>(b_value)) {
    case 0:
      plugin->BYPASS_COMPRESSOR.set_size(1, 3);
      plugin->BYPASS_COMPRESSOR[0] = 'o';
      plugin->BYPASS_COMPRESSOR[1] = 'f';
      plugin->BYPASS_COMPRESSOR[2] = 'f';
      break;
    case 1:
      plugin->BYPASS_COMPRESSOR.set_size(1, 2);
      plugin->BYPASS_COMPRESSOR[0] = 'o';
      plugin->BYPASS_COMPRESSOR[1] = 'n';
      break;
    }
    break;
  case 6:
    plugin->HS_FREQ = b_value;
    //  setter
    plugin->hsFreqSmoother.targetValue = b_value;
    break;
  case 7:
    plugin->HS_Q = b_value;
    //  setter
    plugin->hsQSmoother.targetValue = b_value;
    break;
  case 8:
    plugin->HS_GAIN = b_value;
    //  setter
    plugin->hsGainSmoother.targetValue = b_value;
    break;
  case 9:
    plugin->HMF_FREQ = b_value;
    //  setter
    plugin->hmfFreqSmoother.targetValue = b_value;
    break;
  case 10:
    plugin->HMF_Q = b_value;
    //  setter
    plugin->hmfQSmoother.targetValue = b_value;
    break;
  case 11:
    plugin->HMF_GAIN = b_value;
    //  setter
    plugin->hmfGainSmoother.targetValue = b_value;
    break;
  case 12:
    plugin->LMF_FREQ = b_value;
    //  setter
    plugin->lmfFreqSmoother.targetValue = b_value;
    break;
  case 13:
    plugin->LMF_Q = b_value;
    //  setter
    plugin->lmfQSmoother.targetValue = b_value;
    break;
  case 14:
    plugin->LMF_GAIN = b_value;
    //  setter
    break;
  case 15:
    plugin->HPF_FREQ = b_value;
    //  setter
    plugin->hpfFreqSmoother.targetValue = b_value;
    break;
  case 16:
    plugin->HPF_Q = b_value;
    //  setter
    plugin->hpfQSmoother.targetValue = b_value;
    break;
  case 17:
    plugin->LPF_FREQ = b_value;
    //  setter
    plugin->lpfFreqSmoother.targetValue = b_value;
    break;
  case 18:
    plugin->LPF_Q = b_value;
    //  setter
    plugin->lpfQSmoother.targetValue = b_value;
    break;
  case 19:
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
  case 20:
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
  case 21:
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
  static const char cv[3]{'o', 'f', 'f'};
  derivedAudioPlugin *plugin;
  coder::array<double, 2U> out1;
  coder::array<double, 2U> out2;
  coder::array<double, 2U> result;
  coder::array<double, 2U> t1;
  coder::array<char, 2U> a;
  double b_x_data[4096];
  double c_x_data[4096];
  double d_x_data[4096];
  double e_x_data[4096];
  double x_data[4096];
  double b_result[2];
  double A;
  double Q;
  double f0;
  double filt_b2;
  double gain;
  double w0;
  double w1;
  double ydb;
  int exitg1;
  int i;
  int i1;
  int loop_ub;
  boolean_T b_bool;
  plugin = getPluginInstance(SD);
  result.set_size(i1_size[0], 2);
  loop_ub = i1_size[0];
  for (i = 0; i < loop_ub; i++) {
    result[i] = i1_data[i];
  }
  loop_ub = i2_size[0];
  for (i = 0; i < loop_ub; i++) {
    result[i + result.size(0)] = i2_data[i];
  }
  out1.set_size(result.size(0), 2);
  out2.set_size(result.size(0), 2);
  t1.set_size(result.size(0), 2);
  f0 = plugin->GAIN_DB / 20.0;
  gain = rt_powd_snf(10.0, f0);
  //  Smooth values
  if (plugin->hmfQSmoother.isInitialized != 1) {
    plugin->hmfQSmoother.isInitialized = 1;
  }
  //  used to update parameter value incrementally each time the audio frame is
  //  processed Perform the smoothing
  plugin->hmfQSmoother.currentValue =
      plugin->hmfQSmoother.smoothingFactor * plugin->hmfQSmoother.currentValue +
      (1.0 - plugin->hmfQSmoother.smoothingFactor) *
          plugin->hmfQSmoother.targetValue;
  //  larger smooth val = slower ramp, smaller smooth val = faster ramp
  Q = plugin->hmfQSmoother.currentValue;
  if (plugin->hmfFreqSmoother.isInitialized != 1) {
    plugin->hmfFreqSmoother.isInitialized = 1;
  }
  //  used to update parameter value incrementally each time the audio frame is
  //  processed Perform the smoothing
  plugin->hmfFreqSmoother.currentValue =
      plugin->hmfFreqSmoother.smoothingFactor *
          plugin->hmfFreqSmoother.currentValue +
      (1.0 - plugin->hmfFreqSmoother.smoothingFactor) *
          plugin->hmfFreqSmoother.targetValue;
  //  larger smooth val = slower ramp, smaller smooth val = faster ramp
  f0 = plugin->hmfFreqSmoother.currentValue;
  if (plugin->hmfGainSmoother.isInitialized != 1) {
    plugin->hmfGainSmoother.isInitialized = 1;
  }
  //  used to update parameter value incrementally each time the audio frame is
  //  processed Perform the smoothing
  plugin->hmfGainSmoother.currentValue =
      plugin->hmfGainSmoother.smoothingFactor *
          plugin->hmfGainSmoother.currentValue +
      (1.0 - plugin->hmfGainSmoother.smoothingFactor) *
          plugin->hmfGainSmoother.targetValue;
  //  larger smooth val = slower ramp, smaller smooth val = faster ramp
  ydb = plugin->hmfGainSmoother.currentValue;
  w0 = 6.2831853071795862 * f0 / plugin->fs;
  f0 = std::sin(w0) / (2.0 * Q);
  A = std::sqrt(rt_powd_snf(10.0, ydb / 20.0));
  if (coder::internal::b_strcmp(plugin->typeHMF)) {
    plugin->filter_HMF.a0 = f0 * A;
    plugin->filter_HMF.a1 = 0.0;
    plugin->filter_HMF.a2 = -f0 * A;
    plugin->filter_HMF.b0 = f0 + 1.0;
    plugin->filter_HMF.b1 = -2.0 * std::cos(w0);
    plugin->filter_HMF.b2 = 1.0 - f0;
  } else if (coder::internal::c_strcmp(plugin->typeHMF)) {
    filt_b2 = f0 * A;
    plugin->filter_HMF.a0 = filt_b2 + 1.0;
    w1 = -2.0 * std::cos(w0);
    plugin->filter_HMF.a1 = w1;
    plugin->filter_HMF.a2 = 1.0 - filt_b2;
    filt_b2 = f0 / A;
    plugin->filter_HMF.b0 = filt_b2 + 1.0;
    plugin->filter_HMF.b1 = w1;
    plugin->filter_HMF.b2 = 1.0 - filt_b2;
  } else if (coder::internal::d_strcmp(plugin->typeHMF)) {
    plugin->filter_HMF.a0 = 1.0;
    filt_b2 = -2.0 * std::cos(w0);
    plugin->filter_HMF.a1 = filt_b2;
    plugin->filter_HMF.a2 = 1.0;
    plugin->filter_HMF.b0 = f0 + 1.0;
    plugin->filter_HMF.b1 = filt_b2;
    plugin->filter_HMF.b2 = 1.0 - f0;
  }
  if (plugin->lmfQSmoother.isInitialized != 1) {
    plugin->lmfQSmoother.isInitialized = 1;
  }
  //  used to update parameter value incrementally each time the audio frame is
  //  processed Perform the smoothing
  plugin->lmfQSmoother.currentValue =
      plugin->lmfQSmoother.smoothingFactor * plugin->lmfQSmoother.currentValue +
      (1.0 - plugin->lmfQSmoother.smoothingFactor) *
          plugin->lmfQSmoother.targetValue;
  //  larger smooth val = slower ramp, smaller smooth val = faster ramp
  Q = plugin->lmfQSmoother.currentValue;
  if (plugin->lmfFreqSmoother.isInitialized != 1) {
    plugin->lmfFreqSmoother.isInitialized = 1;
  }
  //  used to update parameter value incrementally each time the audio frame is
  //  processed Perform the smoothing
  plugin->lmfFreqSmoother.currentValue =
      plugin->lmfFreqSmoother.smoothingFactor *
          plugin->lmfFreqSmoother.currentValue +
      (1.0 - plugin->lmfFreqSmoother.smoothingFactor) *
          plugin->lmfFreqSmoother.targetValue;
  //  larger smooth val = slower ramp, smaller smooth val = faster ramp
  f0 = plugin->lmfFreqSmoother.currentValue;
  if (plugin->lmfQSmoother.isInitialized != 1) {
    plugin->lmfQSmoother.isInitialized = 1;
  }
  //  used to update parameter value incrementally each time the audio frame is
  //  processed Perform the smoothing
  plugin->lmfQSmoother.currentValue =
      plugin->lmfQSmoother.smoothingFactor * plugin->lmfQSmoother.currentValue +
      (1.0 - plugin->lmfQSmoother.smoothingFactor) *
          plugin->lmfQSmoother.targetValue;
  //  larger smooth val = slower ramp, smaller smooth val = faster ramp
  ydb = plugin->lmfQSmoother.currentValue;
  w0 = 6.2831853071795862 * f0 / plugin->fs;
  f0 = std::sin(w0) / (2.0 * Q);
  A = std::sqrt(rt_powd_snf(10.0, ydb / 20.0));
  if (coder::internal::b_strcmp(plugin->typeLMF)) {
    plugin->filter_LMF.a0 = f0 * A;
    plugin->filter_LMF.a1 = 0.0;
    plugin->filter_LMF.a2 = -f0 * A;
    plugin->filter_LMF.b0 = f0 + 1.0;
    plugin->filter_LMF.b1 = -2.0 * std::cos(w0);
    plugin->filter_LMF.b2 = 1.0 - f0;
  } else if (coder::internal::c_strcmp(plugin->typeLMF)) {
    filt_b2 = f0 * A;
    plugin->filter_LMF.a0 = filt_b2 + 1.0;
    w1 = -2.0 * std::cos(w0);
    plugin->filter_LMF.a1 = w1;
    plugin->filter_LMF.a2 = 1.0 - filt_b2;
    filt_b2 = f0 / A;
    plugin->filter_LMF.b0 = filt_b2 + 1.0;
    plugin->filter_LMF.b1 = w1;
    plugin->filter_LMF.b2 = 1.0 - filt_b2;
  } else if (coder::internal::d_strcmp(plugin->typeLMF)) {
    plugin->filter_LMF.a0 = 1.0;
    filt_b2 = -2.0 * std::cos(w0);
    plugin->filter_LMF.a1 = filt_b2;
    plugin->filter_LMF.a2 = 1.0;
    plugin->filter_LMF.b0 = f0 + 1.0;
    plugin->filter_LMF.b1 = filt_b2;
    plugin->filter_LMF.b2 = 1.0 - f0;
  }
  if (plugin->hpfFreqSmoother.isInitialized != 1) {
    plugin->hpfFreqSmoother.isInitialized = 1;
  }
  //  used to update parameter value incrementally each time the audio frame is
  //  processed Perform the smoothing
  plugin->hpfFreqSmoother.currentValue =
      plugin->hpfFreqSmoother.smoothingFactor *
          plugin->hpfFreqSmoother.currentValue +
      (1.0 - plugin->hpfFreqSmoother.smoothingFactor) *
          plugin->hpfFreqSmoother.targetValue;
  //  larger smooth val = slower ramp, smaller smooth val = faster ramp
  f0 = plugin->hpfFreqSmoother.currentValue;
  if (plugin->hpfQSmoother.isInitialized != 1) {
    plugin->hpfQSmoother.isInitialized = 1;
  }
  //  used to update parameter value incrementally each time the audio frame is
  //  processed Perform the smoothing
  plugin->hpfQSmoother.currentValue =
      plugin->hpfQSmoother.smoothingFactor * plugin->hpfQSmoother.currentValue +
      (1.0 - plugin->hpfQSmoother.smoothingFactor) *
          plugin->hpfQSmoother.targetValue;
  //  larger smooth val = slower ramp, smaller smooth val = faster ramp
  Q = plugin->hpfQSmoother.currentValue;
  w0 = 6.2831853071795862 * f0 / plugin->fs;
  f0 = std::sin(w0) / (2.0 * Q);
  //  plugin.filter_HPF.a0 =  (1 + cos(w0))/2;
  //  plugin.filter_HPF.a1 = -(1 - cos(w0));
  //  plugin.filter_HPF.a2 =  (1 + cos(w0))/2;
  //  plugin.filter_HPF.b0 =   1 + alpha;
  //  plugin.filter_HPF.b1 =  -2*cos(w0);
  //  plugin.filter_HPF.b2 =   1 - alpha;
  filt_b2 = std::cos(w0);
  w1 = (filt_b2 + 1.0) / 2.0;
  plugin->filter_HPF.a0 = w1;
  plugin->filter_HPF.a1 = -(filt_b2 + 1.0);
  plugin->filter_HPF.a2 = w1;
  plugin->filter_HPF.b0 = f0 + 1.0;
  plugin->filter_HPF.b1 = -2.0 * filt_b2;
  plugin->filter_HPF.b2 = 1.0 - f0;
  if (plugin->lpfFreqSmoother.isInitialized != 1) {
    plugin->lpfFreqSmoother.isInitialized = 1;
  }
  //  used to update parameter value incrementally each time the audio frame is
  //  processed Perform the smoothing
  plugin->lpfFreqSmoother.currentValue =
      plugin->lpfFreqSmoother.smoothingFactor *
          plugin->lpfFreqSmoother.currentValue +
      (1.0 - plugin->lpfFreqSmoother.smoothingFactor) *
          plugin->lpfFreqSmoother.targetValue;
  //  larger smooth val = slower ramp, smaller smooth val = faster ramp
  f0 = plugin->lpfFreqSmoother.currentValue;
  if (plugin->lpfQSmoother.isInitialized != 1) {
    plugin->lpfQSmoother.isInitialized = 1;
  }
  //  used to update parameter value incrementally each time the audio frame is
  //  processed Perform the smoothing
  plugin->lpfQSmoother.currentValue =
      plugin->lpfQSmoother.smoothingFactor * plugin->lpfQSmoother.currentValue +
      (1.0 - plugin->lpfQSmoother.smoothingFactor) *
          plugin->lpfQSmoother.targetValue;
  //  larger smooth val = slower ramp, smaller smooth val = faster ramp
  Q = plugin->lpfQSmoother.currentValue;
  w0 = 6.2831853071795862 * f0 / plugin->fs;
  f0 = std::sin(w0) / (2.0 * Q);
  filt_b2 = std::cos(w0);
  w1 = (1.0 - filt_b2) / 2.0;
  plugin->filter_LPF.a0 = w1;
  plugin->filter_LPF.a1 = 1.0 - filt_b2;
  plugin->filter_LPF.a2 = w1;
  plugin->filter_LPF.b0 = f0 + 1.0;
  plugin->filter_LPF.b1 = -2.0 * filt_b2;
  plugin->filter_LPF.b2 = 1.0 - f0;
  if (plugin->hsFreqSmoother.isInitialized != 1) {
    plugin->hsFreqSmoother.isInitialized = 1;
  }
  //  used to update parameter value incrementally each time the audio frame is
  //  processed Perform the smoothing
  plugin->hsFreqSmoother.currentValue =
      plugin->hsFreqSmoother.smoothingFactor *
          plugin->hsFreqSmoother.currentValue +
      (1.0 - plugin->hsFreqSmoother.smoothingFactor) *
          plugin->hsFreqSmoother.targetValue;
  //  larger smooth val = slower ramp, smaller smooth val = faster ramp
  f0 = plugin->hsFreqSmoother.currentValue;
  if (plugin->hsQSmoother.isInitialized != 1) {
    plugin->hsQSmoother.isInitialized = 1;
  }
  //  used to update parameter value incrementally each time the audio frame is
  //  processed Perform the smoothing
  plugin->hsQSmoother.currentValue =
      plugin->hsQSmoother.smoothingFactor * plugin->hsQSmoother.currentValue +
      (1.0 - plugin->hsQSmoother.smoothingFactor) *
          plugin->hsQSmoother.targetValue;
  //  larger smooth val = slower ramp, smaller smooth val = faster ramp
  Q = plugin->hsQSmoother.currentValue;
  if (plugin->hsGainSmoother.isInitialized != 1) {
    plugin->hsGainSmoother.isInitialized = 1;
  }
  //  used to update parameter value incrementally each time the audio frame is
  //  processed Perform the smoothing
  plugin->hsGainSmoother.currentValue =
      plugin->hsGainSmoother.smoothingFactor *
          plugin->hsGainSmoother.currentValue +
      (1.0 - plugin->hsGainSmoother.smoothingFactor) *
          plugin->hsGainSmoother.targetValue;
  //  larger smooth val = slower ramp, smaller smooth val = faster ramp
  ydb = plugin->hsGainSmoother.currentValue;
  w0 = 6.2831853071795862 * f0 / plugin->fs;
  A = std::sqrt(rt_powd_snf(10.0, ydb / 20.0));
  filt_b2 = std::cos(w0);
  w1 = (A - 1.0) * filt_b2;
  ydb = (A + 1.0) + w1;
  f0 = 2.0 * std::sqrt(A) * (std::sin(w0) / (2.0 * Q));
  plugin->filter_HS.a0 = A * (ydb + f0);
  //  retains updated filter state information
  filt_b2 *= A + 1.0;
  plugin->filter_HS.a1 = -2.0 * A * ((A - 1.0) + filt_b2);
  plugin->filter_HS.a2 = A * (ydb - f0);
  w1 = (A + 1.0) - w1;
  plugin->filter_HS.b0 = w1 + f0;
  plugin->filter_HS.b1 = 2.0 * ((A - 1.0) - filt_b2);
  plugin->filter_HS.b2 = w1 - f0;
  b_result[0] = result.size(0);
  b_result[1] = 2.0;
  i = static_cast<int>(coder::internal::minimum(b_result));
  for (int ch{0}; ch < i; ch++) {
    double filt_w[4];
    double w2;
    double wn;
    int w1_tmp;
    //  iterates over # of channels on the input
    //  creates pointer to channel
    filt_w[0] = plugin->filter_HS.w[0];
    filt_w[1] = plugin->filter_HS.w[1];
    filt_w[2] = plugin->filter_HS.w[2];
    filt_w[3] = plugin->filter_HS.w[3];
    f0 = plugin->filter_HS.a0;
    ydb = plugin->filter_HS.a1;
    Q = plugin->filter_HS.a2;
    w0 = plugin->filter_HS.b0;
    A = plugin->filter_HS.b1;
    filt_b2 = plugin->filter_HS.b2;
    //  Number of input samples
    i1 = result.size(0);
    loop_ub = result.size(0);
    //  Output vector of zeroes
    //  w = zeros(N, 1); % Intermediate vector of zeroes
    //  Filter coefficients
    //  Get initial state
    w1_tmp = ch << 1;
    w1 = filt_w[w1_tmp];
    w2 = filt_w[w1_tmp + 1];
    //  Difference equations
    for (int n{0}; n < i1; n++) {
      //  Loop through each sample in x
      wn = (result[n + result.size(0) * ch] - A / w0 * w1) - filt_b2 / w0 * w2;
      x_data[n] = (f0 / w0 * wn + ydb / w0 * w1) + Q / w0 * w2;
      w2 = w1;
      //  w[n-2] = w[n-1]
      w1 = wn;
      //  w[n-1] = w[n]
    }
    //  filt.w(:, ch) = [w1; w2];
    plugin->filter_HS.w[w1_tmp] = w1;
    plugin->filter_HS.w[w1_tmp + 1] = w2;
    //  passes the filter object containing filter state and filter
    //  coeffiecients
    filt_w[0] = plugin->filter_HMF.w[0];
    filt_w[1] = plugin->filter_HMF.w[1];
    filt_w[2] = plugin->filter_HMF.w[2];
    filt_w[3] = plugin->filter_HMF.w[3];
    f0 = plugin->filter_HMF.a0;
    ydb = plugin->filter_HMF.a1;
    Q = plugin->filter_HMF.a2;
    w0 = plugin->filter_HMF.b0;
    A = plugin->filter_HMF.b1;
    filt_b2 = plugin->filter_HMF.b2;
    //  Number of input samples
    //  Output vector of zeroes
    //  w = zeros(N, 1); % Intermediate vector of zeroes
    //  Filter coefficients
    //  Get initial state
    w1 = filt_w[w1_tmp];
    w2 = filt_w[w1_tmp + 1];
    //  Difference equations
    for (int n{0}; n < loop_ub; n++) {
      //  Loop through each sample in x
      wn = (x_data[n] - A / w0 * w1) - filt_b2 / w0 * w2;
      b_x_data[n] = (f0 / w0 * wn + ydb / w0 * w1) + Q / w0 * w2;
      w2 = w1;
      //  w[n-2] = w[n-1]
      w1 = wn;
      //  w[n-1] = w[n]
    }
    //  filt.w(:, ch) = [w1; w2];
    plugin->filter_HMF.w[w1_tmp] = w1;
    plugin->filter_HMF.w[w1_tmp + 1] = w2;
    filt_w[0] = plugin->filter_LMF.w[0];
    filt_w[1] = plugin->filter_LMF.w[1];
    filt_w[2] = plugin->filter_LMF.w[2];
    filt_w[3] = plugin->filter_LMF.w[3];
    f0 = plugin->filter_LMF.a0;
    ydb = plugin->filter_LMF.a1;
    Q = plugin->filter_LMF.a2;
    w0 = plugin->filter_LMF.b0;
    A = plugin->filter_LMF.b1;
    filt_b2 = plugin->filter_LMF.b2;
    //  Number of input samples
    //  Output vector of zeroes
    //  w = zeros(N, 1); % Intermediate vector of zeroes
    //  Filter coefficients
    //  Get initial state
    w1 = filt_w[w1_tmp];
    w2 = filt_w[w1_tmp + 1];
    //  Difference equations
    for (int n{0}; n < loop_ub; n++) {
      //  Loop through each sample in x
      wn = (b_x_data[n] - A / w0 * w1) - filt_b2 / w0 * w2;
      c_x_data[n] = (f0 / w0 * wn + ydb / w0 * w1) + Q / w0 * w2;
      w2 = w1;
      //  w[n-2] = w[n-1]
      w1 = wn;
      //  w[n-1] = w[n]
    }
    //  filt.w(:, ch) = [w1; w2];
    plugin->filter_LMF.w[w1_tmp] = w1;
    plugin->filter_LMF.w[w1_tmp + 1] = w2;
    filt_w[0] = plugin->filter_HPF.w[0];
    filt_w[1] = plugin->filter_HPF.w[1];
    filt_w[2] = plugin->filter_HPF.w[2];
    filt_w[3] = plugin->filter_HPF.w[3];
    f0 = plugin->filter_HPF.a0;
    ydb = plugin->filter_HPF.a1;
    Q = plugin->filter_HPF.a2;
    w0 = plugin->filter_HPF.b0;
    A = plugin->filter_HPF.b1;
    filt_b2 = plugin->filter_HPF.b2;
    //  Number of input samples
    //  Output vector of zeroes
    //  w = zeros(N, 1); % Intermediate vector of zeroes
    //  Filter coefficients
    //  Get initial state
    w1 = filt_w[w1_tmp];
    w2 = filt_w[w1_tmp + 1];
    //  Difference equations
    for (int n{0}; n < loop_ub; n++) {
      //  Loop through each sample in x
      wn = (c_x_data[n] - A / w0 * w1) - filt_b2 / w0 * w2;
      d_x_data[n] = (f0 / w0 * wn + ydb / w0 * w1) + Q / w0 * w2;
      w2 = w1;
      //  w[n-2] = w[n-1]
      w1 = wn;
      //  w[n-1] = w[n]
    }
    //  filt.w(:, ch) = [w1; w2];
    plugin->filter_HPF.w[w1_tmp] = w1;
    plugin->filter_HPF.w[w1_tmp + 1] = w2;
    filt_w[0] = plugin->filter_LPF.w[0];
    filt_w[1] = plugin->filter_LPF.w[1];
    filt_w[2] = plugin->filter_LPF.w[2];
    filt_w[3] = plugin->filter_LPF.w[3];
    f0 = plugin->filter_LPF.a0;
    ydb = plugin->filter_LPF.a1;
    Q = plugin->filter_LPF.a2;
    w0 = plugin->filter_LPF.b0;
    A = plugin->filter_LPF.b1;
    filt_b2 = plugin->filter_LPF.b2;
    //  Number of input samples
    //  Output vector of zeroes
    //  w = zeros(N, 1); % Intermediate vector of zeroes
    //  Filter coefficients
    //  Get initial state
    w1 = filt_w[w1_tmp];
    w2 = filt_w[w1_tmp + 1];
    //  Difference equations
    for (int n{0}; n < loop_ub; n++) {
      //  Loop through each sample in x
      wn = (d_x_data[n] - A / w0 * w1) - filt_b2 / w0 * w2;
      e_x_data[n] = (f0 / w0 * wn + ydb / w0 * w1) + Q / w0 * w2;
      w2 = w1;
      //  w[n-2] = w[n-1]
      w1 = wn;
      //  w[n-1] = w[n]
    }
    //  filt.w(:, ch) = [w1; w2];
    plugin->filter_LPF.w[w1_tmp] = w1;
    plugin->filter_LPF.w[w1_tmp + 1] = w2;
    a.set_size(1, plugin->BYPASS_BIQUAD.size(1));
    loop_ub = plugin->BYPASS_BIQUAD.size(1);
    for (i1 = 0; i1 < loop_ub; i1++) {
      a[i1] = plugin->BYPASS_BIQUAD[i1];
    }
    b_bool = false;
    if (a.size(1) == 3) {
      loop_ub = 0;
      do {
        exitg1 = 0;
        if (loop_ub < 3) {
          if (a[loop_ub] != cv[loop_ub]) {
            exitg1 = 1;
          } else {
            loop_ub++;
          }
        } else {
          b_bool = true;
          exitg1 = 1;
        }
      } while (exitg1 == 0);
    }
    if (b_bool) {
      loop_ub = out1.size(0);
      for (i1 = 0; i1 < loop_ub; i1++) {
        out1[i1 + out1.size(0) * ch] = result[i1 + result.size(0) * ch];
      }
    } else {
      loop_ub = out1.size(0);
      for (i1 = 0; i1 < loop_ub; i1++) {
        out1[i1 + out1.size(0) * ch] = e_x_data[i1];
      }
    }
  }
  a.set_size(1, plugin->BYPASS_COMPRESSOR.size(1));
  loop_ub = plugin->BYPASS_COMPRESSOR.size(1);
  for (i = 0; i < loop_ub; i++) {
    a[i] = plugin->BYPASS_COMPRESSOR[i];
  }
  b_bool = false;
  if (a.size(1) == 3) {
    loop_ub = 0;
    do {
      exitg1 = 0;
      if (loop_ub < 3) {
        if (a[loop_ub] != cv[loop_ub]) {
          exitg1 = 1;
        } else {
          loop_ub++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }
  if (b_bool) {
    loop_ub = result.size(0);
    for (i = 0; i < 2; i++) {
      for (i1 = 0; i1 < loop_ub; i1++) {
        out2[i1 + out2.size(0) * i] = out1[i1 + out1.size(0) * i] * gain;
      }
    }
  } else {
    loop_ub = out1.size(0);
    for (i = 0; i < 2; i++) {
      for (i1 = 0; i1 < loop_ub; i1++) {
        out1[i1 + loop_ub * i] = out1[i1 + out1.size(0) * i] * gain;
      }
    }
    out1.set_size(out1.size(0), 2);
    plugin->b_compressor.step(out1, result);
    loop_ub = out2.size(0);
    for (i = 0; i < 2; i++) {
      for (i1 = 0; i1 < loop_ub; i1++) {
        out2[i1 + out2.size(0) * i] = result[i1 + result.size(0) * i];
      }
    }
  }
  loop_ub = t1.size(0);
  for (i = 0; i < 2; i++) {
    for (i1 = 0; i1 < loop_ub; i1++) {
      t1[i1 + t1.size(0) * i] = out2[i1 + out2.size(0) * i];
    }
  }
  if (samplesPerFrame < 1.0) {
    loop_ub = 0;
  } else {
    loop_ub = static_cast<int>(samplesPerFrame);
  }
  o1_size[0] = loop_ub;
  for (i = 0; i < loop_ub; i++) {
    o1_data[i] = t1[i];
  }
  o2_size[0] = loop_ub;
  for (i = 0; i < loop_ub; i++) {
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
