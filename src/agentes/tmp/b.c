
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
  float buf_real[1024];	// L3
  float buf_imag[1024];	// L4
  l_S_i_0_i: for (int i = 0; i < 1024; i++) {	// L5
    int v7 = i;	// L6
    int i0;	// L7
    i0 = v7;	// L8
    int v9 = i0;	// L9
    int v10 = v9 / 4;	// L12
    int q0;	// L13
    q0 = v10;	// L14
    int v12 = i0;	// L15
    int v13 = q0;	// L16
    int v14 = v13;	// L17
    int v15 = v14 * 4;	// L21
    int v16 = v12;	// L22
    int v17 = v15;	// L23
    int v18 = v16 - v17;	// L24
    int v19 = v18;	// L25
    int d0;	// L26
    d0 = v19;	// L27
    int v21 = q0;	// L28
    int i1;	// L29
    i1 = v21;	// L30
    int v23 = i1;	// L31
    int v24 = v23 / 4;	// L34
    int q1;	// L35
    q1 = v24;	// L36
    int v26 = i1;	// L37
    int v27 = q1;	// L38
    int v28 = v27;	// L39
    int v29 = v28 * 4;	// L43
    int v30 = v26;	// L44
    int v31 = v29;	// L45
    int v32 = v30 - v31;	// L46
    int v33 = v32;	// L47
    int d1;	// L48
    d1 = v33;	// L49
    int v35 = q1;	// L50
    int i2;	// L51
    i2 = v35;	// L52
    int v37 = i2;	// L53
    int v38 = v37 / 4;	// L56
    int q2;	// L57
    q2 = v38;	// L58
    int v40 = i2;	// L59
    int v41 = q2;	// L60
    int v42 = v41;	// L61
    int v43 = v42 * 4;	// L65
    int v44 = v40;	// L66
    int v45 = v43;	// L67
    int v46 = v44 - v45;	// L68
    int v47 = v46;	// L69
    int d2;	// L70
    d2 = v47;	// L71
    int v49 = q2;	// L72
    int i3;	// L73
    i3 = v49;	// L74
    int v51 = i3;	// L75
    int v52 = v51 / 4;	// L78
    int q3;	// L79
    q3 = v52;	// L80
    int v54 = i3;	// L81
    int v55 = q3;	// L82
    int v56 = v55;	// L83
    int v57 = v56 * 4;	// L87
    int v58 = v54;	// L88
    int v59 = v57;	// L89
    int v60 = v58 - v59;	// L90
    int v61 = v60;	// L91
    int d3;	// L92
    d3 = v61;	// L93
    int v63 = q3;	// L94
    int i4;	// L95
    i4 = v63;	// L96
    int v65 = i4;	// L97
    int v66 = v65 / 4;	// L100
    int q4;	// L101
    q4 = v66;	// L102
    int v68 = i4;	// L103
    int v69 = q4;	// L104
    int v70 = v69;	// L105
    int v71 = v70 * 4;	// L109
    int v72 = v68;	// L110
    int v73 = v71;	// L111
    int v74 = v72 - v73;	// L112
    int v75 = v74;	// L113
    int d4;	// L114
    d4 = v75;	// L115
    int v77 = d0;	// L116
    int v78 = v77;	// L117
    int v79 = v78 * 256;	// L121
    int v80 = d1;	// L122
    int v81 = v80;	// L123
    int v82 = v81 * 64;	// L127
    int v83 = v79;	// L128
    int v84 = v82;	// L129
    int v85 = v83 + v84;	// L130
    int v86 = d2;	// L131
    int v87 = v86;	// L132
    int v88 = v87 * 16;	// L136
    int v89 = v85;	// L137
    int v90 = v88;	// L138
    int v91 = v89 + v90;	// L139
    int v92 = d3;	// L140
    int v93 = v92;	// L141
    int v94 = v93 * 4;	// L145
    int v95 = v91;	// L146
    int v96 = v94;	// L147
    int v97 = v95 + v96;	// L148
    int v98 = d4;	// L149
    int v99 = v97;	// L150
    int v100 = v98;	// L151
    int v101 = v99 + v100;	// L152
    int v102 = v101;	// L153
    int rev;	// L154
    rev = v102;	// L155
    float v104 = v0[i];	// L156
    int v105 = rev;	// L157
    int v106 = v105;	// L158
    buf_real[v106] = v104;	// L159
    float v107 = v1[i];	// L160
    int v108 = rev;	// L161
    int v109 = v108;	// L162
    buf_imag[v109] = v107;	// L163
  }
  l_S_g1_1_g1: for (int g1 = 0; g1 < 256; g1++) {	// L165
    l_S_j1_1_j1: for (int j1 = 0; j1 < 1; j1++) {	// L166
      int v112 = g1;	// L167
      int v113 = v112 * 4;	// L171
      int v114 = v113;	// L172
      int k1;	// L173
      k1 = v114;	// L174
      int v116 = k1;	// L175
      int v117 = v116;	// L176
      int v118 = j1;	// L177
      int v119 = v117 + v118;	// L178
      int v120 = v119;	// L179
      int idx0;	// L180
      idx0 = v120;	// L181
      int v122 = idx0;	// L182
      int v123 = v122;	// L183
      int v124 = v123 + 1;	// L187
      int v125 = v124;	// L188
      int idx1;	// L189
      idx1 = v125;	// L190
      int v127 = idx1;	// L191
      int v128 = v127;	// L192
      int v129 = v128 + 1;	// L196
      int v130 = v129;	// L197
      int idx2;	// L198
      idx2 = v130;	// L199
      int v132 = idx2;	// L200
      int v133 = v132;	// L201
      int v134 = v133 + 1;	// L205
      int v135 = v134;	// L206
      int idx3;	// L207
      idx3 = v135;	// L208
      int v137 = idx0;	// L209
      int v138 = v137;	// L210
      float v139 = buf_real[v138];	// L211
      float s1_ar;	// L212
      s1_ar = v139;	// L213
      int v141 = idx0;	// L214
      int v142 = v141;	// L215
      float v143 = buf_imag[v142];	// L216
      float s1_ai;	// L217
      s1_ai = v143;	// L218
      int v145 = idx1;	// L219
      int v146 = v145;	// L220
      float v147 = buf_real[v146];	// L221
      float s1_br;	// L222
      s1_br = v147;	// L223
      int v149 = idx1;	// L224
      int v150 = v149;	// L225
      float v151 = buf_imag[v150];	// L226
      float s1_bi;	// L227
      s1_bi = v151;	// L228
      int v153 = idx2;	// L229
      int v154 = v153;	// L230
      float v155 = buf_real[v154];	// L231
      float s1_cr;	// L232
      s1_cr = v155;	// L233
      int v157 = idx2;	// L234
      int v158 = v157;	// L235
      float v159 = buf_imag[v158];	// L236
      float s1_ci;	// L237
      s1_ci = v159;	// L238
      int v161 = idx3;	// L239
      int v162 = v161;	// L240
      float v163 = buf_real[v162];	// L241
      float s1_dr;	// L242
      s1_dr = v163;	// L243
      int v165 = idx3;	// L244
      int v166 = v165;	// L245
      float v167 = buf_imag[v166];	// L246
      float s1_di;	// L247
      s1_di = v167;	// L248
      int v169 = j1;	// L249
      float v170 = v169;	// L250
      float s1_jf;	// L251
      s1_jf = v170;	// L252
      float v172 = s1_jf;	// L253
      float v173 = v172 * 1.570796;	// L256
      float s1_x;	// L257
      s1_x = v173;	// L258
      float v175 = s1_x;	// L259
      float v176 = v175 * v175;	// L261
      float s1_x2;	// L262
      s1_x2 = v176;	// L263
      float v178 = s1_x2;	// L264
      float v179 = s1_x;	// L265
      float v180 = v178 * v179;	// L266
      float s1_x3;	// L267
      s1_x3 = v180;	// L268
      float v182 = s1_x2;	// L269
      float v183 = v182 * v182;	// L271
      float s1_x4;	// L272
      s1_x4 = v183;	// L273
      float v185 = s1_x4;	// L274
      float v186 = s1_x;	// L275
      float v187 = v185 * v186;	// L276
      float s1_x5;	// L277
      s1_x5 = v187;	// L278
      float v189 = s1_x4;	// L279
      float v190 = s1_x2;	// L280
      float v191 = v189 * v190;	// L281
      float s1_x6;	// L282
      s1_x6 = v191;	// L283
      float v193 = s1_x6;	// L284
      float v194 = s1_x;	// L285
      float v195 = v193 * v194;	// L286
      float s1_x7;	// L287
      s1_x7 = v195;	// L288
      float v197 = s1_x4;	// L289
      float v198 = v197 * v197;	// L291
      float s1_x8;	// L292
      s1_x8 = v198;	// L293
      float v200 = s1_x8;	// L294
      float v201 = s1_x;	// L295
      float v202 = v200 * v201;	// L296
      float s1_x9;	// L297
      s1_x9 = v202;	// L298
      float v204 = s1_x8;	// L299
      float v205 = s1_x2;	// L300
      float v206 = v204 * v205;	// L301
      float s1_x10;	// L302
      s1_x10 = v206;	// L303
      float v208 = s1_x10;	// L304
      float v209 = s1_x;	// L305
      float v210 = v208 * v209;	// L306
      float s1_x11;	// L307
      s1_x11 = v210;	// L308
      float v212 = s1_x2;	// L309
      float v213 = v212 / 2.000000;	// L312
      float v214 = 1.000000 - v213;	// L315
      float v215 = s1_x4;	// L316
      float v216 = v215 / 24.000000;	// L319
      float v217 = v214 + v216;	// L320
      float v218 = s1_x6;	// L321
      float v219 = v218 / 720.000000;	// L324
      float v220 = v217 - v219;	// L325
      float v221 = s1_x8;	// L326
      float v222 = v221 / 40320.000000;	// L329
      float v223 = v220 + v222;	// L330
      float v224 = s1_x10;	// L331
      float v225 = v224 / 3628800.000000;	// L334
      float v226 = v223 - v225;	// L335
      float s1_cos;	// L336
      s1_cos = v226;	// L337
      float v228 = s1_x;	// L338
      float v229 = s1_x3;	// L339
      float v230 = v229 / 6.000000;	// L342
      float v231 = v228 - v230;	// L343
      float v232 = s1_x5;	// L344
      float v233 = v232 / 120.000000;	// L347
      float v234 = v231 + v233;	// L348
      float v235 = s1_x7;	// L349
      float v236 = v235 / 5040.000000;	// L352
      float v237 = v234 - v236;	// L353
      float v238 = s1_x9;	// L354
      float v239 = v238 / 362880.000000;	// L357
      float v240 = v237 + v239;	// L358
      float v241 = s1_x11;	// L359
      float v242 = v241 / 39916800.000000;	// L362
      float v243 = v240 - v242;	// L363
      float s1_sin;	// L364
      s1_sin = v243;	// L365
      float v245 = s1_cos;	// L366
      float v246 = v245 * v245;	// L368
      float v247 = s1_sin;	// L369
      float v248 = v247 * v247;	// L371
      float v249 = v246 - v248;	// L372
      float s1_cos2;	// L373
      s1_cos2 = v249;	// L374
      float v251 = s1_sin;	// L375
      float v252 = v251  << 1.000000;	// L378
      float v253 = s1_cos;	// L379
      float v254 = v252 * v253;	// L380
      float s1_sin2;	// L381
      s1_sin2 = v254;	// L382
      float v256 = s1_cos2;	// L383
      float v257 = s1_cos;	// L384
      float v258 = v256 * v257;	// L385
      float v259 = s1_sin2;	// L386
      float v260 = s1_sin;	// L387
      float v261 = v259 * v260;	// L388
      float v262 = v258 - v261;	// L389
      float s1_cos3;	// L390
      s1_cos3 = v262;	// L391
      float v264 = s1_sin2;	// L392
      float v265 = s1_cos;	// L393
      float v266 = v264 * v265;	// L394
      float v267 = s1_cos2;	// L395
      float v268 = s1_sin;	// L396
      float v269 = v267 * v268;	// L397
      float v270 = v266 + v269;	// L398
      float s1_sin3;	// L399
      s1_sin3 = v270;	// L400
      float v272 = s1_cos;	// L401
      float s1_w1r;	// L402
      s1_w1r = v272;	// L403
      float v274 = s1_sin;	// L404
      float v275 = -(v274);	// L405
      float s1_w1i;	// L406
      s1_w1i = v275;	// L407
      float v277 = s1_cos2;	// L408
      float s1_w2r;	// L409
      s1_w2r = v277;	// L410
      float v279 = s1_sin2;	// L411
      float v280 = -(v279);	// L412
      float s1_w2i;	// L413
      s1_w2i = v280;	// L414
      float v282 = s1_cos3;	// L415
      float s1_w3r;	// L416
      s1_w3r = v282;	// L417
      float v284 = s1_sin3;	// L418
      float v285 = -(v284);	// L419
      float s1_w3i;	// L420
      s1_w3i = v285;	// L421
      float v287 = s1_br;	// L422
      float v288 = s1_w1r;	// L423
      float v289 = v287 * v288;	// L424
      float v290 = s1_bi;	// L425
      float v291 = s1_w1i;	// L426
      float v292 = v290 * v291;	// L427
      float v293 = v289 - v292;	// L428
      float s1_bpr;	// L429
      s1_bpr = v293;	// L430
      float v295 = s1_br;	// L431
      float v296 = s1_w1i;	// L432
      float v297 = v295 * v296;	// L433
      float v298 = s1_bi;	// L434
      float v299 = s1_w1r;	// L435
      float v300 = v298 * v299;	// L436
      float v301 = v297 + v300;	// L437
      float s1_bpi;	// L438
      s1_bpi = v301;	// L439
      float v303 = s1_cr;	// L440
      float v304 = s1_w2r;	// L441
      float v305 = v303 * v304;	// L442
      float v306 = s1_ci;	// L443
      float v307 = s1_w2i;	// L444
      float v308 = v306 * v307;	// L445
      float v309 = v305 - v308;	// L446
      float s1_cpr;	// L447
      s1_cpr = v309;	// L448
      float v311 = s1_cr;	// L449
      float v312 = s1_w2i;	// L450
      float v313 = v311 * v312;	// L451
      float v314 = s1_ci;	// L452
      float v315 = s1_w2r;	// L453
      float v316 = v314 * v315;	// L454
      float v317 = v313 + v316;	// L455
      float s1_cpi;	// L456
      s1_cpi = v317;	// L457
      float v319 = s1_dr;	// L458
      float v320 = s1_w3r;	// L459
      float v321 = v319 * v320;	// L460
      float v322 = s1_di;	// L461
      float v323 = s1_w3i;	// L462
      float v324 = v322 * v323;	// L463
      float v325 = v321 - v324;	// L464
      float s1_dpr;	// L465
      s1_dpr = v325;	// L466
      float v327 = s1_dr;	// L467
      float v328 = s1_w3i;	// L468
      float v329 = v327 * v328;	// L469
      float v330 = s1_di;	// L470
      float v331 = s1_w3r;	// L471
      float v332 = v330 * v331;	// L472
      float v333 = v329 + v332;	// L473
      float s1_dpi;	// L474
      s1_dpi = v333;	// L475
      float v335 = s1_ar;	// L476
      float v336 = s1_cpr;	// L477
      float v337 = v335 + v336;	// L478
      float s1_t0r;	// L479
      s1_t0r = v337;	// L480
      float v339 = s1_ai;	// L481
      float v340 = s1_cpi;	// L482
      float v341 = v339 + v340;	// L483
      float s1_t0i;	// L484
      s1_t0i = v341;	// L485
      float v343 = s1_ar;	// L486
      float v344 = s1_cpr;	// L487
      float v345 = v343 - v344;	// L488
      float s1_t1r;	// L489
      s1_t1r = v345;	// L490
      float v347 = s1_ai;	// L491
      float v348 = s1_cpi;	// L492
      float v349 = v347 - v348;	// L493
      float s1_t1i;	// L494
      s1_t1i = v349;	// L495
      float v351 = s1_bpr;	// L496
      float v352 = s1_dpr;	// L497
      float v353 = v351 + v352;	// L498
      float s1_t2r;	// L499
      s1_t2r = v353;	// L500
      float v355 = s1_bpi;	// L501
      float v356 = s1_dpi;	// L502
      float v357 = v355 + v356;	// L503
      float s1_t2i;	// L504
      s1_t2i = v357;	// L505
      float v359 = s1_bpr;	// L506
      float v360 = s1_dpr;	// L507
      float v361 = v359 - v360;	// L508
      float s1_t3r;	// L509
      s1_t3r = v361;	// L510
      float v363 = s1_bpi;	// L511
      float v364 = s1_dpi;	// L512
      float v365 = v363 - v364;	// L513
      float s1_t3i;	// L514
      s1_t3i = v365;	// L515
      float v367 = s1_t0r;	// L516
      float v368 = s1_t2r;	// L517
      float v369 = v367 + v368;	// L518
      int v370 = idx0;	// L519
      int v371 = v370;	// L520
      buf_real[v371] = v369;	// L521
      float v372 = s1_t0i;	// L522
      float v373 = s1_t2i;	// L523
      float v374 = v372 + v373;	// L524
      int v375 = idx0;	// L525
      int v376 = v375;	// L526
      buf_imag[v376] = v374;	// L527
      float v377 = s1_t1r;	// L528
      float v378 = s1_t3i;	// L529
      float v379 = v377 + v378;	// L530
      int v380 = idx1;	// L531
      int v381 = v380;	// L532
      buf_real[v381] = v379;	// L533
      float v382 = s1_t1i;	// L534
      float v383 = s1_t3r;	// L535
      float v384 = v382 - v383;	// L536
      int v385 = idx1;	// L537
      int v386 = v385;	// L538
      buf_imag[v386] = v384;	// L539
      float v387 = s1_t0r;	// L540
      float v388 = s1_t2r;	// L541
      float v389 = v387 - v388;	// L542
      int v390 = idx2;	// L543
      int v391 = v390;	// L544
      buf_real[v391] = v389;	// L545
      float v392 = s1_t0i;	// L546
      float v393 = s1_t2i;	// L547
      float v394 = v392 - v393;	// L548
      int v395 = idx2;	// L549
      int v396 = v395;	// L550
      buf_imag[v396] = v394;	// L551
      float v397 = s1_t1r;	// L552
      float v398 = s1_t3i;	// L553
      float v399 = v397 - v398;	// L554
      int v400 = idx3;	// L555
      int v401 = v400;	// L556
      buf_real[v401] = v399;	// L557
      float v402 = s1_t1i;	// L558
      float v403 = s1_t3r;	// L559
      float v404 = v402 + v403;	// L560
      int v405 = idx3;	// L561
      int v406 = v405;	// L562
      buf_imag[v406] = v404;	// L563
    }
  }
  l_S_g2_3_g2: for (int g2 = 0; g2 < 64; g2++) {	// L566
    l_S_j2_3_j2: for (int j2 = 0; j2 < 4; j2++) {	// L567
      int v409 = g2;	// L568
      int v410 = v409 * 16;	// L572
      int v411 = v410;	// L573
      int k2;	// L574
      k2 = v411;	// L575
      int v413 = k2;	// L576
      int v414 = v413;	// L577
      int v415 = j2;	// L578
      int v416 = v414 + v415;	// L579
      int v417 = v416;	// L580
      int idx01;	// L581
      idx01 = v417;	// L582
      int v419 = idx01;	// L583
      int v420 = v419;	// L584
      int v421 = v420 + 4;	// L588
      int v422 = v421;	// L589
      int idx11;	// L590
      idx11 = v422;	// L591
      int v424 = idx11;	// L592
      int v425 = v424;	// L593
      int v426 = v425 + 4;	// L597
      int v427 = v426;	// L598
      int idx21;	// L599
      idx21 = v427;	// L600
      int v429 = idx21;	// L601
      int v430 = v429;	// L602
      int v431 = v430 + 4;	// L606
      int v432 = v431;	// L607
      int idx31;	// L608
      idx31 = v432;	// L609
      int v434 = idx01;	// L610
      int v435 = v434;	// L611
      float v436 = buf_real[v435];	// L612
      float s2_ar;	// L613
      s2_ar = v436;	// L614
      int v438 = idx01;	// L615
      int v439 = v438;	// L616
      float v440 = buf_imag[v439];	// L617
      float s2_ai;	// L618
      s2_ai = v440;	// L619
      int v442 = idx11;	// L620
      int v443 = v442;	// L621
      float v444 = buf_real[v443];	// L622
      float s2_br;	// L623
      s2_br = v444;	// L624
      int v446 = idx11;	// L625
      int v447 = v446;	// L626
      float v448 = buf_imag[v447];	// L627
      float s2_bi;	// L628
      s2_bi = v448;	// L629
      int v450 = idx21;	// L630
      int v451 = v450;	// L631
      float v452 = buf_real[v451];	// L632
      float s2_cr;	// L633
      s2_cr = v452;	// L634
      int v454 = idx21;	// L635
      int v455 = v454;	// L636
      float v456 = buf_imag[v455];	// L637
      float s2_ci;	// L638
      s2_ci = v456;	// L639
      int v458 = idx31;	// L640
      int v459 = v458;	// L641
      float v460 = buf_real[v459];	// L642
      float s2_dr;	// L643
      s2_dr = v460;	// L644
      int v462 = idx31;	// L645
      int v463 = v462;	// L646
      float v464 = buf_imag[v463];	// L647
      float s2_di;	// L648
      s2_di = v464;	// L649
      int v466 = j2;	// L650
      float v467 = v466;	// L651
      float s2_jf;	// L652
      s2_jf = v467;	// L653
      float v469 = s2_jf;	// L654
      float v470 = v469 * 0.392699;	// L657
      float s2_x;	// L658
      s2_x = v470;	// L659
      float v472 = s2_x;	// L660
      float v473 = v472 * v472;	// L662
      float s2_x2;	// L663
      s2_x2 = v473;	// L664
      float v475 = s2_x2;	// L665
      float v476 = s2_x;	// L666
      float v477 = v475 * v476;	// L667
      float s2_x3;	// L668
      s2_x3 = v477;	// L669
      float v479 = s2_x2;	// L670
      float v480 = v479 * v479;	// L672
      float s2_x4;	// L673
      s2_x4 = v480;	// L674
      float v482 = s2_x4;	// L675
      float v483 = s2_x;	// L676
      float v484 = v482 * v483;	// L677
      float s2_x5;	// L678
      s2_x5 = v484;	// L679
      float v486 = s2_x4;	// L680
      float v487 = s2_x2;	// L681
      float v488 = v486 * v487;	// L682
      float s2_x6;	// L683
      s2_x6 = v488;	// L684
      float v490 = s2_x6;	// L685
      float v491 = s2_x;	// L686
      float v492 = v490 * v491;	// L687
      float s2_x7;	// L688
      s2_x7 = v492;	// L689
      float v494 = s2_x4;	// L690
      float v495 = v494 * v494;	// L692
      float s2_x8;	// L693
      s2_x8 = v495;	// L694
      float v497 = s2_x8;	// L695
      float v498 = s2_x;	// L696
      float v499 = v497 * v498;	// L697
      float s2_x9;	// L698
      s2_x9 = v499;	// L699
      float v501 = s2_x8;	// L700
      float v502 = s2_x2;	// L701
      float v503 = v501 * v502;	// L702
      float s2_x10;	// L703
      s2_x10 = v503;	// L704
      float v505 = s2_x10;	// L705
      float v506 = s2_x;	// L706
      float v507 = v505 * v506;	// L707
      float s2_x11;	// L708
      s2_x11 = v507;	// L709
      float v509 = s2_x2;	// L710
      float v510 = v509 / 2.000000;	// L713
      float v511 = 1.000000 - v510;	// L716
      float v512 = s2_x4;	// L717
      float v513 = v512 / 24.000000;	// L720
      float v514 = v511 + v513;	// L721
      float v515 = s2_x6;	// L722
      float v516 = v515 / 720.000000;	// L725
      float v517 = v514 - v516;	// L726
      float v518 = s2_x8;	// L727
      float v519 = v518 / 40320.000000;	// L730
      float v520 = v517 + v519;	// L731
      float v521 = s2_x10;	// L732
      float v522 = v521 / 3628800.000000;	// L735
      float v523 = v520 - v522;	// L736
      float s2_cos;	// L737
      s2_cos = v523;	// L738
      float v525 = s2_x;	// L739
      float v526 = s2_x3;	// L740
      float v527 = v526 / 6.000000;	// L743
      float v528 = v525 - v527;	// L744
      float v529 = s2_x5;	// L745
      float v530 = v529 / 120.000000;	// L748
      float v531 = v528 + v530;	// L749
      float v532 = s2_x7;	// L750
      float v533 = v532 / 5040.000000;	// L753
      float v534 = v531 - v533;	// L754
      float v535 = s2_x9;	// L755
      float v536 = v535 / 362880.000000;	// L758
      float v537 = v534 + v536;	// L759
      float v538 = s2_x11;	// L760
      float v539 = v538 / 39916800.000000;	// L763
      float v540 = v537 - v539;	// L764
      float s2_sin;	// L765
      s2_sin = v540;	// L766
      float v542 = s2_cos;	// L767
      float v543 = v542 * v542;	// L769
      float v544 = s2_sin;	// L770
      float v545 = v544 * v544;	// L772
      float v546 = v543 - v545;	// L773
      float s2_cos2;	// L774
      s2_cos2 = v546;	// L775
      float v548 = s2_sin;	// L776
      float v549 = v548  << 1.000000;	// L779
      float v550 = s2_cos;	// L780
      float v551 = v549 * v550;	// L781
      float s2_sin2;	// L782
      s2_sin2 = v551;	// L783
      float v553 = s2_cos2;	// L784
      float v554 = s2_cos;	// L785
      float v555 = v553 * v554;	// L786
      float v556 = s2_sin2;	// L787
      float v557 = s2_sin;	// L788
      float v558 = v556 * v557;	// L789
      float v559 = v555 - v558;	// L790
      float s2_cos3;	// L791
      s2_cos3 = v559;	// L792
      float v561 = s2_sin2;	// L793
      float v562 = s2_cos;	// L794
      float v563 = v561 * v562;	// L795
      float v564 = s2_cos2;	// L796
      float v565 = s2_sin;	// L797
      float v566 = v564 * v565;	// L798
      float v567 = v563 + v566;	// L799
      float s2_sin3;	// L800
      s2_sin3 = v567;	// L801
      float v569 = s2_cos;	// L802
      float s2_w1r;	// L803
      s2_w1r = v569;	// L804
      float v571 = s2_sin;	// L805
      float v572 = -(v571);	// L806
      float s2_w1i;	// L807
      s2_w1i = v572;	// L808
      float v574 = s2_cos2;	// L809
      float s2_w2r;	// L810
      s2_w2r = v574;	// L811
      float v576 = s2_sin2;	// L812
      float v577 = -(v576);	// L813
      float s2_w2i;	// L814
      s2_w2i = v577;	// L815
      float v579 = s2_cos3;	// L816
      float s2_w3r;	// L817
      s2_w3r = v579;	// L818
      float v581 = s2_sin3;	// L819
      float v582 = -(v581);	// L820
      float s2_w3i;	// L821
      s2_w3i = v582;	// L822
      float v584 = s2_br;	// L823
      float v585 = s2_w1r;	// L824
      float v586 = v584 * v585;	// L825
      float v587 = s2_bi;	// L826
      float v588 = s2_w1i;	// L827
      float v589 = v587 * v588;	// L828
      float v590 = v586 - v589;	// L829
      float s2_bpr;	// L830
      s2_bpr = v590;	// L831
      float v592 = s2_br;	// L832
      float v593 = s2_w1i;	// L833
      float v594 = v592 * v593;	// L834
      float v595 = s2_bi;	// L835
      float v596 = s2_w1r;	// L836
      float v597 = v595 * v596;	// L837
      float v598 = v594 + v597;	// L838
      float s2_bpi;	// L839
      s2_bpi = v598;	// L840
      float v600 = s2_cr;	// L841
      float v601 = s2_w2r;	// L842
      float v602 = v600 * v601;	// L843
      float v603 = s2_ci;	// L844
      float v604 = s2_w2i;	// L845
      float v605 = v603 * v604;	// L846
      float v606 = v602 - v605;	// L847
      float s2_cpr;	// L848
      s2_cpr = v606;	// L849
      float v608 = s2_cr;	// L850
      float v609 = s2_w2i;	// L851
      float v610 = v608 * v609;	// L852
      float v611 = s2_ci;	// L853
      float v612 = s2_w2r;	// L854
      float v613 = v611 * v612;	// L855
      float v614 = v610 + v613;	// L856
      float s2_cpi;	// L857
      s2_cpi = v614;	// L858
      float v616 = s2_dr;	// L859
      float v617 = s2_w3r;	// L860
      float v618 = v616 * v617;	// L861
      float v619 = s2_di;	// L862
      float v620 = s2_w3i;	// L863
      float v621 = v619 * v620;	// L864
      float v622 = v618 - v621;	// L865
      float s2_dpr;	// L866
      s2_dpr = v622;	// L867
      float v624 = s2_dr;	// L868
      float v625 = s2_w3i;	// L869
      float v626 = v624 * v625;	// L870
      float v627 = s2_di;	// L871
      float v628 = s2_w3r;	// L872
      float v629 = v627 * v628;	// L873
      float v630 = v626 + v629;	// L874
      float s2_dpi;	// L875
      s2_dpi = v630;	// L876
      float v632 = s2_ar;	// L877
      float v633 = s2_cpr;	// L878
      float v634 = v632 + v633;	// L879
      float s2_t0r;	// L880
      s2_t0r = v634;	// L881
      float v636 = s2_ai;	// L882
      float v637 = s2_cpi;	// L883
      float v638 = v636 + v637;	// L884
      float s2_t0i;	// L885
      s2_t0i = v638;	// L886
      float v640 = s2_ar;	// L887
      float v641 = s2_cpr;	// L888
      float v642 = v640 - v641;	// L889
      float s2_t1r;	// L890
      s2_t1r = v642;	// L891
      float v644 = s2_ai;	// L892
      float v645 = s2_cpi;	// L893
      float v646 = v644 - v645;	// L894
      float s2_t1i;	// L895
      s2_t1i = v646;	// L896
      float v648 = s2_bpr;	// L897
      float v649 = s2_dpr;	// L898
      float v650 = v648 + v649;	// L899
      float s2_t2r;	// L900
      s2_t2r = v650;	// L901
      float v652 = s2_bpi;	// L902
      float v653 = s2_dpi;	// L903
      float v654 = v652 + v653;	// L904
      float s2_t2i;	// L905
      s2_t2i = v654;	// L906
      float v656 = s2_bpr;	// L907
      float v657 = s2_dpr;	// L908
      float v658 = v656 - v657;	// L909
      float s2_t3r;	// L910
      s2_t3r = v658;	// L911
      float v660 = s2_bpi;	// L912
      float v661 = s2_dpi;	// L913
      float v662 = v660 - v661;	// L914
      float s2_t3i;	// L915
      s2_t3i = v662;	// L916
      float v664 = s2_t0r;	// L917
      float v665 = s2_t2r;	// L918
      float v666 = v664 + v665;	// L919
      int v667 = idx01;	// L920
      int v668 = v667;	// L921
      buf_real[v668] = v666;	// L922
      float v669 = s2_t0i;	// L923
      float v670 = s2_t2i;	// L924
      float v671 = v669 + v670;	// L925
      int v672 = idx01;	// L926
      int v673 = v672;	// L927
      buf_imag[v673] = v671;	// L928
      float v674 = s2_t1r;	// L929
      float v675 = s2_t3i;	// L930
      float v676 = v674 + v675;	// L931
      int v677 = idx11;	// L932
      int v678 = v677;	// L933
      buf_real[v678] = v676;	// L934
      float v679 = s2_t1i;	// L935
      float v680 = s2_t3r;	// L936
      float v681 = v679 - v680;	// L937
      int v682 = idx11;	// L938
      int v683 = v682;	// L939
      buf_imag[v683] = v681;	// L940
      float v684 = s2_t0r;	// L941
      float v685 = s2_t2r;	// L942
      float v686 = v684 - v685;	// L943
      int v687 = idx21;	// L944
      int v688 = v687;	// L945
      buf_real[v688] = v686;	// L946
      float v689 = s2_t0i;	// L947
      float v690 = s2_t2i;	// L948
      float v691 = v689 - v690;	// L949
      int v692 = idx21;	// L950
      int v693 = v692;	// L951
      buf_imag[v693] = v691;	// L952
      float v694 = s2_t1r;	// L953
      float v695 = s2_t3i;	// L954
      float v696 = v694 - v695;	// L955
      int v697 = idx31;	// L956
      int v698 = v697;	// L957
      buf_real[v698] = v696;	// L958
      float v699 = s2_t1i;	// L959
      float v700 = s2_t3r;	// L960
      float v701 = v699 + v700;	// L961
      int v702 = idx31;	// L962
      int v703 = v702;	// L963
      buf_imag[v703] = v701;	// L964
    }
  }
  l_S_g3_5_g3: for (int g3 = 0; g3 < 16; g3++) {	// L967
    l_S_j3_5_j3: for (int j3 = 0; j3 < 16; j3++) {	// L968
      int v706 = g3;	// L969
      int v707 = v706 * 64;	// L973
      int v708 = v707;	// L974
      int k3;	// L975
      k3 = v708;	// L976
      int v710 = k3;	// L977
      int v711 = v710;	// L978
      int v712 = j3;	// L979
      int v713 = v711 + v712;	// L980
      int v714 = v713;	// L981
      int idx02;	// L982
      idx02 = v714;	// L983
      int v716 = idx02;	// L984
      int v717 = v716;	// L985
      int v718 = v717 + 16;	// L989
      int v719 = v718;	// L990
      int idx12;	// L991
      idx12 = v719;	// L992
      int v721 = idx12;	// L993
      int v722 = v721;	// L994
      int v723 = v722 + 16;	// L998
      int v724 = v723;	// L999
      int idx22;	// L1000
      idx22 = v724;	// L1001
      int v726 = idx22;	// L1002
      int v727 = v726;	// L1003
      int v728 = v727 + 16;	// L1007
      int v729 = v728;	// L1008
      int idx32;	// L1009
      idx32 = v729;	// L1010
      int v731 = idx02;	// L1011
      int v732 = v731;	// L1012
      float v733 = buf_real[v732];	// L1013
      float s3_ar;	// L1014
      s3_ar = v733;	// L1015
      int v735 = idx02;	// L1016
      int v736 = v735;	// L1017
      float v737 = buf_imag[v736];	// L1018
      float s3_ai;	// L1019
      s3_ai = v737;	// L1020
      int v739 = idx12;	// L1021
      int v740 = v739;	// L1022
      float v741 = buf_real[v740];	// L1023
      float s3_br;	// L1024
      s3_br = v741;	// L1025
      int v743 = idx12;	// L1026
      int v744 = v743;	// L1027
      float v745 = buf_imag[v744];	// L1028
      float s3_bi;	// L1029
      s3_bi = v745;	// L1030
      int v747 = idx22;	// L1031
      int v748 = v747;	// L1032
      float v749 = buf_real[v748];	// L1033
      float s3_cr;	// L1034
      s3_cr = v749;	// L1035
      int v751 = idx22;	// L1036
      int v752 = v751;	// L1037
      float v753 = buf_imag[v752];	// L1038
      float s3_ci;	// L1039
      s3_ci = v753;	// L1040
      int v755 = idx32;	// L1041
      int v756 = v755;	// L1042
      float v757 = buf_real[v756];	// L1043
      float s3_dr;	// L1044
      s3_dr = v757;	// L1045
      int v759 = idx32;	// L1046
      int v760 = v759;	// L1047
      float v761 = buf_imag[v760];	// L1048
      float s3_di;	// L1049
      s3_di = v761;	// L1050
      int v763 = j3;	// L1051
      float v764 = v763;	// L1052
      float s3_jf;	// L1053
      s3_jf = v764;	// L1054
      float v766 = s3_jf;	// L1055
      float v767 = v766 * 0.098175;	// L1058
      float s3_x;	// L1059
      s3_x = v767;	// L1060
      float v769 = s3_x;	// L1061
      float v770 = v769 * v769;	// L1063
      float s3_x2;	// L1064
      s3_x2 = v770;	// L1065
      float v772 = s3_x2;	// L1066
      float v773 = s3_x;	// L1067
      float v774 = v772 * v773;	// L1068
      float s3_x3;	// L1069
      s3_x3 = v774;	// L1070
      float v776 = s3_x2;	// L1071
      float v777 = v776 * v776;	// L1073
      float s3_x4;	// L1074
      s3_x4 = v777;	// L1075
      float v779 = s3_x4;	// L1076
      float v780 = s3_x;	// L1077
      float v781 = v779 * v780;	// L1078
      float s3_x5;	// L1079
      s3_x5 = v781;	// L1080
      float v783 = s3_x4;	// L1081
      float v784 = s3_x2;	// L1082
      float v785 = v783 * v784;	// L1083
      float s3_x6;	// L1084
      s3_x6 = v785;	// L1085
      float v787 = s3_x6;	// L1086
      float v788 = s3_x;	// L1087
      float v789 = v787 * v788;	// L1088
      float s3_x7;	// L1089
      s3_x7 = v789;	// L1090
      float v791 = s3_x4;	// L1091
      float v792 = v791 * v791;	// L1093
      float s3_x8;	// L1094
      s3_x8 = v792;	// L1095
      float v794 = s3_x8;	// L1096
      float v795 = s3_x;	// L1097
      float v796 = v794 * v795;	// L1098
      float s3_x9;	// L1099
      s3_x9 = v796;	// L1100
      float v798 = s3_x8;	// L1101
      float v799 = s3_x2;	// L1102
      float v800 = v798 * v799;	// L1103
      float s3_x10;	// L1104
      s3_x10 = v800;	// L1105
      float v802 = s3_x10;	// L1106
      float v803 = s3_x;	// L1107
      float v804 = v802 * v803;	// L1108
      float s3_x11;	// L1109
      s3_x11 = v804;	// L1110
      float v806 = s3_x2;	// L1111
      float v807 = v806 / 2.000000;	// L1114
      float v808 = 1.000000 - v807;	// L1117
      float v809 = s3_x4;	// L1118
      float v810 = v809 / 24.000000;	// L1121
      float v811 = v808 + v810;	// L1122
      float v812 = s3_x6;	// L1123
      float v813 = v812 / 720.000000;	// L1126
      float v814 = v811 - v813;	// L1127
      float v815 = s3_x8;	// L1128
      float v816 = v815 / 40320.000000;	// L1131
      float v817 = v814 + v816;	// L1132
      float v818 = s3_x10;	// L1133
      float v819 = v818 / 3628800.000000;	// L1136
      float v820 = v817 - v819;	// L1137
      float s3_cos;	// L1138
      s3_cos = v820;	// L1139
      float v822 = s3_x;	// L1140
      float v823 = s3_x3;	// L1141
      float v824 = v823 / 6.000000;	// L1144
      float v825 = v822 - v824;	// L1145
      float v826 = s3_x5;	// L1146
      float v827 = v826 / 120.000000;	// L1149
      float v828 = v825 + v827;	// L1150
      float v829 = s3_x7;	// L1151
      float v830 = v829 / 5040.000000;	// L1154
      float v831 = v828 - v830;	// L1155
      float v832 = s3_x9;	// L1156
      float v833 = v832 / 362880.000000;	// L1159
      float v834 = v831 + v833;	// L1160
      float v835 = s3_x11;	// L1161
      float v836 = v835 / 39916800.000000;	// L1164
      float v837 = v834 - v836;	// L1165
      float s3_sin;	// L1166
      s3_sin = v837;	// L1167
      float v839 = s3_cos;	// L1168
      float v840 = v839 * v839;	// L1170
      float v841 = s3_sin;	// L1171
      float v842 = v841 * v841;	// L1173
      float v843 = v840 - v842;	// L1174
      float s3_cos2;	// L1175
      s3_cos2 = v843;	// L1176
      float v845 = s3_sin;	// L1177
      float v846 = v845  << 1.000000;	// L1180
      float v847 = s3_cos;	// L1181
      float v848 = v846 * v847;	// L1182
      float s3_sin2;	// L1183
      s3_sin2 = v848;	// L1184
      float v850 = s3_cos2;	// L1185
      float v851 = s3_cos;	// L1186
      float v852 = v850 * v851;	// L1187
      float v853 = s3_sin2;	// L1188
      float v854 = s3_sin;	// L1189
      float v855 = v853 * v854;	// L1190
      float v856 = v852 - v855;	// L1191
      float s3_cos3;	// L1192
      s3_cos3 = v856;	// L1193
      float v858 = s3_sin2;	// L1194
      float v859 = s3_cos;	// L1195
      float v860 = v858 * v859;	// L1196
      float v861 = s3_cos2;	// L1197
      float v862 = s3_sin;	// L1198
      float v863 = v861 * v862;	// L1199
      float v864 = v860 + v863;	// L1200
      float s3_sin3;	// L1201
      s3_sin3 = v864;	// L1202
      float v866 = s3_cos;	// L1203
      float s3_w1r;	// L1204
      s3_w1r = v866;	// L1205
      float v868 = s3_sin;	// L1206
      float v869 = -(v868);	// L1207
      float s3_w1i;	// L1208
      s3_w1i = v869;	// L1209
      float v871 = s3_cos2;	// L1210
      float s3_w2r;	// L1211
      s3_w2r = v871;	// L1212
      float v873 = s3_sin2;	// L1213
      float v874 = -(v873);	// L1214
      float s3_w2i;	// L1215
      s3_w2i = v874;	// L1216
      float v876 = s3_cos3;	// L1217
      float s3_w3r;	// L1218
      s3_w3r = v876;	// L1219
      float v878 = s3_sin3;	// L1220
      float v879 = -(v878);	// L1221
      float s3_w3i;	// L1222
      s3_w3i = v879;	// L1223
      float v881 = s3_br;	// L1224
      float v882 = s3_w1r;	// L1225
      float v883 = v881 * v882;	// L1226
      float v884 = s3_bi;	// L1227
      float v885 = s3_w1i;	// L1228
      float v886 = v884 * v885;	// L1229
      float v887 = v883 - v886;	// L1230
      float s3_bpr;	// L1231
      s3_bpr = v887;	// L1232
      float v889 = s3_br;	// L1233
      float v890 = s3_w1i;	// L1234
      float v891 = v889 * v890;	// L1235
      float v892 = s3_bi;	// L1236
      float v893 = s3_w1r;	// L1237
      float v894 = v892 * v893;	// L1238
      float v895 = v891 + v894;	// L1239
      float s3_bpi;	// L1240
      s3_bpi = v895;	// L1241
      float v897 = s3_cr;	// L1242
      float v898 = s3_w2r;	// L1243
      float v899 = v897 * v898;	// L1244
      float v900 = s3_ci;	// L1245
      float v901 = s3_w2i;	// L1246
      float v902 = v900 * v901;	// L1247
      float v903 = v899 - v902;	// L1248
      float s3_cpr;	// L1249
      s3_cpr = v903;	// L1250
      float v905 = s3_cr;	// L1251
      float v906 = s3_w2i;	// L1252
      float v907 = v905 * v906;	// L1253
      float v908 = s3_ci;	// L1254
      float v909 = s3_w2r;	// L1255
      float v910 = v908 * v909;	// L1256
      float v911 = v907 + v910;	// L1257
      float s3_cpi;	// L1258
      s3_cpi = v911;	// L1259
      float v913 = s3_dr;	// L1260
      float v914 = s3_w3r;	// L1261
      float v915 = v913 * v914;	// L1262
      float v916 = s3_di;	// L1263
      float v917 = s3_w3i;	// L1264
      float v918 = v916 * v917;	// L1265
      float v919 = v915 - v918;	// L1266
      float s3_dpr;	// L1267
      s3_dpr = v919;	// L1268
      float v921 = s3_dr;	// L1269
      float v922 = s3_w3i;	// L1270
      float v923 = v921 * v922;	// L1271
      float v924 = s3_di;	// L1272
      float v925 = s3_w3r;	// L1273
      float v926 = v924 * v925;	// L1274
      float v927 = v923 + v926;	// L1275
      float s3_dpi;	// L1276
      s3_dpi = v927;	// L1277
      float v929 = s3_ar;	// L1278
      float v930 = s3_cpr;	// L1279
      float v931 = v929 + v930;	// L1280
      float s3_t0r;	// L1281
      s3_t0r = v931;	// L1282
      float v933 = s3_ai;	// L1283
      float v934 = s3_cpi;	// L1284
      float v935 = v933 + v934;	// L1285
      float s3_t0i;	// L1286
      s3_t0i = v935;	// L1287
      float v937 = s3_ar;	// L1288
      float v938 = s3_cpr;	// L1289
      float v939 = v937 - v938;	// L1290
      float s3_t1r;	// L1291
      s3_t1r = v939;	// L1292
      float v941 = s3_ai;	// L1293
      float v942 = s3_cpi;	// L1294
      float v943 = v941 - v942;	// L1295
      float s3_t1i;	// L1296
      s3_t1i = v943;	// L1297
      float v945 = s3_bpr;	// L1298
      float v946 = s3_dpr;	// L1299
      float v947 = v945 + v946;	// L1300
      float s3_t2r;	// L1301
      s3_t2r = v947;	// L1302
      float v949 = s3_bpi;	// L1303
      float v950 = s3_dpi;	// L1304
      float v951 = v949 + v950;	// L1305
      float s3_t2i;	// L1306
      s3_t2i = v951;	// L1307
      float v953 = s3_bpr;	// L1308
      float v954 = s3_dpr;	// L1309
      float v955 = v953 - v954;	// L1310
      float s3_t3r;	// L1311
      s3_t3r = v955;	// L1312
      float v957 = s3_bpi;	// L1313
      float v958 = s3_dpi;	// L1314
      float v959 = v957 - v958;	// L1315
      float s3_t3i;	// L1316
      s3_t3i = v959;	// L1317
      float v961 = s3_t0r;	// L1318
      float v962 = s3_t2r;	// L1319
      float v963 = v961 + v962;	// L1320
      int v964 = idx02;	// L1321
      int v965 = v964;	// L1322
      buf_real[v965] = v963;	// L1323
      float v966 = s3_t0i;	// L1324
      float v967 = s3_t2i;	// L1325
      float v968 = v966 + v967;	// L1326
      int v969 = idx02;	// L1327
      int v970 = v969;	// L1328
      buf_imag[v970] = v968;	// L1329
      float v971 = s3_t1r;	// L1330
      float v972 = s3_t3i;	// L1331
      float v973 = v971 + v972;	// L1332
      int v974 = idx12;	// L1333
      int v975 = v974;	// L1334
      buf_real[v975] = v973;	// L1335
      float v976 = s3_t1i;	// L1336
      float v977 = s3_t3r;	// L1337
      float v978 = v976 - v977;	// L1338
      int v979 = idx12;	// L1339
      int v980 = v979;	// L1340
      buf_imag[v980] = v978;	// L1341
      float v981 = s3_t0r;	// L1342
      float v982 = s3_t2r;	// L1343
      float v983 = v981 - v982;	// L1344
      int v984 = idx22;	// L1345
      int v985 = v984;	// L1346
      buf_real[v985] = v983;	// L1347
      float v986 = s3_t0i;	// L1348
      float v987 = s3_t2i;	// L1349
      float v988 = v986 - v987;	// L1350
      int v989 = idx22;	// L1351
      int v990 = v989;	// L1352
      buf_imag[v990] = v988;	// L1353
      float v991 = s3_t1r;	// L1354
      float v992 = s3_t3i;	// L1355
      float v993 = v991 - v992;	// L1356
      int v994 = idx32;	// L1357
      int v995 = v994;	// L1358
      buf_real[v995] = v993;	// L1359
      float v996 = s3_t1i;	// L1360
      float v997 = s3_t3r;	// L1361
      float v998 = v996 + v997;	// L1362
      int v999 = idx32;	// L1363
      int v1000 = v999;	// L1364
      buf_imag[v1000] = v998;	// L1365
    }
  }
  l_S_g4_7_g4: for (int g4 = 0; g4 < 4; g4++) {	// L1368
    l_S_j4_7_j4: for (int j4 = 0; j4 < 64; j4++) {	// L1369
      int v1003 = g4;	// L1370
      int v1004 = v1003 * 256;	// L1374
      int v1005 = v1004;	// L1375
      int k4;	// L1376
      k4 = v1005;	// L1377
      int v1007 = k4;	// L1378
      int v1008 = v1007;	// L1379
      int v1009 = j4;	// L1380
      int v1010 = v1008 + v1009;	// L1381
      int v1011 = v1010;	// L1382
      int idx03;	// L1383
      idx03 = v1011;	// L1384
      int v1013 = idx03;	// L1385
      int v1014 = v1013;	// L1386
      int v1015 = v1014 + 64;	// L1390
      int v1016 = v1015;	// L1391
      int idx13;	// L1392
      idx13 = v1016;	// L1393
      int v1018 = idx13;	// L1394
      int v1019 = v1018;	// L1395
      int v1020 = v1019 + 64;	// L1399
      int v1021 = v1020;	// L1400
      int idx23;	// L1401
      idx23 = v1021;	// L1402
      int v1023 = idx23;	// L1403
      int v1024 = v1023;	// L1404
      int v1025 = v1024 + 64;	// L1408
      int v1026 = v1025;	// L1409
      int idx33;	// L1410
      idx33 = v1026;	// L1411
      int v1028 = idx03;	// L1412
      int v1029 = v1028;	// L1413
      float v1030 = buf_real[v1029];	// L1414
      float s4_ar;	// L1415
      s4_ar = v1030;	// L1416
      int v1032 = idx03;	// L1417
      int v1033 = v1032;	// L1418
      float v1034 = buf_imag[v1033];	// L1419
      float s4_ai;	// L1420
      s4_ai = v1034;	// L1421
      int v1036 = idx13;	// L1422
      int v1037 = v1036;	// L1423
      float v1038 = buf_real[v1037];	// L1424
      float s4_br;	// L1425
      s4_br = v1038;	// L1426
      int v1040 = idx13;	// L1427
      int v1041 = v1040;	// L1428
      float v1042 = buf_imag[v1041];	// L1429
      float s4_bi;	// L1430
      s4_bi = v1042;	// L1431
      int v1044 = idx23;	// L1432
      int v1045 = v1044;	// L1433
      float v1046 = buf_real[v1045];	// L1434
      float s4_cr;	// L1435
      s4_cr = v1046;	// L1436
      int v1048 = idx23;	// L1437
      int v1049 = v1048;	// L1438
      float v1050 = buf_imag[v1049];	// L1439
      float s4_ci;	// L1440
      s4_ci = v1050;	// L1441
      int v1052 = idx33;	// L1442
      int v1053 = v1052;	// L1443
      float v1054 = buf_real[v1053];	// L1444
      float s4_dr;	// L1445
      s4_dr = v1054;	// L1446
      int v1056 = idx33;	// L1447
      int v1057 = v1056;	// L1448
      float v1058 = buf_imag[v1057];	// L1449
      float s4_di;	// L1450
      s4_di = v1058;	// L1451
      int v1060 = j4;	// L1452
      float v1061 = v1060;	// L1453
      float s4_jf;	// L1454
      s4_jf = v1061;	// L1455
      float v1063 = s4_jf;	// L1456
      float v1064 = v1063 * 0.024544;	// L1459
      float s4_x;	// L1460
      s4_x = v1064;	// L1461
      float v1066 = s4_x;	// L1462
      float v1067 = v1066 * v1066;	// L1464
      float s4_x2;	// L1465
      s4_x2 = v1067;	// L1466
      float v1069 = s4_x2;	// L1467
      float v1070 = s4_x;	// L1468
      float v1071 = v1069 * v1070;	// L1469
      float s4_x3;	// L1470
      s4_x3 = v1071;	// L1471
      float v1073 = s4_x2;	// L1472
      float v1074 = v1073 * v1073;	// L1474
      float s4_x4;	// L1475
      s4_x4 = v1074;	// L1476
      float v1076 = s4_x4;	// L1477
      float v1077 = s4_x;	// L1478
      float v1078 = v1076 * v1077;	// L1479
      float s4_x5;	// L1480
      s4_x5 = v1078;	// L1481
      float v1080 = s4_x4;	// L1482
      float v1081 = s4_x2;	// L1483
      float v1082 = v1080 * v1081;	// L1484
      float s4_x6;	// L1485
      s4_x6 = v1082;	// L1486
      float v1084 = s4_x6;	// L1487
      float v1085 = s4_x;	// L1488
      float v1086 = v1084 * v1085;	// L1489
      float s4_x7;	// L1490
      s4_x7 = v1086;	// L1491
      float v1088 = s4_x4;	// L1492
      float v1089 = v1088 * v1088;	// L1494
      float s4_x8;	// L1495
      s4_x8 = v1089;	// L1496
      float v1091 = s4_x8;	// L1497
      float v1092 = s4_x;	// L1498
      float v1093 = v1091 * v1092;	// L1499
      float s4_x9;	// L1500
      s4_x9 = v1093;	// L1501
      float v1095 = s4_x8;	// L1502
      float v1096 = s4_x2;	// L1503
      float v1097 = v1095 * v1096;	// L1504
      float s4_x10;	// L1505
      s4_x10 = v1097;	// L1506
      float v1099 = s4_x10;	// L1507
      float v1100 = s4_x;	// L1508
      float v1101 = v1099 * v1100;	// L1509
      float s4_x11;	// L1510
      s4_x11 = v1101;	// L1511
      float v1103 = s4_x2;	// L1512
      float v1104 = v1103 / 2.000000;	// L1515
      float v1105 = 1.000000 - v1104;	// L1518
      float v1106 = s4_x4;	// L1519
      float v1107 = v1106 / 24.000000;	// L1522
      float v1108 = v1105 + v1107;	// L1523
      float v1109 = s4_x6;	// L1524
      float v1110 = v1109 / 720.000000;	// L1527
      float v1111 = v1108 - v1110;	// L1528
      float v1112 = s4_x8;	// L1529
      float v1113 = v1112 / 40320.000000;	// L1532
      float v1114 = v1111 + v1113;	// L1533
      float v1115 = s4_x10;	// L1534
      float v1116 = v1115 / 3628800.000000;	// L1537
      float v1117 = v1114 - v1116;	// L1538
      float s4_cos;	// L1539
      s4_cos = v1117;	// L1540
      float v1119 = s4_x;	// L1541
      float v1120 = s4_x3;	// L1542
      float v1121 = v1120 / 6.000000;	// L1545
      float v1122 = v1119 - v1121;	// L1546
      float v1123 = s4_x5;	// L1547
      float v1124 = v1123 / 120.000000;	// L1550
      float v1125 = v1122 + v1124;	// L1551
      float v1126 = s4_x7;	// L1552
      float v1127 = v1126 / 5040.000000;	// L1555
      float v1128 = v1125 - v1127;	// L1556
      float v1129 = s4_x9;	// L1557
      float v1130 = v1129 / 362880.000000;	// L1560
      float v1131 = v1128 + v1130;	// L1561
      float v1132 = s4_x11;	// L1562
      float v1133 = v1132 / 39916800.000000;	// L1565
      float v1134 = v1131 - v1133;	// L1566
      float s4_sin;	// L1567
      s4_sin = v1134;	// L1568
      float v1136 = s4_cos;	// L1569
      float v1137 = v1136 * v1136;	// L1571
      float v1138 = s4_sin;	// L1572
      float v1139 = v1138 * v1138;	// L1574
      float v1140 = v1137 - v1139;	// L1575
      float s4_cos2;	// L1576
      s4_cos2 = v1140;	// L1577
      float v1142 = s4_sin;	// L1578
      float v1143 = v1142  << 1.000000;	// L1581
      float v1144 = s4_cos;	// L1582
      float v1145 = v1143 * v1144;	// L1583
      float s4_sin2;	// L1584
      s4_sin2 = v1145;	// L1585
      float v1147 = s4_cos2;	// L1586
      float v1148 = s4_cos;	// L1587
      float v1149 = v1147 * v1148;	// L1588
      float v1150 = s4_sin2;	// L1589
      float v1151 = s4_sin;	// L1590
      float v1152 = v1150 * v1151;	// L1591
      float v1153 = v1149 - v1152;	// L1592
      float s4_cos3;	// L1593
      s4_cos3 = v1153;	// L1594
      float v1155 = s4_sin2;	// L1595
      float v1156 = s4_cos;	// L1596
      float v1157 = v1155 * v1156;	// L1597
      float v1158 = s4_cos2;	// L1598
      float v1159 = s4_sin;	// L1599
      float v1160 = v1158 * v1159;	// L1600
      float v1161 = v1157 + v1160;	// L1601
      float s4_sin3;	// L1602
      s4_sin3 = v1161;	// L1603
      float v1163 = s4_cos;	// L1604
      float s4_w1r;	// L1605
      s4_w1r = v1163;	// L1606
      float v1165 = s4_sin;	// L1607
      float v1166 = -(v1165);	// L1608
      float s4_w1i;	// L1609
      s4_w1i = v1166;	// L1610
      float v1168 = s4_cos2;	// L1611
      float s4_w2r;	// L1612
      s4_w2r = v1168;	// L1613
      float v1170 = s4_sin2;	// L1614
      float v1171 = -(v1170);	// L1615
      float s4_w2i;	// L1616
      s4_w2i = v1171;	// L1617
      float v1173 = s4_cos3;	// L1618
      float s4_w3r;	// L1619
      s4_w3r = v1173;	// L1620
      float v1175 = s4_sin3;	// L1621
      float v1176 = -(v1175);	// L1622
      float s4_w3i;	// L1623
      s4_w3i = v1176;	// L1624
      float v1178 = s4_br;	// L1625
      float v1179 = s4_w1r;	// L1626
      float v1180 = v1178 * v1179;	// L1627
      float v1181 = s4_bi;	// L1628
      float v1182 = s4_w1i;	// L1629
      float v1183 = v1181 * v1182;	// L1630
      float v1184 = v1180 - v1183;	// L1631
      float s4_bpr;	// L1632
      s4_bpr = v1184;	// L1633
      float v1186 = s4_br;	// L1634
      float v1187 = s4_w1i;	// L1635
      float v1188 = v1186 * v1187;	// L1636
      float v1189 = s4_bi;	// L1637
      float v1190 = s4_w1r;	// L1638
      float v1191 = v1189 * v1190;	// L1639
      float v1192 = v1188 + v1191;	// L1640
      float s4_bpi;	// L1641
      s4_bpi = v1192;	// L1642
      float v1194 = s4_cr;	// L1643
      float v1195 = s4_w2r;	// L1644
      float v1196 = v1194 * v1195;	// L1645
      float v1197 = s4_ci;	// L1646
      float v1198 = s4_w2i;	// L1647
      float v1199 = v1197 * v1198;	// L1648
      float v1200 = v1196 - v1199;	// L1649
      float s4_cpr;	// L1650
      s4_cpr = v1200;	// L1651
      float v1202 = s4_cr;	// L1652
      float v1203 = s4_w2i;	// L1653
      float v1204 = v1202 * v1203;	// L1654
      float v1205 = s4_ci;	// L1655
      float v1206 = s4_w2r;	// L1656
      float v1207 = v1205 * v1206;	// L1657
      float v1208 = v1204 + v1207;	// L1658
      float s4_cpi;	// L1659
      s4_cpi = v1208;	// L1660
      float v1210 = s4_dr;	// L1661
      float v1211 = s4_w3r;	// L1662
      float v1212 = v1210 * v1211;	// L1663
      float v1213 = s4_di;	// L1664
      float v1214 = s4_w3i;	// L1665
      float v1215 = v1213 * v1214;	// L1666
      float v1216 = v1212 - v1215;	// L1667
      float s4_dpr;	// L1668
      s4_dpr = v1216;	// L1669
      float v1218 = s4_dr;	// L1670
      float v1219 = s4_w3i;	// L1671
      float v1220 = v1218 * v1219;	// L1672
      float v1221 = s4_di;	// L1673
      float v1222 = s4_w3r;	// L1674
      float v1223 = v1221 * v1222;	// L1675
      float v1224 = v1220 + v1223;	// L1676
      float s4_dpi;	// L1677
      s4_dpi = v1224;	// L1678
      float v1226 = s4_ar;	// L1679
      float v1227 = s4_cpr;	// L1680
      float v1228 = v1226 + v1227;	// L1681
      float s4_t0r;	// L1682
      s4_t0r = v1228;	// L1683
      float v1230 = s4_ai;	// L1684
      float v1231 = s4_cpi;	// L1685
      float v1232 = v1230 + v1231;	// L1686
      float s4_t0i;	// L1687
      s4_t0i = v1232;	// L1688
      float v1234 = s4_ar;	// L1689
      float v1235 = s4_cpr;	// L1690
      float v1236 = v1234 - v1235;	// L1691
      float s4_t1r;	// L1692
      s4_t1r = v1236;	// L1693
      float v1238 = s4_ai;	// L1694
      float v1239 = s4_cpi;	// L1695
      float v1240 = v1238 - v1239;	// L1696
      float s4_t1i;	// L1697
      s4_t1i = v1240;	// L1698
      float v1242 = s4_bpr;	// L1699
      float v1243 = s4_dpr;	// L1700
      float v1244 = v1242 + v1243;	// L1701
      float s4_t2r;	// L1702
      s4_t2r = v1244;	// L1703
      float v1246 = s4_bpi;	// L1704
      float v1247 = s4_dpi;	// L1705
      float v1248 = v1246 + v1247;	// L1706
      float s4_t2i;	// L1707
      s4_t2i = v1248;	// L1708
      float v1250 = s4_bpr;	// L1709
      float v1251 = s4_dpr;	// L1710
      float v1252 = v1250 - v1251;	// L1711
      float s4_t3r;	// L1712
      s4_t3r = v1252;	// L1713
      float v1254 = s4_bpi;	// L1714
      float v1255 = s4_dpi;	// L1715
      float v1256 = v1254 - v1255;	// L1716
      float s4_t3i;	// L1717
      s4_t3i = v1256;	// L1718
      float v1258 = s4_t0r;	// L1719
      float v1259 = s4_t2r;	// L1720
      float v1260 = v1258 + v1259;	// L1721
      int v1261 = idx03;	// L1722
      int v1262 = v1261;	// L1723
      buf_real[v1262] = v1260;	// L1724
      float v1263 = s4_t0i;	// L1725
      float v1264 = s4_t2i;	// L1726
      float v1265 = v1263 + v1264;	// L1727
      int v1266 = idx03;	// L1728
      int v1267 = v1266;	// L1729
      buf_imag[v1267] = v1265;	// L1730
      float v1268 = s4_t1r;	// L1731
      float v1269 = s4_t3i;	// L1732
      float v1270 = v1268 + v1269;	// L1733
      int v1271 = idx13;	// L1734
      int v1272 = v1271;	// L1735
      buf_real[v1272] = v1270;	// L1736
      float v1273 = s4_t1i;	// L1737
      float v1274 = s4_t3r;	// L1738
      float v1275 = v1273 - v1274;	// L1739
      int v1276 = idx13;	// L1740
      int v1277 = v1276;	// L1741
      buf_imag[v1277] = v1275;	// L1742
      float v1278 = s4_t0r;	// L1743
      float v1279 = s4_t2r;	// L1744
      float v1280 = v1278 - v1279;	// L1745
      int v1281 = idx23;	// L1746
      int v1282 = v1281;	// L1747
      buf_real[v1282] = v1280;	// L1748
      float v1283 = s4_t0i;	// L1749
      float v1284 = s4_t2i;	// L1750
      float v1285 = v1283 - v1284;	// L1751
      int v1286 = idx23;	// L1752
      int v1287 = v1286;	// L1753
      buf_imag[v1287] = v1285;	// L1754
      float v1288 = s4_t1r;	// L1755
      float v1289 = s4_t3i;	// L1756
      float v1290 = v1288 - v1289;	// L1757
      int v1291 = idx33;	// L1758
      int v1292 = v1291;	// L1759
      buf_real[v1292] = v1290;	// L1760
      float v1293 = s4_t1i;	// L1761
      float v1294 = s4_t3r;	// L1762
      float v1295 = v1293 + v1294;	// L1763
      int v1296 = idx33;	// L1764
      int v1297 = v1296;	// L1765
      buf_imag[v1297] = v1295;	// L1766
    }
  }
  l_S_g5_9_g5: for (int g5 = 0; g5 < 1; g5++) {	// L1769
    l_S_j5_9_j5: for (int j5 = 0; j5 < 256; j5++) {	// L1770
      int v1300 = g5;	// L1771
      int v1301 = v1300 * 1024;	// L1775
      int v1302 = v1301;	// L1776
      int k5;	// L1777
      k5 = v1302;	// L1778
      int v1304 = k5;	// L1779
      int v1305 = v1304;	// L1780
      int v1306 = j5;	// L1781
      int v1307 = v1305 + v1306;	// L1782
      int v1308 = v1307;	// L1783
      int idx04;	// L1784
      idx04 = v1308;	// L1785
      int v1310 = idx04;	// L1786
      int v1311 = v1310;	// L1787
      int v1312 = v1311 + 256;	// L1791
      int v1313 = v1312;	// L1792
      int idx14;	// L1793
      idx14 = v1313;	// L1794
      int v1315 = idx14;	// L1795
      int v1316 = v1315;	// L1796
      int v1317 = v1316 + 256;	// L1800
      int v1318 = v1317;	// L1801
      int idx24;	// L1802
      idx24 = v1318;	// L1803
      int v1320 = idx24;	// L1804
      int v1321 = v1320;	// L1805
      int v1322 = v1321 + 256;	// L1809
      int v1323 = v1322;	// L1810
      int idx34;	// L1811
      idx34 = v1323;	// L1812
      int v1325 = idx04;	// L1813
      int v1326 = v1325;	// L1814
      float v1327 = buf_real[v1326];	// L1815
      float s5_ar;	// L1816
      s5_ar = v1327;	// L1817
      int v1329 = idx04;	// L1818
      int v1330 = v1329;	// L1819
      float v1331 = buf_imag[v1330];	// L1820
      float s5_ai;	// L1821
      s5_ai = v1331;	// L1822
      int v1333 = idx14;	// L1823
      int v1334 = v1333;	// L1824
      float v1335 = buf_real[v1334];	// L1825
      float s5_br;	// L1826
      s5_br = v1335;	// L1827
      int v1337 = idx14;	// L1828
      int v1338 = v1337;	// L1829
      float v1339 = buf_imag[v1338];	// L1830
      float s5_bi;	// L1831
      s5_bi = v1339;	// L1832
      int v1341 = idx24;	// L1833
      int v1342 = v1341;	// L1834
      float v1343 = buf_real[v1342];	// L1835
      float s5_cr;	// L1836
      s5_cr = v1343;	// L1837
      int v1345 = idx24;	// L1838
      int v1346 = v1345;	// L1839
      float v1347 = buf_imag[v1346];	// L1840
      float s5_ci;	// L1841
      s5_ci = v1347;	// L1842
      int v1349 = idx34;	// L1843
      int v1350 = v1349;	// L1844
      float v1351 = buf_real[v1350];	// L1845
      float s5_dr;	// L1846
      s5_dr = v1351;	// L1847
      int v1353 = idx34;	// L1848
      int v1354 = v1353;	// L1849
      float v1355 = buf_imag[v1354];	// L1850
      float s5_di;	// L1851
      s5_di = v1355;	// L1852
      int v1357 = j5;	// L1853
      float v1358 = v1357;	// L1854
      float s5_jf;	// L1855
      s5_jf = v1358;	// L1856
      float v1360 = s5_jf;	// L1857
      float v1361 = v1360 * 0.006136;	// L1860
      float s5_x;	// L1861
      s5_x = v1361;	// L1862
      float v1363 = s5_x;	// L1863
      float v1364 = v1363 * v1363;	// L1865
      float s5_x2;	// L1866
      s5_x2 = v1364;	// L1867
      float v1366 = s5_x2;	// L1868
      float v1367 = s5_x;	// L1869
      float v1368 = v1366 * v1367;	// L1870
      float s5_x3;	// L1871
      s5_x3 = v1368;	// L1872
      float v1370 = s5_x2;	// L1873
      float v1371 = v1370 * v1370;	// L1875
      float s5_x4;	// L1876
      s5_x4 = v1371;	// L1877
      float v1373 = s5_x4;	// L1878
      float v1374 = s5_x;	// L1879
      float v1375 = v1373 * v1374;	// L1880
      float s5_x5;	// L1881
      s5_x5 = v1375;	// L1882
      float v1377 = s5_x4;	// L1883
      float v1378 = s5_x2;	// L1884
      float v1379 = v1377 * v1378;	// L1885
      float s5_x6;	// L1886
      s5_x6 = v1379;	// L1887
      float v1381 = s5_x6;	// L1888
      float v1382 = s5_x;	// L1889
      float v1383 = v1381 * v1382;	// L1890
      float s5_x7;	// L1891
      s5_x7 = v1383;	// L1892
      float v1385 = s5_x4;	// L1893
      float v1386 = v1385 * v1385;	// L1895
      float s5_x8;	// L1896
      s5_x8 = v1386;	// L1897
      float v1388 = s5_x8;	// L1898
      float v1389 = s5_x;	// L1899
      float v1390 = v1388 * v1389;	// L1900
      float s5_x9;	// L1901
      s5_x9 = v1390;	// L1902
      float v1392 = s5_x8;	// L1903
      float v1393 = s5_x2;	// L1904
      float v1394 = v1392 * v1393;	// L1905
      float s5_x10;	// L1906
      s5_x10 = v1394;	// L1907
      float v1396 = s5_x10;	// L1908
      float v1397 = s5_x;	// L1909
      float v1398 = v1396 * v1397;	// L1910
      float s5_x11;	// L1911
      s5_x11 = v1398;	// L1912
      float v1400 = s5_x2;	// L1913
      float v1401 = v1400 / 2.000000;	// L1916
      float v1402 = 1.000000 - v1401;	// L1919
      float v1403 = s5_x4;	// L1920
      float v1404 = v1403 / 24.000000;	// L1923
      float v1405 = v1402 + v1404;	// L1924
      float v1406 = s5_x6;	// L1925
      float v1407 = v1406 / 720.000000;	// L1928
      float v1408 = v1405 - v1407;	// L1929
      float v1409 = s5_x8;	// L1930
      float v1410 = v1409 / 40320.000000;	// L1933
      float v1411 = v1408 + v1410;	// L1934
      float v1412 = s5_x10;	// L1935
      float v1413 = v1412 / 3628800.000000;	// L1938
      float v1414 = v1411 - v1413;	// L1939
      float s5_cos;	// L1940
      s5_cos = v1414;	// L1941
      float v1416 = s5_x;	// L1942
      float v1417 = s5_x3;	// L1943
      float v1418 = v1417 / 6.000000;	// L1946
      float v1419 = v1416 - v1418;	// L1947
      float v1420 = s5_x5;	// L1948
      float v1421 = v1420 / 120.000000;	// L1951
      float v1422 = v1419 + v1421;	// L1952
      float v1423 = s5_x7;	// L1953
      float v1424 = v1423 / 5040.000000;	// L1956
      float v1425 = v1422 - v1424;	// L1957
      float v1426 = s5_x9;	// L1958
      float v1427 = v1426 / 362880.000000;	// L1961
      float v1428 = v1425 + v1427;	// L1962
      float v1429 = s5_x11;	// L1963
      float v1430 = v1429 / 39916800.000000;	// L1966
      float v1431 = v1428 - v1430;	// L1967
      float s5_sin;	// L1968
      s5_sin = v1431;	// L1969
      float v1433 = s5_cos;	// L1970
      float v1434 = v1433 * v1433;	// L1972
      float v1435 = s5_sin;	// L1973
      float v1436 = v1435 * v1435;	// L1975
      float v1437 = v1434 - v1436;	// L1976
      float s5_cos2;	// L1977
      s5_cos2 = v1437;	// L1978
      float v1439 = s5_sin;	// L1979
      float v1440 = v1439  << 1.000000;	// L1982
      float v1441 = s5_cos;	// L1983
      float v1442 = v1440 * v1441;	// L1984
      float s5_sin2;	// L1985
      s5_sin2 = v1442;	// L1986
      float v1444 = s5_cos2;	// L1987
      float v1445 = s5_cos;	// L1988
      float v1446 = v1444 * v1445;	// L1989
      float v1447 = s5_sin2;	// L1990
      float v1448 = s5_sin;	// L1991
      float v1449 = v1447 * v1448;	// L1992
      float v1450 = v1446 - v1449;	// L1993
      float s5_cos3;	// L1994
      s5_cos3 = v1450;	// L1995
      float v1452 = s5_sin2;	// L1996
      float v1453 = s5_cos;	// L1997
      float v1454 = v1452 * v1453;	// L1998
      float v1455 = s5_cos2;	// L1999
      float v1456 = s5_sin;	// L2000
      float v1457 = v1455 * v1456;	// L2001
      float v1458 = v1454 + v1457;	// L2002
      float s5_sin3;	// L2003
      s5_sin3 = v1458;	// L2004
      float v1460 = s5_cos;	// L2005
      float s5_w1r;	// L2006
      s5_w1r = v1460;	// L2007
      float v1462 = s5_sin;	// L2008
      float v1463 = -(v1462);	// L2009
      float s5_w1i;	// L2010
      s5_w1i = v1463;	// L2011
      float v1465 = s5_cos2;	// L2012
      float s5_w2r;	// L2013
      s5_w2r = v1465;	// L2014
      float v1467 = s5_sin2;	// L2015
      float v1468 = -(v1467);	// L2016
      float s5_w2i;	// L2017
      s5_w2i = v1468;	// L2018
      float v1470 = s5_cos3;	// L2019
      float s5_w3r;	// L2020
      s5_w3r = v1470;	// L2021
      float v1472 = s5_sin3;	// L2022
      float v1473 = -(v1472);	// L2023
      float s5_w3i;	// L2024
      s5_w3i = v1473;	// L2025
      float v1475 = s5_br;	// L2026
      float v1476 = s5_w1r;	// L2027
      float v1477 = v1475 * v1476;	// L2028
      float v1478 = s5_bi;	// L2029
      float v1479 = s5_w1i;	// L2030
      float v1480 = v1478 * v1479;	// L2031
      float v1481 = v1477 - v1480;	// L2032
      float s5_bpr;	// L2033
      s5_bpr = v1481;	// L2034
      float v1483 = s5_br;	// L2035
      float v1484 = s5_w1i;	// L2036
      float v1485 = v1483 * v1484;	// L2037
      float v1486 = s5_bi;	// L2038
      float v1487 = s5_w1r;	// L2039
      float v1488 = v1486 * v1487;	// L2040
      float v1489 = v1485 + v1488;	// L2041
      float s5_bpi;	// L2042
      s5_bpi = v1489;	// L2043
      float v1491 = s5_cr;	// L2044
      float v1492 = s5_w2r;	// L2045
      float v1493 = v1491 * v1492;	// L2046
      float v1494 = s5_ci;	// L2047
      float v1495 = s5_w2i;	// L2048
      float v1496 = v1494 * v1495;	// L2049
      float v1497 = v1493 - v1496;	// L2050
      float s5_cpr;	// L2051
      s5_cpr = v1497;	// L2052
      float v1499 = s5_cr;	// L2053
      float v1500 = s5_w2i;	// L2054
      float v1501 = v1499 * v1500;	// L2055
      float v1502 = s5_ci;	// L2056
      float v1503 = s5_w2r;	// L2057
      float v1504 = v1502 * v1503;	// L2058
      float v1505 = v1501 + v1504;	// L2059
      float s5_cpi;	// L2060
      s5_cpi = v1505;	// L2061
      float v1507 = s5_dr;	// L2062
      float v1508 = s5_w3r;	// L2063
      float v1509 = v1507 * v1508;	// L2064
      float v1510 = s5_di;	// L2065
      float v1511 = s5_w3i;	// L2066
      float v1512 = v1510 * v1511;	// L2067
      float v1513 = v1509 - v1512;	// L2068
      float s5_dpr;	// L2069
      s5_dpr = v1513;	// L2070
      float v1515 = s5_dr;	// L2071
      float v1516 = s5_w3i;	// L2072
      float v1517 = v1515 * v1516;	// L2073
      float v1518 = s5_di;	// L2074
      float v1519 = s5_w3r;	// L2075
      float v1520 = v1518 * v1519;	// L2076
      float v1521 = v1517 + v1520;	// L2077
      float s5_dpi;	// L2078
      s5_dpi = v1521;	// L2079
      float v1523 = s5_ar;	// L2080
      float v1524 = s5_cpr;	// L2081
      float v1525 = v1523 + v1524;	// L2082
      float s5_t0r;	// L2083
      s5_t0r = v1525;	// L2084
      float v1527 = s5_ai;	// L2085
      float v1528 = s5_cpi;	// L2086
      float v1529 = v1527 + v1528;	// L2087
      float s5_t0i;	// L2088
      s5_t0i = v1529;	// L2089
      float v1531 = s5_ar;	// L2090
      float v1532 = s5_cpr;	// L2091
      float v1533 = v1531 - v1532;	// L2092
      float s5_t1r;	// L2093
      s5_t1r = v1533;	// L2094
      float v1535 = s5_ai;	// L2095
      float v1536 = s5_cpi;	// L2096
      float v1537 = v1535 - v1536;	// L2097
      float s5_t1i;	// L2098
      s5_t1i = v1537;	// L2099
      float v1539 = s5_bpr;	// L2100
      float v1540 = s5_dpr;	// L2101
      float v1541 = v1539 + v1540;	// L2102
      float s5_t2r;	// L2103
      s5_t2r = v1541;	// L2104
      float v1543 = s5_bpi;	// L2105
      float v1544 = s5_dpi;	// L2106
      float v1545 = v1543 + v1544;	// L2107
      float s5_t2i;	// L2108
      s5_t2i = v1545;	// L2109
      float v1547 = s5_bpr;	// L2110
      float v1548 = s5_dpr;	// L2111
      float v1549 = v1547 - v1548;	// L2112
      float s5_t3r;	// L2113
      s5_t3r = v1549;	// L2114
      float v1551 = s5_bpi;	// L2115
      float v1552 = s5_dpi;	// L2116
      float v1553 = v1551 - v1552;	// L2117
      float s5_t3i;	// L2118
      s5_t3i = v1553;	// L2119
      float v1555 = s5_t0r;	// L2120
      float v1556 = s5_t2r;	// L2121
      float v1557 = v1555 + v1556;	// L2122
      int v1558 = idx04;	// L2123
      int v1559 = v1558;	// L2124
      buf_real[v1559] = v1557;	// L2125
      float v1560 = s5_t0i;	// L2126
      float v1561 = s5_t2i;	// L2127
      float v1562 = v1560 + v1561;	// L2128
      int v1563 = idx04;	// L2129
      int v1564 = v1563;	// L2130
      buf_imag[v1564] = v1562;	// L2131
      float v1565 = s5_t1r;	// L2132
      float v1566 = s5_t3i;	// L2133
      float v1567 = v1565 + v1566;	// L2134
      int v1568 = idx14;	// L2135
      int v1569 = v1568;	// L2136
      buf_real[v1569] = v1567;	// L2137
      float v1570 = s5_t1i;	// L2138
      float v1571 = s5_t3r;	// L2139
      float v1572 = v1570 - v1571;	// L2140
      int v1573 = idx14;	// L2141
      int v1574 = v1573;	// L2142
      buf_imag[v1574] = v1572;	// L2143
      float v1575 = s5_t0r;	// L2144
      float v1576 = s5_t2r;	// L2145
      float v1577 = v1575 - v1576;	// L2146
      int v1578 = idx24;	// L2147
      int v1579 = v1578;	// L2148
      buf_real[v1579] = v1577;	// L2149
      float v1580 = s5_t0i;	// L2150
      float v1581 = s5_t2i;	// L2151
      float v1582 = v1580 - v1581;	// L2152
      int v1583 = idx24;	// L2153
      int v1584 = v1583;	// L2154
      buf_imag[v1584] = v1582;	// L2155
      float v1585 = s5_t1r;	// L2156
      float v1586 = s5_t3i;	// L2157
      float v1587 = v1585 - v1586;	// L2158
      int v1588 = idx34;	// L2159
      int v1589 = v1588;	// L2160
      buf_real[v1589] = v1587;	// L2161
      float v1590 = s5_t1i;	// L2162
      float v1591 = s5_t3r;	// L2163
      float v1592 = v1590 + v1591;	// L2164
      int v1593 = idx34;	// L2165
      int v1594 = v1593;	// L2166
      buf_imag[v1594] = v1592;	// L2167
    }
  }
  l_S_n_11_n: for (int n = 0; n < 1024; n++) {	// L2170
    float v1596 = buf_real[n];	// L2171
    v2[n] = v1596;	// L2172
    float v1597 = buf_imag[n];	// L2173
    v3[n] = v1597;	// L2174
  }
}
#pragma pocc-region-end
}

