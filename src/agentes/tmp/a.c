
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
  float buf_real[1024];	// L4
  #pragma HLS array_partition variable=buf_real cyclic dim=1 factor=4

  float buf_imag[1024];	// L5
  #pragma HLS array_partition variable=buf_imag cyclic dim=1 factor=4

  l_S_i_0_i: for (int i = 0; i < 1024; i++) {	// L6
  #pragma HLS pipeline II=5
    int v7 = i;	// L7
    int i0;	// L8
    i0 = v7;	// L9
    int v9 = i0;	// L10
    int v10 = v9 / 4;	// L12
    int q0;	// L13
    q0 = v10;	// L14
    int v12 = i0;	// L15
    int v13 = q0;	// L16
    int v14 = v13;	// L17
    int v15 = v14 * 4;	// L19
    int v16 = v12;	// L20
    int v17 = v15;	// L21
    int v18 = v16 - v17;	// L22
    int v19 = v18;	// L23
    int d0;	// L24
    d0 = v19;	// L25
    int v21 = q0;	// L26
    int i1;	// L27
    i1 = v21;	// L28
    int v23 = i1;	// L29
    int v24 = v23 / 4;	// L30
    int q1;	// L31
    q1 = v24;	// L32
    int v26 = i1;	// L33
    int v27 = q1;	// L34
    int v28 = v27;	// L35
    int v29 = v28 * 4;	// L36
    int v30 = v26;	// L37
    int v31 = v29;	// L38
    int v32 = v30 - v31;	// L39
    int v33 = v32;	// L40
    int d1;	// L41
    d1 = v33;	// L42
    int v35 = q1;	// L43
    int i2;	// L44
    i2 = v35;	// L45
    int v37 = i2;	// L46
    int v38 = v37 / 4;	// L47
    int q2;	// L48
    q2 = v38;	// L49
    int v40 = i2;	// L50
    int v41 = q2;	// L51
    int v42 = v41;	// L52
    int v43 = v42 * 4;	// L53
    int v44 = v40;	// L54
    int v45 = v43;	// L55
    int v46 = v44 - v45;	// L56
    int v47 = v46;	// L57
    int d2;	// L58
    d2 = v47;	// L59
    int v49 = q2;	// L60
    int i3;	// L61
    i3 = v49;	// L62
    int v51 = i3;	// L63
    int v52 = v51 / 4;	// L64
    int q3;	// L65
    q3 = v52;	// L66
    int v54 = i3;	// L67
    int v55 = q3;	// L68
    int v56 = v55;	// L69
    int v57 = v56 * 4;	// L70
    int v58 = v54;	// L71
    int v59 = v57;	// L72
    int v60 = v58 - v59;	// L73
    int v61 = v60;	// L74
    int d3;	// L75
    d3 = v61;	// L76
    int v63 = q3;	// L77
    int i4;	// L78
    i4 = v63;	// L79
    int v65 = i4;	// L80
    int v66 = v65 / 4;	// L81
    int q4;	// L82
    q4 = v66;	// L83
    int v68 = i4;	// L84
    int v69 = q4;	// L85
    int v70 = v69;	// L86
    int v71 = v70 * 4;	// L87
    int v72 = v68;	// L88
    int v73 = v71;	// L89
    int v74 = v72 - v73;	// L90
    int v75 = v74;	// L91
    int d4;	// L92
    d4 = v75;	// L93
    int v77 = d0;	// L94
    int v78 = v77;	// L95
    int v79 = v78 * 256;	// L98
    int v80 = d1;	// L99
    int v81 = v80;	// L100
    int v82 = v81 * 64;	// L103
    int v83 = v79;	// L104
    int v84 = v82;	// L105
    int v85 = v83 + v84;	// L106
    int v86 = d2;	// L107
    int v87 = v86;	// L108
    int v88 = v87 * 16;	// L111
    int v89 = v85;	// L112
    int v90 = v88;	// L113
    int v91 = v89 + v90;	// L114
    int v92 = d3;	// L115
    int v93 = v92;	// L116
    int v94 = v93 * 4;	// L117
    int v95 = v91;	// L118
    int v96 = v94;	// L119
    int v97 = v95 + v96;	// L120
    int v98 = d4;	// L121
    int v99 = v97;	// L122
    int v100 = v98;	// L123
    int v101 = v99 + v100;	// L124
    int v102 = v101;	// L125
    int rev;	// L126
    rev = v102;	// L127
    float v104 = v0[i];	// L128
    int v105 = rev;	// L129
    int v106 = v105;	// L130
    buf_real[v106] = v104;	// L131
    float v107 = v1[i];	// L132
    int v108 = rev;	// L133
    int v109 = v108;	// L134
    buf_imag[v109] = v107;	// L135
  }
  l_S_g1_1_g1: for (int g1 = 0; g1 < 256; g1++) {	// L137
  #pragma HLS pipeline II=5
    l_S_j1_1_j1: for (int j1 = 0; j1 < 1; j1++) {	// L138
      int v112 = g1;	// L139
      int v113 = v112 * 4;	// L142
      int v114 = v113;	// L143
      int k1;	// L144
      k1 = v114;	// L145
      int v116 = k1;	// L146
      int v117 = v116;	// L147
      int v118 = j1;	// L148
      int v119 = v117 + v118;	// L149
      int v120 = v119;	// L150
      int idx0;	// L151
      idx0 = v120;	// L152
      int v122 = idx0;	// L153
      int v123 = v122;	// L154
      int v124 = v123 + 1;	// L157
      int v125 = v124;	// L158
      int idx1;	// L159
      idx1 = v125;	// L160
      int v127 = idx1;	// L161
      int v128 = v127;	// L162
      int v129 = v128 + 1;	// L163
      int v130 = v129;	// L164
      int idx2;	// L165
      idx2 = v130;	// L166
      int v132 = idx2;	// L167
      int v133 = v132;	// L168
      int v134 = v133 + 1;	// L169
      int v135 = v134;	// L170
      int idx3;	// L171
      idx3 = v135;	// L172
      int v137 = idx0;	// L173
      int v138 = v137;	// L174
      float v139 = buf_real[v138];	// L175
      float s1_ar;	// L176
      s1_ar = v139;	// L177
      int v141 = idx0;	// L178
      int v142 = v141;	// L179
      float v143 = buf_imag[v142];	// L180
      float s1_ai;	// L181
      s1_ai = v143;	// L182
      int v145 = idx1;	// L183
      int v146 = v145;	// L184
      float v147 = buf_real[v146];	// L185
      float s1_br;	// L186
      s1_br = v147;	// L187
      int v149 = idx1;	// L188
      int v150 = v149;	// L189
      float v151 = buf_imag[v150];	// L190
      float s1_bi;	// L191
      s1_bi = v151;	// L192
      int v153 = idx2;	// L193
      int v154 = v153;	// L194
      float v155 = buf_real[v154];	// L195
      float s1_cr;	// L196
      s1_cr = v155;	// L197
      int v157 = idx2;	// L198
      int v158 = v157;	// L199
      float v159 = buf_imag[v158];	// L200
      float s1_ci;	// L201
      s1_ci = v159;	// L202
      int v161 = idx3;	// L203
      int v162 = v161;	// L204
      float v163 = buf_real[v162];	// L205
      float s1_dr;	// L206
      s1_dr = v163;	// L207
      int v165 = idx3;	// L208
      int v166 = v165;	// L209
      float v167 = buf_imag[v166];	// L210
      float s1_di;	// L211
      s1_di = v167;	// L212
      int v169 = j1;	// L213
      float v170 = v169;	// L214
      float s1_jf;	// L215
      s1_jf = v170;	// L216
      float v172 = s1_jf;	// L217
      float v173 = v172 * 1.570796;	// L219
      float s1_x;	// L220
      s1_x = v173;	// L221
      float v175 = s1_x;	// L222
      float v176 = v175 * v175;	// L223
      float s1_x2;	// L224
      s1_x2 = v176;	// L225
      float v178 = s1_x2;	// L226
      float v179 = s1_x;	// L227
      float v180 = v178 * v179;	// L228
      float s1_x3;	// L229
      s1_x3 = v180;	// L230
      float v182 = s1_x2;	// L231
      float v183 = v182 * v182;	// L232
      float s1_x4;	// L233
      s1_x4 = v183;	// L234
      float v185 = s1_x4;	// L235
      float v186 = s1_x;	// L236
      float v187 = v185 * v186;	// L237
      float s1_x5;	// L238
      s1_x5 = v187;	// L239
      float v189 = s1_x4;	// L240
      float v190 = s1_x2;	// L241
      float v191 = v189 * v190;	// L242
      float s1_x6;	// L243
      s1_x6 = v191;	// L244
      float v193 = s1_x6;	// L245
      float v194 = s1_x;	// L246
      float v195 = v193 * v194;	// L247
      float s1_x7;	// L248
      s1_x7 = v195;	// L249
      float v197 = s1_x4;	// L250
      float v198 = v197 * v197;	// L251
      float s1_x8;	// L252
      s1_x8 = v198;	// L253
      float v200 = s1_x8;	// L254
      float v201 = s1_x;	// L255
      float v202 = v200 * v201;	// L256
      float s1_x9;	// L257
      s1_x9 = v202;	// L258
      float v204 = s1_x8;	// L259
      float v205 = s1_x2;	// L260
      float v206 = v204 * v205;	// L261
      float s1_x10;	// L262
      s1_x10 = v206;	// L263
      float v208 = s1_x10;	// L264
      float v209 = s1_x;	// L265
      float v210 = v208 * v209;	// L266
      float s1_x11;	// L267
      s1_x11 = v210;	// L268
      float v212 = s1_x2;	// L269
      float v213 = v212 / 2.000000;	// L271
      float v214 = 1.000000 - v213;	// L273
      float v215 = s1_x4;	// L274
      float v216 = v215 / 24.000000;	// L276
      float v217 = v214 + v216;	// L277
      float v218 = s1_x6;	// L278
      float v219 = v218 / 720.000000;	// L280
      float v220 = v217 - v219;	// L281
      float v221 = s1_x8;	// L282
      float v222 = v221 / 40320.000000;	// L284
      float v223 = v220 + v222;	// L285
      float v224 = s1_x10;	// L286
      float v225 = v224 / 3628800.000000;	// L288
      float v226 = v223 - v225;	// L289
      float s1_cos;	// L290
      s1_cos = v226;	// L291
      float v228 = s1_x;	// L292
      float v229 = s1_x3;	// L293
      float v230 = v229 / 6.000000;	// L295
      float v231 = v228 - v230;	// L296
      float v232 = s1_x5;	// L297
      float v233 = v232 / 120.000000;	// L299
      float v234 = v231 + v233;	// L300
      float v235 = s1_x7;	// L301
      float v236 = v235 / 5040.000000;	// L303
      float v237 = v234 - v236;	// L304
      float v238 = s1_x9;	// L305
      float v239 = v238 / 362880.000000;	// L307
      float v240 = v237 + v239;	// L308
      float v241 = s1_x11;	// L309
      float v242 = v241 / 39916800.000000;	// L311
      float v243 = v240 - v242;	// L312
      float s1_sin;	// L313
      s1_sin = v243;	// L314
      float v245 = s1_cos;	// L315
      float v246 = v245 * v245;	// L316
      float v247 = s1_sin;	// L317
      float v248 = v247 * v247;	// L318
      float v249 = v246 - v248;	// L319
      float s1_cos2;	// L320
      s1_cos2 = v249;	// L321
      float v251 = s1_sin;	// L322
      float v252 = v251  << 1.000000;	// L323
      float v253 = s1_cos;	// L324
      float v254 = v252 * v253;	// L325
      float s1_sin2;	// L326
      s1_sin2 = v254;	// L327
      float v256 = s1_cos2;	// L328
      float v257 = s1_cos;	// L329
      float v258 = v256 * v257;	// L330
      float v259 = s1_sin2;	// L331
      float v260 = s1_sin;	// L332
      float v261 = v259 * v260;	// L333
      float v262 = v258 - v261;	// L334
      float s1_cos3;	// L335
      s1_cos3 = v262;	// L336
      float v264 = s1_sin2;	// L337
      float v265 = s1_cos;	// L338
      float v266 = v264 * v265;	// L339
      float v267 = s1_cos2;	// L340
      float v268 = s1_sin;	// L341
      float v269 = v267 * v268;	// L342
      float v270 = v266 + v269;	// L343
      float s1_sin3;	// L344
      s1_sin3 = v270;	// L345
      float v272 = s1_cos;	// L346
      float s1_w1r;	// L347
      s1_w1r = v272;	// L348
      float v274 = s1_sin;	// L349
      float v275 = -(v274);	// L350
      float s1_w1i;	// L351
      s1_w1i = v275;	// L352
      float v277 = s1_cos2;	// L353
      float s1_w2r;	// L354
      s1_w2r = v277;	// L355
      float v279 = s1_sin2;	// L356
      float v280 = -(v279);	// L357
      float s1_w2i;	// L358
      s1_w2i = v280;	// L359
      float v282 = s1_cos3;	// L360
      float s1_w3r;	// L361
      s1_w3r = v282;	// L362
      float v284 = s1_sin3;	// L363
      float v285 = -(v284);	// L364
      float s1_w3i;	// L365
      s1_w3i = v285;	// L366
      float v287 = s1_br;	// L367
      float v288 = s1_w1r;	// L368
      float v289 = v287 * v288;	// L369
      float v290 = s1_bi;	// L370
      float v291 = s1_w1i;	// L371
      float v292 = v290 * v291;	// L372
      float v293 = v289 - v292;	// L373
      float s1_bpr;	// L374
      s1_bpr = v293;	// L375
      float v295 = s1_br;	// L376
      float v296 = s1_w1i;	// L377
      float v297 = v295 * v296;	// L378
      float v298 = s1_bi;	// L379
      float v299 = s1_w1r;	// L380
      float v300 = v298 * v299;	// L381
      float v301 = v297 + v300;	// L382
      float s1_bpi;	// L383
      s1_bpi = v301;	// L384
      float v303 = s1_cr;	// L385
      float v304 = s1_w2r;	// L386
      float v305 = v303 * v304;	// L387
      float v306 = s1_ci;	// L388
      float v307 = s1_w2i;	// L389
      float v308 = v306 * v307;	// L390
      float v309 = v305 - v308;	// L391
      float s1_cpr;	// L392
      s1_cpr = v309;	// L393
      float v311 = s1_cr;	// L394
      float v312 = s1_w2i;	// L395
      float v313 = v311 * v312;	// L396
      float v314 = s1_ci;	// L397
      float v315 = s1_w2r;	// L398
      float v316 = v314 * v315;	// L399
      float v317 = v313 + v316;	// L400
      float s1_cpi;	// L401
      s1_cpi = v317;	// L402
      float v319 = s1_dr;	// L403
      float v320 = s1_w3r;	// L404
      float v321 = v319 * v320;	// L405
      float v322 = s1_di;	// L406
      float v323 = s1_w3i;	// L407
      float v324 = v322 * v323;	// L408
      float v325 = v321 - v324;	// L409
      float s1_dpr;	// L410
      s1_dpr = v325;	// L411
      float v327 = s1_dr;	// L412
      float v328 = s1_w3i;	// L413
      float v329 = v327 * v328;	// L414
      float v330 = s1_di;	// L415
      float v331 = s1_w3r;	// L416
      float v332 = v330 * v331;	// L417
      float v333 = v329 + v332;	// L418
      float s1_dpi;	// L419
      s1_dpi = v333;	// L420
      float v335 = s1_ar;	// L421
      float v336 = s1_cpr;	// L422
      float v337 = v335 + v336;	// L423
      float s1_t0r;	// L424
      s1_t0r = v337;	// L425
      float v339 = s1_ai;	// L426
      float v340 = s1_cpi;	// L427
      float v341 = v339 + v340;	// L428
      float s1_t0i;	// L429
      s1_t0i = v341;	// L430
      float v343 = s1_ar;	// L431
      float v344 = s1_cpr;	// L432
      float v345 = v343 - v344;	// L433
      float s1_t1r;	// L434
      s1_t1r = v345;	// L435
      float v347 = s1_ai;	// L436
      float v348 = s1_cpi;	// L437
      float v349 = v347 - v348;	// L438
      float s1_t1i;	// L439
      s1_t1i = v349;	// L440
      float v351 = s1_bpr;	// L441
      float v352 = s1_dpr;	// L442
      float v353 = v351 + v352;	// L443
      float s1_t2r;	// L444
      s1_t2r = v353;	// L445
      float v355 = s1_bpi;	// L446
      float v356 = s1_dpi;	// L447
      float v357 = v355 + v356;	// L448
      float s1_t2i;	// L449
      s1_t2i = v357;	// L450
      float v359 = s1_bpr;	// L451
      float v360 = s1_dpr;	// L452
      float v361 = v359 - v360;	// L453
      float s1_t3r;	// L454
      s1_t3r = v361;	// L455
      float v363 = s1_bpi;	// L456
      float v364 = s1_dpi;	// L457
      float v365 = v363 - v364;	// L458
      float s1_t3i;	// L459
      s1_t3i = v365;	// L460
      float v367 = s1_t0r;	// L461
      float v368 = s1_t2r;	// L462
      float v369 = v367 + v368;	// L463
      int v370 = idx0;	// L464
      int v371 = v370;	// L465
      buf_real[v371] = v369;	// L466
      float v372 = s1_t0i;	// L467
      float v373 = s1_t2i;	// L468
      float v374 = v372 + v373;	// L469
      int v375 = idx0;	// L470
      int v376 = v375;	// L471
      buf_imag[v376] = v374;	// L472
      float v377 = s1_t1r;	// L473
      float v378 = s1_t3i;	// L474
      float v379 = v377 + v378;	// L475
      int v380 = idx1;	// L476
      int v381 = v380;	// L477
      buf_real[v381] = v379;	// L478
      float v382 = s1_t1i;	// L479
      float v383 = s1_t3r;	// L480
      float v384 = v382 - v383;	// L481
      int v385 = idx1;	// L482
      int v386 = v385;	// L483
      buf_imag[v386] = v384;	// L484
      float v387 = s1_t0r;	// L485
      float v388 = s1_t2r;	// L486
      float v389 = v387 - v388;	// L487
      int v390 = idx2;	// L488
      int v391 = v390;	// L489
      buf_real[v391] = v389;	// L490
      float v392 = s1_t0i;	// L491
      float v393 = s1_t2i;	// L492
      float v394 = v392 - v393;	// L493
      int v395 = idx2;	// L494
      int v396 = v395;	// L495
      buf_imag[v396] = v394;	// L496
      float v397 = s1_t1r;	// L497
      float v398 = s1_t3i;	// L498
      float v399 = v397 - v398;	// L499
      int v400 = idx3;	// L500
      int v401 = v400;	// L501
      buf_real[v401] = v399;	// L502
      float v402 = s1_t1i;	// L503
      float v403 = s1_t3r;	// L504
      float v404 = v402 + v403;	// L505
      int v405 = idx3;	// L506
      int v406 = v405;	// L507
      buf_imag[v406] = v404;	// L508
    }
  }
  l_S_g2_3_g2: for (int g2 = 0; g2 < 64; g2++) {	// L511
  #pragma HLS pipeline II=5
    l_S_j2_3_j2: for (int j2 = 0; j2 < 4; j2++) {	// L512
      int v409 = g2;	// L513
      int v410 = v409 * 16;	// L516
      int v411 = v410;	// L517
      int k2;	// L518
      k2 = v411;	// L519
      int v413 = k2;	// L520
      int v414 = v413;	// L521
      int v415 = j2;	// L522
      int v416 = v414 + v415;	// L523
      int v417 = v416;	// L524
      int idx01;	// L525
      idx01 = v417;	// L526
      int v419 = idx01;	// L527
      int v420 = v419;	// L528
      int v421 = v420 + 4;	// L531
      int v422 = v421;	// L532
      int idx11;	// L533
      idx11 = v422;	// L534
      int v424 = idx11;	// L535
      int v425 = v424;	// L536
      int v426 = v425 + 4;	// L537
      int v427 = v426;	// L538
      int idx21;	// L539
      idx21 = v427;	// L540
      int v429 = idx21;	// L541
      int v430 = v429;	// L542
      int v431 = v430 + 4;	// L543
      int v432 = v431;	// L544
      int idx31;	// L545
      idx31 = v432;	// L546
      int v434 = idx01;	// L547
      int v435 = v434;	// L548
      float v436 = buf_real[v435];	// L549
      float s2_ar;	// L550
      s2_ar = v436;	// L551
      int v438 = idx01;	// L552
      int v439 = v438;	// L553
      float v440 = buf_imag[v439];	// L554
      float s2_ai;	// L555
      s2_ai = v440;	// L556
      int v442 = idx11;	// L557
      int v443 = v442;	// L558
      float v444 = buf_real[v443];	// L559
      float s2_br;	// L560
      s2_br = v444;	// L561
      int v446 = idx11;	// L562
      int v447 = v446;	// L563
      float v448 = buf_imag[v447];	// L564
      float s2_bi;	// L565
      s2_bi = v448;	// L566
      int v450 = idx21;	// L567
      int v451 = v450;	// L568
      float v452 = buf_real[v451];	// L569
      float s2_cr;	// L570
      s2_cr = v452;	// L571
      int v454 = idx21;	// L572
      int v455 = v454;	// L573
      float v456 = buf_imag[v455];	// L574
      float s2_ci;	// L575
      s2_ci = v456;	// L576
      int v458 = idx31;	// L577
      int v459 = v458;	// L578
      float v460 = buf_real[v459];	// L579
      float s2_dr;	// L580
      s2_dr = v460;	// L581
      int v462 = idx31;	// L582
      int v463 = v462;	// L583
      float v464 = buf_imag[v463];	// L584
      float s2_di;	// L585
      s2_di = v464;	// L586
      int v466 = j2;	// L587
      float v467 = v466;	// L588
      float s2_jf;	// L589
      s2_jf = v467;	// L590
      float v469 = s2_jf;	// L591
      float v470 = v469 * 0.392699;	// L593
      float s2_x;	// L594
      s2_x = v470;	// L595
      float v472 = s2_x;	// L596
      float v473 = v472 * v472;	// L597
      float s2_x2;	// L598
      s2_x2 = v473;	// L599
      float v475 = s2_x2;	// L600
      float v476 = s2_x;	// L601
      float v477 = v475 * v476;	// L602
      float s2_x3;	// L603
      s2_x3 = v477;	// L604
      float v479 = s2_x2;	// L605
      float v480 = v479 * v479;	// L606
      float s2_x4;	// L607
      s2_x4 = v480;	// L608
      float v482 = s2_x4;	// L609
      float v483 = s2_x;	// L610
      float v484 = v482 * v483;	// L611
      float s2_x5;	// L612
      s2_x5 = v484;	// L613
      float v486 = s2_x4;	// L614
      float v487 = s2_x2;	// L615
      float v488 = v486 * v487;	// L616
      float s2_x6;	// L617
      s2_x6 = v488;	// L618
      float v490 = s2_x6;	// L619
      float v491 = s2_x;	// L620
      float v492 = v490 * v491;	// L621
      float s2_x7;	// L622
      s2_x7 = v492;	// L623
      float v494 = s2_x4;	// L624
      float v495 = v494 * v494;	// L625
      float s2_x8;	// L626
      s2_x8 = v495;	// L627
      float v497 = s2_x8;	// L628
      float v498 = s2_x;	// L629
      float v499 = v497 * v498;	// L630
      float s2_x9;	// L631
      s2_x9 = v499;	// L632
      float v501 = s2_x8;	// L633
      float v502 = s2_x2;	// L634
      float v503 = v501 * v502;	// L635
      float s2_x10;	// L636
      s2_x10 = v503;	// L637
      float v505 = s2_x10;	// L638
      float v506 = s2_x;	// L639
      float v507 = v505 * v506;	// L640
      float s2_x11;	// L641
      s2_x11 = v507;	// L642
      float v509 = s2_x2;	// L643
      float v510 = v509 / 2.000000;	// L645
      float v511 = 1.000000 - v510;	// L647
      float v512 = s2_x4;	// L648
      float v513 = v512 / 24.000000;	// L650
      float v514 = v511 + v513;	// L651
      float v515 = s2_x6;	// L652
      float v516 = v515 / 720.000000;	// L654
      float v517 = v514 - v516;	// L655
      float v518 = s2_x8;	// L656
      float v519 = v518 / 40320.000000;	// L658
      float v520 = v517 + v519;	// L659
      float v521 = s2_x10;	// L660
      float v522 = v521 / 3628800.000000;	// L662
      float v523 = v520 - v522;	// L663
      float s2_cos;	// L664
      s2_cos = v523;	// L665
      float v525 = s2_x;	// L666
      float v526 = s2_x3;	// L667
      float v527 = v526 / 6.000000;	// L669
      float v528 = v525 - v527;	// L670
      float v529 = s2_x5;	// L671
      float v530 = v529 / 120.000000;	// L673
      float v531 = v528 + v530;	// L674
      float v532 = s2_x7;	// L675
      float v533 = v532 / 5040.000000;	// L677
      float v534 = v531 - v533;	// L678
      float v535 = s2_x9;	// L679
      float v536 = v535 / 362880.000000;	// L681
      float v537 = v534 + v536;	// L682
      float v538 = s2_x11;	// L683
      float v539 = v538 / 39916800.000000;	// L685
      float v540 = v537 - v539;	// L686
      float s2_sin;	// L687
      s2_sin = v540;	// L688
      float v542 = s2_cos;	// L689
      float v543 = v542 * v542;	// L690
      float v544 = s2_sin;	// L691
      float v545 = v544 * v544;	// L692
      float v546 = v543 - v545;	// L693
      float s2_cos2;	// L694
      s2_cos2 = v546;	// L695
      float v548 = s2_sin;	// L696
      float v549 = v548  << 1.000000;	// L697
      float v550 = s2_cos;	// L698
      float v551 = v549 * v550;	// L699
      float s2_sin2;	// L700
      s2_sin2 = v551;	// L701
      float v553 = s2_cos2;	// L702
      float v554 = s2_cos;	// L703
      float v555 = v553 * v554;	// L704
      float v556 = s2_sin2;	// L705
      float v557 = s2_sin;	// L706
      float v558 = v556 * v557;	// L707
      float v559 = v555 - v558;	// L708
      float s2_cos3;	// L709
      s2_cos3 = v559;	// L710
      float v561 = s2_sin2;	// L711
      float v562 = s2_cos;	// L712
      float v563 = v561 * v562;	// L713
      float v564 = s2_cos2;	// L714
      float v565 = s2_sin;	// L715
      float v566 = v564 * v565;	// L716
      float v567 = v563 + v566;	// L717
      float s2_sin3;	// L718
      s2_sin3 = v567;	// L719
      float v569 = s2_cos;	// L720
      float s2_w1r;	// L721
      s2_w1r = v569;	// L722
      float v571 = s2_sin;	// L723
      float v572 = -(v571);	// L724
      float s2_w1i;	// L725
      s2_w1i = v572;	// L726
      float v574 = s2_cos2;	// L727
      float s2_w2r;	// L728
      s2_w2r = v574;	// L729
      float v576 = s2_sin2;	// L730
      float v577 = -(v576);	// L731
      float s2_w2i;	// L732
      s2_w2i = v577;	// L733
      float v579 = s2_cos3;	// L734
      float s2_w3r;	// L735
      s2_w3r = v579;	// L736
      float v581 = s2_sin3;	// L737
      float v582 = -(v581);	// L738
      float s2_w3i;	// L739
      s2_w3i = v582;	// L740
      float v584 = s2_br;	// L741
      float v585 = s2_w1r;	// L742
      float v586 = v584 * v585;	// L743
      float v587 = s2_bi;	// L744
      float v588 = s2_w1i;	// L745
      float v589 = v587 * v588;	// L746
      float v590 = v586 - v589;	// L747
      float s2_bpr;	// L748
      s2_bpr = v590;	// L749
      float v592 = s2_br;	// L750
      float v593 = s2_w1i;	// L751
      float v594 = v592 * v593;	// L752
      float v595 = s2_bi;	// L753
      float v596 = s2_w1r;	// L754
      float v597 = v595 * v596;	// L755
      float v598 = v594 + v597;	// L756
      float s2_bpi;	// L757
      s2_bpi = v598;	// L758
      float v600 = s2_cr;	// L759
      float v601 = s2_w2r;	// L760
      float v602 = v600 * v601;	// L761
      float v603 = s2_ci;	// L762
      float v604 = s2_w2i;	// L763
      float v605 = v603 * v604;	// L764
      float v606 = v602 - v605;	// L765
      float s2_cpr;	// L766
      s2_cpr = v606;	// L767
      float v608 = s2_cr;	// L768
      float v609 = s2_w2i;	// L769
      float v610 = v608 * v609;	// L770
      float v611 = s2_ci;	// L771
      float v612 = s2_w2r;	// L772
      float v613 = v611 * v612;	// L773
      float v614 = v610 + v613;	// L774
      float s2_cpi;	// L775
      s2_cpi = v614;	// L776
      float v616 = s2_dr;	// L777
      float v617 = s2_w3r;	// L778
      float v618 = v616 * v617;	// L779
      float v619 = s2_di;	// L780
      float v620 = s2_w3i;	// L781
      float v621 = v619 * v620;	// L782
      float v622 = v618 - v621;	// L783
      float s2_dpr;	// L784
      s2_dpr = v622;	// L785
      float v624 = s2_dr;	// L786
      float v625 = s2_w3i;	// L787
      float v626 = v624 * v625;	// L788
      float v627 = s2_di;	// L789
      float v628 = s2_w3r;	// L790
      float v629 = v627 * v628;	// L791
      float v630 = v626 + v629;	// L792
      float s2_dpi;	// L793
      s2_dpi = v630;	// L794
      float v632 = s2_ar;	// L795
      float v633 = s2_cpr;	// L796
      float v634 = v632 + v633;	// L797
      float s2_t0r;	// L798
      s2_t0r = v634;	// L799
      float v636 = s2_ai;	// L800
      float v637 = s2_cpi;	// L801
      float v638 = v636 + v637;	// L802
      float s2_t0i;	// L803
      s2_t0i = v638;	// L804
      float v640 = s2_ar;	// L805
      float v641 = s2_cpr;	// L806
      float v642 = v640 - v641;	// L807
      float s2_t1r;	// L808
      s2_t1r = v642;	// L809
      float v644 = s2_ai;	// L810
      float v645 = s2_cpi;	// L811
      float v646 = v644 - v645;	// L812
      float s2_t1i;	// L813
      s2_t1i = v646;	// L814
      float v648 = s2_bpr;	// L815
      float v649 = s2_dpr;	// L816
      float v650 = v648 + v649;	// L817
      float s2_t2r;	// L818
      s2_t2r = v650;	// L819
      float v652 = s2_bpi;	// L820
      float v653 = s2_dpi;	// L821
      float v654 = v652 + v653;	// L822
      float s2_t2i;	// L823
      s2_t2i = v654;	// L824
      float v656 = s2_bpr;	// L825
      float v657 = s2_dpr;	// L826
      float v658 = v656 - v657;	// L827
      float s2_t3r;	// L828
      s2_t3r = v658;	// L829
      float v660 = s2_bpi;	// L830
      float v661 = s2_dpi;	// L831
      float v662 = v660 - v661;	// L832
      float s2_t3i;	// L833
      s2_t3i = v662;	// L834
      float v664 = s2_t0r;	// L835
      float v665 = s2_t2r;	// L836
      float v666 = v664 + v665;	// L837
      int v667 = idx01;	// L838
      int v668 = v667;	// L839
      buf_real[v668] = v666;	// L840
      float v669 = s2_t0i;	// L841
      float v670 = s2_t2i;	// L842
      float v671 = v669 + v670;	// L843
      int v672 = idx01;	// L844
      int v673 = v672;	// L845
      buf_imag[v673] = v671;	// L846
      float v674 = s2_t1r;	// L847
      float v675 = s2_t3i;	// L848
      float v676 = v674 + v675;	// L849
      int v677 = idx11;	// L850
      int v678 = v677;	// L851
      buf_real[v678] = v676;	// L852
      float v679 = s2_t1i;	// L853
      float v680 = s2_t3r;	// L854
      float v681 = v679 - v680;	// L855
      int v682 = idx11;	// L856
      int v683 = v682;	// L857
      buf_imag[v683] = v681;	// L858
      float v684 = s2_t0r;	// L859
      float v685 = s2_t2r;	// L860
      float v686 = v684 - v685;	// L861
      int v687 = idx21;	// L862
      int v688 = v687;	// L863
      buf_real[v688] = v686;	// L864
      float v689 = s2_t0i;	// L865
      float v690 = s2_t2i;	// L866
      float v691 = v689 - v690;	// L867
      int v692 = idx21;	// L868
      int v693 = v692;	// L869
      buf_imag[v693] = v691;	// L870
      float v694 = s2_t1r;	// L871
      float v695 = s2_t3i;	// L872
      float v696 = v694 - v695;	// L873
      int v697 = idx31;	// L874
      int v698 = v697;	// L875
      buf_real[v698] = v696;	// L876
      float v699 = s2_t1i;	// L877
      float v700 = s2_t3r;	// L878
      float v701 = v699 + v700;	// L879
      int v702 = idx31;	// L880
      int v703 = v702;	// L881
      buf_imag[v703] = v701;	// L882
    }
  }
  l_S_g3_5_g3: for (int g3 = 0; g3 < 16; g3++) {	// L885
    l_S_j3_5_j3: for (int j3 = 0; j3 < 16; j3++) {	// L886
    #pragma HLS pipeline II=5
      int v706 = g3;	// L887
      int v707 = v706 * 64;	// L890
      int v708 = v707;	// L891
      int k3;	// L892
      k3 = v708;	// L893
      int v710 = k3;	// L894
      int v711 = v710;	// L895
      int v712 = j3;	// L896
      int v713 = v711 + v712;	// L897
      int v714 = v713;	// L898
      int idx02;	// L899
      idx02 = v714;	// L900
      int v716 = idx02;	// L901
      int v717 = v716;	// L902
      int v718 = v717 + 16;	// L905
      int v719 = v718;	// L906
      int idx12;	// L907
      idx12 = v719;	// L908
      int v721 = idx12;	// L909
      int v722 = v721;	// L910
      int v723 = v722 + 16;	// L911
      int v724 = v723;	// L912
      int idx22;	// L913
      idx22 = v724;	// L914
      int v726 = idx22;	// L915
      int v727 = v726;	// L916
      int v728 = v727 + 16;	// L917
      int v729 = v728;	// L918
      int idx32;	// L919
      idx32 = v729;	// L920
      int v731 = idx02;	// L921
      int v732 = v731;	// L922
      float v733 = buf_real[v732];	// L923
      float s3_ar;	// L924
      s3_ar = v733;	// L925
      int v735 = idx02;	// L926
      int v736 = v735;	// L927
      float v737 = buf_imag[v736];	// L928
      float s3_ai;	// L929
      s3_ai = v737;	// L930
      int v739 = idx12;	// L931
      int v740 = v739;	// L932
      float v741 = buf_real[v740];	// L933
      float s3_br;	// L934
      s3_br = v741;	// L935
      int v743 = idx12;	// L936
      int v744 = v743;	// L937
      float v745 = buf_imag[v744];	// L938
      float s3_bi;	// L939
      s3_bi = v745;	// L940
      int v747 = idx22;	// L941
      int v748 = v747;	// L942
      float v749 = buf_real[v748];	// L943
      float s3_cr;	// L944
      s3_cr = v749;	// L945
      int v751 = idx22;	// L946
      int v752 = v751;	// L947
      float v753 = buf_imag[v752];	// L948
      float s3_ci;	// L949
      s3_ci = v753;	// L950
      int v755 = idx32;	// L951
      int v756 = v755;	// L952
      float v757 = buf_real[v756];	// L953
      float s3_dr;	// L954
      s3_dr = v757;	// L955
      int v759 = idx32;	// L956
      int v760 = v759;	// L957
      float v761 = buf_imag[v760];	// L958
      float s3_di;	// L959
      s3_di = v761;	// L960
      int v763 = j3;	// L961
      float v764 = v763;	// L962
      float s3_jf;	// L963
      s3_jf = v764;	// L964
      float v766 = s3_jf;	// L965
      float v767 = v766 * 0.098175;	// L967
      float s3_x;	// L968
      s3_x = v767;	// L969
      float v769 = s3_x;	// L970
      float v770 = v769 * v769;	// L971
      float s3_x2;	// L972
      s3_x2 = v770;	// L973
      float v772 = s3_x2;	// L974
      float v773 = s3_x;	// L975
      float v774 = v772 * v773;	// L976
      float s3_x3;	// L977
      s3_x3 = v774;	// L978
      float v776 = s3_x2;	// L979
      float v777 = v776 * v776;	// L980
      float s3_x4;	// L981
      s3_x4 = v777;	// L982
      float v779 = s3_x4;	// L983
      float v780 = s3_x;	// L984
      float v781 = v779 * v780;	// L985
      float s3_x5;	// L986
      s3_x5 = v781;	// L987
      float v783 = s3_x4;	// L988
      float v784 = s3_x2;	// L989
      float v785 = v783 * v784;	// L990
      float s3_x6;	// L991
      s3_x6 = v785;	// L992
      float v787 = s3_x6;	// L993
      float v788 = s3_x;	// L994
      float v789 = v787 * v788;	// L995
      float s3_x7;	// L996
      s3_x7 = v789;	// L997
      float v791 = s3_x4;	// L998
      float v792 = v791 * v791;	// L999
      float s3_x8;	// L1000
      s3_x8 = v792;	// L1001
      float v794 = s3_x8;	// L1002
      float v795 = s3_x;	// L1003
      float v796 = v794 * v795;	// L1004
      float s3_x9;	// L1005
      s3_x9 = v796;	// L1006
      float v798 = s3_x8;	// L1007
      float v799 = s3_x2;	// L1008
      float v800 = v798 * v799;	// L1009
      float s3_x10;	// L1010
      s3_x10 = v800;	// L1011
      float v802 = s3_x10;	// L1012
      float v803 = s3_x;	// L1013
      float v804 = v802 * v803;	// L1014
      float s3_x11;	// L1015
      s3_x11 = v804;	// L1016
      float v806 = s3_x2;	// L1017
      float v807 = v806 / 2.000000;	// L1019
      float v808 = 1.000000 - v807;	// L1021
      float v809 = s3_x4;	// L1022
      float v810 = v809 / 24.000000;	// L1024
      float v811 = v808 + v810;	// L1025
      float v812 = s3_x6;	// L1026
      float v813 = v812 / 720.000000;	// L1028
      float v814 = v811 - v813;	// L1029
      float v815 = s3_x8;	// L1030
      float v816 = v815 / 40320.000000;	// L1032
      float v817 = v814 + v816;	// L1033
      float v818 = s3_x10;	// L1034
      float v819 = v818 / 3628800.000000;	// L1036
      float v820 = v817 - v819;	// L1037
      float s3_cos;	// L1038
      s3_cos = v820;	// L1039
      float v822 = s3_x;	// L1040
      float v823 = s3_x3;	// L1041
      float v824 = v823 / 6.000000;	// L1043
      float v825 = v822 - v824;	// L1044
      float v826 = s3_x5;	// L1045
      float v827 = v826 / 120.000000;	// L1047
      float v828 = v825 + v827;	// L1048
      float v829 = s3_x7;	// L1049
      float v830 = v829 / 5040.000000;	// L1051
      float v831 = v828 - v830;	// L1052
      float v832 = s3_x9;	// L1053
      float v833 = v832 / 362880.000000;	// L1055
      float v834 = v831 + v833;	// L1056
      float v835 = s3_x11;	// L1057
      float v836 = v835 / 39916800.000000;	// L1059
      float v837 = v834 - v836;	// L1060
      float s3_sin;	// L1061
      s3_sin = v837;	// L1062
      float v839 = s3_cos;	// L1063
      float v840 = v839 * v839;	// L1064
      float v841 = s3_sin;	// L1065
      float v842 = v841 * v841;	// L1066
      float v843 = v840 - v842;	// L1067
      float s3_cos2;	// L1068
      s3_cos2 = v843;	// L1069
      float v845 = s3_sin;	// L1070
      float v846 = v845  << 1.000000;	// L1071
      float v847 = s3_cos;	// L1072
      float v848 = v846 * v847;	// L1073
      float s3_sin2;	// L1074
      s3_sin2 = v848;	// L1075
      float v850 = s3_cos2;	// L1076
      float v851 = s3_cos;	// L1077
      float v852 = v850 * v851;	// L1078
      float v853 = s3_sin2;	// L1079
      float v854 = s3_sin;	// L1080
      float v855 = v853 * v854;	// L1081
      float v856 = v852 - v855;	// L1082
      float s3_cos3;	// L1083
      s3_cos3 = v856;	// L1084
      float v858 = s3_sin2;	// L1085
      float v859 = s3_cos;	// L1086
      float v860 = v858 * v859;	// L1087
      float v861 = s3_cos2;	// L1088
      float v862 = s3_sin;	// L1089
      float v863 = v861 * v862;	// L1090
      float v864 = v860 + v863;	// L1091
      float s3_sin3;	// L1092
      s3_sin3 = v864;	// L1093
      float v866 = s3_cos;	// L1094
      float s3_w1r;	// L1095
      s3_w1r = v866;	// L1096
      float v868 = s3_sin;	// L1097
      float v869 = -(v868);	// L1098
      float s3_w1i;	// L1099
      s3_w1i = v869;	// L1100
      float v871 = s3_cos2;	// L1101
      float s3_w2r;	// L1102
      s3_w2r = v871;	// L1103
      float v873 = s3_sin2;	// L1104
      float v874 = -(v873);	// L1105
      float s3_w2i;	// L1106
      s3_w2i = v874;	// L1107
      float v876 = s3_cos3;	// L1108
      float s3_w3r;	// L1109
      s3_w3r = v876;	// L1110
      float v878 = s3_sin3;	// L1111
      float v879 = -(v878);	// L1112
      float s3_w3i;	// L1113
      s3_w3i = v879;	// L1114
      float v881 = s3_br;	// L1115
      float v882 = s3_w1r;	// L1116
      float v883 = v881 * v882;	// L1117
      float v884 = s3_bi;	// L1118
      float v885 = s3_w1i;	// L1119
      float v886 = v884 * v885;	// L1120
      float v887 = v883 - v886;	// L1121
      float s3_bpr;	// L1122
      s3_bpr = v887;	// L1123
      float v889 = s3_br;	// L1124
      float v890 = s3_w1i;	// L1125
      float v891 = v889 * v890;	// L1126
      float v892 = s3_bi;	// L1127
      float v893 = s3_w1r;	// L1128
      float v894 = v892 * v893;	// L1129
      float v895 = v891 + v894;	// L1130
      float s3_bpi;	// L1131
      s3_bpi = v895;	// L1132
      float v897 = s3_cr;	// L1133
      float v898 = s3_w2r;	// L1134
      float v899 = v897 * v898;	// L1135
      float v900 = s3_ci;	// L1136
      float v901 = s3_w2i;	// L1137
      float v902 = v900 * v901;	// L1138
      float v903 = v899 - v902;	// L1139
      float s3_cpr;	// L1140
      s3_cpr = v903;	// L1141
      float v905 = s3_cr;	// L1142
      float v906 = s3_w2i;	// L1143
      float v907 = v905 * v906;	// L1144
      float v908 = s3_ci;	// L1145
      float v909 = s3_w2r;	// L1146
      float v910 = v908 * v909;	// L1147
      float v911 = v907 + v910;	// L1148
      float s3_cpi;	// L1149
      s3_cpi = v911;	// L1150
      float v913 = s3_dr;	// L1151
      float v914 = s3_w3r;	// L1152
      float v915 = v913 * v914;	// L1153
      float v916 = s3_di;	// L1154
      float v917 = s3_w3i;	// L1155
      float v918 = v916 * v917;	// L1156
      float v919 = v915 - v918;	// L1157
      float s3_dpr;	// L1158
      s3_dpr = v919;	// L1159
      float v921 = s3_dr;	// L1160
      float v922 = s3_w3i;	// L1161
      float v923 = v921 * v922;	// L1162
      float v924 = s3_di;	// L1163
      float v925 = s3_w3r;	// L1164
      float v926 = v924 * v925;	// L1165
      float v927 = v923 + v926;	// L1166
      float s3_dpi;	// L1167
      s3_dpi = v927;	// L1168
      float v929 = s3_ar;	// L1169
      float v930 = s3_cpr;	// L1170
      float v931 = v929 + v930;	// L1171
      float s3_t0r;	// L1172
      s3_t0r = v931;	// L1173
      float v933 = s3_ai;	// L1174
      float v934 = s3_cpi;	// L1175
      float v935 = v933 + v934;	// L1176
      float s3_t0i;	// L1177
      s3_t0i = v935;	// L1178
      float v937 = s3_ar;	// L1179
      float v938 = s3_cpr;	// L1180
      float v939 = v937 - v938;	// L1181
      float s3_t1r;	// L1182
      s3_t1r = v939;	// L1183
      float v941 = s3_ai;	// L1184
      float v942 = s3_cpi;	// L1185
      float v943 = v941 - v942;	// L1186
      float s3_t1i;	// L1187
      s3_t1i = v943;	// L1188
      float v945 = s3_bpr;	// L1189
      float v946 = s3_dpr;	// L1190
      float v947 = v945 + v946;	// L1191
      float s3_t2r;	// L1192
      s3_t2r = v947;	// L1193
      float v949 = s3_bpi;	// L1194
      float v950 = s3_dpi;	// L1195
      float v951 = v949 + v950;	// L1196
      float s3_t2i;	// L1197
      s3_t2i = v951;	// L1198
      float v953 = s3_bpr;	// L1199
      float v954 = s3_dpr;	// L1200
      float v955 = v953 - v954;	// L1201
      float s3_t3r;	// L1202
      s3_t3r = v955;	// L1203
      float v957 = s3_bpi;	// L1204
      float v958 = s3_dpi;	// L1205
      float v959 = v957 - v958;	// L1206
      float s3_t3i;	// L1207
      s3_t3i = v959;	// L1208
      float v961 = s3_t0r;	// L1209
      float v962 = s3_t2r;	// L1210
      float v963 = v961 + v962;	// L1211
      int v964 = idx02;	// L1212
      int v965 = v964;	// L1213
      buf_real[v965] = v963;	// L1214
      float v966 = s3_t0i;	// L1215
      float v967 = s3_t2i;	// L1216
      float v968 = v966 + v967;	// L1217
      int v969 = idx02;	// L1218
      int v970 = v969;	// L1219
      buf_imag[v970] = v968;	// L1220
      float v971 = s3_t1r;	// L1221
      float v972 = s3_t3i;	// L1222
      float v973 = v971 + v972;	// L1223
      int v974 = idx12;	// L1224
      int v975 = v974;	// L1225
      buf_real[v975] = v973;	// L1226
      float v976 = s3_t1i;	// L1227
      float v977 = s3_t3r;	// L1228
      float v978 = v976 - v977;	// L1229
      int v979 = idx12;	// L1230
      int v980 = v979;	// L1231
      buf_imag[v980] = v978;	// L1232
      float v981 = s3_t0r;	// L1233
      float v982 = s3_t2r;	// L1234
      float v983 = v981 - v982;	// L1235
      int v984 = idx22;	// L1236
      int v985 = v984;	// L1237
      buf_real[v985] = v983;	// L1238
      float v986 = s3_t0i;	// L1239
      float v987 = s3_t2i;	// L1240
      float v988 = v986 - v987;	// L1241
      int v989 = idx22;	// L1242
      int v990 = v989;	// L1243
      buf_imag[v990] = v988;	// L1244
      float v991 = s3_t1r;	// L1245
      float v992 = s3_t3i;	// L1246
      float v993 = v991 - v992;	// L1247
      int v994 = idx32;	// L1248
      int v995 = v994;	// L1249
      buf_real[v995] = v993;	// L1250
      float v996 = s3_t1i;	// L1251
      float v997 = s3_t3r;	// L1252
      float v998 = v996 + v997;	// L1253
      int v999 = idx32;	// L1254
      int v1000 = v999;	// L1255
      buf_imag[v1000] = v998;	// L1256
    }
  }
  l_S_g4_7_g4: for (int g4 = 0; g4 < 4; g4++) {	// L1259
    l_S_j4_7_j4: for (int j4 = 0; j4 < 64; j4++) {	// L1260
    #pragma HLS pipeline II=5
      int v1003 = g4;	// L1261
      int v1004 = v1003 * 256;	// L1264
      int v1005 = v1004;	// L1265
      int k4;	// L1266
      k4 = v1005;	// L1267
      int v1007 = k4;	// L1268
      int v1008 = v1007;	// L1269
      int v1009 = j4;	// L1270
      int v1010 = v1008 + v1009;	// L1271
      int v1011 = v1010;	// L1272
      int idx03;	// L1273
      idx03 = v1011;	// L1274
      int v1013 = idx03;	// L1275
      int v1014 = v1013;	// L1276
      int v1015 = v1014 + 64;	// L1279
      int v1016 = v1015;	// L1280
      int idx13;	// L1281
      idx13 = v1016;	// L1282
      int v1018 = idx13;	// L1283
      int v1019 = v1018;	// L1284
      int v1020 = v1019 + 64;	// L1285
      int v1021 = v1020;	// L1286
      int idx23;	// L1287
      idx23 = v1021;	// L1288
      int v1023 = idx23;	// L1289
      int v1024 = v1023;	// L1290
      int v1025 = v1024 + 64;	// L1291
      int v1026 = v1025;	// L1292
      int idx33;	// L1293
      idx33 = v1026;	// L1294
      int v1028 = idx03;	// L1295
      int v1029 = v1028;	// L1296
      float v1030 = buf_real[v1029];	// L1297
      float s4_ar;	// L1298
      s4_ar = v1030;	// L1299
      int v1032 = idx03;	// L1300
      int v1033 = v1032;	// L1301
      float v1034 = buf_imag[v1033];	// L1302
      float s4_ai;	// L1303
      s4_ai = v1034;	// L1304
      int v1036 = idx13;	// L1305
      int v1037 = v1036;	// L1306
      float v1038 = buf_real[v1037];	// L1307
      float s4_br;	// L1308
      s4_br = v1038;	// L1309
      int v1040 = idx13;	// L1310
      int v1041 = v1040;	// L1311
      float v1042 = buf_imag[v1041];	// L1312
      float s4_bi;	// L1313
      s4_bi = v1042;	// L1314
      int v1044 = idx23;	// L1315
      int v1045 = v1044;	// L1316
      float v1046 = buf_real[v1045];	// L1317
      float s4_cr;	// L1318
      s4_cr = v1046;	// L1319
      int v1048 = idx23;	// L1320
      int v1049 = v1048;	// L1321
      float v1050 = buf_imag[v1049];	// L1322
      float s4_ci;	// L1323
      s4_ci = v1050;	// L1324
      int v1052 = idx33;	// L1325
      int v1053 = v1052;	// L1326
      float v1054 = buf_real[v1053];	// L1327
      float s4_dr;	// L1328
      s4_dr = v1054;	// L1329
      int v1056 = idx33;	// L1330
      int v1057 = v1056;	// L1331
      float v1058 = buf_imag[v1057];	// L1332
      float s4_di;	// L1333
      s4_di = v1058;	// L1334
      int v1060 = j4;	// L1335
      float v1061 = v1060;	// L1336
      float s4_jf;	// L1337
      s4_jf = v1061;	// L1338
      float v1063 = s4_jf;	// L1339
      float v1064 = v1063 * 0.024544;	// L1341
      float s4_x;	// L1342
      s4_x = v1064;	// L1343
      float v1066 = s4_x;	// L1344
      float v1067 = v1066 * v1066;	// L1345
      float s4_x2;	// L1346
      s4_x2 = v1067;	// L1347
      float v1069 = s4_x2;	// L1348
      float v1070 = s4_x;	// L1349
      float v1071 = v1069 * v1070;	// L1350
      float s4_x3;	// L1351
      s4_x3 = v1071;	// L1352
      float v1073 = s4_x2;	// L1353
      float v1074 = v1073 * v1073;	// L1354
      float s4_x4;	// L1355
      s4_x4 = v1074;	// L1356
      float v1076 = s4_x4;	// L1357
      float v1077 = s4_x;	// L1358
      float v1078 = v1076 * v1077;	// L1359
      float s4_x5;	// L1360
      s4_x5 = v1078;	// L1361
      float v1080 = s4_x4;	// L1362
      float v1081 = s4_x2;	// L1363
      float v1082 = v1080 * v1081;	// L1364
      float s4_x6;	// L1365
      s4_x6 = v1082;	// L1366
      float v1084 = s4_x6;	// L1367
      float v1085 = s4_x;	// L1368
      float v1086 = v1084 * v1085;	// L1369
      float s4_x7;	// L1370
      s4_x7 = v1086;	// L1371
      float v1088 = s4_x4;	// L1372
      float v1089 = v1088 * v1088;	// L1373
      float s4_x8;	// L1374
      s4_x8 = v1089;	// L1375
      float v1091 = s4_x8;	// L1376
      float v1092 = s4_x;	// L1377
      float v1093 = v1091 * v1092;	// L1378
      float s4_x9;	// L1379
      s4_x9 = v1093;	// L1380
      float v1095 = s4_x8;	// L1381
      float v1096 = s4_x2;	// L1382
      float v1097 = v1095 * v1096;	// L1383
      float s4_x10;	// L1384
      s4_x10 = v1097;	// L1385
      float v1099 = s4_x10;	// L1386
      float v1100 = s4_x;	// L1387
      float v1101 = v1099 * v1100;	// L1388
      float s4_x11;	// L1389
      s4_x11 = v1101;	// L1390
      float v1103 = s4_x2;	// L1391
      float v1104 = v1103 / 2.000000;	// L1393
      float v1105 = 1.000000 - v1104;	// L1395
      float v1106 = s4_x4;	// L1396
      float v1107 = v1106 / 24.000000;	// L1398
      float v1108 = v1105 + v1107;	// L1399
      float v1109 = s4_x6;	// L1400
      float v1110 = v1109 / 720.000000;	// L1402
      float v1111 = v1108 - v1110;	// L1403
      float v1112 = s4_x8;	// L1404
      float v1113 = v1112 / 40320.000000;	// L1406
      float v1114 = v1111 + v1113;	// L1407
      float v1115 = s4_x10;	// L1408
      float v1116 = v1115 / 3628800.000000;	// L1410
      float v1117 = v1114 - v1116;	// L1411
      float s4_cos;	// L1412
      s4_cos = v1117;	// L1413
      float v1119 = s4_x;	// L1414
      float v1120 = s4_x3;	// L1415
      float v1121 = v1120 / 6.000000;	// L1417
      float v1122 = v1119 - v1121;	// L1418
      float v1123 = s4_x5;	// L1419
      float v1124 = v1123 / 120.000000;	// L1421
      float v1125 = v1122 + v1124;	// L1422
      float v1126 = s4_x7;	// L1423
      float v1127 = v1126 / 5040.000000;	// L1425
      float v1128 = v1125 - v1127;	// L1426
      float v1129 = s4_x9;	// L1427
      float v1130 = v1129 / 362880.000000;	// L1429
      float v1131 = v1128 + v1130;	// L1430
      float v1132 = s4_x11;	// L1431
      float v1133 = v1132 / 39916800.000000;	// L1433
      float v1134 = v1131 - v1133;	// L1434
      float s4_sin;	// L1435
      s4_sin = v1134;	// L1436
      float v1136 = s4_cos;	// L1437
      float v1137 = v1136 * v1136;	// L1438
      float v1138 = s4_sin;	// L1439
      float v1139 = v1138 * v1138;	// L1440
      float v1140 = v1137 - v1139;	// L1441
      float s4_cos2;	// L1442
      s4_cos2 = v1140;	// L1443
      float v1142 = s4_sin;	// L1444
      float v1143 = v1142  << 1.000000;	// L1445
      float v1144 = s4_cos;	// L1446
      float v1145 = v1143 * v1144;	// L1447
      float s4_sin2;	// L1448
      s4_sin2 = v1145;	// L1449
      float v1147 = s4_cos2;	// L1450
      float v1148 = s4_cos;	// L1451
      float v1149 = v1147 * v1148;	// L1452
      float v1150 = s4_sin2;	// L1453
      float v1151 = s4_sin;	// L1454
      float v1152 = v1150 * v1151;	// L1455
      float v1153 = v1149 - v1152;	// L1456
      float s4_cos3;	// L1457
      s4_cos3 = v1153;	// L1458
      float v1155 = s4_sin2;	// L1459
      float v1156 = s4_cos;	// L1460
      float v1157 = v1155 * v1156;	// L1461
      float v1158 = s4_cos2;	// L1462
      float v1159 = s4_sin;	// L1463
      float v1160 = v1158 * v1159;	// L1464
      float v1161 = v1157 + v1160;	// L1465
      float s4_sin3;	// L1466
      s4_sin3 = v1161;	// L1467
      float v1163 = s4_cos;	// L1468
      float s4_w1r;	// L1469
      s4_w1r = v1163;	// L1470
      float v1165 = s4_sin;	// L1471
      float v1166 = -(v1165);	// L1472
      float s4_w1i;	// L1473
      s4_w1i = v1166;	// L1474
      float v1168 = s4_cos2;	// L1475
      float s4_w2r;	// L1476
      s4_w2r = v1168;	// L1477
      float v1170 = s4_sin2;	// L1478
      float v1171 = -(v1170);	// L1479
      float s4_w2i;	// L1480
      s4_w2i = v1171;	// L1481
      float v1173 = s4_cos3;	// L1482
      float s4_w3r;	// L1483
      s4_w3r = v1173;	// L1484
      float v1175 = s4_sin3;	// L1485
      float v1176 = -(v1175);	// L1486
      float s4_w3i;	// L1487
      s4_w3i = v1176;	// L1488
      float v1178 = s4_br;	// L1489
      float v1179 = s4_w1r;	// L1490
      float v1180 = v1178 * v1179;	// L1491
      float v1181 = s4_bi;	// L1492
      float v1182 = s4_w1i;	// L1493
      float v1183 = v1181 * v1182;	// L1494
      float v1184 = v1180 - v1183;	// L1495
      float s4_bpr;	// L1496
      s4_bpr = v1184;	// L1497
      float v1186 = s4_br;	// L1498
      float v1187 = s4_w1i;	// L1499
      float v1188 = v1186 * v1187;	// L1500
      float v1189 = s4_bi;	// L1501
      float v1190 = s4_w1r;	// L1502
      float v1191 = v1189 * v1190;	// L1503
      float v1192 = v1188 + v1191;	// L1504
      float s4_bpi;	// L1505
      s4_bpi = v1192;	// L1506
      float v1194 = s4_cr;	// L1507
      float v1195 = s4_w2r;	// L1508
      float v1196 = v1194 * v1195;	// L1509
      float v1197 = s4_ci;	// L1510
      float v1198 = s4_w2i;	// L1511
      float v1199 = v1197 * v1198;	// L1512
      float v1200 = v1196 - v1199;	// L1513
      float s4_cpr;	// L1514
      s4_cpr = v1200;	// L1515
      float v1202 = s4_cr;	// L1516
      float v1203 = s4_w2i;	// L1517
      float v1204 = v1202 * v1203;	// L1518
      float v1205 = s4_ci;	// L1519
      float v1206 = s4_w2r;	// L1520
      float v1207 = v1205 * v1206;	// L1521
      float v1208 = v1204 + v1207;	// L1522
      float s4_cpi;	// L1523
      s4_cpi = v1208;	// L1524
      float v1210 = s4_dr;	// L1525
      float v1211 = s4_w3r;	// L1526
      float v1212 = v1210 * v1211;	// L1527
      float v1213 = s4_di;	// L1528
      float v1214 = s4_w3i;	// L1529
      float v1215 = v1213 * v1214;	// L1530
      float v1216 = v1212 - v1215;	// L1531
      float s4_dpr;	// L1532
      s4_dpr = v1216;	// L1533
      float v1218 = s4_dr;	// L1534
      float v1219 = s4_w3i;	// L1535
      float v1220 = v1218 * v1219;	// L1536
      float v1221 = s4_di;	// L1537
      float v1222 = s4_w3r;	// L1538
      float v1223 = v1221 * v1222;	// L1539
      float v1224 = v1220 + v1223;	// L1540
      float s4_dpi;	// L1541
      s4_dpi = v1224;	// L1542
      float v1226 = s4_ar;	// L1543
      float v1227 = s4_cpr;	// L1544
      float v1228 = v1226 + v1227;	// L1545
      float s4_t0r;	// L1546
      s4_t0r = v1228;	// L1547
      float v1230 = s4_ai;	// L1548
      float v1231 = s4_cpi;	// L1549
      float v1232 = v1230 + v1231;	// L1550
      float s4_t0i;	// L1551
      s4_t0i = v1232;	// L1552
      float v1234 = s4_ar;	// L1553
      float v1235 = s4_cpr;	// L1554
      float v1236 = v1234 - v1235;	// L1555
      float s4_t1r;	// L1556
      s4_t1r = v1236;	// L1557
      float v1238 = s4_ai;	// L1558
      float v1239 = s4_cpi;	// L1559
      float v1240 = v1238 - v1239;	// L1560
      float s4_t1i;	// L1561
      s4_t1i = v1240;	// L1562
      float v1242 = s4_bpr;	// L1563
      float v1243 = s4_dpr;	// L1564
      float v1244 = v1242 + v1243;	// L1565
      float s4_t2r;	// L1566
      s4_t2r = v1244;	// L1567
      float v1246 = s4_bpi;	// L1568
      float v1247 = s4_dpi;	// L1569
      float v1248 = v1246 + v1247;	// L1570
      float s4_t2i;	// L1571
      s4_t2i = v1248;	// L1572
      float v1250 = s4_bpr;	// L1573
      float v1251 = s4_dpr;	// L1574
      float v1252 = v1250 - v1251;	// L1575
      float s4_t3r;	// L1576
      s4_t3r = v1252;	// L1577
      float v1254 = s4_bpi;	// L1578
      float v1255 = s4_dpi;	// L1579
      float v1256 = v1254 - v1255;	// L1580
      float s4_t3i;	// L1581
      s4_t3i = v1256;	// L1582
      float v1258 = s4_t0r;	// L1583
      float v1259 = s4_t2r;	// L1584
      float v1260 = v1258 + v1259;	// L1585
      int v1261 = idx03;	// L1586
      int v1262 = v1261;	// L1587
      buf_real[v1262] = v1260;	// L1588
      float v1263 = s4_t0i;	// L1589
      float v1264 = s4_t2i;	// L1590
      float v1265 = v1263 + v1264;	// L1591
      int v1266 = idx03;	// L1592
      int v1267 = v1266;	// L1593
      buf_imag[v1267] = v1265;	// L1594
      float v1268 = s4_t1r;	// L1595
      float v1269 = s4_t3i;	// L1596
      float v1270 = v1268 + v1269;	// L1597
      int v1271 = idx13;	// L1598
      int v1272 = v1271;	// L1599
      buf_real[v1272] = v1270;	// L1600
      float v1273 = s4_t1i;	// L1601
      float v1274 = s4_t3r;	// L1602
      float v1275 = v1273 - v1274;	// L1603
      int v1276 = idx13;	// L1604
      int v1277 = v1276;	// L1605
      buf_imag[v1277] = v1275;	// L1606
      float v1278 = s4_t0r;	// L1607
      float v1279 = s4_t2r;	// L1608
      float v1280 = v1278 - v1279;	// L1609
      int v1281 = idx23;	// L1610
      int v1282 = v1281;	// L1611
      buf_real[v1282] = v1280;	// L1612
      float v1283 = s4_t0i;	// L1613
      float v1284 = s4_t2i;	// L1614
      float v1285 = v1283 - v1284;	// L1615
      int v1286 = idx23;	// L1616
      int v1287 = v1286;	// L1617
      buf_imag[v1287] = v1285;	// L1618
      float v1288 = s4_t1r;	// L1619
      float v1289 = s4_t3i;	// L1620
      float v1290 = v1288 - v1289;	// L1621
      int v1291 = idx33;	// L1622
      int v1292 = v1291;	// L1623
      buf_real[v1292] = v1290;	// L1624
      float v1293 = s4_t1i;	// L1625
      float v1294 = s4_t3r;	// L1626
      float v1295 = v1293 + v1294;	// L1627
      int v1296 = idx33;	// L1628
      int v1297 = v1296;	// L1629
      buf_imag[v1297] = v1295;	// L1630
    }
  }
  l_S_g5_9_g5: for (int g5 = 0; g5 < 1; g5++) {	// L1633
    l_S_j5_9_j5: for (int j5 = 0; j5 < 256; j5++) {	// L1634
    #pragma HLS pipeline II=5
      int v1300 = g5;	// L1635
      int v1301 = v1300 * 1024;	// L1638
      int v1302 = v1301;	// L1639
      int k5;	// L1640
      k5 = v1302;	// L1641
      int v1304 = k5;	// L1642
      int v1305 = v1304;	// L1643
      int v1306 = j5;	// L1644
      int v1307 = v1305 + v1306;	// L1645
      int v1308 = v1307;	// L1646
      int idx04;	// L1647
      idx04 = v1308;	// L1648
      int v1310 = idx04;	// L1649
      int v1311 = v1310;	// L1650
      int v1312 = v1311 + 256;	// L1653
      int v1313 = v1312;	// L1654
      int idx14;	// L1655
      idx14 = v1313;	// L1656
      int v1315 = idx14;	// L1657
      int v1316 = v1315;	// L1658
      int v1317 = v1316 + 256;	// L1659
      int v1318 = v1317;	// L1660
      int idx24;	// L1661
      idx24 = v1318;	// L1662
      int v1320 = idx24;	// L1663
      int v1321 = v1320;	// L1664
      int v1322 = v1321 + 256;	// L1665
      int v1323 = v1322;	// L1666
      int idx34;	// L1667
      idx34 = v1323;	// L1668
      int v1325 = idx04;	// L1669
      int v1326 = v1325;	// L1670
      float v1327 = buf_real[v1326];	// L1671
      float s5_ar;	// L1672
      s5_ar = v1327;	// L1673
      int v1329 = idx04;	// L1674
      int v1330 = v1329;	// L1675
      float v1331 = buf_imag[v1330];	// L1676
      float s5_ai;	// L1677
      s5_ai = v1331;	// L1678
      int v1333 = idx14;	// L1679
      int v1334 = v1333;	// L1680
      float v1335 = buf_real[v1334];	// L1681
      float s5_br;	// L1682
      s5_br = v1335;	// L1683
      int v1337 = idx14;	// L1684
      int v1338 = v1337;	// L1685
      float v1339 = buf_imag[v1338];	// L1686
      float s5_bi;	// L1687
      s5_bi = v1339;	// L1688
      int v1341 = idx24;	// L1689
      int v1342 = v1341;	// L1690
      float v1343 = buf_real[v1342];	// L1691
      float s5_cr;	// L1692
      s5_cr = v1343;	// L1693
      int v1345 = idx24;	// L1694
      int v1346 = v1345;	// L1695
      float v1347 = buf_imag[v1346];	// L1696
      float s5_ci;	// L1697
      s5_ci = v1347;	// L1698
      int v1349 = idx34;	// L1699
      int v1350 = v1349;	// L1700
      float v1351 = buf_real[v1350];	// L1701
      float s5_dr;	// L1702
      s5_dr = v1351;	// L1703
      int v1353 = idx34;	// L1704
      int v1354 = v1353;	// L1705
      float v1355 = buf_imag[v1354];	// L1706
      float s5_di;	// L1707
      s5_di = v1355;	// L1708
      int v1357 = j5;	// L1709
      float v1358 = v1357;	// L1710
      float s5_jf;	// L1711
      s5_jf = v1358;	// L1712
      float v1360 = s5_jf;	// L1713
      float v1361 = v1360 * 0.006136;	// L1715
      float s5_x;	// L1716
      s5_x = v1361;	// L1717
      float v1363 = s5_x;	// L1718
      float v1364 = v1363 * v1363;	// L1719
      float s5_x2;	// L1720
      s5_x2 = v1364;	// L1721
      float v1366 = s5_x2;	// L1722
      float v1367 = s5_x;	// L1723
      float v1368 = v1366 * v1367;	// L1724
      float s5_x3;	// L1725
      s5_x3 = v1368;	// L1726
      float v1370 = s5_x2;	// L1727
      float v1371 = v1370 * v1370;	// L1728
      float s5_x4;	// L1729
      s5_x4 = v1371;	// L1730
      float v1373 = s5_x4;	// L1731
      float v1374 = s5_x;	// L1732
      float v1375 = v1373 * v1374;	// L1733
      float s5_x5;	// L1734
      s5_x5 = v1375;	// L1735
      float v1377 = s5_x4;	// L1736
      float v1378 = s5_x2;	// L1737
      float v1379 = v1377 * v1378;	// L1738
      float s5_x6;	// L1739
      s5_x6 = v1379;	// L1740
      float v1381 = s5_x6;	// L1741
      float v1382 = s5_x;	// L1742
      float v1383 = v1381 * v1382;	// L1743
      float s5_x7;	// L1744
      s5_x7 = v1383;	// L1745
      float v1385 = s5_x4;	// L1746
      float v1386 = v1385 * v1385;	// L1747
      float s5_x8;	// L1748
      s5_x8 = v1386;	// L1749
      float v1388 = s5_x8;	// L1750
      float v1389 = s5_x;	// L1751
      float v1390 = v1388 * v1389;	// L1752
      float s5_x9;	// L1753
      s5_x9 = v1390;	// L1754
      float v1392 = s5_x8;	// L1755
      float v1393 = s5_x2;	// L1756
      float v1394 = v1392 * v1393;	// L1757
      float s5_x10;	// L1758
      s5_x10 = v1394;	// L1759
      float v1396 = s5_x10;	// L1760
      float v1397 = s5_x;	// L1761
      float v1398 = v1396 * v1397;	// L1762
      float s5_x11;	// L1763
      s5_x11 = v1398;	// L1764
      float v1400 = s5_x2;	// L1765
      float v1401 = v1400 / 2.000000;	// L1767
      float v1402 = 1.000000 - v1401;	// L1769
      float v1403 = s5_x4;	// L1770
      float v1404 = v1403 / 24.000000;	// L1772
      float v1405 = v1402 + v1404;	// L1773
      float v1406 = s5_x6;	// L1774
      float v1407 = v1406 / 720.000000;	// L1776
      float v1408 = v1405 - v1407;	// L1777
      float v1409 = s5_x8;	// L1778
      float v1410 = v1409 / 40320.000000;	// L1780
      float v1411 = v1408 + v1410;	// L1781
      float v1412 = s5_x10;	// L1782
      float v1413 = v1412 / 3628800.000000;	// L1784
      float v1414 = v1411 - v1413;	// L1785
      float s5_cos;	// L1786
      s5_cos = v1414;	// L1787
      float v1416 = s5_x;	// L1788
      float v1417 = s5_x3;	// L1789
      float v1418 = v1417 / 6.000000;	// L1791
      float v1419 = v1416 - v1418;	// L1792
      float v1420 = s5_x5;	// L1793
      float v1421 = v1420 / 120.000000;	// L1795
      float v1422 = v1419 + v1421;	// L1796
      float v1423 = s5_x7;	// L1797
      float v1424 = v1423 / 5040.000000;	// L1799
      float v1425 = v1422 - v1424;	// L1800
      float v1426 = s5_x9;	// L1801
      float v1427 = v1426 / 362880.000000;	// L1803
      float v1428 = v1425 + v1427;	// L1804
      float v1429 = s5_x11;	// L1805
      float v1430 = v1429 / 39916800.000000;	// L1807
      float v1431 = v1428 - v1430;	// L1808
      float s5_sin;	// L1809
      s5_sin = v1431;	// L1810
      float v1433 = s5_cos;	// L1811
      float v1434 = v1433 * v1433;	// L1812
      float v1435 = s5_sin;	// L1813
      float v1436 = v1435 * v1435;	// L1814
      float v1437 = v1434 - v1436;	// L1815
      float s5_cos2;	// L1816
      s5_cos2 = v1437;	// L1817
      float v1439 = s5_sin;	// L1818
      float v1440 = v1439  << 1.000000;	// L1819
      float v1441 = s5_cos;	// L1820
      float v1442 = v1440 * v1441;	// L1821
      float s5_sin2;	// L1822
      s5_sin2 = v1442;	// L1823
      float v1444 = s5_cos2;	// L1824
      float v1445 = s5_cos;	// L1825
      float v1446 = v1444 * v1445;	// L1826
      float v1447 = s5_sin2;	// L1827
      float v1448 = s5_sin;	// L1828
      float v1449 = v1447 * v1448;	// L1829
      float v1450 = v1446 - v1449;	// L1830
      float s5_cos3;	// L1831
      s5_cos3 = v1450;	// L1832
      float v1452 = s5_sin2;	// L1833
      float v1453 = s5_cos;	// L1834
      float v1454 = v1452 * v1453;	// L1835
      float v1455 = s5_cos2;	// L1836
      float v1456 = s5_sin;	// L1837
      float v1457 = v1455 * v1456;	// L1838
      float v1458 = v1454 + v1457;	// L1839
      float s5_sin3;	// L1840
      s5_sin3 = v1458;	// L1841
      float v1460 = s5_cos;	// L1842
      float s5_w1r;	// L1843
      s5_w1r = v1460;	// L1844
      float v1462 = s5_sin;	// L1845
      float v1463 = -(v1462);	// L1846
      float s5_w1i;	// L1847
      s5_w1i = v1463;	// L1848
      float v1465 = s5_cos2;	// L1849
      float s5_w2r;	// L1850
      s5_w2r = v1465;	// L1851
      float v1467 = s5_sin2;	// L1852
      float v1468 = -(v1467);	// L1853
      float s5_w2i;	// L1854
      s5_w2i = v1468;	// L1855
      float v1470 = s5_cos3;	// L1856
      float s5_w3r;	// L1857
      s5_w3r = v1470;	// L1858
      float v1472 = s5_sin3;	// L1859
      float v1473 = -(v1472);	// L1860
      float s5_w3i;	// L1861
      s5_w3i = v1473;	// L1862
      float v1475 = s5_br;	// L1863
      float v1476 = s5_w1r;	// L1864
      float v1477 = v1475 * v1476;	// L1865
      float v1478 = s5_bi;	// L1866
      float v1479 = s5_w1i;	// L1867
      float v1480 = v1478 * v1479;	// L1868
      float v1481 = v1477 - v1480;	// L1869
      float s5_bpr;	// L1870
      s5_bpr = v1481;	// L1871
      float v1483 = s5_br;	// L1872
      float v1484 = s5_w1i;	// L1873
      float v1485 = v1483 * v1484;	// L1874
      float v1486 = s5_bi;	// L1875
      float v1487 = s5_w1r;	// L1876
      float v1488 = v1486 * v1487;	// L1877
      float v1489 = v1485 + v1488;	// L1878
      float s5_bpi;	// L1879
      s5_bpi = v1489;	// L1880
      float v1491 = s5_cr;	// L1881
      float v1492 = s5_w2r;	// L1882
      float v1493 = v1491 * v1492;	// L1883
      float v1494 = s5_ci;	// L1884
      float v1495 = s5_w2i;	// L1885
      float v1496 = v1494 * v1495;	// L1886
      float v1497 = v1493 - v1496;	// L1887
      float s5_cpr;	// L1888
      s5_cpr = v1497;	// L1889
      float v1499 = s5_cr;	// L1890
      float v1500 = s5_w2i;	// L1891
      float v1501 = v1499 * v1500;	// L1892
      float v1502 = s5_ci;	// L1893
      float v1503 = s5_w2r;	// L1894
      float v1504 = v1502 * v1503;	// L1895
      float v1505 = v1501 + v1504;	// L1896
      float s5_cpi;	// L1897
      s5_cpi = v1505;	// L1898
      float v1507 = s5_dr;	// L1899
      float v1508 = s5_w3r;	// L1900
      float v1509 = v1507 * v1508;	// L1901
      float v1510 = s5_di;	// L1902
      float v1511 = s5_w3i;	// L1903
      float v1512 = v1510 * v1511;	// L1904
      float v1513 = v1509 - v1512;	// L1905
      float s5_dpr;	// L1906
      s5_dpr = v1513;	// L1907
      float v1515 = s5_dr;	// L1908
      float v1516 = s5_w3i;	// L1909
      float v1517 = v1515 * v1516;	// L1910
      float v1518 = s5_di;	// L1911
      float v1519 = s5_w3r;	// L1912
      float v1520 = v1518 * v1519;	// L1913
      float v1521 = v1517 + v1520;	// L1914
      float s5_dpi;	// L1915
      s5_dpi = v1521;	// L1916
      float v1523 = s5_ar;	// L1917
      float v1524 = s5_cpr;	// L1918
      float v1525 = v1523 + v1524;	// L1919
      float s5_t0r;	// L1920
      s5_t0r = v1525;	// L1921
      float v1527 = s5_ai;	// L1922
      float v1528 = s5_cpi;	// L1923
      float v1529 = v1527 + v1528;	// L1924
      float s5_t0i;	// L1925
      s5_t0i = v1529;	// L1926
      float v1531 = s5_ar;	// L1927
      float v1532 = s5_cpr;	// L1928
      float v1533 = v1531 - v1532;	// L1929
      float s5_t1r;	// L1930
      s5_t1r = v1533;	// L1931
      float v1535 = s5_ai;	// L1932
      float v1536 = s5_cpi;	// L1933
      float v1537 = v1535 - v1536;	// L1934
      float s5_t1i;	// L1935
      s5_t1i = v1537;	// L1936
      float v1539 = s5_bpr;	// L1937
      float v1540 = s5_dpr;	// L1938
      float v1541 = v1539 + v1540;	// L1939
      float s5_t2r;	// L1940
      s5_t2r = v1541;	// L1941
      float v1543 = s5_bpi;	// L1942
      float v1544 = s5_dpi;	// L1943
      float v1545 = v1543 + v1544;	// L1944
      float s5_t2i;	// L1945
      s5_t2i = v1545;	// L1946
      float v1547 = s5_bpr;	// L1947
      float v1548 = s5_dpr;	// L1948
      float v1549 = v1547 - v1548;	// L1949
      float s5_t3r;	// L1950
      s5_t3r = v1549;	// L1951
      float v1551 = s5_bpi;	// L1952
      float v1552 = s5_dpi;	// L1953
      float v1553 = v1551 - v1552;	// L1954
      float s5_t3i;	// L1955
      s5_t3i = v1553;	// L1956
      float v1555 = s5_t0r;	// L1957
      float v1556 = s5_t2r;	// L1958
      float v1557 = v1555 + v1556;	// L1959
      int v1558 = idx04;	// L1960
      int v1559 = v1558;	// L1961
      buf_real[v1559] = v1557;	// L1962
      float v1560 = s5_t0i;	// L1963
      float v1561 = s5_t2i;	// L1964
      float v1562 = v1560 + v1561;	// L1965
      int v1563 = idx04;	// L1966
      int v1564 = v1563;	// L1967
      buf_imag[v1564] = v1562;	// L1968
      float v1565 = s5_t1r;	// L1969
      float v1566 = s5_t3i;	// L1970
      float v1567 = v1565 + v1566;	// L1971
      int v1568 = idx14;	// L1972
      int v1569 = v1568;	// L1973
      buf_real[v1569] = v1567;	// L1974
      float v1570 = s5_t1i;	// L1975
      float v1571 = s5_t3r;	// L1976
      float v1572 = v1570 - v1571;	// L1977
      int v1573 = idx14;	// L1978
      int v1574 = v1573;	// L1979
      buf_imag[v1574] = v1572;	// L1980
      float v1575 = s5_t0r;	// L1981
      float v1576 = s5_t2r;	// L1982
      float v1577 = v1575 - v1576;	// L1983
      int v1578 = idx24;	// L1984
      int v1579 = v1578;	// L1985
      buf_real[v1579] = v1577;	// L1986
      float v1580 = s5_t0i;	// L1987
      float v1581 = s5_t2i;	// L1988
      float v1582 = v1580 - v1581;	// L1989
      int v1583 = idx24;	// L1990
      int v1584 = v1583;	// L1991
      buf_imag[v1584] = v1582;	// L1992
      float v1585 = s5_t1r;	// L1993
      float v1586 = s5_t3i;	// L1994
      float v1587 = v1585 - v1586;	// L1995
      int v1588 = idx34;	// L1996
      int v1589 = v1588;	// L1997
      buf_real[v1589] = v1587;	// L1998
      float v1590 = s5_t1i;	// L1999
      float v1591 = s5_t3r;	// L2000
      float v1592 = v1590 + v1591;	// L2001
      int v1593 = idx34;	// L2002
      int v1594 = v1593;	// L2003
      buf_imag[v1594] = v1592;	// L2004
    }
  }
  l_S_n_11_n: for (int n = 0; n < 1024; n++) {	// L2007
  #pragma HLS pipeline II=5
    float v1596 = buf_real[n];	// L2008
    v2[n] = v1596;	// L2009
    float v1597 = buf_imag[n];	// L2010
    v3[n] = v1597;	// L2011
  }
}
#pragma pocc-region-end
}

