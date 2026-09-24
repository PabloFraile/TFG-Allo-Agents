
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
  #pragma HLS array_partition variable=v2 cyclic dim=1 factor=8

  #pragma HLS array_partition variable=v3 cyclic dim=1 factor=8

  l_S_i_0_i: for (int i = 0; i < 1024; i++) {	// L4
  #pragma HLS pipeline II=5
    int v5 = i;	// L5
    int idx;	// L6
    idx = v5;	// L7
    int rev;	// L9
    rev = 0;	// L10
    l_S_b_0_b: for (int b = 0; b < 10; b++) {	// L11
      int v9 = idx;	// L12
      int v10 = v9 / 2;	// L14
      int idx_half;	// L15
      idx_half = v10;	// L16
      int v12 = idx;	// L17
      int v13 = idx_half;	// L18
      int v14 = v13;	// L19
      int v15 = v14  << 1;	// L21
      int v16 = v12;	// L22
      int v17 = v15;	// L23
      int v18 = v16 - v17;	// L24
      int v19 = v18;	// L25
      int bit;	// L26
      bit = v19;	// L27
      int v21 = idx_half;	// L28
      idx = v21;	// L29
      int v22 = rev;	// L30
      int v23 = v22;	// L31
      int v24 = v23  << 1;	// L32
      int v25 = bit;	// L33
      int v26 = v24;	// L34
      int v27 = v25;	// L35
      int v28 = v26 + v27;	// L36
      int v29 = v28;	// L37
      rev = v29;	// L38
    }
    int v30 = rev;	// L40
    int v31 = v30;	// L41
    float v32 = v0[v31];	// L42
    v2[i] = v32;	// L43
    int v33 = rev;	// L44
    int v34 = v33;	// L45
    float v35 = v1[v34];	// L46
    v3[i] = v35;	// L47
  }
  l_S_g1_2_g1: for (int g1 = 0; g1 < 512; g1++) {	// L49
  #pragma HLS pipeline II=5
    int v37 = g1;	// L50
    int v38 = v37  << 1;	// L53
    int v39 = v38;	// L54
    int idx1_1;	// L55
    idx1_1 = v39;	// L56
    int v41 = idx1_1;	// L57
    int v42 = v41;	// L58
    int v43 = v42 + 1;	// L61
    int v44 = v43;	// L62
    int idx2_1;	// L63
    idx2_1 = v44;	// L64
    int v46 = idx1_1;	// L65
    int v47 = v46;	// L66
    float v48 = v2[v47];	// L67
    float a_real_1;	// L68
    a_real_1 = v48;	// L69
    int v50 = idx1_1;	// L70
    int v51 = v50;	// L71
    float v52 = v3[v51];	// L72
    float a_imag_1;	// L73
    a_imag_1 = v52;	// L74
    int v54 = idx2_1;	// L75
    int v55 = v54;	// L76
    float v56 = v2[v55];	// L77
    float b_real_1;	// L78
    b_real_1 = v56;	// L79
    int v58 = idx2_1;	// L80
    int v59 = v58;	// L81
    float v60 = v3[v59];	// L82
    float b_imag_1;	// L83
    b_imag_1 = v60;	// L84
    float v62 = a_real_1;	// L85
    float v63 = b_real_1;	// L86
    float v64 = v62 + v63;	// L87
    int v65 = idx1_1;	// L88
    int v66 = v65;	// L89
    v2[v66] = v64;	// L90
    float v67 = a_imag_1;	// L91
    float v68 = b_imag_1;	// L92
    float v69 = v67 + v68;	// L93
    int v70 = idx1_1;	// L94
    int v71 = v70;	// L95
    v3[v71] = v69;	// L96
    float v72 = a_real_1;	// L97
    float v73 = b_real_1;	// L98
    float v74 = v72 - v73;	// L99
    int v75 = idx2_1;	// L100
    int v76 = v75;	// L101
    v2[v76] = v74;	// L102
    float v77 = a_imag_1;	// L103
    float v78 = b_imag_1;	// L104
    float v79 = v77 - v78;	// L105
    int v80 = idx2_1;	// L106
    int v81 = v80;	// L107
    v3[v81] = v79;	// L108
  }
  l_S_g2_3_g2: for (int g2 = 0; g2 < 256; g2++) {	// L110
  #pragma HLS pipeline II=5
    l_S_j2_3_j2: for (int j2 = 0; j2 < 2; j2++) {	// L111
      int v84 = g2;	// L112
      int v85 = v84 * 4;	// L115
      int v86 = v85;	// L116
      int v87 = j2;	// L117
      int v88 = v86 + v87;	// L118
      int v89 = v88;	// L119
      int idx1_2;	// L120
      idx1_2 = v89;	// L121
      int v91 = idx1_2;	// L122
      int v92 = v91;	// L123
      int v93 = v92 + 2;	// L126
      int v94 = v93;	// L127
      int idx2_2;	// L128
      idx2_2 = v94;	// L129
      int v96 = j2;	// L130
      float v97 = v96;	// L131
      float j2_f;	// L132
      j2_f = v97;	// L133
      float v99 = j2_f;	// L136
      float v100 = v99 * -1.570796;	// L137
      float theta_2;	// L138
      theta_2 = v100;	// L139
      float v102 = theta_2;	// L140
      float v103 = v102 * v102;	// L141
      float theta2_2;	// L142
      theta2_2 = v103;	// L143
      float v105 = theta2_2;	// L144
      float v106 = theta_2;	// L145
      float v107 = v105 * v106;	// L146
      float theta3_2;	// L147
      theta3_2 = v107;	// L148
      float v109 = theta2_2;	// L149
      float v110 = v109 * v109;	// L150
      float theta4_2;	// L151
      theta4_2 = v110;	// L152
      float v112 = theta4_2;	// L153
      float v113 = theta_2;	// L154
      float v114 = v112 * v113;	// L155
      float theta5_2;	// L156
      theta5_2 = v114;	// L157
      float v116 = theta4_2;	// L158
      float v117 = theta2_2;	// L159
      float v118 = v116 * v117;	// L160
      float theta6_2;	// L161
      theta6_2 = v118;	// L162
      float v120 = theta6_2;	// L163
      float v121 = theta_2;	// L164
      float v122 = v120 * v121;	// L165
      float theta7_2;	// L166
      theta7_2 = v122;	// L167
      float v124 = theta4_2;	// L168
      float v125 = v124 * v124;	// L169
      float theta8_2;	// L170
      theta8_2 = v125;	// L171
      float v127 = theta8_2;	// L172
      float v128 = theta_2;	// L173
      float v129 = v127 * v128;	// L174
      float theta9_2;	// L175
      theta9_2 = v129;	// L176
      float v131 = theta8_2;	// L177
      float v132 = theta2_2;	// L178
      float v133 = v131 * v132;	// L179
      float theta10_2;	// L180
      theta10_2 = v133;	// L181
      float v135 = theta10_2;	// L182
      float v136 = theta_2;	// L183
      float v137 = v135 * v136;	// L184
      float theta11_2;	// L185
      theta11_2 = v137;	// L186
      float v139 = theta8_2;	// L187
      float v140 = theta4_2;	// L188
      float v141 = v139 * v140;	// L189
      float theta12_2;	// L190
      theta12_2 = v141;	// L191
      float v143 = theta12_2;	// L192
      float v144 = theta_2;	// L193
      float v145 = v143 * v144;	// L194
      float theta13_2;	// L195
      theta13_2 = v145;	// L196
      float v147 = theta12_2;	// L197
      float v148 = theta2_2;	// L198
      float v149 = v147 * v148;	// L199
      float theta14_2;	// L200
      theta14_2 = v149;	// L201
      float v151 = theta14_2;	// L202
      float v152 = theta_2;	// L203
      float v153 = v151 * v152;	// L204
      float theta15_2;	// L205
      theta15_2 = v153;	// L206
      float v155 = theta8_2;	// L207
      float v156 = v155 * v155;	// L208
      float theta16_2;	// L209
      theta16_2 = v156;	// L210
      float v158 = theta16_2;	// L211
      float v159 = theta_2;	// L212
      float v160 = v158 * v159;	// L213
      float theta17_2;	// L214
      theta17_2 = v160;	// L215
      float v162 = theta2_2;	// L216
      float v163 = v162 / 2.000000;	// L218
      float v164 = 1.000000 - v163;	// L220
      float v165 = theta4_2;	// L221
      float v166 = v165 / 24.000000;	// L223
      float v167 = v164 + v166;	// L224
      float v168 = theta6_2;	// L225
      float v169 = v168 / 720.000000;	// L227
      float v170 = v167 - v169;	// L228
      float v171 = theta8_2;	// L229
      float v172 = v171 / 40320.000000;	// L231
      float v173 = v170 + v172;	// L232
      float v174 = theta10_2;	// L233
      float v175 = v174 / 3628800.000000;	// L235
      float v176 = v173 - v175;	// L236
      float v177 = theta12_2;	// L237
      float v178 = v177 / 479001600.000000;	// L239
      float v179 = v176 + v178;	// L240
      float v180 = theta14_2;	// L241
      float v181 = v180 / 87178289152.000000;	// L243
      float v182 = v179 - v181;	// L244
      float v183 = theta16_2;	// L245
      float v184 = v183 / 20922790576128.000000;	// L247
      float v185 = v182 + v184;	// L248
      float cos_2;	// L249
      cos_2 = v185;	// L250
      float v187 = theta_2;	// L251
      float v188 = theta3_2;	// L252
      float v189 = v188 / 6.000000;	// L254
      float v190 = v187 - v189;	// L255
      float v191 = theta5_2;	// L256
      float v192 = v191 / 120.000000;	// L258
      float v193 = v190 + v192;	// L259
      float v194 = theta7_2;	// L260
      float v195 = v194 / 5040.000000;	// L262
      float v196 = v193 - v195;	// L263
      float v197 = theta9_2;	// L264
      float v198 = v197 / 362880.000000;	// L266
      float v199 = v196 + v198;	// L267
      float v200 = theta11_2;	// L268
      float v201 = v200 / 39916800.000000;	// L270
      float v202 = v199 - v201;	// L271
      float v203 = theta13_2;	// L272
      float v204 = v203 / 6227020800.000000;	// L274
      float v205 = v202 + v204;	// L275
      float v206 = theta15_2;	// L276
      float v207 = v206 / 1307674411008.000000;	// L278
      float v208 = v205 - v207;	// L279
      float v209 = theta17_2;	// L280
      float v210 = v209 / 355687414628352.000000;	// L282
      float v211 = v208 + v210;	// L283
      float sin_2;	// L284
      sin_2 = v211;	// L285
      int v213 = idx1_2;	// L286
      int v214 = v213;	// L287
      float v215 = v2[v214];	// L288
      float a_real_2;	// L289
      a_real_2 = v215;	// L290
      int v217 = idx1_2;	// L291
      int v218 = v217;	// L292
      float v219 = v3[v218];	// L293
      float a_imag_2;	// L294
      a_imag_2 = v219;	// L295
      int v221 = idx2_2;	// L296
      int v222 = v221;	// L297
      float v223 = v2[v222];	// L298
      float b_real_2;	// L299
      b_real_2 = v223;	// L300
      int v225 = idx2_2;	// L301
      int v226 = v225;	// L302
      float v227 = v3[v226];	// L303
      float b_imag_2;	// L304
      b_imag_2 = v227;	// L305
      float v229 = cos_2;	// L306
      float v230 = b_real_2;	// L307
      float v231 = v229 * v230;	// L308
      float v232 = sin_2;	// L309
      float v233 = b_imag_2;	// L310
      float v234 = v232 * v233;	// L311
      float v235 = v231 - v234;	// L312
      float t_real_2;	// L313
      t_real_2 = v235;	// L314
      float v237 = cos_2;	// L315
      float v238 = b_imag_2;	// L316
      float v239 = v237 * v238;	// L317
      float v240 = sin_2;	// L318
      float v241 = b_real_2;	// L319
      float v242 = v240 * v241;	// L320
      float v243 = v239 + v242;	// L321
      float t_imag_2;	// L322
      t_imag_2 = v243;	// L323
      float v245 = a_real_2;	// L324
      float v246 = t_real_2;	// L325
      float v247 = v245 + v246;	// L326
      int v248 = idx1_2;	// L327
      int v249 = v248;	// L328
      v2[v249] = v247;	// L329
      float v250 = a_imag_2;	// L330
      float v251 = t_imag_2;	// L331
      float v252 = v250 + v251;	// L332
      int v253 = idx1_2;	// L333
      int v254 = v253;	// L334
      v3[v254] = v252;	// L335
      float v255 = a_real_2;	// L336
      float v256 = t_real_2;	// L337
      float v257 = v255 - v256;	// L338
      int v258 = idx2_2;	// L339
      int v259 = v258;	// L340
      v2[v259] = v257;	// L341
      float v260 = a_imag_2;	// L342
      float v261 = t_imag_2;	// L343
      float v262 = v260 - v261;	// L344
      int v263 = idx2_2;	// L345
      int v264 = v263;	// L346
      v3[v264] = v262;	// L347
    }
  }
  l_S_g3_5_g3: for (int g3 = 0; g3 < 128; g3++) {	// L350
  #pragma HLS pipeline II=5
    l_S_j3_5_j3: for (int j3 = 0; j3 < 4; j3++) {	// L351
      int v267 = g3;	// L352
      int v268 = v267 * 8;	// L355
      int v269 = v268;	// L356
      int v270 = j3;	// L357
      int v271 = v269 + v270;	// L358
      int v272 = v271;	// L359
      int idx1_3;	// L360
      idx1_3 = v272;	// L361
      int v274 = idx1_3;	// L362
      int v275 = v274;	// L363
      int v276 = v275 + 4;	// L366
      int v277 = v276;	// L367
      int idx2_3;	// L368
      idx2_3 = v277;	// L369
      int v279 = j3;	// L370
      float v280 = v279;	// L371
      float j3_f;	// L372
      j3_f = v280;	// L373
      float v282 = j3_f;	// L376
      float v283 = v282 * -0.785398;	// L377
      float theta_3;	// L378
      theta_3 = v283;	// L379
      float v285 = theta_3;	// L380
      float v286 = v285 * v285;	// L381
      float theta2_3;	// L382
      theta2_3 = v286;	// L383
      float v288 = theta2_3;	// L384
      float v289 = theta_3;	// L385
      float v290 = v288 * v289;	// L386
      float theta3_3;	// L387
      theta3_3 = v290;	// L388
      float v292 = theta2_3;	// L389
      float v293 = v292 * v292;	// L390
      float theta4_3;	// L391
      theta4_3 = v293;	// L392
      float v295 = theta4_3;	// L393
      float v296 = theta_3;	// L394
      float v297 = v295 * v296;	// L395
      float theta5_3;	// L396
      theta5_3 = v297;	// L397
      float v299 = theta4_3;	// L398
      float v300 = theta2_3;	// L399
      float v301 = v299 * v300;	// L400
      float theta6_3;	// L401
      theta6_3 = v301;	// L402
      float v303 = theta6_3;	// L403
      float v304 = theta_3;	// L404
      float v305 = v303 * v304;	// L405
      float theta7_3;	// L406
      theta7_3 = v305;	// L407
      float v307 = theta4_3;	// L408
      float v308 = v307 * v307;	// L409
      float theta8_3;	// L410
      theta8_3 = v308;	// L411
      float v310 = theta8_3;	// L412
      float v311 = theta_3;	// L413
      float v312 = v310 * v311;	// L414
      float theta9_3;	// L415
      theta9_3 = v312;	// L416
      float v314 = theta8_3;	// L417
      float v315 = theta2_3;	// L418
      float v316 = v314 * v315;	// L419
      float theta10_3;	// L420
      theta10_3 = v316;	// L421
      float v318 = theta10_3;	// L422
      float v319 = theta_3;	// L423
      float v320 = v318 * v319;	// L424
      float theta11_3;	// L425
      theta11_3 = v320;	// L426
      float v322 = theta8_3;	// L427
      float v323 = theta4_3;	// L428
      float v324 = v322 * v323;	// L429
      float theta12_3;	// L430
      theta12_3 = v324;	// L431
      float v326 = theta12_3;	// L432
      float v327 = theta_3;	// L433
      float v328 = v326 * v327;	// L434
      float theta13_3;	// L435
      theta13_3 = v328;	// L436
      float v330 = theta12_3;	// L437
      float v331 = theta2_3;	// L438
      float v332 = v330 * v331;	// L439
      float theta14_3;	// L440
      theta14_3 = v332;	// L441
      float v334 = theta14_3;	// L442
      float v335 = theta_3;	// L443
      float v336 = v334 * v335;	// L444
      float theta15_3;	// L445
      theta15_3 = v336;	// L446
      float v338 = theta8_3;	// L447
      float v339 = v338 * v338;	// L448
      float theta16_3;	// L449
      theta16_3 = v339;	// L450
      float v341 = theta16_3;	// L451
      float v342 = theta_3;	// L452
      float v343 = v341 * v342;	// L453
      float theta17_3;	// L454
      theta17_3 = v343;	// L455
      float v345 = theta2_3;	// L456
      float v346 = v345 / 2.000000;	// L458
      float v347 = 1.000000 - v346;	// L460
      float v348 = theta4_3;	// L461
      float v349 = v348 / 24.000000;	// L463
      float v350 = v347 + v349;	// L464
      float v351 = theta6_3;	// L465
      float v352 = v351 / 720.000000;	// L467
      float v353 = v350 - v352;	// L468
      float v354 = theta8_3;	// L469
      float v355 = v354 / 40320.000000;	// L471
      float v356 = v353 + v355;	// L472
      float v357 = theta10_3;	// L473
      float v358 = v357 / 3628800.000000;	// L475
      float v359 = v356 - v358;	// L476
      float v360 = theta12_3;	// L477
      float v361 = v360 / 479001600.000000;	// L479
      float v362 = v359 + v361;	// L480
      float v363 = theta14_3;	// L481
      float v364 = v363 / 87178289152.000000;	// L483
      float v365 = v362 - v364;	// L484
      float v366 = theta16_3;	// L485
      float v367 = v366 / 20922790576128.000000;	// L487
      float v368 = v365 + v367;	// L488
      float cos_3;	// L489
      cos_3 = v368;	// L490
      float v370 = theta_3;	// L491
      float v371 = theta3_3;	// L492
      float v372 = v371 / 6.000000;	// L494
      float v373 = v370 - v372;	// L495
      float v374 = theta5_3;	// L496
      float v375 = v374 / 120.000000;	// L498
      float v376 = v373 + v375;	// L499
      float v377 = theta7_3;	// L500
      float v378 = v377 / 5040.000000;	// L502
      float v379 = v376 - v378;	// L503
      float v380 = theta9_3;	// L504
      float v381 = v380 / 362880.000000;	// L506
      float v382 = v379 + v381;	// L507
      float v383 = theta11_3;	// L508
      float v384 = v383 / 39916800.000000;	// L510
      float v385 = v382 - v384;	// L511
      float v386 = theta13_3;	// L512
      float v387 = v386 / 6227020800.000000;	// L514
      float v388 = v385 + v387;	// L515
      float v389 = theta15_3;	// L516
      float v390 = v389 / 1307674411008.000000;	// L518
      float v391 = v388 - v390;	// L519
      float v392 = theta17_3;	// L520
      float v393 = v392 / 355687414628352.000000;	// L522
      float v394 = v391 + v393;	// L523
      float sin_3;	// L524
      sin_3 = v394;	// L525
      int v396 = idx1_3;	// L526
      int v397 = v396;	// L527
      float v398 = v2[v397];	// L528
      float a_real_3;	// L529
      a_real_3 = v398;	// L530
      int v400 = idx1_3;	// L531
      int v401 = v400;	// L532
      float v402 = v3[v401];	// L533
      float a_imag_3;	// L534
      a_imag_3 = v402;	// L535
      int v404 = idx2_3;	// L536
      int v405 = v404;	// L537
      float v406 = v2[v405];	// L538
      float b_real_3;	// L539
      b_real_3 = v406;	// L540
      int v408 = idx2_3;	// L541
      int v409 = v408;	// L542
      float v410 = v3[v409];	// L543
      float b_imag_3;	// L544
      b_imag_3 = v410;	// L545
      float v412 = cos_3;	// L546
      float v413 = b_real_3;	// L547
      float v414 = v412 * v413;	// L548
      float v415 = sin_3;	// L549
      float v416 = b_imag_3;	// L550
      float v417 = v415 * v416;	// L551
      float v418 = v414 - v417;	// L552
      float t_real_3;	// L553
      t_real_3 = v418;	// L554
      float v420 = cos_3;	// L555
      float v421 = b_imag_3;	// L556
      float v422 = v420 * v421;	// L557
      float v423 = sin_3;	// L558
      float v424 = b_real_3;	// L559
      float v425 = v423 * v424;	// L560
      float v426 = v422 + v425;	// L561
      float t_imag_3;	// L562
      t_imag_3 = v426;	// L563
      float v428 = a_real_3;	// L564
      float v429 = t_real_3;	// L565
      float v430 = v428 + v429;	// L566
      int v431 = idx1_3;	// L567
      int v432 = v431;	// L568
      v2[v432] = v430;	// L569
      float v433 = a_imag_3;	// L570
      float v434 = t_imag_3;	// L571
      float v435 = v433 + v434;	// L572
      int v436 = idx1_3;	// L573
      int v437 = v436;	// L574
      v3[v437] = v435;	// L575
      float v438 = a_real_3;	// L576
      float v439 = t_real_3;	// L577
      float v440 = v438 - v439;	// L578
      int v441 = idx2_3;	// L579
      int v442 = v441;	// L580
      v2[v442] = v440;	// L581
      float v443 = a_imag_3;	// L582
      float v444 = t_imag_3;	// L583
      float v445 = v443 - v444;	// L584
      int v446 = idx2_3;	// L585
      int v447 = v446;	// L586
      v3[v447] = v445;	// L587
    }
  }
  l_S_g4_7_g4: for (int g4 = 0; g4 < 64; g4++) {	// L590
  #pragma HLS pipeline II=5
    l_S_j4_7_j4: for (int j4 = 0; j4 < 8; j4++) {	// L591
      int v450 = g4;	// L592
      int v451 = v450 * 16;	// L595
      int v452 = v451;	// L596
      int v453 = j4;	// L597
      int v454 = v452 + v453;	// L598
      int v455 = v454;	// L599
      int idx1_4;	// L600
      idx1_4 = v455;	// L601
      int v457 = idx1_4;	// L602
      int v458 = v457;	// L603
      int v459 = v458 + 8;	// L606
      int v460 = v459;	// L607
      int idx2_4;	// L608
      idx2_4 = v460;	// L609
      int v462 = j4;	// L610
      float v463 = v462;	// L611
      float j4_f;	// L612
      j4_f = v463;	// L613
      float v465 = j4_f;	// L616
      float v466 = v465 * -0.392699;	// L617
      float theta_4;	// L618
      theta_4 = v466;	// L619
      float v468 = theta_4;	// L620
      float v469 = v468 * v468;	// L621
      float theta2_4;	// L622
      theta2_4 = v469;	// L623
      float v471 = theta2_4;	// L624
      float v472 = theta_4;	// L625
      float v473 = v471 * v472;	// L626
      float theta3_4;	// L627
      theta3_4 = v473;	// L628
      float v475 = theta2_4;	// L629
      float v476 = v475 * v475;	// L630
      float theta4_4;	// L631
      theta4_4 = v476;	// L632
      float v478 = theta4_4;	// L633
      float v479 = theta_4;	// L634
      float v480 = v478 * v479;	// L635
      float theta5_4;	// L636
      theta5_4 = v480;	// L637
      float v482 = theta4_4;	// L638
      float v483 = theta2_4;	// L639
      float v484 = v482 * v483;	// L640
      float theta6_4;	// L641
      theta6_4 = v484;	// L642
      float v486 = theta6_4;	// L643
      float v487 = theta_4;	// L644
      float v488 = v486 * v487;	// L645
      float theta7_4;	// L646
      theta7_4 = v488;	// L647
      float v490 = theta4_4;	// L648
      float v491 = v490 * v490;	// L649
      float theta8_4;	// L650
      theta8_4 = v491;	// L651
      float v493 = theta8_4;	// L652
      float v494 = theta_4;	// L653
      float v495 = v493 * v494;	// L654
      float theta9_4;	// L655
      theta9_4 = v495;	// L656
      float v497 = theta8_4;	// L657
      float v498 = theta2_4;	// L658
      float v499 = v497 * v498;	// L659
      float theta10_4;	// L660
      theta10_4 = v499;	// L661
      float v501 = theta10_4;	// L662
      float v502 = theta_4;	// L663
      float v503 = v501 * v502;	// L664
      float theta11_4;	// L665
      theta11_4 = v503;	// L666
      float v505 = theta8_4;	// L667
      float v506 = theta4_4;	// L668
      float v507 = v505 * v506;	// L669
      float theta12_4;	// L670
      theta12_4 = v507;	// L671
      float v509 = theta12_4;	// L672
      float v510 = theta_4;	// L673
      float v511 = v509 * v510;	// L674
      float theta13_4;	// L675
      theta13_4 = v511;	// L676
      float v513 = theta12_4;	// L677
      float v514 = theta2_4;	// L678
      float v515 = v513 * v514;	// L679
      float theta14_4;	// L680
      theta14_4 = v515;	// L681
      float v517 = theta14_4;	// L682
      float v518 = theta_4;	// L683
      float v519 = v517 * v518;	// L684
      float theta15_4;	// L685
      theta15_4 = v519;	// L686
      float v521 = theta8_4;	// L687
      float v522 = v521 * v521;	// L688
      float theta16_4;	// L689
      theta16_4 = v522;	// L690
      float v524 = theta16_4;	// L691
      float v525 = theta_4;	// L692
      float v526 = v524 * v525;	// L693
      float theta17_4;	// L694
      theta17_4 = v526;	// L695
      float v528 = theta2_4;	// L696
      float v529 = v528 / 2.000000;	// L698
      float v530 = 1.000000 - v529;	// L700
      float v531 = theta4_4;	// L701
      float v532 = v531 / 24.000000;	// L703
      float v533 = v530 + v532;	// L704
      float v534 = theta6_4;	// L705
      float v535 = v534 / 720.000000;	// L707
      float v536 = v533 - v535;	// L708
      float v537 = theta8_4;	// L709
      float v538 = v537 / 40320.000000;	// L711
      float v539 = v536 + v538;	// L712
      float v540 = theta10_4;	// L713
      float v541 = v540 / 3628800.000000;	// L715
      float v542 = v539 - v541;	// L716
      float v543 = theta12_4;	// L717
      float v544 = v543 / 479001600.000000;	// L719
      float v545 = v542 + v544;	// L720
      float v546 = theta14_4;	// L721
      float v547 = v546 / 87178289152.000000;	// L723
      float v548 = v545 - v547;	// L724
      float v549 = theta16_4;	// L725
      float v550 = v549 / 20922790576128.000000;	// L727
      float v551 = v548 + v550;	// L728
      float cos_4;	// L729
      cos_4 = v551;	// L730
      float v553 = theta_4;	// L731
      float v554 = theta3_4;	// L732
      float v555 = v554 / 6.000000;	// L734
      float v556 = v553 - v555;	// L735
      float v557 = theta5_4;	// L736
      float v558 = v557 / 120.000000;	// L738
      float v559 = v556 + v558;	// L739
      float v560 = theta7_4;	// L740
      float v561 = v560 / 5040.000000;	// L742
      float v562 = v559 - v561;	// L743
      float v563 = theta9_4;	// L744
      float v564 = v563 / 362880.000000;	// L746
      float v565 = v562 + v564;	// L747
      float v566 = theta11_4;	// L748
      float v567 = v566 / 39916800.000000;	// L750
      float v568 = v565 - v567;	// L751
      float v569 = theta13_4;	// L752
      float v570 = v569 / 6227020800.000000;	// L754
      float v571 = v568 + v570;	// L755
      float v572 = theta15_4;	// L756
      float v573 = v572 / 1307674411008.000000;	// L758
      float v574 = v571 - v573;	// L759
      float v575 = theta17_4;	// L760
      float v576 = v575 / 355687414628352.000000;	// L762
      float v577 = v574 + v576;	// L763
      float sin_4;	// L764
      sin_4 = v577;	// L765
      int v579 = idx1_4;	// L766
      int v580 = v579;	// L767
      float v581 = v2[v580];	// L768
      float a_real_4;	// L769
      a_real_4 = v581;	// L770
      int v583 = idx1_4;	// L771
      int v584 = v583;	// L772
      float v585 = v3[v584];	// L773
      float a_imag_4;	// L774
      a_imag_4 = v585;	// L775
      int v587 = idx2_4;	// L776
      int v588 = v587;	// L777
      float v589 = v2[v588];	// L778
      float b_real_4;	// L779
      b_real_4 = v589;	// L780
      int v591 = idx2_4;	// L781
      int v592 = v591;	// L782
      float v593 = v3[v592];	// L783
      float b_imag_4;	// L784
      b_imag_4 = v593;	// L785
      float v595 = cos_4;	// L786
      float v596 = b_real_4;	// L787
      float v597 = v595 * v596;	// L788
      float v598 = sin_4;	// L789
      float v599 = b_imag_4;	// L790
      float v600 = v598 * v599;	// L791
      float v601 = v597 - v600;	// L792
      float t_real_4;	// L793
      t_real_4 = v601;	// L794
      float v603 = cos_4;	// L795
      float v604 = b_imag_4;	// L796
      float v605 = v603 * v604;	// L797
      float v606 = sin_4;	// L798
      float v607 = b_real_4;	// L799
      float v608 = v606 * v607;	// L800
      float v609 = v605 + v608;	// L801
      float t_imag_4;	// L802
      t_imag_4 = v609;	// L803
      float v611 = a_real_4;	// L804
      float v612 = t_real_4;	// L805
      float v613 = v611 + v612;	// L806
      int v614 = idx1_4;	// L807
      int v615 = v614;	// L808
      v2[v615] = v613;	// L809
      float v616 = a_imag_4;	// L810
      float v617 = t_imag_4;	// L811
      float v618 = v616 + v617;	// L812
      int v619 = idx1_4;	// L813
      int v620 = v619;	// L814
      v3[v620] = v618;	// L815
      float v621 = a_real_4;	// L816
      float v622 = t_real_4;	// L817
      float v623 = v621 - v622;	// L818
      int v624 = idx2_4;	// L819
      int v625 = v624;	// L820
      v2[v625] = v623;	// L821
      float v626 = a_imag_4;	// L822
      float v627 = t_imag_4;	// L823
      float v628 = v626 - v627;	// L824
      int v629 = idx2_4;	// L825
      int v630 = v629;	// L826
      v3[v630] = v628;	// L827
    }
  }
  l_S_g5_9_g5: for (int g5 = 0; g5 < 32; g5++) {	// L830
  #pragma HLS pipeline II=5
    l_S_j5_9_j5: for (int j5 = 0; j5 < 16; j5++) {	// L831
      int v633 = g5;	// L832
      int v634 = v633 * 32;	// L835
      int v635 = v634;	// L836
      int v636 = j5;	// L837
      int v637 = v635 + v636;	// L838
      int v638 = v637;	// L839
      int idx1_5;	// L840
      idx1_5 = v638;	// L841
      int v640 = idx1_5;	// L842
      int v641 = v640;	// L843
      int v642 = v641 + 16;	// L846
      int v643 = v642;	// L847
      int idx2_5;	// L848
      idx2_5 = v643;	// L849
      int v645 = j5;	// L850
      float v646 = v645;	// L851
      float j5_f;	// L852
      j5_f = v646;	// L853
      float v648 = j5_f;	// L856
      float v649 = v648 * -0.196350;	// L857
      float theta_5;	// L858
      theta_5 = v649;	// L859
      float v651 = theta_5;	// L860
      float v652 = v651 * v651;	// L861
      float theta2_5;	// L862
      theta2_5 = v652;	// L863
      float v654 = theta2_5;	// L864
      float v655 = theta_5;	// L865
      float v656 = v654 * v655;	// L866
      float theta3_5;	// L867
      theta3_5 = v656;	// L868
      float v658 = theta2_5;	// L869
      float v659 = v658 * v658;	// L870
      float theta4_5;	// L871
      theta4_5 = v659;	// L872
      float v661 = theta4_5;	// L873
      float v662 = theta_5;	// L874
      float v663 = v661 * v662;	// L875
      float theta5_5;	// L876
      theta5_5 = v663;	// L877
      float v665 = theta4_5;	// L878
      float v666 = theta2_5;	// L879
      float v667 = v665 * v666;	// L880
      float theta6_5;	// L881
      theta6_5 = v667;	// L882
      float v669 = theta6_5;	// L883
      float v670 = theta_5;	// L884
      float v671 = v669 * v670;	// L885
      float theta7_5;	// L886
      theta7_5 = v671;	// L887
      float v673 = theta4_5;	// L888
      float v674 = v673 * v673;	// L889
      float theta8_5;	// L890
      theta8_5 = v674;	// L891
      float v676 = theta8_5;	// L892
      float v677 = theta_5;	// L893
      float v678 = v676 * v677;	// L894
      float theta9_5;	// L895
      theta9_5 = v678;	// L896
      float v680 = theta8_5;	// L897
      float v681 = theta2_5;	// L898
      float v682 = v680 * v681;	// L899
      float theta10_5;	// L900
      theta10_5 = v682;	// L901
      float v684 = theta10_5;	// L902
      float v685 = theta_5;	// L903
      float v686 = v684 * v685;	// L904
      float theta11_5;	// L905
      theta11_5 = v686;	// L906
      float v688 = theta8_5;	// L907
      float v689 = theta4_5;	// L908
      float v690 = v688 * v689;	// L909
      float theta12_5;	// L910
      theta12_5 = v690;	// L911
      float v692 = theta12_5;	// L912
      float v693 = theta_5;	// L913
      float v694 = v692 * v693;	// L914
      float theta13_5;	// L915
      theta13_5 = v694;	// L916
      float v696 = theta12_5;	// L917
      float v697 = theta2_5;	// L918
      float v698 = v696 * v697;	// L919
      float theta14_5;	// L920
      theta14_5 = v698;	// L921
      float v700 = theta14_5;	// L922
      float v701 = theta_5;	// L923
      float v702 = v700 * v701;	// L924
      float theta15_5;	// L925
      theta15_5 = v702;	// L926
      float v704 = theta8_5;	// L927
      float v705 = v704 * v704;	// L928
      float theta16_5;	// L929
      theta16_5 = v705;	// L930
      float v707 = theta16_5;	// L931
      float v708 = theta_5;	// L932
      float v709 = v707 * v708;	// L933
      float theta17_5;	// L934
      theta17_5 = v709;	// L935
      float v711 = theta2_5;	// L936
      float v712 = v711 / 2.000000;	// L938
      float v713 = 1.000000 - v712;	// L940
      float v714 = theta4_5;	// L941
      float v715 = v714 / 24.000000;	// L943
      float v716 = v713 + v715;	// L944
      float v717 = theta6_5;	// L945
      float v718 = v717 / 720.000000;	// L947
      float v719 = v716 - v718;	// L948
      float v720 = theta8_5;	// L949
      float v721 = v720 / 40320.000000;	// L951
      float v722 = v719 + v721;	// L952
      float v723 = theta10_5;	// L953
      float v724 = v723 / 3628800.000000;	// L955
      float v725 = v722 - v724;	// L956
      float v726 = theta12_5;	// L957
      float v727 = v726 / 479001600.000000;	// L959
      float v728 = v725 + v727;	// L960
      float v729 = theta14_5;	// L961
      float v730 = v729 / 87178289152.000000;	// L963
      float v731 = v728 - v730;	// L964
      float v732 = theta16_5;	// L965
      float v733 = v732 / 20922790576128.000000;	// L967
      float v734 = v731 + v733;	// L968
      float cos_5;	// L969
      cos_5 = v734;	// L970
      float v736 = theta_5;	// L971
      float v737 = theta3_5;	// L972
      float v738 = v737 / 6.000000;	// L974
      float v739 = v736 - v738;	// L975
      float v740 = theta5_5;	// L976
      float v741 = v740 / 120.000000;	// L978
      float v742 = v739 + v741;	// L979
      float v743 = theta7_5;	// L980
      float v744 = v743 / 5040.000000;	// L982
      float v745 = v742 - v744;	// L983
      float v746 = theta9_5;	// L984
      float v747 = v746 / 362880.000000;	// L986
      float v748 = v745 + v747;	// L987
      float v749 = theta11_5;	// L988
      float v750 = v749 / 39916800.000000;	// L990
      float v751 = v748 - v750;	// L991
      float v752 = theta13_5;	// L992
      float v753 = v752 / 6227020800.000000;	// L994
      float v754 = v751 + v753;	// L995
      float v755 = theta15_5;	// L996
      float v756 = v755 / 1307674411008.000000;	// L998
      float v757 = v754 - v756;	// L999
      float v758 = theta17_5;	// L1000
      float v759 = v758 / 355687414628352.000000;	// L1002
      float v760 = v757 + v759;	// L1003
      float sin_5;	// L1004
      sin_5 = v760;	// L1005
      int v762 = idx1_5;	// L1006
      int v763 = v762;	// L1007
      float v764 = v2[v763];	// L1008
      float a_real_5;	// L1009
      a_real_5 = v764;	// L1010
      int v766 = idx1_5;	// L1011
      int v767 = v766;	// L1012
      float v768 = v3[v767];	// L1013
      float a_imag_5;	// L1014
      a_imag_5 = v768;	// L1015
      int v770 = idx2_5;	// L1016
      int v771 = v770;	// L1017
      float v772 = v2[v771];	// L1018
      float b_real_5;	// L1019
      b_real_5 = v772;	// L1020
      int v774 = idx2_5;	// L1021
      int v775 = v774;	// L1022
      float v776 = v3[v775];	// L1023
      float b_imag_5;	// L1024
      b_imag_5 = v776;	// L1025
      float v778 = cos_5;	// L1026
      float v779 = b_real_5;	// L1027
      float v780 = v778 * v779;	// L1028
      float v781 = sin_5;	// L1029
      float v782 = b_imag_5;	// L1030
      float v783 = v781 * v782;	// L1031
      float v784 = v780 - v783;	// L1032
      float t_real_5;	// L1033
      t_real_5 = v784;	// L1034
      float v786 = cos_5;	// L1035
      float v787 = b_imag_5;	// L1036
      float v788 = v786 * v787;	// L1037
      float v789 = sin_5;	// L1038
      float v790 = b_real_5;	// L1039
      float v791 = v789 * v790;	// L1040
      float v792 = v788 + v791;	// L1041
      float t_imag_5;	// L1042
      t_imag_5 = v792;	// L1043
      float v794 = a_real_5;	// L1044
      float v795 = t_real_5;	// L1045
      float v796 = v794 + v795;	// L1046
      int v797 = idx1_5;	// L1047
      int v798 = v797;	// L1048
      v2[v798] = v796;	// L1049
      float v799 = a_imag_5;	// L1050
      float v800 = t_imag_5;	// L1051
      float v801 = v799 + v800;	// L1052
      int v802 = idx1_5;	// L1053
      int v803 = v802;	// L1054
      v3[v803] = v801;	// L1055
      float v804 = a_real_5;	// L1056
      float v805 = t_real_5;	// L1057
      float v806 = v804 - v805;	// L1058
      int v807 = idx2_5;	// L1059
      int v808 = v807;	// L1060
      v2[v808] = v806;	// L1061
      float v809 = a_imag_5;	// L1062
      float v810 = t_imag_5;	// L1063
      float v811 = v809 - v810;	// L1064
      int v812 = idx2_5;	// L1065
      int v813 = v812;	// L1066
      v3[v813] = v811;	// L1067
    }
  }
  l_S_g6_11_g6: for (int g6 = 0; g6 < 16; g6++) {	// L1070
    l_S_j6_11_j6: for (int j6 = 0; j6 < 32; j6++) {	// L1071
    #pragma HLS pipeline II=5
      int v816 = g6;	// L1072
      int v817 = v816 * 64;	// L1075
      int v818 = v817;	// L1076
      int v819 = j6;	// L1077
      int v820 = v818 + v819;	// L1078
      int v821 = v820;	// L1079
      int idx1_6;	// L1080
      idx1_6 = v821;	// L1081
      int v823 = idx1_6;	// L1082
      int v824 = v823;	// L1083
      int v825 = v824 + 32;	// L1086
      int v826 = v825;	// L1087
      int idx2_6;	// L1088
      idx2_6 = v826;	// L1089
      int v828 = j6;	// L1090
      float v829 = v828;	// L1091
      float j6_f;	// L1092
      j6_f = v829;	// L1093
      float v831 = j6_f;	// L1096
      float v832 = v831 * -0.098175;	// L1097
      float theta_6;	// L1098
      theta_6 = v832;	// L1099
      float v834 = theta_6;	// L1100
      float v835 = v834 * v834;	// L1101
      float theta2_6;	// L1102
      theta2_6 = v835;	// L1103
      float v837 = theta2_6;	// L1104
      float v838 = theta_6;	// L1105
      float v839 = v837 * v838;	// L1106
      float theta3_6;	// L1107
      theta3_6 = v839;	// L1108
      float v841 = theta2_6;	// L1109
      float v842 = v841 * v841;	// L1110
      float theta4_6;	// L1111
      theta4_6 = v842;	// L1112
      float v844 = theta4_6;	// L1113
      float v845 = theta_6;	// L1114
      float v846 = v844 * v845;	// L1115
      float theta5_6;	// L1116
      theta5_6 = v846;	// L1117
      float v848 = theta4_6;	// L1118
      float v849 = theta2_6;	// L1119
      float v850 = v848 * v849;	// L1120
      float theta6_6;	// L1121
      theta6_6 = v850;	// L1122
      float v852 = theta6_6;	// L1123
      float v853 = theta_6;	// L1124
      float v854 = v852 * v853;	// L1125
      float theta7_6;	// L1126
      theta7_6 = v854;	// L1127
      float v856 = theta4_6;	// L1128
      float v857 = v856 * v856;	// L1129
      float theta8_6;	// L1130
      theta8_6 = v857;	// L1131
      float v859 = theta8_6;	// L1132
      float v860 = theta_6;	// L1133
      float v861 = v859 * v860;	// L1134
      float theta9_6;	// L1135
      theta9_6 = v861;	// L1136
      float v863 = theta8_6;	// L1137
      float v864 = theta2_6;	// L1138
      float v865 = v863 * v864;	// L1139
      float theta10_6;	// L1140
      theta10_6 = v865;	// L1141
      float v867 = theta10_6;	// L1142
      float v868 = theta_6;	// L1143
      float v869 = v867 * v868;	// L1144
      float theta11_6;	// L1145
      theta11_6 = v869;	// L1146
      float v871 = theta8_6;	// L1147
      float v872 = theta4_6;	// L1148
      float v873 = v871 * v872;	// L1149
      float theta12_6;	// L1150
      theta12_6 = v873;	// L1151
      float v875 = theta12_6;	// L1152
      float v876 = theta_6;	// L1153
      float v877 = v875 * v876;	// L1154
      float theta13_6;	// L1155
      theta13_6 = v877;	// L1156
      float v879 = theta12_6;	// L1157
      float v880 = theta2_6;	// L1158
      float v881 = v879 * v880;	// L1159
      float theta14_6;	// L1160
      theta14_6 = v881;	// L1161
      float v883 = theta14_6;	// L1162
      float v884 = theta_6;	// L1163
      float v885 = v883 * v884;	// L1164
      float theta15_6;	// L1165
      theta15_6 = v885;	// L1166
      float v887 = theta8_6;	// L1167
      float v888 = v887 * v887;	// L1168
      float theta16_6;	// L1169
      theta16_6 = v888;	// L1170
      float v890 = theta16_6;	// L1171
      float v891 = theta_6;	// L1172
      float v892 = v890 * v891;	// L1173
      float theta17_6;	// L1174
      theta17_6 = v892;	// L1175
      float v894 = theta2_6;	// L1176
      float v895 = v894 / 2.000000;	// L1178
      float v896 = 1.000000 - v895;	// L1180
      float v897 = theta4_6;	// L1181
      float v898 = v897 / 24.000000;	// L1183
      float v899 = v896 + v898;	// L1184
      float v900 = theta6_6;	// L1185
      float v901 = v900 / 720.000000;	// L1187
      float v902 = v899 - v901;	// L1188
      float v903 = theta8_6;	// L1189
      float v904 = v903 / 40320.000000;	// L1191
      float v905 = v902 + v904;	// L1192
      float v906 = theta10_6;	// L1193
      float v907 = v906 / 3628800.000000;	// L1195
      float v908 = v905 - v907;	// L1196
      float v909 = theta12_6;	// L1197
      float v910 = v909 / 479001600.000000;	// L1199
      float v911 = v908 + v910;	// L1200
      float v912 = theta14_6;	// L1201
      float v913 = v912 / 87178289152.000000;	// L1203
      float v914 = v911 - v913;	// L1204
      float v915 = theta16_6;	// L1205
      float v916 = v915 / 20922790576128.000000;	// L1207
      float v917 = v914 + v916;	// L1208
      float cos_6;	// L1209
      cos_6 = v917;	// L1210
      float v919 = theta_6;	// L1211
      float v920 = theta3_6;	// L1212
      float v921 = v920 / 6.000000;	// L1214
      float v922 = v919 - v921;	// L1215
      float v923 = theta5_6;	// L1216
      float v924 = v923 / 120.000000;	// L1218
      float v925 = v922 + v924;	// L1219
      float v926 = theta7_6;	// L1220
      float v927 = v926 / 5040.000000;	// L1222
      float v928 = v925 - v927;	// L1223
      float v929 = theta9_6;	// L1224
      float v930 = v929 / 362880.000000;	// L1226
      float v931 = v928 + v930;	// L1227
      float v932 = theta11_6;	// L1228
      float v933 = v932 / 39916800.000000;	// L1230
      float v934 = v931 - v933;	// L1231
      float v935 = theta13_6;	// L1232
      float v936 = v935 / 6227020800.000000;	// L1234
      float v937 = v934 + v936;	// L1235
      float v938 = theta15_6;	// L1236
      float v939 = v938 / 1307674411008.000000;	// L1238
      float v940 = v937 - v939;	// L1239
      float v941 = theta17_6;	// L1240
      float v942 = v941 / 355687414628352.000000;	// L1242
      float v943 = v940 + v942;	// L1243
      float sin_6;	// L1244
      sin_6 = v943;	// L1245
      int v945 = idx1_6;	// L1246
      int v946 = v945;	// L1247
      float v947 = v2[v946];	// L1248
      float a_real_6;	// L1249
      a_real_6 = v947;	// L1250
      int v949 = idx1_6;	// L1251
      int v950 = v949;	// L1252
      float v951 = v3[v950];	// L1253
      float a_imag_6;	// L1254
      a_imag_6 = v951;	// L1255
      int v953 = idx2_6;	// L1256
      int v954 = v953;	// L1257
      float v955 = v2[v954];	// L1258
      float b_real_6;	// L1259
      b_real_6 = v955;	// L1260
      int v957 = idx2_6;	// L1261
      int v958 = v957;	// L1262
      float v959 = v3[v958];	// L1263
      float b_imag_6;	// L1264
      b_imag_6 = v959;	// L1265
      float v961 = cos_6;	// L1266
      float v962 = b_real_6;	// L1267
      float v963 = v961 * v962;	// L1268
      float v964 = sin_6;	// L1269
      float v965 = b_imag_6;	// L1270
      float v966 = v964 * v965;	// L1271
      float v967 = v963 - v966;	// L1272
      float t_real_6;	// L1273
      t_real_6 = v967;	// L1274
      float v969 = cos_6;	// L1275
      float v970 = b_imag_6;	// L1276
      float v971 = v969 * v970;	// L1277
      float v972 = sin_6;	// L1278
      float v973 = b_real_6;	// L1279
      float v974 = v972 * v973;	// L1280
      float v975 = v971 + v974;	// L1281
      float t_imag_6;	// L1282
      t_imag_6 = v975;	// L1283
      float v977 = a_real_6;	// L1284
      float v978 = t_real_6;	// L1285
      float v979 = v977 + v978;	// L1286
      int v980 = idx1_6;	// L1287
      int v981 = v980;	// L1288
      v2[v981] = v979;	// L1289
      float v982 = a_imag_6;	// L1290
      float v983 = t_imag_6;	// L1291
      float v984 = v982 + v983;	// L1292
      int v985 = idx1_6;	// L1293
      int v986 = v985;	// L1294
      v3[v986] = v984;	// L1295
      float v987 = a_real_6;	// L1296
      float v988 = t_real_6;	// L1297
      float v989 = v987 - v988;	// L1298
      int v990 = idx2_6;	// L1299
      int v991 = v990;	// L1300
      v2[v991] = v989;	// L1301
      float v992 = a_imag_6;	// L1302
      float v993 = t_imag_6;	// L1303
      float v994 = v992 - v993;	// L1304
      int v995 = idx2_6;	// L1305
      int v996 = v995;	// L1306
      v3[v996] = v994;	// L1307
    }
  }
  l_S_g7_13_g7: for (int g7 = 0; g7 < 8; g7++) {	// L1310
    l_S_j7_13_j7: for (int j7 = 0; j7 < 64; j7++) {	// L1311
    #pragma HLS pipeline II=5
      int v999 = g7;	// L1312
      int v1000 = v999 * 128;	// L1315
      int v1001 = v1000;	// L1316
      int v1002 = j7;	// L1317
      int v1003 = v1001 + v1002;	// L1318
      int v1004 = v1003;	// L1319
      int idx1_7;	// L1320
      idx1_7 = v1004;	// L1321
      int v1006 = idx1_7;	// L1322
      int v1007 = v1006;	// L1323
      int v1008 = v1007 + 64;	// L1326
      int v1009 = v1008;	// L1327
      int idx2_7;	// L1328
      idx2_7 = v1009;	// L1329
      int v1011 = j7;	// L1330
      float v1012 = v1011;	// L1331
      float j7_f;	// L1332
      j7_f = v1012;	// L1333
      float v1014 = j7_f;	// L1336
      float v1015 = v1014 * -0.049087;	// L1337
      float theta_7;	// L1338
      theta_7 = v1015;	// L1339
      float v1017 = theta_7;	// L1340
      float v1018 = v1017 * v1017;	// L1341
      float theta2_7;	// L1342
      theta2_7 = v1018;	// L1343
      float v1020 = theta2_7;	// L1344
      float v1021 = theta_7;	// L1345
      float v1022 = v1020 * v1021;	// L1346
      float theta3_7;	// L1347
      theta3_7 = v1022;	// L1348
      float v1024 = theta2_7;	// L1349
      float v1025 = v1024 * v1024;	// L1350
      float theta4_7;	// L1351
      theta4_7 = v1025;	// L1352
      float v1027 = theta4_7;	// L1353
      float v1028 = theta_7;	// L1354
      float v1029 = v1027 * v1028;	// L1355
      float theta5_7;	// L1356
      theta5_7 = v1029;	// L1357
      float v1031 = theta4_7;	// L1358
      float v1032 = theta2_7;	// L1359
      float v1033 = v1031 * v1032;	// L1360
      float theta6_7;	// L1361
      theta6_7 = v1033;	// L1362
      float v1035 = theta6_7;	// L1363
      float v1036 = theta_7;	// L1364
      float v1037 = v1035 * v1036;	// L1365
      float theta7_7;	// L1366
      theta7_7 = v1037;	// L1367
      float v1039 = theta4_7;	// L1368
      float v1040 = v1039 * v1039;	// L1369
      float theta8_7;	// L1370
      theta8_7 = v1040;	// L1371
      float v1042 = theta8_7;	// L1372
      float v1043 = theta_7;	// L1373
      float v1044 = v1042 * v1043;	// L1374
      float theta9_7;	// L1375
      theta9_7 = v1044;	// L1376
      float v1046 = theta8_7;	// L1377
      float v1047 = theta2_7;	// L1378
      float v1048 = v1046 * v1047;	// L1379
      float theta10_7;	// L1380
      theta10_7 = v1048;	// L1381
      float v1050 = theta10_7;	// L1382
      float v1051 = theta_7;	// L1383
      float v1052 = v1050 * v1051;	// L1384
      float theta11_7;	// L1385
      theta11_7 = v1052;	// L1386
      float v1054 = theta8_7;	// L1387
      float v1055 = theta4_7;	// L1388
      float v1056 = v1054 * v1055;	// L1389
      float theta12_7;	// L1390
      theta12_7 = v1056;	// L1391
      float v1058 = theta12_7;	// L1392
      float v1059 = theta_7;	// L1393
      float v1060 = v1058 * v1059;	// L1394
      float theta13_7;	// L1395
      theta13_7 = v1060;	// L1396
      float v1062 = theta12_7;	// L1397
      float v1063 = theta2_7;	// L1398
      float v1064 = v1062 * v1063;	// L1399
      float theta14_7;	// L1400
      theta14_7 = v1064;	// L1401
      float v1066 = theta14_7;	// L1402
      float v1067 = theta_7;	// L1403
      float v1068 = v1066 * v1067;	// L1404
      float theta15_7;	// L1405
      theta15_7 = v1068;	// L1406
      float v1070 = theta8_7;	// L1407
      float v1071 = v1070 * v1070;	// L1408
      float theta16_7;	// L1409
      theta16_7 = v1071;	// L1410
      float v1073 = theta16_7;	// L1411
      float v1074 = theta_7;	// L1412
      float v1075 = v1073 * v1074;	// L1413
      float theta17_7;	// L1414
      theta17_7 = v1075;	// L1415
      float v1077 = theta2_7;	// L1416
      float v1078 = v1077 / 2.000000;	// L1418
      float v1079 = 1.000000 - v1078;	// L1420
      float v1080 = theta4_7;	// L1421
      float v1081 = v1080 / 24.000000;	// L1423
      float v1082 = v1079 + v1081;	// L1424
      float v1083 = theta6_7;	// L1425
      float v1084 = v1083 / 720.000000;	// L1427
      float v1085 = v1082 - v1084;	// L1428
      float v1086 = theta8_7;	// L1429
      float v1087 = v1086 / 40320.000000;	// L1431
      float v1088 = v1085 + v1087;	// L1432
      float v1089 = theta10_7;	// L1433
      float v1090 = v1089 / 3628800.000000;	// L1435
      float v1091 = v1088 - v1090;	// L1436
      float v1092 = theta12_7;	// L1437
      float v1093 = v1092 / 479001600.000000;	// L1439
      float v1094 = v1091 + v1093;	// L1440
      float v1095 = theta14_7;	// L1441
      float v1096 = v1095 / 87178289152.000000;	// L1443
      float v1097 = v1094 - v1096;	// L1444
      float v1098 = theta16_7;	// L1445
      float v1099 = v1098 / 20922790576128.000000;	// L1447
      float v1100 = v1097 + v1099;	// L1448
      float cos_7;	// L1449
      cos_7 = v1100;	// L1450
      float v1102 = theta_7;	// L1451
      float v1103 = theta3_7;	// L1452
      float v1104 = v1103 / 6.000000;	// L1454
      float v1105 = v1102 - v1104;	// L1455
      float v1106 = theta5_7;	// L1456
      float v1107 = v1106 / 120.000000;	// L1458
      float v1108 = v1105 + v1107;	// L1459
      float v1109 = theta7_7;	// L1460
      float v1110 = v1109 / 5040.000000;	// L1462
      float v1111 = v1108 - v1110;	// L1463
      float v1112 = theta9_7;	// L1464
      float v1113 = v1112 / 362880.000000;	// L1466
      float v1114 = v1111 + v1113;	// L1467
      float v1115 = theta11_7;	// L1468
      float v1116 = v1115 / 39916800.000000;	// L1470
      float v1117 = v1114 - v1116;	// L1471
      float v1118 = theta13_7;	// L1472
      float v1119 = v1118 / 6227020800.000000;	// L1474
      float v1120 = v1117 + v1119;	// L1475
      float v1121 = theta15_7;	// L1476
      float v1122 = v1121 / 1307674411008.000000;	// L1478
      float v1123 = v1120 - v1122;	// L1479
      float v1124 = theta17_7;	// L1480
      float v1125 = v1124 / 355687414628352.000000;	// L1482
      float v1126 = v1123 + v1125;	// L1483
      float sin_7;	// L1484
      sin_7 = v1126;	// L1485
      int v1128 = idx1_7;	// L1486
      int v1129 = v1128;	// L1487
      float v1130 = v2[v1129];	// L1488
      float a_real_7;	// L1489
      a_real_7 = v1130;	// L1490
      int v1132 = idx1_7;	// L1491
      int v1133 = v1132;	// L1492
      float v1134 = v3[v1133];	// L1493
      float a_imag_7;	// L1494
      a_imag_7 = v1134;	// L1495
      int v1136 = idx2_7;	// L1496
      int v1137 = v1136;	// L1497
      float v1138 = v2[v1137];	// L1498
      float b_real_7;	// L1499
      b_real_7 = v1138;	// L1500
      int v1140 = idx2_7;	// L1501
      int v1141 = v1140;	// L1502
      float v1142 = v3[v1141];	// L1503
      float b_imag_7;	// L1504
      b_imag_7 = v1142;	// L1505
      float v1144 = cos_7;	// L1506
      float v1145 = b_real_7;	// L1507
      float v1146 = v1144 * v1145;	// L1508
      float v1147 = sin_7;	// L1509
      float v1148 = b_imag_7;	// L1510
      float v1149 = v1147 * v1148;	// L1511
      float v1150 = v1146 - v1149;	// L1512
      float t_real_7;	// L1513
      t_real_7 = v1150;	// L1514
      float v1152 = cos_7;	// L1515
      float v1153 = b_imag_7;	// L1516
      float v1154 = v1152 * v1153;	// L1517
      float v1155 = sin_7;	// L1518
      float v1156 = b_real_7;	// L1519
      float v1157 = v1155 * v1156;	// L1520
      float v1158 = v1154 + v1157;	// L1521
      float t_imag_7;	// L1522
      t_imag_7 = v1158;	// L1523
      float v1160 = a_real_7;	// L1524
      float v1161 = t_real_7;	// L1525
      float v1162 = v1160 + v1161;	// L1526
      int v1163 = idx1_7;	// L1527
      int v1164 = v1163;	// L1528
      v2[v1164] = v1162;	// L1529
      float v1165 = a_imag_7;	// L1530
      float v1166 = t_imag_7;	// L1531
      float v1167 = v1165 + v1166;	// L1532
      int v1168 = idx1_7;	// L1533
      int v1169 = v1168;	// L1534
      v3[v1169] = v1167;	// L1535
      float v1170 = a_real_7;	// L1536
      float v1171 = t_real_7;	// L1537
      float v1172 = v1170 - v1171;	// L1538
      int v1173 = idx2_7;	// L1539
      int v1174 = v1173;	// L1540
      v2[v1174] = v1172;	// L1541
      float v1175 = a_imag_7;	// L1542
      float v1176 = t_imag_7;	// L1543
      float v1177 = v1175 - v1176;	// L1544
      int v1178 = idx2_7;	// L1545
      int v1179 = v1178;	// L1546
      v3[v1179] = v1177;	// L1547
    }
  }
  l_S_g8_15_g8: for (int g8 = 0; g8 < 4; g8++) {	// L1550
    l_S_j8_15_j8: for (int j8 = 0; j8 < 128; j8++) {	// L1551
    #pragma HLS pipeline II=5
      int v1182 = g8;	// L1552
      int v1183 = v1182 * 256;	// L1555
      int v1184 = v1183;	// L1556
      int v1185 = j8;	// L1557
      int v1186 = v1184 + v1185;	// L1558
      int v1187 = v1186;	// L1559
      int idx1_8;	// L1560
      idx1_8 = v1187;	// L1561
      int v1189 = idx1_8;	// L1562
      int v1190 = v1189;	// L1563
      int v1191 = v1190 + 128;	// L1566
      int v1192 = v1191;	// L1567
      int idx2_8;	// L1568
      idx2_8 = v1192;	// L1569
      int v1194 = j8;	// L1570
      float v1195 = v1194;	// L1571
      float j8_f;	// L1572
      j8_f = v1195;	// L1573
      float v1197 = j8_f;	// L1576
      float v1198 = v1197 * -0.024544;	// L1577
      float theta_8;	// L1578
      theta_8 = v1198;	// L1579
      float v1200 = theta_8;	// L1580
      float v1201 = v1200 * v1200;	// L1581
      float theta2_8;	// L1582
      theta2_8 = v1201;	// L1583
      float v1203 = theta2_8;	// L1584
      float v1204 = theta_8;	// L1585
      float v1205 = v1203 * v1204;	// L1586
      float theta3_8;	// L1587
      theta3_8 = v1205;	// L1588
      float v1207 = theta2_8;	// L1589
      float v1208 = v1207 * v1207;	// L1590
      float theta4_8;	// L1591
      theta4_8 = v1208;	// L1592
      float v1210 = theta4_8;	// L1593
      float v1211 = theta_8;	// L1594
      float v1212 = v1210 * v1211;	// L1595
      float theta5_8;	// L1596
      theta5_8 = v1212;	// L1597
      float v1214 = theta4_8;	// L1598
      float v1215 = theta2_8;	// L1599
      float v1216 = v1214 * v1215;	// L1600
      float theta6_8;	// L1601
      theta6_8 = v1216;	// L1602
      float v1218 = theta6_8;	// L1603
      float v1219 = theta_8;	// L1604
      float v1220 = v1218 * v1219;	// L1605
      float theta7_8;	// L1606
      theta7_8 = v1220;	// L1607
      float v1222 = theta4_8;	// L1608
      float v1223 = v1222 * v1222;	// L1609
      float theta8_8;	// L1610
      theta8_8 = v1223;	// L1611
      float v1225 = theta8_8;	// L1612
      float v1226 = theta_8;	// L1613
      float v1227 = v1225 * v1226;	// L1614
      float theta9_8;	// L1615
      theta9_8 = v1227;	// L1616
      float v1229 = theta8_8;	// L1617
      float v1230 = theta2_8;	// L1618
      float v1231 = v1229 * v1230;	// L1619
      float theta10_8;	// L1620
      theta10_8 = v1231;	// L1621
      float v1233 = theta10_8;	// L1622
      float v1234 = theta_8;	// L1623
      float v1235 = v1233 * v1234;	// L1624
      float theta11_8;	// L1625
      theta11_8 = v1235;	// L1626
      float v1237 = theta8_8;	// L1627
      float v1238 = theta4_8;	// L1628
      float v1239 = v1237 * v1238;	// L1629
      float theta12_8;	// L1630
      theta12_8 = v1239;	// L1631
      float v1241 = theta12_8;	// L1632
      float v1242 = theta_8;	// L1633
      float v1243 = v1241 * v1242;	// L1634
      float theta13_8;	// L1635
      theta13_8 = v1243;	// L1636
      float v1245 = theta12_8;	// L1637
      float v1246 = theta2_8;	// L1638
      float v1247 = v1245 * v1246;	// L1639
      float theta14_8;	// L1640
      theta14_8 = v1247;	// L1641
      float v1249 = theta14_8;	// L1642
      float v1250 = theta_8;	// L1643
      float v1251 = v1249 * v1250;	// L1644
      float theta15_8;	// L1645
      theta15_8 = v1251;	// L1646
      float v1253 = theta8_8;	// L1647
      float v1254 = v1253 * v1253;	// L1648
      float theta16_8;	// L1649
      theta16_8 = v1254;	// L1650
      float v1256 = theta16_8;	// L1651
      float v1257 = theta_8;	// L1652
      float v1258 = v1256 * v1257;	// L1653
      float theta17_8;	// L1654
      theta17_8 = v1258;	// L1655
      float v1260 = theta2_8;	// L1656
      float v1261 = v1260 / 2.000000;	// L1658
      float v1262 = 1.000000 - v1261;	// L1660
      float v1263 = theta4_8;	// L1661
      float v1264 = v1263 / 24.000000;	// L1663
      float v1265 = v1262 + v1264;	// L1664
      float v1266 = theta6_8;	// L1665
      float v1267 = v1266 / 720.000000;	// L1667
      float v1268 = v1265 - v1267;	// L1668
      float v1269 = theta8_8;	// L1669
      float v1270 = v1269 / 40320.000000;	// L1671
      float v1271 = v1268 + v1270;	// L1672
      float v1272 = theta10_8;	// L1673
      float v1273 = v1272 / 3628800.000000;	// L1675
      float v1274 = v1271 - v1273;	// L1676
      float v1275 = theta12_8;	// L1677
      float v1276 = v1275 / 479001600.000000;	// L1679
      float v1277 = v1274 + v1276;	// L1680
      float v1278 = theta14_8;	// L1681
      float v1279 = v1278 / 87178289152.000000;	// L1683
      float v1280 = v1277 - v1279;	// L1684
      float v1281 = theta16_8;	// L1685
      float v1282 = v1281 / 20922790576128.000000;	// L1687
      float v1283 = v1280 + v1282;	// L1688
      float cos_8;	// L1689
      cos_8 = v1283;	// L1690
      float v1285 = theta_8;	// L1691
      float v1286 = theta3_8;	// L1692
      float v1287 = v1286 / 6.000000;	// L1694
      float v1288 = v1285 - v1287;	// L1695
      float v1289 = theta5_8;	// L1696
      float v1290 = v1289 / 120.000000;	// L1698
      float v1291 = v1288 + v1290;	// L1699
      float v1292 = theta7_8;	// L1700
      float v1293 = v1292 / 5040.000000;	// L1702
      float v1294 = v1291 - v1293;	// L1703
      float v1295 = theta9_8;	// L1704
      float v1296 = v1295 / 362880.000000;	// L1706
      float v1297 = v1294 + v1296;	// L1707
      float v1298 = theta11_8;	// L1708
      float v1299 = v1298 / 39916800.000000;	// L1710
      float v1300 = v1297 - v1299;	// L1711
      float v1301 = theta13_8;	// L1712
      float v1302 = v1301 / 6227020800.000000;	// L1714
      float v1303 = v1300 + v1302;	// L1715
      float v1304 = theta15_8;	// L1716
      float v1305 = v1304 / 1307674411008.000000;	// L1718
      float v1306 = v1303 - v1305;	// L1719
      float v1307 = theta17_8;	// L1720
      float v1308 = v1307 / 355687414628352.000000;	// L1722
      float v1309 = v1306 + v1308;	// L1723
      float sin_8;	// L1724
      sin_8 = v1309;	// L1725
      int v1311 = idx1_8;	// L1726
      int v1312 = v1311;	// L1727
      float v1313 = v2[v1312];	// L1728
      float a_real_8;	// L1729
      a_real_8 = v1313;	// L1730
      int v1315 = idx1_8;	// L1731
      int v1316 = v1315;	// L1732
      float v1317 = v3[v1316];	// L1733
      float a_imag_8;	// L1734
      a_imag_8 = v1317;	// L1735
      int v1319 = idx2_8;	// L1736
      int v1320 = v1319;	// L1737
      float v1321 = v2[v1320];	// L1738
      float b_real_8;	// L1739
      b_real_8 = v1321;	// L1740
      int v1323 = idx2_8;	// L1741
      int v1324 = v1323;	// L1742
      float v1325 = v3[v1324];	// L1743
      float b_imag_8;	// L1744
      b_imag_8 = v1325;	// L1745
      float v1327 = cos_8;	// L1746
      float v1328 = b_real_8;	// L1747
      float v1329 = v1327 * v1328;	// L1748
      float v1330 = sin_8;	// L1749
      float v1331 = b_imag_8;	// L1750
      float v1332 = v1330 * v1331;	// L1751
      float v1333 = v1329 - v1332;	// L1752
      float t_real_8;	// L1753
      t_real_8 = v1333;	// L1754
      float v1335 = cos_8;	// L1755
      float v1336 = b_imag_8;	// L1756
      float v1337 = v1335 * v1336;	// L1757
      float v1338 = sin_8;	// L1758
      float v1339 = b_real_8;	// L1759
      float v1340 = v1338 * v1339;	// L1760
      float v1341 = v1337 + v1340;	// L1761
      float t_imag_8;	// L1762
      t_imag_8 = v1341;	// L1763
      float v1343 = a_real_8;	// L1764
      float v1344 = t_real_8;	// L1765
      float v1345 = v1343 + v1344;	// L1766
      int v1346 = idx1_8;	// L1767
      int v1347 = v1346;	// L1768
      v2[v1347] = v1345;	// L1769
      float v1348 = a_imag_8;	// L1770
      float v1349 = t_imag_8;	// L1771
      float v1350 = v1348 + v1349;	// L1772
      int v1351 = idx1_8;	// L1773
      int v1352 = v1351;	// L1774
      v3[v1352] = v1350;	// L1775
      float v1353 = a_real_8;	// L1776
      float v1354 = t_real_8;	// L1777
      float v1355 = v1353 - v1354;	// L1778
      int v1356 = idx2_8;	// L1779
      int v1357 = v1356;	// L1780
      v2[v1357] = v1355;	// L1781
      float v1358 = a_imag_8;	// L1782
      float v1359 = t_imag_8;	// L1783
      float v1360 = v1358 - v1359;	// L1784
      int v1361 = idx2_8;	// L1785
      int v1362 = v1361;	// L1786
      v3[v1362] = v1360;	// L1787
    }
  }
  l_S_g9_17_g9: for (int g9 = 0; g9 < 2; g9++) {	// L1790
    l_S_j9_17_j9: for (int j9 = 0; j9 < 256; j9++) {	// L1791
    #pragma HLS pipeline II=5
      int v1365 = g9;	// L1792
      int v1366 = v1365 * 512;	// L1795
      int v1367 = v1366;	// L1796
      int v1368 = j9;	// L1797
      int v1369 = v1367 + v1368;	// L1798
      int v1370 = v1369;	// L1799
      int idx1_9;	// L1800
      idx1_9 = v1370;	// L1801
      int v1372 = idx1_9;	// L1802
      int v1373 = v1372;	// L1803
      int v1374 = v1373 + 256;	// L1806
      int v1375 = v1374;	// L1807
      int idx2_9;	// L1808
      idx2_9 = v1375;	// L1809
      int v1377 = j9;	// L1810
      float v1378 = v1377;	// L1811
      float j9_f;	// L1812
      j9_f = v1378;	// L1813
      float v1380 = j9_f;	// L1816
      float v1381 = v1380 * -0.012272;	// L1817
      float theta_9;	// L1818
      theta_9 = v1381;	// L1819
      float v1383 = theta_9;	// L1820
      float v1384 = v1383 * v1383;	// L1821
      float theta2_9;	// L1822
      theta2_9 = v1384;	// L1823
      float v1386 = theta2_9;	// L1824
      float v1387 = theta_9;	// L1825
      float v1388 = v1386 * v1387;	// L1826
      float theta3_9;	// L1827
      theta3_9 = v1388;	// L1828
      float v1390 = theta2_9;	// L1829
      float v1391 = v1390 * v1390;	// L1830
      float theta4_9;	// L1831
      theta4_9 = v1391;	// L1832
      float v1393 = theta4_9;	// L1833
      float v1394 = theta_9;	// L1834
      float v1395 = v1393 * v1394;	// L1835
      float theta5_9;	// L1836
      theta5_9 = v1395;	// L1837
      float v1397 = theta4_9;	// L1838
      float v1398 = theta2_9;	// L1839
      float v1399 = v1397 * v1398;	// L1840
      float theta6_9;	// L1841
      theta6_9 = v1399;	// L1842
      float v1401 = theta6_9;	// L1843
      float v1402 = theta_9;	// L1844
      float v1403 = v1401 * v1402;	// L1845
      float theta7_9;	// L1846
      theta7_9 = v1403;	// L1847
      float v1405 = theta4_9;	// L1848
      float v1406 = v1405 * v1405;	// L1849
      float theta8_9;	// L1850
      theta8_9 = v1406;	// L1851
      float v1408 = theta8_9;	// L1852
      float v1409 = theta_9;	// L1853
      float v1410 = v1408 * v1409;	// L1854
      float theta9_9;	// L1855
      theta9_9 = v1410;	// L1856
      float v1412 = theta8_9;	// L1857
      float v1413 = theta2_9;	// L1858
      float v1414 = v1412 * v1413;	// L1859
      float theta10_9;	// L1860
      theta10_9 = v1414;	// L1861
      float v1416 = theta10_9;	// L1862
      float v1417 = theta_9;	// L1863
      float v1418 = v1416 * v1417;	// L1864
      float theta11_9;	// L1865
      theta11_9 = v1418;	// L1866
      float v1420 = theta8_9;	// L1867
      float v1421 = theta4_9;	// L1868
      float v1422 = v1420 * v1421;	// L1869
      float theta12_9;	// L1870
      theta12_9 = v1422;	// L1871
      float v1424 = theta12_9;	// L1872
      float v1425 = theta_9;	// L1873
      float v1426 = v1424 * v1425;	// L1874
      float theta13_9;	// L1875
      theta13_9 = v1426;	// L1876
      float v1428 = theta12_9;	// L1877
      float v1429 = theta2_9;	// L1878
      float v1430 = v1428 * v1429;	// L1879
      float theta14_9;	// L1880
      theta14_9 = v1430;	// L1881
      float v1432 = theta14_9;	// L1882
      float v1433 = theta_9;	// L1883
      float v1434 = v1432 * v1433;	// L1884
      float theta15_9;	// L1885
      theta15_9 = v1434;	// L1886
      float v1436 = theta8_9;	// L1887
      float v1437 = v1436 * v1436;	// L1888
      float theta16_9;	// L1889
      theta16_9 = v1437;	// L1890
      float v1439 = theta16_9;	// L1891
      float v1440 = theta_9;	// L1892
      float v1441 = v1439 * v1440;	// L1893
      float theta17_9;	// L1894
      theta17_9 = v1441;	// L1895
      float v1443 = theta2_9;	// L1896
      float v1444 = v1443 / 2.000000;	// L1898
      float v1445 = 1.000000 - v1444;	// L1900
      float v1446 = theta4_9;	// L1901
      float v1447 = v1446 / 24.000000;	// L1903
      float v1448 = v1445 + v1447;	// L1904
      float v1449 = theta6_9;	// L1905
      float v1450 = v1449 / 720.000000;	// L1907
      float v1451 = v1448 - v1450;	// L1908
      float v1452 = theta8_9;	// L1909
      float v1453 = v1452 / 40320.000000;	// L1911
      float v1454 = v1451 + v1453;	// L1912
      float v1455 = theta10_9;	// L1913
      float v1456 = v1455 / 3628800.000000;	// L1915
      float v1457 = v1454 - v1456;	// L1916
      float v1458 = theta12_9;	// L1917
      float v1459 = v1458 / 479001600.000000;	// L1919
      float v1460 = v1457 + v1459;	// L1920
      float v1461 = theta14_9;	// L1921
      float v1462 = v1461 / 87178289152.000000;	// L1923
      float v1463 = v1460 - v1462;	// L1924
      float v1464 = theta16_9;	// L1925
      float v1465 = v1464 / 20922790576128.000000;	// L1927
      float v1466 = v1463 + v1465;	// L1928
      float cos_9;	// L1929
      cos_9 = v1466;	// L1930
      float v1468 = theta_9;	// L1931
      float v1469 = theta3_9;	// L1932
      float v1470 = v1469 / 6.000000;	// L1934
      float v1471 = v1468 - v1470;	// L1935
      float v1472 = theta5_9;	// L1936
      float v1473 = v1472 / 120.000000;	// L1938
      float v1474 = v1471 + v1473;	// L1939
      float v1475 = theta7_9;	// L1940
      float v1476 = v1475 / 5040.000000;	// L1942
      float v1477 = v1474 - v1476;	// L1943
      float v1478 = theta9_9;	// L1944
      float v1479 = v1478 / 362880.000000;	// L1946
      float v1480 = v1477 + v1479;	// L1947
      float v1481 = theta11_9;	// L1948
      float v1482 = v1481 / 39916800.000000;	// L1950
      float v1483 = v1480 - v1482;	// L1951
      float v1484 = theta13_9;	// L1952
      float v1485 = v1484 / 6227020800.000000;	// L1954
      float v1486 = v1483 + v1485;	// L1955
      float v1487 = theta15_9;	// L1956
      float v1488 = v1487 / 1307674411008.000000;	// L1958
      float v1489 = v1486 - v1488;	// L1959
      float v1490 = theta17_9;	// L1960
      float v1491 = v1490 / 355687414628352.000000;	// L1962
      float v1492 = v1489 + v1491;	// L1963
      float sin_9;	// L1964
      sin_9 = v1492;	// L1965
      int v1494 = idx1_9;	// L1966
      int v1495 = v1494;	// L1967
      float v1496 = v2[v1495];	// L1968
      float a_real_9;	// L1969
      a_real_9 = v1496;	// L1970
      int v1498 = idx1_9;	// L1971
      int v1499 = v1498;	// L1972
      float v1500 = v3[v1499];	// L1973
      float a_imag_9;	// L1974
      a_imag_9 = v1500;	// L1975
      int v1502 = idx2_9;	// L1976
      int v1503 = v1502;	// L1977
      float v1504 = v2[v1503];	// L1978
      float b_real_9;	// L1979
      b_real_9 = v1504;	// L1980
      int v1506 = idx2_9;	// L1981
      int v1507 = v1506;	// L1982
      float v1508 = v3[v1507];	// L1983
      float b_imag_9;	// L1984
      b_imag_9 = v1508;	// L1985
      float v1510 = cos_9;	// L1986
      float v1511 = b_real_9;	// L1987
      float v1512 = v1510 * v1511;	// L1988
      float v1513 = sin_9;	// L1989
      float v1514 = b_imag_9;	// L1990
      float v1515 = v1513 * v1514;	// L1991
      float v1516 = v1512 - v1515;	// L1992
      float t_real_9;	// L1993
      t_real_9 = v1516;	// L1994
      float v1518 = cos_9;	// L1995
      float v1519 = b_imag_9;	// L1996
      float v1520 = v1518 * v1519;	// L1997
      float v1521 = sin_9;	// L1998
      float v1522 = b_real_9;	// L1999
      float v1523 = v1521 * v1522;	// L2000
      float v1524 = v1520 + v1523;	// L2001
      float t_imag_9;	// L2002
      t_imag_9 = v1524;	// L2003
      float v1526 = a_real_9;	// L2004
      float v1527 = t_real_9;	// L2005
      float v1528 = v1526 + v1527;	// L2006
      int v1529 = idx1_9;	// L2007
      int v1530 = v1529;	// L2008
      v2[v1530] = v1528;	// L2009
      float v1531 = a_imag_9;	// L2010
      float v1532 = t_imag_9;	// L2011
      float v1533 = v1531 + v1532;	// L2012
      int v1534 = idx1_9;	// L2013
      int v1535 = v1534;	// L2014
      v3[v1535] = v1533;	// L2015
      float v1536 = a_real_9;	// L2016
      float v1537 = t_real_9;	// L2017
      float v1538 = v1536 - v1537;	// L2018
      int v1539 = idx2_9;	// L2019
      int v1540 = v1539;	// L2020
      v2[v1540] = v1538;	// L2021
      float v1541 = a_imag_9;	// L2022
      float v1542 = t_imag_9;	// L2023
      float v1543 = v1541 - v1542;	// L2024
      int v1544 = idx2_9;	// L2025
      int v1545 = v1544;	// L2026
      v3[v1545] = v1543;	// L2027
    }
  }
  l_S_g10_19_g10: for (int g10 = 0; g10 < 1; g10++) {	// L2030
    l_S_j10_19_j10: for (int j10 = 0; j10 < 512; j10++) {	// L2031
    #pragma HLS pipeline II=5
      int v1548 = g10;	// L2032
      int v1549 = v1548 * 1024;	// L2035
      int v1550 = v1549;	// L2036
      int v1551 = j10;	// L2037
      int v1552 = v1550 + v1551;	// L2038
      int v1553 = v1552;	// L2039
      int idx1_10;	// L2040
      idx1_10 = v1553;	// L2041
      int v1555 = idx1_10;	// L2042
      int v1556 = v1555;	// L2043
      int v1557 = v1556 + 512;	// L2046
      int v1558 = v1557;	// L2047
      int idx2_10;	// L2048
      idx2_10 = v1558;	// L2049
      int v1560 = j10;	// L2050
      float v1561 = v1560;	// L2051
      float j10_f;	// L2052
      j10_f = v1561;	// L2053
      float v1563 = j10_f;	// L2056
      float v1564 = v1563 * -0.006136;	// L2057
      float theta_10;	// L2058
      theta_10 = v1564;	// L2059
      float v1566 = theta_10;	// L2060
      float v1567 = v1566 * v1566;	// L2061
      float theta2_10;	// L2062
      theta2_10 = v1567;	// L2063
      float v1569 = theta2_10;	// L2064
      float v1570 = theta_10;	// L2065
      float v1571 = v1569 * v1570;	// L2066
      float theta3_10;	// L2067
      theta3_10 = v1571;	// L2068
      float v1573 = theta2_10;	// L2069
      float v1574 = v1573 * v1573;	// L2070
      float theta4_10;	// L2071
      theta4_10 = v1574;	// L2072
      float v1576 = theta4_10;	// L2073
      float v1577 = theta_10;	// L2074
      float v1578 = v1576 * v1577;	// L2075
      float theta5_10;	// L2076
      theta5_10 = v1578;	// L2077
      float v1580 = theta4_10;	// L2078
      float v1581 = theta2_10;	// L2079
      float v1582 = v1580 * v1581;	// L2080
      float theta6_10;	// L2081
      theta6_10 = v1582;	// L2082
      float v1584 = theta6_10;	// L2083
      float v1585 = theta_10;	// L2084
      float v1586 = v1584 * v1585;	// L2085
      float theta7_10;	// L2086
      theta7_10 = v1586;	// L2087
      float v1588 = theta4_10;	// L2088
      float v1589 = v1588 * v1588;	// L2089
      float theta8_10;	// L2090
      theta8_10 = v1589;	// L2091
      float v1591 = theta8_10;	// L2092
      float v1592 = theta_10;	// L2093
      float v1593 = v1591 * v1592;	// L2094
      float theta9_10;	// L2095
      theta9_10 = v1593;	// L2096
      float v1595 = theta8_10;	// L2097
      float v1596 = theta2_10;	// L2098
      float v1597 = v1595 * v1596;	// L2099
      float theta10_10;	// L2100
      theta10_10 = v1597;	// L2101
      float v1599 = theta10_10;	// L2102
      float v1600 = theta_10;	// L2103
      float v1601 = v1599 * v1600;	// L2104
      float theta11_10;	// L2105
      theta11_10 = v1601;	// L2106
      float v1603 = theta8_10;	// L2107
      float v1604 = theta4_10;	// L2108
      float v1605 = v1603 * v1604;	// L2109
      float theta12_10;	// L2110
      theta12_10 = v1605;	// L2111
      float v1607 = theta12_10;	// L2112
      float v1608 = theta_10;	// L2113
      float v1609 = v1607 * v1608;	// L2114
      float theta13_10;	// L2115
      theta13_10 = v1609;	// L2116
      float v1611 = theta12_10;	// L2117
      float v1612 = theta2_10;	// L2118
      float v1613 = v1611 * v1612;	// L2119
      float theta14_10;	// L2120
      theta14_10 = v1613;	// L2121
      float v1615 = theta14_10;	// L2122
      float v1616 = theta_10;	// L2123
      float v1617 = v1615 * v1616;	// L2124
      float theta15_10;	// L2125
      theta15_10 = v1617;	// L2126
      float v1619 = theta8_10;	// L2127
      float v1620 = v1619 * v1619;	// L2128
      float theta16_10;	// L2129
      theta16_10 = v1620;	// L2130
      float v1622 = theta16_10;	// L2131
      float v1623 = theta_10;	// L2132
      float v1624 = v1622 * v1623;	// L2133
      float theta17_10;	// L2134
      theta17_10 = v1624;	// L2135
      float v1626 = theta2_10;	// L2136
      float v1627 = v1626 / 2.000000;	// L2138
      float v1628 = 1.000000 - v1627;	// L2140
      float v1629 = theta4_10;	// L2141
      float v1630 = v1629 / 24.000000;	// L2143
      float v1631 = v1628 + v1630;	// L2144
      float v1632 = theta6_10;	// L2145
      float v1633 = v1632 / 720.000000;	// L2147
      float v1634 = v1631 - v1633;	// L2148
      float v1635 = theta8_10;	// L2149
      float v1636 = v1635 / 40320.000000;	// L2151
      float v1637 = v1634 + v1636;	// L2152
      float v1638 = theta10_10;	// L2153
      float v1639 = v1638 / 3628800.000000;	// L2155
      float v1640 = v1637 - v1639;	// L2156
      float v1641 = theta12_10;	// L2157
      float v1642 = v1641 / 479001600.000000;	// L2159
      float v1643 = v1640 + v1642;	// L2160
      float v1644 = theta14_10;	// L2161
      float v1645 = v1644 / 87178289152.000000;	// L2163
      float v1646 = v1643 - v1645;	// L2164
      float v1647 = theta16_10;	// L2165
      float v1648 = v1647 / 20922790576128.000000;	// L2167
      float v1649 = v1646 + v1648;	// L2168
      float cos_10;	// L2169
      cos_10 = v1649;	// L2170
      float v1651 = theta_10;	// L2171
      float v1652 = theta3_10;	// L2172
      float v1653 = v1652 / 6.000000;	// L2174
      float v1654 = v1651 - v1653;	// L2175
      float v1655 = theta5_10;	// L2176
      float v1656 = v1655 / 120.000000;	// L2178
      float v1657 = v1654 + v1656;	// L2179
      float v1658 = theta7_10;	// L2180
      float v1659 = v1658 / 5040.000000;	// L2182
      float v1660 = v1657 - v1659;	// L2183
      float v1661 = theta9_10;	// L2184
      float v1662 = v1661 / 362880.000000;	// L2186
      float v1663 = v1660 + v1662;	// L2187
      float v1664 = theta11_10;	// L2188
      float v1665 = v1664 / 39916800.000000;	// L2190
      float v1666 = v1663 - v1665;	// L2191
      float v1667 = theta13_10;	// L2192
      float v1668 = v1667 / 6227020800.000000;	// L2194
      float v1669 = v1666 + v1668;	// L2195
      float v1670 = theta15_10;	// L2196
      float v1671 = v1670 / 1307674411008.000000;	// L2198
      float v1672 = v1669 - v1671;	// L2199
      float v1673 = theta17_10;	// L2200
      float v1674 = v1673 / 355687414628352.000000;	// L2202
      float v1675 = v1672 + v1674;	// L2203
      float sin_10;	// L2204
      sin_10 = v1675;	// L2205
      int v1677 = idx1_10;	// L2206
      int v1678 = v1677;	// L2207
      float v1679 = v2[v1678];	// L2208
      float a_real_10;	// L2209
      a_real_10 = v1679;	// L2210
      int v1681 = idx1_10;	// L2211
      int v1682 = v1681;	// L2212
      float v1683 = v3[v1682];	// L2213
      float a_imag_10;	// L2214
      a_imag_10 = v1683;	// L2215
      int v1685 = idx2_10;	// L2216
      int v1686 = v1685;	// L2217
      float v1687 = v2[v1686];	// L2218
      float b_real_10;	// L2219
      b_real_10 = v1687;	// L2220
      int v1689 = idx2_10;	// L2221
      int v1690 = v1689;	// L2222
      float v1691 = v3[v1690];	// L2223
      float b_imag_10;	// L2224
      b_imag_10 = v1691;	// L2225
      float v1693 = cos_10;	// L2226
      float v1694 = b_real_10;	// L2227
      float v1695 = v1693 * v1694;	// L2228
      float v1696 = sin_10;	// L2229
      float v1697 = b_imag_10;	// L2230
      float v1698 = v1696 * v1697;	// L2231
      float v1699 = v1695 - v1698;	// L2232
      float t_real_10;	// L2233
      t_real_10 = v1699;	// L2234
      float v1701 = cos_10;	// L2235
      float v1702 = b_imag_10;	// L2236
      float v1703 = v1701 * v1702;	// L2237
      float v1704 = sin_10;	// L2238
      float v1705 = b_real_10;	// L2239
      float v1706 = v1704 * v1705;	// L2240
      float v1707 = v1703 + v1706;	// L2241
      float t_imag_10;	// L2242
      t_imag_10 = v1707;	// L2243
      float v1709 = a_real_10;	// L2244
      float v1710 = t_real_10;	// L2245
      float v1711 = v1709 + v1710;	// L2246
      int v1712 = idx1_10;	// L2247
      int v1713 = v1712;	// L2248
      v2[v1713] = v1711;	// L2249
      float v1714 = a_imag_10;	// L2250
      float v1715 = t_imag_10;	// L2251
      float v1716 = v1714 + v1715;	// L2252
      int v1717 = idx1_10;	// L2253
      int v1718 = v1717;	// L2254
      v3[v1718] = v1716;	// L2255
      float v1719 = a_real_10;	// L2256
      float v1720 = t_real_10;	// L2257
      float v1721 = v1719 - v1720;	// L2258
      int v1722 = idx2_10;	// L2259
      int v1723 = v1722;	// L2260
      v2[v1723] = v1721;	// L2261
      float v1724 = a_imag_10;	// L2262
      float v1725 = t_imag_10;	// L2263
      float v1726 = v1724 - v1725;	// L2264
      int v1727 = idx2_10;	// L2265
      int v1728 = v1727;	// L2266
      v3[v1728] = v1726;	// L2267
    }
  }
}
#pragma pocc-region-end
}

