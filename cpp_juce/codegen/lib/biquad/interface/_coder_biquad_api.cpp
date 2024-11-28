//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// _coder_biquad_api.cpp
//
// Code generation for function 'onParamChangeCImpl'
//

// Include files
#include "_coder_biquad_api.h"
#include "_coder_biquad_mex.h"

// Variable Definitions
emlrtCTX emlrtRootTLSGlobal{nullptr};

emlrtContext emlrtContextGlobal{
    true,                                                 // bFirstTime
    false,                                                // bInitialized
    131659U,                                              // fVersionInfo
    nullptr,                                              // fErrorFunction
    "biquad",                                             // fFunctionName
    nullptr,                                              // fRTCallStack
    false,                                                // bDebugMode
    {2045744189U, 2170104910U, 2743257031U, 4284093946U}, // fSigWrd
    nullptr                                               // fSigMem
};

// Function Declarations
static real_T b_emlrt_marshallIn(const emlrtStack &sp, const mxArray *b_nullptr,
                                 const char_T *identifier);

static real_T b_emlrt_marshallIn(const emlrtStack &sp, const mxArray *u,
                                 const emlrtMsgIdentifier *parentId);

static real_T *b_emlrt_marshallIn(const emlrtStack &sp, const mxArray *src,
                                  const emlrtMsgIdentifier *msgId,
                                  int32_T &ret_size);

static uint64_T c_emlrt_marshallIn(const emlrtStack &sp,
                                   const mxArray *b_nullptr,
                                   const char_T *identifier);

static uint64_T c_emlrt_marshallIn(const emlrtStack &sp, const mxArray *u,
                                   const emlrtMsgIdentifier *parentId);

static int32_T d_emlrt_marshallIn(const emlrtStack &sp, const mxArray *src,
                                  const emlrtMsgIdentifier *msgId);

static real_T e_emlrt_marshallIn(const emlrtStack &sp, const mxArray *src,
                                 const emlrtMsgIdentifier *msgId);

static void emlrtExitTimeCleanupDtorFcn(const void *r);

static int32_T emlrt_marshallIn(const emlrtStack &sp, const mxArray *b_nullptr,
                                const char_T *identifier);

static int32_T emlrt_marshallIn(const emlrtStack &sp, const mxArray *u,
                                const emlrtMsgIdentifier *parentId);

static real_T *emlrt_marshallIn(const emlrtStack &sp, const mxArray *b_nullptr,
                                const char_T *identifier, int32_T &y_size);

static real_T *emlrt_marshallIn(const emlrtStack &sp, const mxArray *u,
                                const emlrtMsgIdentifier *parentId,
                                int32_T &y_size);

static const mxArray *emlrt_marshallOut(real_T u_data[], const int32_T &u_size);

static const mxArray *emlrt_marshallOut(const int32_T u);

static uint64_T f_emlrt_marshallIn(const emlrtStack &sp, const mxArray *src,
                                   const emlrtMsgIdentifier *msgId);

// Function Definitions
static real_T b_emlrt_marshallIn(const emlrtStack &sp, const mxArray *b_nullptr,
                                 const char_T *identifier)
{
  emlrtMsgIdentifier thisId;
  real_T y;
  thisId.fIdentifier = const_cast<const char_T *>(identifier);
  thisId.fParent = nullptr;
  thisId.bParentIsCell = false;
  y = b_emlrt_marshallIn(sp, emlrtAlias(b_nullptr), &thisId);
  emlrtDestroyArray(&b_nullptr);
  return y;
}

