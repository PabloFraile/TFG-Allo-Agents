
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
  #pragma HLS array_partition variable=v2 cyclic dim=1 factor=4

  #pragma HLS array_partition variable=v3 cyclic dim=1 factor=4

  float twiddle_real[512];	// L4
  #pragma HLS array_partition variable=twiddle_real cyclic dim=1 factor=4

  float twiddle_imag[512];	// L5
  #pragma HLS array_partition variable=twiddle_imag cyclic dim=1 factor=4

  float NEG_TWO_PI;	// L8
  NEG_TWO_PI = -6.283185;	// L9
  l_S_k_0_k: for (int k = 0; k < 512; k++) {	// L10
  #pragma HLS pipeline II=20
    int v8 = k;	// L11
    float v9 = v8;	// L12
    float k_f;	// L13
    k_f = v9;	// L14
    float v11 = NEG_TWO_PI;	// L15
    float v12 = k_f;	// L16
    float v13 = v11 * v12;	// L17
    float v14 = v13 / 1024.000000;	// L19
    float ang;	// L20
    ang = v14;	// L21
    float v16 = ang;	// L22
    float v17 = v16 * v16;	// L23
    float x2;	// L24
    x2 = v17;	// L25
    float v19 = x2;	// L26
    float v20 = ang;	// L27
    float v21 = v19 * v20;	// L28
    float x3;	// L29
    x3 = v21;	// L30
    float v23 = x2;	// L31
    float v24 = v23 * v23;	// L32
    float x4;	// L33
    x4 = v24;	// L34
    float v26 = x4;	// L35
    float v27 = ang;	// L36
    float v28 = v26 * v27;	// L37
    float x5;	// L38
    x5 = v28;	// L39
    float v30 = x4;	// L40
    float v31 = x2;	// L41
    float v32 = v30 * v31;	// L42
    float x6;	// L43
    x6 = v32;	// L44
    float v34 = x6;	// L45
    float v35 = ang;	// L46
    float v36 = v34 * v35;	// L47
    float x7;	// L48
    x7 = v36;	// L49
    float v38 = x4;	// L50
    float v39 = v38 * v38;	// L51
    float x8;	// L52
    x8 = v39;	// L53
    float v41 = x8;	// L54
    float v42 = ang;	// L55
    float v43 = v41 * v42;	// L56
    float x9;	// L57
    x9 = v43;	// L58
    float v45 = x8;	// L59
    float v46 = x2;	// L60
    float v47 = v45 * v46;	// L61
    float x10;	// L62
    x10 = v47;	// L63
    float v49 = x10;	// L64
    float v50 = ang;	// L65
    float v51 = v49 * v50;	// L66
    float x11;	// L67
    x11 = v51;	// L68
    float v53 = x8;	// L69
    float v54 = x4;	// L70
    float v55 = v53 * v54;	// L71
    float x12;	// L72
    x12 = v55;	// L73
    float v57 = x12;	// L74
    float v58 = ang;	// L75
    float v59 = v57 * v58;	// L76
    float x13;	// L77
    x13 = v59;	// L78
    float v61 = x8;	// L79
    float v62 = x6;	// L80
    float v63 = v61 * v62;	// L81
    float x14;	// L82
    x14 = v63;	// L83
    float v65 = x14;	// L84
    float v66 = ang;	// L85
    float v67 = v65 * v66;	// L86
    float x15;	// L87
    x15 = v67;	// L88
    float v69 = x8;	// L89
    float v70 = v69 * v69;	// L90
    float x16;	// L91
    x16 = v70;	// L92
    float v72 = x2;	// L93
    float v73 = v72 / 2.000000;	// L95
    float v74 = 1.000000 - v73;	// L97
    float v75 = x4;	// L98
    float v76 = v75 / 24.000000;	// L100
    float v77 = v74 + v76;	// L101
    float v78 = x6;	// L102
    float v79 = v78 / 720.000000;	// L104
    float v80 = v77 - v79;	// L105
    float v81 = x8;	// L106
    float v82 = v81 / 40320.000000;	// L108
    float v83 = v80 + v82;	// L109
    float v84 = x10;	// L110
    float v85 = v84 / 3628800.000000;	// L112
    float v86 = v83 - v85;	// L113
    float v87 = x12;	// L114
    float v88 = v87 / 479001600.000000;	// L116
    float v89 = v86 + v88;	// L117
    float v90 = x14;	// L118
    float v91 = v90 / 87178289152.000000;	// L120
    float v92 = v89 - v91;	// L121
    float v93 = x16;	// L122
    float v94 = v93 / 20922790576128.000000;	// L124
    float v95 = v92 + v94;	// L125
    float cos_val;	// L126
    cos_val = v95;	// L127
    float v97 = ang;	// L128
    float v98 = x3;	// L129
    float v99 = v98 / 6.000000;	// L131
    float v100 = v97 - v99;	// L132
    float v101 = x5;	// L133
    float v102 = v101 / 120.000000;	// L135
    float v103 = v100 + v102;	// L136
    float v104 = x7;	// L137
    float v105 = v104 / 5040.000000;	// L139
    float v106 = v103 - v105;	// L140
    float v107 = x9;	// L141
    float v108 = v107 / 362880.000000;	// L143
    float v109 = v106 + v108;	// L144
    float v110 = x11;	// L145
    float v111 = v110 / 39916800.000000;	// L147
    float v112 = v109 - v111;	// L148
    float v113 = x13;	// L149
    float v114 = v113 / 6227020800.000000;	// L151
    float v115 = v112 + v114;	// L152
    float v116 = x15;	// L153
    float v117 = v116 / 1307674411008.000000;	// L155
    float v118 = v115 - v117;	// L156
    float sin_val;	// L157
    sin_val = v118;	// L158
    float v120 = cos_val;	// L159
    twiddle_real[k] = v120;	// L160
    float v121 = sin_val;	// L161
    twiddle_imag[k] = v121;	// L162
  }
  l_S_i_1_i: for (int i = 0; i < 1024; i++) {	// L164
  #pragma HLS pipeline II=20
    int v123 = i;	// L165
    int idx;	// L166
    idx = v123;	// L167
    int rev;	// L169
    rev = 0;	// L170
    l_S_b_1_b: for (int b = 0; b < 10; b++) {	// L171
      int v127 = idx;	// L172
      int v128 = v127 / 2;	// L174
      int half_idx;	// L175
      half_idx = v128;	// L176
      int v130 = idx;	// L177
      int v131 = half_idx;	// L178
      int v132 = v131;	// L179
      int v133 = v132  << 1;	// L181
      int v134 = v130;	// L182
      int v135 = v133;	// L183
      int v136 = v134 - v135;	// L184
      int v137 = v136;	// L185
      int bit;	// L186
      bit = v137;	// L187
      int v139 = half_idx;	// L188
      idx = v139;	// L189
      int v140 = rev;	// L190
      int v141 = v140;	// L191
      int v142 = v141  << 1;	// L192
      int v143 = bit;	// L193
      int v144 = v142;	// L194
      int v145 = v143;	// L195
      int v146 = v144 + v145;	// L196
      int v147 = v146;	// L197
      rev = v147;	// L198
    }
    float v148 = v0[i];	// L200
    int v149 = rev;	// L201
    int v150 = v149;	// L202
    v2[v150] = v148;	// L203
    float v151 = v1[i];	// L204
    int v152 = rev;	// L205
    int v153 = v152;	// L206
    v3[v153] = v151;	// L207
  }
  l_S_g1_3_g1: for (int g1 = 0; g1 < 512; g1++) {	// L209
  #pragma HLS pipeline II=20
    int v155 = g1;	// L210
    int v156 = v155  << 1;	// L213
    int v157 = v156;	// L214
    int base_1;	// L215
    base_1 = v157;	// L216
    l_S_j1_3_j1: for (int j1 = 0; j1 < 1; j1++) {	// L217
      int v160 = base_1;	// L218
      int v161 = v160;	// L219
      int v162 = j1;	// L220
      int v163 = v161 + v162;	// L221
      int v164 = v163;	// L222
      int idx1_1;	// L223
      idx1_1 = v164;	// L224
      int v166 = idx1_1;	// L225
      int v167 = v166;	// L226
      int v168 = v167 + 1;	// L229
      int v169 = v168;	// L230
      int idx2_1;	// L231
      idx2_1 = v169;	// L232
      int v171 = j1;	// L233
      int v172 = v171 * 512;	// L236
      int v173 = v172;	// L237
      int tw_idx_1;	// L238
      tw_idx_1 = v173;	// L239
      int v175 = tw_idx_1;	// L240
      int v176 = v175;	// L241
      float v177 = twiddle_real[v176];	// L242
      float tr_1;	// L243
      tr_1 = v177;	// L244
      int v179 = tw_idx_1;	// L245
      int v180 = v179;	// L246
      float v181 = twiddle_imag[v180];	// L247
      float ti_1;	// L248
      ti_1 = v181;	// L249
      int v183 = idx1_1;	// L250
      int v184 = v183;	// L251
      float v185 = v2[v184];	// L252
      float ur_1;	// L253
      ur_1 = v185;	// L254
      int v187 = idx1_1;	// L255
      int v188 = v187;	// L256
      float v189 = v3[v188];	// L257
      float ui_1;	// L258
      ui_1 = v189;	// L259
      int v191 = idx2_1;	// L260
      int v192 = v191;	// L261
      float v193 = v2[v192];	// L262
      float vr_1;	// L263
      vr_1 = v193;	// L264
      int v195 = idx2_1;	// L265
      int v196 = v195;	// L266
      float v197 = v3[v196];	// L267
      float vi_1;	// L268
      vi_1 = v197;	// L269
      float v199 = tr_1;	// L270
      float v200 = vr_1;	// L271
      float v201 = v199 * v200;	// L272
      float v202 = ti_1;	// L273
      float v203 = vi_1;	// L274
      float v204 = v202 * v203;	// L275
      float v205 = v201 - v204;	// L276
      float trv_1;	// L277
      trv_1 = v205;	// L278
      float v207 = tr_1;	// L279
      float v208 = vi_1;	// L280
      float v209 = v207 * v208;	// L281
      float v210 = ti_1;	// L282
      float v211 = vr_1;	// L283
      float v212 = v210 * v211;	// L284
      float v213 = v209 + v212;	// L285
      float tiv_1;	// L286
      tiv_1 = v213;	// L287
      float v215 = ur_1;	// L288
      float v216 = trv_1;	// L289
      float v217 = v215 + v216;	// L290
      int v218 = idx1_1;	// L291
      int v219 = v218;	// L292
      v2[v219] = v217;	// L293
      float v220 = ui_1;	// L294
      float v221 = tiv_1;	// L295
      float v222 = v220 + v221;	// L296
      int v223 = idx1_1;	// L297
      int v224 = v223;	// L298
      v3[v224] = v222;	// L299
      float v225 = ur_1;	// L300
      float v226 = trv_1;	// L301
      float v227 = v225 - v226;	// L302
      int v228 = idx2_1;	// L303
      int v229 = v228;	// L304
      v2[v229] = v227;	// L305
      float v230 = ui_1;	// L306
      float v231 = tiv_1;	// L307
      float v232 = v230 - v231;	// L308
      int v233 = idx2_1;	// L309
      int v234 = v233;	// L310
      v3[v234] = v232;	// L311
    }
  }
  l_S_g2_5_g2: for (int g2 = 0; g2 < 256; g2++) {	// L314
  #pragma HLS pipeline II=20
    int v236 = g2;	// L315
    int v237 = v236 * 4;	// L318
    int v238 = v237;	// L319
    int base_2;	// L320
    base_2 = v238;	// L321
    l_S_j2_5_j2: for (int j2 = 0; j2 < 2; j2++) {	// L322
      int v241 = base_2;	// L323
      int v242 = v241;	// L324
      int v243 = j2;	// L325
      int v244 = v242 + v243;	// L326
      int v245 = v244;	// L327
      int idx1_2;	// L328
      idx1_2 = v245;	// L329
      int v247 = idx1_2;	// L330
      int v248 = v247;	// L331
      int v249 = v248 + 2;	// L334
      int v250 = v249;	// L335
      int idx2_2;	// L336
      idx2_2 = v250;	// L337
      int v252 = j2;	// L338
      int v253 = v252 * 256;	// L341
      int v254 = v253;	// L342
      int tw_idx_2;	// L343
      tw_idx_2 = v254;	// L344
      int v256 = tw_idx_2;	// L345
      int v257 = v256;	// L346
      float v258 = twiddle_real[v257];	// L347
      float tr_2;	// L348
      tr_2 = v258;	// L349
      int v260 = tw_idx_2;	// L350
      int v261 = v260;	// L351
      float v262 = twiddle_imag[v261];	// L352
      float ti_2;	// L353
      ti_2 = v262;	// L354
      int v264 = idx1_2;	// L355
      int v265 = v264;	// L356
      float v266 = v2[v265];	// L357
      float ur_2;	// L358
      ur_2 = v266;	// L359
      int v268 = idx1_2;	// L360
      int v269 = v268;	// L361
      float v270 = v3[v269];	// L362
      float ui_2;	// L363
      ui_2 = v270;	// L364
      int v272 = idx2_2;	// L365
      int v273 = v272;	// L366
      float v274 = v2[v273];	// L367
      float vr_2;	// L368
      vr_2 = v274;	// L369
      int v276 = idx2_2;	// L370
      int v277 = v276;	// L371
      float v278 = v3[v277];	// L372
      float vi_2;	// L373
      vi_2 = v278;	// L374
      float v280 = tr_2;	// L375
      float v281 = vr_2;	// L376
      float v282 = v280 * v281;	// L377
      float v283 = ti_2;	// L378
      float v284 = vi_2;	// L379
      float v285 = v283 * v284;	// L380
      float v286 = v282 - v285;	// L381
      float trv_2;	// L382
      trv_2 = v286;	// L383
      float v288 = tr_2;	// L384
      float v289 = vi_2;	// L385
      float v290 = v288 * v289;	// L386
      float v291 = ti_2;	// L387
      float v292 = vr_2;	// L388
      float v293 = v291 * v292;	// L389
      float v294 = v290 + v293;	// L390
      float tiv_2;	// L391
      tiv_2 = v294;	// L392
      float v296 = ur_2;	// L393
      float v297 = trv_2;	// L394
      float v298 = v296 + v297;	// L395
      int v299 = idx1_2;	// L396
      int v300 = v299;	// L397
      v2[v300] = v298;	// L398
      float v301 = ui_2;	// L399
      float v302 = tiv_2;	// L400
      float v303 = v301 + v302;	// L401
      int v304 = idx1_2;	// L402
      int v305 = v304;	// L403
      v3[v305] = v303;	// L404
      float v306 = ur_2;	// L405
      float v307 = trv_2;	// L406
      float v308 = v306 - v307;	// L407
      int v309 = idx2_2;	// L408
      int v310 = v309;	// L409
      v2[v310] = v308;	// L410
      float v311 = ui_2;	// L411
      float v312 = tiv_2;	// L412
      float v313 = v311 - v312;	// L413
      int v314 = idx2_2;	// L414
      int v315 = v314;	// L415
      v3[v315] = v313;	// L416
    }
  }
  l_S_g3_7_g3: for (int g3 = 0; g3 < 128; g3++) {	// L419
  #pragma HLS pipeline II=20
    int v317 = g3;	// L420
    int v318 = v317 * 8;	// L423
    int v319 = v318;	// L424
    int base_3;	// L425
    base_3 = v319;	// L426
    l_S_j3_7_j3: for (int j3 = 0; j3 < 4; j3++) {	// L427
      int v322 = base_3;	// L428
      int v323 = v322;	// L429
      int v324 = j3;	// L430
      int v325 = v323 + v324;	// L431
      int v326 = v325;	// L432
      int idx1_3;	// L433
      idx1_3 = v326;	// L434
      int v328 = idx1_3;	// L435
      int v329 = v328;	// L436
      int v330 = v329 + 4;	// L439
      int v331 = v330;	// L440
      int idx2_3;	// L441
      idx2_3 = v331;	// L442
      int v333 = j3;	// L443
      int v334 = v333 * 128;	// L446
      int v335 = v334;	// L447
      int tw_idx_3;	// L448
      tw_idx_3 = v335;	// L449
      int v337 = tw_idx_3;	// L450
      int v338 = v337;	// L451
      float v339 = twiddle_real[v338];	// L452
      float tr_3;	// L453
      tr_3 = v339;	// L454
      int v341 = tw_idx_3;	// L455
      int v342 = v341;	// L456
      float v343 = twiddle_imag[v342];	// L457
      float ti_3;	// L458
      ti_3 = v343;	// L459
      int v345 = idx1_3;	// L460
      int v346 = v345;	// L461
      float v347 = v2[v346];	// L462
      float ur_3;	// L463
      ur_3 = v347;	// L464
      int v349 = idx1_3;	// L465
      int v350 = v349;	// L466
      float v351 = v3[v350];	// L467
      float ui_3;	// L468
      ui_3 = v351;	// L469
      int v353 = idx2_3;	// L470
      int v354 = v353;	// L471
      float v355 = v2[v354];	// L472
      float vr_3;	// L473
      vr_3 = v355;	// L474
      int v357 = idx2_3;	// L475
      int v358 = v357;	// L476
      float v359 = v3[v358];	// L477
      float vi_3;	// L478
      vi_3 = v359;	// L479
      float v361 = tr_3;	// L480
      float v362 = vr_3;	// L481
      float v363 = v361 * v362;	// L482
      float v364 = ti_3;	// L483
      float v365 = vi_3;	// L484
      float v366 = v364 * v365;	// L485
      float v367 = v363 - v366;	// L486
      float trv_3;	// L487
      trv_3 = v367;	// L488
      float v369 = tr_3;	// L489
      float v370 = vi_3;	// L490
      float v371 = v369 * v370;	// L491
      float v372 = ti_3;	// L492
      float v373 = vr_3;	// L493
      float v374 = v372 * v373;	// L494
      float v375 = v371 + v374;	// L495
      float tiv_3;	// L496
      tiv_3 = v375;	// L497
      float v377 = ur_3;	// L498
      float v378 = trv_3;	// L499
      float v379 = v377 + v378;	// L500
      int v380 = idx1_3;	// L501
      int v381 = v380;	// L502
      v2[v381] = v379;	// L503
      float v382 = ui_3;	// L504
      float v383 = tiv_3;	// L505
      float v384 = v382 + v383;	// L506
      int v385 = idx1_3;	// L507
      int v386 = v385;	// L508
      v3[v386] = v384;	// L509
      float v387 = ur_3;	// L510
      float v388 = trv_3;	// L511
      float v389 = v387 - v388;	// L512
      int v390 = idx2_3;	// L513
      int v391 = v390;	// L514
      v2[v391] = v389;	// L515
      float v392 = ui_3;	// L516
      float v393 = tiv_3;	// L517
      float v394 = v392 - v393;	// L518
      int v395 = idx2_3;	// L519
      int v396 = v395;	// L520
      v3[v396] = v394;	// L521
    }
  }
  l_S_g4_9_g4: for (int g4 = 0; g4 < 64; g4++) {	// L524
  #pragma HLS pipeline II=20
    int v398 = g4;	// L525
    int v399 = v398 * 16;	// L528
    int v400 = v399;	// L529
    int base_4;	// L530
    base_4 = v400;	// L531
    l_S_j4_9_j4: for (int j4 = 0; j4 < 8; j4++) {	// L532
      int v403 = base_4;	// L533
      int v404 = v403;	// L534
      int v405 = j4;	// L535
      int v406 = v404 + v405;	// L536
      int v407 = v406;	// L537
      int idx1_4;	// L538
      idx1_4 = v407;	// L539
      int v409 = idx1_4;	// L540
      int v410 = v409;	// L541
      int v411 = v410 + 8;	// L544
      int v412 = v411;	// L545
      int idx2_4;	// L546
      idx2_4 = v412;	// L547
      int v414 = j4;	// L548
      int v415 = v414 * 64;	// L551
      int v416 = v415;	// L552
      int tw_idx_4;	// L553
      tw_idx_4 = v416;	// L554
      int v418 = tw_idx_4;	// L555
      int v419 = v418;	// L556
      float v420 = twiddle_real[v419];	// L557
      float tr_4;	// L558
      tr_4 = v420;	// L559
      int v422 = tw_idx_4;	// L560
      int v423 = v422;	// L561
      float v424 = twiddle_imag[v423];	// L562
      float ti_4;	// L563
      ti_4 = v424;	// L564
      int v426 = idx1_4;	// L565
      int v427 = v426;	// L566
      float v428 = v2[v427];	// L567
      float ur_4;	// L568
      ur_4 = v428;	// L569
      int v430 = idx1_4;	// L570
      int v431 = v430;	// L571
      float v432 = v3[v431];	// L572
      float ui_4;	// L573
      ui_4 = v432;	// L574
      int v434 = idx2_4;	// L575
      int v435 = v434;	// L576
      float v436 = v2[v435];	// L577
      float vr_4;	// L578
      vr_4 = v436;	// L579
      int v438 = idx2_4;	// L580
      int v439 = v438;	// L581
      float v440 = v3[v439];	// L582
      float vi_4;	// L583
      vi_4 = v440;	// L584
      float v442 = tr_4;	// L585
      float v443 = vr_4;	// L586
      float v444 = v442 * v443;	// L587
      float v445 = ti_4;	// L588
      float v446 = vi_4;	// L589
      float v447 = v445 * v446;	// L590
      float v448 = v444 - v447;	// L591
      float trv_4;	// L592
      trv_4 = v448;	// L593
      float v450 = tr_4;	// L594
      float v451 = vi_4;	// L595
      float v452 = v450 * v451;	// L596
      float v453 = ti_4;	// L597
      float v454 = vr_4;	// L598
      float v455 = v453 * v454;	// L599
      float v456 = v452 + v455;	// L600
      float tiv_4;	// L601
      tiv_4 = v456;	// L602
      float v458 = ur_4;	// L603
      float v459 = trv_4;	// L604
      float v460 = v458 + v459;	// L605
      int v461 = idx1_4;	// L606
      int v462 = v461;	// L607
      v2[v462] = v460;	// L608
      float v463 = ui_4;	// L609
      float v464 = tiv_4;	// L610
      float v465 = v463 + v464;	// L611
      int v466 = idx1_4;	// L612
      int v467 = v466;	// L613
      v3[v467] = v465;	// L614
      float v468 = ur_4;	// L615
      float v469 = trv_4;	// L616
      float v470 = v468 - v469;	// L617
      int v471 = idx2_4;	// L618
      int v472 = v471;	// L619
      v2[v472] = v470;	// L620
      float v473 = ui_4;	// L621
      float v474 = tiv_4;	// L622
      float v475 = v473 - v474;	// L623
      int v476 = idx2_4;	// L624
      int v477 = v476;	// L625
      v3[v477] = v475;	// L626
    }
  }
  l_S_g5_11_g5: for (int g5 = 0; g5 < 32; g5++) {	// L629
  #pragma HLS pipeline II=20
    int v479 = g5;	// L630
    int v480 = v479 * 32;	// L633
    int v481 = v480;	// L634
    int base_5;	// L635
    base_5 = v481;	// L636
    l_S_j5_11_j5: for (int j5 = 0; j5 < 16; j5++) {	// L637
      int v484 = base_5;	// L638
      int v485 = v484;	// L639
      int v486 = j5;	// L640
      int v487 = v485 + v486;	// L641
      int v488 = v487;	// L642
      int idx1_5;	// L643
      idx1_5 = v488;	// L644
      int v490 = idx1_5;	// L645
      int v491 = v490;	// L646
      int v492 = v491 + 16;	// L649
      int v493 = v492;	// L650
      int idx2_5;	// L651
      idx2_5 = v493;	// L652
      int v495 = j5;	// L653
      int v496 = v495 * 32;	// L654
      int v497 = v496;	// L655
      int tw_idx_5;	// L656
      tw_idx_5 = v497;	// L657
      int v499 = tw_idx_5;	// L658
      int v500 = v499;	// L659
      float v501 = twiddle_real[v500];	// L660
      float tr_5;	// L661
      tr_5 = v501;	// L662
      int v503 = tw_idx_5;	// L663
      int v504 = v503;	// L664
      float v505 = twiddle_imag[v504];	// L665
      float ti_5;	// L666
      ti_5 = v505;	// L667
      int v507 = idx1_5;	// L668
      int v508 = v507;	// L669
      float v509 = v2[v508];	// L670
      float ur_5;	// L671
      ur_5 = v509;	// L672
      int v511 = idx1_5;	// L673
      int v512 = v511;	// L674
      float v513 = v3[v512];	// L675
      float ui_5;	// L676
      ui_5 = v513;	// L677
      int v515 = idx2_5;	// L678
      int v516 = v515;	// L679
      float v517 = v2[v516];	// L680
      float vr_5;	// L681
      vr_5 = v517;	// L682
      int v519 = idx2_5;	// L683
      int v520 = v519;	// L684
      float v521 = v3[v520];	// L685
      float vi_5;	// L686
      vi_5 = v521;	// L687
      float v523 = tr_5;	// L688
      float v524 = vr_5;	// L689
      float v525 = v523 * v524;	// L690
      float v526 = ti_5;	// L691
      float v527 = vi_5;	// L692
      float v528 = v526 * v527;	// L693
      float v529 = v525 - v528;	// L694
      float trv_5;	// L695
      trv_5 = v529;	// L696
      float v531 = tr_5;	// L697
      float v532 = vi_5;	// L698
      float v533 = v531 * v532;	// L699
      float v534 = ti_5;	// L700
      float v535 = vr_5;	// L701
      float v536 = v534 * v535;	// L702
      float v537 = v533 + v536;	// L703
      float tiv_5;	// L704
      tiv_5 = v537;	// L705
      float v539 = ur_5;	// L706
      float v540 = trv_5;	// L707
      float v541 = v539 + v540;	// L708
      int v542 = idx1_5;	// L709
      int v543 = v542;	// L710
      v2[v543] = v541;	// L711
      float v544 = ui_5;	// L712
      float v545 = tiv_5;	// L713
      float v546 = v544 + v545;	// L714
      int v547 = idx1_5;	// L715
      int v548 = v547;	// L716
      v3[v548] = v546;	// L717
      float v549 = ur_5;	// L718
      float v550 = trv_5;	// L719
      float v551 = v549 - v550;	// L720
      int v552 = idx2_5;	// L721
      int v553 = v552;	// L722
      v2[v553] = v551;	// L723
      float v554 = ui_5;	// L724
      float v555 = tiv_5;	// L725
      float v556 = v554 - v555;	// L726
      int v557 = idx2_5;	// L727
      int v558 = v557;	// L728
      v3[v558] = v556;	// L729
    }
  }
  l_S_g6_13_g6: for (int g6 = 0; g6 < 16; g6++) {	// L732
    int v560 = g6;	// L733
    int v561 = v560 * 64;	// L736
    int v562 = v561;	// L737
    int base_6;	// L738
    base_6 = v562;	// L739
    l_S_j6_13_j6: for (int j6 = 0; j6 < 32; j6++) {	// L740
    #pragma HLS pipeline II=20
      int v565 = base_6;	// L741
      int v566 = v565;	// L742
      int v567 = j6;	// L743
      int v568 = v566 + v567;	// L744
      int v569 = v568;	// L745
      int idx1_6;	// L746
      idx1_6 = v569;	// L747
      int v571 = idx1_6;	// L748
      int v572 = v571;	// L749
      int v573 = v572 + 32;	// L752
      int v574 = v573;	// L753
      int idx2_6;	// L754
      idx2_6 = v574;	// L755
      int v576 = j6;	// L756
      int v577 = v576 * 16;	// L759
      int v578 = v577;	// L760
      int tw_idx_6;	// L761
      tw_idx_6 = v578;	// L762
      int v580 = tw_idx_6;	// L763
      int v581 = v580;	// L764
      float v582 = twiddle_real[v581];	// L765
      float tr_6;	// L766
      tr_6 = v582;	// L767
      int v584 = tw_idx_6;	// L768
      int v585 = v584;	// L769
      float v586 = twiddle_imag[v585];	// L770
      float ti_6;	// L771
      ti_6 = v586;	// L772
      int v588 = idx1_6;	// L773
      int v589 = v588;	// L774
      float v590 = v2[v589];	// L775
      float ur_6;	// L776
      ur_6 = v590;	// L777
      int v592 = idx1_6;	// L778
      int v593 = v592;	// L779
      float v594 = v3[v593];	// L780
      float ui_6;	// L781
      ui_6 = v594;	// L782
      int v596 = idx2_6;	// L783
      int v597 = v596;	// L784
      float v598 = v2[v597];	// L785
      float vr_6;	// L786
      vr_6 = v598;	// L787
      int v600 = idx2_6;	// L788
      int v601 = v600;	// L789
      float v602 = v3[v601];	// L790
      float vi_6;	// L791
      vi_6 = v602;	// L792
      float v604 = tr_6;	// L793
      float v605 = vr_6;	// L794
      float v606 = v604 * v605;	// L795
      float v607 = ti_6;	// L796
      float v608 = vi_6;	// L797
      float v609 = v607 * v608;	// L798
      float v610 = v606 - v609;	// L799
      float trv_6;	// L800
      trv_6 = v610;	// L801
      float v612 = tr_6;	// L802
      float v613 = vi_6;	// L803
      float v614 = v612 * v613;	// L804
      float v615 = ti_6;	// L805
      float v616 = vr_6;	// L806
      float v617 = v615 * v616;	// L807
      float v618 = v614 + v617;	// L808
      float tiv_6;	// L809
      tiv_6 = v618;	// L810
      float v620 = ur_6;	// L811
      float v621 = trv_6;	// L812
      float v622 = v620 + v621;	// L813
      int v623 = idx1_6;	// L814
      int v624 = v623;	// L815
      v2[v624] = v622;	// L816
      float v625 = ui_6;	// L817
      float v626 = tiv_6;	// L818
      float v627 = v625 + v626;	// L819
      int v628 = idx1_6;	// L820
      int v629 = v628;	// L821
      v3[v629] = v627;	// L822
      float v630 = ur_6;	// L823
      float v631 = trv_6;	// L824
      float v632 = v630 - v631;	// L825
      int v633 = idx2_6;	// L826
      int v634 = v633;	// L827
      v2[v634] = v632;	// L828
      float v635 = ui_6;	// L829
      float v636 = tiv_6;	// L830
      float v637 = v635 - v636;	// L831
      int v638 = idx2_6;	// L832
      int v639 = v638;	// L833
      v3[v639] = v637;	// L834
    }
  }
  l_S_g7_15_g7: for (int g7 = 0; g7 < 8; g7++) {	// L837
    int v641 = g7;	// L838
    int v642 = v641 * 128;	// L841
    int v643 = v642;	// L842
    int base_7;	// L843
    base_7 = v643;	// L844
    l_S_j7_15_j7: for (int j7 = 0; j7 < 64; j7++) {	// L845
    #pragma HLS pipeline II=20
      int v646 = base_7;	// L846
      int v647 = v646;	// L847
      int v648 = j7;	// L848
      int v649 = v647 + v648;	// L849
      int v650 = v649;	// L850
      int idx1_7;	// L851
      idx1_7 = v650;	// L852
      int v652 = idx1_7;	// L853
      int v653 = v652;	// L854
      int v654 = v653 + 64;	// L857
      int v655 = v654;	// L858
      int idx2_7;	// L859
      idx2_7 = v655;	// L860
      int v657 = j7;	// L861
      int v658 = v657 * 8;	// L864
      int v659 = v658;	// L865
      int tw_idx_7;	// L866
      tw_idx_7 = v659;	// L867
      int v661 = tw_idx_7;	// L868
      int v662 = v661;	// L869
      float v663 = twiddle_real[v662];	// L870
      float tr_7;	// L871
      tr_7 = v663;	// L872
      int v665 = tw_idx_7;	// L873
      int v666 = v665;	// L874
      float v667 = twiddle_imag[v666];	// L875
      float ti_7;	// L876
      ti_7 = v667;	// L877
      int v669 = idx1_7;	// L878
      int v670 = v669;	// L879
      float v671 = v2[v670];	// L880
      float ur_7;	// L881
      ur_7 = v671;	// L882
      int v673 = idx1_7;	// L883
      int v674 = v673;	// L884
      float v675 = v3[v674];	// L885
      float ui_7;	// L886
      ui_7 = v675;	// L887
      int v677 = idx2_7;	// L888
      int v678 = v677;	// L889
      float v679 = v2[v678];	// L890
      float vr_7;	// L891
      vr_7 = v679;	// L892
      int v681 = idx2_7;	// L893
      int v682 = v681;	// L894
      float v683 = v3[v682];	// L895
      float vi_7;	// L896
      vi_7 = v683;	// L897
      float v685 = tr_7;	// L898
      float v686 = vr_7;	// L899
      float v687 = v685 * v686;	// L900
      float v688 = ti_7;	// L901
      float v689 = vi_7;	// L902
      float v690 = v688 * v689;	// L903
      float v691 = v687 - v690;	// L904
      float trv_7;	// L905
      trv_7 = v691;	// L906
      float v693 = tr_7;	// L907
      float v694 = vi_7;	// L908
      float v695 = v693 * v694;	// L909
      float v696 = ti_7;	// L910
      float v697 = vr_7;	// L911
      float v698 = v696 * v697;	// L912
      float v699 = v695 + v698;	// L913
      float tiv_7;	// L914
      tiv_7 = v699;	// L915
      float v701 = ur_7;	// L916
      float v702 = trv_7;	// L917
      float v703 = v701 + v702;	// L918
      int v704 = idx1_7;	// L919
      int v705 = v704;	// L920
      v2[v705] = v703;	// L921
      float v706 = ui_7;	// L922
      float v707 = tiv_7;	// L923
      float v708 = v706 + v707;	// L924
      int v709 = idx1_7;	// L925
      int v710 = v709;	// L926
      v3[v710] = v708;	// L927
      float v711 = ur_7;	// L928
      float v712 = trv_7;	// L929
      float v713 = v711 - v712;	// L930
      int v714 = idx2_7;	// L931
      int v715 = v714;	// L932
      v2[v715] = v713;	// L933
      float v716 = ui_7;	// L934
      float v717 = tiv_7;	// L935
      float v718 = v716 - v717;	// L936
      int v719 = idx2_7;	// L937
      int v720 = v719;	// L938
      v3[v720] = v718;	// L939
    }
  }
  l_S_g8_17_g8: for (int g8 = 0; g8 < 4; g8++) {	// L942
    int v722 = g8;	// L943
    int v723 = v722 * 256;	// L946
    int v724 = v723;	// L947
    int base_8;	// L948
    base_8 = v724;	// L949
    l_S_j8_17_j8: for (int j8 = 0; j8 < 128; j8++) {	// L950
    #pragma HLS pipeline II=20
      int v727 = base_8;	// L951
      int v728 = v727;	// L952
      int v729 = j8;	// L953
      int v730 = v728 + v729;	// L954
      int v731 = v730;	// L955
      int idx1_8;	// L956
      idx1_8 = v731;	// L957
      int v733 = idx1_8;	// L958
      int v734 = v733;	// L959
      int v735 = v734 + 128;	// L962
      int v736 = v735;	// L963
      int idx2_8;	// L964
      idx2_8 = v736;	// L965
      int v738 = j8;	// L966
      int v739 = v738 * 4;	// L969
      int v740 = v739;	// L970
      int tw_idx_8;	// L971
      tw_idx_8 = v740;	// L972
      int v742 = tw_idx_8;	// L973
      int v743 = v742;	// L974
      float v744 = twiddle_real[v743];	// L975
      float tr_8;	// L976
      tr_8 = v744;	// L977
      int v746 = tw_idx_8;	// L978
      int v747 = v746;	// L979
      float v748 = twiddle_imag[v747];	// L980
      float ti_8;	// L981
      ti_8 = v748;	// L982
      int v750 = idx1_8;	// L983
      int v751 = v750;	// L984
      float v752 = v2[v751];	// L985
      float ur_8;	// L986
      ur_8 = v752;	// L987
      int v754 = idx1_8;	// L988
      int v755 = v754;	// L989
      float v756 = v3[v755];	// L990
      float ui_8;	// L991
      ui_8 = v756;	// L992
      int v758 = idx2_8;	// L993
      int v759 = v758;	// L994
      float v760 = v2[v759];	// L995
      float vr_8;	// L996
      vr_8 = v760;	// L997
      int v762 = idx2_8;	// L998
      int v763 = v762;	// L999
      float v764 = v3[v763];	// L1000
      float vi_8;	// L1001
      vi_8 = v764;	// L1002
      float v766 = tr_8;	// L1003
      float v767 = vr_8;	// L1004
      float v768 = v766 * v767;	// L1005
      float v769 = ti_8;	// L1006
      float v770 = vi_8;	// L1007
      float v771 = v769 * v770;	// L1008
      float v772 = v768 - v771;	// L1009
      float trv_8;	// L1010
      trv_8 = v772;	// L1011
      float v774 = tr_8;	// L1012
      float v775 = vi_8;	// L1013
      float v776 = v774 * v775;	// L1014
      float v777 = ti_8;	// L1015
      float v778 = vr_8;	// L1016
      float v779 = v777 * v778;	// L1017
      float v780 = v776 + v779;	// L1018
      float tiv_8;	// L1019
      tiv_8 = v780;	// L1020
      float v782 = ur_8;	// L1021
      float v783 = trv_8;	// L1022
      float v784 = v782 + v783;	// L1023
      int v785 = idx1_8;	// L1024
      int v786 = v785;	// L1025
      v2[v786] = v784;	// L1026
      float v787 = ui_8;	// L1027
      float v788 = tiv_8;	// L1028
      float v789 = v787 + v788;	// L1029
      int v790 = idx1_8;	// L1030
      int v791 = v790;	// L1031
      v3[v791] = v789;	// L1032
      float v792 = ur_8;	// L1033
      float v793 = trv_8;	// L1034
      float v794 = v792 - v793;	// L1035
      int v795 = idx2_8;	// L1036
      int v796 = v795;	// L1037
      v2[v796] = v794;	// L1038
      float v797 = ui_8;	// L1039
      float v798 = tiv_8;	// L1040
      float v799 = v797 - v798;	// L1041
      int v800 = idx2_8;	// L1042
      int v801 = v800;	// L1043
      v3[v801] = v799;	// L1044
    }
  }
  l_S_g9_19_g9: for (int g9 = 0; g9 < 2; g9++) {	// L1047
    int v803 = g9;	// L1048
    int v804 = v803 * 512;	// L1051
    int v805 = v804;	// L1052
    int base_9;	// L1053
    base_9 = v805;	// L1054
    l_S_j9_19_j9: for (int j9 = 0; j9 < 256; j9++) {	// L1055
    #pragma HLS pipeline II=20
      int v808 = base_9;	// L1056
      int v809 = v808;	// L1057
      int v810 = j9;	// L1058
      int v811 = v809 + v810;	// L1059
      int v812 = v811;	// L1060
      int idx1_9;	// L1061
      idx1_9 = v812;	// L1062
      int v814 = idx1_9;	// L1063
      int v815 = v814;	// L1064
      int v816 = v815 + 256;	// L1067
      int v817 = v816;	// L1068
      int idx2_9;	// L1069
      idx2_9 = v817;	// L1070
      int v819 = j9;	// L1071
      int v820 = v819  << 1;	// L1074
      int v821 = v820;	// L1075
      int tw_idx_9;	// L1076
      tw_idx_9 = v821;	// L1077
      int v823 = tw_idx_9;	// L1078
      int v824 = v823;	// L1079
      float v825 = twiddle_real[v824];	// L1080
      float tr_9;	// L1081
      tr_9 = v825;	// L1082
      int v827 = tw_idx_9;	// L1083
      int v828 = v827;	// L1084
      float v829 = twiddle_imag[v828];	// L1085
      float ti_9;	// L1086
      ti_9 = v829;	// L1087
      int v831 = idx1_9;	// L1088
      int v832 = v831;	// L1089
      float v833 = v2[v832];	// L1090
      float ur_9;	// L1091
      ur_9 = v833;	// L1092
      int v835 = idx1_9;	// L1093
      int v836 = v835;	// L1094
      float v837 = v3[v836];	// L1095
      float ui_9;	// L1096
      ui_9 = v837;	// L1097
      int v839 = idx2_9;	// L1098
      int v840 = v839;	// L1099
      float v841 = v2[v840];	// L1100
      float vr_9;	// L1101
      vr_9 = v841;	// L1102
      int v843 = idx2_9;	// L1103
      int v844 = v843;	// L1104
      float v845 = v3[v844];	// L1105
      float vi_9;	// L1106
      vi_9 = v845;	// L1107
      float v847 = tr_9;	// L1108
      float v848 = vr_9;	// L1109
      float v849 = v847 * v848;	// L1110
      float v850 = ti_9;	// L1111
      float v851 = vi_9;	// L1112
      float v852 = v850 * v851;	// L1113
      float v853 = v849 - v852;	// L1114
      float trv_9;	// L1115
      trv_9 = v853;	// L1116
      float v855 = tr_9;	// L1117
      float v856 = vi_9;	// L1118
      float v857 = v855 * v856;	// L1119
      float v858 = ti_9;	// L1120
      float v859 = vr_9;	// L1121
      float v860 = v858 * v859;	// L1122
      float v861 = v857 + v860;	// L1123
      float tiv_9;	// L1124
      tiv_9 = v861;	// L1125
      float v863 = ur_9;	// L1126
      float v864 = trv_9;	// L1127
      float v865 = v863 + v864;	// L1128
      int v866 = idx1_9;	// L1129
      int v867 = v866;	// L1130
      v2[v867] = v865;	// L1131
      float v868 = ui_9;	// L1132
      float v869 = tiv_9;	// L1133
      float v870 = v868 + v869;	// L1134
      int v871 = idx1_9;	// L1135
      int v872 = v871;	// L1136
      v3[v872] = v870;	// L1137
      float v873 = ur_9;	// L1138
      float v874 = trv_9;	// L1139
      float v875 = v873 - v874;	// L1140
      int v876 = idx2_9;	// L1141
      int v877 = v876;	// L1142
      v2[v877] = v875;	// L1143
      float v878 = ui_9;	// L1144
      float v879 = tiv_9;	// L1145
      float v880 = v878 - v879;	// L1146
      int v881 = idx2_9;	// L1147
      int v882 = v881;	// L1148
      v3[v882] = v880;	// L1149
    }
  }
  l_S_g10_21_g10: for (int g10 = 0; g10 < 1; g10++) {	// L1152
    int v884 = g10;	// L1153
    int v885 = v884 * 1024;	// L1156
    int v886 = v885;	// L1157
    int base_10;	// L1158
    base_10 = v886;	// L1159
    l_S_j10_21_j10: for (int j10 = 0; j10 < 512; j10++) {	// L1160
    #pragma HLS pipeline II=20
      int v889 = base_10;	// L1161
      int v890 = v889;	// L1162
      int v891 = j10;	// L1163
      int v892 = v890 + v891;	// L1164
      int v893 = v892;	// L1165
      int idx1_10;	// L1166
      idx1_10 = v893;	// L1167
      int v895 = idx1_10;	// L1168
      int v896 = v895;	// L1169
      int v897 = v896 + 512;	// L1172
      int v898 = v897;	// L1173
      int idx2_10;	// L1174
      idx2_10 = v898;	// L1175
      int v900 = j10;	// L1176
      int v901 = v900;	// L1180
      int tw_idx_10;	// L1181
      tw_idx_10 = v901;	// L1182
      int v903 = tw_idx_10;	// L1183
      int v904 = v903;	// L1184
      float v905 = twiddle_real[v904];	// L1185
      float tr_10;	// L1186
      tr_10 = v905;	// L1187
      int v907 = tw_idx_10;	// L1188
      int v908 = v907;	// L1189
      float v909 = twiddle_imag[v908];	// L1190
      float ti_10;	// L1191
      ti_10 = v909;	// L1192
      int v911 = idx1_10;	// L1193
      int v912 = v911;	// L1194
      float v913 = v2[v912];	// L1195
      float ur_10;	// L1196
      ur_10 = v913;	// L1197
      int v915 = idx1_10;	// L1198
      int v916 = v915;	// L1199
      float v917 = v3[v916];	// L1200
      float ui_10;	// L1201
      ui_10 = v917;	// L1202
      int v919 = idx2_10;	// L1203
      int v920 = v919;	// L1204
      float v921 = v2[v920];	// L1205
      float vr_10;	// L1206
      vr_10 = v921;	// L1207
      int v923 = idx2_10;	// L1208
      int v924 = v923;	// L1209
      float v925 = v3[v924];	// L1210
      float vi_10;	// L1211
      vi_10 = v925;	// L1212
      float v927 = tr_10;	// L1213
      float v928 = vr_10;	// L1214
      float v929 = v927 * v928;	// L1215
      float v930 = ti_10;	// L1216
      float v931 = vi_10;	// L1217
      float v932 = v930 * v931;	// L1218
      float v933 = v929 - v932;	// L1219
      float trv_10;	// L1220
      trv_10 = v933;	// L1221
      float v935 = tr_10;	// L1222
      float v936 = vi_10;	// L1223
      float v937 = v935 * v936;	// L1224
      float v938 = ti_10;	// L1225
      float v939 = vr_10;	// L1226
      float v940 = v938 * v939;	// L1227
      float v941 = v937 + v940;	// L1228
      float tiv_10;	// L1229
      tiv_10 = v941;	// L1230
      float v943 = ur_10;	// L1231
      float v944 = trv_10;	// L1232
      float v945 = v943 + v944;	// L1233
      int v946 = idx1_10;	// L1234
      int v947 = v946;	// L1235
      v2[v947] = v945;	// L1236
      float v948 = ui_10;	// L1237
      float v949 = tiv_10;	// L1238
      float v950 = v948 + v949;	// L1239
      int v951 = idx1_10;	// L1240
      int v952 = v951;	// L1241
      v3[v952] = v950;	// L1242
      float v953 = ur_10;	// L1243
      float v954 = trv_10;	// L1244
      float v955 = v953 - v954;	// L1245
      int v956 = idx2_10;	// L1246
      int v957 = v956;	// L1247
      v2[v957] = v955;	// L1248
      float v958 = ui_10;	// L1249
      float v959 = tiv_10;	// L1250
      float v960 = v958 - v959;	// L1251
      int v961 = idx2_10;	// L1252
      int v962 = v961;	// L1253
      v3[v962] = v960;	// L1254
    }
  }
}
#pragma pocc-region-end
}

