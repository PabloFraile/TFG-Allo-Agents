
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
  l_S_ip_0_ip: for (int ip = 0; ip < 1024; ip++) {	// L5
    int v7 = ip;	// L6
    int n0;	// L7
    n0 = v7;	// L8
    int v9 = n0;	// L9
    int v10 = v9 % 4;	// L12
    int d0;	// L13
    d0 = v10;	// L14
    int v12 = n0;	// L15
    int v13 = v12 / 4;	// L18
    int n1;	// L19
    n1 = v13;	// L20
    int v15 = n1;	// L21
    int v16 = v15 % 4;	// L24
    int d1;	// L25
    d1 = v16;	// L26
    int v18 = n1;	// L27
    int v19 = v18 / 4;	// L30
    int n2;	// L31
    n2 = v19;	// L32
    int v21 = n2;	// L33
    int v22 = v21 % 4;	// L36
    int d2;	// L37
    d2 = v22;	// L38
    int v24 = n2;	// L39
    int v25 = v24 / 4;	// L42
    int n3;	// L43
    n3 = v25;	// L44
    int v27 = n3;	// L45
    int v28 = v27 % 4;	// L48
    int d3;	// L49
    d3 = v28;	// L50
    int v30 = n3;	// L51
    int v31 = v30 / 4;	// L54
    int n4;	// L55
    n4 = v31;	// L56
    int v33 = n4;	// L57
    int v34 = v33 % 4;	// L60
    int d4;	// L61
    d4 = v34;	// L62
    int v36 = d0;	// L63
    int v37 = v36;	// L64
    int v38 = v37 * 256;	// L68
    int v39 = d1;	// L69
    int v40 = v39;	// L70
    int v41 = v40 * 64;	// L74
    int v42 = v38;	// L75
    int v43 = v41;	// L76
    int v44 = v42 + v43;	// L77
    int v45 = d2;	// L78
    int v46 = v45;	// L79
    int v47 = v46 * 16;	// L83
    int v48 = v44;	// L84
    int v49 = v47;	// L85
    int v50 = v48 + v49;	// L86
    int v51 = d3;	// L87
    int v52 = v51;	// L88
    int v53 = v52 * 4;	// L92
    int v54 = v50;	// L93
    int v55 = v53;	// L94
    int v56 = v54 + v55;	// L95
    int v57 = d4;	// L96
    int v58 = v56;	// L97
    int v59 = v57;	// L98
    int v60 = v58 + v59;	// L99
    int v61 = v60;	// L100
    int ri;	// L101
    ri = v61;	// L102
    int v63 = ri;	// L103
    int v64 = v63;	// L104
    float v65 = v0[v64];	// L105
    buf_real[ip] = v65;	// L106
    int v66 = ri;	// L107
    int v67 = v66;	// L108
    float v68 = v1[v67];	// L109
    buf_imag[ip] = v68;	// L110
  }
  l_S_g0_1_g0: for (int g0 = 0; g0 < 256; g0++) {	// L112
    int v70 = g0;	// L113
    int v71 = v70 * 4;	// L117
    int v72 = v71;	// L118
    int i0_0;	// L119
    i0_0 = v72;	// L120
    int v74 = i0_0;	// L121
    int v75 = v74;	// L122
    int v76 = v75 + 1;	// L126
    int v77 = v76;	// L127
    int i1_0;	// L128
    i1_0 = v77;	// L129
    int v79 = i0_0;	// L130
    int v80 = v79;	// L131
    int v81 = v80 + 2;	// L135
    int v82 = v81;	// L136
    int i2_0;	// L137
    i2_0 = v82;	// L138
    int v84 = i0_0;	// L139
    int v85 = v84;	// L140
    int v86 = v85 + 3;	// L144
    int v87 = v86;	// L145
    int i3_0;	// L146
    i3_0 = v87;	// L147
    int v89 = i0_0;	// L148
    int v90 = v89;	// L149
    float v91 = buf_real[v90];	// L150
    float a0r_0;	// L151
    a0r_0 = v91;	// L152
    int v93 = i0_0;	// L153
    int v94 = v93;	// L154
    float v95 = buf_imag[v94];	// L155
    float a0i_0;	// L156
    a0i_0 = v95;	// L157
    int v97 = i1_0;	// L158
    int v98 = v97;	// L159
    float v99 = buf_real[v98];	// L160
    float a1r_0;	// L161
    a1r_0 = v99;	// L162
    int v101 = i1_0;	// L163
    int v102 = v101;	// L164
    float v103 = buf_imag[v102];	// L165
    float a1i_0;	// L166
    a1i_0 = v103;	// L167
    int v105 = i2_0;	// L168
    int v106 = v105;	// L169
    float v107 = buf_real[v106];	// L170
    float a2r_0;	// L171
    a2r_0 = v107;	// L172
    int v109 = i2_0;	// L173
    int v110 = v109;	// L174
    float v111 = buf_imag[v110];	// L175
    float a2i_0;	// L176
    a2i_0 = v111;	// L177
    int v113 = i3_0;	// L178
    int v114 = v113;	// L179
    float v115 = buf_real[v114];	// L180
    float a3r_0;	// L181
    a3r_0 = v115;	// L182
    int v117 = i3_0;	// L183
    int v118 = v117;	// L184
    float v119 = buf_imag[v118];	// L185
    float a3i_0;	// L186
    a3i_0 = v119;	// L187
    float v121 = a0r_0;	// L188
    float v122 = a2r_0;	// L189
    float v123 = v121 + v122;	// L190
    float t0r_0;	// L191
    t0r_0 = v123;	// L192
    float v125 = a0i_0;	// L193
    float v126 = a2i_0;	// L194
    float v127 = v125 + v126;	// L195
    float t0i_0;	// L196
    t0i_0 = v127;	// L197
    float v129 = a0r_0;	// L198
    float v130 = a2r_0;	// L199
    float v131 = v129 - v130;	// L200
    float t1r_0;	// L201
    t1r_0 = v131;	// L202
    float v133 = a0i_0;	// L203
    float v134 = a2i_0;	// L204
    float v135 = v133 - v134;	// L205
    float t1i_0;	// L206
    t1i_0 = v135;	// L207
    float v137 = a1r_0;	// L208
    float v138 = a3r_0;	// L209
    float v139 = v137 + v138;	// L210
    float t2r_0;	// L211
    t2r_0 = v139;	// L212
    float v141 = a1i_0;	// L213
    float v142 = a3i_0;	// L214
    float v143 = v141 + v142;	// L215
    float t2i_0;	// L216
    t2i_0 = v143;	// L217
    float v145 = a1r_0;	// L218
    float v146 = a3r_0;	// L219
    float v147 = v145 - v146;	// L220
    float t3r_0;	// L221
    t3r_0 = v147;	// L222
    float v149 = a1i_0;	// L223
    float v150 = a3i_0;	// L224
    float v151 = v149 - v150;	// L225
    float t3i_0;	// L226
    t3i_0 = v151;	// L227
    float v153 = t0r_0;	// L228
    float v154 = t2r_0;	// L229
    float v155 = v153 + v154;	// L230
    int v156 = i0_0;	// L231
    int v157 = v156;	// L232
    buf_real[v157] = v155;	// L233
    float v158 = t0i_0;	// L234
    float v159 = t2i_0;	// L235
    float v160 = v158 + v159;	// L236
    int v161 = i0_0;	// L237
    int v162 = v161;	// L238
    buf_imag[v162] = v160;	// L239
    float v163 = t0r_0;	// L240
    float v164 = t2r_0;	// L241
    float v165 = v163 - v164;	// L242
    int v166 = i2_0;	// L243
    int v167 = v166;	// L244
    buf_real[v167] = v165;	// L245
    float v168 = t0i_0;	// L246
    float v169 = t2i_0;	// L247
    float v170 = v168 - v169;	// L248
    int v171 = i2_0;	// L249
    int v172 = v171;	// L250
    buf_imag[v172] = v170;	// L251
    float v173 = t1r_0;	// L252
    float v174 = t3i_0;	// L253
    float v175 = v173 + v174;	// L254
    int v176 = i1_0;	// L255
    int v177 = v176;	// L256
    buf_real[v177] = v175;	// L257
    float v178 = t1i_0;	// L258
    float v179 = t3r_0;	// L259
    float v180 = v178 - v179;	// L260
    int v181 = i1_0;	// L261
    int v182 = v181;	// L262
    buf_imag[v182] = v180;	// L263
    float v183 = t1r_0;	// L264
    float v184 = t3i_0;	// L265
    float v185 = v183 - v184;	// L266
    int v186 = i3_0;	// L267
    int v187 = v186;	// L268
    buf_real[v187] = v185;	// L269
    float v188 = t1i_0;	// L270
    float v189 = t3r_0;	// L271
    float v190 = v188 + v189;	// L272
    int v191 = i3_0;	// L273
    int v192 = v191;	// L274
    buf_imag[v192] = v190;	// L275
  }
  l_S_g1_2_g1: for (int g1 = 0; g1 < 64; g1++) {	// L277
    l_S_j1_2_j1: for (int j1 = 0; j1 < 4; j1++) {	// L278
      int v195 = j1;	// L279
      float v196 = v195;	// L280
      float j_f_1;	// L281
      j_f_1 = v196;	// L282
      float v198 = j_f_1;	// L286
      float v199 = v198 * -0.392699;	// L287
      float theta1_1;	// L288
      theta1_1 = v199;	// L289
      float v201 = theta1_1;	// L290
      float v202 = v201 * v201;	// L292
      float x2_1;	// L293
      x2_1 = v202;	// L294
      float v204 = x2_1;	// L295
      float v205 = theta1_1;	// L296
      float v206 = v204 * v205;	// L297
      float x3_1;	// L298
      x3_1 = v206;	// L299
      float v208 = x2_1;	// L300
      float v209 = v208 * v208;	// L302
      float x4_1;	// L303
      x4_1 = v209;	// L304
      float v211 = x4_1;	// L305
      float v212 = theta1_1;	// L306
      float v213 = v211 * v212;	// L307
      float x5_1;	// L308
      x5_1 = v213;	// L309
      float v215 = x4_1;	// L310
      float v216 = x2_1;	// L311
      float v217 = v215 * v216;	// L312
      float x6_1;	// L313
      x6_1 = v217;	// L314
      float v219 = x6_1;	// L315
      float v220 = theta1_1;	// L316
      float v221 = v219 * v220;	// L317
      float x7_1;	// L318
      x7_1 = v221;	// L319
      float v223 = x4_1;	// L320
      float v224 = v223 * v223;	// L322
      float x8_1;	// L323
      x8_1 = v224;	// L324
      float v226 = x8_1;	// L325
      float v227 = theta1_1;	// L326
      float v228 = v226 * v227;	// L327
      float x9_1;	// L328
      x9_1 = v228;	// L329
      float v230 = x8_1;	// L330
      float v231 = x2_1;	// L331
      float v232 = v230 * v231;	// L332
      float x10_1;	// L333
      x10_1 = v232;	// L334
      float v234 = x10_1;	// L335
      float v235 = theta1_1;	// L336
      float v236 = v234 * v235;	// L337
      float x11_1;	// L338
      x11_1 = v236;	// L339
      float v238 = x2_1;	// L340
      float v239 = v238 / 2.000000;	// L343
      float v240 = 1.000000 - v239;	// L346
      float v241 = x4_1;	// L347
      float v242 = v241 / 24.000000;	// L350
      float v243 = v240 + v242;	// L351
      float v244 = x6_1;	// L352
      float v245 = v244 / 720.000000;	// L355
      float v246 = v243 - v245;	// L356
      float v247 = x8_1;	// L357
      float v248 = v247 / 40320.000000;	// L360
      float v249 = v246 + v248;	// L361
      float v250 = x10_1;	// L362
      float v251 = v250 / 3628800.000000;	// L365
      float v252 = v249 - v251;	// L366
      float cos1_1;	// L367
      cos1_1 = v252;	// L368
      float v254 = theta1_1;	// L369
      float v255 = x3_1;	// L370
      float v256 = v255 / 6.000000;	// L373
      float v257 = v254 - v256;	// L374
      float v258 = x5_1;	// L375
      float v259 = v258 / 120.000000;	// L378
      float v260 = v257 + v259;	// L379
      float v261 = x7_1;	// L380
      float v262 = v261 / 5040.000000;	// L383
      float v263 = v260 - v262;	// L384
      float v264 = x9_1;	// L385
      float v265 = v264 / 362880.000000;	// L388
      float v266 = v263 + v265;	// L389
      float v267 = x11_1;	// L390
      float v268 = v267 / 39916800.000000;	// L393
      float v269 = v266 - v268;	// L394
      float sin1_1;	// L395
      sin1_1 = v269;	// L396
      float v271 = cos1_1;	// L397
      float v272 = v271 * v271;	// L399
      float v273 = sin1_1;	// L400
      float v274 = v273 * v273;	// L402
      float v275 = v272 - v274;	// L403
      float cos2_1;	// L404
      cos2_1 = v275;	// L405
      float v277 = cos1_1;	// L406
      float v278 = v277  << 1.000000;	// L409
      float v279 = sin1_1;	// L410
      float v280 = v278 * v279;	// L411
      float sin2_1;	// L412
      sin2_1 = v280;	// L413
      float v282 = cos2_1;	// L414
      float v283 = cos1_1;	// L415
      float v284 = v282 * v283;	// L416
      float v285 = sin2_1;	// L417
      float v286 = sin1_1;	// L418
      float v287 = v285 * v286;	// L419
      float v288 = v284 - v287;	// L420
      float cos3_1;	// L421
      cos3_1 = v288;	// L422
      float v290 = cos2_1;	// L423
      float v291 = sin1_1;	// L424
      float v292 = v290 * v291;	// L425
      float v293 = sin2_1;	// L426
      float v294 = cos1_1;	// L427
      float v295 = v293 * v294;	// L428
      float v296 = v292 + v295;	// L429
      float sin3_1;	// L430
      sin3_1 = v296;	// L431
      int v298 = g1;	// L432
      int v299 = v298 * 16;	// L436
      int v300 = v299;	// L437
      int v301 = j1;	// L438
      int v302 = v300 + v301;	// L439
      int v303 = v302;	// L440
      int i0_1;	// L441
      i0_1 = v303;	// L442
      int v305 = i0_1;	// L443
      int v306 = v305;	// L444
      int v307 = v306 + 4;	// L448
      int v308 = v307;	// L449
      int i1_1;	// L450
      i1_1 = v308;	// L451
      int v310 = i1_1;	// L452
      int v311 = v310;	// L453
      int v312 = v311 + 4;	// L457
      int v313 = v312;	// L458
      int i2_1;	// L459
      i2_1 = v313;	// L460
      int v315 = i2_1;	// L461
      int v316 = v315;	// L462
      int v317 = v316 + 4;	// L466
      int v318 = v317;	// L467
      int i3_1;	// L468
      i3_1 = v318;	// L469
      int v320 = i0_1;	// L470
      int v321 = v320;	// L471
      float v322 = buf_real[v321];	// L472
      float a0r_1;	// L473
      a0r_1 = v322;	// L474
      int v324 = i0_1;	// L475
      int v325 = v324;	// L476
      float v326 = buf_imag[v325];	// L477
      float a0i_1;	// L478
      a0i_1 = v326;	// L479
      int v328 = i1_1;	// L480
      int v329 = v328;	// L481
      float v330 = buf_real[v329];	// L482
      float a1r_1;	// L483
      a1r_1 = v330;	// L484
      int v332 = i1_1;	// L485
      int v333 = v332;	// L486
      float v334 = buf_imag[v333];	// L487
      float a1i_1;	// L488
      a1i_1 = v334;	// L489
      int v336 = i2_1;	// L490
      int v337 = v336;	// L491
      float v338 = buf_real[v337];	// L492
      float a2r_1;	// L493
      a2r_1 = v338;	// L494
      int v340 = i2_1;	// L495
      int v341 = v340;	// L496
      float v342 = buf_imag[v341];	// L497
      float a2i_1;	// L498
      a2i_1 = v342;	// L499
      int v344 = i3_1;	// L500
      int v345 = v344;	// L501
      float v346 = buf_real[v345];	// L502
      float a3r_1;	// L503
      a3r_1 = v346;	// L504
      int v348 = i3_1;	// L505
      int v349 = v348;	// L506
      float v350 = buf_imag[v349];	// L507
      float a3i_1;	// L508
      a3i_1 = v350;	// L509
      float v352 = a1r_1;	// L510
      float v353 = cos1_1;	// L511
      float v354 = v352 * v353;	// L512
      float v355 = a1i_1;	// L513
      float v356 = sin1_1;	// L514
      float v357 = v355 * v356;	// L515
      float v358 = v354 - v357;	// L516
      float Br_1;	// L517
      Br_1 = v358;	// L518
      float v360 = a1r_1;	// L519
      float v361 = sin1_1;	// L520
      float v362 = v360 * v361;	// L521
      float v363 = a1i_1;	// L522
      float v364 = cos1_1;	// L523
      float v365 = v363 * v364;	// L524
      float v366 = v362 + v365;	// L525
      float Bi_1;	// L526
      Bi_1 = v366;	// L527
      float v368 = a2r_1;	// L528
      float v369 = cos2_1;	// L529
      float v370 = v368 * v369;	// L530
      float v371 = a2i_1;	// L531
      float v372 = sin2_1;	// L532
      float v373 = v371 * v372;	// L533
      float v374 = v370 - v373;	// L534
      float Cr_1;	// L535
      Cr_1 = v374;	// L536
      float v376 = a2r_1;	// L537
      float v377 = sin2_1;	// L538
      float v378 = v376 * v377;	// L539
      float v379 = a2i_1;	// L540
      float v380 = cos2_1;	// L541
      float v381 = v379 * v380;	// L542
      float v382 = v378 + v381;	// L543
      float Ci_1;	// L544
      Ci_1 = v382;	// L545
      float v384 = a3r_1;	// L546
      float v385 = cos3_1;	// L547
      float v386 = v384 * v385;	// L548
      float v387 = a3i_1;	// L549
      float v388 = sin3_1;	// L550
      float v389 = v387 * v388;	// L551
      float v390 = v386 - v389;	// L552
      float Dr_1;	// L553
      Dr_1 = v390;	// L554
      float v392 = a3r_1;	// L555
      float v393 = sin3_1;	// L556
      float v394 = v392 * v393;	// L557
      float v395 = a3i_1;	// L558
      float v396 = cos3_1;	// L559
      float v397 = v395 * v396;	// L560
      float v398 = v394 + v397;	// L561
      float Di_1;	// L562
      Di_1 = v398;	// L563
      float v400 = a0r_1;	// L564
      float v401 = Cr_1;	// L565
      float v402 = v400 + v401;	// L566
      float t0r_1;	// L567
      t0r_1 = v402;	// L568
      float v404 = a0i_1;	// L569
      float v405 = Ci_1;	// L570
      float v406 = v404 + v405;	// L571
      float t0i_1;	// L572
      t0i_1 = v406;	// L573
      float v408 = a0r_1;	// L574
      float v409 = Cr_1;	// L575
      float v410 = v408 - v409;	// L576
      float t1r_1;	// L577
      t1r_1 = v410;	// L578
      float v412 = a0i_1;	// L579
      float v413 = Ci_1;	// L580
      float v414 = v412 - v413;	// L581
      float t1i_1;	// L582
      t1i_1 = v414;	// L583
      float v416 = Br_1;	// L584
      float v417 = Dr_1;	// L585
      float v418 = v416 + v417;	// L586
      float t2r_1;	// L587
      t2r_1 = v418;	// L588
      float v420 = Bi_1;	// L589
      float v421 = Di_1;	// L590
      float v422 = v420 + v421;	// L591
      float t2i_1;	// L592
      t2i_1 = v422;	// L593
      float v424 = Br_1;	// L594
      float v425 = Dr_1;	// L595
      float v426 = v424 - v425;	// L596
      float t3r_1;	// L597
      t3r_1 = v426;	// L598
      float v428 = Bi_1;	// L599
      float v429 = Di_1;	// L600
      float v430 = v428 - v429;	// L601
      float t3i_1;	// L602
      t3i_1 = v430;	// L603
      float v432 = t0r_1;	// L604
      float v433 = t2r_1;	// L605
      float v434 = v432 + v433;	// L606
      int v435 = i0_1;	// L607
      int v436 = v435;	// L608
      buf_real[v436] = v434;	// L609
      float v437 = t0i_1;	// L610
      float v438 = t2i_1;	// L611
      float v439 = v437 + v438;	// L612
      int v440 = i0_1;	// L613
      int v441 = v440;	// L614
      buf_imag[v441] = v439;	// L615
      float v442 = t0r_1;	// L616
      float v443 = t2r_1;	// L617
      float v444 = v442 - v443;	// L618
      int v445 = i2_1;	// L619
      int v446 = v445;	// L620
      buf_real[v446] = v444;	// L621
      float v447 = t0i_1;	// L622
      float v448 = t2i_1;	// L623
      float v449 = v447 - v448;	// L624
      int v450 = i2_1;	// L625
      int v451 = v450;	// L626
      buf_imag[v451] = v449;	// L627
      float v452 = t1r_1;	// L628
      float v453 = t3i_1;	// L629
      float v454 = v452 + v453;	// L630
      int v455 = i1_1;	// L631
      int v456 = v455;	// L632
      buf_real[v456] = v454;	// L633
      float v457 = t1i_1;	// L634
      float v458 = t3r_1;	// L635
      float v459 = v457 - v458;	// L636
      int v460 = i1_1;	// L637
      int v461 = v460;	// L638
      buf_imag[v461] = v459;	// L639
      float v462 = t1r_1;	// L640
      float v463 = t3i_1;	// L641
      float v464 = v462 - v463;	// L642
      int v465 = i3_1;	// L643
      int v466 = v465;	// L644
      buf_real[v466] = v464;	// L645
      float v467 = t1i_1;	// L646
      float v468 = t3r_1;	// L647
      float v469 = v467 + v468;	// L648
      int v470 = i3_1;	// L649
      int v471 = v470;	// L650
      buf_imag[v471] = v469;	// L651
    }
  }
  l_S_g2_4_g2: for (int g2 = 0; g2 < 16; g2++) {	// L654
    l_S_j2_4_j2: for (int j2 = 0; j2 < 16; j2++) {	// L655
      int v474 = j2;	// L656
      float v475 = v474;	// L657
      float j_f_2;	// L658
      j_f_2 = v475;	// L659
      float v477 = j_f_2;	// L663
      float v478 = v477 * -0.098175;	// L664
      float theta1_2;	// L665
      theta1_2 = v478;	// L666
      float v480 = theta1_2;	// L667
      float v481 = v480 * v480;	// L669
      float x2_2;	// L670
      x2_2 = v481;	// L671
      float v483 = x2_2;	// L672
      float v484 = theta1_2;	// L673
      float v485 = v483 * v484;	// L674
      float x3_2;	// L675
      x3_2 = v485;	// L676
      float v487 = x2_2;	// L677
      float v488 = v487 * v487;	// L679
      float x4_2;	// L680
      x4_2 = v488;	// L681
      float v490 = x4_2;	// L682
      float v491 = theta1_2;	// L683
      float v492 = v490 * v491;	// L684
      float x5_2;	// L685
      x5_2 = v492;	// L686
      float v494 = x4_2;	// L687
      float v495 = x2_2;	// L688
      float v496 = v494 * v495;	// L689
      float x6_2;	// L690
      x6_2 = v496;	// L691
      float v498 = x6_2;	// L692
      float v499 = theta1_2;	// L693
      float v500 = v498 * v499;	// L694
      float x7_2;	// L695
      x7_2 = v500;	// L696
      float v502 = x4_2;	// L697
      float v503 = v502 * v502;	// L699
      float x8_2;	// L700
      x8_2 = v503;	// L701
      float v505 = x8_2;	// L702
      float v506 = theta1_2;	// L703
      float v507 = v505 * v506;	// L704
      float x9_2;	// L705
      x9_2 = v507;	// L706
      float v509 = x8_2;	// L707
      float v510 = x2_2;	// L708
      float v511 = v509 * v510;	// L709
      float x10_2;	// L710
      x10_2 = v511;	// L711
      float v513 = x10_2;	// L712
      float v514 = theta1_2;	// L713
      float v515 = v513 * v514;	// L714
      float x11_2;	// L715
      x11_2 = v515;	// L716
      float v517 = x2_2;	// L717
      float v518 = v517 / 2.000000;	// L720
      float v519 = 1.000000 - v518;	// L723
      float v520 = x4_2;	// L724
      float v521 = v520 / 24.000000;	// L727
      float v522 = v519 + v521;	// L728
      float v523 = x6_2;	// L729
      float v524 = v523 / 720.000000;	// L732
      float v525 = v522 - v524;	// L733
      float v526 = x8_2;	// L734
      float v527 = v526 / 40320.000000;	// L737
      float v528 = v525 + v527;	// L738
      float v529 = x10_2;	// L739
      float v530 = v529 / 3628800.000000;	// L742
      float v531 = v528 - v530;	// L743
      float cos1_2;	// L744
      cos1_2 = v531;	// L745
      float v533 = theta1_2;	// L746
      float v534 = x3_2;	// L747
      float v535 = v534 / 6.000000;	// L750
      float v536 = v533 - v535;	// L751
      float v537 = x5_2;	// L752
      float v538 = v537 / 120.000000;	// L755
      float v539 = v536 + v538;	// L756
      float v540 = x7_2;	// L757
      float v541 = v540 / 5040.000000;	// L760
      float v542 = v539 - v541;	// L761
      float v543 = x9_2;	// L762
      float v544 = v543 / 362880.000000;	// L765
      float v545 = v542 + v544;	// L766
      float v546 = x11_2;	// L767
      float v547 = v546 / 39916800.000000;	// L770
      float v548 = v545 - v547;	// L771
      float sin1_2;	// L772
      sin1_2 = v548;	// L773
      float v550 = cos1_2;	// L774
      float v551 = v550 * v550;	// L776
      float v552 = sin1_2;	// L777
      float v553 = v552 * v552;	// L779
      float v554 = v551 - v553;	// L780
      float cos2_2;	// L781
      cos2_2 = v554;	// L782
      float v556 = cos1_2;	// L783
      float v557 = v556  << 1.000000;	// L786
      float v558 = sin1_2;	// L787
      float v559 = v557 * v558;	// L788
      float sin2_2;	// L789
      sin2_2 = v559;	// L790
      float v561 = cos2_2;	// L791
      float v562 = cos1_2;	// L792
      float v563 = v561 * v562;	// L793
      float v564 = sin2_2;	// L794
      float v565 = sin1_2;	// L795
      float v566 = v564 * v565;	// L796
      float v567 = v563 - v566;	// L797
      float cos3_2;	// L798
      cos3_2 = v567;	// L799
      float v569 = cos2_2;	// L800
      float v570 = sin1_2;	// L801
      float v571 = v569 * v570;	// L802
      float v572 = sin2_2;	// L803
      float v573 = cos1_2;	// L804
      float v574 = v572 * v573;	// L805
      float v575 = v571 + v574;	// L806
      float sin3_2;	// L807
      sin3_2 = v575;	// L808
      int v577 = g2;	// L809
      int v578 = v577 * 64;	// L813
      int v579 = v578;	// L814
      int v580 = j2;	// L815
      int v581 = v579 + v580;	// L816
      int v582 = v581;	// L817
      int i0_2;	// L818
      i0_2 = v582;	// L819
      int v584 = i0_2;	// L820
      int v585 = v584;	// L821
      int v586 = v585 + 16;	// L825
      int v587 = v586;	// L826
      int i1_2;	// L827
      i1_2 = v587;	// L828
      int v589 = i1_2;	// L829
      int v590 = v589;	// L830
      int v591 = v590 + 16;	// L834
      int v592 = v591;	// L835
      int i2_2;	// L836
      i2_2 = v592;	// L837
      int v594 = i2_2;	// L838
      int v595 = v594;	// L839
      int v596 = v595 + 16;	// L843
      int v597 = v596;	// L844
      int i3_2;	// L845
      i3_2 = v597;	// L846
      int v599 = i0_2;	// L847
      int v600 = v599;	// L848
      float v601 = buf_real[v600];	// L849
      float a0r_2;	// L850
      a0r_2 = v601;	// L851
      int v603 = i0_2;	// L852
      int v604 = v603;	// L853
      float v605 = buf_imag[v604];	// L854
      float a0i_2;	// L855
      a0i_2 = v605;	// L856
      int v607 = i1_2;	// L857
      int v608 = v607;	// L858
      float v609 = buf_real[v608];	// L859
      float a1r_2;	// L860
      a1r_2 = v609;	// L861
      int v611 = i1_2;	// L862
      int v612 = v611;	// L863
      float v613 = buf_imag[v612];	// L864
      float a1i_2;	// L865
      a1i_2 = v613;	// L866
      int v615 = i2_2;	// L867
      int v616 = v615;	// L868
      float v617 = buf_real[v616];	// L869
      float a2r_2;	// L870
      a2r_2 = v617;	// L871
      int v619 = i2_2;	// L872
      int v620 = v619;	// L873
      float v621 = buf_imag[v620];	// L874
      float a2i_2;	// L875
      a2i_2 = v621;	// L876
      int v623 = i3_2;	// L877
      int v624 = v623;	// L878
      float v625 = buf_real[v624];	// L879
      float a3r_2;	// L880
      a3r_2 = v625;	// L881
      int v627 = i3_2;	// L882
      int v628 = v627;	// L883
      float v629 = buf_imag[v628];	// L884
      float a3i_2;	// L885
      a3i_2 = v629;	// L886
      float v631 = a1r_2;	// L887
      float v632 = cos1_2;	// L888
      float v633 = v631 * v632;	// L889
      float v634 = a1i_2;	// L890
      float v635 = sin1_2;	// L891
      float v636 = v634 * v635;	// L892
      float v637 = v633 - v636;	// L893
      float Br_2;	// L894
      Br_2 = v637;	// L895
      float v639 = a1r_2;	// L896
      float v640 = sin1_2;	// L897
      float v641 = v639 * v640;	// L898
      float v642 = a1i_2;	// L899
      float v643 = cos1_2;	// L900
      float v644 = v642 * v643;	// L901
      float v645 = v641 + v644;	// L902
      float Bi_2;	// L903
      Bi_2 = v645;	// L904
      float v647 = a2r_2;	// L905
      float v648 = cos2_2;	// L906
      float v649 = v647 * v648;	// L907
      float v650 = a2i_2;	// L908
      float v651 = sin2_2;	// L909
      float v652 = v650 * v651;	// L910
      float v653 = v649 - v652;	// L911
      float Cr_2;	// L912
      Cr_2 = v653;	// L913
      float v655 = a2r_2;	// L914
      float v656 = sin2_2;	// L915
      float v657 = v655 * v656;	// L916
      float v658 = a2i_2;	// L917
      float v659 = cos2_2;	// L918
      float v660 = v658 * v659;	// L919
      float v661 = v657 + v660;	// L920
      float Ci_2;	// L921
      Ci_2 = v661;	// L922
      float v663 = a3r_2;	// L923
      float v664 = cos3_2;	// L924
      float v665 = v663 * v664;	// L925
      float v666 = a3i_2;	// L926
      float v667 = sin3_2;	// L927
      float v668 = v666 * v667;	// L928
      float v669 = v665 - v668;	// L929
      float Dr_2;	// L930
      Dr_2 = v669;	// L931
      float v671 = a3r_2;	// L932
      float v672 = sin3_2;	// L933
      float v673 = v671 * v672;	// L934
      float v674 = a3i_2;	// L935
      float v675 = cos3_2;	// L936
      float v676 = v674 * v675;	// L937
      float v677 = v673 + v676;	// L938
      float Di_2;	// L939
      Di_2 = v677;	// L940
      float v679 = a0r_2;	// L941
      float v680 = Cr_2;	// L942
      float v681 = v679 + v680;	// L943
      float t0r_2;	// L944
      t0r_2 = v681;	// L945
      float v683 = a0i_2;	// L946
      float v684 = Ci_2;	// L947
      float v685 = v683 + v684;	// L948
      float t0i_2;	// L949
      t0i_2 = v685;	// L950
      float v687 = a0r_2;	// L951
      float v688 = Cr_2;	// L952
      float v689 = v687 - v688;	// L953
      float t1r_2;	// L954
      t1r_2 = v689;	// L955
      float v691 = a0i_2;	// L956
      float v692 = Ci_2;	// L957
      float v693 = v691 - v692;	// L958
      float t1i_2;	// L959
      t1i_2 = v693;	// L960
      float v695 = Br_2;	// L961
      float v696 = Dr_2;	// L962
      float v697 = v695 + v696;	// L963
      float t2r_2;	// L964
      t2r_2 = v697;	// L965
      float v699 = Bi_2;	// L966
      float v700 = Di_2;	// L967
      float v701 = v699 + v700;	// L968
      float t2i_2;	// L969
      t2i_2 = v701;	// L970
      float v703 = Br_2;	// L971
      float v704 = Dr_2;	// L972
      float v705 = v703 - v704;	// L973
      float t3r_2;	// L974
      t3r_2 = v705;	// L975
      float v707 = Bi_2;	// L976
      float v708 = Di_2;	// L977
      float v709 = v707 - v708;	// L978
      float t3i_2;	// L979
      t3i_2 = v709;	// L980
      float v711 = t0r_2;	// L981
      float v712 = t2r_2;	// L982
      float v713 = v711 + v712;	// L983
      int v714 = i0_2;	// L984
      int v715 = v714;	// L985
      buf_real[v715] = v713;	// L986
      float v716 = t0i_2;	// L987
      float v717 = t2i_2;	// L988
      float v718 = v716 + v717;	// L989
      int v719 = i0_2;	// L990
      int v720 = v719;	// L991
      buf_imag[v720] = v718;	// L992
      float v721 = t0r_2;	// L993
      float v722 = t2r_2;	// L994
      float v723 = v721 - v722;	// L995
      int v724 = i2_2;	// L996
      int v725 = v724;	// L997
      buf_real[v725] = v723;	// L998
      float v726 = t0i_2;	// L999
      float v727 = t2i_2;	// L1000
      float v728 = v726 - v727;	// L1001
      int v729 = i2_2;	// L1002
      int v730 = v729;	// L1003
      buf_imag[v730] = v728;	// L1004
      float v731 = t1r_2;	// L1005
      float v732 = t3i_2;	// L1006
      float v733 = v731 + v732;	// L1007
      int v734 = i1_2;	// L1008
      int v735 = v734;	// L1009
      buf_real[v735] = v733;	// L1010
      float v736 = t1i_2;	// L1011
      float v737 = t3r_2;	// L1012
      float v738 = v736 - v737;	// L1013
      int v739 = i1_2;	// L1014
      int v740 = v739;	// L1015
      buf_imag[v740] = v738;	// L1016
      float v741 = t1r_2;	// L1017
      float v742 = t3i_2;	// L1018
      float v743 = v741 - v742;	// L1019
      int v744 = i3_2;	// L1020
      int v745 = v744;	// L1021
      buf_real[v745] = v743;	// L1022
      float v746 = t1i_2;	// L1023
      float v747 = t3r_2;	// L1024
      float v748 = v746 + v747;	// L1025
      int v749 = i3_2;	// L1026
      int v750 = v749;	// L1027
      buf_imag[v750] = v748;	// L1028
    }
  }
  l_S_g3_6_g3: for (int g3 = 0; g3 < 4; g3++) {	// L1031
    l_S_j3_6_j3: for (int j3 = 0; j3 < 64; j3++) {	// L1032
      int v753 = j3;	// L1033
      float v754 = v753;	// L1034
      float j_f_3;	// L1035
      j_f_3 = v754;	// L1036
      float v756 = j_f_3;	// L1040
      float v757 = v756 * -0.024544;	// L1041
      float theta1_3;	// L1042
      theta1_3 = v757;	// L1043
      float v759 = theta1_3;	// L1044
      float v760 = v759 * v759;	// L1046
      float x2_3;	// L1047
      x2_3 = v760;	// L1048
      float v762 = x2_3;	// L1049
      float v763 = theta1_3;	// L1050
      float v764 = v762 * v763;	// L1051
      float x3_3;	// L1052
      x3_3 = v764;	// L1053
      float v766 = x2_3;	// L1054
      float v767 = v766 * v766;	// L1056
      float x4_3;	// L1057
      x4_3 = v767;	// L1058
      float v769 = x4_3;	// L1059
      float v770 = theta1_3;	// L1060
      float v771 = v769 * v770;	// L1061
      float x5_3;	// L1062
      x5_3 = v771;	// L1063
      float v773 = x4_3;	// L1064
      float v774 = x2_3;	// L1065
      float v775 = v773 * v774;	// L1066
      float x6_3;	// L1067
      x6_3 = v775;	// L1068
      float v777 = x6_3;	// L1069
      float v778 = theta1_3;	// L1070
      float v779 = v777 * v778;	// L1071
      float x7_3;	// L1072
      x7_3 = v779;	// L1073
      float v781 = x4_3;	// L1074
      float v782 = v781 * v781;	// L1076
      float x8_3;	// L1077
      x8_3 = v782;	// L1078
      float v784 = x8_3;	// L1079
      float v785 = theta1_3;	// L1080
      float v786 = v784 * v785;	// L1081
      float x9_3;	// L1082
      x9_3 = v786;	// L1083
      float v788 = x8_3;	// L1084
      float v789 = x2_3;	// L1085
      float v790 = v788 * v789;	// L1086
      float x10_3;	// L1087
      x10_3 = v790;	// L1088
      float v792 = x10_3;	// L1089
      float v793 = theta1_3;	// L1090
      float v794 = v792 * v793;	// L1091
      float x11_3;	// L1092
      x11_3 = v794;	// L1093
      float v796 = x2_3;	// L1094
      float v797 = v796 / 2.000000;	// L1097
      float v798 = 1.000000 - v797;	// L1100
      float v799 = x4_3;	// L1101
      float v800 = v799 / 24.000000;	// L1104
      float v801 = v798 + v800;	// L1105
      float v802 = x6_3;	// L1106
      float v803 = v802 / 720.000000;	// L1109
      float v804 = v801 - v803;	// L1110
      float v805 = x8_3;	// L1111
      float v806 = v805 / 40320.000000;	// L1114
      float v807 = v804 + v806;	// L1115
      float v808 = x10_3;	// L1116
      float v809 = v808 / 3628800.000000;	// L1119
      float v810 = v807 - v809;	// L1120
      float cos1_3;	// L1121
      cos1_3 = v810;	// L1122
      float v812 = theta1_3;	// L1123
      float v813 = x3_3;	// L1124
      float v814 = v813 / 6.000000;	// L1127
      float v815 = v812 - v814;	// L1128
      float v816 = x5_3;	// L1129
      float v817 = v816 / 120.000000;	// L1132
      float v818 = v815 + v817;	// L1133
      float v819 = x7_3;	// L1134
      float v820 = v819 / 5040.000000;	// L1137
      float v821 = v818 - v820;	// L1138
      float v822 = x9_3;	// L1139
      float v823 = v822 / 362880.000000;	// L1142
      float v824 = v821 + v823;	// L1143
      float v825 = x11_3;	// L1144
      float v826 = v825 / 39916800.000000;	// L1147
      float v827 = v824 - v826;	// L1148
      float sin1_3;	// L1149
      sin1_3 = v827;	// L1150
      float v829 = cos1_3;	// L1151
      float v830 = v829 * v829;	// L1153
      float v831 = sin1_3;	// L1154
      float v832 = v831 * v831;	// L1156
      float v833 = v830 - v832;	// L1157
      float cos2_3;	// L1158
      cos2_3 = v833;	// L1159
      float v835 = cos1_3;	// L1160
      float v836 = v835  << 1.000000;	// L1163
      float v837 = sin1_3;	// L1164
      float v838 = v836 * v837;	// L1165
      float sin2_3;	// L1166
      sin2_3 = v838;	// L1167
      float v840 = cos2_3;	// L1168
      float v841 = cos1_3;	// L1169
      float v842 = v840 * v841;	// L1170
      float v843 = sin2_3;	// L1171
      float v844 = sin1_3;	// L1172
      float v845 = v843 * v844;	// L1173
      float v846 = v842 - v845;	// L1174
      float cos3_3;	// L1175
      cos3_3 = v846;	// L1176
      float v848 = cos2_3;	// L1177
      float v849 = sin1_3;	// L1178
      float v850 = v848 * v849;	// L1179
      float v851 = sin2_3;	// L1180
      float v852 = cos1_3;	// L1181
      float v853 = v851 * v852;	// L1182
      float v854 = v850 + v853;	// L1183
      float sin3_3;	// L1184
      sin3_3 = v854;	// L1185
      int v856 = g3;	// L1186
      int v857 = v856 * 256;	// L1190
      int v858 = v857;	// L1191
      int v859 = j3;	// L1192
      int v860 = v858 + v859;	// L1193
      int v861 = v860;	// L1194
      int i0_3;	// L1195
      i0_3 = v861;	// L1196
      int v863 = i0_3;	// L1197
      int v864 = v863;	// L1198
      int v865 = v864 + 64;	// L1202
      int v866 = v865;	// L1203
      int i1_3;	// L1204
      i1_3 = v866;	// L1205
      int v868 = i1_3;	// L1206
      int v869 = v868;	// L1207
      int v870 = v869 + 64;	// L1211
      int v871 = v870;	// L1212
      int i2_3;	// L1213
      i2_3 = v871;	// L1214
      int v873 = i2_3;	// L1215
      int v874 = v873;	// L1216
      int v875 = v874 + 64;	// L1220
      int v876 = v875;	// L1221
      int i3_3;	// L1222
      i3_3 = v876;	// L1223
      int v878 = i0_3;	// L1224
      int v879 = v878;	// L1225
      float v880 = buf_real[v879];	// L1226
      float a0r_3;	// L1227
      a0r_3 = v880;	// L1228
      int v882 = i0_3;	// L1229
      int v883 = v882;	// L1230
      float v884 = buf_imag[v883];	// L1231
      float a0i_3;	// L1232
      a0i_3 = v884;	// L1233
      int v886 = i1_3;	// L1234
      int v887 = v886;	// L1235
      float v888 = buf_real[v887];	// L1236
      float a1r_3;	// L1237
      a1r_3 = v888;	// L1238
      int v890 = i1_3;	// L1239
      int v891 = v890;	// L1240
      float v892 = buf_imag[v891];	// L1241
      float a1i_3;	// L1242
      a1i_3 = v892;	// L1243
      int v894 = i2_3;	// L1244
      int v895 = v894;	// L1245
      float v896 = buf_real[v895];	// L1246
      float a2r_3;	// L1247
      a2r_3 = v896;	// L1248
      int v898 = i2_3;	// L1249
      int v899 = v898;	// L1250
      float v900 = buf_imag[v899];	// L1251
      float a2i_3;	// L1252
      a2i_3 = v900;	// L1253
      int v902 = i3_3;	// L1254
      int v903 = v902;	// L1255
      float v904 = buf_real[v903];	// L1256
      float a3r_3;	// L1257
      a3r_3 = v904;	// L1258
      int v906 = i3_3;	// L1259
      int v907 = v906;	// L1260
      float v908 = buf_imag[v907];	// L1261
      float a3i_3;	// L1262
      a3i_3 = v908;	// L1263
      float v910 = a1r_3;	// L1264
      float v911 = cos1_3;	// L1265
      float v912 = v910 * v911;	// L1266
      float v913 = a1i_3;	// L1267
      float v914 = sin1_3;	// L1268
      float v915 = v913 * v914;	// L1269
      float v916 = v912 - v915;	// L1270
      float Br_3;	// L1271
      Br_3 = v916;	// L1272
      float v918 = a1r_3;	// L1273
      float v919 = sin1_3;	// L1274
      float v920 = v918 * v919;	// L1275
      float v921 = a1i_3;	// L1276
      float v922 = cos1_3;	// L1277
      float v923 = v921 * v922;	// L1278
      float v924 = v920 + v923;	// L1279
      float Bi_3;	// L1280
      Bi_3 = v924;	// L1281
      float v926 = a2r_3;	// L1282
      float v927 = cos2_3;	// L1283
      float v928 = v926 * v927;	// L1284
      float v929 = a2i_3;	// L1285
      float v930 = sin2_3;	// L1286
      float v931 = v929 * v930;	// L1287
      float v932 = v928 - v931;	// L1288
      float Cr_3;	// L1289
      Cr_3 = v932;	// L1290
      float v934 = a2r_3;	// L1291
      float v935 = sin2_3;	// L1292
      float v936 = v934 * v935;	// L1293
      float v937 = a2i_3;	// L1294
      float v938 = cos2_3;	// L1295
      float v939 = v937 * v938;	// L1296
      float v940 = v936 + v939;	// L1297
      float Ci_3;	// L1298
      Ci_3 = v940;	// L1299
      float v942 = a3r_3;	// L1300
      float v943 = cos3_3;	// L1301
      float v944 = v942 * v943;	// L1302
      float v945 = a3i_3;	// L1303
      float v946 = sin3_3;	// L1304
      float v947 = v945 * v946;	// L1305
      float v948 = v944 - v947;	// L1306
      float Dr_3;	// L1307
      Dr_3 = v948;	// L1308
      float v950 = a3r_3;	// L1309
      float v951 = sin3_3;	// L1310
      float v952 = v950 * v951;	// L1311
      float v953 = a3i_3;	// L1312
      float v954 = cos3_3;	// L1313
      float v955 = v953 * v954;	// L1314
      float v956 = v952 + v955;	// L1315
      float Di_3;	// L1316
      Di_3 = v956;	// L1317
      float v958 = a0r_3;	// L1318
      float v959 = Cr_3;	// L1319
      float v960 = v958 + v959;	// L1320
      float t0r_3;	// L1321
      t0r_3 = v960;	// L1322
      float v962 = a0i_3;	// L1323
      float v963 = Ci_3;	// L1324
      float v964 = v962 + v963;	// L1325
      float t0i_3;	// L1326
      t0i_3 = v964;	// L1327
      float v966 = a0r_3;	// L1328
      float v967 = Cr_3;	// L1329
      float v968 = v966 - v967;	// L1330
      float t1r_3;	// L1331
      t1r_3 = v968;	// L1332
      float v970 = a0i_3;	// L1333
      float v971 = Ci_3;	// L1334
      float v972 = v970 - v971;	// L1335
      float t1i_3;	// L1336
      t1i_3 = v972;	// L1337
      float v974 = Br_3;	// L1338
      float v975 = Dr_3;	// L1339
      float v976 = v974 + v975;	// L1340
      float t2r_3;	// L1341
      t2r_3 = v976;	// L1342
      float v978 = Bi_3;	// L1343
      float v979 = Di_3;	// L1344
      float v980 = v978 + v979;	// L1345
      float t2i_3;	// L1346
      t2i_3 = v980;	// L1347
      float v982 = Br_3;	// L1348
      float v983 = Dr_3;	// L1349
      float v984 = v982 - v983;	// L1350
      float t3r_3;	// L1351
      t3r_3 = v984;	// L1352
      float v986 = Bi_3;	// L1353
      float v987 = Di_3;	// L1354
      float v988 = v986 - v987;	// L1355
      float t3i_3;	// L1356
      t3i_3 = v988;	// L1357
      float v990 = t0r_3;	// L1358
      float v991 = t2r_3;	// L1359
      float v992 = v990 + v991;	// L1360
      int v993 = i0_3;	// L1361
      int v994 = v993;	// L1362
      buf_real[v994] = v992;	// L1363
      float v995 = t0i_3;	// L1364
      float v996 = t2i_3;	// L1365
      float v997 = v995 + v996;	// L1366
      int v998 = i0_3;	// L1367
      int v999 = v998;	// L1368
      buf_imag[v999] = v997;	// L1369
      float v1000 = t0r_3;	// L1370
      float v1001 = t2r_3;	// L1371
      float v1002 = v1000 - v1001;	// L1372
      int v1003 = i2_3;	// L1373
      int v1004 = v1003;	// L1374
      buf_real[v1004] = v1002;	// L1375
      float v1005 = t0i_3;	// L1376
      float v1006 = t2i_3;	// L1377
      float v1007 = v1005 - v1006;	// L1378
      int v1008 = i2_3;	// L1379
      int v1009 = v1008;	// L1380
      buf_imag[v1009] = v1007;	// L1381
      float v1010 = t1r_3;	// L1382
      float v1011 = t3i_3;	// L1383
      float v1012 = v1010 + v1011;	// L1384
      int v1013 = i1_3;	// L1385
      int v1014 = v1013;	// L1386
      buf_real[v1014] = v1012;	// L1387
      float v1015 = t1i_3;	// L1388
      float v1016 = t3r_3;	// L1389
      float v1017 = v1015 - v1016;	// L1390
      int v1018 = i1_3;	// L1391
      int v1019 = v1018;	// L1392
      buf_imag[v1019] = v1017;	// L1393
      float v1020 = t1r_3;	// L1394
      float v1021 = t3i_3;	// L1395
      float v1022 = v1020 - v1021;	// L1396
      int v1023 = i3_3;	// L1397
      int v1024 = v1023;	// L1398
      buf_real[v1024] = v1022;	// L1399
      float v1025 = t1i_3;	// L1400
      float v1026 = t3r_3;	// L1401
      float v1027 = v1025 + v1026;	// L1402
      int v1028 = i3_3;	// L1403
      int v1029 = v1028;	// L1404
      buf_imag[v1029] = v1027;	// L1405
    }
  }
  l_S_j4_8_j4: for (int j4 = 0; j4 < 256; j4++) {	// L1408
    int v1031 = j4;	// L1409
    float v1032 = v1031;	// L1410
    float j_f_4;	// L1411
    j_f_4 = v1032;	// L1412
    float v1034 = j_f_4;	// L1416
    float v1035 = v1034 * -0.006136;	// L1417
    float theta1_4;	// L1418
    theta1_4 = v1035;	// L1419
    float v1037 = theta1_4;	// L1420
    float v1038 = v1037 * v1037;	// L1422
    float x2_4;	// L1423
    x2_4 = v1038;	// L1424
    float v1040 = x2_4;	// L1425
    float v1041 = theta1_4;	// L1426
    float v1042 = v1040 * v1041;	// L1427
    float x3_4;	// L1428
    x3_4 = v1042;	// L1429
    float v1044 = x2_4;	// L1430
    float v1045 = v1044 * v1044;	// L1432
    float x4_4;	// L1433
    x4_4 = v1045;	// L1434
    float v1047 = x4_4;	// L1435
    float v1048 = theta1_4;	// L1436
    float v1049 = v1047 * v1048;	// L1437
    float x5_4;	// L1438
    x5_4 = v1049;	// L1439
    float v1051 = x4_4;	// L1440
    float v1052 = x2_4;	// L1441
    float v1053 = v1051 * v1052;	// L1442
    float x6_4;	// L1443
    x6_4 = v1053;	// L1444
    float v1055 = x6_4;	// L1445
    float v1056 = theta1_4;	// L1446
    float v1057 = v1055 * v1056;	// L1447
    float x7_4;	// L1448
    x7_4 = v1057;	// L1449
    float v1059 = x4_4;	// L1450
    float v1060 = v1059 * v1059;	// L1452
    float x8_4;	// L1453
    x8_4 = v1060;	// L1454
    float v1062 = x8_4;	// L1455
    float v1063 = theta1_4;	// L1456
    float v1064 = v1062 * v1063;	// L1457
    float x9_4;	// L1458
    x9_4 = v1064;	// L1459
    float v1066 = x8_4;	// L1460
    float v1067 = x2_4;	// L1461
    float v1068 = v1066 * v1067;	// L1462
    float x10_4;	// L1463
    x10_4 = v1068;	// L1464
    float v1070 = x10_4;	// L1465
    float v1071 = theta1_4;	// L1466
    float v1072 = v1070 * v1071;	// L1467
    float x11_4;	// L1468
    x11_4 = v1072;	// L1469
    float v1074 = x2_4;	// L1470
    float v1075 = v1074 / 2.000000;	// L1473
    float v1076 = 1.000000 - v1075;	// L1476
    float v1077 = x4_4;	// L1477
    float v1078 = v1077 / 24.000000;	// L1480
    float v1079 = v1076 + v1078;	// L1481
    float v1080 = x6_4;	// L1482
    float v1081 = v1080 / 720.000000;	// L1485
    float v1082 = v1079 - v1081;	// L1486
    float v1083 = x8_4;	// L1487
    float v1084 = v1083 / 40320.000000;	// L1490
    float v1085 = v1082 + v1084;	// L1491
    float v1086 = x10_4;	// L1492
    float v1087 = v1086 / 3628800.000000;	// L1495
    float v1088 = v1085 - v1087;	// L1496
    float cos1_4;	// L1497
    cos1_4 = v1088;	// L1498
    float v1090 = theta1_4;	// L1499
    float v1091 = x3_4;	// L1500
    float v1092 = v1091 / 6.000000;	// L1503
    float v1093 = v1090 - v1092;	// L1504
    float v1094 = x5_4;	// L1505
    float v1095 = v1094 / 120.000000;	// L1508
    float v1096 = v1093 + v1095;	// L1509
    float v1097 = x7_4;	// L1510
    float v1098 = v1097 / 5040.000000;	// L1513
    float v1099 = v1096 - v1098;	// L1514
    float v1100 = x9_4;	// L1515
    float v1101 = v1100 / 362880.000000;	// L1518
    float v1102 = v1099 + v1101;	// L1519
    float v1103 = x11_4;	// L1520
    float v1104 = v1103 / 39916800.000000;	// L1523
    float v1105 = v1102 - v1104;	// L1524
    float sin1_4;	// L1525
    sin1_4 = v1105;	// L1526
    float v1107 = cos1_4;	// L1527
    float v1108 = v1107 * v1107;	// L1529
    float v1109 = sin1_4;	// L1530
    float v1110 = v1109 * v1109;	// L1532
    float v1111 = v1108 - v1110;	// L1533
    float cos2_4;	// L1534
    cos2_4 = v1111;	// L1535
    float v1113 = cos1_4;	// L1536
    float v1114 = v1113  << 1.000000;	// L1539
    float v1115 = sin1_4;	// L1540
    float v1116 = v1114 * v1115;	// L1541
    float sin2_4;	// L1542
    sin2_4 = v1116;	// L1543
    float v1118 = cos2_4;	// L1544
    float v1119 = cos1_4;	// L1545
    float v1120 = v1118 * v1119;	// L1546
    float v1121 = sin2_4;	// L1547
    float v1122 = sin1_4;	// L1548
    float v1123 = v1121 * v1122;	// L1549
    float v1124 = v1120 - v1123;	// L1550
    float cos3_4;	// L1551
    cos3_4 = v1124;	// L1552
    float v1126 = cos2_4;	// L1553
    float v1127 = sin1_4;	// L1554
    float v1128 = v1126 * v1127;	// L1555
    float v1129 = sin2_4;	// L1556
    float v1130 = cos1_4;	// L1557
    float v1131 = v1129 * v1130;	// L1558
    float v1132 = v1128 + v1131;	// L1559
    float sin3_4;	// L1560
    sin3_4 = v1132;	// L1561
    int i0_4;	// L1563
    i0_4 = v1031;	// L1564
    int v1135 = i0_4;	// L1565
    int v1136 = v1135;	// L1566
    int v1137 = v1136 + 256;	// L1570
    int v1138 = v1137;	// L1571
    int i1_4;	// L1572
    i1_4 = v1138;	// L1573
    int v1140 = i1_4;	// L1574
    int v1141 = v1140;	// L1575
    int v1142 = v1141 + 256;	// L1579
    int v1143 = v1142;	// L1580
    int i2_4;	// L1581
    i2_4 = v1143;	// L1582
    int v1145 = i2_4;	// L1583
    int v1146 = v1145;	// L1584
    int v1147 = v1146 + 256;	// L1588
    int v1148 = v1147;	// L1589
    int i3_4;	// L1590
    i3_4 = v1148;	// L1591
    int v1150 = i0_4;	// L1592
    int v1151 = v1150;	// L1593
    float v1152 = buf_real[v1151];	// L1594
    float a0r_4;	// L1595
    a0r_4 = v1152;	// L1596
    int v1154 = i0_4;	// L1597
    int v1155 = v1154;	// L1598
    float v1156 = buf_imag[v1155];	// L1599
    float a0i_4;	// L1600
    a0i_4 = v1156;	// L1601
    int v1158 = i1_4;	// L1602
    int v1159 = v1158;	// L1603
    float v1160 = buf_real[v1159];	// L1604
    float a1r_4;	// L1605
    a1r_4 = v1160;	// L1606
    int v1162 = i1_4;	// L1607
    int v1163 = v1162;	// L1608
    float v1164 = buf_imag[v1163];	// L1609
    float a1i_4;	// L1610
    a1i_4 = v1164;	// L1611
    int v1166 = i2_4;	// L1612
    int v1167 = v1166;	// L1613
    float v1168 = buf_real[v1167];	// L1614
    float a2r_4;	// L1615
    a2r_4 = v1168;	// L1616
    int v1170 = i2_4;	// L1617
    int v1171 = v1170;	// L1618
    float v1172 = buf_imag[v1171];	// L1619
    float a2i_4;	// L1620
    a2i_4 = v1172;	// L1621
    int v1174 = i3_4;	// L1622
    int v1175 = v1174;	// L1623
    float v1176 = buf_real[v1175];	// L1624
    float a3r_4;	// L1625
    a3r_4 = v1176;	// L1626
    int v1178 = i3_4;	// L1627
    int v1179 = v1178;	// L1628
    float v1180 = buf_imag[v1179];	// L1629
    float a3i_4;	// L1630
    a3i_4 = v1180;	// L1631
    float v1182 = a1r_4;	// L1632
    float v1183 = cos1_4;	// L1633
    float v1184 = v1182 * v1183;	// L1634
    float v1185 = a1i_4;	// L1635
    float v1186 = sin1_4;	// L1636
    float v1187 = v1185 * v1186;	// L1637
    float v1188 = v1184 - v1187;	// L1638
    float Br_4;	// L1639
    Br_4 = v1188;	// L1640
    float v1190 = a1r_4;	// L1641
    float v1191 = sin1_4;	// L1642
    float v1192 = v1190 * v1191;	// L1643
    float v1193 = a1i_4;	// L1644
    float v1194 = cos1_4;	// L1645
    float v1195 = v1193 * v1194;	// L1646
    float v1196 = v1192 + v1195;	// L1647
    float Bi_4;	// L1648
    Bi_4 = v1196;	// L1649
    float v1198 = a2r_4;	// L1650
    float v1199 = cos2_4;	// L1651
    float v1200 = v1198 * v1199;	// L1652
    float v1201 = a2i_4;	// L1653
    float v1202 = sin2_4;	// L1654
    float v1203 = v1201 * v1202;	// L1655
    float v1204 = v1200 - v1203;	// L1656
    float Cr_4;	// L1657
    Cr_4 = v1204;	// L1658
    float v1206 = a2r_4;	// L1659
    float v1207 = sin2_4;	// L1660
    float v1208 = v1206 * v1207;	// L1661
    float v1209 = a2i_4;	// L1662
    float v1210 = cos2_4;	// L1663
    float v1211 = v1209 * v1210;	// L1664
    float v1212 = v1208 + v1211;	// L1665
    float Ci_4;	// L1666
    Ci_4 = v1212;	// L1667
    float v1214 = a3r_4;	// L1668
    float v1215 = cos3_4;	// L1669
    float v1216 = v1214 * v1215;	// L1670
    float v1217 = a3i_4;	// L1671
    float v1218 = sin3_4;	// L1672
    float v1219 = v1217 * v1218;	// L1673
    float v1220 = v1216 - v1219;	// L1674
    float Dr_4;	// L1675
    Dr_4 = v1220;	// L1676
    float v1222 = a3r_4;	// L1677
    float v1223 = sin3_4;	// L1678
    float v1224 = v1222 * v1223;	// L1679
    float v1225 = a3i_4;	// L1680
    float v1226 = cos3_4;	// L1681
    float v1227 = v1225 * v1226;	// L1682
    float v1228 = v1224 + v1227;	// L1683
    float Di_4;	// L1684
    Di_4 = v1228;	// L1685
    float v1230 = a0r_4;	// L1686
    float v1231 = Cr_4;	// L1687
    float v1232 = v1230 + v1231;	// L1688
    float t0r_4;	// L1689
    t0r_4 = v1232;	// L1690
    float v1234 = a0i_4;	// L1691
    float v1235 = Ci_4;	// L1692
    float v1236 = v1234 + v1235;	// L1693
    float t0i_4;	// L1694
    t0i_4 = v1236;	// L1695
    float v1238 = a0r_4;	// L1696
    float v1239 = Cr_4;	// L1697
    float v1240 = v1238 - v1239;	// L1698
    float t1r_4;	// L1699
    t1r_4 = v1240;	// L1700
    float v1242 = a0i_4;	// L1701
    float v1243 = Ci_4;	// L1702
    float v1244 = v1242 - v1243;	// L1703
    float t1i_4;	// L1704
    t1i_4 = v1244;	// L1705
    float v1246 = Br_4;	// L1706
    float v1247 = Dr_4;	// L1707
    float v1248 = v1246 + v1247;	// L1708
    float t2r_4;	// L1709
    t2r_4 = v1248;	// L1710
    float v1250 = Bi_4;	// L1711
    float v1251 = Di_4;	// L1712
    float v1252 = v1250 + v1251;	// L1713
    float t2i_4;	// L1714
    t2i_4 = v1252;	// L1715
    float v1254 = Br_4;	// L1716
    float v1255 = Dr_4;	// L1717
    float v1256 = v1254 - v1255;	// L1718
    float t3r_4;	// L1719
    t3r_4 = v1256;	// L1720
    float v1258 = Bi_4;	// L1721
    float v1259 = Di_4;	// L1722
    float v1260 = v1258 - v1259;	// L1723
    float t3i_4;	// L1724
    t3i_4 = v1260;	// L1725
    float v1262 = t0r_4;	// L1726
    float v1263 = t2r_4;	// L1727
    float v1264 = v1262 + v1263;	// L1728
    int v1265 = i0_4;	// L1729
    int v1266 = v1265;	// L1730
    buf_real[v1266] = v1264;	// L1731
    float v1267 = t0i_4;	// L1732
    float v1268 = t2i_4;	// L1733
    float v1269 = v1267 + v1268;	// L1734
    int v1270 = i0_4;	// L1735
    int v1271 = v1270;	// L1736
    buf_imag[v1271] = v1269;	// L1737
    float v1272 = t0r_4;	// L1738
    float v1273 = t2r_4;	// L1739
    float v1274 = v1272 - v1273;	// L1740
    int v1275 = i2_4;	// L1741
    int v1276 = v1275;	// L1742
    buf_real[v1276] = v1274;	// L1743
    float v1277 = t0i_4;	// L1744
    float v1278 = t2i_4;	// L1745
    float v1279 = v1277 - v1278;	// L1746
    int v1280 = i2_4;	// L1747
    int v1281 = v1280;	// L1748
    buf_imag[v1281] = v1279;	// L1749
    float v1282 = t1r_4;	// L1750
    float v1283 = t3i_4;	// L1751
    float v1284 = v1282 + v1283;	// L1752
    int v1285 = i1_4;	// L1753
    int v1286 = v1285;	// L1754
    buf_real[v1286] = v1284;	// L1755
    float v1287 = t1i_4;	// L1756
    float v1288 = t3r_4;	// L1757
    float v1289 = v1287 - v1288;	// L1758
    int v1290 = i1_4;	// L1759
    int v1291 = v1290;	// L1760
    buf_imag[v1291] = v1289;	// L1761
    float v1292 = t1r_4;	// L1762
    float v1293 = t3i_4;	// L1763
    float v1294 = v1292 - v1293;	// L1764
    int v1295 = i3_4;	// L1765
    int v1296 = v1295;	// L1766
    buf_real[v1296] = v1294;	// L1767
    float v1297 = t1i_4;	// L1768
    float v1298 = t3r_4;	// L1769
    float v1299 = v1297 + v1298;	// L1770
    int v1300 = i3_4;	// L1771
    int v1301 = v1300;	// L1772
    buf_imag[v1301] = v1299;	// L1773
  }
  l_S_ic_9_ic: for (int ic = 0; ic < 1024; ic++) {	// L1775
    float v1303 = buf_real[ic];	// L1776
    v2[ic] = v1303;	// L1777
    float v1304 = buf_imag[ic];	// L1778
    v3[ic] = v1304;	// L1779
  }
}
#pragma pocc-region-end
}