static real_T b_emlrt_marshallIn(const emlrtStack &sp, const mxArray *u,
                                 const emlrtMsgIdentifier *parentId)
{
  real_T y;
  y = e_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static real_T *b_emlrt_marshallIn(const emlrtStack &sp, const mxArray *src,
                                  const emlrtMsgIdentifier *msgId,
                                  int32_T &ret_size)
{
  static const int32_T dims{4096};
  real_T *ret_data;
  boolean_T b{true};
  emlrtCheckVsBuiltInR2012b((emlrtConstCTX)&sp, msgId, src, "double", false, 1U,
                            (const void *)&dims, &b, &ret_size);
  ret_data = static_cast<real_T *>(emlrtMxGetData(src));
  emlrtDestroyArray(&src);
  return ret_data;
}

static uint64_T c_emlrt_marshallIn(const emlrtStack &sp,
                                   const mxArray *b_nullptr,
                                   const char_T *identifier)
{
  emlrtMsgIdentifier thisId;
  uint64_T y;
  thisId.fIdentifier = const_cast<const char_T *>(identifier);
  thisId.fParent = nullptr;
  thisId.bParentIsCell = false;
  y = c_emlrt_marshallIn(sp, emlrtAlias(b_nullptr), &thisId);
  emlrtDestroyArray(&b_nullptr);
  return y;
}

static uint64_T c_emlrt_marshallIn(const emlrtStack &sp, const mxArray *u,
                                   const emlrtMsgIdentifier *parentId)
{
  uint64_T y;
  y = f_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static int32_T d_emlrt_marshallIn(const emlrtStack &sp, const mxArray *src,
                                  const emlrtMsgIdentifier *msgId)
{
  static const int32_T dims{0};
  int32_T ret;
  emlrtCheckBuiltInR2012b((emlrtConstCTX)&sp, msgId, src, "int32", false, 0U,
                          (const void *)&dims);
  ret = *static_cast<int32_T *>(emlrtMxGetData(src));
  emlrtDestroyArray(&src);
  return ret;
}

static real_T e_emlrt_marshallIn(const emlrtStack &sp, const mxArray *src,
                                 const emlrtMsgIdentifier *msgId)
{
  static const int32_T dims{0};
  real_T ret;
  emlrtCheckBuiltInR2012b((emlrtConstCTX)&sp, msgId, src, "double", false, 0U,
                          (const void *)&dims);
  ret = *static_cast<real_T *>(emlrtMxGetData(src));
  emlrtDestroyArray(&src);
  return ret;
}

static void emlrtExitTimeCleanupDtorFcn(const void *r)
{
  emlrtExitTimeCleanup(&emlrtContextGlobal);
}

static int32_T emlrt_marshallIn(const emlrtStack &sp, const mxArray *b_nullptr,
                                const char_T *identifier)
{
  emlrtMsgIdentifier thisId;
  int32_T y;
  thisId.fIdentifier = const_cast<const char_T *>(identifier);
  thisId.fParent = nullptr;
  thisId.bParentIsCell = false;
  y = emlrt_marshallIn(sp, emlrtAlias(b_nullptr), &thisId);
  emlrtDestroyArray(&b_nullptr);
  return y;
}

static int32_T emlrt_marshallIn(const emlrtStack &sp, const mxArray *u,
                                const emlrtMsgIdentifier *parentId)
{
  int32_T y;
  y = d_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static real_T *emlrt_marshallIn(const emlrtStack &sp, const mxArray *b_nullptr,
                                const char_T *identifier, int32_T &y_size)
{
  emlrtMsgIdentifier thisId;
  real_T *y_data;
  int32_T i;
  thisId.fIdentifier = const_cast<const char_T *>(identifier);
  thisId.fParent = nullptr;
  thisId.bParentIsCell = false;
  y_data = emlrt_marshallIn(sp, emlrtAlias(b_nullptr), &thisId, i);
  y_size = i;
  emlrtDestroyArray(&b_nullptr);
  return y_data;
}

static real_T *emlrt_marshallIn(const emlrtStack &sp, const mxArray *u,
                                const emlrtMsgIdentifier *parentId,
                                int32_T &y_size)
{
  real_T *y_data;
  int32_T i;
  y_data = b_emlrt_marshallIn(sp, emlrtAlias(u), parentId, i);
  y_size = i;
  emlrtDestroyArray(&u);
  return y_data;
}

static const mxArray *emlrt_marshallOut(real_T u_data[], const int32_T &u_size)
{
  static const int32_T i{0};
  const mxArray *m;
  const mxArray *y;
  y = nullptr;
  m = emlrtCreateNumericArray(1, (const void *)&i, mxDOUBLE_CLASS, mxREAL);
  emlrtMxSetData((mxArray *)m, &u_data[0]);
  emlrtSetDimensions((mxArray *)m, &u_size, 1);
  emlrtAssign(&y, m);
  return y;
}

static const mxArray *emlrt_marshallOut(const int32_T u)
{
  const mxArray *m;
  const mxArray *y;
  y = nullptr;
  m = emlrtCreateNumericMatrix(1, 1, mxINT32_CLASS, mxREAL);
  *static_cast<int32_T *>(emlrtMxGetData(m)) = u;
  emlrtAssign(&y, m);
  return y;
}

static uint64_T f_emlrt_marshallIn(const emlrtStack &sp, const mxArray *src,
                                   const emlrtMsgIdentifier *msgId)
{
  static const int32_T dims{0};
  uint64_T ret;
  emlrtCheckBuiltInR2012b((emlrtConstCTX)&sp, msgId, src, "uint64", false, 0U,
                          (const void *)&dims);
  ret = *static_cast<uint64_T *>(emlrtMxGetData(src));
  emlrtDestroyArray(&src);
  return ret;
}

void biquad_atexit()
{
  emlrtStack st{
      nullptr, // site
      nullptr, // tls
      nullptr  // prev
  };
  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtPushHeapReferenceStackR2021a(&st, false, nullptr,
                                    (void *)&emlrtExitTimeCleanupDtorFcn,
                                    nullptr, nullptr, nullptr);
  emlrtEnterRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  biquad_xil_terminate();
  biquad_xil_shutdown();
  emlrtExitTimeCleanup(&emlrtContextGlobal);
}

void biquad_initialize()
{
  emlrtStack st{
      nullptr, // site
      nullptr, // tls
      nullptr  // prev
  };
  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtClearAllocCountR2012b(&st, false, 0U, nullptr);
  emlrtEnterRtStackR2012b(&st);
  emlrtFirstTimeR2012b(emlrtRootTLSGlobal);
}

void biquad_terminate()
{
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

void createPluginInstance_api(const mxArray *prhs)
{
  emlrtStack st{
      nullptr, // site
      nullptr, // tls
      nullptr  // prev
  };
  uint64_T thisPtr;
  st.tls = emlrtRootTLSGlobal;
  // Marshall function inputs
  thisPtr = c_emlrt_marshallIn(st, emlrtAliasP(prhs), "thisPtr");
  // Invoke the target function
  createPluginInstance(thisPtr);
}

void getLatencyInSamplesCImpl_api(const mxArray **plhs)
{
  int32_T n;
  // Invoke the target function
  n = getLatencyInSamplesCImpl();
  // Marshall function outputs
  *plhs = emlrt_marshallOut(n);
}

void onParamChangeCImpl_api(const mxArray *const prhs[2])
{
  emlrtStack st{
      nullptr, // site
      nullptr, // tls
      nullptr  // prev
  };
  real_T b_value;
  int32_T paramIdx;
  st.tls = emlrtRootTLSGlobal;
  // Marshall function inputs
  paramIdx = emlrt_marshallIn(st, emlrtAliasP(prhs[0]), "paramIdx");
  b_value = b_emlrt_marshallIn(st, emlrtAliasP(prhs[1]), "value");
  // Invoke the target function
  onParamChangeCImpl(paramIdx, b_value);
}

void processEntryPoint_api(const mxArray *const prhs[3], int32_T nlhs,
                           const mxArray *plhs[2])
{
  emlrtStack st{
      nullptr, // site
      nullptr, // tls
      nullptr  // prev
  };
  real_T(*i1_data)[4096];
  real_T(*i2_data)[4096];
  real_T(*o1_data)[4096];
  real_T(*o2_data)[4096];
  real_T samplesPerFrame;
  int32_T i1_size;
  int32_T i2_size;
  int32_T o1_size;
  int32_T o2_size;
  st.tls = emlrtRootTLSGlobal;
  o1_data = (real_T(*)[4096])mxMalloc(sizeof(real_T[4096]));
  o2_data = (real_T(*)[4096])mxMalloc(sizeof(real_T[4096]));
  // Marshall function inputs
  samplesPerFrame =
      b_emlrt_marshallIn(st, emlrtAliasP(prhs[0]), "samplesPerFrame");
  *(real_T **)&i1_data =
      emlrt_marshallIn(st, emlrtAlias(prhs[1]), "i1", i1_size);
  *(real_T **)&i2_data =
      emlrt_marshallIn(st, emlrtAlias(prhs[2]), "i2", i2_size);
  // Invoke the target function
  processEntryPoint(samplesPerFrame, *i1_data, &i1_size, *i2_data, &i2_size,
                    *o1_data, &o1_size, *o2_data, &o2_size);
  // Marshall function outputs
  plhs[0] = emlrt_marshallOut(*o1_data, o1_size);
  if (nlhs > 1) {
    plhs[1] = emlrt_marshallOut(*o2_data, o2_size);
  }
}

void resetCImpl_api(const mxArray *prhs)
{
  emlrtStack st{
      nullptr, // site
      nullptr, // tls
      nullptr  // prev
  };
  real_T rate;
  st.tls = emlrtRootTLSGlobal;
  // Marshall function inputs
  rate = b_emlrt_marshallIn(st, emlrtAliasP(prhs), "rate");
  // Invoke the target function
  resetCImpl(rate);
}

// End of code generation (_coder_biquad_api.cpp)
