
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
  float v0[1024],
  float v1[1024],
  float v2[1024],
  float v3[1024]
) {	// L2
#pragma pocc-region-start {
  float tw_real[512];	// L3
  float tw_imag[512];	// L4
  float two_pi;	// L7
  two_pi = 6.283185;	// L8
  l_S_k_0_k: for (int k = 0; k < 512; k++) {	// L9
    int v8 = k;	// L10
    float v9 = v8;	// L11
    float k_f;	// L12
    k_f = v9;	// L13
    float n_f;	// L16
    n_f = 1024.000000;	// L17
    float v12 = two_pi;	// L21
    float v13 = v12 * -1.000000;	// L22
    float v14 = k_f;	// L23
    float v15 = v13 * v14;	// L24
    float v16 = n_f;	// L25
    float v17 = v15 / v16;	// L26
    float theta;	// L27
    theta = v17;	// L28
    float v19 = theta;	// L29
    float v20 = v19 * v19;	// L31
    float theta2;	// L32
    theta2 = v20;	// L33
    float cos_term;	// L36
    cos_term = 1.000000;	// L37
    float cos_sum;	// L40
    cos_sum = 1.000000;	// L41
    float v24 = theta;	// L42
    float sin_term;	// L43
    sin_term = v24;	// L44
    float v26 = theta;	// L45
    float sin_sum;	// L46
    sin_sum = v26;	// L47
    l_S_t0_0_t0: for (int t0 = 0; t0 < 8; t0++) {	// L48
      int v29 = t0;	// L49
      float v30 = v29;	// L50
      float t_f;	// L51
      t_f = v30;	// L52
      float v32 = t_f;	// L53
      float v33 = v32 + 1.000000;	// L56
      t_f = v33;	// L57
      float v34 = t_f;	// L58
      float v35 = v34  << 1.000000;	// L61
      float two_t;	// L62
      two_t = v35;	// L63
      float v37 = two_t;	// L64
      float v38 = v37 - 1.000000;	// L67
      float two_t_minus1;	// L68
      two_t_minus1 = v38;	// L69
      float v40 = two_t;	// L70
      float v41 = v40 + 1.000000;	// L73
      float two_t_plus1;	// L74
      two_t_plus1 = v41;	// L75
      float v43 = two_t_minus1;	// L76
      float v44 = two_t;	// L77
      float v45 = v43 * v44;	// L78
      float denom_cos;	// L79
      denom_cos = v45;	// L80
      float v47 = cos_term;	// L81
      float v48 = theta2;	// L82
      float v49 = v47 * v48;	// L83
      float v50 = v49 * -1.000000;	// L87
      float v51 = denom_cos;	// L88
      float v52 = v50 / v51;	// L89
      cos_term = v52;	// L90
      float v53 = cos_sum;	// L91
      float v54 = cos_term;	// L92
      float v55 = v53 + v54;	// L93
      cos_sum = v55;	// L94
      float v56 = two_t;	// L95
      float v57 = two_t_plus1;	// L96
      float v58 = v56 * v57;	// L97
      float denom_sin;	// L98
      denom_sin = v58;	// L99
      float v60 = sin_term;	// L100
      float v61 = theta2;	// L101
      float v62 = v60 * v61;	// L102
      float v63 = v62 * -1.000000;	// L106
      float v64 = denom_sin;	// L107
      float v65 = v63 / v64;	// L108
      sin_term = v65;	// L109
      float v66 = sin_sum;	// L110
      float v67 = sin_term;	// L111
      float v68 = v66 + v67;	// L112
      sin_sum = v68;	// L113
    }
    float v69 = cos_sum;	// L115
    tw_real[k] = v69;	// L116
    float v70 = sin_sum;	// L117
    tw_imag[k] = v70;	// L118
  }
  l_S_i_2_i: for (int i = 0; i < 1024; i++) {	// L120
    int v72 = i;	// L121
    int idx;	// L122
    idx = v72;	// L123
    int rev;	// L126
    rev = 0;	// L127
    l_S_b_2_b: for (int b = 0; b < 10; b++) {	// L128
      int v76 = idx;	// L129
      int v77 = v76 / 2;	// L132
      int idx_div2;	// L133
      idx_div2 = v77;	// L134
      int v79 = idx;	// L135
      int v80 = idx_div2;	// L136
      int v81 = v80;	// L137
      int v82 = v81  << 1;	// L141
      int v83 = v79;	// L142
      int v84 = v82;	// L143
      int v85 = v83 - v84;	// L144
      int v86 = v85;	// L145
      int bit;	// L146
      bit = v86;	// L147
      int v88 = rev;	// L148
      int v89 = v88;	// L149
      int v90 = v89  << 1;	// L153
      int v91 = bit;	// L154
      int v92 = v90;	// L155
      int v93 = v91;	// L156
      int v94 = v92 + v93;	// L157
      int v95 = v94;	// L158
      rev = v95;	// L159
      int v96 = idx_div2;	// L160
      idx = v96;	// L161
    }
    int v97 = rev;	// L163
    int v98 = v97;	// L164
    float v99 = v0[v98];	// L165
    v2[i] = v99;	// L166
    int v100 = rev;	// L167
    int v101 = v100;	// L168
    float v102 = v1[v101];	// L169
    v3[i] = v102;	// L170
  }
  int m;	// L174
  m = 1;	// L175
  l_S_s_4_s: for (int s = 0; s < 10; s++) {	// L176
    int v105 = m;	// L177
    int v106 = v105;	// L178
    int v107 = v106  << 1;	// L182
    int v108 = v107;	// L183
    m = v108;	// L184
    int v109 = m;	// L185
    int v110 = v109 / 2;	// L188
    int half;	// L189
    half = v110;	// L190
    int v112 = m;	// L191
    int v113 = 1024 / v112;	// L194
    int step;	// L195
    step = v113;	// L196
    int v115 = m;	// L197
    int v116 = 1024 / v115;	// L200
    int num_groups;	// L201
    num_groups = v116;	// L202
    int v118 = num_groups;	// L203
    int v119 = v118;	// L207
    for (int v120 = 0; v120 < v119; v120 += 1) {	// L211
      int v121 = half;	// L212
      int v122 = v121;	// L216
      for (int v123 = 0; v123 < v122; v123 += 1) {	// L220
        int v124 = m;	// L221
        int v125 = v120;	// L222
        int v126 = v124;	// L223
        int v127 = v125 * v126;	// L224
        int v128 = v127;	// L225
        int v129 = v123;	// L226
        int v130 = v128 + v129;	// L227
        int v131 = v130;	// L228
        int idx1;	// L229
        idx1 = v131;	// L230
        int v133 = idx1;	// L231
        int v134 = half;	// L232
        int v135 = v133;	// L233
        int v136 = v134;	// L234
        int v137 = v135 + v136;	// L235
        int v138 = v137;	// L236
        int idx2;	// L237
        idx2 = v138;	// L238
        int v140 = step;	// L239
        int v141 = v123;	// L240
        int v142 = v140;	// L241
        int v143 = v141 * v142;	// L242
        int v144 = v143;	// L243
        int tw_index;	// L244
        tw_index = v144;	// L245
        int v146 = tw_index;	// L246
        int v147 = v146;	// L247
        float v148 = tw_real[v147];	// L248
        float wr;	// L249
        wr = v148;	// L250
        int v150 = tw_index;	// L251
        int v151 = v150;	// L252
        float v152 = tw_imag[v151];	// L253
        float wi;	// L254
        wi = v152;	// L255
        int v154 = idx2;	// L256
        int v155 = v154;	// L257
        float v156 = v2[v155];	// L258
        float xr2;	// L259
        xr2 = v156;	// L260
        int v158 = idx2;	// L261
        int v159 = v158;	// L262
        float v160 = v3[v159];	// L263
        float xi2;	// L264
        xi2 = v160;	// L265
        float v162 = wr;	// L266
        float v163 = xr2;	// L267
        float v164 = v162 * v163;	// L268
        float v165 = wi;	// L269
        float v166 = xi2;	// L270
        float v167 = v165 * v166;	// L271
        float v168 = v164 - v167;	// L272
        float tr;	// L273
        tr = v168;	// L274
        float v170 = wr;	// L275
        float v171 = xi2;	// L276
        float v172 = v170 * v171;	// L277
        float v173 = wi;	// L278
        float v174 = xr2;	// L279
        float v175 = v173 * v174;	// L280
        float v176 = v172 + v175;	// L281
        float ti;	// L282
        ti = v176;	// L283
        int v178 = idx1;	// L284
        int v179 = v178;	// L285
        float v180 = v2[v179];	// L286
        float xr1;	// L287
        xr1 = v180;	// L288
        int v182 = idx1;	// L289
        int v183 = v182;	// L290
        float v184 = v3[v183];	// L291
        float xi1;	// L292
        xi1 = v184;	// L293
        float v186 = xr1;	// L294
        float v187 = tr;	// L295
        float v188 = v186 + v187;	// L296
        int v189 = idx1;	// L297
        int v190 = v189;	// L298
        v2[v190] = v188;	// L299
        float v191 = xi1;	// L300
        float v192 = ti;	// L301
        float v193 = v191 + v192;	// L302
        int v194 = idx1;	// L303
        int v195 = v194;	// L304
        v3[v195] = v193;	// L305
        float v196 = xr1;	// L306
        float v197 = tr;	// L307
        float v198 = v196 - v197;	// L308
        int v199 = idx2;	// L309
        int v200 = v199;	// L310
        v2[v200] = v198;	// L311
        float v201 = xi1;	// L312
        float v202 = ti;	// L313
        float v203 = v201 - v202;	// L314
        int v204 = idx2;	// L315
        int v205 = v204;	// L316
        v3[v205] = v203;	// L317
      }
    }
  }
}
#pragma pocc-region-end
}

