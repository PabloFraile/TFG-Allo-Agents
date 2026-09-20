
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
  float twiddle_real[512];	// L3
  float twiddle_imag[512];	// L4
  float NEG_TWO_PI;	// L8
  NEG_TWO_PI = -6.283185;	// L9
  l_S_k_0_k: for (int k = 0; k < 512; k++) {	// L10
    int v8 = k;	// L11
    float v9 = v8;	// L12
    float k_f;	// L13
    k_f = v9;	// L14
    float v11 = NEG_TWO_PI;	// L15
    float v12 = k_f;	// L16
    float v13 = v11 * v12;	// L17
    float v14 = v13 / 1024.000000;	// L20
    float ang;	// L21
    ang = v14;	// L22
    float v16 = ang;	// L23
    float v17 = v16 * v16;	// L25
    float x2;	// L26
    x2 = v17;	// L27
    float v19 = x2;	// L28
    float v20 = ang;	// L29
    float v21 = v19 * v20;	// L30
    float x3;	// L31
    x3 = v21;	// L32
    float v23 = x2;	// L33
    float v24 = v23 * v23;	// L35
    float x4;	// L36
    x4 = v24;	// L37
    float v26 = x4;	// L38
    float v27 = ang;	// L39
    float v28 = v26 * v27;	// L40
    float x5;	// L41
    x5 = v28;	// L42
    float v30 = x4;	// L43
    float v31 = x2;	// L44
    float v32 = v30 * v31;	// L45
    float x6;	// L46
    x6 = v32;	// L47
    float v34 = x6;	// L48
    float v35 = ang;	// L49
    float v36 = v34 * v35;	// L50
    float x7;	// L51
    x7 = v36;	// L52
    float v38 = x4;	// L53
    float v39 = v38 * v38;	// L55
    float x8;	// L56
    x8 = v39;	// L57
    float v41 = x8;	// L58
    float v42 = ang;	// L59
    float v43 = v41 * v42;	// L60
    float x9;	// L61
    x9 = v43;	// L62
    float v45 = x8;	// L63
    float v46 = x2;	// L64
    float v47 = v45 * v46;	// L65
    float x10;	// L66
    x10 = v47;	// L67
    float v49 = x10;	// L68
    float v50 = ang;	// L69
    float v51 = v49 * v50;	// L70
    float x11;	// L71
    x11 = v51;	// L72
    float v53 = x8;	// L73
    float v54 = x4;	// L74
    float v55 = v53 * v54;	// L75
    float x12;	// L76
    x12 = v55;	// L77
    float v57 = x12;	// L78
    float v58 = ang;	// L79
    float v59 = v57 * v58;	// L80
    float x13;	// L81
    x13 = v59;	// L82
    float v61 = x8;	// L83
    float v62 = x6;	// L84
    float v63 = v61 * v62;	// L85
    float x14;	// L86
    x14 = v63;	// L87
    float v65 = x14;	// L88
    float v66 = ang;	// L89
    float v67 = v65 * v66;	// L90
    float x15;	// L91
    x15 = v67;	// L92
    float v69 = x8;	// L93
    float v70 = v69 * v69;	// L95
    float x16;	// L96
    x16 = v70;	// L97
    float v72 = x2;	// L98
    float v73 = v72 / 2.000000;	// L101
    float v74 = 1.000000 - v73;	// L104
    float v75 = x4;	// L105
    float v76 = v75 / 24.000000;	// L108
    float v77 = v74 + v76;	// L109
    float v78 = x6;	// L110
    float v79 = v78 / 720.000000;	// L113
    float v80 = v77 - v79;	// L114
    float v81 = x8;	// L115
    float v82 = v81 / 40320.000000;	// L118
    float v83 = v80 + v82;	// L119
    float v84 = x10;	// L120
    float v85 = v84 / 3628800.000000;	// L123
    float v86 = v83 - v85;	// L124
    float v87 = x12;	// L125
    float v88 = v87 / 479001600.000000;	// L128
    float v89 = v86 + v88;	// L129
    float v90 = x14;	// L130
    float v91 = v90 / 87178289152.000000;	// L133
    float v92 = v89 - v91;	// L134
    float v93 = x16;	// L135
    float v94 = v93 / 20922790576128.000000;	// L138
    float v95 = v92 + v94;	// L139
    float cos_val;	// L140
    cos_val = v95;	// L141
    float v97 = ang;	// L142
    float v98 = x3;	// L143
    float v99 = v98 / 6.000000;	// L146
    float v100 = v97 - v99;	// L147
    float v101 = x5;	// L148
    float v102 = v101 / 120.000000;	// L151
    float v103 = v100 + v102;	// L152
    float v104 = x7;	// L153
    float v105 = v104 / 5040.000000;	// L156
    float v106 = v103 - v105;	// L157
    float v107 = x9;	// L158
    float v108 = v107 / 362880.000000;	// L161
    float v109 = v106 + v108;	// L162
    float v110 = x11;	// L163
    float v111 = v110 / 39916800.000000;	// L166
    float v112 = v109 - v111;	// L167
    float v113 = x13;	// L168
    float v114 = v113 / 6227020800.000000;	// L171
    float v115 = v112 + v114;	// L172
    float v116 = x15;	// L173
    float v117 = v116 / 1307674411008.000000;	// L176
    float v118 = v115 - v117;	// L177
    float sin_val;	// L178
    sin_val = v118;	// L179
    float v120 = cos_val;	// L180
    twiddle_real[k] = v120;	// L181
    float v121 = sin_val;	// L182
    twiddle_imag[k] = v121;	// L183
  }
  l_S_i_1_i: for (int i = 0; i < 1024; i++) {	// L185
    int v123 = i;	// L186
    int idx;	// L187
    idx = v123;	// L188
    int rev;	// L191
    rev = 0;	// L192
    l_S_b_1_b: for (int b = 0; b < 10; b++) {	// L193
      int v127 = idx;	// L194
      int v128 = v127 / 2;	// L197
      int half_idx;	// L198
      half_idx = v128;	// L199
      int v130 = idx;	// L200
      int v131 = half_idx;	// L201
      int v132 = v131;	// L202
      int v133 = v132  << 1;	// L206
      int v134 = v130;	// L207
      int v135 = v133;	// L208
      int v136 = v134 - v135;	// L209
      int v137 = v136;	// L210
      int bit;	// L211
      bit = v137;	// L212
      int v139 = half_idx;	// L213
      idx = v139;	// L214
      int v140 = rev;	// L215
      int v141 = v140;	// L216
      int v142 = v141  << 1;	// L220
      int v143 = bit;	// L221
      int v144 = v142;	// L222
      int v145 = v143;	// L223
      int v146 = v144 + v145;	// L224
      int v147 = v146;	// L225
      rev = v147;	// L226
    }
    float v148 = v0[i];	// L228
    int v149 = rev;	// L229
    int v150 = v149;	// L230
    v2[v150] = v148;	// L231
    float v151 = v1[i];	// L232
    int v152 = rev;	// L233
    int v153 = v152;	// L234
    v3[v153] = v151;	// L235
  }
  l_S_g1_3_g1: for (int g1 = 0; g1 < 512; g1++) {	// L237
    int v155 = g1;	// L238
    int v156 = v155  << 1;	// L242
    int v157 = v156;	// L243
    int base_1;	// L244
    base_1 = v157;	// L245
    l_S_j1_3_j1: for (int j1 = 0; j1 < 1; j1++) {	// L246
      int v160 = base_1;	// L247
      int v161 = v160;	// L248
      int v162 = j1;	// L249
      int v163 = v161 + v162;	// L250
      int v164 = v163;	// L251
      int idx1_1;	// L252
      idx1_1 = v164;	// L253
      int v166 = idx1_1;	// L254
      int v167 = v166;	// L255
      int v168 = v167 + 1;	// L259
      int v169 = v168;	// L260
      int idx2_1;	// L261
      idx2_1 = v169;	// L262
      int v171 = j1;	// L263
      int v172 = v171 * 512;	// L267
      int v173 = v172;	// L268
      int tw_idx_1;	// L269
      tw_idx_1 = v173;	// L270
      int v175 = tw_idx_1;	// L271
      int v176 = v175;	// L272
      float v177 = twiddle_real[v176];	// L273
      float tr_1;	// L274
      tr_1 = v177;	// L275
      int v179 = tw_idx_1;	// L276
      int v180 = v179;	// L277
      float v181 = twiddle_imag[v180];	// L278
      float ti_1;	// L279
      ti_1 = v181;	// L280
      int v183 = idx1_1;	// L281
      int v184 = v183;	// L282
      float v185 = v2[v184];	// L283
      float ur_1;	// L284
      ur_1 = v185;	// L285
      int v187 = idx1_1;	// L286
      int v188 = v187;	// L287
      float v189 = v3[v188];	// L288
      float ui_1;	// L289
      ui_1 = v189;	// L290
      int v191 = idx2_1;	// L291
      int v192 = v191;	// L292
      float v193 = v2[v192];	// L293
      float vr_1;	// L294
      vr_1 = v193;	// L295
      int v195 = idx2_1;	// L296
      int v196 = v195;	// L297
      float v197 = v3[v196];	// L298
      float vi_1;	// L299
      vi_1 = v197;	// L300
      float v199 = tr_1;	// L301
      float v200 = vr_1;	// L302
      float v201 = v199 * v200;	// L303
      float v202 = ti_1;	// L304
      float v203 = vi_1;	// L305
      float v204 = v202 * v203;	// L306
      float v205 = v201 - v204;	// L307
      float trv_1;	// L308
      trv_1 = v205;	// L309
      float v207 = tr_1;	// L310
      float v208 = vi_1;	// L311
      float v209 = v207 * v208;	// L312
      float v210 = ti_1;	// L313
      float v211 = vr_1;	// L314
      float v212 = v210 * v211;	// L315
      float v213 = v209 + v212;	// L316
      float tiv_1;	// L317
      tiv_1 = v213;	// L318
      float v215 = ur_1;	// L319
      float v216 = trv_1;	// L320
      float v217 = v215 + v216;	// L321
      int v218 = idx1_1;	// L322
      int v219 = v218;	// L323
      v2[v219] = v217;	// L324
      float v220 = ui_1;	// L325
      float v221 = tiv_1;	// L326
      float v222 = v220 + v221;	// L327
      int v223 = idx1_1;	// L328
      int v224 = v223;	// L329
      v3[v224] = v222;	// L330
      float v225 = ur_1;	// L331
      float v226 = trv_1;	// L332
      float v227 = v225 - v226;	// L333
      int v228 = idx2_1;	// L334
      int v229 = v228;	// L335
      v2[v229] = v227;	// L336
      float v230 = ui_1;	// L337
      float v231 = tiv_1;	// L338
      float v232 = v230 - v231;	// L339
      int v233 = idx2_1;	// L340
      int v234 = v233;	// L341
      v3[v234] = v232;	// L342
    }
  }
  l_S_g2_5_g2: for (int g2 = 0; g2 < 256; g2++) {	// L345
    int v236 = g2;	// L346
    int v237 = v236 * 4;	// L350
    int v238 = v237;	// L351
    int base_2;	// L352
    base_2 = v238;	// L353
    l_S_j2_5_j2: for (int j2 = 0; j2 < 2; j2++) {	// L354
      int v241 = base_2;	// L355
      int v242 = v241;	// L356
      int v243 = j2;	// L357
      int v244 = v242 + v243;	// L358
      int v245 = v244;	// L359
      int idx1_2;	// L360
      idx1_2 = v245;	// L361
      int v247 = idx1_2;	// L362
      int v248 = v247;	// L363
      int v249 = v248 + 2;	// L367
      int v250 = v249;	// L368
      int idx2_2;	// L369
      idx2_2 = v250;	// L370
      int v252 = j2;	// L371
      int v253 = v252 * 256;	// L375
      int v254 = v253;	// L376
      int tw_idx_2;	// L377
      tw_idx_2 = v254;	// L378
      int v256 = tw_idx_2;	// L379
      int v257 = v256;	// L380
      float v258 = twiddle_real[v257];	// L381
      float tr_2;	// L382
      tr_2 = v258;	// L383
      int v260 = tw_idx_2;	// L384
      int v261 = v260;	// L385
      float v262 = twiddle_imag[v261];	// L386
      float ti_2;	// L387
      ti_2 = v262;	// L388
      int v264 = idx1_2;	// L389
      int v265 = v264;	// L390
      float v266 = v2[v265];	// L391
      float ur_2;	// L392
      ur_2 = v266;	// L393
      int v268 = idx1_2;	// L394
      int v269 = v268;	// L395
      float v270 = v3[v269];	// L396
      float ui_2;	// L397
      ui_2 = v270;	// L398
      int v272 = idx2_2;	// L399
      int v273 = v272;	// L400
      float v274 = v2[v273];	// L401
      float vr_2;	// L402
      vr_2 = v274;	// L403
      int v276 = idx2_2;	// L404
      int v277 = v276;	// L405
      float v278 = v3[v277];	// L406
      float vi_2;	// L407
      vi_2 = v278;	// L408
      float v280 = tr_2;	// L409
      float v281 = vr_2;	// L410
      float v282 = v280 * v281;	// L411
      float v283 = ti_2;	// L412
      float v284 = vi_2;	// L413
      float v285 = v283 * v284;	// L414
      float v286 = v282 - v285;	// L415
      float trv_2;	// L416
      trv_2 = v286;	// L417
      float v288 = tr_2;	// L418
      float v289 = vi_2;	// L419
      float v290 = v288 * v289;	// L420
      float v291 = ti_2;	// L421
      float v292 = vr_2;	// L422
      float v293 = v291 * v292;	// L423
      float v294 = v290 + v293;	// L424
      float tiv_2;	// L425
      tiv_2 = v294;	// L426
      float v296 = ur_2;	// L427
      float v297 = trv_2;	// L428
      float v298 = v296 + v297;	// L429
      int v299 = idx1_2;	// L430
      int v300 = v299;	// L431
      v2[v300] = v298;	// L432
      float v301 = ui_2;	// L433
      float v302 = tiv_2;	// L434
      float v303 = v301 + v302;	// L435
      int v304 = idx1_2;	// L436
      int v305 = v304;	// L437
      v3[v305] = v303;	// L438
      float v306 = ur_2;	// L439
      float v307 = trv_2;	// L440
      float v308 = v306 - v307;	// L441
      int v309 = idx2_2;	// L442
      int v310 = v309;	// L443
      v2[v310] = v308;	// L444
      float v311 = ui_2;	// L445
      float v312 = tiv_2;	// L446
      float v313 = v311 - v312;	// L447
      int v314 = idx2_2;	// L448
      int v315 = v314;	// L449
      v3[v315] = v313;	// L450
    }
  }
  l_S_g3_7_g3: for (int g3 = 0; g3 < 128; g3++) {	// L453
    int v317 = g3;	// L454
    int v318 = v317 * 8;	// L458
    int v319 = v318;	// L459
    int base_3;	// L460
    base_3 = v319;	// L461
    l_S_j3_7_j3: for (int j3 = 0; j3 < 4; j3++) {	// L462
      int v322 = base_3;	// L463
      int v323 = v322;	// L464
      int v324 = j3;	// L465
      int v325 = v323 + v324;	// L466
      int v326 = v325;	// L467
      int idx1_3;	// L468
      idx1_3 = v326;	// L469
      int v328 = idx1_3;	// L470
      int v329 = v328;	// L471
      int v330 = v329 + 4;	// L475
      int v331 = v330;	// L476
      int idx2_3;	// L477
      idx2_3 = v331;	// L478
      int v333 = j3;	// L479
      int v334 = v333 * 128;	// L483
      int v335 = v334;	// L484
      int tw_idx_3;	// L485
      tw_idx_3 = v335;	// L486
      int v337 = tw_idx_3;	// L487
      int v338 = v337;	// L488
      float v339 = twiddle_real[v338];	// L489
      float tr_3;	// L490
      tr_3 = v339;	// L491
      int v341 = tw_idx_3;	// L492
      int v342 = v341;	// L493
      float v343 = twiddle_imag[v342];	// L494
      float ti_3;	// L495
      ti_3 = v343;	// L496
      int v345 = idx1_3;	// L497
      int v346 = v345;	// L498
      float v347 = v2[v346];	// L499
      float ur_3;	// L500
      ur_3 = v347;	// L501
      int v349 = idx1_3;	// L502
      int v350 = v349;	// L503
      float v351 = v3[v350];	// L504
      float ui_3;	// L505
      ui_3 = v351;	// L506
      int v353 = idx2_3;	// L507
      int v354 = v353;	// L508
      float v355 = v2[v354];	// L509
      float vr_3;	// L510
      vr_3 = v355;	// L511
      int v357 = idx2_3;	// L512
      int v358 = v357;	// L513
      float v359 = v3[v358];	// L514
      float vi_3;	// L515
      vi_3 = v359;	// L516
      float v361 = tr_3;	// L517
      float v362 = vr_3;	// L518
      float v363 = v361 * v362;	// L519
      float v364 = ti_3;	// L520
      float v365 = vi_3;	// L521
      float v366 = v364 * v365;	// L522
      float v367 = v363 - v366;	// L523
      float trv_3;	// L524
      trv_3 = v367;	// L525
      float v369 = tr_3;	// L526
      float v370 = vi_3;	// L527
      float v371 = v369 * v370;	// L528
      float v372 = ti_3;	// L529
      float v373 = vr_3;	// L530
      float v374 = v372 * v373;	// L531
      float v375 = v371 + v374;	// L532
      float tiv_3;	// L533
      tiv_3 = v375;	// L534
      float v377 = ur_3;	// L535
      float v378 = trv_3;	// L536
      float v379 = v377 + v378;	// L537
      int v380 = idx1_3;	// L538
      int v381 = v380;	// L539
      v2[v381] = v379;	// L540
      float v382 = ui_3;	// L541
      float v383 = tiv_3;	// L542
      float v384 = v382 + v383;	// L543
      int v385 = idx1_3;	// L544
      int v386 = v385;	// L545
      v3[v386] = v384;	// L546
      float v387 = ur_3;	// L547
      float v388 = trv_3;	// L548
      float v389 = v387 - v388;	// L549
      int v390 = idx2_3;	// L550
      int v391 = v390;	// L551
      v2[v391] = v389;	// L552
      float v392 = ui_3;	// L553
      float v393 = tiv_3;	// L554
      float v394 = v392 - v393;	// L555
      int v395 = idx2_3;	// L556
      int v396 = v395;	// L557
      v3[v396] = v394;	// L558
    }
  }
  l_S_g4_9_g4: for (int g4 = 0; g4 < 64; g4++) {	// L561
    int v398 = g4;	// L562
    int v399 = v398 * 16;	// L566
    int v400 = v399;	// L567
    int base_4;	// L568
    base_4 = v400;	// L569
    l_S_j4_9_j4: for (int j4 = 0; j4 < 8; j4++) {	// L570
      int v403 = base_4;	// L571
      int v404 = v403;	// L572
      int v405 = j4;	// L573
      int v406 = v404 + v405;	// L574
      int v407 = v406;	// L575
      int idx1_4;	// L576
      idx1_4 = v407;	// L577
      int v409 = idx1_4;	// L578
      int v410 = v409;	// L579
      int v411 = v410 + 8;	// L583
      int v412 = v411;	// L584
      int idx2_4;	// L585
      idx2_4 = v412;	// L586
      int v414 = j4;	// L587
      int v415 = v414 * 64;	// L591
      int v416 = v415;	// L592
      int tw_idx_4;	// L593
      tw_idx_4 = v416;	// L594
      int v418 = tw_idx_4;	// L595
      int v419 = v418;	// L596
      float v420 = twiddle_real[v419];	// L597
      float tr_4;	// L598
      tr_4 = v420;	// L599
      int v422 = tw_idx_4;	// L600
      int v423 = v422;	// L601
      float v424 = twiddle_imag[v423];	// L602
      float ti_4;	// L603
      ti_4 = v424;	// L604
      int v426 = idx1_4;	// L605
      int v427 = v426;	// L606
      float v428 = v2[v427];	// L607
      float ur_4;	// L608
      ur_4 = v428;	// L609
      int v430 = idx1_4;	// L610
      int v431 = v430;	// L611
      float v432 = v3[v431];	// L612
      float ui_4;	// L613
      ui_4 = v432;	// L614
      int v434 = idx2_4;	// L615
      int v435 = v434;	// L616
      float v436 = v2[v435];	// L617
      float vr_4;	// L618
      vr_4 = v436;	// L619
      int v438 = idx2_4;	// L620
      int v439 = v438;	// L621
      float v440 = v3[v439];	// L622
      float vi_4;	// L623
      vi_4 = v440;	// L624
      float v442 = tr_4;	// L625
      float v443 = vr_4;	// L626
      float v444 = v442 * v443;	// L627
      float v445 = ti_4;	// L628
      float v446 = vi_4;	// L629
      float v447 = v445 * v446;	// L630
      float v448 = v444 - v447;	// L631
      float trv_4;	// L632
      trv_4 = v448;	// L633
      float v450 = tr_4;	// L634
      float v451 = vi_4;	// L635
      float v452 = v450 * v451;	// L636
      float v453 = ti_4;	// L637
      float v454 = vr_4;	// L638
      float v455 = v453 * v454;	// L639
      float v456 = v452 + v455;	// L640
      float tiv_4;	// L641
      tiv_4 = v456;	// L642
      float v458 = ur_4;	// L643
      float v459 = trv_4;	// L644
      float v460 = v458 + v459;	// L645
      int v461 = idx1_4;	// L646
      int v462 = v461;	// L647
      v2[v462] = v460;	// L648
      float v463 = ui_4;	// L649
      float v464 = tiv_4;	// L650
      float v465 = v463 + v464;	// L651
      int v466 = idx1_4;	// L652
      int v467 = v466;	// L653
      v3[v467] = v465;	// L654
      float v468 = ur_4;	// L655
      float v469 = trv_4;	// L656
      float v470 = v468 - v469;	// L657
      int v471 = idx2_4;	// L658
      int v472 = v471;	// L659
      v2[v472] = v470;	// L660
      float v473 = ui_4;	// L661
      float v474 = tiv_4;	// L662
      float v475 = v473 - v474;	// L663
      int v476 = idx2_4;	// L664
      int v477 = v476;	// L665
      v3[v477] = v475;	// L666
    }
  }
  l_S_g5_11_g5: for (int g5 = 0; g5 < 32; g5++) {	// L669
    int v479 = g5;	// L670
    int v480 = v479 * 32;	// L674
    int v481 = v480;	// L675
    int base_5;	// L676
    base_5 = v481;	// L677
    l_S_j5_11_j5: for (int j5 = 0; j5 < 16; j5++) {	// L678
      int v484 = base_5;	// L679
      int v485 = v484;	// L680
      int v486 = j5;	// L681
      int v487 = v485 + v486;	// L682
      int v488 = v487;	// L683
      int idx1_5;	// L684
      idx1_5 = v488;	// L685
      int v490 = idx1_5;	// L686
      int v491 = v490;	// L687
      int v492 = v491 + 16;	// L691
      int v493 = v492;	// L692
      int idx2_5;	// L693
      idx2_5 = v493;	// L694
      int v495 = j5;	// L695
      int v496 = v495 * 32;	// L699
      int v497 = v496;	// L700
      int tw_idx_5;	// L701
      tw_idx_5 = v497;	// L702
      int v499 = tw_idx_5;	// L703
      int v500 = v499;	// L704
      float v501 = twiddle_real[v500];	// L705
      float tr_5;	// L706
      tr_5 = v501;	// L707
      int v503 = tw_idx_5;	// L708
      int v504 = v503;	// L709
      float v505 = twiddle_imag[v504];	// L710
      float ti_5;	// L711
      ti_5 = v505;	// L712
      int v507 = idx1_5;	// L713
      int v508 = v507;	// L714
      float v509 = v2[v508];	// L715
      float ur_5;	// L716
      ur_5 = v509;	// L717
      int v511 = idx1_5;	// L718
      int v512 = v511;	// L719
      float v513 = v3[v512];	// L720
      float ui_5;	// L721
      ui_5 = v513;	// L722
      int v515 = idx2_5;	// L723
      int v516 = v515;	// L724
      float v517 = v2[v516];	// L725
      float vr_5;	// L726
      vr_5 = v517;	// L727
      int v519 = idx2_5;	// L728
      int v520 = v519;	// L729
      float v521 = v3[v520];	// L730
      float vi_5;	// L731
      vi_5 = v521;	// L732
      float v523 = tr_5;	// L733
      float v524 = vr_5;	// L734
      float v525 = v523 * v524;	// L735
      float v526 = ti_5;	// L736
      float v527 = vi_5;	// L737
      float v528 = v526 * v527;	// L738
      float v529 = v525 - v528;	// L739
      float trv_5;	// L740
      trv_5 = v529;	// L741
      float v531 = tr_5;	// L742
      float v532 = vi_5;	// L743
      float v533 = v531 * v532;	// L744
      float v534 = ti_5;	// L745
      float v535 = vr_5;	// L746
      float v536 = v534 * v535;	// L747
      float v537 = v533 + v536;	// L748
      float tiv_5;	// L749
      tiv_5 = v537;	// L750
      float v539 = ur_5;	// L751
      float v540 = trv_5;	// L752
      float v541 = v539 + v540;	// L753
      int v542 = idx1_5;	// L754
      int v543 = v542;	// L755
      v2[v543] = v541;	// L756
      float v544 = ui_5;	// L757
      float v545 = tiv_5;	// L758
      float v546 = v544 + v545;	// L759
      int v547 = idx1_5;	// L760
      int v548 = v547;	// L761
      v3[v548] = v546;	// L762
      float v549 = ur_5;	// L763
      float v550 = trv_5;	// L764
      float v551 = v549 - v550;	// L765
      int v552 = idx2_5;	// L766
      int v553 = v552;	// L767
      v2[v553] = v551;	// L768
      float v554 = ui_5;	// L769
      float v555 = tiv_5;	// L770
      float v556 = v554 - v555;	// L771
      int v557 = idx2_5;	// L772
      int v558 = v557;	// L773
      v3[v558] = v556;	// L774
    }
  }
  l_S_g6_13_g6: for (int g6 = 0; g6 < 16; g6++) {	// L777
    int v560 = g6;	// L778
    int v561 = v560 * 64;	// L782
    int v562 = v561;	// L783
    int base_6;	// L784
    base_6 = v562;	// L785
    l_S_j6_13_j6: for (int j6 = 0; j6 < 32; j6++) {	// L786
      int v565 = base_6;	// L787
      int v566 = v565;	// L788
      int v567 = j6;	// L789
      int v568 = v566 + v567;	// L790
      int v569 = v568;	// L791
      int idx1_6;	// L792
      idx1_6 = v569;	// L793
      int v571 = idx1_6;	// L794
      int v572 = v571;	// L795
      int v573 = v572 + 32;	// L799
      int v574 = v573;	// L800
      int idx2_6;	// L801
      idx2_6 = v574;	// L802
      int v576 = j6;	// L803
      int v577 = v576 * 16;	// L807
      int v578 = v577;	// L808
      int tw_idx_6;	// L809
      tw_idx_6 = v578;	// L810
      int v580 = tw_idx_6;	// L811
      int v581 = v580;	// L812
      float v582 = twiddle_real[v581];	// L813
      float tr_6;	// L814
      tr_6 = v582;	// L815
      int v584 = tw_idx_6;	// L816
      int v585 = v584;	// L817
      float v586 = twiddle_imag[v585];	// L818
      float ti_6;	// L819
      ti_6 = v586;	// L820
      int v588 = idx1_6;	// L821
      int v589 = v588;	// L822
      float v590 = v2[v589];	// L823
      float ur_6;	// L824
      ur_6 = v590;	// L825
      int v592 = idx1_6;	// L826
      int v593 = v592;	// L827
      float v594 = v3[v593];	// L828
      float ui_6;	// L829
      ui_6 = v594;	// L830
      int v596 = idx2_6;	// L831
      int v597 = v596;	// L832
      float v598 = v2[v597];	// L833
      float vr_6;	// L834
      vr_6 = v598;	// L835
      int v600 = idx2_6;	// L836
      int v601 = v600;	// L837
      float v602 = v3[v601];	// L838
      float vi_6;	// L839
      vi_6 = v602;	// L840
      float v604 = tr_6;	// L841
      float v605 = vr_6;	// L842
      float v606 = v604 * v605;	// L843
      float v607 = ti_6;	// L844
      float v608 = vi_6;	// L845
      float v609 = v607 * v608;	// L846
      float v610 = v606 - v609;	// L847
      float trv_6;	// L848
      trv_6 = v610;	// L849
      float v612 = tr_6;	// L850
      float v613 = vi_6;	// L851
      float v614 = v612 * v613;	// L852
      float v615 = ti_6;	// L853
      float v616 = vr_6;	// L854
      float v617 = v615 * v616;	// L855
      float v618 = v614 + v617;	// L856
      float tiv_6;	// L857
      tiv_6 = v618;	// L858
      float v620 = ur_6;	// L859
      float v621 = trv_6;	// L860
      float v622 = v620 + v621;	// L861
      int v623 = idx1_6;	// L862
      int v624 = v623;	// L863
      v2[v624] = v622;	// L864
      float v625 = ui_6;	// L865
      float v626 = tiv_6;	// L866
      float v627 = v625 + v626;	// L867
      int v628 = idx1_6;	// L868
      int v629 = v628;	// L869
      v3[v629] = v627;	// L870
      float v630 = ur_6;	// L871
      float v631 = trv_6;	// L872
      float v632 = v630 - v631;	// L873
      int v633 = idx2_6;	// L874
      int v634 = v633;	// L875
      v2[v634] = v632;	// L876
      float v635 = ui_6;	// L877
      float v636 = tiv_6;	// L878
      float v637 = v635 - v636;	// L879
      int v638 = idx2_6;	// L880
      int v639 = v638;	// L881
      v3[v639] = v637;	// L882
    }
  }
  l_S_g7_15_g7: for (int g7 = 0; g7 < 8; g7++) {	// L885
    int v641 = g7;	// L886
    int v642 = v641 * 128;	// L890
    int v643 = v642;	// L891
    int base_7;	// L892
    base_7 = v643;	// L893
    l_S_j7_15_j7: for (int j7 = 0; j7 < 64; j7++) {	// L894
      int v646 = base_7;	// L895
      int v647 = v646;	// L896
      int v648 = j7;	// L897
      int v649 = v647 + v648;	// L898
      int v650 = v649;	// L899
      int idx1_7;	// L900
      idx1_7 = v650;	// L901
      int v652 = idx1_7;	// L902
      int v653 = v652;	// L903
      int v654 = v653 + 64;	// L907
      int v655 = v654;	// L908
      int idx2_7;	// L909
      idx2_7 = v655;	// L910
      int v657 = j7;	// L911
      int v658 = v657 * 8;	// L915
      int v659 = v658;	// L916
      int tw_idx_7;	// L917
      tw_idx_7 = v659;	// L918
      int v661 = tw_idx_7;	// L919
      int v662 = v661;	// L920
      float v663 = twiddle_real[v662];	// L921
      float tr_7;	// L922
      tr_7 = v663;	// L923
      int v665 = tw_idx_7;	// L924
      int v666 = v665;	// L925
      float v667 = twiddle_imag[v666];	// L926
      float ti_7;	// L927
      ti_7 = v667;	// L928
      int v669 = idx1_7;	// L929
      int v670 = v669;	// L930
      float v671 = v2[v670];	// L931
      float ur_7;	// L932
      ur_7 = v671;	// L933
      int v673 = idx1_7;	// L934
      int v674 = v673;	// L935
      float v675 = v3[v674];	// L936
      float ui_7;	// L937
      ui_7 = v675;	// L938
      int v677 = idx2_7;	// L939
      int v678 = v677;	// L940
      float v679 = v2[v678];	// L941
      float vr_7;	// L942
      vr_7 = v679;	// L943
      int v681 = idx2_7;	// L944
      int v682 = v681;	// L945
      float v683 = v3[v682];	// L946
      float vi_7;	// L947
      vi_7 = v683;	// L948
      float v685 = tr_7;	// L949
      float v686 = vr_7;	// L950
      float v687 = v685 * v686;	// L951
      float v688 = ti_7;	// L952
      float v689 = vi_7;	// L953
      float v690 = v688 * v689;	// L954
      float v691 = v687 - v690;	// L955
      float trv_7;	// L956
      trv_7 = v691;	// L957
      float v693 = tr_7;	// L958
      float v694 = vi_7;	// L959
      float v695 = v693 * v694;	// L960
      float v696 = ti_7;	// L961
      float v697 = vr_7;	// L962
      float v698 = v696 * v697;	// L963
      float v699 = v695 + v698;	// L964
      float tiv_7;	// L965
      tiv_7 = v699;	// L966
      float v701 = ur_7;	// L967
      float v702 = trv_7;	// L968
      float v703 = v701 + v702;	// L969
      int v704 = idx1_7;	// L970
      int v705 = v704;	// L971
      v2[v705] = v703;	// L972
      float v706 = ui_7;	// L973
      float v707 = tiv_7;	// L974
      float v708 = v706 + v707;	// L975
      int v709 = idx1_7;	// L976
      int v710 = v709;	// L977
      v3[v710] = v708;	// L978
      float v711 = ur_7;	// L979
      float v712 = trv_7;	// L980
      float v713 = v711 - v712;	// L981
      int v714 = idx2_7;	// L982
      int v715 = v714;	// L983
      v2[v715] = v713;	// L984
      float v716 = ui_7;	// L985
      float v717 = tiv_7;	// L986
      float v718 = v716 - v717;	// L987
      int v719 = idx2_7;	// L988
      int v720 = v719;	// L989
      v3[v720] = v718;	// L990
    }
  }
  l_S_g8_17_g8: for (int g8 = 0; g8 < 4; g8++) {	// L993
    int v722 = g8;	// L994
    int v723 = v722 * 256;	// L998
    int v724 = v723;	// L999
    int base_8;	// L1000
    base_8 = v724;	// L1001
    l_S_j8_17_j8: for (int j8 = 0; j8 < 128; j8++) {	// L1002
      int v727 = base_8;	// L1003
      int v728 = v727;	// L1004
      int v729 = j8;	// L1005
      int v730 = v728 + v729;	// L1006
      int v731 = v730;	// L1007
      int idx1_8;	// L1008
      idx1_8 = v731;	// L1009
      int v733 = idx1_8;	// L1010
      int v734 = v733;	// L1011
      int v735 = v734 + 128;	// L1015
      int v736 = v735;	// L1016
      int idx2_8;	// L1017
      idx2_8 = v736;	// L1018
      int v738 = j8;	// L1019
      int v739 = v738 * 4;	// L1023
      int v740 = v739;	// L1024
      int tw_idx_8;	// L1025
      tw_idx_8 = v740;	// L1026
      int v742 = tw_idx_8;	// L1027
      int v743 = v742;	// L1028
      float v744 = twiddle_real[v743];	// L1029
      float tr_8;	// L1030
      tr_8 = v744;	// L1031
      int v746 = tw_idx_8;	// L1032
      int v747 = v746;	// L1033
      float v748 = twiddle_imag[v747];	// L1034
      float ti_8;	// L1035
      ti_8 = v748;	// L1036
      int v750 = idx1_8;	// L1037
      int v751 = v750;	// L1038
      float v752 = v2[v751];	// L1039
      float ur_8;	// L1040
      ur_8 = v752;	// L1041
      int v754 = idx1_8;	// L1042
      int v755 = v754;	// L1043
      float v756 = v3[v755];	// L1044
      float ui_8;	// L1045
      ui_8 = v756;	// L1046
      int v758 = idx2_8;	// L1047
      int v759 = v758;	// L1048
      float v760 = v2[v759];	// L1049
      float vr_8;	// L1050
      vr_8 = v760;	// L1051
      int v762 = idx2_8;	// L1052
      int v763 = v762;	// L1053
      float v764 = v3[v763];	// L1054
      float vi_8;	// L1055
      vi_8 = v764;	// L1056
      float v766 = tr_8;	// L1057
      float v767 = vr_8;	// L1058
      float v768 = v766 * v767;	// L1059
      float v769 = ti_8;	// L1060
      float v770 = vi_8;	// L1061
      float v771 = v769 * v770;	// L1062
      float v772 = v768 - v771;	// L1063
      float trv_8;	// L1064
      trv_8 = v772;	// L1065
      float v774 = tr_8;	// L1066
      float v775 = vi_8;	// L1067
      float v776 = v774 * v775;	// L1068
      float v777 = ti_8;	// L1069
      float v778 = vr_8;	// L1070
      float v779 = v777 * v778;	// L1071
      float v780 = v776 + v779;	// L1072
      float tiv_8;	// L1073
      tiv_8 = v780;	// L1074
      float v782 = ur_8;	// L1075
      float v783 = trv_8;	// L1076
      float v784 = v782 + v783;	// L1077
      int v785 = idx1_8;	// L1078
      int v786 = v785;	// L1079
      v2[v786] = v784;	// L1080
      float v787 = ui_8;	// L1081
      float v788 = tiv_8;	// L1082
      float v789 = v787 + v788;	// L1083
      int v790 = idx1_8;	// L1084
      int v791 = v790;	// L1085
      v3[v791] = v789;	// L1086
      float v792 = ur_8;	// L1087
      float v793 = trv_8;	// L1088
      float v794 = v792 - v793;	// L1089
      int v795 = idx2_8;	// L1090
      int v796 = v795;	// L1091
      v2[v796] = v794;	// L1092
      float v797 = ui_8;	// L1093
      float v798 = tiv_8;	// L1094
      float v799 = v797 - v798;	// L1095
      int v800 = idx2_8;	// L1096
      int v801 = v800;	// L1097
      v3[v801] = v799;	// L1098
    }
  }
  l_S_g9_19_g9: for (int g9 = 0; g9 < 2; g9++) {	// L1101
    int v803 = g9;	// L1102
    int v804 = v803 * 512;	// L1106
    int v805 = v804;	// L1107
    int base_9;	// L1108
    base_9 = v805;	// L1109
    l_S_j9_19_j9: for (int j9 = 0; j9 < 256; j9++) {	// L1110
      int v808 = base_9;	// L1111
      int v809 = v808;	// L1112
      int v810 = j9;	// L1113
      int v811 = v809 + v810;	// L1114
      int v812 = v811;	// L1115
      int idx1_9;	// L1116
      idx1_9 = v812;	// L1117
      int v814 = idx1_9;	// L1118
      int v815 = v814;	// L1119
      int v816 = v815 + 256;	// L1123
      int v817 = v816;	// L1124
      int idx2_9;	// L1125
      idx2_9 = v817;	// L1126
      int v819 = j9;	// L1127
      int v820 = v819  << 1;	// L1131
      int v821 = v820;	// L1132
      int tw_idx_9;	// L1133
      tw_idx_9 = v821;	// L1134
      int v823 = tw_idx_9;	// L1135
      int v824 = v823;	// L1136
      float v825 = twiddle_real[v824];	// L1137
      float tr_9;	// L1138
      tr_9 = v825;	// L1139
      int v827 = tw_idx_9;	// L1140
      int v828 = v827;	// L1141
      float v829 = twiddle_imag[v828];	// L1142
      float ti_9;	// L1143
      ti_9 = v829;	// L1144
      int v831 = idx1_9;	// L1145
      int v832 = v831;	// L1146
      float v833 = v2[v832];	// L1147
      float ur_9;	// L1148
      ur_9 = v833;	// L1149
      int v835 = idx1_9;	// L1150
      int v836 = v835;	// L1151
      float v837 = v3[v836];	// L1152
      float ui_9;	// L1153
      ui_9 = v837;	// L1154
      int v839 = idx2_9;	// L1155
      int v840 = v839;	// L1156
      float v841 = v2[v840];	// L1157
      float vr_9;	// L1158
      vr_9 = v841;	// L1159
      int v843 = idx2_9;	// L1160
      int v844 = v843;	// L1161
      float v845 = v3[v844];	// L1162
      float vi_9;	// L1163
      vi_9 = v845;	// L1164
      float v847 = tr_9;	// L1165
      float v848 = vr_9;	// L1166
      float v849 = v847 * v848;	// L1167
      float v850 = ti_9;	// L1168
      float v851 = vi_9;	// L1169
      float v852 = v850 * v851;	// L1170
      float v853 = v849 - v852;	// L1171
      float trv_9;	// L1172
      trv_9 = v853;	// L1173
      float v855 = tr_9;	// L1174
      float v856 = vi_9;	// L1175
      float v857 = v855 * v856;	// L1176
      float v858 = ti_9;	// L1177
      float v859 = vr_9;	// L1178
      float v860 = v858 * v859;	// L1179
      float v861 = v857 + v860;	// L1180
      float tiv_9;	// L1181
      tiv_9 = v861;	// L1182
      float v863 = ur_9;	// L1183
      float v864 = trv_9;	// L1184
      float v865 = v863 + v864;	// L1185
      int v866 = idx1_9;	// L1186
      int v867 = v866;	// L1187
      v2[v867] = v865;	// L1188
      float v868 = ui_9;	// L1189
      float v869 = tiv_9;	// L1190
      float v870 = v868 + v869;	// L1191
      int v871 = idx1_9;	// L1192
      int v872 = v871;	// L1193
      v3[v872] = v870;	// L1194
      float v873 = ur_9;	// L1195
      float v874 = trv_9;	// L1196
      float v875 = v873 - v874;	// L1197
      int v876 = idx2_9;	// L1198
      int v877 = v876;	// L1199
      v2[v877] = v875;	// L1200
      float v878 = ui_9;	// L1201
      float v879 = tiv_9;	// L1202
      float v880 = v878 - v879;	// L1203
      int v881 = idx2_9;	// L1204
      int v882 = v881;	// L1205
      v3[v882] = v880;	// L1206
    }
  }
  l_S_g10_21_g10: for (int g10 = 0; g10 < 1; g10++) {	// L1209
    int v884 = g10;	// L1210
    int v885 = v884 * 1024;	// L1214
    int v886 = v885;	// L1215
    int base_10;	// L1216
    base_10 = v886;	// L1217
    l_S_j10_21_j10: for (int j10 = 0; j10 < 512; j10++) {	// L1218
      int v889 = base_10;	// L1219
      int v890 = v889;	// L1220
      int v891 = j10;	// L1221
      int v892 = v890 + v891;	// L1222
      int v893 = v892;	// L1223
      int idx1_10;	// L1224
      idx1_10 = v893;	// L1225
      int v895 = idx1_10;	// L1226
      int v896 = v895;	// L1227
      int v897 = v896 + 512;	// L1231
      int v898 = v897;	// L1232
      int idx2_10;	// L1233
      idx2_10 = v898;	// L1234
      int v900 = j10;	// L1235
      int v901 = v900;	// L1240
      int tw_idx_10;	// L1241
      tw_idx_10 = v901;	// L1242
      int v903 = tw_idx_10;	// L1243
      int v904 = v903;	// L1244
      float v905 = twiddle_real[v904];	// L1245
      float tr_10;	// L1246
      tr_10 = v905;	// L1247
      int v907 = tw_idx_10;	// L1248
      int v908 = v907;	// L1249
      float v909 = twiddle_imag[v908];	// L1250
      float ti_10;	// L1251
      ti_10 = v909;	// L1252
      int v911 = idx1_10;	// L1253
      int v912 = v911;	// L1254
      float v913 = v2[v912];	// L1255
      float ur_10;	// L1256
      ur_10 = v913;	// L1257
      int v915 = idx1_10;	// L1258
      int v916 = v915;	// L1259
      float v917 = v3[v916];	// L1260
      float ui_10;	// L1261
      ui_10 = v917;	// L1262
      int v919 = idx2_10;	// L1263
      int v920 = v919;	// L1264
      float v921 = v2[v920];	// L1265
      float vr_10;	// L1266
      vr_10 = v921;	// L1267
      int v923 = idx2_10;	// L1268
      int v924 = v923;	// L1269
      float v925 = v3[v924];	// L1270
      float vi_10;	// L1271
      vi_10 = v925;	// L1272
      float v927 = tr_10;	// L1273
      float v928 = vr_10;	// L1274
      float v929 = v927 * v928;	// L1275
      float v930 = ti_10;	// L1276
      float v931 = vi_10;	// L1277
      float v932 = v930 * v931;	// L1278
      float v933 = v929 - v932;	// L1279
      float trv_10;	// L1280
      trv_10 = v933;	// L1281
      float v935 = tr_10;	// L1282
      float v936 = vi_10;	// L1283
      float v937 = v935 * v936;	// L1284
      float v938 = ti_10;	// L1285
      float v939 = vr_10;	// L1286
      float v940 = v938 * v939;	// L1287
      float v941 = v937 + v940;	// L1288
      float tiv_10;	// L1289
      tiv_10 = v941;	// L1290
      float v943 = ur_10;	// L1291
      float v944 = trv_10;	// L1292
      float v945 = v943 + v944;	// L1293
      int v946 = idx1_10;	// L1294
      int v947 = v946;	// L1295
      v2[v947] = v945;	// L1296
      float v948 = ui_10;	// L1297
      float v949 = tiv_10;	// L1298
      float v950 = v948 + v949;	// L1299
      int v951 = idx1_10;	// L1300
      int v952 = v951;	// L1301
      v3[v952] = v950;	// L1302
      float v953 = ur_10;	// L1303
      float v954 = trv_10;	// L1304
      float v955 = v953 - v954;	// L1305
      int v956 = idx2_10;	// L1306
      int v957 = v956;	// L1307
      v2[v957] = v955;	// L1308
      float v958 = ui_10;	// L1309
      float v959 = tiv_10;	// L1310
      float v960 = v958 - v959;	// L1311
      int v961 = idx2_10;	// L1312
      int v962 = v961;	// L1313
      v3[v962] = v960;	// L1314
    }
  }
}
#pragma pocc-region-end
}

