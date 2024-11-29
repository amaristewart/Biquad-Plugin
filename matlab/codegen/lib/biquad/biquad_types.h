//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// biquad_types.h
//
// Code generation for function 'onParamChangeCImpl'
//

#ifndef BIQUAD_TYPES_H
#define BIQUAD_TYPES_H

// Include files
#include "biquad.h"
#include "rtwtypes.h"

// Type Definitions
struct biquadPersistentData {
  derivedAudioPlugin plugin;
  boolean_T plugin_not_empty;
  boolean_T thisPtr_not_empty;
};

struct biquadStackData {
  biquadPersistentData *pd;
};

#endif
// End of code generation (biquad_types.h)
