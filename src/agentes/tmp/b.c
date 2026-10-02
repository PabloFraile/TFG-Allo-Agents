
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
  float buf_real[1024];	// L7
  float buf_imag[1024];	// L8
  l_S_p_0_p: for (int p = 0; p < 1024; p++) {	// L9
    int v8 = p;	// L10
    int t0;	// L11
    t0 = v8;	// L12
    int v10 = t0;	// L13
    int v11 = v10 / 4;	// L16
    int q0;	// L17
    q0 = v11;	// L18
    int v13 = t0;	// L19
    int v14 = q0;	// L20
    int v15 = v14;	// L21
    int v16 = v15 * 4;	// L25
    int v17 = v13;	// L26
    int v18 = v16;	// L27
    int v19 = v17 - v18;	// L28
    int v20 = v19;	// L29
    int d0;	// L30
    d0 = v20;	// L31
    int v22 = q0;	// L32
    int t1;	// L33
    t1 = v22;	// L34
    int v24 = t1;	// L35
    int v25 = v24 / 4;	// L38
    int q1;	// L39
    q1 = v25;	// L40
    int v27 = t1;	// L41
    int v28 = q1;	// L42
    int v29 = v28;	// L43
    int v30 = v29 * 4;	// L47
    int v31 = v27;	// L48
    int v32 = v30;	// L49
    int v33 = v31 - v32;	// L50
    int v34 = v33;	// L51
    int d1;	// L52
    d1 = v34;	// L53
    int v36 = q1;	// L54
    int t2;	// L55
    t2 = v36;	// L56
    int v38 = t2;	// L57
    int v39 = v38 / 4;	// L60
    int q2;	// L61
    q2 = v39;	// L62
    int v41 = t2;	// L63
    int v42 = q2;	// L64
    int v43 = v42;	// L65
    int v44 = v43 * 4;	// L69
    int v45 = v41;	// L70
    int v46 = v44;	// L71
    int v47 = v45 - v46;	// L72
    int v48 = v47;	// L73
    int d2;	// L74
    d2 = v48;	// L75
    int v50 = q2;	// L76
    int t3;	// L77
    t3 = v50;	// L78
    int v52 = t3;	// L79
    int v53 = v52 / 4;	// L82
    int q3;	// L83
    q3 = v53;	// L84
    int v55 = t3;	// L85
    int v56 = q3;	// L86
    int v57 = v56;	// L87
    int v58 = v57 * 4;	// L91
    int v59 = v55;	// L92
    int v60 = v58;	// L93
    int v61 = v59 - v60;	// L94
    int v62 = v61;	// L95
    int d3;	// L96
    d3 = v62;	// L97
    int v64 = q3;	// L98
    int t4;	// L99
    t4 = v64;	// L100
    int v66 = t4;	// L101
    int v67 = v66 / 4;	// L104
    int q4;	// L105
    q4 = v67;	// L106
    int v69 = t4;	// L107
    int v70 = q4;	// L108
    int v71 = v70;	// L109
    int v72 = v71 * 4;	// L113
    int v73 = v69;	// L114
    int v74 = v72;	// L115
    int v75 = v73 - v74;	// L116
    int v76 = v75;	// L117
    int d4;	// L118
    d4 = v76;	// L119
    int v78 = d0;	// L120
    int v79 = v78;	// L121
    int v80 = v79 * 256;	// L125
    int v81 = d1;	// L126
    int v82 = v81;	// L127
    int v83 = v82 * 64;	// L131
    int v84 = v80;	// L132
    int v85 = v83;	// L133
    int v86 = v84 + v85;	// L134
    int v87 = d2;	// L135
    int v88 = v87;	// L136
    int v89 = v88 * 16;	// L140
    int v90 = v86;	// L141
    int v91 = v89;	// L142
    int v92 = v90 + v91;	// L143
    int v93 = d3;	// L144
    int v94 = v93;	// L145
    int v95 = v94 * 4;	// L149
    int v96 = v92;	// L150
    int v97 = v95;	// L151
    int v98 = v96 + v97;	// L152
    int v99 = d4;	// L153
    int v100 = v98;	// L154
    int v101 = v99;	// L155
    int v102 = v100 + v101;	// L156
    int v103 = v102;	// L157
    int r;	// L158
    r = v103;	// L159
    int v105 = r;	// L160
    int v106 = v105;	// L161
    float v107 = v0[v106];	// L162
    buf_real[p] = v107;	// L163
    int v108 = r;	// L164
    int v109 = v108;	// L165
    float v110 = v1[v109];	// L166
    buf_imag[p] = v110;	// L167
  }
  l_S_g1_1_g1: for (int g1 = 0; g1 < 256; g1++) {	// L169
    l_S_j1_1_j1: for (int j1 = 0; j1 < 1; j1++) {	// L170
      int v113 = j1;	// L171
      float v114 = v113;	// L172
      float j1_f;	// L173
      j1_f = v114;	// L174
      float v116 = PI;	// L178
      float v117 = v116 * -2.000000;	// L179
      float v118 = j1_f;	// L180
      float v119 = v117 * v118;	// L181
      float v120 = v119 / 4.000000;	// L184
      float theta1;	// L185
      theta1 = v120;	// L186
      float v122 = theta1;	// L187
      float v123 = v122 * v122;	// L189
      float th1_2;	// L190
      th1_2 = v123;	// L191
      float v125 = th1_2;	// L192
      float v126 = theta1;	// L193
      float v127 = v125 * v126;	// L194
      float th1_3;	// L195
      th1_3 = v127;	// L196
      float v129 = th1_2;	// L197
      float v130 = v129 * v129;	// L199
      float th1_4;	// L200
      th1_4 = v130;	// L201
      float v132 = th1_4;	// L202
      float v133 = theta1;	// L203
      float v134 = v132 * v133;	// L204
      float th1_5;	// L205
      th1_5 = v134;	// L206
      float v136 = th1_4;	// L207
      float v137 = th1_2;	// L208
      float v138 = v136 * v137;	// L209
      float th1_6;	// L210
      th1_6 = v138;	// L211
      float v140 = th1_6;	// L212
      float v141 = theta1;	// L213
      float v142 = v140 * v141;	// L214
      float th1_7;	// L215
      th1_7 = v142;	// L216
      float v144 = th1_4;	// L217
      float v145 = v144 * v144;	// L219
      float th1_8;	// L220
      th1_8 = v145;	// L221
      float v147 = th1_8;	// L222
      float v148 = theta1;	// L223
      float v149 = v147 * v148;	// L224
      float th1_9;	// L225
      th1_9 = v149;	// L226
      float v151 = th1_8;	// L227
      float v152 = th1_2;	// L228
      float v153 = v151 * v152;	// L229
      float th1_10;	// L230
      th1_10 = v153;	// L231
      float v155 = th1_10;	// L232
      float v156 = theta1;	// L233
      float v157 = v155 * v156;	// L234
      float th1_11;	// L235
      th1_11 = v157;	// L236
      float v159 = th1_2;	// L237
      float v160 = v159 / 2.000000;	// L240
      float v161 = 1.000000 - v160;	// L243
      float v162 = th1_4;	// L244
      float v163 = v162 / 24.000000;	// L247
      float v164 = v161 + v163;	// L248
      float v165 = th1_6;	// L249
      float v166 = v165 / 720.000000;	// L252
      float v167 = v164 - v166;	// L253
      float v168 = th1_8;	// L254
      float v169 = v168 / 40320.000000;	// L257
      float v170 = v167 + v169;	// L258
      float v171 = th1_10;	// L259
      float v172 = v171 / 3628800.000000;	// L262
      float v173 = v170 - v172;	// L263
      float cos1;	// L264
      cos1 = v173;	// L265
      float v175 = theta1;	// L266
      float v176 = th1_3;	// L267
      float v177 = v176 / 6.000000;	// L270
      float v178 = v175 - v177;	// L271
      float v179 = th1_5;	// L272
      float v180 = v179 / 120.000000;	// L275
      float v181 = v178 + v180;	// L276
      float v182 = th1_7;	// L277
      float v183 = v182 / 5040.000000;	// L280
      float v184 = v181 - v183;	// L281
      float v185 = th1_9;	// L282
      float v186 = v185 / 362880.000000;	// L285
      float v187 = v184 + v186;	// L286
      float v188 = th1_11;	// L287
      float v189 = v188 / 39916800.000000;	// L290
      float v190 = v187 - v189;	// L291
      float sin1;	// L292
      sin1 = v190;	// L293
      float v192 = cos1;	// L294
      float Wr1;	// L295
      Wr1 = v192;	// L296
      float v194 = sin1;	// L297
      float Wi1;	// L298
      Wi1 = v194;	// L299
      float v196 = Wr1;	// L300
      float v197 = v196 * v196;	// L302
      float v198 = Wi1;	// L303
      float v199 = v198 * v198;	// L305
      float v200 = v197 - v199;	// L306
      float W2r1;	// L307
      W2r1 = v200;	// L308
      float v202 = Wr1;	// L309
      float v203 = v202  << 1.000000;	// L312
      float v204 = Wi1;	// L313
      float v205 = v203 * v204;	// L314
      float W2i1;	// L315
      W2i1 = v205;	// L316
      float v207 = W2r1;	// L317
      float v208 = Wr1;	// L318
      float v209 = v207 * v208;	// L319
      float v210 = W2i1;	// L320
      float v211 = Wi1;	// L321
      float v212 = v210 * v211;	// L322
      float v213 = v209 - v212;	// L323
      float W3r1;	// L324
      W3r1 = v213;	// L325
      float v215 = W2r1;	// L326
      float v216 = Wi1;	// L327
      float v217 = v215 * v216;	// L328
      float v218 = W2i1;	// L329
      float v219 = Wr1;	// L330
      float v220 = v218 * v219;	// L331
      float v221 = v217 + v220;	// L332
      float W3i1;	// L333
      W3i1 = v221;	// L334
      int v223 = g1;	// L335
      int v224 = v223 * 4;	// L339
      int v225 = v224;	// L340
      int v226 = j1;	// L341
      int v227 = v225 + v226;	// L342
      int v228 = v227;	// L343
      int base1;	// L344
      base1 = v228;	// L345
      int v230 = base1;	// L346
      int idx1_1;	// L347
      idx1_1 = v230;	// L348
      int v232 = base1;	// L349
      int v233 = v232;	// L350
      int v234 = v233 + 1;	// L354
      int v235 = v234;	// L355
      int idx2_1;	// L356
      idx2_1 = v235;	// L357
      int v237 = base1;	// L358
      int v238 = v237;	// L359
      int v239 = v238 + 2;	// L363
      int v240 = v239;	// L364
      int idx3_1;	// L365
      idx3_1 = v240;	// L366
      int v242 = base1;	// L367
      int v243 = v242;	// L368
      int v244 = v243 + 3;	// L372
      int v245 = v244;	// L373
      int idx4_1;	// L374
      idx4_1 = v245;	// L375
      int v247 = idx1_1;	// L376
      int v248 = v247;	// L377
      float v249 = buf_real[v248];	// L378
      float a0r1;	// L379
      a0r1 = v249;	// L380
      int v251 = idx1_1;	// L381
      int v252 = v251;	// L382
      float v253 = buf_imag[v252];	// L383
      float a0i1;	// L384
      a0i1 = v253;	// L385
      int v255 = idx2_1;	// L386
      int v256 = v255;	// L387
      float v257 = buf_real[v256];	// L388
      float a1r01;	// L389
      a1r01 = v257;	// L390
      int v259 = idx2_1;	// L391
      int v260 = v259;	// L392
      float v261 = buf_imag[v260];	// L393
      float a1i01;	// L394
      a1i01 = v261;	// L395
      int v263 = idx3_1;	// L396
      int v264 = v263;	// L397
      float v265 = buf_real[v264];	// L398
      float a2r01;	// L399
      a2r01 = v265;	// L400
      int v267 = idx3_1;	// L401
      int v268 = v267;	// L402
      float v269 = buf_imag[v268];	// L403
      float a2i01;	// L404
      a2i01 = v269;	// L405
      int v271 = idx4_1;	// L406
      int v272 = v271;	// L407
      float v273 = buf_real[v272];	// L408
      float a3r01;	// L409
      a3r01 = v273;	// L410
      int v275 = idx4_1;	// L411
      int v276 = v275;	// L412
      float v277 = buf_imag[v276];	// L413
      float a3i01;	// L414
      a3i01 = v277;	// L415
      float v279 = a1r01;	// L416
      float v280 = Wr1;	// L417
      float v281 = v279 * v280;	// L418
      float v282 = a1i01;	// L419
      float v283 = Wi1;	// L420
      float v284 = v282 * v283;	// L421
      float v285 = v281 - v284;	// L422
      float a1r1;	// L423
      a1r1 = v285;	// L424
      float v287 = a1r01;	// L425
      float v288 = Wi1;	// L426
      float v289 = v287 * v288;	// L427
      float v290 = a1i01;	// L428
      float v291 = Wr1;	// L429
      float v292 = v290 * v291;	// L430
      float v293 = v289 + v292;	// L431
      float a1i1;	// L432
      a1i1 = v293;	// L433
      float v295 = a2r01;	// L434
      float v296 = W2r1;	// L435
      float v297 = v295 * v296;	// L436
      float v298 = a2i01;	// L437
      float v299 = W2i1;	// L438
      float v300 = v298 * v299;	// L439
      float v301 = v297 - v300;	// L440
      float a2r1;	// L441
      a2r1 = v301;	// L442
      float v303 = a2r01;	// L443
      float v304 = W2i1;	// L444
      float v305 = v303 * v304;	// L445
      float v306 = a2i01;	// L446
      float v307 = W2r1;	// L447
      float v308 = v306 * v307;	// L448
      float v309 = v305 + v308;	// L449
      float a2i1;	// L450
      a2i1 = v309;	// L451
      float v311 = a3r01;	// L452
      float v312 = W3r1;	// L453
      float v313 = v311 * v312;	// L454
      float v314 = a3i01;	// L455
      float v315 = W3i1;	// L456
      float v316 = v314 * v315;	// L457
      float v317 = v313 - v316;	// L458
      float a3r1;	// L459
      a3r1 = v317;	// L460
      float v319 = a3r01;	// L461
      float v320 = W3i1;	// L462
      float v321 = v319 * v320;	// L463
      float v322 = a3i01;	// L464
      float v323 = W3r1;	// L465
      float v324 = v322 * v323;	// L466
      float v325 = v321 + v324;	// L467
      float a3i1;	// L468
      a3i1 = v325;	// L469
      float v327 = a0r1;	// L470
      float v328 = a1r1;	// L471
      float v329 = v327 + v328;	// L472
      float v330 = a2r1;	// L473
      float v331 = v329 + v330;	// L474
      float v332 = a3r1;	// L475
      float v333 = v331 + v332;	// L476
      float b0r1;	// L477
      b0r1 = v333;	// L478
      float v335 = a0i1;	// L479
      float v336 = a1i1;	// L480
      float v337 = v335 + v336;	// L481
      float v338 = a2i1;	// L482
      float v339 = v337 + v338;	// L483
      float v340 = a3i1;	// L484
      float v341 = v339 + v340;	// L485
      float b0i1;	// L486
      b0i1 = v341;	// L487
      float v343 = a0r1;	// L488
      float v344 = a1i1;	// L489
      float v345 = v343 + v344;	// L490
      float v346 = a2r1;	// L491
      float v347 = v345 - v346;	// L492
      float v348 = a3i1;	// L493
      float v349 = v347 - v348;	// L494
      float b1r1;	// L495
      b1r1 = v349;	// L496
      float v351 = a0i1;	// L497
      float v352 = a1r1;	// L498
      float v353 = v351 - v352;	// L499
      float v354 = a2i1;	// L500
      float v355 = v353 - v354;	// L501
      float v356 = a3r1;	// L502
      float v357 = v355 + v356;	// L503
      float b1i1;	// L504
      b1i1 = v357;	// L505
      float v359 = a0r1;	// L506
      float v360 = a1r1;	// L507
      float v361 = v359 - v360;	// L508
      float v362 = a2r1;	// L509
      float v363 = v361 + v362;	// L510
      float v364 = a3r1;	// L511
      float v365 = v363 - v364;	// L512
      float b2r1;	// L513
      b2r1 = v365;	// L514
      float v367 = a0i1;	// L515
      float v368 = a1i1;	// L516
      float v369 = v367 - v368;	// L517
      float v370 = a2i1;	// L518
      float v371 = v369 + v370;	// L519
      float v372 = a3i1;	// L520
      float v373 = v371 - v372;	// L521
      float b2i1;	// L522
      b2i1 = v373;	// L523
      float v375 = a0r1;	// L524
      float v376 = a1i1;	// L525
      float v377 = v375 - v376;	// L526
      float v378 = a2r1;	// L527
      float v379 = v377 - v378;	// L528
      float v380 = a3i1;	// L529
      float v381 = v379 + v380;	// L530
      float b3r1;	// L531
      b3r1 = v381;	// L532
      float v383 = a0i1;	// L533
      float v384 = a1r1;	// L534
      float v385 = v383 + v384;	// L535
      float v386 = a2i1;	// L536
      float v387 = v385 - v386;	// L537
      float v388 = a3r1;	// L538
      float v389 = v387 - v388;	// L539
      float b3i1;	// L540
      b3i1 = v389;	// L541
      float v391 = b0r1;	// L542
      int v392 = idx1_1;	// L543
      int v393 = v392;	// L544
      buf_real[v393] = v391;	// L545
      float v394 = b0i1;	// L546
      int v395 = idx1_1;	// L547
      int v396 = v395;	// L548
      buf_imag[v396] = v394;	// L549
      float v397 = b1r1;	// L550
      int v398 = idx2_1;	// L551
      int v399 = v398;	// L552
      buf_real[v399] = v397;	// L553
      float v400 = b1i1;	// L554
      int v401 = idx2_1;	// L555
      int v402 = v401;	// L556
      buf_imag[v402] = v400;	// L557
      float v403 = b2r1;	// L558
      int v404 = idx3_1;	// L559
      int v405 = v404;	// L560
      buf_real[v405] = v403;	// L561
      float v406 = b2i1;	// L562
      int v407 = idx3_1;	// L563
      int v408 = v407;	// L564
      buf_imag[v408] = v406;	// L565
      float v409 = b3r1;	// L566
      int v410 = idx4_1;	// L567
      int v411 = v410;	// L568
      buf_real[v411] = v409;	// L569
      float v412 = b3i1;	// L570
      int v413 = idx4_1;	// L571
      int v414 = v413;	// L572
      buf_imag[v414] = v412;	// L573
    }
  }
  l_S_g2_3_g2: for (int g2 = 0; g2 < 64; g2++) {	// L576
    l_S_j2_3_j2: for (int j2 = 0; j2 < 4; j2++) {	// L577
      int v417 = j2;	// L578
      float v418 = v417;	// L579
      float j2_f;	// L580
      j2_f = v418;	// L581
      float v420 = PI;	// L585
      float v421 = v420 * -2.000000;	// L586
      float v422 = j2_f;	// L587
      float v423 = v421 * v422;	// L588
      float v424 = v423 / 16.000000;	// L591
      float theta2;	// L592
      theta2 = v424;	// L593
      float v426 = theta2;	// L594
      float v427 = v426 * v426;	// L596
      float th2_2;	// L597
      th2_2 = v427;	// L598
      float v429 = th2_2;	// L599
      float v430 = theta2;	// L600
      float v431 = v429 * v430;	// L601
      float th2_3;	// L602
      th2_3 = v431;	// L603
      float v433 = th2_2;	// L604
      float v434 = v433 * v433;	// L606
      float th2_4;	// L607
      th2_4 = v434;	// L608
      float v436 = th2_4;	// L609
      float v437 = theta2;	// L610
      float v438 = v436 * v437;	// L611
      float th2_5;	// L612
      th2_5 = v438;	// L613
      float v440 = th2_4;	// L614
      float v441 = th2_2;	// L615
      float v442 = v440 * v441;	// L616
      float th2_6;	// L617
      th2_6 = v442;	// L618
      float v444 = th2_6;	// L619
      float v445 = theta2;	// L620
      float v446 = v444 * v445;	// L621
      float th2_7;	// L622
      th2_7 = v446;	// L623
      float v448 = th2_4;	// L624
      float v449 = v448 * v448;	// L626
      float th2_8;	// L627
      th2_8 = v449;	// L628
      float v451 = th2_8;	// L629
      float v452 = theta2;	// L630
      float v453 = v451 * v452;	// L631
      float th2_9;	// L632
      th2_9 = v453;	// L633
      float v455 = th2_8;	// L634
      float v456 = th2_2;	// L635
      float v457 = v455 * v456;	// L636
      float th2_10;	// L637
      th2_10 = v457;	// L638
      float v459 = th2_10;	// L639
      float v460 = theta2;	// L640
      float v461 = v459 * v460;	// L641
      float th2_11;	// L642
      th2_11 = v461;	// L643
      float v463 = th2_2;	// L644
      float v464 = v463 / 2.000000;	// L647
      float v465 = 1.000000 - v464;	// L650
      float v466 = th2_4;	// L651
      float v467 = v466 / 24.000000;	// L654
      float v468 = v465 + v467;	// L655
      float v469 = th2_6;	// L656
      float v470 = v469 / 720.000000;	// L659
      float v471 = v468 - v470;	// L660
      float v472 = th2_8;	// L661
      float v473 = v472 / 40320.000000;	// L664
      float v474 = v471 + v473;	// L665
      float v475 = th2_10;	// L666
      float v476 = v475 / 3628800.000000;	// L669
      float v477 = v474 - v476;	// L670
      float cos2;	// L671
      cos2 = v477;	// L672
      float v479 = theta2;	// L673
      float v480 = th2_3;	// L674
      float v481 = v480 / 6.000000;	// L677
      float v482 = v479 - v481;	// L678
      float v483 = th2_5;	// L679
      float v484 = v483 / 120.000000;	// L682
      float v485 = v482 + v484;	// L683
      float v486 = th2_7;	// L684
      float v487 = v486 / 5040.000000;	// L687
      float v488 = v485 - v487;	// L688
      float v489 = th2_9;	// L689
      float v490 = v489 / 362880.000000;	// L692
      float v491 = v488 + v490;	// L693
      float v492 = th2_11;	// L694
      float v493 = v492 / 39916800.000000;	// L697
      float v494 = v491 - v493;	// L698
      float sin2;	// L699
      sin2 = v494;	// L700
      float v496 = cos2;	// L701
      float Wr2;	// L702
      Wr2 = v496;	// L703
      float v498 = sin2;	// L704
      float Wi2;	// L705
      Wi2 = v498;	// L706
      float v500 = Wr2;	// L707
      float v501 = v500 * v500;	// L709
      float v502 = Wi2;	// L710
      float v503 = v502 * v502;	// L712
      float v504 = v501 - v503;	// L713
      float W2r2;	// L714
      W2r2 = v504;	// L715
      float v506 = Wr2;	// L716
      float v507 = v506  << 1.000000;	// L719
      float v508 = Wi2;	// L720
      float v509 = v507 * v508;	// L721
      float W2i2;	// L722
      W2i2 = v509;	// L723
      float v511 = W2r2;	// L724
      float v512 = Wr2;	// L725
      float v513 = v511 * v512;	// L726
      float v514 = W2i2;	// L727
      float v515 = Wi2;	// L728
      float v516 = v514 * v515;	// L729
      float v517 = v513 - v516;	// L730
      float W3r2;	// L731
      W3r2 = v517;	// L732
      float v519 = W2r2;	// L733
      float v520 = Wi2;	// L734
      float v521 = v519 * v520;	// L735
      float v522 = W2i2;	// L736
      float v523 = Wr2;	// L737
      float v524 = v522 * v523;	// L738
      float v525 = v521 + v524;	// L739
      float W3i2;	// L740
      W3i2 = v525;	// L741
      int v527 = g2;	// L742
      int v528 = v527 * 16;	// L746
      int v529 = v528;	// L747
      int v530 = j2;	// L748
      int v531 = v529 + v530;	// L749
      int v532 = v531;	// L750
      int base2;	// L751
      base2 = v532;	// L752
      int v534 = base2;	// L753
      int idx1_2;	// L754
      idx1_2 = v534;	// L755
      int v536 = base2;	// L756
      int v537 = v536;	// L757
      int v538 = v537 + 4;	// L761
      int v539 = v538;	// L762
      int idx2_2;	// L763
      idx2_2 = v539;	// L764
      int v541 = base2;	// L765
      int v542 = v541;	// L766
      int v543 = v542 + 8;	// L770
      int v544 = v543;	// L771
      int idx3_2;	// L772
      idx3_2 = v544;	// L773
      int v546 = base2;	// L774
      int v547 = v546;	// L775
      int v548 = v547 + 12;	// L779
      int v549 = v548;	// L780
      int idx4_2;	// L781
      idx4_2 = v549;	// L782
      int v551 = idx1_2;	// L783
      int v552 = v551;	// L784
      float v553 = buf_real[v552];	// L785
      float a0r2;	// L786
      a0r2 = v553;	// L787
      int v555 = idx1_2;	// L788
      int v556 = v555;	// L789
      float v557 = buf_imag[v556];	// L790
      float a0i2;	// L791
      a0i2 = v557;	// L792
      int v559 = idx2_2;	// L793
      int v560 = v559;	// L794
      float v561 = buf_real[v560];	// L795
      float a1r02;	// L796
      a1r02 = v561;	// L797
      int v563 = idx2_2;	// L798
      int v564 = v563;	// L799
      float v565 = buf_imag[v564];	// L800
      float a1i02;	// L801
      a1i02 = v565;	// L802
      int v567 = idx3_2;	// L803
      int v568 = v567;	// L804
      float v569 = buf_real[v568];	// L805
      float a2r02;	// L806
      a2r02 = v569;	// L807
      int v571 = idx3_2;	// L808
      int v572 = v571;	// L809
      float v573 = buf_imag[v572];	// L810
      float a2i02;	// L811
      a2i02 = v573;	// L812
      int v575 = idx4_2;	// L813
      int v576 = v575;	// L814
      float v577 = buf_real[v576];	// L815
      float a3r02;	// L816
      a3r02 = v577;	// L817
      int v579 = idx4_2;	// L818
      int v580 = v579;	// L819
      float v581 = buf_imag[v580];	// L820
      float a3i02;	// L821
      a3i02 = v581;	// L822
      float v583 = a1r02;	// L823
      float v584 = Wr2;	// L824
      float v585 = v583 * v584;	// L825
      float v586 = a1i02;	// L826
      float v587 = Wi2;	// L827
      float v588 = v586 * v587;	// L828
      float v589 = v585 - v588;	// L829
      float a1r2;	// L830
      a1r2 = v589;	// L831
      float v591 = a1r02;	// L832
      float v592 = Wi2;	// L833
      float v593 = v591 * v592;	// L834
      float v594 = a1i02;	// L835
      float v595 = Wr2;	// L836
      float v596 = v594 * v595;	// L837
      float v597 = v593 + v596;	// L838
      float a1i2;	// L839
      a1i2 = v597;	// L840
      float v599 = a2r02;	// L841
      float v600 = W2r2;	// L842
      float v601 = v599 * v600;	// L843
      float v602 = a2i02;	// L844
      float v603 = W2i2;	// L845
      float v604 = v602 * v603;	// L846
      float v605 = v601 - v604;	// L847
      float a2r2;	// L848
      a2r2 = v605;	// L849
      float v607 = a2r02;	// L850
      float v608 = W2i2;	// L851
      float v609 = v607 * v608;	// L852
      float v610 = a2i02;	// L853
      float v611 = W2r2;	// L854
      float v612 = v610 * v611;	// L855
      float v613 = v609 + v612;	// L856
      float a2i2;	// L857
      a2i2 = v613;	// L858
      float v615 = a3r02;	// L859
      float v616 = W3r2;	// L860
      float v617 = v615 * v616;	// L861
      float v618 = a3i02;	// L862
      float v619 = W3i2;	// L863
      float v620 = v618 * v619;	// L864
      float v621 = v617 - v620;	// L865
      float a3r2;	// L866
      a3r2 = v621;	// L867
      float v623 = a3r02;	// L868
      float v624 = W3i2;	// L869
      float v625 = v623 * v624;	// L870
      float v626 = a3i02;	// L871
      float v627 = W3r2;	// L872
      float v628 = v626 * v627;	// L873
      float v629 = v625 + v628;	// L874
      float a3i2;	// L875
      a3i2 = v629;	// L876
      float v631 = a0r2;	// L877
      float v632 = a1r2;	// L878
      float v633 = v631 + v632;	// L879
      float v634 = a2r2;	// L880
      float v635 = v633 + v634;	// L881
      float v636 = a3r2;	// L882
      float v637 = v635 + v636;	// L883
      float b0r2;	// L884
      b0r2 = v637;	// L885
      float v639 = a0i2;	// L886
      float v640 = a1i2;	// L887
      float v641 = v639 + v640;	// L888
      float v642 = a2i2;	// L889
      float v643 = v641 + v642;	// L890
      float v644 = a3i2;	// L891
      float v645 = v643 + v644;	// L892
      float b0i2;	// L893
      b0i2 = v645;	// L894
      float v647 = a0r2;	// L895
      float v648 = a1i2;	// L896
      float v649 = v647 + v648;	// L897
      float v650 = a2r2;	// L898
      float v651 = v649 - v650;	// L899
      float v652 = a3i2;	// L900
      float v653 = v651 - v652;	// L901
      float b1r2;	// L902
      b1r2 = v653;	// L903
      float v655 = a0i2;	// L904
      float v656 = a1r2;	// L905
      float v657 = v655 - v656;	// L906
      float v658 = a2i2;	// L907
      float v659 = v657 - v658;	// L908
      float v660 = a3r2;	// L909
      float v661 = v659 + v660;	// L910
      float b1i2;	// L911
      b1i2 = v661;	// L912
      float v663 = a0r2;	// L913
      float v664 = a1r2;	// L914
      float v665 = v663 - v664;	// L915
      float v666 = a2r2;	// L916
      float v667 = v665 + v666;	// L917
      float v668 = a3r2;	// L918
      float v669 = v667 - v668;	// L919
      float b2r2;	// L920
      b2r2 = v669;	// L921
      float v671 = a0i2;	// L922
      float v672 = a1i2;	// L923
      float v673 = v671 - v672;	// L924
      float v674 = a2i2;	// L925
      float v675 = v673 + v674;	// L926
      float v676 = a3i2;	// L927
      float v677 = v675 - v676;	// L928
      float b2i2;	// L929
      b2i2 = v677;	// L930
      float v679 = a0r2;	// L931
      float v680 = a1i2;	// L932
      float v681 = v679 - v680;	// L933
      float v682 = a2r2;	// L934
      float v683 = v681 - v682;	// L935
      float v684 = a3i2;	// L936
      float v685 = v683 + v684;	// L937
      float b3r2;	// L938
      b3r2 = v685;	// L939
      float v687 = a0i2;	// L940
      float v688 = a1r2;	// L941
      float v689 = v687 + v688;	// L942
      float v690 = a2i2;	// L943
      float v691 = v689 - v690;	// L944
      float v692 = a3r2;	// L945
      float v693 = v691 - v692;	// L946
      float b3i2;	// L947
      b3i2 = v693;	// L948
      float v695 = b0r2;	// L949
      int v696 = idx1_2;	// L950
      int v697 = v696;	// L951
      buf_real[v697] = v695;	// L952
      float v698 = b0i2;	// L953
      int v699 = idx1_2;	// L954
      int v700 = v699;	// L955
      buf_imag[v700] = v698;	// L956
      float v701 = b1r2;	// L957
      int v702 = idx2_2;	// L958
      int v703 = v702;	// L959
      buf_real[v703] = v701;	// L960
      float v704 = b1i2;	// L961
      int v705 = idx2_2;	// L962
      int v706 = v705;	// L963
      buf_imag[v706] = v704;	// L964
      float v707 = b2r2;	// L965
      int v708 = idx3_2;	// L966
      int v709 = v708;	// L967
      buf_real[v709] = v707;	// L968
      float v710 = b2i2;	// L969
      int v711 = idx3_2;	// L970
      int v712 = v711;	// L971
      buf_imag[v712] = v710;	// L972
      float v713 = b3r2;	// L973
      int v714 = idx4_2;	// L974
      int v715 = v714;	// L975
      buf_real[v715] = v713;	// L976
      float v716 = b3i2;	// L977
      int v717 = idx4_2;	// L978
      int v718 = v717;	// L979
      buf_imag[v718] = v716;	// L980
    }
  }
  l_S_g3_5_g3: for (int g3 = 0; g3 < 16; g3++) {	// L983
    l_S_j3_5_j3: for (int j3 = 0; j3 < 16; j3++) {	// L984
      int v721 = j3;	// L985
      float v722 = v721;	// L986
      float j3_f;	// L987
      j3_f = v722;	// L988
      float v724 = PI;	// L992
      float v725 = v724 * -2.000000;	// L993
      float v726 = j3_f;	// L994
      float v727 = v725 * v726;	// L995
      float v728 = v727 / 64.000000;	// L998
      float theta3;	// L999
      theta3 = v728;	// L1000
      float v730 = theta3;	// L1001
      float v731 = v730 * v730;	// L1003
      float th3_2;	// L1004
      th3_2 = v731;	// L1005
      float v733 = th3_2;	// L1006
      float v734 = theta3;	// L1007
      float v735 = v733 * v734;	// L1008
      float th3_3;	// L1009
      th3_3 = v735;	// L1010
      float v737 = th3_2;	// L1011
      float v738 = v737 * v737;	// L1013
      float th3_4;	// L1014
      th3_4 = v738;	// L1015
      float v740 = th3_4;	// L1016
      float v741 = theta3;	// L1017
      float v742 = v740 * v741;	// L1018
      float th3_5;	// L1019
      th3_5 = v742;	// L1020
      float v744 = th3_4;	// L1021
      float v745 = th3_2;	// L1022
      float v746 = v744 * v745;	// L1023
      float th3_6;	// L1024
      th3_6 = v746;	// L1025
      float v748 = th3_6;	// L1026
      float v749 = theta3;	// L1027
      float v750 = v748 * v749;	// L1028
      float th3_7;	// L1029
      th3_7 = v750;	// L1030
      float v752 = th3_4;	// L1031
      float v753 = v752 * v752;	// L1033
      float th3_8;	// L1034
      th3_8 = v753;	// L1035
      float v755 = th3_8;	// L1036
      float v756 = theta3;	// L1037
      float v757 = v755 * v756;	// L1038
      float th3_9;	// L1039
      th3_9 = v757;	// L1040
      float v759 = th3_8;	// L1041
      float v760 = th3_2;	// L1042
      float v761 = v759 * v760;	// L1043
      float th3_10;	// L1044
      th3_10 = v761;	// L1045
      float v763 = th3_10;	// L1046
      float v764 = theta3;	// L1047
      float v765 = v763 * v764;	// L1048
      float th3_11;	// L1049
      th3_11 = v765;	// L1050
      float v767 = th3_2;	// L1051
      float v768 = v767 / 2.000000;	// L1054
      float v769 = 1.000000 - v768;	// L1057
      float v770 = th3_4;	// L1058
      float v771 = v770 / 24.000000;	// L1061
      float v772 = v769 + v771;	// L1062
      float v773 = th3_6;	// L1063
      float v774 = v773 / 720.000000;	// L1066
      float v775 = v772 - v774;	// L1067
      float v776 = th3_8;	// L1068
      float v777 = v776 / 40320.000000;	// L1071
      float v778 = v775 + v777;	// L1072
      float v779 = th3_10;	// L1073
      float v780 = v779 / 3628800.000000;	// L1076
      float v781 = v778 - v780;	// L1077
      float cos3;	// L1078
      cos3 = v781;	// L1079
      float v783 = theta3;	// L1080
      float v784 = th3_3;	// L1081
      float v785 = v784 / 6.000000;	// L1084
      float v786 = v783 - v785;	// L1085
      float v787 = th3_5;	// L1086
      float v788 = v787 / 120.000000;	// L1089
      float v789 = v786 + v788;	// L1090
      float v790 = th3_7;	// L1091
      float v791 = v790 / 5040.000000;	// L1094
      float v792 = v789 - v791;	// L1095
      float v793 = th3_9;	// L1096
      float v794 = v793 / 362880.000000;	// L1099
      float v795 = v792 + v794;	// L1100
      float v796 = th3_11;	// L1101
      float v797 = v796 / 39916800.000000;	// L1104
      float v798 = v795 - v797;	// L1105
      float sin3;	// L1106
      sin3 = v798;	// L1107
      float v800 = cos3;	// L1108
      float Wr3;	// L1109
      Wr3 = v800;	// L1110
      float v802 = sin3;	// L1111
      float Wi3;	// L1112
      Wi3 = v802;	// L1113
      float v804 = Wr3;	// L1114
      float v805 = v804 * v804;	// L1116
      float v806 = Wi3;	// L1117
      float v807 = v806 * v806;	// L1119
      float v808 = v805 - v807;	// L1120
      float W2r3;	// L1121
      W2r3 = v808;	// L1122
      float v810 = Wr3;	// L1123
      float v811 = v810  << 1.000000;	// L1126
      float v812 = Wi3;	// L1127
      float v813 = v811 * v812;	// L1128
      float W2i3;	// L1129
      W2i3 = v813;	// L1130
      float v815 = W2r3;	// L1131
      float v816 = Wr3;	// L1132
      float v817 = v815 * v816;	// L1133
      float v818 = W2i3;	// L1134
      float v819 = Wi3;	// L1135
      float v820 = v818 * v819;	// L1136
      float v821 = v817 - v820;	// L1137
      float W3r3;	// L1138
      W3r3 = v821;	// L1139
      float v823 = W2r3;	// L1140
      float v824 = Wi3;	// L1141
      float v825 = v823 * v824;	// L1142
      float v826 = W2i3;	// L1143
      float v827 = Wr3;	// L1144
      float v828 = v826 * v827;	// L1145
      float v829 = v825 + v828;	// L1146
      float W3i3;	// L1147
      W3i3 = v829;	// L1148
      int v831 = g3;	// L1149
      int v832 = v831 * 64;	// L1153
      int v833 = v832;	// L1154
      int v834 = j3;	// L1155
      int v835 = v833 + v834;	// L1156
      int v836 = v835;	// L1157
      int base3;	// L1158
      base3 = v836;	// L1159
      int v838 = base3;	// L1160
      int idx1_3;	// L1161
      idx1_3 = v838;	// L1162
      int v840 = base3;	// L1163
      int v841 = v840;	// L1164
      int v842 = v841 + 16;	// L1168
      int v843 = v842;	// L1169
      int idx2_3;	// L1170
      idx2_3 = v843;	// L1171
      int v845 = base3;	// L1172
      int v846 = v845;	// L1173
      int v847 = v846 + 32;	// L1177
      int v848 = v847;	// L1178
      int idx3_3;	// L1179
      idx3_3 = v848;	// L1180
      int v850 = base3;	// L1181
      int v851 = v850;	// L1182
      int v852 = v851 + 48;	// L1186
      int v853 = v852;	// L1187
      int idx4_3;	// L1188
      idx4_3 = v853;	// L1189
      int v855 = idx1_3;	// L1190
      int v856 = v855;	// L1191
      float v857 = buf_real[v856];	// L1192
      float a0r3;	// L1193
      a0r3 = v857;	// L1194
      int v859 = idx1_3;	// L1195
      int v860 = v859;	// L1196
      float v861 = buf_imag[v860];	// L1197
      float a0i3;	// L1198
      a0i3 = v861;	// L1199
      int v863 = idx2_3;	// L1200
      int v864 = v863;	// L1201
      float v865 = buf_real[v864];	// L1202
      float a1r03;	// L1203
      a1r03 = v865;	// L1204
      int v867 = idx2_3;	// L1205
      int v868 = v867;	// L1206
      float v869 = buf_imag[v868];	// L1207
      float a1i03;	// L1208
      a1i03 = v869;	// L1209
      int v871 = idx3_3;	// L1210
      int v872 = v871;	// L1211
      float v873 = buf_real[v872];	// L1212
      float a2r03;	// L1213
      a2r03 = v873;	// L1214
      int v875 = idx3_3;	// L1215
      int v876 = v875;	// L1216
      float v877 = buf_imag[v876];	// L1217
      float a2i03;	// L1218
      a2i03 = v877;	// L1219
      int v879 = idx4_3;	// L1220
      int v880 = v879;	// L1221
      float v881 = buf_real[v880];	// L1222
      float a3r03;	// L1223
      a3r03 = v881;	// L1224
      int v883 = idx4_3;	// L1225
      int v884 = v883;	// L1226
      float v885 = buf_imag[v884];	// L1227
      float a3i03;	// L1228
      a3i03 = v885;	// L1229
      float v887 = a1r03;	// L1230
      float v888 = Wr3;	// L1231
      float v889 = v887 * v888;	// L1232
      float v890 = a1i03;	// L1233
      float v891 = Wi3;	// L1234
      float v892 = v890 * v891;	// L1235
      float v893 = v889 - v892;	// L1236
      float a1r3;	// L1237
      a1r3 = v893;	// L1238
      float v895 = a1r03;	// L1239
      float v896 = Wi3;	// L1240
      float v897 = v895 * v896;	// L1241
      float v898 = a1i03;	// L1242
      float v899 = Wr3;	// L1243
      float v900 = v898 * v899;	// L1244
      float v901 = v897 + v900;	// L1245
      float a1i3;	// L1246
      a1i3 = v901;	// L1247
      float v903 = a2r03;	// L1248
      float v904 = W2r3;	// L1249
      float v905 = v903 * v904;	// L1250
      float v906 = a2i03;	// L1251
      float v907 = W2i3;	// L1252
      float v908 = v906 * v907;	// L1253
      float v909 = v905 - v908;	// L1254
      float a2r3;	// L1255
      a2r3 = v909;	// L1256
      float v911 = a2r03;	// L1257
      float v912 = W2i3;	// L1258
      float v913 = v911 * v912;	// L1259
      float v914 = a2i03;	// L1260
      float v915 = W2r3;	// L1261
      float v916 = v914 * v915;	// L1262
      float v917 = v913 + v916;	// L1263
      float a2i3;	// L1264
      a2i3 = v917;	// L1265
      float v919 = a3r03;	// L1266
      float v920 = W3r3;	// L1267
      float v921 = v919 * v920;	// L1268
      float v922 = a3i03;	// L1269
      float v923 = W3i3;	// L1270
      float v924 = v922 * v923;	// L1271
      float v925 = v921 - v924;	// L1272
      float a3r3;	// L1273
      a3r3 = v925;	// L1274
      float v927 = a3r03;	// L1275
      float v928 = W3i3;	// L1276
      float v929 = v927 * v928;	// L1277
      float v930 = a3i03;	// L1278
      float v931 = W3r3;	// L1279
      float v932 = v930 * v931;	// L1280
      float v933 = v929 + v932;	// L1281
      float a3i3;	// L1282
      a3i3 = v933;	// L1283
      float v935 = a0r3;	// L1284
      float v936 = a1r3;	// L1285
      float v937 = v935 + v936;	// L1286
      float v938 = a2r3;	// L1287
      float v939 = v937 + v938;	// L1288
      float v940 = a3r3;	// L1289
      float v941 = v939 + v940;	// L1290
      float b0r3;	// L1291
      b0r3 = v941;	// L1292
      float v943 = a0i3;	// L1293
      float v944 = a1i3;	// L1294
      float v945 = v943 + v944;	// L1295
      float v946 = a2i3;	// L1296
      float v947 = v945 + v946;	// L1297
      float v948 = a3i3;	// L1298
      float v949 = v947 + v948;	// L1299
      float b0i3;	// L1300
      b0i3 = v949;	// L1301
      float v951 = a0r3;	// L1302
      float v952 = a1i3;	// L1303
      float v953 = v951 + v952;	// L1304
      float v954 = a2r3;	// L1305
      float v955 = v953 - v954;	// L1306
      float v956 = a3i3;	// L1307
      float v957 = v955 - v956;	// L1308
      float b1r3;	// L1309
      b1r3 = v957;	// L1310
      float v959 = a0i3;	// L1311
      float v960 = a1r3;	// L1312
      float v961 = v959 - v960;	// L1313
      float v962 = a2i3;	// L1314
      float v963 = v961 - v962;	// L1315
      float v964 = a3r3;	// L1316
      float v965 = v963 + v964;	// L1317
      float b1i3;	// L1318
      b1i3 = v965;	// L1319
      float v967 = a0r3;	// L1320
      float v968 = a1r3;	// L1321
      float v969 = v967 - v968;	// L1322
      float v970 = a2r3;	// L1323
      float v971 = v969 + v970;	// L1324
      float v972 = a3r3;	// L1325
      float v973 = v971 - v972;	// L1326
      float b2r3;	// L1327
      b2r3 = v973;	// L1328
      float v975 = a0i3;	// L1329
      float v976 = a1i3;	// L1330
      float v977 = v975 - v976;	// L1331
      float v978 = a2i3;	// L1332
      float v979 = v977 + v978;	// L1333
      float v980 = a3i3;	// L1334
      float v981 = v979 - v980;	// L1335
      float b2i3;	// L1336
      b2i3 = v981;	// L1337
      float v983 = a0r3;	// L1338
      float v984 = a1i3;	// L1339
      float v985 = v983 - v984;	// L1340
      float v986 = a2r3;	// L1341
      float v987 = v985 - v986;	// L1342
      float v988 = a3i3;	// L1343
      float v989 = v987 + v988;	// L1344
      float b3r3;	// L1345
      b3r3 = v989;	// L1346
      float v991 = a0i3;	// L1347
      float v992 = a1r3;	// L1348
      float v993 = v991 + v992;	// L1349
      float v994 = a2i3;	// L1350
      float v995 = v993 - v994;	// L1351
      float v996 = a3r3;	// L1352
      float v997 = v995 - v996;	// L1353
      float b3i3;	// L1354
      b3i3 = v997;	// L1355
      float v999 = b0r3;	// L1356
      int v1000 = idx1_3;	// L1357
      int v1001 = v1000;	// L1358
      buf_real[v1001] = v999;	// L1359
      float v1002 = b0i3;	// L1360
      int v1003 = idx1_3;	// L1361
      int v1004 = v1003;	// L1362
      buf_imag[v1004] = v1002;	// L1363
      float v1005 = b1r3;	// L1364
      int v1006 = idx2_3;	// L1365
      int v1007 = v1006;	// L1366
      buf_real[v1007] = v1005;	// L1367
      float v1008 = b1i3;	// L1368
      int v1009 = idx2_3;	// L1369
      int v1010 = v1009;	// L1370
      buf_imag[v1010] = v1008;	// L1371
      float v1011 = b2r3;	// L1372
      int v1012 = idx3_3;	// L1373
      int v1013 = v1012;	// L1374
      buf_real[v1013] = v1011;	// L1375
      float v1014 = b2i3;	// L1376
      int v1015 = idx3_3;	// L1377
      int v1016 = v1015;	// L1378
      buf_imag[v1016] = v1014;	// L1379
      float v1017 = b3r3;	// L1380
      int v1018 = idx4_3;	// L1381
      int v1019 = v1018;	// L1382
      buf_real[v1019] = v1017;	// L1383
      float v1020 = b3i3;	// L1384
      int v1021 = idx4_3;	// L1385
      int v1022 = v1021;	// L1386
      buf_imag[v1022] = v1020;	// L1387
    }
  }
  l_S_g4_7_g4: for (int g4 = 0; g4 < 4; g4++) {	// L1390
    l_S_j4_7_j4: for (int j4 = 0; j4 < 64; j4++) {	// L1391
      int v1025 = j4;	// L1392
      float v1026 = v1025;	// L1393
      float j4_f;	// L1394
      j4_f = v1026;	// L1395
      float v1028 = PI;	// L1399
      float v1029 = v1028 * -2.000000;	// L1400
      float v1030 = j4_f;	// L1401
      float v1031 = v1029 * v1030;	// L1402
      float v1032 = v1031 / 256.000000;	// L1405
      float theta4;	// L1406
      theta4 = v1032;	// L1407
      float v1034 = theta4;	// L1408
      float v1035 = v1034 * v1034;	// L1410
      float th4_2;	// L1411
      th4_2 = v1035;	// L1412
      float v1037 = th4_2;	// L1413
      float v1038 = theta4;	// L1414
      float v1039 = v1037 * v1038;	// L1415
      float th4_3;	// L1416
      th4_3 = v1039;	// L1417
      float v1041 = th4_2;	// L1418
      float v1042 = v1041 * v1041;	// L1420
      float th4_4;	// L1421
      th4_4 = v1042;	// L1422
      float v1044 = th4_4;	// L1423
      float v1045 = theta4;	// L1424
      float v1046 = v1044 * v1045;	// L1425
      float th4_5;	// L1426
      th4_5 = v1046;	// L1427
      float v1048 = th4_4;	// L1428
      float v1049 = th4_2;	// L1429
      float v1050 = v1048 * v1049;	// L1430
      float th4_6;	// L1431
      th4_6 = v1050;	// L1432
      float v1052 = th4_6;	// L1433
      float v1053 = theta4;	// L1434
      float v1054 = v1052 * v1053;	// L1435
      float th4_7;	// L1436
      th4_7 = v1054;	// L1437
      float v1056 = th4_4;	// L1438
      float v1057 = v1056 * v1056;	// L1440
      float th4_8;	// L1441
      th4_8 = v1057;	// L1442
      float v1059 = th4_8;	// L1443
      float v1060 = theta4;	// L1444
      float v1061 = v1059 * v1060;	// L1445
      float th4_9;	// L1446
      th4_9 = v1061;	// L1447
      float v1063 = th4_8;	// L1448
      float v1064 = th4_2;	// L1449
      float v1065 = v1063 * v1064;	// L1450
      float th4_10;	// L1451
      th4_10 = v1065;	// L1452
      float v1067 = th4_10;	// L1453
      float v1068 = theta4;	// L1454
      float v1069 = v1067 * v1068;	// L1455
      float th4_11;	// L1456
      th4_11 = v1069;	// L1457
      float v1071 = th4_2;	// L1458
      float v1072 = v1071 / 2.000000;	// L1461
      float v1073 = 1.000000 - v1072;	// L1464
      float v1074 = th4_4;	// L1465
      float v1075 = v1074 / 24.000000;	// L1468
      float v1076 = v1073 + v1075;	// L1469
      float v1077 = th4_6;	// L1470
      float v1078 = v1077 / 720.000000;	// L1473
      float v1079 = v1076 - v1078;	// L1474
      float v1080 = th4_8;	// L1475
      float v1081 = v1080 / 40320.000000;	// L1478
      float v1082 = v1079 + v1081;	// L1479
      float v1083 = th4_10;	// L1480
      float v1084 = v1083 / 3628800.000000;	// L1483
      float v1085 = v1082 - v1084;	// L1484
      float cos4;	// L1485
      cos4 = v1085;	// L1486
      float v1087 = theta4;	// L1487
      float v1088 = th4_3;	// L1488
      float v1089 = v1088 / 6.000000;	// L1491
      float v1090 = v1087 - v1089;	// L1492
      float v1091 = th4_5;	// L1493
      float v1092 = v1091 / 120.000000;	// L1496
      float v1093 = v1090 + v1092;	// L1497
      float v1094 = th4_7;	// L1498
      float v1095 = v1094 / 5040.000000;	// L1501
      float v1096 = v1093 - v1095;	// L1502
      float v1097 = th4_9;	// L1503
      float v1098 = v1097 / 362880.000000;	// L1506
      float v1099 = v1096 + v1098;	// L1507
      float v1100 = th4_11;	// L1508
      float v1101 = v1100 / 39916800.000000;	// L1511
      float v1102 = v1099 - v1101;	// L1512
      float sin4;	// L1513
      sin4 = v1102;	// L1514
      float v1104 = cos4;	// L1515
      float Wr4;	// L1516
      Wr4 = v1104;	// L1517
      float v1106 = sin4;	// L1518
      float Wi4;	// L1519
      Wi4 = v1106;	// L1520
      float v1108 = Wr4;	// L1521
      float v1109 = v1108 * v1108;	// L1523
      float v1110 = Wi4;	// L1524
      float v1111 = v1110 * v1110;	// L1526
      float v1112 = v1109 - v1111;	// L1527
      float W2r4;	// L1528
      W2r4 = v1112;	// L1529
      float v1114 = Wr4;	// L1530
      float v1115 = v1114  << 1.000000;	// L1533
      float v1116 = Wi4;	// L1534
      float v1117 = v1115 * v1116;	// L1535
      float W2i4;	// L1536
      W2i4 = v1117;	// L1537
      float v1119 = W2r4;	// L1538
      float v1120 = Wr4;	// L1539
      float v1121 = v1119 * v1120;	// L1540
      float v1122 = W2i4;	// L1541
      float v1123 = Wi4;	// L1542
      float v1124 = v1122 * v1123;	// L1543
      float v1125 = v1121 - v1124;	// L1544
      float W3r4;	// L1545
      W3r4 = v1125;	// L1546
      float v1127 = W2r4;	// L1547
      float v1128 = Wi4;	// L1548
      float v1129 = v1127 * v1128;	// L1549
      float v1130 = W2i4;	// L1550
      float v1131 = Wr4;	// L1551
      float v1132 = v1130 * v1131;	// L1552
      float v1133 = v1129 + v1132;	// L1553
      float W3i4;	// L1554
      W3i4 = v1133;	// L1555
      int v1135 = g4;	// L1556
      int v1136 = v1135 * 256;	// L1560
      int v1137 = v1136;	// L1561
      int v1138 = j4;	// L1562
      int v1139 = v1137 + v1138;	// L1563
      int v1140 = v1139;	// L1564
      int base4;	// L1565
      base4 = v1140;	// L1566
      int v1142 = base4;	// L1567
      int idx1_4;	// L1568
      idx1_4 = v1142;	// L1569
      int v1144 = base4;	// L1570
      int v1145 = v1144;	// L1571
      int v1146 = v1145 + 64;	// L1575
      int v1147 = v1146;	// L1576
      int idx2_4;	// L1577
      idx2_4 = v1147;	// L1578
      int v1149 = base4;	// L1579
      int v1150 = v1149;	// L1580
      int v1151 = v1150 + 128;	// L1584
      int v1152 = v1151;	// L1585
      int idx3_4;	// L1586
      idx3_4 = v1152;	// L1587
      int v1154 = base4;	// L1588
      int v1155 = v1154;	// L1589
      int v1156 = v1155 + 192;	// L1593
      int v1157 = v1156;	// L1594
      int idx4_4;	// L1595
      idx4_4 = v1157;	// L1596
      int v1159 = idx1_4;	// L1597
      int v1160 = v1159;	// L1598
      float v1161 = buf_real[v1160];	// L1599
      float a0r4;	// L1600
      a0r4 = v1161;	// L1601
      int v1163 = idx1_4;	// L1602
      int v1164 = v1163;	// L1603
      float v1165 = buf_imag[v1164];	// L1604
      float a0i4;	// L1605
      a0i4 = v1165;	// L1606
      int v1167 = idx2_4;	// L1607
      int v1168 = v1167;	// L1608
      float v1169 = buf_real[v1168];	// L1609
      float a1r04;	// L1610
      a1r04 = v1169;	// L1611
      int v1171 = idx2_4;	// L1612
      int v1172 = v1171;	// L1613
      float v1173 = buf_imag[v1172];	// L1614
      float a1i04;	// L1615
      a1i04 = v1173;	// L1616
      int v1175 = idx3_4;	// L1617
      int v1176 = v1175;	// L1618
      float v1177 = buf_real[v1176];	// L1619
      float a2r04;	// L1620
      a2r04 = v1177;	// L1621
      int v1179 = idx3_4;	// L1622
      int v1180 = v1179;	// L1623
      float v1181 = buf_imag[v1180];	// L1624
      float a2i04;	// L1625
      a2i04 = v1181;	// L1626
      int v1183 = idx4_4;	// L1627
      int v1184 = v1183;	// L1628
      float v1185 = buf_real[v1184];	// L1629
      float a3r04;	// L1630
      a3r04 = v1185;	// L1631
      int v1187 = idx4_4;	// L1632
      int v1188 = v1187;	// L1633
      float v1189 = buf_imag[v1188];	// L1634
      float a3i04;	// L1635
      a3i04 = v1189;	// L1636
      float v1191 = a1r04;	// L1637
      float v1192 = Wr4;	// L1638
      float v1193 = v1191 * v1192;	// L1639
      float v1194 = a1i04;	// L1640
      float v1195 = Wi4;	// L1641
      float v1196 = v1194 * v1195;	// L1642
      float v1197 = v1193 - v1196;	// L1643
      float a1r4;	// L1644
      a1r4 = v1197;	// L1645
      float v1199 = a1r04;	// L1646
      float v1200 = Wi4;	// L1647
      float v1201 = v1199 * v1200;	// L1648
      float v1202 = a1i04;	// L1649
      float v1203 = Wr4;	// L1650
      float v1204 = v1202 * v1203;	// L1651
      float v1205 = v1201 + v1204;	// L1652
      float a1i4;	// L1653
      a1i4 = v1205;	// L1654
      float v1207 = a2r04;	// L1655
      float v1208 = W2r4;	// L1656
      float v1209 = v1207 * v1208;	// L1657
      float v1210 = a2i04;	// L1658
      float v1211 = W2i4;	// L1659
      float v1212 = v1210 * v1211;	// L1660
      float v1213 = v1209 - v1212;	// L1661
      float a2r4;	// L1662
      a2r4 = v1213;	// L1663
      float v1215 = a2r04;	// L1664
      float v1216 = W2i4;	// L1665
      float v1217 = v1215 * v1216;	// L1666
      float v1218 = a2i04;	// L1667
      float v1219 = W2r4;	// L1668
      float v1220 = v1218 * v1219;	// L1669
      float v1221 = v1217 + v1220;	// L1670
      float a2i4;	// L1671
      a2i4 = v1221;	// L1672
      float v1223 = a3r04;	// L1673
      float v1224 = W3r4;	// L1674
      float v1225 = v1223 * v1224;	// L1675
      float v1226 = a3i04;	// L1676
      float v1227 = W3i4;	// L1677
      float v1228 = v1226 * v1227;	// L1678
      float v1229 = v1225 - v1228;	// L1679
      float a3r4;	// L1680
      a3r4 = v1229;	// L1681
      float v1231 = a3r04;	// L1682
      float v1232 = W3i4;	// L1683
      float v1233 = v1231 * v1232;	// L1684
      float v1234 = a3i04;	// L1685
      float v1235 = W3r4;	// L1686
      float v1236 = v1234 * v1235;	// L1687
      float v1237 = v1233 + v1236;	// L1688
      float a3i4;	// L1689
      a3i4 = v1237;	// L1690
      float v1239 = a0r4;	// L1691
      float v1240 = a1r4;	// L1692
      float v1241 = v1239 + v1240;	// L1693
      float v1242 = a2r4;	// L1694
      float v1243 = v1241 + v1242;	// L1695
      float v1244 = a3r4;	// L1696
      float v1245 = v1243 + v1244;	// L1697
      float b0r4;	// L1698
      b0r4 = v1245;	// L1699
      float v1247 = a0i4;	// L1700
      float v1248 = a1i4;	// L1701
      float v1249 = v1247 + v1248;	// L1702
      float v1250 = a2i4;	// L1703
      float v1251 = v1249 + v1250;	// L1704
      float v1252 = a3i4;	// L1705
      float v1253 = v1251 + v1252;	// L1706
      float b0i4;	// L1707
      b0i4 = v1253;	// L1708
      float v1255 = a0r4;	// L1709
      float v1256 = a1i4;	// L1710
      float v1257 = v1255 + v1256;	// L1711
      float v1258 = a2r4;	// L1712
      float v1259 = v1257 - v1258;	// L1713
      float v1260 = a3i4;	// L1714
      float v1261 = v1259 - v1260;	// L1715
      float b1r4;	// L1716
      b1r4 = v1261;	// L1717
      float v1263 = a0i4;	// L1718
      float v1264 = a1r4;	// L1719
      float v1265 = v1263 - v1264;	// L1720
      float v1266 = a2i4;	// L1721
      float v1267 = v1265 - v1266;	// L1722
      float v1268 = a3r4;	// L1723
      float v1269 = v1267 + v1268;	// L1724
      float b1i4;	// L1725
      b1i4 = v1269;	// L1726
      float v1271 = a0r4;	// L1727
      float v1272 = a1r4;	// L1728
      float v1273 = v1271 - v1272;	// L1729
      float v1274 = a2r4;	// L1730
      float v1275 = v1273 + v1274;	// L1731
      float v1276 = a3r4;	// L1732
      float v1277 = v1275 - v1276;	// L1733
      float b2r4;	// L1734
      b2r4 = v1277;	// L1735
      float v1279 = a0i4;	// L1736
      float v1280 = a1i4;	// L1737
      float v1281 = v1279 - v1280;	// L1738
      float v1282 = a2i4;	// L1739
      float v1283 = v1281 + v1282;	// L1740
      float v1284 = a3i4;	// L1741
      float v1285 = v1283 - v1284;	// L1742
      float b2i4;	// L1743
      b2i4 = v1285;	// L1744
      float v1287 = a0r4;	// L1745
      float v1288 = a1i4;	// L1746
      float v1289 = v1287 - v1288;	// L1747
      float v1290 = a2r4;	// L1748
      float v1291 = v1289 - v1290;	// L1749
      float v1292 = a3i4;	// L1750
      float v1293 = v1291 + v1292;	// L1751
      float b3r4;	// L1752
      b3r4 = v1293;	// L1753
      float v1295 = a0i4;	// L1754
      float v1296 = a1r4;	// L1755
      float v1297 = v1295 + v1296;	// L1756
      float v1298 = a2i4;	// L1757
      float v1299 = v1297 - v1298;	// L1758
      float v1300 = a3r4;	// L1759
      float v1301 = v1299 - v1300;	// L1760
      float b3i4;	// L1761
      b3i4 = v1301;	// L1762
      float v1303 = b0r4;	// L1763
      int v1304 = idx1_4;	// L1764
      int v1305 = v1304;	// L1765
      buf_real[v1305] = v1303;	// L1766
      float v1306 = b0i4;	// L1767
      int v1307 = idx1_4;	// L1768
      int v1308 = v1307;	// L1769
      buf_imag[v1308] = v1306;	// L1770
      float v1309 = b1r4;	// L1771
      int v1310 = idx2_4;	// L1772
      int v1311 = v1310;	// L1773
      buf_real[v1311] = v1309;	// L1774
      float v1312 = b1i4;	// L1775
      int v1313 = idx2_4;	// L1776
      int v1314 = v1313;	// L1777
      buf_imag[v1314] = v1312;	// L1778
      float v1315 = b2r4;	// L1779
      int v1316 = idx3_4;	// L1780
      int v1317 = v1316;	// L1781
      buf_real[v1317] = v1315;	// L1782
      float v1318 = b2i4;	// L1783
      int v1319 = idx3_4;	// L1784
      int v1320 = v1319;	// L1785
      buf_imag[v1320] = v1318;	// L1786
      float v1321 = b3r4;	// L1787
      int v1322 = idx4_4;	// L1788
      int v1323 = v1322;	// L1789
      buf_real[v1323] = v1321;	// L1790
      float v1324 = b3i4;	// L1791
      int v1325 = idx4_4;	// L1792
      int v1326 = v1325;	// L1793
      buf_imag[v1326] = v1324;	// L1794
    }
  }
  l_S_g5_9_g5: for (int g5 = 0; g5 < 1; g5++) {	// L1797
    l_S_j5_9_j5: for (int j5 = 0; j5 < 256; j5++) {	// L1798
      int v1329 = j5;	// L1799
      float v1330 = v1329;	// L1800
      float j5_f;	// L1801
      j5_f = v1330;	// L1802
      float v1332 = PI;	// L1806
      float v1333 = v1332 * -2.000000;	// L1807
      float v1334 = j5_f;	// L1808
      float v1335 = v1333 * v1334;	// L1809
      float v1336 = v1335 / 1024.000000;	// L1812
      float theta5;	// L1813
      theta5 = v1336;	// L1814
      float v1338 = theta5;	// L1815
      float v1339 = v1338 * v1338;	// L1817
      float th5_2;	// L1818
      th5_2 = v1339;	// L1819
      float v1341 = th5_2;	// L1820
      float v1342 = theta5;	// L1821
      float v1343 = v1341 * v1342;	// L1822
      float th5_3;	// L1823
      th5_3 = v1343;	// L1824
      float v1345 = th5_2;	// L1825
      float v1346 = v1345 * v1345;	// L1827
      float th5_4;	// L1828
      th5_4 = v1346;	// L1829
      float v1348 = th5_4;	// L1830
      float v1349 = theta5;	// L1831
      float v1350 = v1348 * v1349;	// L1832
      float th5_5;	// L1833
      th5_5 = v1350;	// L1834
      float v1352 = th5_4;	// L1835
      float v1353 = th5_2;	// L1836
      float v1354 = v1352 * v1353;	// L1837
      float th5_6;	// L1838
      th5_6 = v1354;	// L1839
      float v1356 = th5_6;	// L1840
      float v1357 = theta5;	// L1841
      float v1358 = v1356 * v1357;	// L1842
      float th5_7;	// L1843
      th5_7 = v1358;	// L1844
      float v1360 = th5_4;	// L1845
      float v1361 = v1360 * v1360;	// L1847
      float th5_8;	// L1848
      th5_8 = v1361;	// L1849
      float v1363 = th5_8;	// L1850
      float v1364 = theta5;	// L1851
      float v1365 = v1363 * v1364;	// L1852
      float th5_9;	// L1853
      th5_9 = v1365;	// L1854
      float v1367 = th5_8;	// L1855
      float v1368 = th5_2;	// L1856
      float v1369 = v1367 * v1368;	// L1857
      float th5_10;	// L1858
      th5_10 = v1369;	// L1859
      float v1371 = th5_10;	// L1860
      float v1372 = theta5;	// L1861
      float v1373 = v1371 * v1372;	// L1862
      float th5_11;	// L1863
      th5_11 = v1373;	// L1864
      float v1375 = th5_2;	// L1865
      float v1376 = v1375 / 2.000000;	// L1868
      float v1377 = 1.000000 - v1376;	// L1871
      float v1378 = th5_4;	// L1872
      float v1379 = v1378 / 24.000000;	// L1875
      float v1380 = v1377 + v1379;	// L1876
      float v1381 = th5_6;	// L1877
      float v1382 = v1381 / 720.000000;	// L1880
      float v1383 = v1380 - v1382;	// L1881
      float v1384 = th5_8;	// L1882
      float v1385 = v1384 / 40320.000000;	// L1885
      float v1386 = v1383 + v1385;	// L1886
      float v1387 = th5_10;	// L1887
      float v1388 = v1387 / 3628800.000000;	// L1890
      float v1389 = v1386 - v1388;	// L1891
      float cos5;	// L1892
      cos5 = v1389;	// L1893
      float v1391 = theta5;	// L1894
      float v1392 = th5_3;	// L1895
      float v1393 = v1392 / 6.000000;	// L1898
      float v1394 = v1391 - v1393;	// L1899
      float v1395 = th5_5;	// L1900
      float v1396 = v1395 / 120.000000;	// L1903
      float v1397 = v1394 + v1396;	// L1904
      float v1398 = th5_7;	// L1905
      float v1399 = v1398 / 5040.000000;	// L1908
      float v1400 = v1397 - v1399;	// L1909
      float v1401 = th5_9;	// L1910
      float v1402 = v1401 / 362880.000000;	// L1913
      float v1403 = v1400 + v1402;	// L1914
      float v1404 = th5_11;	// L1915
      float v1405 = v1404 / 39916800.000000;	// L1918
      float v1406 = v1403 - v1405;	// L1919
      float sin5;	// L1920
      sin5 = v1406;	// L1921
      float v1408 = cos5;	// L1922
      float Wr5;	// L1923
      Wr5 = v1408;	// L1924
      float v1410 = sin5;	// L1925
      float Wi5;	// L1926
      Wi5 = v1410;	// L1927
      float v1412 = Wr5;	// L1928
      float v1413 = v1412 * v1412;	// L1930
      float v1414 = Wi5;	// L1931
      float v1415 = v1414 * v1414;	// L1933
      float v1416 = v1413 - v1415;	// L1934
      float W2r5;	// L1935
      W2r5 = v1416;	// L1936
      float v1418 = Wr5;	// L1937
      float v1419 = v1418  << 1.000000;	// L1940
      float v1420 = Wi5;	// L1941
      float v1421 = v1419 * v1420;	// L1942
      float W2i5;	// L1943
      W2i5 = v1421;	// L1944
      float v1423 = W2r5;	// L1945
      float v1424 = Wr5;	// L1946
      float v1425 = v1423 * v1424;	// L1947
      float v1426 = W2i5;	// L1948
      float v1427 = Wi5;	// L1949
      float v1428 = v1426 * v1427;	// L1950
      float v1429 = v1425 - v1428;	// L1951
      float W3r5;	// L1952
      W3r5 = v1429;	// L1953
      float v1431 = W2r5;	// L1954
      float v1432 = Wi5;	// L1955
      float v1433 = v1431 * v1432;	// L1956
      float v1434 = W2i5;	// L1957
      float v1435 = Wr5;	// L1958
      float v1436 = v1434 * v1435;	// L1959
      float v1437 = v1433 + v1436;	// L1960
      float W3i5;	// L1961
      W3i5 = v1437;	// L1962
      int v1439 = g5;	// L1963
      int v1440 = v1439 * 1024;	// L1967
      int v1441 = v1440;	// L1968
      int v1442 = j5;	// L1969
      int v1443 = v1441 + v1442;	// L1970
      int v1444 = v1443;	// L1971
      int base5;	// L1972
      base5 = v1444;	// L1973
      int v1446 = base5;	// L1974
      int idx1_5;	// L1975
      idx1_5 = v1446;	// L1976
      int v1448 = base5;	// L1977
      int v1449 = v1448;	// L1978
      int v1450 = v1449 + 256;	// L1982
      int v1451 = v1450;	// L1983
      int idx2_5;	// L1984
      idx2_5 = v1451;	// L1985
      int v1453 = base5;	// L1986
      int v1454 = v1453;	// L1987
      int v1455 = v1454 + 512;	// L1991
      int v1456 = v1455;	// L1992
      int idx3_5;	// L1993
      idx3_5 = v1456;	// L1994
      int v1458 = base5;	// L1995
      int v1459 = v1458;	// L1996
      int v1460 = v1459 + 768;	// L2000
      int v1461 = v1460;	// L2001
      int idx4_5;	// L2002
      idx4_5 = v1461;	// L2003
      int v1463 = idx1_5;	// L2004
      int v1464 = v1463;	// L2005
      float v1465 = buf_real[v1464];	// L2006
      float a0r5;	// L2007
      a0r5 = v1465;	// L2008
      int v1467 = idx1_5;	// L2009
      int v1468 = v1467;	// L2010
      float v1469 = buf_imag[v1468];	// L2011
      float a0i5;	// L2012
      a0i5 = v1469;	// L2013
      int v1471 = idx2_5;	// L2014
      int v1472 = v1471;	// L2015
      float v1473 = buf_real[v1472];	// L2016
      float a1r05;	// L2017
      a1r05 = v1473;	// L2018
      int v1475 = idx2_5;	// L2019
      int v1476 = v1475;	// L2020
      float v1477 = buf_imag[v1476];	// L2021
      float a1i05;	// L2022
      a1i05 = v1477;	// L2023
      int v1479 = idx3_5;	// L2024
      int v1480 = v1479;	// L2025
      float v1481 = buf_real[v1480];	// L2026
      float a2r05;	// L2027
      a2r05 = v1481;	// L2028
      int v1483 = idx3_5;	// L2029
      int v1484 = v1483;	// L2030
      float v1485 = buf_imag[v1484];	// L2031
      float a2i05;	// L2032
      a2i05 = v1485;	// L2033
      int v1487 = idx4_5;	// L2034
      int v1488 = v1487;	// L2035
      float v1489 = buf_real[v1488];	// L2036
      float a3r05;	// L2037
      a3r05 = v1489;	// L2038
      int v1491 = idx4_5;	// L2039
      int v1492 = v1491;	// L2040
      float v1493 = buf_imag[v1492];	// L2041
      float a3i05;	// L2042
      a3i05 = v1493;	// L2043
      float v1495 = a1r05;	// L2044
      float v1496 = Wr5;	// L2045
      float v1497 = v1495 * v1496;	// L2046
      float v1498 = a1i05;	// L2047
      float v1499 = Wi5;	// L2048
      float v1500 = v1498 * v1499;	// L2049
      float v1501 = v1497 - v1500;	// L2050
      float a1r5;	// L2051
      a1r5 = v1501;	// L2052
      float v1503 = a1r05;	// L2053
      float v1504 = Wi5;	// L2054
      float v1505 = v1503 * v1504;	// L2055
      float v1506 = a1i05;	// L2056
      float v1507 = Wr5;	// L2057
      float v1508 = v1506 * v1507;	// L2058
      float v1509 = v1505 + v1508;	// L2059
      float a1i5;	// L2060
      a1i5 = v1509;	// L2061
      float v1511 = a2r05;	// L2062
      float v1512 = W2r5;	// L2063
      float v1513 = v1511 * v1512;	// L2064
      float v1514 = a2i05;	// L2065
      float v1515 = W2i5;	// L2066
      float v1516 = v1514 * v1515;	// L2067
      float v1517 = v1513 - v1516;	// L2068
      float a2r5;	// L2069
      a2r5 = v1517;	// L2070
      float v1519 = a2r05;	// L2071
      float v1520 = W2i5;	// L2072
      float v1521 = v1519 * v1520;	// L2073
      float v1522 = a2i05;	// L2074
      float v1523 = W2r5;	// L2075
      float v1524 = v1522 * v1523;	// L2076
      float v1525 = v1521 + v1524;	// L2077
      float a2i5;	// L2078
      a2i5 = v1525;	// L2079
      float v1527 = a3r05;	// L2080
      float v1528 = W3r5;	// L2081
      float v1529 = v1527 * v1528;	// L2082
      float v1530 = a3i05;	// L2083
      float v1531 = W3i5;	// L2084
      float v1532 = v1530 * v1531;	// L2085
      float v1533 = v1529 - v1532;	// L2086
      float a3r5;	// L2087
      a3r5 = v1533;	// L2088
      float v1535 = a3r05;	// L2089
      float v1536 = W3i5;	// L2090
      float v1537 = v1535 * v1536;	// L2091
      float v1538 = a3i05;	// L2092
      float v1539 = W3r5;	// L2093
      float v1540 = v1538 * v1539;	// L2094
      float v1541 = v1537 + v1540;	// L2095
      float a3i5;	// L2096
      a3i5 = v1541;	// L2097
      float v1543 = a0r5;	// L2098
      float v1544 = a1r5;	// L2099
      float v1545 = v1543 + v1544;	// L2100
      float v1546 = a2r5;	// L2101
      float v1547 = v1545 + v1546;	// L2102
      float v1548 = a3r5;	// L2103
      float v1549 = v1547 + v1548;	// L2104
      float b0r5;	// L2105
      b0r5 = v1549;	// L2106
      float v1551 = a0i5;	// L2107
      float v1552 = a1i5;	// L2108
      float v1553 = v1551 + v1552;	// L2109
      float v1554 = a2i5;	// L2110
      float v1555 = v1553 + v1554;	// L2111
      float v1556 = a3i5;	// L2112
      float v1557 = v1555 + v1556;	// L2113
      float b0i5;	// L2114
      b0i5 = v1557;	// L2115
      float v1559 = a0r5;	// L2116
      float v1560 = a1i5;	// L2117
      float v1561 = v1559 + v1560;	// L2118
      float v1562 = a2r5;	// L2119
      float v1563 = v1561 - v1562;	// L2120
      float v1564 = a3i5;	// L2121
      float v1565 = v1563 - v1564;	// L2122
      float b1r5;	// L2123
      b1r5 = v1565;	// L2124
      float v1567 = a0i5;	// L2125
      float v1568 = a1r5;	// L2126
      float v1569 = v1567 - v1568;	// L2127
      float v1570 = a2i5;	// L2128
      float v1571 = v1569 - v1570;	// L2129
      float v1572 = a3r5;	// L2130
      float v1573 = v1571 + v1572;	// L2131
      float b1i5;	// L2132
      b1i5 = v1573;	// L2133
      float v1575 = a0r5;	// L2134
      float v1576 = a1r5;	// L2135
      float v1577 = v1575 - v1576;	// L2136
      float v1578 = a2r5;	// L2137
      float v1579 = v1577 + v1578;	// L2138
      float v1580 = a3r5;	// L2139
      float v1581 = v1579 - v1580;	// L2140
      float b2r5;	// L2141
      b2r5 = v1581;	// L2142
      float v1583 = a0i5;	// L2143
      float v1584 = a1i5;	// L2144
      float v1585 = v1583 - v1584;	// L2145
      float v1586 = a2i5;	// L2146
      float v1587 = v1585 + v1586;	// L2147
      float v1588 = a3i5;	// L2148
      float v1589 = v1587 - v1588;	// L2149
      float b2i5;	// L2150
      b2i5 = v1589;	// L2151
      float v1591 = a0r5;	// L2152
      float v1592 = a1i5;	// L2153
      float v1593 = v1591 - v1592;	// L2154
      float v1594 = a2r5;	// L2155
      float v1595 = v1593 - v1594;	// L2156
      float v1596 = a3i5;	// L2157
      float v1597 = v1595 + v1596;	// L2158
      float b3r5;	// L2159
      b3r5 = v1597;	// L2160
      float v1599 = a0i5;	// L2161
      float v1600 = a1r5;	// L2162
      float v1601 = v1599 + v1600;	// L2163
      float v1602 = a2i5;	// L2164
      float v1603 = v1601 - v1602;	// L2165
      float v1604 = a3r5;	// L2166
      float v1605 = v1603 - v1604;	// L2167
      float b3i5;	// L2168
      b3i5 = v1605;	// L2169
      float v1607 = b0r5;	// L2170
      int v1608 = idx1_5;	// L2171
      int v1609 = v1608;	// L2172
      buf_real[v1609] = v1607;	// L2173
      float v1610 = b0i5;	// L2174
      int v1611 = idx1_5;	// L2175
      int v1612 = v1611;	// L2176
      buf_imag[v1612] = v1610;	// L2177
      float v1613 = b1r5;	// L2178
      int v1614 = idx2_5;	// L2179
      int v1615 = v1614;	// L2180
      buf_real[v1615] = v1613;	// L2181
      float v1616 = b1i5;	// L2182
      int v1617 = idx2_5;	// L2183
      int v1618 = v1617;	// L2184
      buf_imag[v1618] = v1616;	// L2185
      float v1619 = b2r5;	// L2186
      int v1620 = idx3_5;	// L2187
      int v1621 = v1620;	// L2188
      buf_real[v1621] = v1619;	// L2189
      float v1622 = b2i5;	// L2190
      int v1623 = idx3_5;	// L2191
      int v1624 = v1623;	// L2192
      buf_imag[v1624] = v1622;	// L2193
      float v1625 = b3r5;	// L2194
      int v1626 = idx4_5;	// L2195
      int v1627 = v1626;	// L2196
      buf_real[v1627] = v1625;	// L2197
      float v1628 = b3i5;	// L2198
      int v1629 = idx4_5;	// L2199
      int v1630 = v1629;	// L2200
      buf_imag[v1630] = v1628;	// L2201
    }
  }
  l_S_c_11_c: for (int c = 0; c < 1024; c++) {	// L2204
    float v1632 = buf_real[c];	// L2205
    v2[c] = v1632;	// L2206
    float v1633 = buf_imag[c];	// L2207
    v3[c] = v1633;	// L2208
  }
}
#pragma pocc-region-end
}

