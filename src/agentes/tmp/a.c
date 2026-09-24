
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
  #pragma HLS array_partition variable=buf_real cyclic dim=1 factor=16

  float buf_imag[1024];	// L5
  #pragma HLS array_partition variable=buf_imag cyclic dim=1 factor=16

  l_S_ip_0_ip: for (int ip = 0; ip < 1024; ip++) {	// L6
  #pragma HLS pipeline II=5
    int v7 = ip;	// L7
    int n0;	// L8
    n0 = v7;	// L9
    int v9 = n0;	// L10
    int v10 = v9 % 4;	// L12
    int d0;	// L13
    d0 = v10;	// L14
    int v12 = n0;	// L15
    int v13 = v12 / 4;	// L16
    int n1;	// L17
    n1 = v13;	// L18
    int v15 = n1;	// L19
    int v16 = v15 % 4;	// L20
    int d1;	// L21
    d1 = v16;	// L22
    int v18 = n1;	// L23
    int v19 = v18 / 4;	// L24
    int n2;	// L25
    n2 = v19;	// L26
    int v21 = n2;	// L27
    int v22 = v21 % 4;	// L28
    int d2;	// L29
    d2 = v22;	// L30
    int v24 = n2;	// L31
    int v25 = v24 / 4;	// L32
    int n3;	// L33
    n3 = v25;	// L34
    int v27 = n3;	// L35
    int v28 = v27 % 4;	// L36
    int d3;	// L37
    d3 = v28;	// L38
    int v30 = n3;	// L39
    int v31 = v30 / 4;	// L40
    int n4;	// L41
    n4 = v31;	// L42
    int v33 = n4;	// L43
    int v34 = v33 % 4;	// L44
    int d4;	// L45
    d4 = v34;	// L46
    int v36 = d0;	// L47
    int v37 = v36;	// L48
    int v38 = v37 * 256;	// L51
    int v39 = d1;	// L52
    int v40 = v39;	// L53
    int v41 = v40 * 64;	// L56
    int v42 = v38;	// L57
    int v43 = v41;	// L58
    int v44 = v42 + v43;	// L59
    int v45 = d2;	// L60
    int v46 = v45;	// L61
    int v47 = v46 * 16;	// L64
    int v48 = v44;	// L65
    int v49 = v47;	// L66
    int v50 = v48 + v49;	// L67
    int v51 = d3;	// L68
    int v52 = v51;	// L69
    int v53 = v52 * 4;	// L71
    int v54 = v50;	// L72
    int v55 = v53;	// L73
    int v56 = v54 + v55;	// L74
    int v57 = d4;	// L75
    int v58 = v56;	// L76
    int v59 = v57;	// L77
    int v60 = v58 + v59;	// L78
    int v61 = v60;	// L79
    int ri;	// L80
    ri = v61;	// L81
    int v63 = ri;	// L82
    int v64 = v63;	// L83
    float v65 = v0[v64];	// L84
    buf_real[ip] = v65;	// L85
    int v66 = ri;	// L86
    int v67 = v66;	// L87
    float v68 = v1[v67];	// L88
    buf_imag[ip] = v68;	// L89
  }
  l_S_g0_1_g0: for (int g0 = 0; g0 < 256; g0++) {	// L91
  #pragma HLS pipeline II=5
    int v70 = g0;	// L92
    int v71 = v70 * 4;	// L95
    int v72 = v71;	// L96
    int i0_0;	// L97
    i0_0 = v72;	// L98
    int v74 = i0_0;	// L99
    int v75 = v74;	// L100
    int v76 = v75 + 1;	// L103
    int v77 = v76;	// L104
    int i1_0;	// L105
    i1_0 = v77;	// L106
    int v79 = i0_0;	// L107
    int v80 = v79;	// L108
    int v81 = v80 + 2;	// L111
    int v82 = v81;	// L112
    int i2_0;	// L113
    i2_0 = v82;	// L114
    int v84 = i0_0;	// L115
    int v85 = v84;	// L116
    int v86 = v85 + 3;	// L119
    int v87 = v86;	// L120
    int i3_0;	// L121
    i3_0 = v87;	// L122
    int v89 = i0_0;	// L123
    int v90 = v89;	// L124
    float v91 = buf_real[v90];	// L125
    float a0r_0;	// L126
    a0r_0 = v91;	// L127
    int v93 = i0_0;	// L128
    int v94 = v93;	// L129
    float v95 = buf_imag[v94];	// L130
    float a0i_0;	// L131
    a0i_0 = v95;	// L132
    int v97 = i1_0;	// L133
    int v98 = v97;	// L134
    float v99 = buf_real[v98];	// L135
    float a1r_0;	// L136
    a1r_0 = v99;	// L137
    int v101 = i1_0;	// L138
    int v102 = v101;	// L139
    float v103 = buf_imag[v102];	// L140
    float a1i_0;	// L141
    a1i_0 = v103;	// L142
    int v105 = i2_0;	// L143
    int v106 = v105;	// L144
    float v107 = buf_real[v106];	// L145
    float a2r_0;	// L146
    a2r_0 = v107;	// L147
    int v109 = i2_0;	// L148
    int v110 = v109;	// L149
    float v111 = buf_imag[v110];	// L150
    float a2i_0;	// L151
    a2i_0 = v111;	// L152
    int v113 = i3_0;	// L153
    int v114 = v113;	// L154
    float v115 = buf_real[v114];	// L155
    float a3r_0;	// L156
    a3r_0 = v115;	// L157
    int v117 = i3_0;	// L158
    int v118 = v117;	// L159
    float v119 = buf_imag[v118];	// L160
    float a3i_0;	// L161
    a3i_0 = v119;	// L162
    float v121 = a0r_0;	// L163
    float v122 = a2r_0;	// L164
    float v123 = v121 + v122;	// L165
    float t0r_0;	// L166
    t0r_0 = v123;	// L167
    float v125 = a0i_0;	// L168
    float v126 = a2i_0;	// L169
    float v127 = v125 + v126;	// L170
    float t0i_0;	// L171
    t0i_0 = v127;	// L172
    float v129 = a0r_0;	// L173
    float v130 = a2r_0;	// L174
    float v131 = v129 - v130;	// L175
    float t1r_0;	// L176
    t1r_0 = v131;	// L177
    float v133 = a0i_0;	// L178
    float v134 = a2i_0;	// L179
    float v135 = v133 - v134;	// L180
    float t1i_0;	// L181
    t1i_0 = v135;	// L182
    float v137 = a1r_0;	// L183
    float v138 = a3r_0;	// L184
    float v139 = v137 + v138;	// L185
    float t2r_0;	// L186
    t2r_0 = v139;	// L187
    float v141 = a1i_0;	// L188
    float v142 = a3i_0;	// L189
    float v143 = v141 + v142;	// L190
    float t2i_0;	// L191
    t2i_0 = v143;	// L192
    float v145 = a1r_0;	// L193
    float v146 = a3r_0;	// L194
    float v147 = v145 - v146;	// L195
    float t3r_0;	// L196
    t3r_0 = v147;	// L197
    float v149 = a1i_0;	// L198
    float v150 = a3i_0;	// L199
    float v151 = v149 - v150;	// L200
    float t3i_0;	// L201
    t3i_0 = v151;	// L202
    float v153 = t0r_0;	// L203
    float v154 = t2r_0;	// L204
    float v155 = v153 + v154;	// L205
    int v156 = i0_0;	// L206
    int v157 = v156;	// L207
    buf_real[v157] = v155;	// L208
    float v158 = t0i_0;	// L209
    float v159 = t2i_0;	// L210
    float v160 = v158 + v159;	// L211
    int v161 = i0_0;	// L212
    int v162 = v161;	// L213
    buf_imag[v162] = v160;	// L214
    float v163 = t0r_0;	// L215
    float v164 = t2r_0;	// L216
    float v165 = v163 - v164;	// L217
    int v166 = i2_0;	// L218
    int v167 = v166;	// L219
    buf_real[v167] = v165;	// L220
    float v168 = t0i_0;	// L221
    float v169 = t2i_0;	// L222
    float v170 = v168 - v169;	// L223
    int v171 = i2_0;	// L224
    int v172 = v171;	// L225
    buf_imag[v172] = v170;	// L226
    float v173 = t1r_0;	// L227
    float v174 = t3i_0;	// L228
    float v175 = v173 + v174;	// L229
    int v176 = i1_0;	// L230
    int v177 = v176;	// L231
    buf_real[v177] = v175;	// L232
    float v178 = t1i_0;	// L233
    float v179 = t3r_0;	// L234
    float v180 = v178 - v179;	// L235
    int v181 = i1_0;	// L236
    int v182 = v181;	// L237
    buf_imag[v182] = v180;	// L238
    float v183 = t1r_0;	// L239
    float v184 = t3i_0;	// L240
    float v185 = v183 - v184;	// L241
    int v186 = i3_0;	// L242
    int v187 = v186;	// L243
    buf_real[v187] = v185;	// L244
    float v188 = t1i_0;	// L245
    float v189 = t3r_0;	// L246
    float v190 = v188 + v189;	// L247
    int v191 = i3_0;	// L248
    int v192 = v191;	// L249
    buf_imag[v192] = v190;	// L250
  }
  l_S_g1_2_g1: for (int g1 = 0; g1 < 64; g1++) {	// L252
  #pragma HLS pipeline II=5
    l_S_j1_2_j1: for (int j1 = 0; j1 < 4; j1++) {	// L253
      int v195 = j1;	// L254
      float v196 = v195;	// L255
      float j_f_1;	// L256
      j_f_1 = v196;	// L257
      float v198 = j_f_1;	// L260
      float v199 = v198 * -0.392699;	// L261
      float theta1_1;	// L262
      theta1_1 = v199;	// L263
      float v201 = theta1_1;	// L264
      float v202 = v201 * v201;	// L265
      float x2_1;	// L266
      x2_1 = v202;	// L267
      float v204 = x2_1;	// L268
      float v205 = theta1_1;	// L269
      float v206 = v204 * v205;	// L270
      float x3_1;	// L271
      x3_1 = v206;	// L272
      float v208 = x2_1;	// L273
      float v209 = v208 * v208;	// L274
      float x4_1;	// L275
      x4_1 = v209;	// L276
      float v211 = x4_1;	// L277
      float v212 = theta1_1;	// L278
      float v213 = v211 * v212;	// L279
      float x5_1;	// L280
      x5_1 = v213;	// L281
      float v215 = x4_1;	// L282
      float v216 = x2_1;	// L283
      float v217 = v215 * v216;	// L284
      float x6_1;	// L285
      x6_1 = v217;	// L286
      float v219 = x6_1;	// L287
      float v220 = theta1_1;	// L288
      float v221 = v219 * v220;	// L289
      float x7_1;	// L290
      x7_1 = v221;	// L291
      float v223 = x4_1;	// L292
      float v224 = v223 * v223;	// L293
      float x8_1;	// L294
      x8_1 = v224;	// L295
      float v226 = x8_1;	// L296
      float v227 = theta1_1;	// L297
      float v228 = v226 * v227;	// L298
      float x9_1;	// L299
      x9_1 = v228;	// L300
      float v230 = x8_1;	// L301
      float v231 = x2_1;	// L302
      float v232 = v230 * v231;	// L303
      float x10_1;	// L304
      x10_1 = v232;	// L305
      float v234 = x10_1;	// L306
      float v235 = theta1_1;	// L307
      float v236 = v234 * v235;	// L308
      float x11_1;	// L309
      x11_1 = v236;	// L310
      float v238 = x2_1;	// L311
      float v239 = v238 / 2.000000;	// L313
      float v240 = 1.000000 - v239;	// L315
      float v241 = x4_1;	// L316
      float v242 = v241 / 24.000000;	// L318
      float v243 = v240 + v242;	// L319
      float v244 = x6_1;	// L320
      float v245 = v244 / 720.000000;	// L322
      float v246 = v243 - v245;	// L323
      float v247 = x8_1;	// L324
      float v248 = v247 / 40320.000000;	// L326
      float v249 = v246 + v248;	// L327
      float v250 = x10_1;	// L328
      float v251 = v250 / 3628800.000000;	// L330
      float v252 = v249 - v251;	// L331
      float cos1_1;	// L332
      cos1_1 = v252;	// L333
      float v254 = theta1_1;	// L334
      float v255 = x3_1;	// L335
      float v256 = v255 / 6.000000;	// L337
      float v257 = v254 - v256;	// L338
      float v258 = x5_1;	// L339
      float v259 = v258 / 120.000000;	// L341
      float v260 = v257 + v259;	// L342
      float v261 = x7_1;	// L343
      float v262 = v261 / 5040.000000;	// L345
      float v263 = v260 - v262;	// L346
      float v264 = x9_1;	// L347
      float v265 = v264 / 362880.000000;	// L349
      float v266 = v263 + v265;	// L350
      float v267 = x11_1;	// L351
      float v268 = v267 / 39916800.000000;	// L353
      float v269 = v266 - v268;	// L354
      float sin1_1;	// L355
      sin1_1 = v269;	// L356
      float v271 = cos1_1;	// L357
      float v272 = v271 * v271;	// L358
      float v273 = sin1_1;	// L359
      float v274 = v273 * v273;	// L360
      float v275 = v272 - v274;	// L361
      float cos2_1;	// L362
      cos2_1 = v275;	// L363
      float v277 = cos1_1;	// L364
      float v278 = v277  << 1.000000;	// L365
      float v279 = sin1_1;	// L366
      float v280 = v278 * v279;	// L367
      float sin2_1;	// L368
      sin2_1 = v280;	// L369
      float v282 = cos2_1;	// L370
      float v283 = cos1_1;	// L371
      float v284 = v282 * v283;	// L372
      float v285 = sin2_1;	// L373
      float v286 = sin1_1;	// L374
      float v287 = v285 * v286;	// L375
      float v288 = v284 - v287;	// L376
      float cos3_1;	// L377
      cos3_1 = v288;	// L378
      float v290 = cos2_1;	// L379
      float v291 = sin1_1;	// L380
      float v292 = v290 * v291;	// L381
      float v293 = sin2_1;	// L382
      float v294 = cos1_1;	// L383
      float v295 = v293 * v294;	// L384
      float v296 = v292 + v295;	// L385
      float sin3_1;	// L386
      sin3_1 = v296;	// L387
      int v298 = g1;	// L388
      int v299 = v298 * 16;	// L391
      int v300 = v299;	// L392
      int v301 = j1;	// L393
      int v302 = v300 + v301;	// L394
      int v303 = v302;	// L395
      int i0_1;	// L396
      i0_1 = v303;	// L397
      int v305 = i0_1;	// L398
      int v306 = v305;	// L399
      int v307 = v306 + 4;	// L402
      int v308 = v307;	// L403
      int i1_1;	// L404
      i1_1 = v308;	// L405
      int v310 = i1_1;	// L406
      int v311 = v310;	// L407
      int v312 = v311 + 4;	// L408
      int v313 = v312;	// L409
      int i2_1;	// L410
      i2_1 = v313;	// L411
      int v315 = i2_1;	// L412
      int v316 = v315;	// L413
      int v317 = v316 + 4;	// L414
      int v318 = v317;	// L415
      int i3_1;	// L416
      i3_1 = v318;	// L417
      int v320 = i0_1;	// L418
      int v321 = v320;	// L419
      float v322 = buf_real[v321];	// L420
      float a0r_1;	// L421
      a0r_1 = v322;	// L422
      int v324 = i0_1;	// L423
      int v325 = v324;	// L424
      float v326 = buf_imag[v325];	// L425
      float a0i_1;	// L426
      a0i_1 = v326;	// L427
      int v328 = i1_1;	// L428
      int v329 = v328;	// L429
      float v330 = buf_real[v329];	// L430
      float a1r_1;	// L431
      a1r_1 = v330;	// L432
      int v332 = i1_1;	// L433
      int v333 = v332;	// L434
      float v334 = buf_imag[v333];	// L435
      float a1i_1;	// L436
      a1i_1 = v334;	// L437
      int v336 = i2_1;	// L438
      int v337 = v336;	// L439
      float v338 = buf_real[v337];	// L440
      float a2r_1;	// L441
      a2r_1 = v338;	// L442
      int v340 = i2_1;	// L443
      int v341 = v340;	// L444
      float v342 = buf_imag[v341];	// L445
      float a2i_1;	// L446
      a2i_1 = v342;	// L447
      int v344 = i3_1;	// L448
      int v345 = v344;	// L449
      float v346 = buf_real[v345];	// L450
      float a3r_1;	// L451
      a3r_1 = v346;	// L452
      int v348 = i3_1;	// L453
      int v349 = v348;	// L454
      float v350 = buf_imag[v349];	// L455
      float a3i_1;	// L456
      a3i_1 = v350;	// L457
      float v352 = a1r_1;	// L458
      float v353 = cos1_1;	// L459
      float v354 = v352 * v353;	// L460
      float v355 = a1i_1;	// L461
      float v356 = sin1_1;	// L462
      float v357 = v355 * v356;	// L463
      float v358 = v354 - v357;	// L464
      float Br_1;	// L465
      Br_1 = v358;	// L466
      float v360 = a1r_1;	// L467
      float v361 = sin1_1;	// L468
      float v362 = v360 * v361;	// L469
      float v363 = a1i_1;	// L470
      float v364 = cos1_1;	// L471
      float v365 = v363 * v364;	// L472
      float v366 = v362 + v365;	// L473
      float Bi_1;	// L474
      Bi_1 = v366;	// L475
      float v368 = a2r_1;	// L476
      float v369 = cos2_1;	// L477
      float v370 = v368 * v369;	// L478
      float v371 = a2i_1;	// L479
      float v372 = sin2_1;	// L480
      float v373 = v371 * v372;	// L481
      float v374 = v370 - v373;	// L482
      float Cr_1;	// L483
      Cr_1 = v374;	// L484
      float v376 = a2r_1;	// L485
      float v377 = sin2_1;	// L486
      float v378 = v376 * v377;	// L487
      float v379 = a2i_1;	// L488
      float v380 = cos2_1;	// L489
      float v381 = v379 * v380;	// L490
      float v382 = v378 + v381;	// L491
      float Ci_1;	// L492
      Ci_1 = v382;	// L493
      float v384 = a3r_1;	// L494
      float v385 = cos3_1;	// L495
      float v386 = v384 * v385;	// L496
      float v387 = a3i_1;	// L497
      float v388 = sin3_1;	// L498
      float v389 = v387 * v388;	// L499
      float v390 = v386 - v389;	// L500
      float Dr_1;	// L501
      Dr_1 = v390;	// L502
      float v392 = a3r_1;	// L503
      float v393 = sin3_1;	// L504
      float v394 = v392 * v393;	// L505
      float v395 = a3i_1;	// L506
      float v396 = cos3_1;	// L507
      float v397 = v395 * v396;	// L508
      float v398 = v394 + v397;	// L509
      float Di_1;	// L510
      Di_1 = v398;	// L511
      float v400 = a0r_1;	// L512
      float v401 = Cr_1;	// L513
      float v402 = v400 + v401;	// L514
      float t0r_1;	// L515
      t0r_1 = v402;	// L516
      float v404 = a0i_1;	// L517
      float v405 = Ci_1;	// L518
      float v406 = v404 + v405;	// L519
      float t0i_1;	// L520
      t0i_1 = v406;	// L521
      float v408 = a0r_1;	// L522
      float v409 = Cr_1;	// L523
      float v410 = v408 - v409;	// L524
      float t1r_1;	// L525
      t1r_1 = v410;	// L526
      float v412 = a0i_1;	// L527
      float v413 = Ci_1;	// L528
      float v414 = v412 - v413;	// L529
      float t1i_1;	// L530
      t1i_1 = v414;	// L531
      float v416 = Br_1;	// L532
      float v417 = Dr_1;	// L533
      float v418 = v416 + v417;	// L534
      float t2r_1;	// L535
      t2r_1 = v418;	// L536
      float v420 = Bi_1;	// L537
      float v421 = Di_1;	// L538
      float v422 = v420 + v421;	// L539
      float t2i_1;	// L540
      t2i_1 = v422;	// L541
      float v424 = Br_1;	// L542
      float v425 = Dr_1;	// L543
      float v426 = v424 - v425;	// L544
      float t3r_1;	// L545
      t3r_1 = v426;	// L546
      float v428 = Bi_1;	// L547
      float v429 = Di_1;	// L548
      float v430 = v428 - v429;	// L549
      float t3i_1;	// L550
      t3i_1 = v430;	// L551
      float v432 = t0r_1;	// L552
      float v433 = t2r_1;	// L553
      float v434 = v432 + v433;	// L554
      int v435 = i0_1;	// L555
      int v436 = v435;	// L556
      buf_real[v436] = v434;	// L557
      float v437 = t0i_1;	// L558
      float v438 = t2i_1;	// L559
      float v439 = v437 + v438;	// L560
      int v440 = i0_1;	// L561
      int v441 = v440;	// L562
      buf_imag[v441] = v439;	// L563
      float v442 = t0r_1;	// L564
      float v443 = t2r_1;	// L565
      float v444 = v442 - v443;	// L566
      int v445 = i2_1;	// L567
      int v446 = v445;	// L568
      buf_real[v446] = v444;	// L569
      float v447 = t0i_1;	// L570
      float v448 = t2i_1;	// L571
      float v449 = v447 - v448;	// L572
      int v450 = i2_1;	// L573
      int v451 = v450;	// L574
      buf_imag[v451] = v449;	// L575
      float v452 = t1r_1;	// L576
      float v453 = t3i_1;	// L577
      float v454 = v452 + v453;	// L578
      int v455 = i1_1;	// L579
      int v456 = v455;	// L580
      buf_real[v456] = v454;	// L581
      float v457 = t1i_1;	// L582
      float v458 = t3r_1;	// L583
      float v459 = v457 - v458;	// L584
      int v460 = i1_1;	// L585
      int v461 = v460;	// L586
      buf_imag[v461] = v459;	// L587
      float v462 = t1r_1;	// L588
      float v463 = t3i_1;	// L589
      float v464 = v462 - v463;	// L590
      int v465 = i3_1;	// L591
      int v466 = v465;	// L592
      buf_real[v466] = v464;	// L593
      float v467 = t1i_1;	// L594
      float v468 = t3r_1;	// L595
      float v469 = v467 + v468;	// L596
      int v470 = i3_1;	// L597
      int v471 = v470;	// L598
      buf_imag[v471] = v469;	// L599
    }
  }
  l_S_g2_4_g2: for (int g2 = 0; g2 < 16; g2++) {	// L602
  #pragma HLS pipeline II=5
    l_S_j2_4_j2: for (int j2 = 0; j2 < 16; j2++) {	// L603
      int v474 = j2;	// L604
      float v475 = v474;	// L605
      float j_f_2;	// L606
      j_f_2 = v475;	// L607
      float v477 = j_f_2;	// L610
      float v478 = v477 * -0.098175;	// L611
      float theta1_2;	// L612
      theta1_2 = v478;	// L613
      float v480 = theta1_2;	// L614
      float v481 = v480 * v480;	// L615
      float x2_2;	// L616
      x2_2 = v481;	// L617
      float v483 = x2_2;	// L618
      float v484 = theta1_2;	// L619
      float v485 = v483 * v484;	// L620
      float x3_2;	// L621
      x3_2 = v485;	// L622
      float v487 = x2_2;	// L623
      float v488 = v487 * v487;	// L624
      float x4_2;	// L625
      x4_2 = v488;	// L626
      float v490 = x4_2;	// L627
      float v491 = theta1_2;	// L628
      float v492 = v490 * v491;	// L629
      float x5_2;	// L630
      x5_2 = v492;	// L631
      float v494 = x4_2;	// L632
      float v495 = x2_2;	// L633
      float v496 = v494 * v495;	// L634
      float x6_2;	// L635
      x6_2 = v496;	// L636
      float v498 = x6_2;	// L637
      float v499 = theta1_2;	// L638
      float v500 = v498 * v499;	// L639
      float x7_2;	// L640
      x7_2 = v500;	// L641
      float v502 = x4_2;	// L642
      float v503 = v502 * v502;	// L643
      float x8_2;	// L644
      x8_2 = v503;	// L645
      float v505 = x8_2;	// L646
      float v506 = theta1_2;	// L647
      float v507 = v505 * v506;	// L648
      float x9_2;	// L649
      x9_2 = v507;	// L650
      float v509 = x8_2;	// L651
      float v510 = x2_2;	// L652
      float v511 = v509 * v510;	// L653
      float x10_2;	// L654
      x10_2 = v511;	// L655
      float v513 = x10_2;	// L656
      float v514 = theta1_2;	// L657
      float v515 = v513 * v514;	// L658
      float x11_2;	// L659
      x11_2 = v515;	// L660
      float v517 = x2_2;	// L661
      float v518 = v517 / 2.000000;	// L663
      float v519 = 1.000000 - v518;	// L665
      float v520 = x4_2;	// L666
      float v521 = v520 / 24.000000;	// L668
      float v522 = v519 + v521;	// L669
      float v523 = x6_2;	// L670
      float v524 = v523 / 720.000000;	// L672
      float v525 = v522 - v524;	// L673
      float v526 = x8_2;	// L674
      float v527 = v526 / 40320.000000;	// L676
      float v528 = v525 + v527;	// L677
      float v529 = x10_2;	// L678
      float v530 = v529 / 3628800.000000;	// L680
      float v531 = v528 - v530;	// L681
      float cos1_2;	// L682
      cos1_2 = v531;	// L683
      float v533 = theta1_2;	// L684
      float v534 = x3_2;	// L685
      float v535 = v534 / 6.000000;	// L687
      float v536 = v533 - v535;	// L688
      float v537 = x5_2;	// L689
      float v538 = v537 / 120.000000;	// L691
      float v539 = v536 + v538;	// L692
      float v540 = x7_2;	// L693
      float v541 = v540 / 5040.000000;	// L695
      float v542 = v539 - v541;	// L696
      float v543 = x9_2;	// L697
      float v544 = v543 / 362880.000000;	// L699
      float v545 = v542 + v544;	// L700
      float v546 = x11_2;	// L701
      float v547 = v546 / 39916800.000000;	// L703
      float v548 = v545 - v547;	// L704
      float sin1_2;	// L705
      sin1_2 = v548;	// L706
      float v550 = cos1_2;	// L707
      float v551 = v550 * v550;	// L708
      float v552 = sin1_2;	// L709
      float v553 = v552 * v552;	// L710
      float v554 = v551 - v553;	// L711
      float cos2_2;	// L712
      cos2_2 = v554;	// L713
      float v556 = cos1_2;	// L714
      float v557 = v556  << 1.000000;	// L715
      float v558 = sin1_2;	// L716
      float v559 = v557 * v558;	// L717
      float sin2_2;	// L718
      sin2_2 = v559;	// L719
      float v561 = cos2_2;	// L720
      float v562 = cos1_2;	// L721
      float v563 = v561 * v562;	// L722
      float v564 = sin2_2;	// L723
      float v565 = sin1_2;	// L724
      float v566 = v564 * v565;	// L725
      float v567 = v563 - v566;	// L726
      float cos3_2;	// L727
      cos3_2 = v567;	// L728
      float v569 = cos2_2;	// L729
      float v570 = sin1_2;	// L730
      float v571 = v569 * v570;	// L731
      float v572 = sin2_2;	// L732
      float v573 = cos1_2;	// L733
      float v574 = v572 * v573;	// L734
      float v575 = v571 + v574;	// L735
      float sin3_2;	// L736
      sin3_2 = v575;	// L737
      int v577 = g2;	// L738
      int v578 = v577 * 64;	// L741
      int v579 = v578;	// L742
      int v580 = j2;	// L743
      int v581 = v579 + v580;	// L744
      int v582 = v581;	// L745
      int i0_2;	// L746
      i0_2 = v582;	// L747
      int v584 = i0_2;	// L748
      int v585 = v584;	// L749
      int v586 = v585 + 16;	// L752
      int v587 = v586;	// L753
      int i1_2;	// L754
      i1_2 = v587;	// L755
      int v589 = i1_2;	// L756
      int v590 = v589;	// L757
      int v591 = v590 + 16;	// L758
      int v592 = v591;	// L759
      int i2_2;	// L760
      i2_2 = v592;	// L761
      int v594 = i2_2;	// L762
      int v595 = v594;	// L763
      int v596 = v595 + 16;	// L764
      int v597 = v596;	// L765
      int i3_2;	// L766
      i3_2 = v597;	// L767
      int v599 = i0_2;	// L768
      int v600 = v599;	// L769
      float v601 = buf_real[v600];	// L770
      float a0r_2;	// L771
      a0r_2 = v601;	// L772
      int v603 = i0_2;	// L773
      int v604 = v603;	// L774
      float v605 = buf_imag[v604];	// L775
      float a0i_2;	// L776
      a0i_2 = v605;	// L777
      int v607 = i1_2;	// L778
      int v608 = v607;	// L779
      float v609 = buf_real[v608];	// L780
      float a1r_2;	// L781
      a1r_2 = v609;	// L782
      int v611 = i1_2;	// L783
      int v612 = v611;	// L784
      float v613 = buf_imag[v612];	// L785
      float a1i_2;	// L786
      a1i_2 = v613;	// L787
      int v615 = i2_2;	// L788
      int v616 = v615;	// L789
      float v617 = buf_real[v616];	// L790
      float a2r_2;	// L791
      a2r_2 = v617;	// L792
      int v619 = i2_2;	// L793
      int v620 = v619;	// L794
      float v621 = buf_imag[v620];	// L795
      float a2i_2;	// L796
      a2i_2 = v621;	// L797
      int v623 = i3_2;	// L798
      int v624 = v623;	// L799
      float v625 = buf_real[v624];	// L800
      float a3r_2;	// L801
      a3r_2 = v625;	// L802
      int v627 = i3_2;	// L803
      int v628 = v627;	// L804
      float v629 = buf_imag[v628];	// L805
      float a3i_2;	// L806
      a3i_2 = v629;	// L807
      float v631 = a1r_2;	// L808
      float v632 = cos1_2;	// L809
      float v633 = v631 * v632;	// L810
      float v634 = a1i_2;	// L811
      float v635 = sin1_2;	// L812
      float v636 = v634 * v635;	// L813
      float v637 = v633 - v636;	// L814
      float Br_2;	// L815
      Br_2 = v637;	// L816
      float v639 = a1r_2;	// L817
      float v640 = sin1_2;	// L818
      float v641 = v639 * v640;	// L819
      float v642 = a1i_2;	// L820
      float v643 = cos1_2;	// L821
      float v644 = v642 * v643;	// L822
      float v645 = v641 + v644;	// L823
      float Bi_2;	// L824
      Bi_2 = v645;	// L825
      float v647 = a2r_2;	// L826
      float v648 = cos2_2;	// L827
      float v649 = v647 * v648;	// L828
      float v650 = a2i_2;	// L829
      float v651 = sin2_2;	// L830
      float v652 = v650 * v651;	// L831
      float v653 = v649 - v652;	// L832
      float Cr_2;	// L833
      Cr_2 = v653;	// L834
      float v655 = a2r_2;	// L835
      float v656 = sin2_2;	// L836
      float v657 = v655 * v656;	// L837
      float v658 = a2i_2;	// L838
      float v659 = cos2_2;	// L839
      float v660 = v658 * v659;	// L840
      float v661 = v657 + v660;	// L841
      float Ci_2;	// L842
      Ci_2 = v661;	// L843
      float v663 = a3r_2;	// L844
      float v664 = cos3_2;	// L845
      float v665 = v663 * v664;	// L846
      float v666 = a3i_2;	// L847
      float v667 = sin3_2;	// L848
      float v668 = v666 * v667;	// L849
      float v669 = v665 - v668;	// L850
      float Dr_2;	// L851
      Dr_2 = v669;	// L852
      float v671 = a3r_2;	// L853
      float v672 = sin3_2;	// L854
      float v673 = v671 * v672;	// L855
      float v674 = a3i_2;	// L856
      float v675 = cos3_2;	// L857
      float v676 = v674 * v675;	// L858
      float v677 = v673 + v676;	// L859
      float Di_2;	// L860
      Di_2 = v677;	// L861
      float v679 = a0r_2;	// L862
      float v680 = Cr_2;	// L863
      float v681 = v679 + v680;	// L864
      float t0r_2;	// L865
      t0r_2 = v681;	// L866
      float v683 = a0i_2;	// L867
      float v684 = Ci_2;	// L868
      float v685 = v683 + v684;	// L869
      float t0i_2;	// L870
      t0i_2 = v685;	// L871
      float v687 = a0r_2;	// L872
      float v688 = Cr_2;	// L873
      float v689 = v687 - v688;	// L874
      float t1r_2;	// L875
      t1r_2 = v689;	// L876
      float v691 = a0i_2;	// L877
      float v692 = Ci_2;	// L878
      float v693 = v691 - v692;	// L879
      float t1i_2;	// L880
      t1i_2 = v693;	// L881
      float v695 = Br_2;	// L882
      float v696 = Dr_2;	// L883
      float v697 = v695 + v696;	// L884
      float t2r_2;	// L885
      t2r_2 = v697;	// L886
      float v699 = Bi_2;	// L887
      float v700 = Di_2;	// L888
      float v701 = v699 + v700;	// L889
      float t2i_2;	// L890
      t2i_2 = v701;	// L891
      float v703 = Br_2;	// L892
      float v704 = Dr_2;	// L893
      float v705 = v703 - v704;	// L894
      float t3r_2;	// L895
      t3r_2 = v705;	// L896
      float v707 = Bi_2;	// L897
      float v708 = Di_2;	// L898
      float v709 = v707 - v708;	// L899
      float t3i_2;	// L900
      t3i_2 = v709;	// L901
      float v711 = t0r_2;	// L902
      float v712 = t2r_2;	// L903
      float v713 = v711 + v712;	// L904
      int v714 = i0_2;	// L905
      int v715 = v714;	// L906
      buf_real[v715] = v713;	// L907
      float v716 = t0i_2;	// L908
      float v717 = t2i_2;	// L909
      float v718 = v716 + v717;	// L910
      int v719 = i0_2;	// L911
      int v720 = v719;	// L912
      buf_imag[v720] = v718;	// L913
      float v721 = t0r_2;	// L914
      float v722 = t2r_2;	// L915
      float v723 = v721 - v722;	// L916
      int v724 = i2_2;	// L917
      int v725 = v724;	// L918
      buf_real[v725] = v723;	// L919
      float v726 = t0i_2;	// L920
      float v727 = t2i_2;	// L921
      float v728 = v726 - v727;	// L922
      int v729 = i2_2;	// L923
      int v730 = v729;	// L924
      buf_imag[v730] = v728;	// L925
      float v731 = t1r_2;	// L926
      float v732 = t3i_2;	// L927
      float v733 = v731 + v732;	// L928
      int v734 = i1_2;	// L929
      int v735 = v734;	// L930
      buf_real[v735] = v733;	// L931
      float v736 = t1i_2;	// L932
      float v737 = t3r_2;	// L933
      float v738 = v736 - v737;	// L934
      int v739 = i1_2;	// L935
      int v740 = v739;	// L936
      buf_imag[v740] = v738;	// L937
      float v741 = t1r_2;	// L938
      float v742 = t3i_2;	// L939
      float v743 = v741 - v742;	// L940
      int v744 = i3_2;	// L941
      int v745 = v744;	// L942
      buf_real[v745] = v743;	// L943
      float v746 = t1i_2;	// L944
      float v747 = t3r_2;	// L945
      float v748 = v746 + v747;	// L946
      int v749 = i3_2;	// L947
      int v750 = v749;	// L948
      buf_imag[v750] = v748;	// L949
    }
  }
  l_S_g3_6_g3: for (int g3 = 0; g3 < 4; g3++) {	// L952
    l_S_j3_6_j3: for (int j3 = 0; j3 < 64; j3++) {	// L953
    #pragma HLS pipeline II=5
      int v753 = j3;	// L954
      float v754 = v753;	// L955
      float j_f_3;	// L956
      j_f_3 = v754;	// L957
      float v756 = j_f_3;	// L960
      float v757 = v756 * -0.024544;	// L961
      float theta1_3;	// L962
      theta1_3 = v757;	// L963
      float v759 = theta1_3;	// L964
      float v760 = v759 * v759;	// L965
      float x2_3;	// L966
      x2_3 = v760;	// L967
      float v762 = x2_3;	// L968
      float v763 = theta1_3;	// L969
      float v764 = v762 * v763;	// L970
      float x3_3;	// L971
      x3_3 = v764;	// L972
      float v766 = x2_3;	// L973
      float v767 = v766 * v766;	// L974
      float x4_3;	// L975
      x4_3 = v767;	// L976
      float v769 = x4_3;	// L977
      float v770 = theta1_3;	// L978
      float v771 = v769 * v770;	// L979
      float x5_3;	// L980
      x5_3 = v771;	// L981
      float v773 = x4_3;	// L982
      float v774 = x2_3;	// L983
      float v775 = v773 * v774;	// L984
      float x6_3;	// L985
      x6_3 = v775;	// L986
      float v777 = x6_3;	// L987
      float v778 = theta1_3;	// L988
      float v779 = v777 * v778;	// L989
      float x7_3;	// L990
      x7_3 = v779;	// L991
      float v781 = x4_3;	// L992
      float v782 = v781 * v781;	// L993
      float x8_3;	// L994
      x8_3 = v782;	// L995
      float v784 = x8_3;	// L996
      float v785 = theta1_3;	// L997
      float v786 = v784 * v785;	// L998
      float x9_3;	// L999
      x9_3 = v786;	// L1000
      float v788 = x8_3;	// L1001
      float v789 = x2_3;	// L1002
      float v790 = v788 * v789;	// L1003
      float x10_3;	// L1004
      x10_3 = v790;	// L1005
      float v792 = x10_3;	// L1006
      float v793 = theta1_3;	// L1007
      float v794 = v792 * v793;	// L1008
      float x11_3;	// L1009
      x11_3 = v794;	// L1010
      float v796 = x2_3;	// L1011
      float v797 = v796 / 2.000000;	// L1013
      float v798 = 1.000000 - v797;	// L1015
      float v799 = x4_3;	// L1016
      float v800 = v799 / 24.000000;	// L1018
      float v801 = v798 + v800;	// L1019
      float v802 = x6_3;	// L1020
      float v803 = v802 / 720.000000;	// L1022
      float v804 = v801 - v803;	// L1023
      float v805 = x8_3;	// L1024
      float v806 = v805 / 40320.000000;	// L1026
      float v807 = v804 + v806;	// L1027
      float v808 = x10_3;	// L1028
      float v809 = v808 / 3628800.000000;	// L1030
      float v810 = v807 - v809;	// L1031
      float cos1_3;	// L1032
      cos1_3 = v810;	// L1033
      float v812 = theta1_3;	// L1034
      float v813 = x3_3;	// L1035
      float v814 = v813 / 6.000000;	// L1037
      float v815 = v812 - v814;	// L1038
      float v816 = x5_3;	// L1039
      float v817 = v816 / 120.000000;	// L1041
      float v818 = v815 + v817;	// L1042
      float v819 = x7_3;	// L1043
      float v820 = v819 / 5040.000000;	// L1045
      float v821 = v818 - v820;	// L1046
      float v822 = x9_3;	// L1047
      float v823 = v822 / 362880.000000;	// L1049
      float v824 = v821 + v823;	// L1050
      float v825 = x11_3;	// L1051
      float v826 = v825 / 39916800.000000;	// L1053
      float v827 = v824 - v826;	// L1054
      float sin1_3;	// L1055
      sin1_3 = v827;	// L1056
      float v829 = cos1_3;	// L1057
      float v830 = v829 * v829;	// L1058
      float v831 = sin1_3;	// L1059
      float v832 = v831 * v831;	// L1060
      float v833 = v830 - v832;	// L1061
      float cos2_3;	// L1062
      cos2_3 = v833;	// L1063
      float v835 = cos1_3;	// L1064
      float v836 = v835  << 1.000000;	// L1065
      float v837 = sin1_3;	// L1066
      float v838 = v836 * v837;	// L1067
      float sin2_3;	// L1068
      sin2_3 = v838;	// L1069
      float v840 = cos2_3;	// L1070
      float v841 = cos1_3;	// L1071
      float v842 = v840 * v841;	// L1072
      float v843 = sin2_3;	// L1073
      float v844 = sin1_3;	// L1074
      float v845 = v843 * v844;	// L1075
      float v846 = v842 - v845;	// L1076
      float cos3_3;	// L1077
      cos3_3 = v846;	// L1078
      float v848 = cos2_3;	// L1079
      float v849 = sin1_3;	// L1080
      float v850 = v848 * v849;	// L1081
      float v851 = sin2_3;	// L1082
      float v852 = cos1_3;	// L1083
      float v853 = v851 * v852;	// L1084
      float v854 = v850 + v853;	// L1085
      float sin3_3;	// L1086
      sin3_3 = v854;	// L1087
      int v856 = g3;	// L1088
      int v857 = v856 * 256;	// L1091
      int v858 = v857;	// L1092
      int v859 = j3;	// L1093
      int v860 = v858 + v859;	// L1094
      int v861 = v860;	// L1095
      int i0_3;	// L1096
      i0_3 = v861;	// L1097
      int v863 = i0_3;	// L1098
      int v864 = v863;	// L1099
      int v865 = v864 + 64;	// L1102
      int v866 = v865;	// L1103
      int i1_3;	// L1104
      i1_3 = v866;	// L1105
      int v868 = i1_3;	// L1106
      int v869 = v868;	// L1107
      int v870 = v869 + 64;	// L1108
      int v871 = v870;	// L1109
      int i2_3;	// L1110
      i2_3 = v871;	// L1111
      int v873 = i2_3;	// L1112
      int v874 = v873;	// L1113
      int v875 = v874 + 64;	// L1114
      int v876 = v875;	// L1115
      int i3_3;	// L1116
      i3_3 = v876;	// L1117
      int v878 = i0_3;	// L1118
      int v879 = v878;	// L1119
      float v880 = buf_real[v879];	// L1120
      float a0r_3;	// L1121
      a0r_3 = v880;	// L1122
      int v882 = i0_3;	// L1123
      int v883 = v882;	// L1124
      float v884 = buf_imag[v883];	// L1125
      float a0i_3;	// L1126
      a0i_3 = v884;	// L1127
      int v886 = i1_3;	// L1128
      int v887 = v886;	// L1129
      float v888 = buf_real[v887];	// L1130
      float a1r_3;	// L1131
      a1r_3 = v888;	// L1132
      int v890 = i1_3;	// L1133
      int v891 = v890;	// L1134
      float v892 = buf_imag[v891];	// L1135
      float a1i_3;	// L1136
      a1i_3 = v892;	// L1137
      int v894 = i2_3;	// L1138
      int v895 = v894;	// L1139
      float v896 = buf_real[v895];	// L1140
      float a2r_3;	// L1141
      a2r_3 = v896;	// L1142
      int v898 = i2_3;	// L1143
      int v899 = v898;	// L1144
      float v900 = buf_imag[v899];	// L1145
      float a2i_3;	// L1146
      a2i_3 = v900;	// L1147
      int v902 = i3_3;	// L1148
      int v903 = v902;	// L1149
      float v904 = buf_real[v903];	// L1150
      float a3r_3;	// L1151
      a3r_3 = v904;	// L1152
      int v906 = i3_3;	// L1153
      int v907 = v906;	// L1154
      float v908 = buf_imag[v907];	// L1155
      float a3i_3;	// L1156
      a3i_3 = v908;	// L1157
      float v910 = a1r_3;	// L1158
      float v911 = cos1_3;	// L1159
      float v912 = v910 * v911;	// L1160
      float v913 = a1i_3;	// L1161
      float v914 = sin1_3;	// L1162
      float v915 = v913 * v914;	// L1163
      float v916 = v912 - v915;	// L1164
      float Br_3;	// L1165
      Br_3 = v916;	// L1166
      float v918 = a1r_3;	// L1167
      float v919 = sin1_3;	// L1168
      float v920 = v918 * v919;	// L1169
      float v921 = a1i_3;	// L1170
      float v922 = cos1_3;	// L1171
      float v923 = v921 * v922;	// L1172
      float v924 = v920 + v923;	// L1173
      float Bi_3;	// L1174
      Bi_3 = v924;	// L1175
      float v926 = a2r_3;	// L1176
      float v927 = cos2_3;	// L1177
      float v928 = v926 * v927;	// L1178
      float v929 = a2i_3;	// L1179
      float v930 = sin2_3;	// L1180
      float v931 = v929 * v930;	// L1181
      float v932 = v928 - v931;	// L1182
      float Cr_3;	// L1183
      Cr_3 = v932;	// L1184
      float v934 = a2r_3;	// L1185
      float v935 = sin2_3;	// L1186
      float v936 = v934 * v935;	// L1187
      float v937 = a2i_3;	// L1188
      float v938 = cos2_3;	// L1189
      float v939 = v937 * v938;	// L1190
      float v940 = v936 + v939;	// L1191
      float Ci_3;	// L1192
      Ci_3 = v940;	// L1193
      float v942 = a3r_3;	// L1194
      float v943 = cos3_3;	// L1195
      float v944 = v942 * v943;	// L1196
      float v945 = a3i_3;	// L1197
      float v946 = sin3_3;	// L1198
      float v947 = v945 * v946;	// L1199
      float v948 = v944 - v947;	// L1200
      float Dr_3;	// L1201
      Dr_3 = v948;	// L1202
      float v950 = a3r_3;	// L1203
      float v951 = sin3_3;	// L1204
      float v952 = v950 * v951;	// L1205
      float v953 = a3i_3;	// L1206
      float v954 = cos3_3;	// L1207
      float v955 = v953 * v954;	// L1208
      float v956 = v952 + v955;	// L1209
      float Di_3;	// L1210
      Di_3 = v956;	// L1211
      float v958 = a0r_3;	// L1212
      float v959 = Cr_3;	// L1213
      float v960 = v958 + v959;	// L1214
      float t0r_3;	// L1215
      t0r_3 = v960;	// L1216
      float v962 = a0i_3;	// L1217
      float v963 = Ci_3;	// L1218
      float v964 = v962 + v963;	// L1219
      float t0i_3;	// L1220
      t0i_3 = v964;	// L1221
      float v966 = a0r_3;	// L1222
      float v967 = Cr_3;	// L1223
      float v968 = v966 - v967;	// L1224
      float t1r_3;	// L1225
      t1r_3 = v968;	// L1226
      float v970 = a0i_3;	// L1227
      float v971 = Ci_3;	// L1228
      float v972 = v970 - v971;	// L1229
      float t1i_3;	// L1230
      t1i_3 = v972;	// L1231
      float v974 = Br_3;	// L1232
      float v975 = Dr_3;	// L1233
      float v976 = v974 + v975;	// L1234
      float t2r_3;	// L1235
      t2r_3 = v976;	// L1236
      float v978 = Bi_3;	// L1237
      float v979 = Di_3;	// L1238
      float v980 = v978 + v979;	// L1239
      float t2i_3;	// L1240
      t2i_3 = v980;	// L1241
      float v982 = Br_3;	// L1242
      float v983 = Dr_3;	// L1243
      float v984 = v982 - v983;	// L1244
      float t3r_3;	// L1245
      t3r_3 = v984;	// L1246
      float v986 = Bi_3;	// L1247
      float v987 = Di_3;	// L1248
      float v988 = v986 - v987;	// L1249
      float t3i_3;	// L1250
      t3i_3 = v988;	// L1251
      float v990 = t0r_3;	// L1252
      float v991 = t2r_3;	// L1253
      float v992 = v990 + v991;	// L1254
      int v993 = i0_3;	// L1255
      int v994 = v993;	// L1256
      buf_real[v994] = v992;	// L1257
      float v995 = t0i_3;	// L1258
      float v996 = t2i_3;	// L1259
      float v997 = v995 + v996;	// L1260
      int v998 = i0_3;	// L1261
      int v999 = v998;	// L1262
      buf_imag[v999] = v997;	// L1263
      float v1000 = t0r_3;	// L1264
      float v1001 = t2r_3;	// L1265
      float v1002 = v1000 - v1001;	// L1266
      int v1003 = i2_3;	// L1267
      int v1004 = v1003;	// L1268
      buf_real[v1004] = v1002;	// L1269
      float v1005 = t0i_3;	// L1270
      float v1006 = t2i_3;	// L1271
      float v1007 = v1005 - v1006;	// L1272
      int v1008 = i2_3;	// L1273
      int v1009 = v1008;	// L1274
      buf_imag[v1009] = v1007;	// L1275
      float v1010 = t1r_3;	// L1276
      float v1011 = t3i_3;	// L1277
      float v1012 = v1010 + v1011;	// L1278
      int v1013 = i1_3;	// L1279
      int v1014 = v1013;	// L1280
      buf_real[v1014] = v1012;	// L1281
      float v1015 = t1i_3;	// L1282
      float v1016 = t3r_3;	// L1283
      float v1017 = v1015 - v1016;	// L1284
      int v1018 = i1_3;	// L1285
      int v1019 = v1018;	// L1286
      buf_imag[v1019] = v1017;	// L1287
      float v1020 = t1r_3;	// L1288
      float v1021 = t3i_3;	// L1289
      float v1022 = v1020 - v1021;	// L1290
      int v1023 = i3_3;	// L1291
      int v1024 = v1023;	// L1292
      buf_real[v1024] = v1022;	// L1293
      float v1025 = t1i_3;	// L1294
      float v1026 = t3r_3;	// L1295
      float v1027 = v1025 + v1026;	// L1296
      int v1028 = i3_3;	// L1297
      int v1029 = v1028;	// L1298
      buf_imag[v1029] = v1027;	// L1299
    }
  }
  l_S_j4_8_j4: for (int j4 = 0; j4 < 256; j4++) {	// L1302
  #pragma HLS pipeline II=5
    int v1031 = j4;	// L1303
    float v1032 = v1031;	// L1304
    float j_f_4;	// L1305
    j_f_4 = v1032;	// L1306
    float v1034 = j_f_4;	// L1309
    float v1035 = v1034 * -0.006136;	// L1310
    float theta1_4;	// L1311
    theta1_4 = v1035;	// L1312
    float v1037 = theta1_4;	// L1313
    float v1038 = v1037 * v1037;	// L1314
    float x2_4;	// L1315
    x2_4 = v1038;	// L1316
    float v1040 = x2_4;	// L1317
    float v1041 = theta1_4;	// L1318
    float v1042 = v1040 * v1041;	// L1319
    float x3_4;	// L1320
    x3_4 = v1042;	// L1321
    float v1044 = x2_4;	// L1322
    float v1045 = v1044 * v1044;	// L1323
    float x4_4;	// L1324
    x4_4 = v1045;	// L1325
    float v1047 = x4_4;	// L1326
    float v1048 = theta1_4;	// L1327
    float v1049 = v1047 * v1048;	// L1328
    float x5_4;	// L1329
    x5_4 = v1049;	// L1330
    float v1051 = x4_4;	// L1331
    float v1052 = x2_4;	// L1332
    float v1053 = v1051 * v1052;	// L1333
    float x6_4;	// L1334
    x6_4 = v1053;	// L1335
    float v1055 = x6_4;	// L1336
    float v1056 = theta1_4;	// L1337
    float v1057 = v1055 * v1056;	// L1338
    float x7_4;	// L1339
    x7_4 = v1057;	// L1340
    float v1059 = x4_4;	// L1341
    float v1060 = v1059 * v1059;	// L1342
    float x8_4;	// L1343
    x8_4 = v1060;	// L1344
    float v1062 = x8_4;	// L1345
    float v1063 = theta1_4;	// L1346
    float v1064 = v1062 * v1063;	// L1347
    float x9_4;	// L1348
    x9_4 = v1064;	// L1349
    float v1066 = x8_4;	// L1350
    float v1067 = x2_4;	// L1351
    float v1068 = v1066 * v1067;	// L1352
    float x10_4;	// L1353
    x10_4 = v1068;	// L1354
    float v1070 = x10_4;	// L1355
    float v1071 = theta1_4;	// L1356
    float v1072 = v1070 * v1071;	// L1357
    float x11_4;	// L1358
    x11_4 = v1072;	// L1359
    float v1074 = x2_4;	// L1360
    float v1075 = v1074 / 2.000000;	// L1362
    float v1076 = 1.000000 - v1075;	// L1364
    float v1077 = x4_4;	// L1365
    float v1078 = v1077 / 24.000000;	// L1367
    float v1079 = v1076 + v1078;	// L1368
    float v1080 = x6_4;	// L1369
    float v1081 = v1080 / 720.000000;	// L1371
    float v1082 = v1079 - v1081;	// L1372
    float v1083 = x8_4;	// L1373
    float v1084 = v1083 / 40320.000000;	// L1375
    float v1085 = v1082 + v1084;	// L1376
    float v1086 = x10_4;	// L1377
    float v1087 = v1086 / 3628800.000000;	// L1379
    float v1088 = v1085 - v1087;	// L1380
    float cos1_4;	// L1381
    cos1_4 = v1088;	// L1382
    float v1090 = theta1_4;	// L1383
    float v1091 = x3_4;	// L1384
    float v1092 = v1091 / 6.000000;	// L1386
    float v1093 = v1090 - v1092;	// L1387
    float v1094 = x5_4;	// L1388
    float v1095 = v1094 / 120.000000;	// L1390
    float v1096 = v1093 + v1095;	// L1391
    float v1097 = x7_4;	// L1392
    float v1098 = v1097 / 5040.000000;	// L1394
    float v1099 = v1096 - v1098;	// L1395
    float v1100 = x9_4;	// L1396
    float v1101 = v1100 / 362880.000000;	// L1398
    float v1102 = v1099 + v1101;	// L1399
    float v1103 = x11_4;	// L1400
    float v1104 = v1103 / 39916800.000000;	// L1402
    float v1105 = v1102 - v1104;	// L1403
    float sin1_4;	// L1404
    sin1_4 = v1105;	// L1405
    float v1107 = cos1_4;	// L1406
    float v1108 = v1107 * v1107;	// L1407
    float v1109 = sin1_4;	// L1408
    float v1110 = v1109 * v1109;	// L1409
    float v1111 = v1108 - v1110;	// L1410
    float cos2_4;	// L1411
    cos2_4 = v1111;	// L1412
    float v1113 = cos1_4;	// L1413
    float v1114 = v1113  << 1.000000;	// L1414
    float v1115 = sin1_4;	// L1415
    float v1116 = v1114 * v1115;	// L1416
    float sin2_4;	// L1417
    sin2_4 = v1116;	// L1418
    float v1118 = cos2_4;	// L1419
    float v1119 = cos1_4;	// L1420
    float v1120 = v1118 * v1119;	// L1421
    float v1121 = sin2_4;	// L1422
    float v1122 = sin1_4;	// L1423
    float v1123 = v1121 * v1122;	// L1424
    float v1124 = v1120 - v1123;	// L1425
    float cos3_4;	// L1426
    cos3_4 = v1124;	// L1427
    float v1126 = cos2_4;	// L1428
    float v1127 = sin1_4;	// L1429
    float v1128 = v1126 * v1127;	// L1430
    float v1129 = sin2_4;	// L1431
    float v1130 = cos1_4;	// L1432
    float v1131 = v1129 * v1130;	// L1433
    float v1132 = v1128 + v1131;	// L1434
    float sin3_4;	// L1435
    sin3_4 = v1132;	// L1436
    int i0_4;	// L1437
    i0_4 = v1031;	// L1438
    int v1135 = i0_4;	// L1439
    int v1136 = v1135;	// L1440
    int v1137 = v1136 + 256;	// L1443
    int v1138 = v1137;	// L1444
    int i1_4;	// L1445
    i1_4 = v1138;	// L1446
    int v1140 = i1_4;	// L1447
    int v1141 = v1140;	// L1448
    int v1142 = v1141 + 256;	// L1449
    int v1143 = v1142;	// L1450
    int i2_4;	// L1451
    i2_4 = v1143;	// L1452
    int v1145 = i2_4;	// L1453
    int v1146 = v1145;	// L1454
    int v1147 = v1146 + 256;	// L1455
    int v1148 = v1147;	// L1456
    int i3_4;	// L1457
    i3_4 = v1148;	// L1458
    int v1150 = i0_4;	// L1459
    int v1151 = v1150;	// L1460
    float v1152 = buf_real[v1151];	// L1461
    float a0r_4;	// L1462
    a0r_4 = v1152;	// L1463
    int v1154 = i0_4;	// L1464
    int v1155 = v1154;	// L1465
    float v1156 = buf_imag[v1155];	// L1466
    float a0i_4;	// L1467
    a0i_4 = v1156;	// L1468
    int v1158 = i1_4;	// L1469
    int v1159 = v1158;	// L1470
    float v1160 = buf_real[v1159];	// L1471
    float a1r_4;	// L1472
    a1r_4 = v1160;	// L1473
    int v1162 = i1_4;	// L1474
    int v1163 = v1162;	// L1475
    float v1164 = buf_imag[v1163];	// L1476
    float a1i_4;	// L1477
    a1i_4 = v1164;	// L1478
    int v1166 = i2_4;	// L1479
    int v1167 = v1166;	// L1480
    float v1168 = buf_real[v1167];	// L1481
    float a2r_4;	// L1482
    a2r_4 = v1168;	// L1483
    int v1170 = i2_4;	// L1484
    int v1171 = v1170;	// L1485
    float v1172 = buf_imag[v1171];	// L1486
    float a2i_4;	// L1487
    a2i_4 = v1172;	// L1488
    int v1174 = i3_4;	// L1489
    int v1175 = v1174;	// L1490
    float v1176 = buf_real[v1175];	// L1491
    float a3r_4;	// L1492
    a3r_4 = v1176;	// L1493
    int v1178 = i3_4;	// L1494
    int v1179 = v1178;	// L1495
    float v1180 = buf_imag[v1179];	// L1496
    float a3i_4;	// L1497
    a3i_4 = v1180;	// L1498
    float v1182 = a1r_4;	// L1499
    float v1183 = cos1_4;	// L1500
    float v1184 = v1182 * v1183;	// L1501
    float v1185 = a1i_4;	// L1502
    float v1186 = sin1_4;	// L1503
    float v1187 = v1185 * v1186;	// L1504
    float v1188 = v1184 - v1187;	// L1505
    float Br_4;	// L1506
    Br_4 = v1188;	// L1507
    float v1190 = a1r_4;	// L1508
    float v1191 = sin1_4;	// L1509
    float v1192 = v1190 * v1191;	// L1510
    float v1193 = a1i_4;	// L1511
    float v1194 = cos1_4;	// L1512
    float v1195 = v1193 * v1194;	// L1513
    float v1196 = v1192 + v1195;	// L1514
    float Bi_4;	// L1515
    Bi_4 = v1196;	// L1516
    float v1198 = a2r_4;	// L1517
    float v1199 = cos2_4;	// L1518
    float v1200 = v1198 * v1199;	// L1519
    float v1201 = a2i_4;	// L1520
    float v1202 = sin2_4;	// L1521
    float v1203 = v1201 * v1202;	// L1522
    float v1204 = v1200 - v1203;	// L1523
    float Cr_4;	// L1524
    Cr_4 = v1204;	// L1525
    float v1206 = a2r_4;	// L1526
    float v1207 = sin2_4;	// L1527
    float v1208 = v1206 * v1207;	// L1528
    float v1209 = a2i_4;	// L1529
    float v1210 = cos2_4;	// L1530
    float v1211 = v1209 * v1210;	// L1531
    float v1212 = v1208 + v1211;	// L1532
    float Ci_4;	// L1533
    Ci_4 = v1212;	// L1534
    float v1214 = a3r_4;	// L1535
    float v1215 = cos3_4;	// L1536
    float v1216 = v1214 * v1215;	// L1537
    float v1217 = a3i_4;	// L1538
    float v1218 = sin3_4;	// L1539
    float v1219 = v1217 * v1218;	// L1540
    float v1220 = v1216 - v1219;	// L1541
    float Dr_4;	// L1542
    Dr_4 = v1220;	// L1543
    float v1222 = a3r_4;	// L1544
    float v1223 = sin3_4;	// L1545
    float v1224 = v1222 * v1223;	// L1546
    float v1225 = a3i_4;	// L1547
    float v1226 = cos3_4;	// L1548
    float v1227 = v1225 * v1226;	// L1549
    float v1228 = v1224 + v1227;	// L1550
    float Di_4;	// L1551
    Di_4 = v1228;	// L1552
    float v1230 = a0r_4;	// L1553
    float v1231 = Cr_4;	// L1554
    float v1232 = v1230 + v1231;	// L1555
    float t0r_4;	// L1556
    t0r_4 = v1232;	// L1557
    float v1234 = a0i_4;	// L1558
    float v1235 = Ci_4;	// L1559
    float v1236 = v1234 + v1235;	// L1560
    float t0i_4;	// L1561
    t0i_4 = v1236;	// L1562
    float v1238 = a0r_4;	// L1563
    float v1239 = Cr_4;	// L1564
    float v1240 = v1238 - v1239;	// L1565
    float t1r_4;	// L1566
    t1r_4 = v1240;	// L1567
    float v1242 = a0i_4;	// L1568
    float v1243 = Ci_4;	// L1569
    float v1244 = v1242 - v1243;	// L1570
    float t1i_4;	// L1571
    t1i_4 = v1244;	// L1572
    float v1246 = Br_4;	// L1573
    float v1247 = Dr_4;	// L1574
    float v1248 = v1246 + v1247;	// L1575
    float t2r_4;	// L1576
    t2r_4 = v1248;	// L1577
    float v1250 = Bi_4;	// L1578
    float v1251 = Di_4;	// L1579
    float v1252 = v1250 + v1251;	// L1580
    float t2i_4;	// L1581
    t2i_4 = v1252;	// L1582
    float v1254 = Br_4;	// L1583
    float v1255 = Dr_4;	// L1584
    float v1256 = v1254 - v1255;	// L1585
    float t3r_4;	// L1586
    t3r_4 = v1256;	// L1587
    float v1258 = Bi_4;	// L1588
    float v1259 = Di_4;	// L1589
    float v1260 = v1258 - v1259;	// L1590
    float t3i_4;	// L1591
    t3i_4 = v1260;	// L1592
    float v1262 = t0r_4;	// L1593
    float v1263 = t2r_4;	// L1594
    float v1264 = v1262 + v1263;	// L1595
    int v1265 = i0_4;	// L1596
    int v1266 = v1265;	// L1597
    buf_real[v1266] = v1264;	// L1598
    float v1267 = t0i_4;	// L1599
    float v1268 = t2i_4;	// L1600
    float v1269 = v1267 + v1268;	// L1601
    int v1270 = i0_4;	// L1602
    int v1271 = v1270;	// L1603
    buf_imag[v1271] = v1269;	// L1604
    float v1272 = t0r_4;	// L1605
    float v1273 = t2r_4;	// L1606
    float v1274 = v1272 - v1273;	// L1607
    int v1275 = i2_4;	// L1608
    int v1276 = v1275;	// L1609
    buf_real[v1276] = v1274;	// L1610
    float v1277 = t0i_4;	// L1611
    float v1278 = t2i_4;	// L1612
    float v1279 = v1277 - v1278;	// L1613
    int v1280 = i2_4;	// L1614
    int v1281 = v1280;	// L1615
    buf_imag[v1281] = v1279;	// L1616
    float v1282 = t1r_4;	// L1617
    float v1283 = t3i_4;	// L1618
    float v1284 = v1282 + v1283;	// L1619
    int v1285 = i1_4;	// L1620
    int v1286 = v1285;	// L1621
    buf_real[v1286] = v1284;	// L1622
    float v1287 = t1i_4;	// L1623
    float v1288 = t3r_4;	// L1624
    float v1289 = v1287 - v1288;	// L1625
    int v1290 = i1_4;	// L1626
    int v1291 = v1290;	// L1627
    buf_imag[v1291] = v1289;	// L1628
    float v1292 = t1r_4;	// L1629
    float v1293 = t3i_4;	// L1630
    float v1294 = v1292 - v1293;	// L1631
    int v1295 = i3_4;	// L1632
    int v1296 = v1295;	// L1633
    buf_real[v1296] = v1294;	// L1634
    float v1297 = t1i_4;	// L1635
    float v1298 = t3r_4;	// L1636
    float v1299 = v1297 + v1298;	// L1637
    int v1300 = i3_4;	// L1638
    int v1301 = v1300;	// L1639
    buf_imag[v1301] = v1299;	// L1640
  }
  l_S_ic_9_ic: for (int ic = 0; ic < 1024; ic++) {	// L1642
  #pragma HLS pipeline II=5
    float v1303 = buf_real[ic];	// L1643
    v2[ic] = v1303;	// L1644
    float v1304 = buf_imag[ic];	// L1645
    v3[ic] = v1304;	// L1646
  }
}
#pragma pocc-region-end
}

