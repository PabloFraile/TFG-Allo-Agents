
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
) {	// L3
#pragma pocc-region-start {
  #pragma HLS array_partition variable=v2 cyclic dim=1 factor=2

  #pragma HLS array_partition variable=v3 cyclic dim=1 factor=2

  float PI;	// L5
  PI = 3.141593;	// L6
  l_S_i_0_i: for (int i = 0; i < 1024; i++) {	// L7
    int rev;	// L9
    rev = 0;	// L10
    int v7 = i;	// L11
    int num;	// L12
    num = v7;	// L13
    l_S_b_0_b: for (int b = 0; b < 10; b++) {	// L14
      int v10 = num;	// L15
      int v11 = v10 % 2;	// L17
      int bit;	// L18
      bit = v11;	// L19
      int v13 = num;	// L20
      int v14 = v13 / 2;	// L21
      num = v14;	// L22
      int v15 = rev;	// L23
      int v16 = v15;	// L24
      int v17 = v16  << 1;	// L26
      int v18 = bit;	// L27
      int v19 = v17;	// L28
      int v20 = v18;	// L29
      int v21 = v19 + v20;	// L30
      int v22 = v21;	// L31
      rev = v22;	// L32
    }
    int v23 = rev;	// L34
    int v24 = v23;	// L35
    float v25 = v0[v24];	// L36
    v2[i] = v25;	// L37
    int v26 = rev;	// L38
    int v27 = v26;	// L39
    float v28 = v1[v27];	// L40
    v3[i] = v28;	// L41
  }
  int m;	// L44
  m = 1;	// L45
  l_S_stage_2_stage: for (int stage = 0; stage < 10; stage++) {	// L46
  #pragma HLS unroll
    int v31 = m;	// L47
    int v32 = v31;	// L48
    int v33 = v32  << 1;	// L51
    int v34 = v33;	// L52
    m = v34;	// L53
    int v35 = m;	// L54
    int v36 = v35 / 2;	// L55
    int half;	// L56
    half = v36;	// L57
    int v38 = m;	// L58
    int v39 = 1024 / v38;	// L60
    int num_groups;	// L61
    num_groups = v39;	// L62
    int v41 = num_groups;	// L63
    int v42 = v41;	// L66
    for (int v43 = 0; v43 < v42; v43 += 1) {	// L68
      int v44 = m;	// L69
      int v45 = v43;	// L70
      int v46 = v44;	// L71
      int v47 = v45 * v46;	// L72
      int v48 = v47;	// L73
      int base;	// L74
      base = v48;	// L75
      int v50 = half;	// L76
      int v51 = v50;	// L77
      for (int v52 = 0; v52 < v51; v52 += 1) {	// L78
      #pragma HLS pipeline II=2
        int v53 = v52;	// L79
        float v54 = v53;	// L80
        float j_f;	// L81
        j_f = v54;	// L82
        int v56 = m;	// L83
        float v57 = v56;	// L84
        float m_f;	// L85
        m_f = v57;	// L86
        float v59 = PI;	// L89
        float v60 = v59 * -2.000000;	// L90
        float v61 = j_f;	// L91
        float v62 = v60 * v61;	// L92
        float v63 = m_f;	// L93
        float v64 = v62 / v63;	// L94
        float angle;	// L95
        angle = v64;	// L96
        float v66 = angle;	// L97
        float v67 = v66 * v66;	// L98
        float x2;	// L99
        x2 = v67;	// L100
        float v69 = x2;	// L101
        float v70 = v69 * v69;	// L102
        float x4;	// L103
        x4 = v70;	// L104
        float v72 = x4;	// L105
        float v73 = x2;	// L106
        float v74 = v72 * v73;	// L107
        float x6;	// L108
        x6 = v74;	// L109
        float v76 = x6;	// L110
        float v77 = x2;	// L111
        float v78 = v76 * v77;	// L112
        float x8;	// L113
        x8 = v78;	// L114
        float v80 = x8;	// L115
        float v81 = x2;	// L116
        float v82 = v80 * v81;	// L117
        float x10;	// L118
        x10 = v82;	// L119
        float v84 = x10;	// L120
        float v85 = x2;	// L121
        float v86 = v84 * v85;	// L122
        float x12;	// L123
        x12 = v86;	// L124
        float v88 = x12;	// L125
        float v89 = x2;	// L126
        float v90 = v88 * v89;	// L127
        float x14;	// L128
        x14 = v90;	// L129
        float v92 = x2;	// L130
        float v93 = v92 / 2.000000;	// L131
        float v94 = 1.000000 - v93;	// L133
        float v95 = x4;	// L134
        float v96 = v95 / 24.000000;	// L136
        float v97 = v94 + v96;	// L137
        float v98 = x6;	// L138
        float v99 = v98 / 720.000000;	// L140
        float v100 = v97 - v99;	// L141
        float v101 = x8;	// L142
        float v102 = v101 / 40320.000000;	// L144
        float v103 = v100 + v102;	// L145
        float v104 = x10;	// L146
        float v105 = v104 / 3628800.000000;	// L148
        float v106 = v103 - v105;	// L149
        float v107 = x12;	// L150
        float v108 = v107 / 479001600.000000;	// L152
        float v109 = v106 + v108;	// L153
        float v110 = x14;	// L154
        float v111 = v110 / 87178289152.000000;	// L156
        float v112 = v109 - v111;	// L157
        float cos_a;	// L158
        cos_a = v112;	// L159
        float v114 = angle;	// L160
        float v115 = x2;	// L161
        float v116 = v114 * v115;	// L162
        float x3;	// L163
        x3 = v116;	// L164
        float v118 = x3;	// L165
        float v119 = x2;	// L166
        float v120 = v118 * v119;	// L167
        float x5;	// L168
        x5 = v120;	// L169
        float v122 = x5;	// L170
        float v123 = x2;	// L171
        float v124 = v122 * v123;	// L172
        float x7;	// L173
        x7 = v124;	// L174
        float v126 = x7;	// L175
        float v127 = x2;	// L176
        float v128 = v126 * v127;	// L177
        float x9;	// L178
        x9 = v128;	// L179
        float v130 = x9;	// L180
        float v131 = x2;	// L181
        float v132 = v130 * v131;	// L182
        float x11;	// L183
        x11 = v132;	// L184
        float v134 = x11;	// L185
        float v135 = x2;	// L186
        float v136 = v134 * v135;	// L187
        float x13;	// L188
        x13 = v136;	// L189
        float v138 = x13;	// L190
        float v139 = x2;	// L191
        float v140 = v138 * v139;	// L192
        float x15;	// L193
        x15 = v140;	// L194
        float v142 = angle;	// L195
        float v143 = x3;	// L196
        float v144 = v143 / 6.000000;	// L198
        float v145 = v142 - v144;	// L199
        float v146 = x5;	// L200
        float v147 = v146 / 120.000000;	// L202
        float v148 = v145 + v147;	// L203
        float v149 = x7;	// L204
        float v150 = v149 / 5040.000000;	// L206
        float v151 = v148 - v150;	// L207
        float v152 = x9;	// L208
        float v153 = v152 / 362880.000000;	// L210
        float v154 = v151 + v153;	// L211
        float v155 = x11;	// L212
        float v156 = v155 / 39916800.000000;	// L214
        float v157 = v154 - v156;	// L215
        float v158 = x13;	// L216
        float v159 = v158 / 6227020800.000000;	// L218
        float v160 = v157 + v159;	// L219
        float v161 = x15;	// L220
        float v162 = v161 / 1307674411008.000000;	// L222
        float v163 = v160 - v162;	// L223
        float sin_a;	// L224
        sin_a = v163;	// L225
        int v165 = base;	// L226
        int v166 = v165;	// L227
        int v167 = v52;	// L228
        int v168 = v166 + v167;	// L229
        int v169 = v168;	// L230
        int idx1;	// L231
        idx1 = v169;	// L232
        int v171 = base;	// L233
        int v172 = v171;	// L234
        int v173 = v172 + v167;	// L235
        int v174 = half;	// L236
        int v175 = v173;	// L237
        int v176 = v174;	// L238
        int v177 = v175 + v176;	// L239
        int v178 = v177;	// L240
        int idx2;	// L241
        idx2 = v178;	// L242
        int v180 = idx2;	// L243
        int v181 = v180;	// L244
        float v182 = v2[v181];	// L245
        float v_real;	// L246
        v_real = v182;	// L247
        int v184 = idx2;	// L248
        int v185 = v184;	// L249
        float v186 = v3[v185];	// L250
        float v_imag;	// L251
        v_imag = v186;	// L252
        float v188 = v_real;	// L253
        float v189 = cos_a;	// L254
        float v190 = v188 * v189;	// L255
        float v191 = v_imag;	// L256
        float v192 = sin_a;	// L257
        float v193 = v191 * v192;	// L258
        float v194 = v190 - v193;	// L259
        float t_real;	// L260
        t_real = v194;	// L261
        float v196 = v_real;	// L262
        float v197 = sin_a;	// L263
        float v198 = v196 * v197;	// L264
        float v199 = v_imag;	// L265
        float v200 = cos_a;	// L266
        float v201 = v199 * v200;	// L267
        float v202 = v198 + v201;	// L268
        float t_imag;	// L269
        t_imag = v202;	// L270
        int v204 = idx1;	// L271
        int v205 = v204;	// L272
        float v206 = v2[v205];	// L273
        float u_real;	// L274
        u_real = v206;	// L275
        int v208 = idx1;	// L276
        int v209 = v208;	// L277
        float v210 = v3[v209];	// L278
        float u_imag;	// L279
        u_imag = v210;	// L280
        float v212 = u_real;	// L281
        float v213 = t_real;	// L282
        float v214 = v212 + v213;	// L283
        int v215 = idx1;	// L284
        int v216 = v215;	// L285
        v2[v216] = v214;	// L286
        float v217 = u_imag;	// L287
        float v218 = t_imag;	// L288
        float v219 = v217 + v218;	// L289
        int v220 = idx1;	// L290
        int v221 = v220;	// L291
        v3[v221] = v219;	// L292
        float v222 = u_real;	// L293
        float v223 = t_real;	// L294
        float v224 = v222 - v223;	// L295
        int v225 = idx2;	// L296
        int v226 = v225;	// L297
        v2[v226] = v224;	// L298
        float v227 = u_imag;	// L299
        float v228 = t_imag;	// L300
        float v229 = v227 - v228;	// L301
        int v230 = idx2;	// L302
        int v231 = v230;	// L303
        v3[v231] = v229;	// L304
      }
    }
  }
}
#pragma pocc-region-end
}

