
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
  l_S_i_0_i: for (int i = 0; i < 1024; i++) {	// L3
    int v5 = i;	// L4
    int idx;	// L5
    idx = v5;	// L6
    int rev;	// L9
    rev = 0;	// L10
    l_S_b_0_b: for (int b = 0; b < 10; b++) {	// L11
      int v9 = idx;	// L12
      int v10 = v9 / 2;	// L15
      int idx_half;	// L16
      idx_half = v10;	// L17
      int v12 = idx;	// L18
      int v13 = idx_half;	// L19
      int v14 = v13;	// L20
      int v15 = v14  << 1;	// L24
      int v16 = v12;	// L25
      int v17 = v15;	// L26
      int v18 = v16 - v17;	// L27
      int v19 = v18;	// L28
      int bit;	// L29
      bit = v19;	// L30
      int v21 = idx_half;	// L31
      idx = v21;	// L32
      int v22 = rev;	// L33
      int v23 = v22;	// L34
      int v24 = v23  << 1;	// L38
      int v25 = bit;	// L39
      int v26 = v24;	// L40
      int v27 = v25;	// L41
      int v28 = v26 + v27;	// L42
      int v29 = v28;	// L43
      rev = v29;	// L44
    }
    int v30 = rev;	// L46
    int v31 = v30;	// L47
    float v32 = v0[v31];	// L48
    v2[i] = v32;	// L49
    int v33 = rev;	// L50
    int v34 = v33;	// L51
    float v35 = v1[v34];	// L52
    v3[i] = v35;	// L53
  }
  l_S_g1_2_g1: for (int g1 = 0; g1 < 512; g1++) {	// L55
    int v37 = g1;	// L56
    int v38 = v37  << 1;	// L60
    int v39 = v38;	// L61
    int idx1_1;	// L62
    idx1_1 = v39;	// L63
    int v41 = idx1_1;	// L64
    int v42 = v41;	// L65
    int v43 = v42 + 1;	// L69
    int v44 = v43;	// L70
    int idx2_1;	// L71
    idx2_1 = v44;	// L72
    int v46 = idx1_1;	// L73
    int v47 = v46;	// L74
    float v48 = v2[v47];	// L75
    float a_real_1;	// L76
    a_real_1 = v48;	// L77
    int v50 = idx1_1;	// L78
    int v51 = v50;	// L79
    float v52 = v3[v51];	// L80
    float a_imag_1;	// L81
    a_imag_1 = v52;	// L82
    int v54 = idx2_1;	// L83
    int v55 = v54;	// L84
    float v56 = v2[v55];	// L85
    float b_real_1;	// L86
    b_real_1 = v56;	// L87
    int v58 = idx2_1;	// L88
    int v59 = v58;	// L89
    float v60 = v3[v59];	// L90
    float b_imag_1;	// L91
    b_imag_1 = v60;	// L92
    float v62 = a_real_1;	// L93
    float v63 = b_real_1;	// L94
    float v64 = v62 + v63;	// L95
    int v65 = idx1_1;	// L96
    int v66 = v65;	// L97
    v2[v66] = v64;	// L98
    float v67 = a_imag_1;	// L99
    float v68 = b_imag_1;	// L100
    float v69 = v67 + v68;	// L101
    int v70 = idx1_1;	// L102
    int v71 = v70;	// L103
    v3[v71] = v69;	// L104
    float v72 = a_real_1;	// L105
    float v73 = b_real_1;	// L106
    float v74 = v72 - v73;	// L107
    int v75 = idx2_1;	// L108
    int v76 = v75;	// L109
    v2[v76] = v74;	// L110
    float v77 = a_imag_1;	// L111
    float v78 = b_imag_1;	// L112
    float v79 = v77 - v78;	// L113
    int v80 = idx2_1;	// L114
    int v81 = v80;	// L115
    v3[v81] = v79;	// L116
  }
  l_S_g2_3_g2: for (int g2 = 0; g2 < 256; g2++) {	// L118
    l_S_j2_3_j2: for (int j2 = 0; j2 < 2; j2++) {	// L119
      int v84 = g2;	// L120
      int v85 = v84 * 4;	// L124
      int v86 = v85;	// L125
      int v87 = j2;	// L126
      int v88 = v86 + v87;	// L127
      int v89 = v88;	// L128
      int idx1_2;	// L129
      idx1_2 = v89;	// L130
      int v91 = idx1_2;	// L131
      int v92 = v91;	// L132
      int v93 = v92 + 2;	// L136
      int v94 = v93;	// L137
      int idx2_2;	// L138
      idx2_2 = v94;	// L139
      int v96 = j2;	// L140
      float v97 = v96;	// L141
      float j2_f;	// L142
      j2_f = v97;	// L143
      float v99 = j2_f;	// L147
      float v100 = v99 * -1.570796;	// L148
      float theta_2;	// L149
      theta_2 = v100;	// L150
      float v102 = theta_2;	// L151
      float v103 = v102 * v102;	// L153
      float theta2_2;	// L154
      theta2_2 = v103;	// L155
      float v105 = theta2_2;	// L156
      float v106 = theta_2;	// L157
      float v107 = v105 * v106;	// L158
      float theta3_2;	// L159
      theta3_2 = v107;	// L160
      float v109 = theta2_2;	// L161
      float v110 = v109 * v109;	// L163
      float theta4_2;	// L164
      theta4_2 = v110;	// L165
      float v112 = theta4_2;	// L166
      float v113 = theta_2;	// L167
      float v114 = v112 * v113;	// L168
      float theta5_2;	// L169
      theta5_2 = v114;	// L170
      float v116 = theta4_2;	// L171
      float v117 = theta2_2;	// L172
      float v118 = v116 * v117;	// L173
      float theta6_2;	// L174
      theta6_2 = v118;	// L175
      float v120 = theta6_2;	// L176
      float v121 = theta_2;	// L177
      float v122 = v120 * v121;	// L178
      float theta7_2;	// L179
      theta7_2 = v122;	// L180
      float v124 = theta4_2;	// L181
      float v125 = v124 * v124;	// L183
      float theta8_2;	// L184
      theta8_2 = v125;	// L185
      float v127 = theta8_2;	// L186
      float v128 = theta_2;	// L187
      float v129 = v127 * v128;	// L188
      float theta9_2;	// L189
      theta9_2 = v129;	// L190
      float v131 = theta8_2;	// L191
      float v132 = theta2_2;	// L192
      float v133 = v131 * v132;	// L193
      float theta10_2;	// L194
      theta10_2 = v133;	// L195
      float v135 = theta10_2;	// L196
      float v136 = theta_2;	// L197
      float v137 = v135 * v136;	// L198
      float theta11_2;	// L199
      theta11_2 = v137;	// L200
      float v139 = theta8_2;	// L201
      float v140 = theta4_2;	// L202
      float v141 = v139 * v140;	// L203
      float theta12_2;	// L204
      theta12_2 = v141;	// L205
      float v143 = theta12_2;	// L206
      float v144 = theta_2;	// L207
      float v145 = v143 * v144;	// L208
      float theta13_2;	// L209
      theta13_2 = v145;	// L210
      float v147 = theta12_2;	// L211
      float v148 = theta2_2;	// L212
      float v149 = v147 * v148;	// L213
      float theta14_2;	// L214
      theta14_2 = v149;	// L215
      float v151 = theta14_2;	// L216
      float v152 = theta_2;	// L217
      float v153 = v151 * v152;	// L218
      float theta15_2;	// L219
      theta15_2 = v153;	// L220
      float v155 = theta8_2;	// L221
      float v156 = v155 * v155;	// L223
      float theta16_2;	// L224
      theta16_2 = v156;	// L225
      float v158 = theta16_2;	// L226
      float v159 = theta_2;	// L227
      float v160 = v158 * v159;	// L228
      float theta17_2;	// L229
      theta17_2 = v160;	// L230
      float v162 = theta2_2;	// L231
      float v163 = v162 / 2.000000;	// L234
      float v164 = 1.000000 - v163;	// L237
      float v165 = theta4_2;	// L238
      float v166 = v165 / 24.000000;	// L241
      float v167 = v164 + v166;	// L242
      float v168 = theta6_2;	// L243
      float v169 = v168 / 720.000000;	// L246
      float v170 = v167 - v169;	// L247
      float v171 = theta8_2;	// L248
      float v172 = v171 / 40320.000000;	// L251
      float v173 = v170 + v172;	// L252
      float v174 = theta10_2;	// L253
      float v175 = v174 / 3628800.000000;	// L256
      float v176 = v173 - v175;	// L257
      float v177 = theta12_2;	// L258
      float v178 = v177 / 479001600.000000;	// L261
      float v179 = v176 + v178;	// L262
      float v180 = theta14_2;	// L263
      float v181 = v180 / 87178289152.000000;	// L266
      float v182 = v179 - v181;	// L267
      float v183 = theta16_2;	// L268
      float v184 = v183 / 20922790576128.000000;	// L271
      float v185 = v182 + v184;	// L272
      float cos_2;	// L273
      cos_2 = v185;	// L274
      float v187 = theta_2;	// L275
      float v188 = theta3_2;	// L276
      float v189 = v188 / 6.000000;	// L279
      float v190 = v187 - v189;	// L280
      float v191 = theta5_2;	// L281
      float v192 = v191 / 120.000000;	// L284
      float v193 = v190 + v192;	// L285
      float v194 = theta7_2;	// L286
      float v195 = v194 / 5040.000000;	// L289
      float v196 = v193 - v195;	// L290
      float v197 = theta9_2;	// L291
      float v198 = v197 / 362880.000000;	// L294
      float v199 = v196 + v198;	// L295
      float v200 = theta11_2;	// L296
      float v201 = v200 / 39916800.000000;	// L299
      float v202 = v199 - v201;	// L300
      float v203 = theta13_2;	// L301
      float v204 = v203 / 6227020800.000000;	// L304
      float v205 = v202 + v204;	// L305
      float v206 = theta15_2;	// L306
      float v207 = v206 / 1307674411008.000000;	// L309
      float v208 = v205 - v207;	// L310
      float v209 = theta17_2;	// L311
      float v210 = v209 / 355687414628352.000000;	// L314
      float v211 = v208 + v210;	// L315
      float sin_2;	// L316
      sin_2 = v211;	// L317
      int v213 = idx1_2;	// L318
      int v214 = v213;	// L319
      float v215 = v2[v214];	// L320
      float a_real_2;	// L321
      a_real_2 = v215;	// L322
      int v217 = idx1_2;	// L323
      int v218 = v217;	// L324
      float v219 = v3[v218];	// L325
      float a_imag_2;	// L326
      a_imag_2 = v219;	// L327
      int v221 = idx2_2;	// L328
      int v222 = v221;	// L329
      float v223 = v2[v222];	// L330
      float b_real_2;	// L331
      b_real_2 = v223;	// L332
      int v225 = idx2_2;	// L333
      int v226 = v225;	// L334
      float v227 = v3[v226];	// L335
      float b_imag_2;	// L336
      b_imag_2 = v227;	// L337
      float v229 = cos_2;	// L338
      float v230 = b_real_2;	// L339
      float v231 = v229 * v230;	// L340
      float v232 = sin_2;	// L341
      float v233 = b_imag_2;	// L342
      float v234 = v232 * v233;	// L343
      float v235 = v231 - v234;	// L344
      float t_real_2;	// L345
      t_real_2 = v235;	// L346
      float v237 = cos_2;	// L347
      float v238 = b_imag_2;	// L348
      float v239 = v237 * v238;	// L349
      float v240 = sin_2;	// L350
      float v241 = b_real_2;	// L351
      float v242 = v240 * v241;	// L352
      float v243 = v239 + v242;	// L353
      float t_imag_2;	// L354
      t_imag_2 = v243;	// L355
      float v245 = a_real_2;	// L356
      float v246 = t_real_2;	// L357
      float v247 = v245 + v246;	// L358
      int v248 = idx1_2;	// L359
      int v249 = v248;	// L360
      v2[v249] = v247;	// L361
      float v250 = a_imag_2;	// L362
      float v251 = t_imag_2;	// L363
      float v252 = v250 + v251;	// L364
      int v253 = idx1_2;	// L365
      int v254 = v253;	// L366
      v3[v254] = v252;	// L367
      float v255 = a_real_2;	// L368
      float v256 = t_real_2;	// L369
      float v257 = v255 - v256;	// L370
      int v258 = idx2_2;	// L371
      int v259 = v258;	// L372
      v2[v259] = v257;	// L373
      float v260 = a_imag_2;	// L374
      float v261 = t_imag_2;	// L375
      float v262 = v260 - v261;	// L376
      int v263 = idx2_2;	// L377
      int v264 = v263;	// L378
      v3[v264] = v262;	// L379
    }
  }
  l_S_g3_5_g3: for (int g3 = 0; g3 < 128; g3++) {	// L382
    l_S_j3_5_j3: for (int j3 = 0; j3 < 4; j3++) {	// L383
      int v267 = g3;	// L384
      int v268 = v267 * 8;	// L388
      int v269 = v268;	// L389
      int v270 = j3;	// L390
      int v271 = v269 + v270;	// L391
      int v272 = v271;	// L392
      int idx1_3;	// L393
      idx1_3 = v272;	// L394
      int v274 = idx1_3;	// L395
      int v275 = v274;	// L396
      int v276 = v275 + 4;	// L400
      int v277 = v276;	// L401
      int idx2_3;	// L402
      idx2_3 = v277;	// L403
      int v279 = j3;	// L404
      float v280 = v279;	// L405
      float j3_f;	// L406
      j3_f = v280;	// L407
      float v282 = j3_f;	// L411
      float v283 = v282 * -0.785398;	// L412
      float theta_3;	// L413
      theta_3 = v283;	// L414
      float v285 = theta_3;	// L415
      float v286 = v285 * v285;	// L417
      float theta2_3;	// L418
      theta2_3 = v286;	// L419
      float v288 = theta2_3;	// L420
      float v289 = theta_3;	// L421
      float v290 = v288 * v289;	// L422
      float theta3_3;	// L423
      theta3_3 = v290;	// L424
      float v292 = theta2_3;	// L425
      float v293 = v292 * v292;	// L427
      float theta4_3;	// L428
      theta4_3 = v293;	// L429
      float v295 = theta4_3;	// L430
      float v296 = theta_3;	// L431
      float v297 = v295 * v296;	// L432
      float theta5_3;	// L433
      theta5_3 = v297;	// L434
      float v299 = theta4_3;	// L435
      float v300 = theta2_3;	// L436
      float v301 = v299 * v300;	// L437
      float theta6_3;	// L438
      theta6_3 = v301;	// L439
      float v303 = theta6_3;	// L440
      float v304 = theta_3;	// L441
      float v305 = v303 * v304;	// L442
      float theta7_3;	// L443
      theta7_3 = v305;	// L444
      float v307 = theta4_3;	// L445
      float v308 = v307 * v307;	// L447
      float theta8_3;	// L448
      theta8_3 = v308;	// L449
      float v310 = theta8_3;	// L450
      float v311 = theta_3;	// L451
      float v312 = v310 * v311;	// L452
      float theta9_3;	// L453
      theta9_3 = v312;	// L454
      float v314 = theta8_3;	// L455
      float v315 = theta2_3;	// L456
      float v316 = v314 * v315;	// L457
      float theta10_3;	// L458
      theta10_3 = v316;	// L459
      float v318 = theta10_3;	// L460
      float v319 = theta_3;	// L461
      float v320 = v318 * v319;	// L462
      float theta11_3;	// L463
      theta11_3 = v320;	// L464
      float v322 = theta8_3;	// L465
      float v323 = theta4_3;	// L466
      float v324 = v322 * v323;	// L467
      float theta12_3;	// L468
      theta12_3 = v324;	// L469
      float v326 = theta12_3;	// L470
      float v327 = theta_3;	// L471
      float v328 = v326 * v327;	// L472
      float theta13_3;	// L473
      theta13_3 = v328;	// L474
      float v330 = theta12_3;	// L475
      float v331 = theta2_3;	// L476
      float v332 = v330 * v331;	// L477
      float theta14_3;	// L478
      theta14_3 = v332;	// L479
      float v334 = theta14_3;	// L480
      float v335 = theta_3;	// L481
      float v336 = v334 * v335;	// L482
      float theta15_3;	// L483
      theta15_3 = v336;	// L484
      float v338 = theta8_3;	// L485
      float v339 = v338 * v338;	// L487
      float theta16_3;	// L488
      theta16_3 = v339;	// L489
      float v341 = theta16_3;	// L490
      float v342 = theta_3;	// L491
      float v343 = v341 * v342;	// L492
      float theta17_3;	// L493
      theta17_3 = v343;	// L494
      float v345 = theta2_3;	// L495
      float v346 = v345 / 2.000000;	// L498
      float v347 = 1.000000 - v346;	// L501
      float v348 = theta4_3;	// L502
      float v349 = v348 / 24.000000;	// L505
      float v350 = v347 + v349;	// L506
      float v351 = theta6_3;	// L507
      float v352 = v351 / 720.000000;	// L510
      float v353 = v350 - v352;	// L511
      float v354 = theta8_3;	// L512
      float v355 = v354 / 40320.000000;	// L515
      float v356 = v353 + v355;	// L516
      float v357 = theta10_3;	// L517
      float v358 = v357 / 3628800.000000;	// L520
      float v359 = v356 - v358;	// L521
      float v360 = theta12_3;	// L522
      float v361 = v360 / 479001600.000000;	// L525
      float v362 = v359 + v361;	// L526
      float v363 = theta14_3;	// L527
      float v364 = v363 / 87178289152.000000;	// L530
      float v365 = v362 - v364;	// L531
      float v366 = theta16_3;	// L532
      float v367 = v366 / 20922790576128.000000;	// L535
      float v368 = v365 + v367;	// L536
      float cos_3;	// L537
      cos_3 = v368;	// L538
      float v370 = theta_3;	// L539
      float v371 = theta3_3;	// L540
      float v372 = v371 / 6.000000;	// L543
      float v373 = v370 - v372;	// L544
      float v374 = theta5_3;	// L545
      float v375 = v374 / 120.000000;	// L548
      float v376 = v373 + v375;	// L549
      float v377 = theta7_3;	// L550
      float v378 = v377 / 5040.000000;	// L553
      float v379 = v376 - v378;	// L554
      float v380 = theta9_3;	// L555
      float v381 = v380 / 362880.000000;	// L558
      float v382 = v379 + v381;	// L559
      float v383 = theta11_3;	// L560
      float v384 = v383 / 39916800.000000;	// L563
      float v385 = v382 - v384;	// L564
      float v386 = theta13_3;	// L565
      float v387 = v386 / 6227020800.000000;	// L568
      float v388 = v385 + v387;	// L569
      float v389 = theta15_3;	// L570
      float v390 = v389 / 1307674411008.000000;	// L573
      float v391 = v388 - v390;	// L574
      float v392 = theta17_3;	// L575
      float v393 = v392 / 355687414628352.000000;	// L578
      float v394 = v391 + v393;	// L579
      float sin_3;	// L580
      sin_3 = v394;	// L581
      int v396 = idx1_3;	// L582
      int v397 = v396;	// L583
      float v398 = v2[v397];	// L584
      float a_real_3;	// L585
      a_real_3 = v398;	// L586
      int v400 = idx1_3;	// L587
      int v401 = v400;	// L588
      float v402 = v3[v401];	// L589
      float a_imag_3;	// L590
      a_imag_3 = v402;	// L591
      int v404 = idx2_3;	// L592
      int v405 = v404;	// L593
      float v406 = v2[v405];	// L594
      float b_real_3;	// L595
      b_real_3 = v406;	// L596
      int v408 = idx2_3;	// L597
      int v409 = v408;	// L598
      float v410 = v3[v409];	// L599
      float b_imag_3;	// L600
      b_imag_3 = v410;	// L601
      float v412 = cos_3;	// L602
      float v413 = b_real_3;	// L603
      float v414 = v412 * v413;	// L604
      float v415 = sin_3;	// L605
      float v416 = b_imag_3;	// L606
      float v417 = v415 * v416;	// L607
      float v418 = v414 - v417;	// L608
      float t_real_3;	// L609
      t_real_3 = v418;	// L610
      float v420 = cos_3;	// L611
      float v421 = b_imag_3;	// L612
      float v422 = v420 * v421;	// L613
      float v423 = sin_3;	// L614
      float v424 = b_real_3;	// L615
      float v425 = v423 * v424;	// L616
      float v426 = v422 + v425;	// L617
      float t_imag_3;	// L618
      t_imag_3 = v426;	// L619
      float v428 = a_real_3;	// L620
      float v429 = t_real_3;	// L621
      float v430 = v428 + v429;	// L622
      int v431 = idx1_3;	// L623
      int v432 = v431;	// L624
      v2[v432] = v430;	// L625
      float v433 = a_imag_3;	// L626
      float v434 = t_imag_3;	// L627
      float v435 = v433 + v434;	// L628
      int v436 = idx1_3;	// L629
      int v437 = v436;	// L630
      v3[v437] = v435;	// L631
      float v438 = a_real_3;	// L632
      float v439 = t_real_3;	// L633
      float v440 = v438 - v439;	// L634
      int v441 = idx2_3;	// L635
      int v442 = v441;	// L636
      v2[v442] = v440;	// L637
      float v443 = a_imag_3;	// L638
      float v444 = t_imag_3;	// L639
      float v445 = v443 - v444;	// L640
      int v446 = idx2_3;	// L641
      int v447 = v446;	// L642
      v3[v447] = v445;	// L643
    }
  }
  l_S_g4_7_g4: for (int g4 = 0; g4 < 64; g4++) {	// L646
    l_S_j4_7_j4: for (int j4 = 0; j4 < 8; j4++) {	// L647
      int v450 = g4;	// L648
      int v451 = v450 * 16;	// L652
      int v452 = v451;	// L653
      int v453 = j4;	// L654
      int v454 = v452 + v453;	// L655
      int v455 = v454;	// L656
      int idx1_4;	// L657
      idx1_4 = v455;	// L658
      int v457 = idx1_4;	// L659
      int v458 = v457;	// L660
      int v459 = v458 + 8;	// L664
      int v460 = v459;	// L665
      int idx2_4;	// L666
      idx2_4 = v460;	// L667
      int v462 = j4;	// L668
      float v463 = v462;	// L669
      float j4_f;	// L670
      j4_f = v463;	// L671
      float v465 = j4_f;	// L675
      float v466 = v465 * -0.392699;	// L676
      float theta_4;	// L677
      theta_4 = v466;	// L678
      float v468 = theta_4;	// L679
      float v469 = v468 * v468;	// L681
      float theta2_4;	// L682
      theta2_4 = v469;	// L683
      float v471 = theta2_4;	// L684
      float v472 = theta_4;	// L685
      float v473 = v471 * v472;	// L686
      float theta3_4;	// L687
      theta3_4 = v473;	// L688
      float v475 = theta2_4;	// L689
      float v476 = v475 * v475;	// L691
      float theta4_4;	// L692
      theta4_4 = v476;	// L693
      float v478 = theta4_4;	// L694
      float v479 = theta_4;	// L695
      float v480 = v478 * v479;	// L696
      float theta5_4;	// L697
      theta5_4 = v480;	// L698
      float v482 = theta4_4;	// L699
      float v483 = theta2_4;	// L700
      float v484 = v482 * v483;	// L701
      float theta6_4;	// L702
      theta6_4 = v484;	// L703
      float v486 = theta6_4;	// L704
      float v487 = theta_4;	// L705
      float v488 = v486 * v487;	// L706
      float theta7_4;	// L707
      theta7_4 = v488;	// L708
      float v490 = theta4_4;	// L709
      float v491 = v490 * v490;	// L711
      float theta8_4;	// L712
      theta8_4 = v491;	// L713
      float v493 = theta8_4;	// L714
      float v494 = theta_4;	// L715
      float v495 = v493 * v494;	// L716
      float theta9_4;	// L717
      theta9_4 = v495;	// L718
      float v497 = theta8_4;	// L719
      float v498 = theta2_4;	// L720
      float v499 = v497 * v498;	// L721
      float theta10_4;	// L722
      theta10_4 = v499;	// L723
      float v501 = theta10_4;	// L724
      float v502 = theta_4;	// L725
      float v503 = v501 * v502;	// L726
      float theta11_4;	// L727
      theta11_4 = v503;	// L728
      float v505 = theta8_4;	// L729
      float v506 = theta4_4;	// L730
      float v507 = v505 * v506;	// L731
      float theta12_4;	// L732
      theta12_4 = v507;	// L733
      float v509 = theta12_4;	// L734
      float v510 = theta_4;	// L735
      float v511 = v509 * v510;	// L736
      float theta13_4;	// L737
      theta13_4 = v511;	// L738
      float v513 = theta12_4;	// L739
      float v514 = theta2_4;	// L740
      float v515 = v513 * v514;	// L741
      float theta14_4;	// L742
      theta14_4 = v515;	// L743
      float v517 = theta14_4;	// L744
      float v518 = theta_4;	// L745
      float v519 = v517 * v518;	// L746
      float theta15_4;	// L747
      theta15_4 = v519;	// L748
      float v521 = theta8_4;	// L749
      float v522 = v521 * v521;	// L751
      float theta16_4;	// L752
      theta16_4 = v522;	// L753
      float v524 = theta16_4;	// L754
      float v525 = theta_4;	// L755
      float v526 = v524 * v525;	// L756
      float theta17_4;	// L757
      theta17_4 = v526;	// L758
      float v528 = theta2_4;	// L759
      float v529 = v528 / 2.000000;	// L762
      float v530 = 1.000000 - v529;	// L765
      float v531 = theta4_4;	// L766
      float v532 = v531 / 24.000000;	// L769
      float v533 = v530 + v532;	// L770
      float v534 = theta6_4;	// L771
      float v535 = v534 / 720.000000;	// L774
      float v536 = v533 - v535;	// L775
      float v537 = theta8_4;	// L776
      float v538 = v537 / 40320.000000;	// L779
      float v539 = v536 + v538;	// L780
      float v540 = theta10_4;	// L781
      float v541 = v540 / 3628800.000000;	// L784
      float v542 = v539 - v541;	// L785
      float v543 = theta12_4;	// L786
      float v544 = v543 / 479001600.000000;	// L789
      float v545 = v542 + v544;	// L790
      float v546 = theta14_4;	// L791
      float v547 = v546 / 87178289152.000000;	// L794
      float v548 = v545 - v547;	// L795
      float v549 = theta16_4;	// L796
      float v550 = v549 / 20922790576128.000000;	// L799
      float v551 = v548 + v550;	// L800
      float cos_4;	// L801
      cos_4 = v551;	// L802
      float v553 = theta_4;	// L803
      float v554 = theta3_4;	// L804
      float v555 = v554 / 6.000000;	// L807
      float v556 = v553 - v555;	// L808
      float v557 = theta5_4;	// L809
      float v558 = v557 / 120.000000;	// L812
      float v559 = v556 + v558;	// L813
      float v560 = theta7_4;	// L814
      float v561 = v560 / 5040.000000;	// L817
      float v562 = v559 - v561;	// L818
      float v563 = theta9_4;	// L819
      float v564 = v563 / 362880.000000;	// L822
      float v565 = v562 + v564;	// L823
      float v566 = theta11_4;	// L824
      float v567 = v566 / 39916800.000000;	// L827
      float v568 = v565 - v567;	// L828
      float v569 = theta13_4;	// L829
      float v570 = v569 / 6227020800.000000;	// L832
      float v571 = v568 + v570;	// L833
      float v572 = theta15_4;	// L834
      float v573 = v572 / 1307674411008.000000;	// L837
      float v574 = v571 - v573;	// L838
      float v575 = theta17_4;	// L839
      float v576 = v575 / 355687414628352.000000;	// L842
      float v577 = v574 + v576;	// L843
      float sin_4;	// L844
      sin_4 = v577;	// L845
      int v579 = idx1_4;	// L846
      int v580 = v579;	// L847
      float v581 = v2[v580];	// L848
      float a_real_4;	// L849
      a_real_4 = v581;	// L850
      int v583 = idx1_4;	// L851
      int v584 = v583;	// L852
      float v585 = v3[v584];	// L853
      float a_imag_4;	// L854
      a_imag_4 = v585;	// L855
      int v587 = idx2_4;	// L856
      int v588 = v587;	// L857
      float v589 = v2[v588];	// L858
      float b_real_4;	// L859
      b_real_4 = v589;	// L860
      int v591 = idx2_4;	// L861
      int v592 = v591;	// L862
      float v593 = v3[v592];	// L863
      float b_imag_4;	// L864
      b_imag_4 = v593;	// L865
      float v595 = cos_4;	// L866
      float v596 = b_real_4;	// L867
      float v597 = v595 * v596;	// L868
      float v598 = sin_4;	// L869
      float v599 = b_imag_4;	// L870
      float v600 = v598 * v599;	// L871
      float v601 = v597 - v600;	// L872
      float t_real_4;	// L873
      t_real_4 = v601;	// L874
      float v603 = cos_4;	// L875
      float v604 = b_imag_4;	// L876
      float v605 = v603 * v604;	// L877
      float v606 = sin_4;	// L878
      float v607 = b_real_4;	// L879
      float v608 = v606 * v607;	// L880
      float v609 = v605 + v608;	// L881
      float t_imag_4;	// L882
      t_imag_4 = v609;	// L883
      float v611 = a_real_4;	// L884
      float v612 = t_real_4;	// L885
      float v613 = v611 + v612;	// L886
      int v614 = idx1_4;	// L887
      int v615 = v614;	// L888
      v2[v615] = v613;	// L889
      float v616 = a_imag_4;	// L890
      float v617 = t_imag_4;	// L891
      float v618 = v616 + v617;	// L892
      int v619 = idx1_4;	// L893
      int v620 = v619;	// L894
      v3[v620] = v618;	// L895
      float v621 = a_real_4;	// L896
      float v622 = t_real_4;	// L897
      float v623 = v621 - v622;	// L898
      int v624 = idx2_4;	// L899
      int v625 = v624;	// L900
      v2[v625] = v623;	// L901
      float v626 = a_imag_4;	// L902
      float v627 = t_imag_4;	// L903
      float v628 = v626 - v627;	// L904
      int v629 = idx2_4;	// L905
      int v630 = v629;	// L906
      v3[v630] = v628;	// L907
    }
  }
  l_S_g5_9_g5: for (int g5 = 0; g5 < 32; g5++) {	// L910
    l_S_j5_9_j5: for (int j5 = 0; j5 < 16; j5++) {	// L911
      int v633 = g5;	// L912
      int v634 = v633 * 32;	// L916
      int v635 = v634;	// L917
      int v636 = j5;	// L918
      int v637 = v635 + v636;	// L919
      int v638 = v637;	// L920
      int idx1_5;	// L921
      idx1_5 = v638;	// L922
      int v640 = idx1_5;	// L923
      int v641 = v640;	// L924
      int v642 = v641 + 16;	// L928
      int v643 = v642;	// L929
      int idx2_5;	// L930
      idx2_5 = v643;	// L931
      int v645 = j5;	// L932
      float v646 = v645;	// L933
      float j5_f;	// L934
      j5_f = v646;	// L935
      float v648 = j5_f;	// L939
      float v649 = v648 * -0.196350;	// L940
      float theta_5;	// L941
      theta_5 = v649;	// L942
      float v651 = theta_5;	// L943
      float v652 = v651 * v651;	// L945
      float theta2_5;	// L946
      theta2_5 = v652;	// L947
      float v654 = theta2_5;	// L948
      float v655 = theta_5;	// L949
      float v656 = v654 * v655;	// L950
      float theta3_5;	// L951
      theta3_5 = v656;	// L952
      float v658 = theta2_5;	// L953
      float v659 = v658 * v658;	// L955
      float theta4_5;	// L956
      theta4_5 = v659;	// L957
      float v661 = theta4_5;	// L958
      float v662 = theta_5;	// L959
      float v663 = v661 * v662;	// L960
      float theta5_5;	// L961
      theta5_5 = v663;	// L962
      float v665 = theta4_5;	// L963
      float v666 = theta2_5;	// L964
      float v667 = v665 * v666;	// L965
      float theta6_5;	// L966
      theta6_5 = v667;	// L967
      float v669 = theta6_5;	// L968
      float v670 = theta_5;	// L969
      float v671 = v669 * v670;	// L970
      float theta7_5;	// L971
      theta7_5 = v671;	// L972
      float v673 = theta4_5;	// L973
      float v674 = v673 * v673;	// L975
      float theta8_5;	// L976
      theta8_5 = v674;	// L977
      float v676 = theta8_5;	// L978
      float v677 = theta_5;	// L979
      float v678 = v676 * v677;	// L980
      float theta9_5;	// L981
      theta9_5 = v678;	// L982
      float v680 = theta8_5;	// L983
      float v681 = theta2_5;	// L984
      float v682 = v680 * v681;	// L985
      float theta10_5;	// L986
      theta10_5 = v682;	// L987
      float v684 = theta10_5;	// L988
      float v685 = theta_5;	// L989
      float v686 = v684 * v685;	// L990
      float theta11_5;	// L991
      theta11_5 = v686;	// L992
      float v688 = theta8_5;	// L993
      float v689 = theta4_5;	// L994
      float v690 = v688 * v689;	// L995
      float theta12_5;	// L996
      theta12_5 = v690;	// L997
      float v692 = theta12_5;	// L998
      float v693 = theta_5;	// L999
      float v694 = v692 * v693;	// L1000
      float theta13_5;	// L1001
      theta13_5 = v694;	// L1002
      float v696 = theta12_5;	// L1003
      float v697 = theta2_5;	// L1004
      float v698 = v696 * v697;	// L1005
      float theta14_5;	// L1006
      theta14_5 = v698;	// L1007
      float v700 = theta14_5;	// L1008
      float v701 = theta_5;	// L1009
      float v702 = v700 * v701;	// L1010
      float theta15_5;	// L1011
      theta15_5 = v702;	// L1012
      float v704 = theta8_5;	// L1013
      float v705 = v704 * v704;	// L1015
      float theta16_5;	// L1016
      theta16_5 = v705;	// L1017
      float v707 = theta16_5;	// L1018
      float v708 = theta_5;	// L1019
      float v709 = v707 * v708;	// L1020
      float theta17_5;	// L1021
      theta17_5 = v709;	// L1022
      float v711 = theta2_5;	// L1023
      float v712 = v711 / 2.000000;	// L1026
      float v713 = 1.000000 - v712;	// L1029
      float v714 = theta4_5;	// L1030
      float v715 = v714 / 24.000000;	// L1033
      float v716 = v713 + v715;	// L1034
      float v717 = theta6_5;	// L1035
      float v718 = v717 / 720.000000;	// L1038
      float v719 = v716 - v718;	// L1039
      float v720 = theta8_5;	// L1040
      float v721 = v720 / 40320.000000;	// L1043
      float v722 = v719 + v721;	// L1044
      float v723 = theta10_5;	// L1045
      float v724 = v723 / 3628800.000000;	// L1048
      float v725 = v722 - v724;	// L1049
      float v726 = theta12_5;	// L1050
      float v727 = v726 / 479001600.000000;	// L1053
      float v728 = v725 + v727;	// L1054
      float v729 = theta14_5;	// L1055
      float v730 = v729 / 87178289152.000000;	// L1058
      float v731 = v728 - v730;	// L1059
      float v732 = theta16_5;	// L1060
      float v733 = v732 / 20922790576128.000000;	// L1063
      float v734 = v731 + v733;	// L1064
      float cos_5;	// L1065
      cos_5 = v734;	// L1066
      float v736 = theta_5;	// L1067
      float v737 = theta3_5;	// L1068
      float v738 = v737 / 6.000000;	// L1071
      float v739 = v736 - v738;	// L1072
      float v740 = theta5_5;	// L1073
      float v741 = v740 / 120.000000;	// L1076
      float v742 = v739 + v741;	// L1077
      float v743 = theta7_5;	// L1078
      float v744 = v743 / 5040.000000;	// L1081
      float v745 = v742 - v744;	// L1082
      float v746 = theta9_5;	// L1083
      float v747 = v746 / 362880.000000;	// L1086
      float v748 = v745 + v747;	// L1087
      float v749 = theta11_5;	// L1088
      float v750 = v749 / 39916800.000000;	// L1091
      float v751 = v748 - v750;	// L1092
      float v752 = theta13_5;	// L1093
      float v753 = v752 / 6227020800.000000;	// L1096
      float v754 = v751 + v753;	// L1097
      float v755 = theta15_5;	// L1098
      float v756 = v755 / 1307674411008.000000;	// L1101
      float v757 = v754 - v756;	// L1102
      float v758 = theta17_5;	// L1103
      float v759 = v758 / 355687414628352.000000;	// L1106
      float v760 = v757 + v759;	// L1107
      float sin_5;	// L1108
      sin_5 = v760;	// L1109
      int v762 = idx1_5;	// L1110
      int v763 = v762;	// L1111
      float v764 = v2[v763];	// L1112
      float a_real_5;	// L1113
      a_real_5 = v764;	// L1114
      int v766 = idx1_5;	// L1115
      int v767 = v766;	// L1116
      float v768 = v3[v767];	// L1117
      float a_imag_5;	// L1118
      a_imag_5 = v768;	// L1119
      int v770 = idx2_5;	// L1120
      int v771 = v770;	// L1121
      float v772 = v2[v771];	// L1122
      float b_real_5;	// L1123
      b_real_5 = v772;	// L1124
      int v774 = idx2_5;	// L1125
      int v775 = v774;	// L1126
      float v776 = v3[v775];	// L1127
      float b_imag_5;	// L1128
      b_imag_5 = v776;	// L1129
      float v778 = cos_5;	// L1130
      float v779 = b_real_5;	// L1131
      float v780 = v778 * v779;	// L1132
      float v781 = sin_5;	// L1133
      float v782 = b_imag_5;	// L1134
      float v783 = v781 * v782;	// L1135
      float v784 = v780 - v783;	// L1136
      float t_real_5;	// L1137
      t_real_5 = v784;	// L1138
      float v786 = cos_5;	// L1139
      float v787 = b_imag_5;	// L1140
      float v788 = v786 * v787;	// L1141
      float v789 = sin_5;	// L1142
      float v790 = b_real_5;	// L1143
      float v791 = v789 * v790;	// L1144
      float v792 = v788 + v791;	// L1145
      float t_imag_5;	// L1146
      t_imag_5 = v792;	// L1147
      float v794 = a_real_5;	// L1148
      float v795 = t_real_5;	// L1149
      float v796 = v794 + v795;	// L1150
      int v797 = idx1_5;	// L1151
      int v798 = v797;	// L1152
      v2[v798] = v796;	// L1153
      float v799 = a_imag_5;	// L1154
      float v800 = t_imag_5;	// L1155
      float v801 = v799 + v800;	// L1156
      int v802 = idx1_5;	// L1157
      int v803 = v802;	// L1158
      v3[v803] = v801;	// L1159
      float v804 = a_real_5;	// L1160
      float v805 = t_real_5;	// L1161
      float v806 = v804 - v805;	// L1162
      int v807 = idx2_5;	// L1163
      int v808 = v807;	// L1164
      v2[v808] = v806;	// L1165
      float v809 = a_imag_5;	// L1166
      float v810 = t_imag_5;	// L1167
      float v811 = v809 - v810;	// L1168
      int v812 = idx2_5;	// L1169
      int v813 = v812;	// L1170
      v3[v813] = v811;	// L1171
    }
  }
  l_S_g6_11_g6: for (int g6 = 0; g6 < 16; g6++) {	// L1174
    l_S_j6_11_j6: for (int j6 = 0; j6 < 32; j6++) {	// L1175
      int v816 = g6;	// L1176
      int v817 = v816 * 64;	// L1180
      int v818 = v817;	// L1181
      int v819 = j6;	// L1182
      int v820 = v818 + v819;	// L1183
      int v821 = v820;	// L1184
      int idx1_6;	// L1185
      idx1_6 = v821;	// L1186
      int v823 = idx1_6;	// L1187
      int v824 = v823;	// L1188
      int v825 = v824 + 32;	// L1192
      int v826 = v825;	// L1193
      int idx2_6;	// L1194
      idx2_6 = v826;	// L1195
      int v828 = j6;	// L1196
      float v829 = v828;	// L1197
      float j6_f;	// L1198
      j6_f = v829;	// L1199
      float v831 = j6_f;	// L1203
      float v832 = v831 * -0.098175;	// L1204
      float theta_6;	// L1205
      theta_6 = v832;	// L1206
      float v834 = theta_6;	// L1207
      float v835 = v834 * v834;	// L1209
      float theta2_6;	// L1210
      theta2_6 = v835;	// L1211
      float v837 = theta2_6;	// L1212
      float v838 = theta_6;	// L1213
      float v839 = v837 * v838;	// L1214
      float theta3_6;	// L1215
      theta3_6 = v839;	// L1216
      float v841 = theta2_6;	// L1217
      float v842 = v841 * v841;	// L1219
      float theta4_6;	// L1220
      theta4_6 = v842;	// L1221
      float v844 = theta4_6;	// L1222
      float v845 = theta_6;	// L1223
      float v846 = v844 * v845;	// L1224
      float theta5_6;	// L1225
      theta5_6 = v846;	// L1226
      float v848 = theta4_6;	// L1227
      float v849 = theta2_6;	// L1228
      float v850 = v848 * v849;	// L1229
      float theta6_6;	// L1230
      theta6_6 = v850;	// L1231
      float v852 = theta6_6;	// L1232
      float v853 = theta_6;	// L1233
      float v854 = v852 * v853;	// L1234
      float theta7_6;	// L1235
      theta7_6 = v854;	// L1236
      float v856 = theta4_6;	// L1237
      float v857 = v856 * v856;	// L1239
      float theta8_6;	// L1240
      theta8_6 = v857;	// L1241
      float v859 = theta8_6;	// L1242
      float v860 = theta_6;	// L1243
      float v861 = v859 * v860;	// L1244
      float theta9_6;	// L1245
      theta9_6 = v861;	// L1246
      float v863 = theta8_6;	// L1247
      float v864 = theta2_6;	// L1248
      float v865 = v863 * v864;	// L1249
      float theta10_6;	// L1250
      theta10_6 = v865;	// L1251
      float v867 = theta10_6;	// L1252
      float v868 = theta_6;	// L1253
      float v869 = v867 * v868;	// L1254
      float theta11_6;	// L1255
      theta11_6 = v869;	// L1256
      float v871 = theta8_6;	// L1257
      float v872 = theta4_6;	// L1258
      float v873 = v871 * v872;	// L1259
      float theta12_6;	// L1260
      theta12_6 = v873;	// L1261
      float v875 = theta12_6;	// L1262
      float v876 = theta_6;	// L1263
      float v877 = v875 * v876;	// L1264
      float theta13_6;	// L1265
      theta13_6 = v877;	// L1266
      float v879 = theta12_6;	// L1267
      float v880 = theta2_6;	// L1268
      float v881 = v879 * v880;	// L1269
      float theta14_6;	// L1270
      theta14_6 = v881;	// L1271
      float v883 = theta14_6;	// L1272
      float v884 = theta_6;	// L1273
      float v885 = v883 * v884;	// L1274
      float theta15_6;	// L1275
      theta15_6 = v885;	// L1276
      float v887 = theta8_6;	// L1277
      float v888 = v887 * v887;	// L1279
      float theta16_6;	// L1280
      theta16_6 = v888;	// L1281
      float v890 = theta16_6;	// L1282
      float v891 = theta_6;	// L1283
      float v892 = v890 * v891;	// L1284
      float theta17_6;	// L1285
      theta17_6 = v892;	// L1286
      float v894 = theta2_6;	// L1287
      float v895 = v894 / 2.000000;	// L1290
      float v896 = 1.000000 - v895;	// L1293
      float v897 = theta4_6;	// L1294
      float v898 = v897 / 24.000000;	// L1297
      float v899 = v896 + v898;	// L1298
      float v900 = theta6_6;	// L1299
      float v901 = v900 / 720.000000;	// L1302
      float v902 = v899 - v901;	// L1303
      float v903 = theta8_6;	// L1304
      float v904 = v903 / 40320.000000;	// L1307
      float v905 = v902 + v904;	// L1308
      float v906 = theta10_6;	// L1309
      float v907 = v906 / 3628800.000000;	// L1312
      float v908 = v905 - v907;	// L1313
      float v909 = theta12_6;	// L1314
      float v910 = v909 / 479001600.000000;	// L1317
      float v911 = v908 + v910;	// L1318
      float v912 = theta14_6;	// L1319
      float v913 = v912 / 87178289152.000000;	// L1322
      float v914 = v911 - v913;	// L1323
      float v915 = theta16_6;	// L1324
      float v916 = v915 / 20922790576128.000000;	// L1327
      float v917 = v914 + v916;	// L1328
      float cos_6;	// L1329
      cos_6 = v917;	// L1330
      float v919 = theta_6;	// L1331
      float v920 = theta3_6;	// L1332
      float v921 = v920 / 6.000000;	// L1335
      float v922 = v919 - v921;	// L1336
      float v923 = theta5_6;	// L1337
      float v924 = v923 / 120.000000;	// L1340
      float v925 = v922 + v924;	// L1341
      float v926 = theta7_6;	// L1342
      float v927 = v926 / 5040.000000;	// L1345
      float v928 = v925 - v927;	// L1346
      float v929 = theta9_6;	// L1347
      float v930 = v929 / 362880.000000;	// L1350
      float v931 = v928 + v930;	// L1351
      float v932 = theta11_6;	// L1352
      float v933 = v932 / 39916800.000000;	// L1355
      float v934 = v931 - v933;	// L1356
      float v935 = theta13_6;	// L1357
      float v936 = v935 / 6227020800.000000;	// L1360
      float v937 = v934 + v936;	// L1361
      float v938 = theta15_6;	// L1362
      float v939 = v938 / 1307674411008.000000;	// L1365
      float v940 = v937 - v939;	// L1366
      float v941 = theta17_6;	// L1367
      float v942 = v941 / 355687414628352.000000;	// L1370
      float v943 = v940 + v942;	// L1371
      float sin_6;	// L1372
      sin_6 = v943;	// L1373
      int v945 = idx1_6;	// L1374
      int v946 = v945;	// L1375
      float v947 = v2[v946];	// L1376
      float a_real_6;	// L1377
      a_real_6 = v947;	// L1378
      int v949 = idx1_6;	// L1379
      int v950 = v949;	// L1380
      float v951 = v3[v950];	// L1381
      float a_imag_6;	// L1382
      a_imag_6 = v951;	// L1383
      int v953 = idx2_6;	// L1384
      int v954 = v953;	// L1385
      float v955 = v2[v954];	// L1386
      float b_real_6;	// L1387
      b_real_6 = v955;	// L1388
      int v957 = idx2_6;	// L1389
      int v958 = v957;	// L1390
      float v959 = v3[v958];	// L1391
      float b_imag_6;	// L1392
      b_imag_6 = v959;	// L1393
      float v961 = cos_6;	// L1394
      float v962 = b_real_6;	// L1395
      float v963 = v961 * v962;	// L1396
      float v964 = sin_6;	// L1397
      float v965 = b_imag_6;	// L1398
      float v966 = v964 * v965;	// L1399
      float v967 = v963 - v966;	// L1400
      float t_real_6;	// L1401
      t_real_6 = v967;	// L1402
      float v969 = cos_6;	// L1403
      float v970 = b_imag_6;	// L1404
      float v971 = v969 * v970;	// L1405
      float v972 = sin_6;	// L1406
      float v973 = b_real_6;	// L1407
      float v974 = v972 * v973;	// L1408
      float v975 = v971 + v974;	// L1409
      float t_imag_6;	// L1410
      t_imag_6 = v975;	// L1411
      float v977 = a_real_6;	// L1412
      float v978 = t_real_6;	// L1413
      float v979 = v977 + v978;	// L1414
      int v980 = idx1_6;	// L1415
      int v981 = v980;	// L1416
      v2[v981] = v979;	// L1417
      float v982 = a_imag_6;	// L1418
      float v983 = t_imag_6;	// L1419
      float v984 = v982 + v983;	// L1420
      int v985 = idx1_6;	// L1421
      int v986 = v985;	// L1422
      v3[v986] = v984;	// L1423
      float v987 = a_real_6;	// L1424
      float v988 = t_real_6;	// L1425
      float v989 = v987 - v988;	// L1426
      int v990 = idx2_6;	// L1427
      int v991 = v990;	// L1428
      v2[v991] = v989;	// L1429
      float v992 = a_imag_6;	// L1430
      float v993 = t_imag_6;	// L1431
      float v994 = v992 - v993;	// L1432
      int v995 = idx2_6;	// L1433
      int v996 = v995;	// L1434
      v3[v996] = v994;	// L1435
    }
  }
  l_S_g7_13_g7: for (int g7 = 0; g7 < 8; g7++) {	// L1438
    l_S_j7_13_j7: for (int j7 = 0; j7 < 64; j7++) {	// L1439
      int v999 = g7;	// L1440
      int v1000 = v999 * 128;	// L1444
      int v1001 = v1000;	// L1445
      int v1002 = j7;	// L1446
      int v1003 = v1001 + v1002;	// L1447
      int v1004 = v1003;	// L1448
      int idx1_7;	// L1449
      idx1_7 = v1004;	// L1450
      int v1006 = idx1_7;	// L1451
      int v1007 = v1006;	// L1452
      int v1008 = v1007 + 64;	// L1456
      int v1009 = v1008;	// L1457
      int idx2_7;	// L1458
      idx2_7 = v1009;	// L1459
      int v1011 = j7;	// L1460
      float v1012 = v1011;	// L1461
      float j7_f;	// L1462
      j7_f = v1012;	// L1463
      float v1014 = j7_f;	// L1467
      float v1015 = v1014 * -0.049087;	// L1468
      float theta_7;	// L1469
      theta_7 = v1015;	// L1470
      float v1017 = theta_7;	// L1471
      float v1018 = v1017 * v1017;	// L1473
      float theta2_7;	// L1474
      theta2_7 = v1018;	// L1475
      float v1020 = theta2_7;	// L1476
      float v1021 = theta_7;	// L1477
      float v1022 = v1020 * v1021;	// L1478
      float theta3_7;	// L1479
      theta3_7 = v1022;	// L1480
      float v1024 = theta2_7;	// L1481
      float v1025 = v1024 * v1024;	// L1483
      float theta4_7;	// L1484
      theta4_7 = v1025;	// L1485
      float v1027 = theta4_7;	// L1486
      float v1028 = theta_7;	// L1487
      float v1029 = v1027 * v1028;	// L1488
      float theta5_7;	// L1489
      theta5_7 = v1029;	// L1490
      float v1031 = theta4_7;	// L1491
      float v1032 = theta2_7;	// L1492
      float v1033 = v1031 * v1032;	// L1493
      float theta6_7;	// L1494
      theta6_7 = v1033;	// L1495
      float v1035 = theta6_7;	// L1496
      float v1036 = theta_7;	// L1497
      float v1037 = v1035 * v1036;	// L1498
      float theta7_7;	// L1499
      theta7_7 = v1037;	// L1500
      float v1039 = theta4_7;	// L1501
      float v1040 = v1039 * v1039;	// L1503
      float theta8_7;	// L1504
      theta8_7 = v1040;	// L1505
      float v1042 = theta8_7;	// L1506
      float v1043 = theta_7;	// L1507
      float v1044 = v1042 * v1043;	// L1508
      float theta9_7;	// L1509
      theta9_7 = v1044;	// L1510
      float v1046 = theta8_7;	// L1511
      float v1047 = theta2_7;	// L1512
      float v1048 = v1046 * v1047;	// L1513
      float theta10_7;	// L1514
      theta10_7 = v1048;	// L1515
      float v1050 = theta10_7;	// L1516
      float v1051 = theta_7;	// L1517
      float v1052 = v1050 * v1051;	// L1518
      float theta11_7;	// L1519
      theta11_7 = v1052;	// L1520
      float v1054 = theta8_7;	// L1521
      float v1055 = theta4_7;	// L1522
      float v1056 = v1054 * v1055;	// L1523
      float theta12_7;	// L1524
      theta12_7 = v1056;	// L1525
      float v1058 = theta12_7;	// L1526
      float v1059 = theta_7;	// L1527
      float v1060 = v1058 * v1059;	// L1528
      float theta13_7;	// L1529
      theta13_7 = v1060;	// L1530
      float v1062 = theta12_7;	// L1531
      float v1063 = theta2_7;	// L1532
      float v1064 = v1062 * v1063;	// L1533
      float theta14_7;	// L1534
      theta14_7 = v1064;	// L1535
      float v1066 = theta14_7;	// L1536
      float v1067 = theta_7;	// L1537
      float v1068 = v1066 * v1067;	// L1538
      float theta15_7;	// L1539
      theta15_7 = v1068;	// L1540
      float v1070 = theta8_7;	// L1541
      float v1071 = v1070 * v1070;	// L1543
      float theta16_7;	// L1544
      theta16_7 = v1071;	// L1545
      float v1073 = theta16_7;	// L1546
      float v1074 = theta_7;	// L1547
      float v1075 = v1073 * v1074;	// L1548
      float theta17_7;	// L1549
      theta17_7 = v1075;	// L1550
      float v1077 = theta2_7;	// L1551
      float v1078 = v1077 / 2.000000;	// L1554
      float v1079 = 1.000000 - v1078;	// L1557
      float v1080 = theta4_7;	// L1558
      float v1081 = v1080 / 24.000000;	// L1561
      float v1082 = v1079 + v1081;	// L1562
      float v1083 = theta6_7;	// L1563
      float v1084 = v1083 / 720.000000;	// L1566
      float v1085 = v1082 - v1084;	// L1567
      float v1086 = theta8_7;	// L1568
      float v1087 = v1086 / 40320.000000;	// L1571
      float v1088 = v1085 + v1087;	// L1572
      float v1089 = theta10_7;	// L1573
      float v1090 = v1089 / 3628800.000000;	// L1576
      float v1091 = v1088 - v1090;	// L1577
      float v1092 = theta12_7;	// L1578
      float v1093 = v1092 / 479001600.000000;	// L1581
      float v1094 = v1091 + v1093;	// L1582
      float v1095 = theta14_7;	// L1583
      float v1096 = v1095 / 87178289152.000000;	// L1586
      float v1097 = v1094 - v1096;	// L1587
      float v1098 = theta16_7;	// L1588
      float v1099 = v1098 / 20922790576128.000000;	// L1591
      float v1100 = v1097 + v1099;	// L1592
      float cos_7;	// L1593
      cos_7 = v1100;	// L1594
      float v1102 = theta_7;	// L1595
      float v1103 = theta3_7;	// L1596
      float v1104 = v1103 / 6.000000;	// L1599
      float v1105 = v1102 - v1104;	// L1600
      float v1106 = theta5_7;	// L1601
      float v1107 = v1106 / 120.000000;	// L1604
      float v1108 = v1105 + v1107;	// L1605
      float v1109 = theta7_7;	// L1606
      float v1110 = v1109 / 5040.000000;	// L1609
      float v1111 = v1108 - v1110;	// L1610
      float v1112 = theta9_7;	// L1611
      float v1113 = v1112 / 362880.000000;	// L1614
      float v1114 = v1111 + v1113;	// L1615
      float v1115 = theta11_7;	// L1616
      float v1116 = v1115 / 39916800.000000;	// L1619
      float v1117 = v1114 - v1116;	// L1620
      float v1118 = theta13_7;	// L1621
      float v1119 = v1118 / 6227020800.000000;	// L1624
      float v1120 = v1117 + v1119;	// L1625
      float v1121 = theta15_7;	// L1626
      float v1122 = v1121 / 1307674411008.000000;	// L1629
      float v1123 = v1120 - v1122;	// L1630
      float v1124 = theta17_7;	// L1631
      float v1125 = v1124 / 355687414628352.000000;	// L1634
      float v1126 = v1123 + v1125;	// L1635
      float sin_7;	// L1636
      sin_7 = v1126;	// L1637
      int v1128 = idx1_7;	// L1638
      int v1129 = v1128;	// L1639
      float v1130 = v2[v1129];	// L1640
      float a_real_7;	// L1641
      a_real_7 = v1130;	// L1642
      int v1132 = idx1_7;	// L1643
      int v1133 = v1132;	// L1644
      float v1134 = v3[v1133];	// L1645
      float a_imag_7;	// L1646
      a_imag_7 = v1134;	// L1647
      int v1136 = idx2_7;	// L1648
      int v1137 = v1136;	// L1649
      float v1138 = v2[v1137];	// L1650
      float b_real_7;	// L1651
      b_real_7 = v1138;	// L1652
      int v1140 = idx2_7;	// L1653
      int v1141 = v1140;	// L1654
      float v1142 = v3[v1141];	// L1655
      float b_imag_7;	// L1656
      b_imag_7 = v1142;	// L1657
      float v1144 = cos_7;	// L1658
      float v1145 = b_real_7;	// L1659
      float v1146 = v1144 * v1145;	// L1660
      float v1147 = sin_7;	// L1661
      float v1148 = b_imag_7;	// L1662
      float v1149 = v1147 * v1148;	// L1663
      float v1150 = v1146 - v1149;	// L1664
      float t_real_7;	// L1665
      t_real_7 = v1150;	// L1666
      float v1152 = cos_7;	// L1667
      float v1153 = b_imag_7;	// L1668
      float v1154 = v1152 * v1153;	// L1669
      float v1155 = sin_7;	// L1670
      float v1156 = b_real_7;	// L1671
      float v1157 = v1155 * v1156;	// L1672
      float v1158 = v1154 + v1157;	// L1673
      float t_imag_7;	// L1674
      t_imag_7 = v1158;	// L1675
      float v1160 = a_real_7;	// L1676
      float v1161 = t_real_7;	// L1677
      float v1162 = v1160 + v1161;	// L1678
      int v1163 = idx1_7;	// L1679
      int v1164 = v1163;	// L1680
      v2[v1164] = v1162;	// L1681
      float v1165 = a_imag_7;	// L1682
      float v1166 = t_imag_7;	// L1683
      float v1167 = v1165 + v1166;	// L1684
      int v1168 = idx1_7;	// L1685
      int v1169 = v1168;	// L1686
      v3[v1169] = v1167;	// L1687
      float v1170 = a_real_7;	// L1688
      float v1171 = t_real_7;	// L1689
      float v1172 = v1170 - v1171;	// L1690
      int v1173 = idx2_7;	// L1691
      int v1174 = v1173;	// L1692
      v2[v1174] = v1172;	// L1693
      float v1175 = a_imag_7;	// L1694
      float v1176 = t_imag_7;	// L1695
      float v1177 = v1175 - v1176;	// L1696
      int v1178 = idx2_7;	// L1697
      int v1179 = v1178;	// L1698
      v3[v1179] = v1177;	// L1699
    }
  }
  l_S_g8_15_g8: for (int g8 = 0; g8 < 4; g8++) {	// L1702
    l_S_j8_15_j8: for (int j8 = 0; j8 < 128; j8++) {	// L1703
      int v1182 = g8;	// L1704
      int v1183 = v1182 * 256;	// L1708
      int v1184 = v1183;	// L1709
      int v1185 = j8;	// L1710
      int v1186 = v1184 + v1185;	// L1711
      int v1187 = v1186;	// L1712
      int idx1_8;	// L1713
      idx1_8 = v1187;	// L1714
      int v1189 = idx1_8;	// L1715
      int v1190 = v1189;	// L1716
      int v1191 = v1190 + 128;	// L1720
      int v1192 = v1191;	// L1721
      int idx2_8;	// L1722
      idx2_8 = v1192;	// L1723
      int v1194 = j8;	// L1724
      float v1195 = v1194;	// L1725
      float j8_f;	// L1726
      j8_f = v1195;	// L1727
      float v1197 = j8_f;	// L1731
      float v1198 = v1197 * -0.024544;	// L1732
      float theta_8;	// L1733
      theta_8 = v1198;	// L1734
      float v1200 = theta_8;	// L1735
      float v1201 = v1200 * v1200;	// L1737
      float theta2_8;	// L1738
      theta2_8 = v1201;	// L1739
      float v1203 = theta2_8;	// L1740
      float v1204 = theta_8;	// L1741
      float v1205 = v1203 * v1204;	// L1742
      float theta3_8;	// L1743
      theta3_8 = v1205;	// L1744
      float v1207 = theta2_8;	// L1745
      float v1208 = v1207 * v1207;	// L1747
      float theta4_8;	// L1748
      theta4_8 = v1208;	// L1749
      float v1210 = theta4_8;	// L1750
      float v1211 = theta_8;	// L1751
      float v1212 = v1210 * v1211;	// L1752
      float theta5_8;	// L1753
      theta5_8 = v1212;	// L1754
      float v1214 = theta4_8;	// L1755
      float v1215 = theta2_8;	// L1756
      float v1216 = v1214 * v1215;	// L1757
      float theta6_8;	// L1758
      theta6_8 = v1216;	// L1759
      float v1218 = theta6_8;	// L1760
      float v1219 = theta_8;	// L1761
      float v1220 = v1218 * v1219;	// L1762
      float theta7_8;	// L1763
      theta7_8 = v1220;	// L1764
      float v1222 = theta4_8;	// L1765
      float v1223 = v1222 * v1222;	// L1767
      float theta8_8;	// L1768
      theta8_8 = v1223;	// L1769
      float v1225 = theta8_8;	// L1770
      float v1226 = theta_8;	// L1771
      float v1227 = v1225 * v1226;	// L1772
      float theta9_8;	// L1773
      theta9_8 = v1227;	// L1774
      float v1229 = theta8_8;	// L1775
      float v1230 = theta2_8;	// L1776
      float v1231 = v1229 * v1230;	// L1777
      float theta10_8;	// L1778
      theta10_8 = v1231;	// L1779
      float v1233 = theta10_8;	// L1780
      float v1234 = theta_8;	// L1781
      float v1235 = v1233 * v1234;	// L1782
      float theta11_8;	// L1783
      theta11_8 = v1235;	// L1784
      float v1237 = theta8_8;	// L1785
      float v1238 = theta4_8;	// L1786
      float v1239 = v1237 * v1238;	// L1787
      float theta12_8;	// L1788
      theta12_8 = v1239;	// L1789
      float v1241 = theta12_8;	// L1790
      float v1242 = theta_8;	// L1791
      float v1243 = v1241 * v1242;	// L1792
      float theta13_8;	// L1793
      theta13_8 = v1243;	// L1794
      float v1245 = theta12_8;	// L1795
      float v1246 = theta2_8;	// L1796
      float v1247 = v1245 * v1246;	// L1797
      float theta14_8;	// L1798
      theta14_8 = v1247;	// L1799
      float v1249 = theta14_8;	// L1800
      float v1250 = theta_8;	// L1801
      float v1251 = v1249 * v1250;	// L1802
      float theta15_8;	// L1803
      theta15_8 = v1251;	// L1804
      float v1253 = theta8_8;	// L1805
      float v1254 = v1253 * v1253;	// L1807
      float theta16_8;	// L1808
      theta16_8 = v1254;	// L1809
      float v1256 = theta16_8;	// L1810
      float v1257 = theta_8;	// L1811
      float v1258 = v1256 * v1257;	// L1812
      float theta17_8;	// L1813
      theta17_8 = v1258;	// L1814
      float v1260 = theta2_8;	// L1815
      float v1261 = v1260 / 2.000000;	// L1818
      float v1262 = 1.000000 - v1261;	// L1821
      float v1263 = theta4_8;	// L1822
      float v1264 = v1263 / 24.000000;	// L1825
      float v1265 = v1262 + v1264;	// L1826
      float v1266 = theta6_8;	// L1827
      float v1267 = v1266 / 720.000000;	// L1830
      float v1268 = v1265 - v1267;	// L1831
      float v1269 = theta8_8;	// L1832
      float v1270 = v1269 / 40320.000000;	// L1835
      float v1271 = v1268 + v1270;	// L1836
      float v1272 = theta10_8;	// L1837
      float v1273 = v1272 / 3628800.000000;	// L1840
      float v1274 = v1271 - v1273;	// L1841
      float v1275 = theta12_8;	// L1842
      float v1276 = v1275 / 479001600.000000;	// L1845
      float v1277 = v1274 + v1276;	// L1846
      float v1278 = theta14_8;	// L1847
      float v1279 = v1278 / 87178289152.000000;	// L1850
      float v1280 = v1277 - v1279;	// L1851
      float v1281 = theta16_8;	// L1852
      float v1282 = v1281 / 20922790576128.000000;	// L1855
      float v1283 = v1280 + v1282;	// L1856
      float cos_8;	// L1857
      cos_8 = v1283;	// L1858
      float v1285 = theta_8;	// L1859
      float v1286 = theta3_8;	// L1860
      float v1287 = v1286 / 6.000000;	// L1863
      float v1288 = v1285 - v1287;	// L1864
      float v1289 = theta5_8;	// L1865
      float v1290 = v1289 / 120.000000;	// L1868
      float v1291 = v1288 + v1290;	// L1869
      float v1292 = theta7_8;	// L1870
      float v1293 = v1292 / 5040.000000;	// L1873
      float v1294 = v1291 - v1293;	// L1874
      float v1295 = theta9_8;	// L1875
      float v1296 = v1295 / 362880.000000;	// L1878
      float v1297 = v1294 + v1296;	// L1879
      float v1298 = theta11_8;	// L1880
      float v1299 = v1298 / 39916800.000000;	// L1883
      float v1300 = v1297 - v1299;	// L1884
      float v1301 = theta13_8;	// L1885
      float v1302 = v1301 / 6227020800.000000;	// L1888
      float v1303 = v1300 + v1302;	// L1889
      float v1304 = theta15_8;	// L1890
      float v1305 = v1304 / 1307674411008.000000;	// L1893
      float v1306 = v1303 - v1305;	// L1894
      float v1307 = theta17_8;	// L1895
      float v1308 = v1307 / 355687414628352.000000;	// L1898
      float v1309 = v1306 + v1308;	// L1899
      float sin_8;	// L1900
      sin_8 = v1309;	// L1901
      int v1311 = idx1_8;	// L1902
      int v1312 = v1311;	// L1903
      float v1313 = v2[v1312];	// L1904
      float a_real_8;	// L1905
      a_real_8 = v1313;	// L1906
      int v1315 = idx1_8;	// L1907
      int v1316 = v1315;	// L1908
      float v1317 = v3[v1316];	// L1909
      float a_imag_8;	// L1910
      a_imag_8 = v1317;	// L1911
      int v1319 = idx2_8;	// L1912
      int v1320 = v1319;	// L1913
      float v1321 = v2[v1320];	// L1914
      float b_real_8;	// L1915
      b_real_8 = v1321;	// L1916
      int v1323 = idx2_8;	// L1917
      int v1324 = v1323;	// L1918
      float v1325 = v3[v1324];	// L1919
      float b_imag_8;	// L1920
      b_imag_8 = v1325;	// L1921
      float v1327 = cos_8;	// L1922
      float v1328 = b_real_8;	// L1923
      float v1329 = v1327 * v1328;	// L1924
      float v1330 = sin_8;	// L1925
      float v1331 = b_imag_8;	// L1926
      float v1332 = v1330 * v1331;	// L1927
      float v1333 = v1329 - v1332;	// L1928
      float t_real_8;	// L1929
      t_real_8 = v1333;	// L1930
      float v1335 = cos_8;	// L1931
      float v1336 = b_imag_8;	// L1932
      float v1337 = v1335 * v1336;	// L1933
      float v1338 = sin_8;	// L1934
      float v1339 = b_real_8;	// L1935
      float v1340 = v1338 * v1339;	// L1936
      float v1341 = v1337 + v1340;	// L1937
      float t_imag_8;	// L1938
      t_imag_8 = v1341;	// L1939
      float v1343 = a_real_8;	// L1940
      float v1344 = t_real_8;	// L1941
      float v1345 = v1343 + v1344;	// L1942
      int v1346 = idx1_8;	// L1943
      int v1347 = v1346;	// L1944
      v2[v1347] = v1345;	// L1945
      float v1348 = a_imag_8;	// L1946
      float v1349 = t_imag_8;	// L1947
      float v1350 = v1348 + v1349;	// L1948
      int v1351 = idx1_8;	// L1949
      int v1352 = v1351;	// L1950
      v3[v1352] = v1350;	// L1951
      float v1353 = a_real_8;	// L1952
      float v1354 = t_real_8;	// L1953
      float v1355 = v1353 - v1354;	// L1954
      int v1356 = idx2_8;	// L1955
      int v1357 = v1356;	// L1956
      v2[v1357] = v1355;	// L1957
      float v1358 = a_imag_8;	// L1958
      float v1359 = t_imag_8;	// L1959
      float v1360 = v1358 - v1359;	// L1960
      int v1361 = idx2_8;	// L1961
      int v1362 = v1361;	// L1962
      v3[v1362] = v1360;	// L1963
    }
  }
  l_S_g9_17_g9: for (int g9 = 0; g9 < 2; g9++) {	// L1966
    l_S_j9_17_j9: for (int j9 = 0; j9 < 256; j9++) {	// L1967
      int v1365 = g9;	// L1968
      int v1366 = v1365 * 512;	// L1972
      int v1367 = v1366;	// L1973
      int v1368 = j9;	// L1974
      int v1369 = v1367 + v1368;	// L1975
      int v1370 = v1369;	// L1976
      int idx1_9;	// L1977
      idx1_9 = v1370;	// L1978
      int v1372 = idx1_9;	// L1979
      int v1373 = v1372;	// L1980
      int v1374 = v1373 + 256;	// L1984
      int v1375 = v1374;	// L1985
      int idx2_9;	// L1986
      idx2_9 = v1375;	// L1987
      int v1377 = j9;	// L1988
      float v1378 = v1377;	// L1989
      float j9_f;	// L1990
      j9_f = v1378;	// L1991
      float v1380 = j9_f;	// L1995
      float v1381 = v1380 * -0.012272;	// L1996
      float theta_9;	// L1997
      theta_9 = v1381;	// L1998
      float v1383 = theta_9;	// L1999
      float v1384 = v1383 * v1383;	// L2001
      float theta2_9;	// L2002
      theta2_9 = v1384;	// L2003
      float v1386 = theta2_9;	// L2004
      float v1387 = theta_9;	// L2005
      float v1388 = v1386 * v1387;	// L2006
      float theta3_9;	// L2007
      theta3_9 = v1388;	// L2008
      float v1390 = theta2_9;	// L2009
      float v1391 = v1390 * v1390;	// L2011
      float theta4_9;	// L2012
      theta4_9 = v1391;	// L2013
      float v1393 = theta4_9;	// L2014
      float v1394 = theta_9;	// L2015
      float v1395 = v1393 * v1394;	// L2016
      float theta5_9;	// L2017
      theta5_9 = v1395;	// L2018
      float v1397 = theta4_9;	// L2019
      float v1398 = theta2_9;	// L2020
      float v1399 = v1397 * v1398;	// L2021
      float theta6_9;	// L2022
      theta6_9 = v1399;	// L2023
      float v1401 = theta6_9;	// L2024
      float v1402 = theta_9;	// L2025
      float v1403 = v1401 * v1402;	// L2026
      float theta7_9;	// L2027
      theta7_9 = v1403;	// L2028
      float v1405 = theta4_9;	// L2029
      float v1406 = v1405 * v1405;	// L2031
      float theta8_9;	// L2032
      theta8_9 = v1406;	// L2033
      float v1408 = theta8_9;	// L2034
      float v1409 = theta_9;	// L2035
      float v1410 = v1408 * v1409;	// L2036
      float theta9_9;	// L2037
      theta9_9 = v1410;	// L2038
      float v1412 = theta8_9;	// L2039
      float v1413 = theta2_9;	// L2040
      float v1414 = v1412 * v1413;	// L2041
      float theta10_9;	// L2042
      theta10_9 = v1414;	// L2043
      float v1416 = theta10_9;	// L2044
      float v1417 = theta_9;	// L2045
      float v1418 = v1416 * v1417;	// L2046
      float theta11_9;	// L2047
      theta11_9 = v1418;	// L2048
      float v1420 = theta8_9;	// L2049
      float v1421 = theta4_9;	// L2050
      float v1422 = v1420 * v1421;	// L2051
      float theta12_9;	// L2052
      theta12_9 = v1422;	// L2053
      float v1424 = theta12_9;	// L2054
      float v1425 = theta_9;	// L2055
      float v1426 = v1424 * v1425;	// L2056
      float theta13_9;	// L2057
      theta13_9 = v1426;	// L2058
      float v1428 = theta12_9;	// L2059
      float v1429 = theta2_9;	// L2060
      float v1430 = v1428 * v1429;	// L2061
      float theta14_9;	// L2062
      theta14_9 = v1430;	// L2063
      float v1432 = theta14_9;	// L2064
      float v1433 = theta_9;	// L2065
      float v1434 = v1432 * v1433;	// L2066
      float theta15_9;	// L2067
      theta15_9 = v1434;	// L2068
      float v1436 = theta8_9;	// L2069
      float v1437 = v1436 * v1436;	// L2071
      float theta16_9;	// L2072
      theta16_9 = v1437;	// L2073
      float v1439 = theta16_9;	// L2074
      float v1440 = theta_9;	// L2075
      float v1441 = v1439 * v1440;	// L2076
      float theta17_9;	// L2077
      theta17_9 = v1441;	// L2078
      float v1443 = theta2_9;	// L2079
      float v1444 = v1443 / 2.000000;	// L2082
      float v1445 = 1.000000 - v1444;	// L2085
      float v1446 = theta4_9;	// L2086
      float v1447 = v1446 / 24.000000;	// L2089
      float v1448 = v1445 + v1447;	// L2090
      float v1449 = theta6_9;	// L2091
      float v1450 = v1449 / 720.000000;	// L2094
      float v1451 = v1448 - v1450;	// L2095
      float v1452 = theta8_9;	// L2096
      float v1453 = v1452 / 40320.000000;	// L2099
      float v1454 = v1451 + v1453;	// L2100
      float v1455 = theta10_9;	// L2101
      float v1456 = v1455 / 3628800.000000;	// L2104
      float v1457 = v1454 - v1456;	// L2105
      float v1458 = theta12_9;	// L2106
      float v1459 = v1458 / 479001600.000000;	// L2109
      float v1460 = v1457 + v1459;	// L2110
      float v1461 = theta14_9;	// L2111
      float v1462 = v1461 / 87178289152.000000;	// L2114
      float v1463 = v1460 - v1462;	// L2115
      float v1464 = theta16_9;	// L2116
      float v1465 = v1464 / 20922790576128.000000;	// L2119
      float v1466 = v1463 + v1465;	// L2120
      float cos_9;	// L2121
      cos_9 = v1466;	// L2122
      float v1468 = theta_9;	// L2123
      float v1469 = theta3_9;	// L2124
      float v1470 = v1469 / 6.000000;	// L2127
      float v1471 = v1468 - v1470;	// L2128
      float v1472 = theta5_9;	// L2129
      float v1473 = v1472 / 120.000000;	// L2132
      float v1474 = v1471 + v1473;	// L2133
      float v1475 = theta7_9;	// L2134
      float v1476 = v1475 / 5040.000000;	// L2137
      float v1477 = v1474 - v1476;	// L2138
      float v1478 = theta9_9;	// L2139
      float v1479 = v1478 / 362880.000000;	// L2142
      float v1480 = v1477 + v1479;	// L2143
      float v1481 = theta11_9;	// L2144
      float v1482 = v1481 / 39916800.000000;	// L2147
      float v1483 = v1480 - v1482;	// L2148
      float v1484 = theta13_9;	// L2149
      float v1485 = v1484 / 6227020800.000000;	// L2152
      float v1486 = v1483 + v1485;	// L2153
      float v1487 = theta15_9;	// L2154
      float v1488 = v1487 / 1307674411008.000000;	// L2157
      float v1489 = v1486 - v1488;	// L2158
      float v1490 = theta17_9;	// L2159
      float v1491 = v1490 / 355687414628352.000000;	// L2162
      float v1492 = v1489 + v1491;	// L2163
      float sin_9;	// L2164
      sin_9 = v1492;	// L2165
      int v1494 = idx1_9;	// L2166
      int v1495 = v1494;	// L2167
      float v1496 = v2[v1495];	// L2168
      float a_real_9;	// L2169
      a_real_9 = v1496;	// L2170
      int v1498 = idx1_9;	// L2171
      int v1499 = v1498;	// L2172
      float v1500 = v3[v1499];	// L2173
      float a_imag_9;	// L2174
      a_imag_9 = v1500;	// L2175
      int v1502 = idx2_9;	// L2176
      int v1503 = v1502;	// L2177
      float v1504 = v2[v1503];	// L2178
      float b_real_9;	// L2179
      b_real_9 = v1504;	// L2180
      int v1506 = idx2_9;	// L2181
      int v1507 = v1506;	// L2182
      float v1508 = v3[v1507];	// L2183
      float b_imag_9;	// L2184
      b_imag_9 = v1508;	// L2185
      float v1510 = cos_9;	// L2186
      float v1511 = b_real_9;	// L2187
      float v1512 = v1510 * v1511;	// L2188
      float v1513 = sin_9;	// L2189
      float v1514 = b_imag_9;	// L2190
      float v1515 = v1513 * v1514;	// L2191
      float v1516 = v1512 - v1515;	// L2192
      float t_real_9;	// L2193
      t_real_9 = v1516;	// L2194
      float v1518 = cos_9;	// L2195
      float v1519 = b_imag_9;	// L2196
      float v1520 = v1518 * v1519;	// L2197
      float v1521 = sin_9;	// L2198
      float v1522 = b_real_9;	// L2199
      float v1523 = v1521 * v1522;	// L2200
      float v1524 = v1520 + v1523;	// L2201
      float t_imag_9;	// L2202
      t_imag_9 = v1524;	// L2203
      float v1526 = a_real_9;	// L2204
      float v1527 = t_real_9;	// L2205
      float v1528 = v1526 + v1527;	// L2206
      int v1529 = idx1_9;	// L2207
      int v1530 = v1529;	// L2208
      v2[v1530] = v1528;	// L2209
      float v1531 = a_imag_9;	// L2210
      float v1532 = t_imag_9;	// L2211
      float v1533 = v1531 + v1532;	// L2212
      int v1534 = idx1_9;	// L2213
      int v1535 = v1534;	// L2214
      v3[v1535] = v1533;	// L2215
      float v1536 = a_real_9;	// L2216
      float v1537 = t_real_9;	// L2217
      float v1538 = v1536 - v1537;	// L2218
      int v1539 = idx2_9;	// L2219
      int v1540 = v1539;	// L2220
      v2[v1540] = v1538;	// L2221
      float v1541 = a_imag_9;	// L2222
      float v1542 = t_imag_9;	// L2223
      float v1543 = v1541 - v1542;	// L2224
      int v1544 = idx2_9;	// L2225
      int v1545 = v1544;	// L2226
      v3[v1545] = v1543;	// L2227
    }
  }
  l_S_g10_19_g10: for (int g10 = 0; g10 < 1; g10++) {	// L2230
    l_S_j10_19_j10: for (int j10 = 0; j10 < 512; j10++) {	// L2231
      int v1548 = g10;	// L2232
      int v1549 = v1548 * 1024;	// L2236
      int v1550 = v1549;	// L2237
      int v1551 = j10;	// L2238
      int v1552 = v1550 + v1551;	// L2239
      int v1553 = v1552;	// L2240
      int idx1_10;	// L2241
      idx1_10 = v1553;	// L2242
      int v1555 = idx1_10;	// L2243
      int v1556 = v1555;	// L2244
      int v1557 = v1556 + 512;	// L2248
      int v1558 = v1557;	// L2249
      int idx2_10;	// L2250
      idx2_10 = v1558;	// L2251
      int v1560 = j10;	// L2252
      float v1561 = v1560;	// L2253
      float j10_f;	// L2254
      j10_f = v1561;	// L2255
      float v1563 = j10_f;	// L2259
      float v1564 = v1563 * -0.006136;	// L2260
      float theta_10;	// L2261
      theta_10 = v1564;	// L2262
      float v1566 = theta_10;	// L2263
      float v1567 = v1566 * v1566;	// L2265
      float theta2_10;	// L2266
      theta2_10 = v1567;	// L2267
      float v1569 = theta2_10;	// L2268
      float v1570 = theta_10;	// L2269
      float v1571 = v1569 * v1570;	// L2270
      float theta3_10;	// L2271
      theta3_10 = v1571;	// L2272
      float v1573 = theta2_10;	// L2273
      float v1574 = v1573 * v1573;	// L2275
      float theta4_10;	// L2276
      theta4_10 = v1574;	// L2277
      float v1576 = theta4_10;	// L2278
      float v1577 = theta_10;	// L2279
      float v1578 = v1576 * v1577;	// L2280
      float theta5_10;	// L2281
      theta5_10 = v1578;	// L2282
      float v1580 = theta4_10;	// L2283
      float v1581 = theta2_10;	// L2284
      float v1582 = v1580 * v1581;	// L2285
      float theta6_10;	// L2286
      theta6_10 = v1582;	// L2287
      float v1584 = theta6_10;	// L2288
      float v1585 = theta_10;	// L2289
      float v1586 = v1584 * v1585;	// L2290
      float theta7_10;	// L2291
      theta7_10 = v1586;	// L2292
      float v1588 = theta4_10;	// L2293
      float v1589 = v1588 * v1588;	// L2295
      float theta8_10;	// L2296
      theta8_10 = v1589;	// L2297
      float v1591 = theta8_10;	// L2298
      float v1592 = theta_10;	// L2299
      float v1593 = v1591 * v1592;	// L2300
      float theta9_10;	// L2301
      theta9_10 = v1593;	// L2302
      float v1595 = theta8_10;	// L2303
      float v1596 = theta2_10;	// L2304
      float v1597 = v1595 * v1596;	// L2305
      float theta10_10;	// L2306
      theta10_10 = v1597;	// L2307
      float v1599 = theta10_10;	// L2308
      float v1600 = theta_10;	// L2309
      float v1601 = v1599 * v1600;	// L2310
      float theta11_10;	// L2311
      theta11_10 = v1601;	// L2312
      float v1603 = theta8_10;	// L2313
      float v1604 = theta4_10;	// L2314
      float v1605 = v1603 * v1604;	// L2315
      float theta12_10;	// L2316
      theta12_10 = v1605;	// L2317
      float v1607 = theta12_10;	// L2318
      float v1608 = theta_10;	// L2319
      float v1609 = v1607 * v1608;	// L2320
      float theta13_10;	// L2321
      theta13_10 = v1609;	// L2322
      float v1611 = theta12_10;	// L2323
      float v1612 = theta2_10;	// L2324
      float v1613 = v1611 * v1612;	// L2325
      float theta14_10;	// L2326
      theta14_10 = v1613;	// L2327
      float v1615 = theta14_10;	// L2328
      float v1616 = theta_10;	// L2329
      float v1617 = v1615 * v1616;	// L2330
      float theta15_10;	// L2331
      theta15_10 = v1617;	// L2332
      float v1619 = theta8_10;	// L2333
      float v1620 = v1619 * v1619;	// L2335
      float theta16_10;	// L2336
      theta16_10 = v1620;	// L2337
      float v1622 = theta16_10;	// L2338
      float v1623 = theta_10;	// L2339
      float v1624 = v1622 * v1623;	// L2340
      float theta17_10;	// L2341
      theta17_10 = v1624;	// L2342
      float v1626 = theta2_10;	// L2343
      float v1627 = v1626 / 2.000000;	// L2346
      float v1628 = 1.000000 - v1627;	// L2349
      float v1629 = theta4_10;	// L2350
      float v1630 = v1629 / 24.000000;	// L2353
      float v1631 = v1628 + v1630;	// L2354
      float v1632 = theta6_10;	// L2355
      float v1633 = v1632 / 720.000000;	// L2358
      float v1634 = v1631 - v1633;	// L2359
      float v1635 = theta8_10;	// L2360
      float v1636 = v1635 / 40320.000000;	// L2363
      float v1637 = v1634 + v1636;	// L2364
      float v1638 = theta10_10;	// L2365
      float v1639 = v1638 / 3628800.000000;	// L2368
      float v1640 = v1637 - v1639;	// L2369
      float v1641 = theta12_10;	// L2370
      float v1642 = v1641 / 479001600.000000;	// L2373
      float v1643 = v1640 + v1642;	// L2374
      float v1644 = theta14_10;	// L2375
      float v1645 = v1644 / 87178289152.000000;	// L2378
      float v1646 = v1643 - v1645;	// L2379
      float v1647 = theta16_10;	// L2380
      float v1648 = v1647 / 20922790576128.000000;	// L2383
      float v1649 = v1646 + v1648;	// L2384
      float cos_10;	// L2385
      cos_10 = v1649;	// L2386
      float v1651 = theta_10;	// L2387
      float v1652 = theta3_10;	// L2388
      float v1653 = v1652 / 6.000000;	// L2391
      float v1654 = v1651 - v1653;	// L2392
      float v1655 = theta5_10;	// L2393
      float v1656 = v1655 / 120.000000;	// L2396
      float v1657 = v1654 + v1656;	// L2397
      float v1658 = theta7_10;	// L2398
      float v1659 = v1658 / 5040.000000;	// L2401
      float v1660 = v1657 - v1659;	// L2402
      float v1661 = theta9_10;	// L2403
      float v1662 = v1661 / 362880.000000;	// L2406
      float v1663 = v1660 + v1662;	// L2407
      float v1664 = theta11_10;	// L2408
      float v1665 = v1664 / 39916800.000000;	// L2411
      float v1666 = v1663 - v1665;	// L2412
      float v1667 = theta13_10;	// L2413
      float v1668 = v1667 / 6227020800.000000;	// L2416
      float v1669 = v1666 + v1668;	// L2417
      float v1670 = theta15_10;	// L2418
      float v1671 = v1670 / 1307674411008.000000;	// L2421
      float v1672 = v1669 - v1671;	// L2422
      float v1673 = theta17_10;	// L2423
      float v1674 = v1673 / 355687414628352.000000;	// L2426
      float v1675 = v1672 + v1674;	// L2427
      float sin_10;	// L2428
      sin_10 = v1675;	// L2429
      int v1677 = idx1_10;	// L2430
      int v1678 = v1677;	// L2431
      float v1679 = v2[v1678];	// L2432
      float a_real_10;	// L2433
      a_real_10 = v1679;	// L2434
      int v1681 = idx1_10;	// L2435
      int v1682 = v1681;	// L2436
      float v1683 = v3[v1682];	// L2437
      float a_imag_10;	// L2438
      a_imag_10 = v1683;	// L2439
      int v1685 = idx2_10;	// L2440
      int v1686 = v1685;	// L2441
      float v1687 = v2[v1686];	// L2442
      float b_real_10;	// L2443
      b_real_10 = v1687;	// L2444
      int v1689 = idx2_10;	// L2445
      int v1690 = v1689;	// L2446
      float v1691 = v3[v1690];	// L2447
      float b_imag_10;	// L2448
      b_imag_10 = v1691;	// L2449
      float v1693 = cos_10;	// L2450
      float v1694 = b_real_10;	// L2451
      float v1695 = v1693 * v1694;	// L2452
      float v1696 = sin_10;	// L2453
      float v1697 = b_imag_10;	// L2454
      float v1698 = v1696 * v1697;	// L2455
      float v1699 = v1695 - v1698;	// L2456
      float t_real_10;	// L2457
      t_real_10 = v1699;	// L2458
      float v1701 = cos_10;	// L2459
      float v1702 = b_imag_10;	// L2460
      float v1703 = v1701 * v1702;	// L2461
      float v1704 = sin_10;	// L2462
      float v1705 = b_real_10;	// L2463
      float v1706 = v1704 * v1705;	// L2464
      float v1707 = v1703 + v1706;	// L2465
      float t_imag_10;	// L2466
      t_imag_10 = v1707;	// L2467
      float v1709 = a_real_10;	// L2468
      float v1710 = t_real_10;	// L2469
      float v1711 = v1709 + v1710;	// L2470
      int v1712 = idx1_10;	// L2471
      int v1713 = v1712;	// L2472
      v2[v1713] = v1711;	// L2473
      float v1714 = a_imag_10;	// L2474
      float v1715 = t_imag_10;	// L2475
      float v1716 = v1714 + v1715;	// L2476
      int v1717 = idx1_10;	// L2477
      int v1718 = v1717;	// L2478
      v3[v1718] = v1716;	// L2479
      float v1719 = a_real_10;	// L2480
      float v1720 = t_real_10;	// L2481
      float v1721 = v1719 - v1720;	// L2482
      int v1722 = idx2_10;	// L2483
      int v1723 = v1722;	// L2484
      v2[v1723] = v1721;	// L2485
      float v1724 = a_imag_10;	// L2486
      float v1725 = t_imag_10;	// L2487
      float v1726 = v1724 - v1725;	// L2488
      int v1727 = idx2_10;	// L2489
      int v1728 = v1727;	// L2490
      v3[v1728] = v1726;	// L2491
    }
  }
}
#pragma pocc-region-end
}

