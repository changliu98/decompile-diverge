void __cdecl bn_sqr_comba8(unsigned __int64 *r, const unsigned __int64 *a)
{
  unsigned __int128 v2; // kr00_16
  unsigned __int128 v3; // kr10_16
  unsigned __int64 v4; // rcx
  __int64 v5; // rax
  unsigned __int64 v6; // rcx
  unsigned __int128 v7; // kr30_16
  bool v8; // cf
  unsigned __int128 v9; // kr40_16
  __int64 v10; // rax
  unsigned __int128 v11; // kr50_16
  unsigned __int64 v12; // rcx
  __int64 v13; // rax
  unsigned __int64 v14; // rcx
  unsigned __int128 v15; // kr70_16
  unsigned __int128 v16; // kr80_16
  unsigned __int64 v17; // rcx
  __int64 v18; // rax
  unsigned __int128 v19; // kr20_16
  unsigned __int128 v20; // krB0_16
  unsigned __int64 v21; // rcx
  __int64 v22; // rax
  unsigned __int64 v23; // rcx
  unsigned __int128 v24; // krD0_16
  unsigned __int128 v25; // krE0_16
  __int64 v26; // rax
  unsigned __int128 v27; // krF0_16
  unsigned __int64 v28; // rcx
  __int64 v29; // rax
  unsigned __int128 v30; // kr60_16
  unsigned __int128 v31; // kr120_16
  unsigned __int64 v32; // rcx
  __int64 v33; // rax
  unsigned __int64 v34; // rcx
  unsigned __int128 v35; // kr140_16
  unsigned __int128 v36; // kr150_16
  unsigned __int64 v37; // rcx
  __int64 v38; // rax
  unsigned __int128 v39; // kr90_16
  unsigned __int128 v40; // kr180_16
  unsigned __int64 v41; // rcx
  __int64 v42; // rax
  unsigned __int128 v43; // krA0_16
  unsigned __int128 v44; // kr1B0_16
  unsigned __int64 v45; // rcx
  __int64 v46; // rax
  unsigned __int64 v47; // rcx
  unsigned __int128 v48; // kr1D0_16
  unsigned __int128 v49; // kr1E0_16
  __int64 v50; // rax
  unsigned __int128 v51; // kr1F0_16
  unsigned __int64 v52; // rcx
  __int64 v53; // rax
  unsigned __int128 v54; // krC0_16
  unsigned __int128 v55; // kr220_16
  unsigned __int64 v56; // rcx
  __int64 v57; // rax
  unsigned __int128 v58; // kr100_16
  unsigned __int128 v59; // kr250_16
  unsigned __int64 v60; // rcx
  __int64 v61; // rax
  unsigned __int64 v62; // rcx
  unsigned __int128 v63; // kr270_16
  unsigned __int128 v64; // kr280_16
  unsigned __int64 v65; // rcx
  __int64 v66; // rax
  unsigned __int128 v67; // kr110_16
  unsigned __int128 v68; // kr2B0_16
  unsigned __int64 v69; // rcx
  __int64 v70; // rax
  unsigned __int128 v71; // kr130_16
  unsigned __int128 v72; // kr2E0_16
  unsigned __int64 v73; // rcx
  __int64 v74; // rax
  unsigned __int128 v75; // kr160_16
  unsigned __int128 v76; // kr310_16
  unsigned __int64 v77; // rcx
  __int64 v78; // rax
  unsigned __int64 v79; // rcx
  unsigned __int128 v80; // kr330_16
  unsigned __int128 v81; // kr340_16
  __int64 v82; // rax
  unsigned __int128 v83; // kr350_16
  unsigned __int64 v84; // rcx
  __int64 v85; // rax
  unsigned __int128 v86; // kr170_16
  unsigned __int128 v87; // kr380_16
  unsigned __int64 v88; // rcx
  __int64 v89; // rax
  unsigned __int128 v90; // kr190_16
  unsigned __int128 v91; // kr3B0_16
  unsigned __int64 v92; // rcx
  __int64 v93; // rax
  unsigned __int64 v94; // rcx
  unsigned __int128 v95; // kr3D0_16
  unsigned __int128 v96; // kr3E0_16
  unsigned __int64 v97; // rcx
  __int64 v98; // rax
  unsigned __int128 v99; // kr1A0_16
  unsigned __int128 v100; // kr410_16
  unsigned __int64 v101; // rcx
  __int64 v102; // rax
  unsigned __int128 v103; // kr1C0_16
  unsigned __int128 v104; // kr440_16
  unsigned __int64 v105; // rcx
  __int64 v106; // rax
  unsigned __int64 v107; // rcx
  unsigned __int128 v108; // kr460_16
  unsigned __int128 v109; // kr470_16
  __int64 v110; // rax
  unsigned __int128 v111; // kr480_16
  unsigned __int64 v112; // rcx
  __int64 v113; // rax
  unsigned __int128 v114; // kr200_16
  unsigned __int128 v115; // kr4B0_16
  unsigned __int64 v116; // rcx
  __int64 v117; // rax
  unsigned __int64 v118; // rcx
  unsigned __int128 v119; // kr4D0_16
  unsigned __int128 v120; // kr4E0_16
  unsigned __int64 v121; // rcx
  __int64 v122; // rax
  unsigned __int128 v123; // kr210_16
  unsigned __int128 v124; // kr510_16
  unsigned __int64 v125; // rcx
  __int64 v126; // rax
  unsigned __int64 v127; // rcx
  unsigned __int128 v128; // kr530_16
  unsigned __int128 v129; // kr540_16
  __int64 v130; // rax
  unsigned __int128 v131; // kr550_16
  unsigned __int64 v132; // rcx
  __int64 v133; // rax
  unsigned __int64 v134; // rcx
  unsigned __int128 v135; // kr570_16
  unsigned __int128 v136; // kr580_16
  unsigned __int64 c3; // [rsp+240h] [rbp-28h]
  unsigned __int64 c3a; // [rsp+240h] [rbp-28h]
  unsigned __int64 c3b; // [rsp+240h] [rbp-28h]
  unsigned __int64 c3c; // [rsp+240h] [rbp-28h]
  unsigned __int64 c3d; // [rsp+240h] [rbp-28h]
  unsigned __int64 c3e; // [rsp+240h] [rbp-28h]
  unsigned __int64 c3f; // [rsp+240h] [rbp-28h]
  unsigned __int64 c3g; // [rsp+240h] [rbp-28h]
  unsigned __int64 c3h; // [rsp+240h] [rbp-28h]
  unsigned __int64 c3i; // [rsp+240h] [rbp-28h]
  unsigned __int64 c3j; // [rsp+240h] [rbp-28h]
  unsigned __int64 c3k; // [rsp+240h] [rbp-28h]
  unsigned __int64 c3l; // [rsp+240h] [rbp-28h]
  unsigned __int64 c3m; // [rsp+240h] [rbp-28h]
  unsigned __int64 c3n; // [rsp+240h] [rbp-28h]
  unsigned __int64 c3o; // [rsp+240h] [rbp-28h]
  unsigned __int64 c3p; // [rsp+240h] [rbp-28h]
  unsigned __int64 c3q; // [rsp+240h] [rbp-28h]
  unsigned __int64 c3r; // [rsp+240h] [rbp-28h]
  unsigned __int64 c3s; // [rsp+240h] [rbp-28h]
  unsigned __int64 c3t; // [rsp+240h] [rbp-28h]
  unsigned __int64 c3u; // [rsp+240h] [rbp-28h]
  unsigned __int64 c3v; // [rsp+240h] [rbp-28h]
  unsigned __int64 c3w; // [rsp+240h] [rbp-28h]
  unsigned __int64 c3x; // [rsp+240h] [rbp-28h]
  unsigned __int64 c3y; // [rsp+240h] [rbp-28h]
  unsigned __int64 c3z; // [rsp+240h] [rbp-28h]
  unsigned __int64 c3ba; // [rsp+240h] [rbp-28h]
  unsigned __int64 c3bb; // [rsp+240h] [rbp-28h]
  unsigned __int64 c3bc; // [rsp+240h] [rbp-28h]
  unsigned __int64 c2; // [rsp+248h] [rbp-20h]
  unsigned __int64 c2a; // [rsp+248h] [rbp-20h]
  unsigned __int64 c2b; // [rsp+248h] [rbp-20h]
  unsigned __int64 c2c; // [rsp+248h] [rbp-20h]
  unsigned __int64 c2d; // [rsp+248h] [rbp-20h]
  unsigned __int64 c2e; // [rsp+248h] [rbp-20h]
  unsigned __int64 c2f; // [rsp+248h] [rbp-20h]
  unsigned __int64 c2g; // [rsp+248h] [rbp-20h]
  unsigned __int64 c2h; // [rsp+248h] [rbp-20h]
  unsigned __int64 c2i; // [rsp+248h] [rbp-20h]
  unsigned __int64 c2j; // [rsp+248h] [rbp-20h]
  unsigned __int64 c2k; // [rsp+248h] [rbp-20h]
  unsigned __int64 c2l; // [rsp+248h] [rbp-20h]
  unsigned __int64 c2m; // [rsp+248h] [rbp-20h]
  unsigned __int64 c2n; // [rsp+248h] [rbp-20h]
  unsigned __int64 c2o; // [rsp+248h] [rbp-20h]
  unsigned __int64 c2p; // [rsp+248h] [rbp-20h]
  unsigned __int64 c2q; // [rsp+248h] [rbp-20h]
  unsigned __int64 c2r; // [rsp+248h] [rbp-20h]
  unsigned __int64 c2s; // [rsp+248h] [rbp-20h]
  unsigned __int64 c2t; // [rsp+248h] [rbp-20h]
  unsigned __int64 c2u; // [rsp+248h] [rbp-20h]
  unsigned __int64 c2v; // [rsp+248h] [rbp-20h]
  unsigned __int64 c2w; // [rsp+248h] [rbp-20h]
  unsigned __int64 c2x; // [rsp+248h] [rbp-20h]
  unsigned __int64 c2y; // [rsp+248h] [rbp-20h]
  unsigned __int64 c2z; // [rsp+248h] [rbp-20h]
  unsigned __int64 c2ba; // [rsp+248h] [rbp-20h]
  unsigned __int64 c2bb; // [rsp+248h] [rbp-20h]
  unsigned __int64 c1; // [rsp+250h] [rbp-18h]
  unsigned __int64 c1a; // [rsp+250h] [rbp-18h]
  unsigned __int64 c1b; // [rsp+250h] [rbp-18h]
  unsigned __int64 c1c; // [rsp+250h] [rbp-18h]
  unsigned __int64 c1d; // [rsp+250h] [rbp-18h]
  unsigned __int64 c1e; // [rsp+250h] [rbp-18h]
  unsigned __int64 c1f; // [rsp+250h] [rbp-18h]
  unsigned __int64 c1g; // [rsp+250h] [rbp-18h]
  unsigned __int64 c1h; // [rsp+250h] [rbp-18h]
  unsigned __int64 c1i; // [rsp+250h] [rbp-18h]
  unsigned __int64 c1j; // [rsp+250h] [rbp-18h]
  unsigned __int64 c1k; // [rsp+250h] [rbp-18h]
  unsigned __int64 c1l; // [rsp+250h] [rbp-18h]
  unsigned __int64 c1m; // [rsp+250h] [rbp-18h]
  unsigned __int64 c1n; // [rsp+250h] [rbp-18h]
  unsigned __int64 c1o; // [rsp+250h] [rbp-18h]
  unsigned __int64 c1p; // [rsp+250h] [rbp-18h]
  unsigned __int64 c1q; // [rsp+250h] [rbp-18h]
  unsigned __int64 c1r; // [rsp+250h] [rbp-18h]
  unsigned __int64 c1s; // [rsp+250h] [rbp-18h]
  unsigned __int64 c1t; // [rsp+250h] [rbp-18h]
  unsigned __int64 c1u; // [rsp+250h] [rbp-18h]
  unsigned __int64 c1v; // [rsp+250h] [rbp-18h]
  unsigned __int64 c1w; // [rsp+250h] [rbp-18h]
  unsigned __int64 c1x; // [rsp+250h] [rbp-18h]
  unsigned __int64 c1y; // [rsp+250h] [rbp-18h]
  unsigned __int64 c1z; // [rsp+250h] [rbp-18h]
  unsigned __int64 c1ba; // [rsp+250h] [rbp-18h]
  unsigned __int64 c1bb; // [rsp+250h] [rbp-18h]

  v2 = *a * (unsigned __int128)*a;
  c2 = (v2 + 0) >> 64;
  c3 = __CFADD__(*((_QWORD *)&v2 + 1), c2);
  *r = v2;
  v3 = *a * (unsigned __int128)a[1];
  v4 = (v3 + __PAIR128__(c3, c2)) >> 64;
  v5 = __CFADD__(__CFADD__((_QWORD)v3, c2), c3) | (unsigned __int8)__CFADD__(*((_QWORD *)&v3 + 1), v4);
  c2a = v3 + c2;
  v8 = __CFADD__(__CFADD__((_QWORD)v3, c2a), v4);
  v7 = v3 + __PAIR128__(v4, c2a);
  v6 = (v3 + __PAIR128__(v4, c2a)) >> 64;
  c1 = (v8 | (unsigned __int8)__CFADD__(*((_QWORD *)&v3 + 1), v6)) + v5;
  r[1] = v7;
  v9 = a[1] * (unsigned __int128)a[1];
  v10 = __CFADD__(__CFADD__((_QWORD)v9, v6), c1) | (unsigned __int8)__CFADD__(
                                                                      *((_QWORD *)&v9 + 1),
                                                                      (v9 + __PAIR128__(c1, v6)) >> 64);
  c3a = v9 + v6;
  c1a = (v9 + __PAIR128__(c1, v6)) >> 64;
  v11 = *a * (unsigned __int128)a[2];
  v12 = (v11 + __PAIR128__(c1a, (unsigned __int64)v9 + v6)) >> 64;
  v13 = (__CFADD__(__CFADD__((_QWORD)v11, c3a), c1a) | (unsigned __int8)__CFADD__(
                                                                          *((_QWORD *)&v11 + 1),
                                                                          (v11 + __PAIR128__(c1a, c3a)) >> 64))
      + v10;
  c3b = v11 + c3a;
  v8 = __CFADD__(__CFADD__((_QWORD)v11, c3b), v12);
  v15 = v11 + __PAIR128__(v12, c3b);
  v14 = (v11 + __PAIR128__(v12, c3b)) >> 64;
  c1b = v14;
  c2b = (v8 | (unsigned __int8)__CFADD__(*((_QWORD *)&v11 + 1), v14)) + v13;
  r[2] = v15;
  v16 = *a * (unsigned __int128)a[3];
  v17 = (v16 + __PAIR128__(c2b, v14)) >> 64;
  v18 = __CFADD__(__CFADD__((_QWORD)v16, c1b), c2b) | (unsigned __int8)__CFADD__(
                                                                         *((_QWORD *)&v16 + 1),
                                                                         (v16 + __PAIR128__(c2b, c1b)) >> 64);
  c1c = v16 + c1b;
  v8 = __CFADD__(__CFADD__((_QWORD)v16, c1c), v17);
  v19 = v16 + __PAIR128__(v17, c1c);
  c2c = v19 >> 64;
  c1d = v19;
  v20 = a[1] * (unsigned __int128)a[2];
  v21 = (v20 + __PAIR128__(c2c, c1d)) >> 64;
  v22 = (__CFADD__(__CFADD__((_QWORD)v20, c1d), c2c) | (unsigned __int8)__CFADD__(*((_QWORD *)&v20 + 1), v21))
      + (v8 | (unsigned __int8)__CFADD__(*((_QWORD *)&v16 + 1), c2c))
      + v18;
  c1e = v20 + c1d;
  v8 = __CFADD__(__CFADD__((_QWORD)v20, c1e), v21);
  v24 = v20 + __PAIR128__(v21, c1e);
  v23 = (v20 + __PAIR128__(v21, c1e)) >> 64;
  c3c = (v8 | (unsigned __int8)__CFADD__(*((_QWORD *)&v20 + 1), v23)) + v22;
  r[3] = v24;
  v25 = a[2] * (unsigned __int128)a[2];
  v26 = __CFADD__(__CFADD__((_QWORD)v25, v23), c3c) | (unsigned __int8)__CFADD__(
                                                                         *((_QWORD *)&v25 + 1),
                                                                         (v25 + __PAIR128__(c3c, v23)) >> 64);
  c2d = v25 + v23;
  c3d = (v25 + __PAIR128__(c3c, v23)) >> 64;
  v27 = a[1] * (unsigned __int128)a[3];
  v28 = (v27 + __PAIR128__(c3d, (unsigned __int64)v25 + v23)) >> 64;
  v29 = (__CFADD__(__CFADD__((_QWORD)v27, c2d), c3d) | (unsigned __int8)__CFADD__(
                                                                          *((_QWORD *)&v27 + 1),
                                                                          (v27 + __PAIR128__(c3d, c2d)) >> 64))
      + v26;
  c2e = v27 + c2d;
  v8 = __CFADD__(__CFADD__((_QWORD)v27, c2e), v28);
  v30 = v27 + __PAIR128__(v28, c2e);
  c3e = v30 >> 64;
  c2f = v30;
  v31 = *a * (unsigned __int128)a[4];
  v32 = (v31 + __PAIR128__(c3e, c2f)) >> 64;
  v33 = (__CFADD__(__CFADD__((_QWORD)v31, c2f), c3e) | (unsigned __int8)__CFADD__(*((_QWORD *)&v31 + 1), v32))
      + (v8 | (unsigned __int8)__CFADD__(*((_QWORD *)&v27 + 1), c3e))
      + v29;
  c2g = v31 + c2f;
  v8 = __CFADD__(__CFADD__((_QWORD)v31, c2g), v32);
  v35 = v31 + __PAIR128__(v32, c2g);
  v34 = (v31 + __PAIR128__(v32, c2g)) >> 64;
  c3f = v34;
  c1f = (v8 | (unsigned __int8)__CFADD__(*((_QWORD *)&v31 + 1), v34)) + v33;
  r[4] = v35;
  v36 = *a * (unsigned __int128)a[5];
  v37 = (v36 + __PAIR128__(c1f, v34)) >> 64;
  v38 = __CFADD__(__CFADD__((_QWORD)v36, c3f), c1f) | (unsigned __int8)__CFADD__(
                                                                         *((_QWORD *)&v36 + 1),
                                                                         (v36 + __PAIR128__(c1f, c3f)) >> 64);
  c3g = v36 + c3f;
  v8 = __CFADD__(__CFADD__((_QWORD)v36, c3g), v37);
  v39 = v36 + __PAIR128__(v37, c3g);
  c1g = v39 >> 64;
  c3h = v39;
  v40 = a[1] * (unsigned __int128)a[4];
  v41 = (v40 + __PAIR128__(c1g, c3h)) >> 64;
  v42 = (__CFADD__(__CFADD__((_QWORD)v40, c3h), c1g) | (unsigned __int8)__CFADD__(*((_QWORD *)&v40 + 1), v41))
      + (v8 | (unsigned __int8)__CFADD__(*((_QWORD *)&v36 + 1), c1g))
      + v38;
  c3i = v40 + c3h;
  v8 = __CFADD__(__CFADD__((_QWORD)v40, c3i), v41);
  v43 = v40 + __PAIR128__(v41, c3i);
  c1h = v43 >> 64;
  c3j = v43;
  v44 = a[2] * (unsigned __int128)a[3];
  v45 = (v44 + __PAIR128__(c1h, c3j)) >> 64;
  v46 = (__CFADD__(__CFADD__((_QWORD)v44, c3j), c1h) | (unsigned __int8)__CFADD__(*((_QWORD *)&v44 + 1), v45))
      + (v8 | (unsigned __int8)__CFADD__(*((_QWORD *)&v40 + 1), c1h))
      + v42;
  c3k = v44 + c3j;
  v8 = __CFADD__(__CFADD__((_QWORD)v44, c3k), v45);
  v48 = v44 + __PAIR128__(v45, c3k);
  v47 = (v44 + __PAIR128__(v45, c3k)) >> 64;
  c2h = (v8 | (unsigned __int8)__CFADD__(*((_QWORD *)&v44 + 1), v47)) + v46;
  r[5] = v48;
  v49 = a[3] * (unsigned __int128)a[3];
  v50 = __CFADD__(__CFADD__((_QWORD)v49, v47), c2h) | (unsigned __int8)__CFADD__(
                                                                         *((_QWORD *)&v49 + 1),
                                                                         (v49 + __PAIR128__(c2h, v47)) >> 64);
  c1i = v49 + v47;
  c2i = (v49 + __PAIR128__(c2h, v47)) >> 64;
  v51 = a[2] * (unsigned __int128)a[4];
  v52 = (v51 + __PAIR128__(c2i, (unsigned __int64)v49 + v47)) >> 64;
  v53 = (__CFADD__(__CFADD__((_QWORD)v51, c1i), c2i) | (unsigned __int8)__CFADD__(
                                                                          *((_QWORD *)&v51 + 1),
                                                                          (v51 + __PAIR128__(c2i, c1i)) >> 64))
      + v50;
  c1j = v51 + c1i;
  v8 = __CFADD__(__CFADD__((_QWORD)v51, c1j), v52);
  v54 = v51 + __PAIR128__(v52, c1j);
  c2j = v54 >> 64;
  c1k = v54;
  v55 = a[1] * (unsigned __int128)a[5];
  v56 = (v55 + __PAIR128__(c2j, c1k)) >> 64;
  v57 = (__CFADD__(__CFADD__((_QWORD)v55, c1k), c2j) | (unsigned __int8)__CFADD__(*((_QWORD *)&v55 + 1), v56))
      + (v8 | (unsigned __int8)__CFADD__(*((_QWORD *)&v51 + 1), c2j))
      + v53;
  c1l = v55 + c1k;
  v8 = __CFADD__(__CFADD__((_QWORD)v55, c1l), v56);
  v58 = v55 + __PAIR128__(v56, c1l);
  c2k = v58 >> 64;
  c1m = v58;
  v59 = *a * (unsigned __int128)a[6];
  v60 = (v59 + __PAIR128__(c2k, c1m)) >> 64;
  v61 = (__CFADD__(__CFADD__((_QWORD)v59, c1m), c2k) | (unsigned __int8)__CFADD__(*((_QWORD *)&v59 + 1), v60))
      + (v8 | (unsigned __int8)__CFADD__(*((_QWORD *)&v55 + 1), c2k))
      + v57;
  c1n = v59 + c1m;
  v8 = __CFADD__(__CFADD__((_QWORD)v59, c1n), v60);
  v63 = v59 + __PAIR128__(v60, c1n);
  v62 = (v59 + __PAIR128__(v60, c1n)) >> 64;
  c2l = v62;
  c3l = (v8 | (unsigned __int8)__CFADD__(*((_QWORD *)&v59 + 1), v62)) + v61;
  r[6] = v63;
  v64 = *a * (unsigned __int128)a[7];
  v65 = (v64 + __PAIR128__(c3l, v62)) >> 64;
  v66 = __CFADD__(__CFADD__((_QWORD)v64, c2l), c3l) | (unsigned __int8)__CFADD__(
                                                                         *((_QWORD *)&v64 + 1),
                                                                         (v64 + __PAIR128__(c3l, c2l)) >> 64);
  c2m = v64 + c2l;
  v8 = __CFADD__(__CFADD__((_QWORD)v64, c2m), v65);
  v67 = v64 + __PAIR128__(v65, c2m);
  c3m = v67 >> 64;
  c2n = v67;
  v68 = a[1] * (unsigned __int128)a[6];
  v69 = (v68 + __PAIR128__(c3m, c2n)) >> 64;
  v70 = (__CFADD__(__CFADD__((_QWORD)v68, c2n), c3m) | (unsigned __int8)__CFADD__(*((_QWORD *)&v68 + 1), v69))
      + (v8 | (unsigned __int8)__CFADD__(*((_QWORD *)&v64 + 1), c3m))
      + v66;
  c2o = v68 + c2n;
  v8 = __CFADD__(__CFADD__((_QWORD)v68, c2o), v69);
  v71 = v68 + __PAIR128__(v69, c2o);
  c3n = v71 >> 64;
  c2p = v71;
  v72 = a[2] * (unsigned __int128)a[5];
  v73 = (v72 + __PAIR128__(c3n, c2p)) >> 64;
  v74 = (__CFADD__(__CFADD__((_QWORD)v72, c2p), c3n) | (unsigned __int8)__CFADD__(*((_QWORD *)&v72 + 1), v73))
      + (v8 | (unsigned __int8)__CFADD__(*((_QWORD *)&v68 + 1), c3n))
      + v70;
  c2q = v72 + c2p;
  v8 = __CFADD__(__CFADD__((_QWORD)v72, c2q), v73);
  v75 = v72 + __PAIR128__(v73, c2q);
  c3o = v75 >> 64;
  c2r = v75;
  v76 = a[3] * (unsigned __int128)a[4];
  v77 = (v76 + __PAIR128__(c3o, c2r)) >> 64;
  v78 = (__CFADD__(__CFADD__((_QWORD)v76, c2r), c3o) | (unsigned __int8)__CFADD__(*((_QWORD *)&v76 + 1), v77))
      + (v8 | (unsigned __int8)__CFADD__(*((_QWORD *)&v72 + 1), c3o))
      + v74;
  c2s = v76 + c2r;
  v8 = __CFADD__(__CFADD__((_QWORD)v76, c2s), v77);
  v80 = v76 + __PAIR128__(v77, c2s);
  v79 = (v76 + __PAIR128__(v77, c2s)) >> 64;
  c1o = (v8 | (unsigned __int8)__CFADD__(*((_QWORD *)&v76 + 1), v79)) + v78;
  r[7] = v80;
  v81 = a[4] * (unsigned __int128)a[4];
  v82 = __CFADD__(__CFADD__((_QWORD)v81, v79), c1o) | (unsigned __int8)__CFADD__(
                                                                         *((_QWORD *)&v81 + 1),
                                                                         (v81 + __PAIR128__(c1o, v79)) >> 64);
  c3p = v81 + v79;
  c1p = (v81 + __PAIR128__(c1o, v79)) >> 64;
  v83 = a[3] * (unsigned __int128)a[5];
  v84 = (v83 + __PAIR128__(c1p, (unsigned __int64)v81 + v79)) >> 64;
  v85 = (__CFADD__(__CFADD__((_QWORD)v83, c3p), c1p) | (unsigned __int8)__CFADD__(
                                                                          *((_QWORD *)&v83 + 1),
                                                                          (v83 + __PAIR128__(c1p, c3p)) >> 64))
      + v82;
  c3q = v83 + c3p;
  v8 = __CFADD__(__CFADD__((_QWORD)v83, c3q), v84);
  v86 = v83 + __PAIR128__(v84, c3q);
  c1q = v86 >> 64;
  c3r = v86;
  v87 = a[2] * (unsigned __int128)a[6];
  v88 = (v87 + __PAIR128__(c1q, c3r)) >> 64;
  v89 = (__CFADD__(__CFADD__((_QWORD)v87, c3r), c1q) | (unsigned __int8)__CFADD__(*((_QWORD *)&v87 + 1), v88))
      + (v8 | (unsigned __int8)__CFADD__(*((_QWORD *)&v83 + 1), c1q))
      + v85;
  c3s = v87 + c3r;
  v8 = __CFADD__(__CFADD__((_QWORD)v87, c3s), v88);
  v90 = v87 + __PAIR128__(v88, c3s);
  c1r = v90 >> 64;
  c3t = v90;
  v91 = a[1] * (unsigned __int128)a[7];
  v92 = (v91 + __PAIR128__(c1r, c3t)) >> 64;
  v93 = (__CFADD__(__CFADD__((_QWORD)v91, c3t), c1r) | (unsigned __int8)__CFADD__(*((_QWORD *)&v91 + 1), v92))
      + (v8 | (unsigned __int8)__CFADD__(*((_QWORD *)&v87 + 1), c1r))
      + v89;
  c3u = v91 + c3t;
  v8 = __CFADD__(__CFADD__((_QWORD)v91, c3u), v92);
  v95 = v91 + __PAIR128__(v92, c3u);
  v94 = (v91 + __PAIR128__(v92, c3u)) >> 64;
  c1s = v94;
  c2t = (v8 | (unsigned __int8)__CFADD__(*((_QWORD *)&v91 + 1), v94)) + v93;
  r[8] = v95;
  v96 = a[2] * (unsigned __int128)a[7];
  v97 = (v96 + __PAIR128__(c2t, v94)) >> 64;
  v98 = __CFADD__(__CFADD__((_QWORD)v96, c1s), c2t) | (unsigned __int8)__CFADD__(
                                                                         *((_QWORD *)&v96 + 1),
                                                                         (v96 + __PAIR128__(c2t, c1s)) >> 64);
  c1t = v96 + c1s;
  v8 = __CFADD__(__CFADD__((_QWORD)v96, c1t), v97);
  v99 = v96 + __PAIR128__(v97, c1t);
  c2u = v99 >> 64;
  c1u = v99;
  v100 = a[3] * (unsigned __int128)a[6];
  v101 = (v100 + __PAIR128__(c2u, c1u)) >> 64;
  v102 = (__CFADD__(__CFADD__((_QWORD)v100, c1u), c2u) | (unsigned __int8)__CFADD__(*((_QWORD *)&v100 + 1), v101))
       + (v8 | (unsigned __int8)__CFADD__(*((_QWORD *)&v96 + 1), c2u))
       + v98;
  c1v = v100 + c1u;
  v8 = __CFADD__(__CFADD__((_QWORD)v100, c1v), v101);
  v103 = v100 + __PAIR128__(v101, c1v);
  c2v = v103 >> 64;
  c1w = v103;
  v104 = a[4] * (unsigned __int128)a[5];
  v105 = (v104 + __PAIR128__(c2v, c1w)) >> 64;
  v106 = (__CFADD__(__CFADD__((_QWORD)v104, c1w), c2v) | (unsigned __int8)__CFADD__(*((_QWORD *)&v104 + 1), v105))
       + (v8 | (unsigned __int8)__CFADD__(*((_QWORD *)&v100 + 1), c2v))
       + v102;
  c1x = v104 + c1w;
  v8 = __CFADD__(__CFADD__((_QWORD)v104, c1x), v105);
  v108 = v104 + __PAIR128__(v105, c1x);
  v107 = (v104 + __PAIR128__(v105, c1x)) >> 64;
  c3v = (v8 | (unsigned __int8)__CFADD__(*((_QWORD *)&v104 + 1), v107)) + v106;
  r[9] = v108;
  v109 = a[5] * (unsigned __int128)a[5];
  v110 = __CFADD__(__CFADD__((_QWORD)v109, v107), c3v) | (unsigned __int8)__CFADD__(
                                                                            *((_QWORD *)&v109 + 1),
                                                                            (v109 + __PAIR128__(c3v, v107)) >> 64);
  c2w = v109 + v107;
  c3w = (v109 + __PAIR128__(c3v, v107)) >> 64;
  v111 = a[4] * (unsigned __int128)a[6];
  v112 = (v111 + __PAIR128__(c3w, (unsigned __int64)v109 + v107)) >> 64;
  v113 = (__CFADD__(__CFADD__((_QWORD)v111, c2w), c3w) | (unsigned __int8)__CFADD__(
                                                                            *((_QWORD *)&v111 + 1),
                                                                            (v111 + __PAIR128__(c3w, c2w)) >> 64))
       + v110;
  c2x = v111 + c2w;
  v8 = __CFADD__(__CFADD__((_QWORD)v111, c2x), v112);
  v114 = v111 + __PAIR128__(v112, c2x);
  c3x = v114 >> 64;
  c2y = v114;
  v115 = a[3] * (unsigned __int128)a[7];
  v116 = (v115 + __PAIR128__(c3x, c2y)) >> 64;
  v117 = (__CFADD__(__CFADD__((_QWORD)v115, c2y), c3x) | (unsigned __int8)__CFADD__(*((_QWORD *)&v115 + 1), v116))
       + (v8 | (unsigned __int8)__CFADD__(*((_QWORD *)&v111 + 1), c3x))
       + v113;
  c2z = v115 + c2y;
  v8 = __CFADD__(__CFADD__((_QWORD)v115, c2z), v116);
  v119 = v115 + __PAIR128__(v116, c2z);
  v118 = (v115 + __PAIR128__(v116, c2z)) >> 64;
  c3y = v118;
  c1y = (v8 | (unsigned __int8)__CFADD__(*((_QWORD *)&v115 + 1), v118)) + v117;
  r[10] = v119;
  v120 = a[4] * (unsigned __int128)a[7];
  v121 = (v120 + __PAIR128__(c1y, v118)) >> 64;
  v122 = __CFADD__(__CFADD__((_QWORD)v120, c3y), c1y) | (unsigned __int8)__CFADD__(
                                                                           *((_QWORD *)&v120 + 1),
                                                                           (v120 + __PAIR128__(c1y, c3y)) >> 64);
  c3z = v120 + c3y;
  v8 = __CFADD__(__CFADD__((_QWORD)v120, c3z), v121);
  v123 = v120 + __PAIR128__(v121, c3z);
  c1z = v123 >> 64;
  c3ba = v123;
  v124 = a[5] * (unsigned __int128)a[6];
  v125 = (v124 + __PAIR128__(c1z, c3ba)) >> 64;
  v126 = (__CFADD__(__CFADD__((_QWORD)v124, c3ba), c1z) | (unsigned __int8)__CFADD__(*((_QWORD *)&v124 + 1), v125))
       + (v8 | (unsigned __int8)__CFADD__(*((_QWORD *)&v120 + 1), c1z))
       + v122;
  c3bb = v124 + c3ba;
  v8 = __CFADD__(__CFADD__((_QWORD)v124, c3bb), v125);
  v128 = v124 + __PAIR128__(v125, c3bb);
  v127 = (v124 + __PAIR128__(v125, c3bb)) >> 64;
  c2ba = (v8 | (unsigned __int8)__CFADD__(*((_QWORD *)&v124 + 1), v127)) + v126;
  r[11] = v128;
  v129 = a[6] * (unsigned __int128)a[6];
  v130 = __CFADD__(__CFADD__((_QWORD)v129, v127), c2ba) | (unsigned __int8)__CFADD__(
                                                                             *((_QWORD *)&v129 + 1),
                                                                             (v129 + __PAIR128__(c2ba, v127)) >> 64);
  c1ba = v129 + v127;
  c2bb = (v129 + __PAIR128__(c2ba, v127)) >> 64;
  v131 = a[5] * (unsigned __int128)a[7];
  v132 = (v131 + __PAIR128__(c2bb, (unsigned __int64)v129 + v127)) >> 64;
  v133 = (__CFADD__(__CFADD__((_QWORD)v131, c1ba), c2bb) | (unsigned __int8)__CFADD__(
                                                                              *((_QWORD *)&v131 + 1),
                                                                              (v131 + __PAIR128__(c2bb, c1ba)) >> 64))
       + v130;
  c1bb = v131 + c1ba;
  v8 = __CFADD__(__CFADD__((_QWORD)v131, c1bb), v132);
  v135 = v131 + __PAIR128__(v132, c1bb);
  v134 = (v131 + __PAIR128__(v132, c1bb)) >> 64;
  c3bc = (v8 | (unsigned __int8)__CFADD__(*((_QWORD *)&v131 + 1), v134)) + v133;
  r[12] = v135;
  v136 = a[6] * (unsigned __int128)a[7];
  r[13] = v136 + v136 + v134;
  *((_OWORD *)r + 7) = a[7] * (unsigned __int128)a[7]
                     + __PAIR128__(
                         (__CFADD__(__CFADD__((_QWORD)v136, v136 + v134), (v136 + __PAIR128__(c3bc, v134)) >> 64) | (unsigned __int8)__CFADD__(*((_QWORD *)&v136 + 1), (v136 + v136 + __PAIR128__(c3bc, v134)) >> 64))
                       + (unsigned __int64)(__CFADD__(__CFADD__((_QWORD)v136, v134), c3bc) | (unsigned __int8)__CFADD__(*((_QWORD *)&v136 + 1), (v136 + __PAIR128__(c3bc, v134)) >> 64)),
                         (v136 + v136 + __PAIR128__(c3bc, v134)) >> 64);
}