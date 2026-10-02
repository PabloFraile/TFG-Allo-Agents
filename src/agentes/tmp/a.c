
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
  float PI;	// L5
  PI = 3.141593;	// L6
  float buf_real[1024];	// L7
  #pragma HLS array_partition variable=buf_real complete dim=1

  float buf_imag[1024];	// L8
  #pragma HLS array_partition variable=buf_imag complete dim=1

  l_S_p_0_p: for (int p = 0; p < 1024; p++) {	// L9
  #pragma HLS pipeline II=3
    int v8 = p;	// L10
    int t0;	// L11
    t0 = v8;	// L12
    int v10 = t0;	// L13
    int v11 = v10 / 4;	// L15
    int q0;	// L16
    q0 = v11;	// L17
    int v13 = t0;	// L18
    int v14 = q0;	// L19
    int v15 = v14;	// L20
    int v16 = v15 * 4;	// L22
    int v17 = v13;	// L23
    int v18 = v16;	// L24
    int v19 = v17 - v18;	// L25
    int v20 = v19;	// L26
    int d0;	// L27
    d0 = v20;	// L28
    int v22 = q0;	// L29
    int t1;	// L30
    t1 = v22;	// L31
    int v24 = t1;	// L32
    int v25 = v24 / 4;	// L33
    int q1;	// L34
    q1 = v25;	// L35
    int v27 = t1;	// L36
    int v28 = q1;	// L37
    int v29 = v28;	// L38
    int v30 = v29 * 4;	// L39
    int v31 = v27;	// L40
    int v32 = v30;	// L41
    int v33 = v31 - v32;	// L42
    int v34 = v33;	// L43
    int d1;	// L44
    d1 = v34;	// L45
    int v36 = q1;	// L46
    int t2;	// L47
    t2 = v36;	// L48
    int v38 = t2;	// L49
    int v39 = v38 / 4;	// L50
    int q2;	// L51
    q2 = v39;	// L52
    int v41 = t2;	// L53
    int v42 = q2;	// L54
    int v43 = v42;	// L55
    int v44 = v43 * 4;	// L56
    int v45 = v41;	// L57
    int v46 = v44;	// L58
    int v47 = v45 - v46;	// L59
    int v48 = v47;	// L60
    int d2;	// L61
    d2 = v48;	// L62
    int v50 = q2;	// L63
    int t3;	// L64
    t3 = v50;	// L65
    int v52 = t3;	// L66
    int v53 = v52 / 4;	// L67
    int q3;	// L68
    q3 = v53;	// L69
    int v55 = t3;	// L70
    int v56 = q3;	// L71
    int v57 = v56;	// L72
    int v58 = v57 * 4;	// L73
    int v59 = v55;	// L74
    int v60 = v58;	// L75
    int v61 = v59 - v60;	// L76
    int v62 = v61;	// L77
    int d3;	// L78
    d3 = v62;	// L79
    int v64 = q3;	// L80
    int t4;	// L81
    t4 = v64;	// L82
    int v66 = t4;	// L83
    int v67 = v66 / 4;	// L84
    int q4;	// L85
    q4 = v67;	// L86
    int v69 = t4;	// L87
    int v70 = q4;	// L88
    int v71 = v70;	// L89
    int v72 = v71 * 4;	// L90
    int v73 = v69;	// L91
    int v74 = v72;	// L92
    int v75 = v73 - v74;	// L93
    int v76 = v75;	// L94
    int d4;	// L95
    d4 = v76;	// L96
    int v78 = d0;	// L97
    int v79 = v78;	// L98
    int v80 = v79 * 256;	// L101
    int v81 = d1;	// L102
    int v82 = v81;	// L103
    int v83 = v82 * 64;	// L106
    int v84 = v80;	// L107
    int v85 = v83;	// L108
    int v86 = v84 + v85;	// L109
    int v87 = d2;	// L110
    int v88 = v87;	// L111
    int v89 = v88 * 16;	// L114
    int v90 = v86;	// L115
    int v91 = v89;	// L116
    int v92 = v90 + v91;	// L117
    int v93 = d3;	// L118
    int v94 = v93;	// L119
    int v95 = v94 * 4;	// L120
    int v96 = v92;	// L121
    int v97 = v95;	// L122
    int v98 = v96 + v97;	// L123
    int v99 = d4;	// L124
    int v100 = v98;	// L125
    int v101 = v99;	// L126
    int v102 = v100 + v101;	// L127
    int v103 = v102;	// L128
    int r;	// L129
    r = v103;	// L130
    int v105 = r;	// L131
    int v106 = v105;	// L132
    float v107 = v0[v106];	// L133
    buf_real[p] = v107;	// L134
    int v108 = r;	// L135
    int v109 = v108;	// L136
    float v110 = v1[v109];	// L137
    buf_imag[p] = v110;	// L138
  }
  l_S_g1_1_g1: for (int g1 = 0; g1 < 256; g1++) {	// L140
  #pragma HLS pipeline II=3
    l_S_j1_1_j1: for (int j1 = 0; j1 < 1; j1++) {	// L141
      int v113 = j1;	// L142
      float v114 = v113;	// L143
      float j1_f;	// L144
      j1_f = v114;	// L145
      float v116 = PI;	// L148
      float v117 = v116 * -2.000000;	// L149
      float v118 = j1_f;	// L150
      float v119 = v117 * v118;	// L151
      float v120 = v119 / 4.000000;	// L153
      float theta1;	// L154
      theta1 = v120;	// L155
      float v122 = theta1;	// L156
      float v123 = v122 * v122;	// L157
      float th1_2;	// L158
      th1_2 = v123;	// L159
      float v125 = th1_2;	// L160
      float v126 = theta1;	// L161
      float v127 = v125 * v126;	// L162
      float th1_3;	// L163
      th1_3 = v127;	// L164
      float v129 = th1_2;	// L165
      float v130 = v129 * v129;	// L166
      float th1_4;	// L167
      th1_4 = v130;	// L168
      float v132 = th1_4;	// L169
      float v133 = theta1;	// L170
      float v134 = v132 * v133;	// L171
      float th1_5;	// L172
      th1_5 = v134;	// L173
      float v136 = th1_4;	// L174
      float v137 = th1_2;	// L175
      float v138 = v136 * v137;	// L176
      float th1_6;	// L177
      th1_6 = v138;	// L178
      float v140 = th1_6;	// L179
      float v141 = theta1;	// L180
      float v142 = v140 * v141;	// L181
      float th1_7;	// L182
      th1_7 = v142;	// L183
      float v144 = th1_4;	// L184
      float v145 = v144 * v144;	// L185
      float th1_8;	// L186
      th1_8 = v145;	// L187
      float v147 = th1_8;	// L188
      float v148 = theta1;	// L189
      float v149 = v147 * v148;	// L190
      float th1_9;	// L191
      th1_9 = v149;	// L192
      float v151 = th1_8;	// L193
      float v152 = th1_2;	// L194
      float v153 = v151 * v152;	// L195
      float th1_10;	// L196
      th1_10 = v153;	// L197
      float v155 = th1_10;	// L198
      float v156 = theta1;	// L199
      float v157 = v155 * v156;	// L200
      float th1_11;	// L201
      th1_11 = v157;	// L202
      float v159 = th1_2;	// L203
      float v160 = v159 / 2.000000;	// L204
      float v161 = 1.000000 - v160;	// L206
      float v162 = th1_4;	// L207
      float v163 = v162 / 24.000000;	// L209
      float v164 = v161 + v163;	// L210
      float v165 = th1_6;	// L211
      float v166 = v165 / 720.000000;	// L213
      float v167 = v164 - v166;	// L214
      float v168 = th1_8;	// L215
      float v169 = v168 / 40320.000000;	// L217
      float v170 = v167 + v169;	// L218
      float v171 = th1_10;	// L219
      float v172 = v171 / 3628800.000000;	// L221
      float v173 = v170 - v172;	// L222
      float cos1;	// L223
      cos1 = v173;	// L224
      float v175 = theta1;	// L225
      float v176 = th1_3;	// L226
      float v177 = v176 / 6.000000;	// L228
      float v178 = v175 - v177;	// L229
      float v179 = th1_5;	// L230
      float v180 = v179 / 120.000000;	// L232
      float v181 = v178 + v180;	// L233
      float v182 = th1_7;	// L234
      float v183 = v182 / 5040.000000;	// L236
      float v184 = v181 - v183;	// L237
      float v185 = th1_9;	// L238
      float v186 = v185 / 362880.000000;	// L240
      float v187 = v184 + v186;	// L241
      float v188 = th1_11;	// L242
      float v189 = v188 / 39916800.000000;	// L244
      float v190 = v187 - v189;	// L245
      float sin1;	// L246
      sin1 = v190;	// L247
      float v192 = cos1;	// L248
      float Wr1;	// L249
      Wr1 = v192;	// L250
      float v194 = sin1;	// L251
      float Wi1;	// L252
      Wi1 = v194;	// L253
      float v196 = Wr1;	// L254
      float v197 = v196 * v196;	// L255
      float v198 = Wi1;	// L256
      float v199 = v198 * v198;	// L257
      float v200 = v197 - v199;	// L258
      float W2r1;	// L259
      W2r1 = v200;	// L260
      float v202 = Wr1;	// L261
      float v203 = v202  << 1.000000;	// L262
      float v204 = Wi1;	// L263
      float v205 = v203 * v204;	// L264
      float W2i1;	// L265
      W2i1 = v205;	// L266
      float v207 = W2r1;	// L267
      float v208 = Wr1;	// L268
      float v209 = v207 * v208;	// L269
      float v210 = W2i1;	// L270
      float v211 = Wi1;	// L271
      float v212 = v210 * v211;	// L272
      float v213 = v209 - v212;	// L273
      float W3r1;	// L274
      W3r1 = v213;	// L275
      float v215 = W2r1;	// L276
      float v216 = Wi1;	// L277
      float v217 = v215 * v216;	// L278
      float v218 = W2i1;	// L279
      float v219 = Wr1;	// L280
      float v220 = v218 * v219;	// L281
      float v221 = v217 + v220;	// L282
      float W3i1;	// L283
      W3i1 = v221;	// L284
      int v223 = g1;	// L285
      int v224 = v223 * 4;	// L288
      int v225 = v224;	// L289
      int v226 = j1;	// L290
      int v227 = v225 + v226;	// L291
      int v228 = v227;	// L292
      int base1;	// L293
      base1 = v228;	// L294
      int v230 = base1;	// L295
      int idx1_1;	// L296
      idx1_1 = v230;	// L297
      int v232 = base1;	// L298
      int v233 = v232;	// L299
      int v234 = v233 + 1;	// L302
      int v235 = v234;	// L303
      int idx2_1;	// L304
      idx2_1 = v235;	// L305
      int v237 = base1;	// L306
      int v238 = v237;	// L307
      int v239 = v238 + 2;	// L310
      int v240 = v239;	// L311
      int idx3_1;	// L312
      idx3_1 = v240;	// L313
      int v242 = base1;	// L314
      int v243 = v242;	// L315
      int v244 = v243 + 3;	// L318
      int v245 = v244;	// L319
      int idx4_1;	// L320
      idx4_1 = v245;	// L321
      int v247 = idx1_1;	// L322
      int v248 = v247;	// L323
      float v249 = buf_real[v248];	// L324
      float a0r1;	// L325
      a0r1 = v249;	// L326
      int v251 = idx1_1;	// L327
      int v252 = v251;	// L328
      float v253 = buf_imag[v252];	// L329
      float a0i1;	// L330
      a0i1 = v253;	// L331
      int v255 = idx2_1;	// L332
      int v256 = v255;	// L333
      float v257 = buf_real[v256];	// L334
      float a1r01;	// L335
      a1r01 = v257;	// L336
      int v259 = idx2_1;	// L337
      int v260 = v259;	// L338
      float v261 = buf_imag[v260];	// L339
      float a1i01;	// L340
      a1i01 = v261;	// L341
      int v263 = idx3_1;	// L342
      int v264 = v263;	// L343
      float v265 = buf_real[v264];	// L344
      float a2r01;	// L345
      a2r01 = v265;	// L346
      int v267 = idx3_1;	// L347
      int v268 = v267;	// L348
      float v269 = buf_imag[v268];	// L349
      float a2i01;	// L350
      a2i01 = v269;	// L351
      int v271 = idx4_1;	// L352
      int v272 = v271;	// L353
      float v273 = buf_real[v272];	// L354
      float a3r01;	// L355
      a3r01 = v273;	// L356
      int v275 = idx4_1;	// L357
      int v276 = v275;	// L358
      float v277 = buf_imag[v276];	// L359
      float a3i01;	// L360
      a3i01 = v277;	// L361
      float v279 = a1r01;	// L362
      float v280 = Wr1;	// L363
      float v281 = v279 * v280;	// L364
      float v282 = a1i01;	// L365
      float v283 = Wi1;	// L366
      float v284 = v282 * v283;	// L367
      float v285 = v281 - v284;	// L368
      float a1r1;	// L369
      a1r1 = v285;	// L370
      float v287 = a1r01;	// L371
      float v288 = Wi1;	// L372
      float v289 = v287 * v288;	// L373
      float v290 = a1i01;	// L374
      float v291 = Wr1;	// L375
      float v292 = v290 * v291;	// L376
      float v293 = v289 + v292;	// L377
      float a1i1;	// L378
      a1i1 = v293;	// L379
      float v295 = a2r01;	// L380
      float v296 = W2r1;	// L381
      float v297 = v295 * v296;	// L382
      float v298 = a2i01;	// L383
      float v299 = W2i1;	// L384
      float v300 = v298 * v299;	// L385
      float v301 = v297 - v300;	// L386
      float a2r1;	// L387
      a2r1 = v301;	// L388
      float v303 = a2r01;	// L389
      float v304 = W2i1;	// L390
      float v305 = v303 * v304;	// L391
      float v306 = a2i01;	// L392
      float v307 = W2r1;	// L393
      float v308 = v306 * v307;	// L394
      float v309 = v305 + v308;	// L395
      float a2i1;	// L396
      a2i1 = v309;	// L397
      float v311 = a3r01;	// L398
      float v312 = W3r1;	// L399
      float v313 = v311 * v312;	// L400
      float v314 = a3i01;	// L401
      float v315 = W3i1;	// L402
      float v316 = v314 * v315;	// L403
      float v317 = v313 - v316;	// L404
      float a3r1;	// L405
      a3r1 = v317;	// L406
      float v319 = a3r01;	// L407
      float v320 = W3i1;	// L408
      float v321 = v319 * v320;	// L409
      float v322 = a3i01;	// L410
      float v323 = W3r1;	// L411
      float v324 = v322 * v323;	// L412
      float v325 = v321 + v324;	// L413
      float a3i1;	// L414
      a3i1 = v325;	// L415
      float v327 = a0r1;	// L416
      float v328 = a1r1;	// L417
      float v329 = v327 + v328;	// L418
      float v330 = a2r1;	// L419
      float v331 = v329 + v330;	// L420
      float v332 = a3r1;	// L421
      float v333 = v331 + v332;	// L422
      float b0r1;	// L423
      b0r1 = v333;	// L424
      float v335 = a0i1;	// L425
      float v336 = a1i1;	// L426
      float v337 = v335 + v336;	// L427
      float v338 = a2i1;	// L428
      float v339 = v337 + v338;	// L429
      float v340 = a3i1;	// L430
      float v341 = v339 + v340;	// L431
      float b0i1;	// L432
      b0i1 = v341;	// L433
      float v343 = a0r1;	// L434
      float v344 = a1i1;	// L435
      float v345 = v343 + v344;	// L436
      float v346 = a2r1;	// L437
      float v347 = v345 - v346;	// L438
      float v348 = a3i1;	// L439
      float v349 = v347 - v348;	// L440
      float b1r1;	// L441
      b1r1 = v349;	// L442
      float v351 = a0i1;	// L443
      float v352 = a1r1;	// L444
      float v353 = v351 - v352;	// L445
      float v354 = a2i1;	// L446
      float v355 = v353 - v354;	// L447
      float v356 = a3r1;	// L448
      float v357 = v355 + v356;	// L449
      float b1i1;	// L450
      b1i1 = v357;	// L451
      float v359 = a0r1;	// L452
      float v360 = a1r1;	// L453
      float v361 = v359 - v360;	// L454
      float v362 = a2r1;	// L455
      float v363 = v361 + v362;	// L456
      float v364 = a3r1;	// L457
      float v365 = v363 - v364;	// L458
      float b2r1;	// L459
      b2r1 = v365;	// L460
      float v367 = a0i1;	// L461
      float v368 = a1i1;	// L462
      float v369 = v367 - v368;	// L463
      float v370 = a2i1;	// L464
      float v371 = v369 + v370;	// L465
      float v372 = a3i1;	// L466
      float v373 = v371 - v372;	// L467
      float b2i1;	// L468
      b2i1 = v373;	// L469
      float v375 = a0r1;	// L470
      float v376 = a1i1;	// L471
      float v377 = v375 - v376;	// L472
      float v378 = a2r1;	// L473
      float v379 = v377 - v378;	// L474
      float v380 = a3i1;	// L475
      float v381 = v379 + v380;	// L476
      float b3r1;	// L477
      b3r1 = v381;	// L478
      float v383 = a0i1;	// L479
      float v384 = a1r1;	// L480
      float v385 = v383 + v384;	// L481
      float v386 = a2i1;	// L482
      float v387 = v385 - v386;	// L483
      float v388 = a3r1;	// L484
      float v389 = v387 - v388;	// L485
      float b3i1;	// L486
      b3i1 = v389;	// L487
      float v391 = b0r1;	// L488
      int v392 = idx1_1;	// L489
      int v393 = v392;	// L490
      buf_real[v393] = v391;	// L491
      float v394 = b0i1;	// L492
      int v395 = idx1_1;	// L493
      int v396 = v395;	// L494
      buf_imag[v396] = v394;	// L495
      float v397 = b1r1;	// L496
      int v398 = idx2_1;	// L497
      int v399 = v398;	// L498
      buf_real[v399] = v397;	// L499
      float v400 = b1i1;	// L500
      int v401 = idx2_1;	// L501
      int v402 = v401;	// L502
      buf_imag[v402] = v400;	// L503
      float v403 = b2r1;	// L504
      int v404 = idx3_1;	// L505
      int v405 = v404;	// L506
      buf_real[v405] = v403;	// L507
      float v406 = b2i1;	// L508
      int v407 = idx3_1;	// L509
      int v408 = v407;	// L510
      buf_imag[v408] = v406;	// L511
      float v409 = b3r1;	// L512
      int v410 = idx4_1;	// L513
      int v411 = v410;	// L514
      buf_real[v411] = v409;	// L515
      float v412 = b3i1;	// L516
      int v413 = idx4_1;	// L517
      int v414 = v413;	// L518
      buf_imag[v414] = v412;	// L519
    }
  }
  l_S_g2_3_g2: for (int g2 = 0; g2 < 64; g2++) {	// L522
  #pragma HLS pipeline II=3
    l_S_j2_3_j2: for (int j2 = 0; j2 < 4; j2++) {	// L523
      int v417 = j2;	// L524
      float v418 = v417;	// L525
      float j2_f;	// L526
      j2_f = v418;	// L527
      float v420 = PI;	// L530
      float v421 = v420 * -2.000000;	// L531
      float v422 = j2_f;	// L532
      float v423 = v421 * v422;	// L533
      float v424 = v423 / 16.000000;	// L535
      float theta2;	// L536
      theta2 = v424;	// L537
      float v426 = theta2;	// L538
      float v427 = v426 * v426;	// L539
      float th2_2;	// L540
      th2_2 = v427;	// L541
      float v429 = th2_2;	// L542
      float v430 = theta2;	// L543
      float v431 = v429 * v430;	// L544
      float th2_3;	// L545
      th2_3 = v431;	// L546
      float v433 = th2_2;	// L547
      float v434 = v433 * v433;	// L548
      float th2_4;	// L549
      th2_4 = v434;	// L550
      float v436 = th2_4;	// L551
      float v437 = theta2;	// L552
      float v438 = v436 * v437;	// L553
      float th2_5;	// L554
      th2_5 = v438;	// L555
      float v440 = th2_4;	// L556
      float v441 = th2_2;	// L557
      float v442 = v440 * v441;	// L558
      float th2_6;	// L559
      th2_6 = v442;	// L560
      float v444 = th2_6;	// L561
      float v445 = theta2;	// L562
      float v446 = v444 * v445;	// L563
      float th2_7;	// L564
      th2_7 = v446;	// L565
      float v448 = th2_4;	// L566
      float v449 = v448 * v448;	// L567
      float th2_8;	// L568
      th2_8 = v449;	// L569
      float v451 = th2_8;	// L570
      float v452 = theta2;	// L571
      float v453 = v451 * v452;	// L572
      float th2_9;	// L573
      th2_9 = v453;	// L574
      float v455 = th2_8;	// L575
      float v456 = th2_2;	// L576
      float v457 = v455 * v456;	// L577
      float th2_10;	// L578
      th2_10 = v457;	// L579
      float v459 = th2_10;	// L580
      float v460 = theta2;	// L581
      float v461 = v459 * v460;	// L582
      float th2_11;	// L583
      th2_11 = v461;	// L584
      float v463 = th2_2;	// L585
      float v464 = v463 / 2.000000;	// L586
      float v465 = 1.000000 - v464;	// L588
      float v466 = th2_4;	// L589
      float v467 = v466 / 24.000000;	// L591
      float v468 = v465 + v467;	// L592
      float v469 = th2_6;	// L593
      float v470 = v469 / 720.000000;	// L595
      float v471 = v468 - v470;	// L596
      float v472 = th2_8;	// L597
      float v473 = v472 / 40320.000000;	// L599
      float v474 = v471 + v473;	// L600
      float v475 = th2_10;	// L601
      float v476 = v475 / 3628800.000000;	// L603
      float v477 = v474 - v476;	// L604
      float cos2;	// L605
      cos2 = v477;	// L606
      float v479 = theta2;	// L607
      float v480 = th2_3;	// L608
      float v481 = v480 / 6.000000;	// L610
      float v482 = v479 - v481;	// L611
      float v483 = th2_5;	// L612
      float v484 = v483 / 120.000000;	// L614
      float v485 = v482 + v484;	// L615
      float v486 = th2_7;	// L616
      float v487 = v486 / 5040.000000;	// L618
      float v488 = v485 - v487;	// L619
      float v489 = th2_9;	// L620
      float v490 = v489 / 362880.000000;	// L622
      float v491 = v488 + v490;	// L623
      float v492 = th2_11;	// L624
      float v493 = v492 / 39916800.000000;	// L626
      float v494 = v491 - v493;	// L627
      float sin2;	// L628
      sin2 = v494;	// L629
      float v496 = cos2;	// L630
      float Wr2;	// L631
      Wr2 = v496;	// L632
      float v498 = sin2;	// L633
      float Wi2;	// L634
      Wi2 = v498;	// L635
      float v500 = Wr2;	// L636
      float v501 = v500 * v500;	// L637
      float v502 = Wi2;	// L638
      float v503 = v502 * v502;	// L639
      float v504 = v501 - v503;	// L640
      float W2r2;	// L641
      W2r2 = v504;	// L642
      float v506 = Wr2;	// L643
      float v507 = v506  << 1.000000;	// L644
      float v508 = Wi2;	// L645
      float v509 = v507 * v508;	// L646
      float W2i2;	// L647
      W2i2 = v509;	// L648
      float v511 = W2r2;	// L649
      float v512 = Wr2;	// L650
      float v513 = v511 * v512;	// L651
      float v514 = W2i2;	// L652
      float v515 = Wi2;	// L653
      float v516 = v514 * v515;	// L654
      float v517 = v513 - v516;	// L655
      float W3r2;	// L656
      W3r2 = v517;	// L657
      float v519 = W2r2;	// L658
      float v520 = Wi2;	// L659
      float v521 = v519 * v520;	// L660
      float v522 = W2i2;	// L661
      float v523 = Wr2;	// L662
      float v524 = v522 * v523;	// L663
      float v525 = v521 + v524;	// L664
      float W3i2;	// L665
      W3i2 = v525;	// L666
      int v527 = g2;	// L667
      int v528 = v527 * 16;	// L670
      int v529 = v528;	// L671
      int v530 = j2;	// L672
      int v531 = v529 + v530;	// L673
      int v532 = v531;	// L674
      int base2;	// L675
      base2 = v532;	// L676
      int v534 = base2;	// L677
      int idx1_2;	// L678
      idx1_2 = v534;	// L679
      int v536 = base2;	// L680
      int v537 = v536;	// L681
      int v538 = v537 + 4;	// L684
      int v539 = v538;	// L685
      int idx2_2;	// L686
      idx2_2 = v539;	// L687
      int v541 = base2;	// L688
      int v542 = v541;	// L689
      int v543 = v542 + 8;	// L692
      int v544 = v543;	// L693
      int idx3_2;	// L694
      idx3_2 = v544;	// L695
      int v546 = base2;	// L696
      int v547 = v546;	// L697
      int v548 = v547 + 12;	// L700
      int v549 = v548;	// L701
      int idx4_2;	// L702
      idx4_2 = v549;	// L703
      int v551 = idx1_2;	// L704
      int v552 = v551;	// L705
      float v553 = buf_real[v552];	// L706
      float a0r2;	// L707
      a0r2 = v553;	// L708
      int v555 = idx1_2;	// L709
      int v556 = v555;	// L710
      float v557 = buf_imag[v556];	// L711
      float a0i2;	// L712
      a0i2 = v557;	// L713
      int v559 = idx2_2;	// L714
      int v560 = v559;	// L715
      float v561 = buf_real[v560];	// L716
      float a1r02;	// L717
      a1r02 = v561;	// L718
      int v563 = idx2_2;	// L719
      int v564 = v563;	// L720
      float v565 = buf_imag[v564];	// L721
      float a1i02;	// L722
      a1i02 = v565;	// L723
      int v567 = idx3_2;	// L724
      int v568 = v567;	// L725
      float v569 = buf_real[v568];	// L726
      float a2r02;	// L727
      a2r02 = v569;	// L728
      int v571 = idx3_2;	// L729
      int v572 = v571;	// L730
      float v573 = buf_imag[v572];	// L731
      float a2i02;	// L732
      a2i02 = v573;	// L733
      int v575 = idx4_2;	// L734
      int v576 = v575;	// L735
      float v577 = buf_real[v576];	// L736
      float a3r02;	// L737
      a3r02 = v577;	// L738
      int v579 = idx4_2;	// L739
      int v580 = v579;	// L740
      float v581 = buf_imag[v580];	// L741
      float a3i02;	// L742
      a3i02 = v581;	// L743
      float v583 = a1r02;	// L744
      float v584 = Wr2;	// L745
      float v585 = v583 * v584;	// L746
      float v586 = a1i02;	// L747
      float v587 = Wi2;	// L748
      float v588 = v586 * v587;	// L749
      float v589 = v585 - v588;	// L750
      float a1r2;	// L751
      a1r2 = v589;	// L752
      float v591 = a1r02;	// L753
      float v592 = Wi2;	// L754
      float v593 = v591 * v592;	// L755
      float v594 = a1i02;	// L756
      float v595 = Wr2;	// L757
      float v596 = v594 * v595;	// L758
      float v597 = v593 + v596;	// L759
      float a1i2;	// L760
      a1i2 = v597;	// L761
      float v599 = a2r02;	// L762
      float v600 = W2r2;	// L763
      float v601 = v599 * v600;	// L764
      float v602 = a2i02;	// L765
      float v603 = W2i2;	// L766
      float v604 = v602 * v603;	// L767
      float v605 = v601 - v604;	// L768
      float a2r2;	// L769
      a2r2 = v605;	// L770
      float v607 = a2r02;	// L771
      float v608 = W2i2;	// L772
      float v609 = v607 * v608;	// L773
      float v610 = a2i02;	// L774
      float v611 = W2r2;	// L775
      float v612 = v610 * v611;	// L776
      float v613 = v609 + v612;	// L777
      float a2i2;	// L778
      a2i2 = v613;	// L779
      float v615 = a3r02;	// L780
      float v616 = W3r2;	// L781
      float v617 = v615 * v616;	// L782
      float v618 = a3i02;	// L783
      float v619 = W3i2;	// L784
      float v620 = v618 * v619;	// L785
      float v621 = v617 - v620;	// L786
      float a3r2;	// L787
      a3r2 = v621;	// L788
      float v623 = a3r02;	// L789
      float v624 = W3i2;	// L790
      float v625 = v623 * v624;	// L791
      float v626 = a3i02;	// L792
      float v627 = W3r2;	// L793
      float v628 = v626 * v627;	// L794
      float v629 = v625 + v628;	// L795
      float a3i2;	// L796
      a3i2 = v629;	// L797
      float v631 = a0r2;	// L798
      float v632 = a1r2;	// L799
      float v633 = v631 + v632;	// L800
      float v634 = a2r2;	// L801
      float v635 = v633 + v634;	// L802
      float v636 = a3r2;	// L803
      float v637 = v635 + v636;	// L804
      float b0r2;	// L805
      b0r2 = v637;	// L806
      float v639 = a0i2;	// L807
      float v640 = a1i2;	// L808
      float v641 = v639 + v640;	// L809
      float v642 = a2i2;	// L810
      float v643 = v641 + v642;	// L811
      float v644 = a3i2;	// L812
      float v645 = v643 + v644;	// L813
      float b0i2;	// L814
      b0i2 = v645;	// L815
      float v647 = a0r2;	// L816
      float v648 = a1i2;	// L817
      float v649 = v647 + v648;	// L818
      float v650 = a2r2;	// L819
      float v651 = v649 - v650;	// L820
      float v652 = a3i2;	// L821
      float v653 = v651 - v652;	// L822
      float b1r2;	// L823
      b1r2 = v653;	// L824
      float v655 = a0i2;	// L825
      float v656 = a1r2;	// L826
      float v657 = v655 - v656;	// L827
      float v658 = a2i2;	// L828
      float v659 = v657 - v658;	// L829
      float v660 = a3r2;	// L830
      float v661 = v659 + v660;	// L831
      float b1i2;	// L832
      b1i2 = v661;	// L833
      float v663 = a0r2;	// L834
      float v664 = a1r2;	// L835
      float v665 = v663 - v664;	// L836
      float v666 = a2r2;	// L837
      float v667 = v665 + v666;	// L838
      float v668 = a3r2;	// L839
      float v669 = v667 - v668;	// L840
      float b2r2;	// L841
      b2r2 = v669;	// L842
      float v671 = a0i2;	// L843
      float v672 = a1i2;	// L844
      float v673 = v671 - v672;	// L845
      float v674 = a2i2;	// L846
      float v675 = v673 + v674;	// L847
      float v676 = a3i2;	// L848
      float v677 = v675 - v676;	// L849
      float b2i2;	// L850
      b2i2 = v677;	// L851
      float v679 = a0r2;	// L852
      float v680 = a1i2;	// L853
      float v681 = v679 - v680;	// L854
      float v682 = a2r2;	// L855
      float v683 = v681 - v682;	// L856
      float v684 = a3i2;	// L857
      float v685 = v683 + v684;	// L858
      float b3r2;	// L859
      b3r2 = v685;	// L860
      float v687 = a0i2;	// L861
      float v688 = a1r2;	// L862
      float v689 = v687 + v688;	// L863
      float v690 = a2i2;	// L864
      float v691 = v689 - v690;	// L865
      float v692 = a3r2;	// L866
      float v693 = v691 - v692;	// L867
      float b3i2;	// L868
      b3i2 = v693;	// L869
      float v695 = b0r2;	// L870
      int v696 = idx1_2;	// L871
      int v697 = v696;	// L872
      buf_real[v697] = v695;	// L873
      float v698 = b0i2;	// L874
      int v699 = idx1_2;	// L875
      int v700 = v699;	// L876
      buf_imag[v700] = v698;	// L877
      float v701 = b1r2;	// L878
      int v702 = idx2_2;	// L879
      int v703 = v702;	// L880
      buf_real[v703] = v701;	// L881
      float v704 = b1i2;	// L882
      int v705 = idx2_2;	// L883
      int v706 = v705;	// L884
      buf_imag[v706] = v704;	// L885
      float v707 = b2r2;	// L886
      int v708 = idx3_2;	// L887
      int v709 = v708;	// L888
      buf_real[v709] = v707;	// L889
      float v710 = b2i2;	// L890
      int v711 = idx3_2;	// L891
      int v712 = v711;	// L892
      buf_imag[v712] = v710;	// L893
      float v713 = b3r2;	// L894
      int v714 = idx4_2;	// L895
      int v715 = v714;	// L896
      buf_real[v715] = v713;	// L897
      float v716 = b3i2;	// L898
      int v717 = idx4_2;	// L899
      int v718 = v717;	// L900
      buf_imag[v718] = v716;	// L901
    }
  }
  l_S_g3_5_g3: for (int g3 = 0; g3 < 16; g3++) {	// L904
  #pragma HLS pipeline II=3
    l_S_j3_5_j3: for (int j3 = 0; j3 < 16; j3++) {	// L905
      int v721 = j3;	// L906
      float v722 = v721;	// L907
      float j3_f;	// L908
      j3_f = v722;	// L909
      float v724 = PI;	// L912
      float v725 = v724 * -2.000000;	// L913
      float v726 = j3_f;	// L914
      float v727 = v725 * v726;	// L915
      float v728 = v727 / 64.000000;	// L917
      float theta3;	// L918
      theta3 = v728;	// L919
      float v730 = theta3;	// L920
      float v731 = v730 * v730;	// L921
      float th3_2;	// L922
      th3_2 = v731;	// L923
      float v733 = th3_2;	// L924
      float v734 = theta3;	// L925
      float v735 = v733 * v734;	// L926
      float th3_3;	// L927
      th3_3 = v735;	// L928
      float v737 = th3_2;	// L929
      float v738 = v737 * v737;	// L930
      float th3_4;	// L931
      th3_4 = v738;	// L932
      float v740 = th3_4;	// L933
      float v741 = theta3;	// L934
      float v742 = v740 * v741;	// L935
      float th3_5;	// L936
      th3_5 = v742;	// L937
      float v744 = th3_4;	// L938
      float v745 = th3_2;	// L939
      float v746 = v744 * v745;	// L940
      float th3_6;	// L941
      th3_6 = v746;	// L942
      float v748 = th3_6;	// L943
      float v749 = theta3;	// L944
      float v750 = v748 * v749;	// L945
      float th3_7;	// L946
      th3_7 = v750;	// L947
      float v752 = th3_4;	// L948
      float v753 = v752 * v752;	// L949
      float th3_8;	// L950
      th3_8 = v753;	// L951
      float v755 = th3_8;	// L952
      float v756 = theta3;	// L953
      float v757 = v755 * v756;	// L954
      float th3_9;	// L955
      th3_9 = v757;	// L956
      float v759 = th3_8;	// L957
      float v760 = th3_2;	// L958
      float v761 = v759 * v760;	// L959
      float th3_10;	// L960
      th3_10 = v761;	// L961
      float v763 = th3_10;	// L962
      float v764 = theta3;	// L963
      float v765 = v763 * v764;	// L964
      float th3_11;	// L965
      th3_11 = v765;	// L966
      float v767 = th3_2;	// L967
      float v768 = v767 / 2.000000;	// L968
      float v769 = 1.000000 - v768;	// L970
      float v770 = th3_4;	// L971
      float v771 = v770 / 24.000000;	// L973
      float v772 = v769 + v771;	// L974
      float v773 = th3_6;	// L975
      float v774 = v773 / 720.000000;	// L977
      float v775 = v772 - v774;	// L978
      float v776 = th3_8;	// L979
      float v777 = v776 / 40320.000000;	// L981
      float v778 = v775 + v777;	// L982
      float v779 = th3_10;	// L983
      float v780 = v779 / 3628800.000000;	// L985
      float v781 = v778 - v780;	// L986
      float cos3;	// L987
      cos3 = v781;	// L988
      float v783 = theta3;	// L989
      float v784 = th3_3;	// L990
      float v785 = v784 / 6.000000;	// L992
      float v786 = v783 - v785;	// L993
      float v787 = th3_5;	// L994
      float v788 = v787 / 120.000000;	// L996
      float v789 = v786 + v788;	// L997
      float v790 = th3_7;	// L998
      float v791 = v790 / 5040.000000;	// L1000
      float v792 = v789 - v791;	// L1001
      float v793 = th3_9;	// L1002
      float v794 = v793 / 362880.000000;	// L1004
      float v795 = v792 + v794;	// L1005
      float v796 = th3_11;	// L1006
      float v797 = v796 / 39916800.000000;	// L1008
      float v798 = v795 - v797;	// L1009
      float sin3;	// L1010
      sin3 = v798;	// L1011
      float v800 = cos3;	// L1012
      float Wr3;	// L1013
      Wr3 = v800;	// L1014
      float v802 = sin3;	// L1015
      float Wi3;	// L1016
      Wi3 = v802;	// L1017
      float v804 = Wr3;	// L1018
      float v805 = v804 * v804;	// L1019
      float v806 = Wi3;	// L1020
      float v807 = v806 * v806;	// L1021
      float v808 = v805 - v807;	// L1022
      float W2r3;	// L1023
      W2r3 = v808;	// L1024
      float v810 = Wr3;	// L1025
      float v811 = v810  << 1.000000;	// L1026
      float v812 = Wi3;	// L1027
      float v813 = v811 * v812;	// L1028
      float W2i3;	// L1029
      W2i3 = v813;	// L1030
      float v815 = W2r3;	// L1031
      float v816 = Wr3;	// L1032
      float v817 = v815 * v816;	// L1033
      float v818 = W2i3;	// L1034
      float v819 = Wi3;	// L1035
      float v820 = v818 * v819;	// L1036
      float v821 = v817 - v820;	// L1037
      float W3r3;	// L1038
      W3r3 = v821;	// L1039
      float v823 = W2r3;	// L1040
      float v824 = Wi3;	// L1041
      float v825 = v823 * v824;	// L1042
      float v826 = W2i3;	// L1043
      float v827 = Wr3;	// L1044
      float v828 = v826 * v827;	// L1045
      float v829 = v825 + v828;	// L1046
      float W3i3;	// L1047
      W3i3 = v829;	// L1048
      int v831 = g3;	// L1049
      int v832 = v831 * 64;	// L1052
      int v833 = v832;	// L1053
      int v834 = j3;	// L1054
      int v835 = v833 + v834;	// L1055
      int v836 = v835;	// L1056
      int base3;	// L1057
      base3 = v836;	// L1058
      int v838 = base3;	// L1059
      int idx1_3;	// L1060
      idx1_3 = v838;	// L1061
      int v840 = base3;	// L1062
      int v841 = v840;	// L1063
      int v842 = v841 + 16;	// L1066
      int v843 = v842;	// L1067
      int idx2_3;	// L1068
      idx2_3 = v843;	// L1069
      int v845 = base3;	// L1070
      int v846 = v845;	// L1071
      int v847 = v846 + 32;	// L1074
      int v848 = v847;	// L1075
      int idx3_3;	// L1076
      idx3_3 = v848;	// L1077
      int v850 = base3;	// L1078
      int v851 = v850;	// L1079
      int v852 = v851 + 48;	// L1082
      int v853 = v852;	// L1083
      int idx4_3;	// L1084
      idx4_3 = v853;	// L1085
      int v855 = idx1_3;	// L1086
      int v856 = v855;	// L1087
      float v857 = buf_real[v856];	// L1088
      float a0r3;	// L1089
      a0r3 = v857;	// L1090
      int v859 = idx1_3;	// L1091
      int v860 = v859;	// L1092
      float v861 = buf_imag[v860];	// L1093
      float a0i3;	// L1094
      a0i3 = v861;	// L1095
      int v863 = idx2_3;	// L1096
      int v864 = v863;	// L1097
      float v865 = buf_real[v864];	// L1098
      float a1r03;	// L1099
      a1r03 = v865;	// L1100
      int v867 = idx2_3;	// L1101
      int v868 = v867;	// L1102
      float v869 = buf_imag[v868];	// L1103
      float a1i03;	// L1104
      a1i03 = v869;	// L1105
      int v871 = idx3_3;	// L1106
      int v872 = v871;	// L1107
      float v873 = buf_real[v872];	// L1108
      float a2r03;	// L1109
      a2r03 = v873;	// L1110
      int v875 = idx3_3;	// L1111
      int v876 = v875;	// L1112
      float v877 = buf_imag[v876];	// L1113
      float a2i03;	// L1114
      a2i03 = v877;	// L1115
      int v879 = idx4_3;	// L1116
      int v880 = v879;	// L1117
      float v881 = buf_real[v880];	// L1118
      float a3r03;	// L1119
      a3r03 = v881;	// L1120
      int v883 = idx4_3;	// L1121
      int v884 = v883;	// L1122
      float v885 = buf_imag[v884];	// L1123
      float a3i03;	// L1124
      a3i03 = v885;	// L1125
      float v887 = a1r03;	// L1126
      float v888 = Wr3;	// L1127
      float v889 = v887 * v888;	// L1128
      float v890 = a1i03;	// L1129
      float v891 = Wi3;	// L1130
      float v892 = v890 * v891;	// L1131
      float v893 = v889 - v892;	// L1132
      float a1r3;	// L1133
      a1r3 = v893;	// L1134
      float v895 = a1r03;	// L1135
      float v896 = Wi3;	// L1136
      float v897 = v895 * v896;	// L1137
      float v898 = a1i03;	// L1138
      float v899 = Wr3;	// L1139
      float v900 = v898 * v899;	// L1140
      float v901 = v897 + v900;	// L1141
      float a1i3;	// L1142
      a1i3 = v901;	// L1143
      float v903 = a2r03;	// L1144
      float v904 = W2r3;	// L1145
      float v905 = v903 * v904;	// L1146
      float v906 = a2i03;	// L1147
      float v907 = W2i3;	// L1148
      float v908 = v906 * v907;	// L1149
      float v909 = v905 - v908;	// L1150
      float a2r3;	// L1151
      a2r3 = v909;	// L1152
      float v911 = a2r03;	// L1153
      float v912 = W2i3;	// L1154
      float v913 = v911 * v912;	// L1155
      float v914 = a2i03;	// L1156
      float v915 = W2r3;	// L1157
      float v916 = v914 * v915;	// L1158
      float v917 = v913 + v916;	// L1159
      float a2i3;	// L1160
      a2i3 = v917;	// L1161
      float v919 = a3r03;	// L1162
      float v920 = W3r3;	// L1163
      float v921 = v919 * v920;	// L1164
      float v922 = a3i03;	// L1165
      float v923 = W3i3;	// L1166
      float v924 = v922 * v923;	// L1167
      float v925 = v921 - v924;	// L1168
      float a3r3;	// L1169
      a3r3 = v925;	// L1170
      float v927 = a3r03;	// L1171
      float v928 = W3i3;	// L1172
      float v929 = v927 * v928;	// L1173
      float v930 = a3i03;	// L1174
      float v931 = W3r3;	// L1175
      float v932 = v930 * v931;	// L1176
      float v933 = v929 + v932;	// L1177
      float a3i3;	// L1178
      a3i3 = v933;	// L1179
      float v935 = a0r3;	// L1180
      float v936 = a1r3;	// L1181
      float v937 = v935 + v936;	// L1182
      float v938 = a2r3;	// L1183
      float v939 = v937 + v938;	// L1184
      float v940 = a3r3;	// L1185
      float v941 = v939 + v940;	// L1186
      float b0r3;	// L1187
      b0r3 = v941;	// L1188
      float v943 = a0i3;	// L1189
      float v944 = a1i3;	// L1190
      float v945 = v943 + v944;	// L1191
      float v946 = a2i3;	// L1192
      float v947 = v945 + v946;	// L1193
      float v948 = a3i3;	// L1194
      float v949 = v947 + v948;	// L1195
      float b0i3;	// L1196
      b0i3 = v949;	// L1197
      float v951 = a0r3;	// L1198
      float v952 = a1i3;	// L1199
      float v953 = v951 + v952;	// L1200
      float v954 = a2r3;	// L1201
      float v955 = v953 - v954;	// L1202
      float v956 = a3i3;	// L1203
      float v957 = v955 - v956;	// L1204
      float b1r3;	// L1205
      b1r3 = v957;	// L1206
      float v959 = a0i3;	// L1207
      float v960 = a1r3;	// L1208
      float v961 = v959 - v960;	// L1209
      float v962 = a2i3;	// L1210
      float v963 = v961 - v962;	// L1211
      float v964 = a3r3;	// L1212
      float v965 = v963 + v964;	// L1213
      float b1i3;	// L1214
      b1i3 = v965;	// L1215
      float v967 = a0r3;	// L1216
      float v968 = a1r3;	// L1217
      float v969 = v967 - v968;	// L1218
      float v970 = a2r3;	// L1219
      float v971 = v969 + v970;	// L1220
      float v972 = a3r3;	// L1221
      float v973 = v971 - v972;	// L1222
      float b2r3;	// L1223
      b2r3 = v973;	// L1224
      float v975 = a0i3;	// L1225
      float v976 = a1i3;	// L1226
      float v977 = v975 - v976;	// L1227
      float v978 = a2i3;	// L1228
      float v979 = v977 + v978;	// L1229
      float v980 = a3i3;	// L1230
      float v981 = v979 - v980;	// L1231
      float b2i3;	// L1232
      b2i3 = v981;	// L1233
      float v983 = a0r3;	// L1234
      float v984 = a1i3;	// L1235
      float v985 = v983 - v984;	// L1236
      float v986 = a2r3;	// L1237
      float v987 = v985 - v986;	// L1238
      float v988 = a3i3;	// L1239
      float v989 = v987 + v988;	// L1240
      float b3r3;	// L1241
      b3r3 = v989;	// L1242
      float v991 = a0i3;	// L1243
      float v992 = a1r3;	// L1244
      float v993 = v991 + v992;	// L1245
      float v994 = a2i3;	// L1246
      float v995 = v993 - v994;	// L1247
      float v996 = a3r3;	// L1248
      float v997 = v995 - v996;	// L1249
      float b3i3;	// L1250
      b3i3 = v997;	// L1251
      float v999 = b0r3;	// L1252
      int v1000 = idx1_3;	// L1253
      int v1001 = v1000;	// L1254
      buf_real[v1001] = v999;	// L1255
      float v1002 = b0i3;	// L1256
      int v1003 = idx1_3;	// L1257
      int v1004 = v1003;	// L1258
      buf_imag[v1004] = v1002;	// L1259
      float v1005 = b1r3;	// L1260
      int v1006 = idx2_3;	// L1261
      int v1007 = v1006;	// L1262
      buf_real[v1007] = v1005;	// L1263
      float v1008 = b1i3;	// L1264
      int v1009 = idx2_3;	// L1265
      int v1010 = v1009;	// L1266
      buf_imag[v1010] = v1008;	// L1267
      float v1011 = b2r3;	// L1268
      int v1012 = idx3_3;	// L1269
      int v1013 = v1012;	// L1270
      buf_real[v1013] = v1011;	// L1271
      float v1014 = b2i3;	// L1272
      int v1015 = idx3_3;	// L1273
      int v1016 = v1015;	// L1274
      buf_imag[v1016] = v1014;	// L1275
      float v1017 = b3r3;	// L1276
      int v1018 = idx4_3;	// L1277
      int v1019 = v1018;	// L1278
      buf_real[v1019] = v1017;	// L1279
      float v1020 = b3i3;	// L1280
      int v1021 = idx4_3;	// L1281
      int v1022 = v1021;	// L1282
      buf_imag[v1022] = v1020;	// L1283
    }
  }
  l_S_g4_7_g4: for (int g4 = 0; g4 < 4; g4++) {	// L1286
    l_S_j4_7_j4: for (int j4 = 0; j4 < 64; j4++) {	// L1287
    #pragma HLS pipeline II=3
      int v1025 = j4;	// L1288
      float v1026 = v1025;	// L1289
      float j4_f;	// L1290
      j4_f = v1026;	// L1291
      float v1028 = PI;	// L1294
      float v1029 = v1028 * -2.000000;	// L1295
      float v1030 = j4_f;	// L1296
      float v1031 = v1029 * v1030;	// L1297
      float v1032 = v1031 / 256.000000;	// L1299
      float theta4;	// L1300
      theta4 = v1032;	// L1301
      float v1034 = theta4;	// L1302
      float v1035 = v1034 * v1034;	// L1303
      float th4_2;	// L1304
      th4_2 = v1035;	// L1305
      float v1037 = th4_2;	// L1306
      float v1038 = theta4;	// L1307
      float v1039 = v1037 * v1038;	// L1308
      float th4_3;	// L1309
      th4_3 = v1039;	// L1310
      float v1041 = th4_2;	// L1311
      float v1042 = v1041 * v1041;	// L1312
      float th4_4;	// L1313
      th4_4 = v1042;	// L1314
      float v1044 = th4_4;	// L1315
      float v1045 = theta4;	// L1316
      float v1046 = v1044 * v1045;	// L1317
      float th4_5;	// L1318
      th4_5 = v1046;	// L1319
      float v1048 = th4_4;	// L1320
      float v1049 = th4_2;	// L1321
      float v1050 = v1048 * v1049;	// L1322
      float th4_6;	// L1323
      th4_6 = v1050;	// L1324
      float v1052 = th4_6;	// L1325
      float v1053 = theta4;	// L1326
      float v1054 = v1052 * v1053;	// L1327
      float th4_7;	// L1328
      th4_7 = v1054;	// L1329
      float v1056 = th4_4;	// L1330
      float v1057 = v1056 * v1056;	// L1331
      float th4_8;	// L1332
      th4_8 = v1057;	// L1333
      float v1059 = th4_8;	// L1334
      float v1060 = theta4;	// L1335
      float v1061 = v1059 * v1060;	// L1336
      float th4_9;	// L1337
      th4_9 = v1061;	// L1338
      float v1063 = th4_8;	// L1339
      float v1064 = th4_2;	// L1340
      float v1065 = v1063 * v1064;	// L1341
      float th4_10;	// L1342
      th4_10 = v1065;	// L1343
      float v1067 = th4_10;	// L1344
      float v1068 = theta4;	// L1345
      float v1069 = v1067 * v1068;	// L1346
      float th4_11;	// L1347
      th4_11 = v1069;	// L1348
      float v1071 = th4_2;	// L1349
      float v1072 = v1071 / 2.000000;	// L1350
      float v1073 = 1.000000 - v1072;	// L1352
      float v1074 = th4_4;	// L1353
      float v1075 = v1074 / 24.000000;	// L1355
      float v1076 = v1073 + v1075;	// L1356
      float v1077 = th4_6;	// L1357
      float v1078 = v1077 / 720.000000;	// L1359
      float v1079 = v1076 - v1078;	// L1360
      float v1080 = th4_8;	// L1361
      float v1081 = v1080 / 40320.000000;	// L1363
      float v1082 = v1079 + v1081;	// L1364
      float v1083 = th4_10;	// L1365
      float v1084 = v1083 / 3628800.000000;	// L1367
      float v1085 = v1082 - v1084;	// L1368
      float cos4;	// L1369
      cos4 = v1085;	// L1370
      float v1087 = theta4;	// L1371
      float v1088 = th4_3;	// L1372
      float v1089 = v1088 / 6.000000;	// L1374
      float v1090 = v1087 - v1089;	// L1375
      float v1091 = th4_5;	// L1376
      float v1092 = v1091 / 120.000000;	// L1378
      float v1093 = v1090 + v1092;	// L1379
      float v1094 = th4_7;	// L1380
      float v1095 = v1094 / 5040.000000;	// L1382
      float v1096 = v1093 - v1095;	// L1383
      float v1097 = th4_9;	// L1384
      float v1098 = v1097 / 362880.000000;	// L1386
      float v1099 = v1096 + v1098;	// L1387
      float v1100 = th4_11;	// L1388
      float v1101 = v1100 / 39916800.000000;	// L1390
      float v1102 = v1099 - v1101;	// L1391
      float sin4;	// L1392
      sin4 = v1102;	// L1393
      float v1104 = cos4;	// L1394
      float Wr4;	// L1395
      Wr4 = v1104;	// L1396
      float v1106 = sin4;	// L1397
      float Wi4;	// L1398
      Wi4 = v1106;	// L1399
      float v1108 = Wr4;	// L1400
      float v1109 = v1108 * v1108;	// L1401
      float v1110 = Wi4;	// L1402
      float v1111 = v1110 * v1110;	// L1403
      float v1112 = v1109 - v1111;	// L1404
      float W2r4;	// L1405
      W2r4 = v1112;	// L1406
      float v1114 = Wr4;	// L1407
      float v1115 = v1114  << 1.000000;	// L1408
      float v1116 = Wi4;	// L1409
      float v1117 = v1115 * v1116;	// L1410
      float W2i4;	// L1411
      W2i4 = v1117;	// L1412
      float v1119 = W2r4;	// L1413
      float v1120 = Wr4;	// L1414
      float v1121 = v1119 * v1120;	// L1415
      float v1122 = W2i4;	// L1416
      float v1123 = Wi4;	// L1417
      float v1124 = v1122 * v1123;	// L1418
      float v1125 = v1121 - v1124;	// L1419
      float W3r4;	// L1420
      W3r4 = v1125;	// L1421
      float v1127 = W2r4;	// L1422
      float v1128 = Wi4;	// L1423
      float v1129 = v1127 * v1128;	// L1424
      float v1130 = W2i4;	// L1425
      float v1131 = Wr4;	// L1426
      float v1132 = v1130 * v1131;	// L1427
      float v1133 = v1129 + v1132;	// L1428
      float W3i4;	// L1429
      W3i4 = v1133;	// L1430
      int v1135 = g4;	// L1431
      int v1136 = v1135 * 256;	// L1434
      int v1137 = v1136;	// L1435
      int v1138 = j4;	// L1436
      int v1139 = v1137 + v1138;	// L1437
      int v1140 = v1139;	// L1438
      int base4;	// L1439
      base4 = v1140;	// L1440
      int v1142 = base4;	// L1441
      int idx1_4;	// L1442
      idx1_4 = v1142;	// L1443
      int v1144 = base4;	// L1444
      int v1145 = v1144;	// L1445
      int v1146 = v1145 + 64;	// L1448
      int v1147 = v1146;	// L1449
      int idx2_4;	// L1450
      idx2_4 = v1147;	// L1451
      int v1149 = base4;	// L1452
      int v1150 = v1149;	// L1453
      int v1151 = v1150 + 128;	// L1456
      int v1152 = v1151;	// L1457
      int idx3_4;	// L1458
      idx3_4 = v1152;	// L1459
      int v1154 = base4;	// L1460
      int v1155 = v1154;	// L1461
      int v1156 = v1155 + 192;	// L1464
      int v1157 = v1156;	// L1465
      int idx4_4;	// L1466
      idx4_4 = v1157;	// L1467
      int v1159 = idx1_4;	// L1468
      int v1160 = v1159;	// L1469
      float v1161 = buf_real[v1160];	// L1470
      float a0r4;	// L1471
      a0r4 = v1161;	// L1472
      int v1163 = idx1_4;	// L1473
      int v1164 = v1163;	// L1474
      float v1165 = buf_imag[v1164];	// L1475
      float a0i4;	// L1476
      a0i4 = v1165;	// L1477
      int v1167 = idx2_4;	// L1478
      int v1168 = v1167;	// L1479
      float v1169 = buf_real[v1168];	// L1480
      float a1r04;	// L1481
      a1r04 = v1169;	// L1482
      int v1171 = idx2_4;	// L1483
      int v1172 = v1171;	// L1484
      float v1173 = buf_imag[v1172];	// L1485
      float a1i04;	// L1486
      a1i04 = v1173;	// L1487
      int v1175 = idx3_4;	// L1488
      int v1176 = v1175;	// L1489
      float v1177 = buf_real[v1176];	// L1490
      float a2r04;	// L1491
      a2r04 = v1177;	// L1492
      int v1179 = idx3_4;	// L1493
      int v1180 = v1179;	// L1494
      float v1181 = buf_imag[v1180];	// L1495
      float a2i04;	// L1496
      a2i04 = v1181;	// L1497
      int v1183 = idx4_4;	// L1498
      int v1184 = v1183;	// L1499
      float v1185 = buf_real[v1184];	// L1500
      float a3r04;	// L1501
      a3r04 = v1185;	// L1502
      int v1187 = idx4_4;	// L1503
      int v1188 = v1187;	// L1504
      float v1189 = buf_imag[v1188];	// L1505
      float a3i04;	// L1506
      a3i04 = v1189;	// L1507
      float v1191 = a1r04;	// L1508
      float v1192 = Wr4;	// L1509
      float v1193 = v1191 * v1192;	// L1510
      float v1194 = a1i04;	// L1511
      float v1195 = Wi4;	// L1512
      float v1196 = v1194 * v1195;	// L1513
      float v1197 = v1193 - v1196;	// L1514
      float a1r4;	// L1515
      a1r4 = v1197;	// L1516
      float v1199 = a1r04;	// L1517
      float v1200 = Wi4;	// L1518
      float v1201 = v1199 * v1200;	// L1519
      float v1202 = a1i04;	// L1520
      float v1203 = Wr4;	// L1521
      float v1204 = v1202 * v1203;	// L1522
      float v1205 = v1201 + v1204;	// L1523
      float a1i4;	// L1524
      a1i4 = v1205;	// L1525
      float v1207 = a2r04;	// L1526
      float v1208 = W2r4;	// L1527
      float v1209 = v1207 * v1208;	// L1528
      float v1210 = a2i04;	// L1529
      float v1211 = W2i4;	// L1530
      float v1212 = v1210 * v1211;	// L1531
      float v1213 = v1209 - v1212;	// L1532
      float a2r4;	// L1533
      a2r4 = v1213;	// L1534
      float v1215 = a2r04;	// L1535
      float v1216 = W2i4;	// L1536
      float v1217 = v1215 * v1216;	// L1537
      float v1218 = a2i04;	// L1538
      float v1219 = W2r4;	// L1539
      float v1220 = v1218 * v1219;	// L1540
      float v1221 = v1217 + v1220;	// L1541
      float a2i4;	// L1542
      a2i4 = v1221;	// L1543
      float v1223 = a3r04;	// L1544
      float v1224 = W3r4;	// L1545
      float v1225 = v1223 * v1224;	// L1546
      float v1226 = a3i04;	// L1547
      float v1227 = W3i4;	// L1548
      float v1228 = v1226 * v1227;	// L1549
      float v1229 = v1225 - v1228;	// L1550
      float a3r4;	// L1551
      a3r4 = v1229;	// L1552
      float v1231 = a3r04;	// L1553
      float v1232 = W3i4;	// L1554
      float v1233 = v1231 * v1232;	// L1555
      float v1234 = a3i04;	// L1556
      float v1235 = W3r4;	// L1557
      float v1236 = v1234 * v1235;	// L1558
      float v1237 = v1233 + v1236;	// L1559
      float a3i4;	// L1560
      a3i4 = v1237;	// L1561
      float v1239 = a0r4;	// L1562
      float v1240 = a1r4;	// L1563
      float v1241 = v1239 + v1240;	// L1564
      float v1242 = a2r4;	// L1565
      float v1243 = v1241 + v1242;	// L1566
      float v1244 = a3r4;	// L1567
      float v1245 = v1243 + v1244;	// L1568
      float b0r4;	// L1569
      b0r4 = v1245;	// L1570
      float v1247 = a0i4;	// L1571
      float v1248 = a1i4;	// L1572
      float v1249 = v1247 + v1248;	// L1573
      float v1250 = a2i4;	// L1574
      float v1251 = v1249 + v1250;	// L1575
      float v1252 = a3i4;	// L1576
      float v1253 = v1251 + v1252;	// L1577
      float b0i4;	// L1578
      b0i4 = v1253;	// L1579
      float v1255 = a0r4;	// L1580
      float v1256 = a1i4;	// L1581
      float v1257 = v1255 + v1256;	// L1582
      float v1258 = a2r4;	// L1583
      float v1259 = v1257 - v1258;	// L1584
      float v1260 = a3i4;	// L1585
      float v1261 = v1259 - v1260;	// L1586
      float b1r4;	// L1587
      b1r4 = v1261;	// L1588
      float v1263 = a0i4;	// L1589
      float v1264 = a1r4;	// L1590
      float v1265 = v1263 - v1264;	// L1591
      float v1266 = a2i4;	// L1592
      float v1267 = v1265 - v1266;	// L1593
      float v1268 = a3r4;	// L1594
      float v1269 = v1267 + v1268;	// L1595
      float b1i4;	// L1596
      b1i4 = v1269;	// L1597
      float v1271 = a0r4;	// L1598
      float v1272 = a1r4;	// L1599
      float v1273 = v1271 - v1272;	// L1600
      float v1274 = a2r4;	// L1601
      float v1275 = v1273 + v1274;	// L1602
      float v1276 = a3r4;	// L1603
      float v1277 = v1275 - v1276;	// L1604
      float b2r4;	// L1605
      b2r4 = v1277;	// L1606
      float v1279 = a0i4;	// L1607
      float v1280 = a1i4;	// L1608
      float v1281 = v1279 - v1280;	// L1609
      float v1282 = a2i4;	// L1610
      float v1283 = v1281 + v1282;	// L1611
      float v1284 = a3i4;	// L1612
      float v1285 = v1283 - v1284;	// L1613
      float b2i4;	// L1614
      b2i4 = v1285;	// L1615
      float v1287 = a0r4;	// L1616
      float v1288 = a1i4;	// L1617
      float v1289 = v1287 - v1288;	// L1618
      float v1290 = a2r4;	// L1619
      float v1291 = v1289 - v1290;	// L1620
      float v1292 = a3i4;	// L1621
      float v1293 = v1291 + v1292;	// L1622
      float b3r4;	// L1623
      b3r4 = v1293;	// L1624
      float v1295 = a0i4;	// L1625
      float v1296 = a1r4;	// L1626
      float v1297 = v1295 + v1296;	// L1627
      float v1298 = a2i4;	// L1628
      float v1299 = v1297 - v1298;	// L1629
      float v1300 = a3r4;	// L1630
      float v1301 = v1299 - v1300;	// L1631
      float b3i4;	// L1632
      b3i4 = v1301;	// L1633
      float v1303 = b0r4;	// L1634
      int v1304 = idx1_4;	// L1635
      int v1305 = v1304;	// L1636
      buf_real[v1305] = v1303;	// L1637
      float v1306 = b0i4;	// L1638
      int v1307 = idx1_4;	// L1639
      int v1308 = v1307;	// L1640
      buf_imag[v1308] = v1306;	// L1641
      float v1309 = b1r4;	// L1642
      int v1310 = idx2_4;	// L1643
      int v1311 = v1310;	// L1644
      buf_real[v1311] = v1309;	// L1645
      float v1312 = b1i4;	// L1646
      int v1313 = idx2_4;	// L1647
      int v1314 = v1313;	// L1648
      buf_imag[v1314] = v1312;	// L1649
      float v1315 = b2r4;	// L1650
      int v1316 = idx3_4;	// L1651
      int v1317 = v1316;	// L1652
      buf_real[v1317] = v1315;	// L1653
      float v1318 = b2i4;	// L1654
      int v1319 = idx3_4;	// L1655
      int v1320 = v1319;	// L1656
      buf_imag[v1320] = v1318;	// L1657
      float v1321 = b3r4;	// L1658
      int v1322 = idx4_4;	// L1659
      int v1323 = v1322;	// L1660
      buf_real[v1323] = v1321;	// L1661
      float v1324 = b3i4;	// L1662
      int v1325 = idx4_4;	// L1663
      int v1326 = v1325;	// L1664
      buf_imag[v1326] = v1324;	// L1665
    }
  }
  l_S_g5_9_g5: for (int g5 = 0; g5 < 1; g5++) {	// L1668
    l_S_j5_9_j5: for (int j5 = 0; j5 < 256; j5++) {	// L1669
    #pragma HLS pipeline II=3
      int v1329 = j5;	// L1670
      float v1330 = v1329;	// L1671
      float j5_f;	// L1672
      j5_f = v1330;	// L1673
      float v1332 = PI;	// L1676
      float v1333 = v1332 * -2.000000;	// L1677
      float v1334 = j5_f;	// L1678
      float v1335 = v1333 * v1334;	// L1679
      float v1336 = v1335 / 1024.000000;	// L1681
      float theta5;	// L1682
      theta5 = v1336;	// L1683
      float v1338 = theta5;	// L1684
      float v1339 = v1338 * v1338;	// L1685
      float th5_2;	// L1686
      th5_2 = v1339;	// L1687
      float v1341 = th5_2;	// L1688
      float v1342 = theta5;	// L1689
      float v1343 = v1341 * v1342;	// L1690
      float th5_3;	// L1691
      th5_3 = v1343;	// L1692
      float v1345 = th5_2;	// L1693
      float v1346 = v1345 * v1345;	// L1694
      float th5_4;	// L1695
      th5_4 = v1346;	// L1696
      float v1348 = th5_4;	// L1697
      float v1349 = theta5;	// L1698
      float v1350 = v1348 * v1349;	// L1699
      float th5_5;	// L1700
      th5_5 = v1350;	// L1701
      float v1352 = th5_4;	// L1702
      float v1353 = th5_2;	// L1703
      float v1354 = v1352 * v1353;	// L1704
      float th5_6;	// L1705
      th5_6 = v1354;	// L1706
      float v1356 = th5_6;	// L1707
      float v1357 = theta5;	// L1708
      float v1358 = v1356 * v1357;	// L1709
      float th5_7;	// L1710
      th5_7 = v1358;	// L1711
      float v1360 = th5_4;	// L1712
      float v1361 = v1360 * v1360;	// L1713
      float th5_8;	// L1714
      th5_8 = v1361;	// L1715
      float v1363 = th5_8;	// L1716
      float v1364 = theta5;	// L1717
      float v1365 = v1363 * v1364;	// L1718
      float th5_9;	// L1719
      th5_9 = v1365;	// L1720
      float v1367 = th5_8;	// L1721
      float v1368 = th5_2;	// L1722
      float v1369 = v1367 * v1368;	// L1723
      float th5_10;	// L1724
      th5_10 = v1369;	// L1725
      float v1371 = th5_10;	// L1726
      float v1372 = theta5;	// L1727
      float v1373 = v1371 * v1372;	// L1728
      float th5_11;	// L1729
      th5_11 = v1373;	// L1730
      float v1375 = th5_2;	// L1731
      float v1376 = v1375 / 2.000000;	// L1732
      float v1377 = 1.000000 - v1376;	// L1734
      float v1378 = th5_4;	// L1735
      float v1379 = v1378 / 24.000000;	// L1737
      float v1380 = v1377 + v1379;	// L1738
      float v1381 = th5_6;	// L1739
      float v1382 = v1381 / 720.000000;	// L1741
      float v1383 = v1380 - v1382;	// L1742
      float v1384 = th5_8;	// L1743
      float v1385 = v1384 / 40320.000000;	// L1745
      float v1386 = v1383 + v1385;	// L1746
      float v1387 = th5_10;	// L1747
      float v1388 = v1387 / 3628800.000000;	// L1749
      float v1389 = v1386 - v1388;	// L1750
      float cos5;	// L1751
      cos5 = v1389;	// L1752
      float v1391 = theta5;	// L1753
      float v1392 = th5_3;	// L1754
      float v1393 = v1392 / 6.000000;	// L1756
      float v1394 = v1391 - v1393;	// L1757
      float v1395 = th5_5;	// L1758
      float v1396 = v1395 / 120.000000;	// L1760
      float v1397 = v1394 + v1396;	// L1761
      float v1398 = th5_7;	// L1762
      float v1399 = v1398 / 5040.000000;	// L1764
      float v1400 = v1397 - v1399;	// L1765
      float v1401 = th5_9;	// L1766
      float v1402 = v1401 / 362880.000000;	// L1768
      float v1403 = v1400 + v1402;	// L1769
      float v1404 = th5_11;	// L1770
      float v1405 = v1404 / 39916800.000000;	// L1772
      float v1406 = v1403 - v1405;	// L1773
      float sin5;	// L1774
      sin5 = v1406;	// L1775
      float v1408 = cos5;	// L1776
      float Wr5;	// L1777
      Wr5 = v1408;	// L1778
      float v1410 = sin5;	// L1779
      float Wi5;	// L1780
      Wi5 = v1410;	// L1781
      float v1412 = Wr5;	// L1782
      float v1413 = v1412 * v1412;	// L1783
      float v1414 = Wi5;	// L1784
      float v1415 = v1414 * v1414;	// L1785
      float v1416 = v1413 - v1415;	// L1786
      float W2r5;	// L1787
      W2r5 = v1416;	// L1788
      float v1418 = Wr5;	// L1789
      float v1419 = v1418  << 1.000000;	// L1790
      float v1420 = Wi5;	// L1791
      float v1421 = v1419 * v1420;	// L1792
      float W2i5;	// L1793
      W2i5 = v1421;	// L1794
      float v1423 = W2r5;	// L1795
      float v1424 = Wr5;	// L1796
      float v1425 = v1423 * v1424;	// L1797
      float v1426 = W2i5;	// L1798
      float v1427 = Wi5;	// L1799
      float v1428 = v1426 * v1427;	// L1800
      float v1429 = v1425 - v1428;	// L1801
      float W3r5;	// L1802
      W3r5 = v1429;	// L1803
      float v1431 = W2r5;	// L1804
      float v1432 = Wi5;	// L1805
      float v1433 = v1431 * v1432;	// L1806
      float v1434 = W2i5;	// L1807
      float v1435 = Wr5;	// L1808
      float v1436 = v1434 * v1435;	// L1809
      float v1437 = v1433 + v1436;	// L1810
      float W3i5;	// L1811
      W3i5 = v1437;	// L1812
      int v1439 = g5;	// L1813
      int v1440 = v1439 * 1024;	// L1816
      int v1441 = v1440;	// L1817
      int v1442 = j5;	// L1818
      int v1443 = v1441 + v1442;	// L1819
      int v1444 = v1443;	// L1820
      int base5;	// L1821
      base5 = v1444;	// L1822
      int v1446 = base5;	// L1823
      int idx1_5;	// L1824
      idx1_5 = v1446;	// L1825
      int v1448 = base5;	// L1826
      int v1449 = v1448;	// L1827
      int v1450 = v1449 + 256;	// L1830
      int v1451 = v1450;	// L1831
      int idx2_5;	// L1832
      idx2_5 = v1451;	// L1833
      int v1453 = base5;	// L1834
      int v1454 = v1453;	// L1835
      int v1455 = v1454 + 512;	// L1838
      int v1456 = v1455;	// L1839
      int idx3_5;	// L1840
      idx3_5 = v1456;	// L1841
      int v1458 = base5;	// L1842
      int v1459 = v1458;	// L1843
      int v1460 = v1459 + 768;	// L1846
      int v1461 = v1460;	// L1847
      int idx4_5;	// L1848
      idx4_5 = v1461;	// L1849
      int v1463 = idx1_5;	// L1850
      int v1464 = v1463;	// L1851
      float v1465 = buf_real[v1464];	// L1852
      float a0r5;	// L1853
      a0r5 = v1465;	// L1854
      int v1467 = idx1_5;	// L1855
      int v1468 = v1467;	// L1856
      float v1469 = buf_imag[v1468];	// L1857
      float a0i5;	// L1858
      a0i5 = v1469;	// L1859
      int v1471 = idx2_5;	// L1860
      int v1472 = v1471;	// L1861
      float v1473 = buf_real[v1472];	// L1862
      float a1r05;	// L1863
      a1r05 = v1473;	// L1864
      int v1475 = idx2_5;	// L1865
      int v1476 = v1475;	// L1866
      float v1477 = buf_imag[v1476];	// L1867
      float a1i05;	// L1868
      a1i05 = v1477;	// L1869
      int v1479 = idx3_5;	// L1870
      int v1480 = v1479;	// L1871
      float v1481 = buf_real[v1480];	// L1872
      float a2r05;	// L1873
      a2r05 = v1481;	// L1874
      int v1483 = idx3_5;	// L1875
      int v1484 = v1483;	// L1876
      float v1485 = buf_imag[v1484];	// L1877
      float a2i05;	// L1878
      a2i05 = v1485;	// L1879
      int v1487 = idx4_5;	// L1880
      int v1488 = v1487;	// L1881
      float v1489 = buf_real[v1488];	// L1882
      float a3r05;	// L1883
      a3r05 = v1489;	// L1884
      int v1491 = idx4_5;	// L1885
      int v1492 = v1491;	// L1886
      float v1493 = buf_imag[v1492];	// L1887
      float a3i05;	// L1888
      a3i05 = v1493;	// L1889
      float v1495 = a1r05;	// L1890
      float v1496 = Wr5;	// L1891
      float v1497 = v1495 * v1496;	// L1892
      float v1498 = a1i05;	// L1893
      float v1499 = Wi5;	// L1894
      float v1500 = v1498 * v1499;	// L1895
      float v1501 = v1497 - v1500;	// L1896
      float a1r5;	// L1897
      a1r5 = v1501;	// L1898
      float v1503 = a1r05;	// L1899
      float v1504 = Wi5;	// L1900
      float v1505 = v1503 * v1504;	// L1901
      float v1506 = a1i05;	// L1902
      float v1507 = Wr5;	// L1903
      float v1508 = v1506 * v1507;	// L1904
      float v1509 = v1505 + v1508;	// L1905
      float a1i5;	// L1906
      a1i5 = v1509;	// L1907
      float v1511 = a2r05;	// L1908
      float v1512 = W2r5;	// L1909
      float v1513 = v1511 * v1512;	// L1910
      float v1514 = a2i05;	// L1911
      float v1515 = W2i5;	// L1912
      float v1516 = v1514 * v1515;	// L1913
      float v1517 = v1513 - v1516;	// L1914
      float a2r5;	// L1915
      a2r5 = v1517;	// L1916
      float v1519 = a2r05;	// L1917
      float v1520 = W2i5;	// L1918
      float v1521 = v1519 * v1520;	// L1919
      float v1522 = a2i05;	// L1920
      float v1523 = W2r5;	// L1921
      float v1524 = v1522 * v1523;	// L1922
      float v1525 = v1521 + v1524;	// L1923
      float a2i5;	// L1924
      a2i5 = v1525;	// L1925
      float v1527 = a3r05;	// L1926
      float v1528 = W3r5;	// L1927
      float v1529 = v1527 * v1528;	// L1928
      float v1530 = a3i05;	// L1929
      float v1531 = W3i5;	// L1930
      float v1532 = v1530 * v1531;	// L1931
      float v1533 = v1529 - v1532;	// L1932
      float a3r5;	// L1933
      a3r5 = v1533;	// L1934
      float v1535 = a3r05;	// L1935
      float v1536 = W3i5;	// L1936
      float v1537 = v1535 * v1536;	// L1937
      float v1538 = a3i05;	// L1938
      float v1539 = W3r5;	// L1939
      float v1540 = v1538 * v1539;	// L1940
      float v1541 = v1537 + v1540;	// L1941
      float a3i5;	// L1942
      a3i5 = v1541;	// L1943
      float v1543 = a0r5;	// L1944
      float v1544 = a1r5;	// L1945
      float v1545 = v1543 + v1544;	// L1946
      float v1546 = a2r5;	// L1947
      float v1547 = v1545 + v1546;	// L1948
      float v1548 = a3r5;	// L1949
      float v1549 = v1547 + v1548;	// L1950
      float b0r5;	// L1951
      b0r5 = v1549;	// L1952
      float v1551 = a0i5;	// L1953
      float v1552 = a1i5;	// L1954
      float v1553 = v1551 + v1552;	// L1955
      float v1554 = a2i5;	// L1956
      float v1555 = v1553 + v1554;	// L1957
      float v1556 = a3i5;	// L1958
      float v1557 = v1555 + v1556;	// L1959
      float b0i5;	// L1960
      b0i5 = v1557;	// L1961
      float v1559 = a0r5;	// L1962
      float v1560 = a1i5;	// L1963
      float v1561 = v1559 + v1560;	// L1964
      float v1562 = a2r5;	// L1965
      float v1563 = v1561 - v1562;	// L1966
      float v1564 = a3i5;	// L1967
      float v1565 = v1563 - v1564;	// L1968
      float b1r5;	// L1969
      b1r5 = v1565;	// L1970
      float v1567 = a0i5;	// L1971
      float v1568 = a1r5;	// L1972
      float v1569 = v1567 - v1568;	// L1973
      float v1570 = a2i5;	// L1974
      float v1571 = v1569 - v1570;	// L1975
      float v1572 = a3r5;	// L1976
      float v1573 = v1571 + v1572;	// L1977
      float b1i5;	// L1978
      b1i5 = v1573;	// L1979
      float v1575 = a0r5;	// L1980
      float v1576 = a1r5;	// L1981
      float v1577 = v1575 - v1576;	// L1982
      float v1578 = a2r5;	// L1983
      float v1579 = v1577 + v1578;	// L1984
      float v1580 = a3r5;	// L1985
      float v1581 = v1579 - v1580;	// L1986
      float b2r5;	// L1987
      b2r5 = v1581;	// L1988
      float v1583 = a0i5;	// L1989
      float v1584 = a1i5;	// L1990
      float v1585 = v1583 - v1584;	// L1991
      float v1586 = a2i5;	// L1992
      float v1587 = v1585 + v1586;	// L1993
      float v1588 = a3i5;	// L1994
      float v1589 = v1587 - v1588;	// L1995
      float b2i5;	// L1996
      b2i5 = v1589;	// L1997
      float v1591 = a0r5;	// L1998
      float v1592 = a1i5;	// L1999
      float v1593 = v1591 - v1592;	// L2000
      float v1594 = a2r5;	// L2001
      float v1595 = v1593 - v1594;	// L2002
      float v1596 = a3i5;	// L2003
      float v1597 = v1595 + v1596;	// L2004
      float b3r5;	// L2005
      b3r5 = v1597;	// L2006
      float v1599 = a0i5;	// L2007
      float v1600 = a1r5;	// L2008
      float v1601 = v1599 + v1600;	// L2009
      float v1602 = a2i5;	// L2010
      float v1603 = v1601 - v1602;	// L2011
      float v1604 = a3r5;	// L2012
      float v1605 = v1603 - v1604;	// L2013
      float b3i5;	// L2014
      b3i5 = v1605;	// L2015
      float v1607 = b0r5;	// L2016
      int v1608 = idx1_5;	// L2017
      int v1609 = v1608;	// L2018
      buf_real[v1609] = v1607;	// L2019
      float v1610 = b0i5;	// L2020
      int v1611 = idx1_5;	// L2021
      int v1612 = v1611;	// L2022
      buf_imag[v1612] = v1610;	// L2023
      float v1613 = b1r5;	// L2024
      int v1614 = idx2_5;	// L2025
      int v1615 = v1614;	// L2026
      buf_real[v1615] = v1613;	// L2027
      float v1616 = b1i5;	// L2028
      int v1617 = idx2_5;	// L2029
      int v1618 = v1617;	// L2030
      buf_imag[v1618] = v1616;	// L2031
      float v1619 = b2r5;	// L2032
      int v1620 = idx3_5;	// L2033
      int v1621 = v1620;	// L2034
      buf_real[v1621] = v1619;	// L2035
      float v1622 = b2i5;	// L2036
      int v1623 = idx3_5;	// L2037
      int v1624 = v1623;	// L2038
      buf_imag[v1624] = v1622;	// L2039
      float v1625 = b3r5;	// L2040
      int v1626 = idx4_5;	// L2041
      int v1627 = v1626;	// L2042
      buf_real[v1627] = v1625;	// L2043
      float v1628 = b3i5;	// L2044
      int v1629 = idx4_5;	// L2045
      int v1630 = v1629;	// L2046
      buf_imag[v1630] = v1628;	// L2047
    }
  }
  l_S_c_11_c: for (int c = 0; c < 1024; c++) {	// L2050
  #pragma HLS pipeline II=3
    float v1632 = buf_real[c];	// L2051
    v2[c] = v1632;	// L2052
    float v1633 = buf_imag[c];	// L2053
    v3[c] = v1633;	// L2054
  }
}
#pragma pocc-region-end
}

