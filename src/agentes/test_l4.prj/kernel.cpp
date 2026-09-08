
//===------------------------------------------------------------*- C++ -*-===//
//
// Automatically generated file for High-level Synthesis (HLS).
//
//===----------------------------------------------------------------------===//
#include <algorithm>
#include <ap_axi_sdata.h>
#include <ap_fixed.h>
#include <ap_int.h>
#include <hls_math.h>
#include <hls_stream.h>
#include <hls_vector.h>
#include <math.h>
#include <stdint.h>
using namespace std;
/// This is top function.
void kernel(
  int32_t v0[32],
  int32_t v1[32],
  int32_t v2[32]
) {	// L2
  l_S_i_0_i: for (int i = 0; i < 32; i++) {	// L3
    int32_t v4 = v0[i];	// L4
    int32_t v5 = v1[i];	// L5
    ap_int<33> v6 = v4;	// L6
    ap_int<33> v7 = v5;	// L7
    ap_int<33> v8 = v6 + v7;	// L8
    int32_t v9 = v8;	// L9
    v2[i] = v9;	// L10
  }
}

