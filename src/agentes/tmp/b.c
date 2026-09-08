
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
  float PI;	// L5
  PI = 3.141593;	// L6
  l_S_i_0_i: for (int i = 0; i < 1024; i++) {	// L7
    int rev;	// L10
    rev = 0;	// L11
    int v7 = i;	// L12
    int num;	// L13
    num = v7;	// L14
    l_S_b_0_b: for (int b = 0; b < 10; b++) {	// L15
      int v10 = num;	// L16
      int v11 = v10 % 2;	// L19
      int bit;	// L20
      bit = v11;	// L21
      int v13 = num;	// L22
      int v14 = v13 / 2;	// L25
      num = v14;	// L26
      int v15 = rev;	// L27
      int v16 = v15;	// L28
      int v17 = v16  << 1;	// L32
      int v18 = bit;	// L33
      int v19 = v17;	// L34
      int v20 = v18;	// L35
      int v21 = v19 + v20;	// L36
      int v22 = v21;	// L37
      rev = v22;	// L38
    }
    int v23 = rev;	// L40
    int v24 = v23;	// L41
    float v25 = v0[v24];	// L42
    v2[i] = v25;	// L43
    int v26 = rev;	// L44
    int v27 = v26;	// L45
    float v28 = v1[v27];	// L46
    v3[i] = v28;	// L47
  }
  int m;	// L51
  m = 1;	// L52
  l_S_stage_2_stage: for (int stage = 0; stage < 10; stage++) {	// L53
    int v31 = m;	// L54
    int v32 = v31;	// L55
    int v33 = v32  << 1;	// L59
    int v34 = v33;	// L60
    m = v34;	// L61
    int v35 = m;	// L62
    int v36 = v35 / 2;	// L65
    int half;	// L66
    half = v36;	// L67
    int v38 = m;	// L68
    int v39 = 1024 / v38;	// L71
    int num_groups;	// L72
    num_groups = v39;	// L73
    int v41 = num_groups;	// L74
    int v42 = v41;	// L78
    for (int v43 = 0; v43 < v42; v43 += 1) {	// L82
      int v44 = m;	// L83
      int v45 = v43;	// L84
      int v46 = v44;	// L85
      int v47 = v45 * v46;	// L86
      int v48 = v47;	// L87
      int base;	// L88
      base = v48;	// L89
      int v50 = half;	// L90
      int v51 = v50;	// L94
      for (int v52 = 0; v52 < v51; v52 += 1) {	// L98
        int v53 = v52;	// L99
        float v54 = v53;	// L100
        float j_f;	// L101
        j_f = v54;	// L102
        int v56 = m;	// L103
        float v57 = v56;	// L104
        float m_f;	// L105
        m_f = v57;	// L106
        float v59 = PI;	// L110
        float v60 = v59 * -2.000000;	// L111
        float v61 = j_f;	// L112
        float v62 = v60 * v61;	// L113
        float v63 = m_f;	// L114
        float v64 = v62 / v63;	// L115
        float angle;	// L116
        angle = v64;	// L117
        float v66 = angle;	// L118
        float v67 = v66 * v66;	// L120
        float x2;	// L121
        x2 = v67;	// L122
        float v69 = x2;	// L123
        float v70 = v69 * v69;	// L125
        float x4;	// L126
        x4 = v70;	// L127
        float v72 = x4;	// L128
        float v73 = x2;	// L129
        float v74 = v72 * v73;	// L130
        float x6;	// L131
        x6 = v74;	// L132
        float v76 = x6;	// L133
        float v77 = x2;	// L134
        float v78 = v76 * v77;	// L135
        float x8;	// L136
        x8 = v78;	// L137
        float v80 = x8;	// L138
        float v81 = x2;	// L139
        float v82 = v80 * v81;	// L140
        float x10;	// L141
        x10 = v82;	// L142
        float v84 = x10;	// L143
        float v85 = x2;	// L144
        float v86 = v84 * v85;	// L145
        float x12;	// L146
        x12 = v86;	// L147
        float v88 = x12;	// L148
        float v89 = x2;	// L149
        float v90 = v88 * v89;	// L150
        float x14;	// L151
        x14 = v90;	// L152
        float v92 = x2;	// L153
        float v93 = v92 / 2.000000;	// L156
        float v94 = 1.000000 - v93;	// L159
        float v95 = x4;	// L160
        float v96 = v95 / 24.000000;	// L163
        float v97 = v94 + v96;	// L164
        float v98 = x6;	// L165
        float v99 = v98 / 720.000000;	// L168
        float v100 = v97 - v99;	// L169
        float v101 = x8;	// L170
        float v102 = v101 / 40320.000000;	// L173
        float v103 = v100 + v102;	// L174
        float v104 = x10;	// L175
        float v105 = v104 / 3628800.000000;	// L178
        float v106 = v103 - v105;	// L179
        float v107 = x12;	// L180
        float v108 = v107 / 479001600.000000;	// L183
        float v109 = v106 + v108;	// L184
        float v110 = x14;	// L185
        float v111 = v110 / 87178289152.000000;	// L188
        float v112 = v109 - v111;	// L189
        float cos_a;	// L190
        cos_a = v112;	// L191
        float v114 = angle;	// L192
        float v115 = x2;	// L193
        float v116 = v114 * v115;	// L194
        float x3;	// L195
        x3 = v116;	// L196
        float v118 = x3;	// L197
        float v119 = x2;	// L198
        float v120 = v118 * v119;	// L199
        float x5;	// L200
        x5 = v120;	// L201
        float v122 = x5;	// L202
        float v123 = x2;	// L203
        float v124 = v122 * v123;	// L204
        float x7;	// L205
        x7 = v124;	// L206
        float v126 = x7;	// L207
        float v127 = x2;	// L208
        float v128 = v126 * v127;	// L209
        float x9;	// L210
        x9 = v128;	// L211
        float v130 = x9;	// L212
        float v131 = x2;	// L213
        float v132 = v130 * v131;	// L214
        float x11;	// L215
        x11 = v132;	// L216
        float v134 = x11;	// L217
        float v135 = x2;	// L218
        float v136 = v134 * v135;	// L219
        float x13;	// L220
        x13 = v136;	// L221
        float v138 = x13;	// L222
        float v139 = x2;	// L223
        float v140 = v138 * v139;	// L224
        float x15;	// L225
        x15 = v140;	// L226
        float v142 = angle;	// L227
        float v143 = x3;	// L228
        float v144 = v143 / 6.000000;	// L231
        float v145 = v142 - v144;	// L232
        float v146 = x5;	// L233
        float v147 = v146 / 120.000000;	// L236
        float v148 = v145 + v147;	// L237
        float v149 = x7;	// L238
        float v150 = v149 / 5040.000000;	// L241
        float v151 = v148 - v150;	// L242
        float v152 = x9;	// L243
        float v153 = v152 / 362880.000000;	// L246
        float v154 = v151 + v153;	// L247
        float v155 = x11;	// L248
        float v156 = v155 / 39916800.000000;	// L251
        float v157 = v154 - v156;	// L252
        float v158 = x13;	// L253
        float v159 = v158 / 6227020800.000000;	// L256
        float v160 = v157 + v159;	// L257
        float v161 = x15;	// L258
        float v162 = v161 / 1307674411008.000000;	// L261
        float v163 = v160 - v162;	// L262
        float sin_a;	// L263
        sin_a = v163;	// L264
        int v165 = base;	// L265
        int v166 = v165;	// L266
        int v167 = v52;	// L267
        int v168 = v166 + v167;	// L268
        int v169 = v168;	// L269
        int idx1;	// L270
        idx1 = v169;	// L271
        int v171 = base;	// L272
        int v172 = v171;	// L273
        int v173 = v172 + v167;	// L275
        int v174 = half;	// L276
        int v175 = v173;	// L277
        int v176 = v174;	// L278
        int v177 = v175 + v176;	// L279
        int v178 = v177;	// L280
        int idx2;	// L281
        idx2 = v178;	// L282
        int v180 = idx2;	// L283
        int v181 = v180;	// L284
        float v182 = v2[v181];	// L285
        float v_real;	// L286
        v_real = v182;	// L287
        int v184 = idx2;	// L288
        int v185 = v184;	// L289
        float v186 = v3[v185];	// L290
        float v_imag;	// L291
        v_imag = v186;	// L292
        float v188 = v_real;	// L293
        float v189 = cos_a;	// L294
        float v190 = v188 * v189;	// L295
        float v191 = v_imag;	// L296
        float v192 = sin_a;	// L297
        float v193 = v191 * v192;	// L298
        float v194 = v190 - v193;	// L299
        float t_real;	// L300
        t_real = v194;	// L301
        float v196 = v_real;	// L302
        float v197 = sin_a;	// L303
        float v198 = v196 * v197;	// L304
        float v199 = v_imag;	// L305
        float v200 = cos_a;	// L306
        float v201 = v199 * v200;	// L307
        float v202 = v198 + v201;	// L308
        float t_imag;	// L309
        t_imag = v202;	// L310
        int v204 = idx1;	// L311
        int v205 = v204;	// L312
        float v206 = v2[v205];	// L313
        float u_real;	// L314
        u_real = v206;	// L315
        int v208 = idx1;	// L316
        int v209 = v208;	// L317
        float v210 = v3[v209];	// L318
        float u_imag;	// L319
        u_imag = v210;	// L320
        float v212 = u_real;	// L321
        float v213 = t_real;	// L322
        float v214 = v212 + v213;	// L323
        int v215 = idx1;	// L324
        int v216 = v215;	// L325
        v2[v216] = v214;	// L326
        float v217 = u_imag;	// L327
        float v218 = t_imag;	// L328
        float v219 = v217 + v218;	// L329
        int v220 = idx1;	// L330
        int v221 = v220;	// L331
        v3[v221] = v219;	// L332
        float v222 = u_real;	// L333
        float v223 = t_real;	// L334
        float v224 = v222 - v223;	// L335
        int v225 = idx2;	// L336
        int v226 = v225;	// L337
        v2[v226] = v224;	// L338
        float v227 = u_imag;	// L339
        float v228 = t_imag;	// L340
        float v229 = v227 - v228;	// L341
        int v230 = idx2;	// L342
        int v231 = v230;	// L343
        v3[v231] = v229;	// L344
      }
    }
  }
}
#pragma pocc-region-end
}

