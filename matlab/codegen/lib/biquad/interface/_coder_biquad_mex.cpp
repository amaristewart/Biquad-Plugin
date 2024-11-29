//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// _coder_biquad_mex.cpp
//
// Code generation for function 'onParamChangeCImpl'
//

// Include files
#include "_coder_biquad_mex.h"
#include "_coder_biquad_api.h"

// Function Definitions
void mexFunction(int32_T nlhs, mxArray *plhs[], int32_T nrhs,
                 const mxArray *prhs[])
{
  emlrtStack st{
      nullptr, // site
      nullptr, // tls
      nullptr  // prev
  };
  const mxArray *d_prhs[3];
  const mxArray *b_prhs[2];
  const mxArray *c_prhs[1];
  const mxArray *e_prhs[1];
  const char_T *entryPointTemplateNames[5]{
      "onParamChangeCImpl", "resetCImpl", "processEntryPoint",
      "createPluginInstance", "getLatencyInSamplesCImpl"};
  mexAtExit(&biquad_atexit);
  biquad_initialize();
  st.tls = emlrtRootTLSGlobal;
  switch (emlrtGetEntryPointIndexR2016a(
      &st, nrhs, &prhs[0], (const char_T **)&entryPointTemplateNames[0], 5)) {
  case 0:
    b_prhs[0] = prhs[1];
    b_prhs[1] = prhs[2];
    unsafe_onParamChangeCImpl_mexFunction(nlhs, nrhs - 1, b_prhs);
    break;
  case 1:
    c_prhs[0] = prhs[1];
    unsafe_resetCImpl_mexFunction(nlhs, nrhs - 1, c_prhs);
    break;
  case 2:
    d_prhs[0] = prhs[1];
    d_prhs[1] = prhs[2];
    d_prhs[2] = prhs[3];
    unsafe_processEntryPoint_mexFunction(nlhs, plhs, nrhs - 1, d_prhs);
    break;
  case 3:
    e_prhs[0] = prhs[1];
    unsafe_createPluginInstance_mexFunction(nlhs, nrhs - 1, e_prhs);
    break;
  case 4:
    unsafe_getLatencyInSamplesCImpl_mexFunction(nlhs, plhs, nrhs - 1);
    break;
  }
  biquad_terminate();
}

emlrtCTX mexFunctionCreateRootTLS()
{
  emlrtCreateRootTLSR2022a(&emlrtRootTLSGlobal, &emlrtContextGlobal, nullptr, 1,
                           nullptr, "UTF-8", true);
  return emlrtRootTLSGlobal;
}

void unsafe_createPluginInstance_mexFunction(int32_T nlhs, int32_T nrhs,
                                             const mxArray *prhs[1])
{
  emlrtStack st{
      nullptr, // site
      nullptr, // tls
      nullptr  // prev
  };
  st.tls = emlrtRootTLSGlobal;
  // Check for proper number of arguments.
  if (nrhs != 1) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 1, 4,
                        20, "createPluginInstance");
  }
  if (nlhs > 0) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 20,
                        "createPluginInstance");
  }
  // Call the function.
  createPluginInstance_api(prhs[0]);
}

void unsafe_getLatencyInSamplesCImpl_mexFunction(int32_T nlhs, mxArray *plhs[1],
                                                 int32_T nrhs)
{
  emlrtStack st{
      nullptr, // site
      nullptr, // tls
      nullptr  // prev
  };
  const mxArray *outputs;
  st.tls = emlrtRootTLSGlobal;
  // Check for proper number of arguments.
  if (nrhs != 0) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 0, 4,
                        24, "getLatencyInSamplesCImpl");
  }
  if (nlhs > 1) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 24,
                        "getLatencyInSamplesCImpl");
  }
  // Call the function.
  getLatencyInSamplesCImpl_api(&outputs);
  // Copy over outputs to the caller.
  emlrtReturnArrays(1, &plhs[0], &outputs);
}

void unsafe_onParamChangeCImpl_mexFunction(int32_T nlhs, int32_T nrhs,
                                           const mxArray *prhs[2])
{
  emlrtStack st{
      nullptr, // site
      nullptr, // tls
      nullptr  // prev
  };
  st.tls = emlrtRootTLSGlobal;
  // Check for proper number of arguments.
  if (nrhs != 2) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 2, 4,
                        18, "onParamChangeCImpl");
  }
  if (nlhs > 0) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 18,
                        "onParamChangeCImpl");
  }
  // Call the function.
  onParamChangeCImpl_api(prhs);
}

void unsafe_processEntryPoint_mexFunction(int32_T nlhs, mxArray *plhs[2],
                                          int32_T nrhs, const mxArray *prhs[3])
{
  emlrtStack st{
      nullptr, // site
      nullptr, // tls
      nullptr  // prev
  };
  const mxArray *b_prhs[3];
  const mxArray *outputs[2];
  int32_T i;
  st.tls = emlrtRootTLSGlobal;
  // Check for proper number of arguments.
  if (nrhs != 3) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 3, 4,
                        17, "processEntryPoint");
  }
  if (nlhs > 2) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 17,
                        "processEntryPoint");
  }
  // Call the function.
  b_prhs[0] = prhs[0];
  b_prhs[1] = prhs[1];
  b_prhs[2] = prhs[2];
  processEntryPoint_api(b_prhs, nlhs, outputs);
  // Copy over outputs to the caller.
  if (nlhs < 1) {
    i = 1;
  } else {
    i = nlhs;
  }
  emlrtReturnArrays(i, &plhs[0], &outputs[0]);
}

void unsafe_resetCImpl_mexFunction(int32_T nlhs, int32_T nrhs,
                                   const mxArray *prhs[1])
{
  emlrtStack st{
      nullptr, // site
      nullptr, // tls
      nullptr  // prev
  };
  st.tls = emlrtRootTLSGlobal;
  // Check for proper number of arguments.
  if (nrhs != 1) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 1, 4,
                        10, "resetCImpl");
  }
  if (nlhs > 0) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 10,
                        "resetCImpl");
  }
  // Call the function.
  resetCImpl_api(prhs[0]);
}

// End of code generation (_coder_biquad_mex.cpp)
