void __cdecl bn_mul_comba8(unsigned __int64 *r, unsigned __int64 *a, unsigned __int64 *b)
{
  unsigned __int128 v3; // rax
  unsigned __int64 v4; // rcx
  unsigned __int128 v5; // kr10_16
  unsigned __int128 v6; // kr20_16
  unsigned __int64 v7; // rcx
  unsigned __int128 v8; // kr40_16
  unsigned __int64 v9; // rcx
  unsigned __int128 v10; // kr60_16
  unsigned __int64 v11; // rcx
  unsigned __int128 v12; // kr80_16
  unsigned __int128 v13; // kr90_16
  unsigned __int64 v14; // rcx
  unsigned __int128 v15; // krB0_16
  unsigned __int64 v16; // rcx
  unsigned __int128 v17; // krD0_16
  unsigned __int64 v18; // rcx
  unsigned __int128 v19; // krF0_16
  unsigned __int128 v20; // kr100_16
  unsigned __int64 v21; // rcx
  unsigned __int128 v22; // kr120_16
  unsigned __int64 v23; // rcx
  unsigned __int128 v24; // kr140_16
  unsigned __int64 v25; // rcx
  unsigned __int128 v26; // kr160_16
  unsigned __int64 v27; // rcx
  unsigned __int128 v28; // kr180_16
  unsigned __int128 v29; // kr190_16
  unsigned __int64 v30; // rcx
  unsigned __int128 v31; // kr1B0_16
  unsigned __int64 v32; // rcx
  unsigned __int128 v33; // kr1D0_16
  unsigned __int64 v34; // rcx
  unsigned __int128 v35; // kr1F0_16
  unsigned __int64 v36; // rcx
  unsigned __int128 v37; // kr210_16
  unsigned __int64 v38; // rcx
  unsigned __int128 v39; // kr230_16
  unsigned __int128 v40; // kr240_16
  unsigned __int64 v41; // rcx
  unsigned __int128 v42; // kr260_16
  unsigned __int64 v43; // rcx
  unsigned __int128 v44; // kr280_16
  unsigned __int64 v45; // rcx
  unsigned __int128 v46; // kr2A0_16
  unsigned __int64 v47; // rcx
  unsigned __int128 v48; // kr2C0_16
  unsigned __int64 v49; // rcx
  unsigned __int128 v50; // kr2E0_16
  unsigned __int64 v51; // rcx
  unsigned __int128 v52; // kr300_16
  unsigned __int128 v53; // kr310_16
  unsigned __int64 v54; // rcx
  unsigned __int128 v55; // kr330_16
  unsigned __int64 v56; // rcx
  unsigned __int128 v57; // kr350_16
  unsigned __int64 v58; // rcx
  unsigned __int128 v59; // kr370_16
  unsigned __int64 v60; // rcx
  unsigned __int128 v61; // kr390_16
  unsigned __int64 v62; // rcx
  unsigned __int128 v63; // kr3B0_16
  unsigned __int64 v64; // rcx
  unsigned __int128 v65; // kr3D0_16
  unsigned __int64 v66; // rcx
  unsigned __int128 v67; // kr3F0_16
  unsigned __int128 v68; // kr400_16
  unsigned __int64 v69; // rcx
  unsigned __int128 v70; // kr420_16
  unsigned __int64 v71; // rcx
  unsigned __int128 v72; // kr440_16
  unsigned __int64 v73; // rcx
  unsigned __int128 v74; // kr460_16
  unsigned __int64 v75; // rcx
  unsigned __int128 v76; // kr480_16
  unsigned __int64 v77; // rcx
  unsigned __int128 v78; // kr4A0_16
  unsigned __int64 v79; // rcx
  unsigned __int128 v80; // kr4C0_16
  unsigned __int128 v81; // kr4D0_16
  unsigned __int64 v82; // rcx
  unsigned __int128 v83; // kr4F0_16
  unsigned __int64 v84; // rcx
  unsigned __int128 v85; // kr510_16
  unsigned __int64 v86; // rcx
  unsigned __int128 v87; // kr530_16
  unsigned __int64 v88; // rcx
  unsigned __int128 v89; // kr550_16
  unsigned __int64 v90; // rcx
  unsigned __int128 v91; // kr570_16
  unsigned __int128 v92; // kr580_16
  unsigned __int64 v93; // rcx
  unsigned __int128 v94; // kr5A0_16
  unsigned __int64 v95; // rcx
  unsigned __int128 v96; // kr5C0_16
  unsigned __int64 v97; // rcx
  unsigned __int128 v98; // kr5E0_16
  unsigned __int64 v99; // rcx
  unsigned __int128 v100; // kr600_16
  unsigned __int128 v101; // kr610_16
  unsigned __int64 v102; // rcx
  unsigned __int128 v103; // kr630_16
  unsigned __int64 v104; // rcx
  unsigned __int128 v105; // kr650_16
  unsigned __int64 v106; // rcx
  unsigned __int128 v107; // kr670_16
  unsigned __int128 v108; // kr680_16
  unsigned __int64 v109; // rcx
  unsigned __int128 v110; // kr6A0_16
  unsigned __int64 v111; // rcx
  unsigned __int128 v112; // kr6C0_16
  unsigned __int128 v113; // kr6D0_16
  unsigned __int64 v114; // rcx
  unsigned __int128 v115; // kr6F0_16
  unsigned __int64 c3; // [rsp+400h] [rbp-30h]
  unsigned __int64 c3a; // [rsp+400h] [rbp-30h]
  unsigned __int64 c3b; // [rsp+400h] [rbp-30h]
  unsigned __int64 c3c; // [rsp+400h] [rbp-30h]
  unsigned __int64 c3d; // [rsp+400h] [rbp-30h]
  unsigned __int64 c3e; // [rsp+400h] [rbp-30h]
  unsigned __int64 c3f; // [rsp+400h] [rbp-30h]
  unsigned __int64 c3g; // [rsp+400h] [rbp-30h]
  unsigned __int64 c3h; // [rsp+400h] [rbp-30h]
  unsigned __int64 c3i; // [rsp+400h] [rbp-30h]
  unsigned __int64 c3j; // [rsp+400h] [rbp-30h]
  unsigned __int64 c3k; // [rsp+400h] [rbp-30h]
  unsigned __int64 c3l; // [rsp+400h] [rbp-30h]
  unsigned __int64 c3m; // [rsp+400h] [rbp-30h]
  unsigned __int64 c3n; // [rsp+400h] [rbp-30h]
  unsigned __int64 c3o; // [rsp+400h] [rbp-30h]
  unsigned __int64 c3p; // [rsp+400h] [rbp-30h]
  unsigned __int64 c3q; // [rsp+400h] [rbp-30h]
  unsigned __int64 c3r; // [rsp+400h] [rbp-30h]
  unsigned __int64 c3s; // [rsp+400h] [rbp-30h]
  unsigned __int64 c3t; // [rsp+400h] [rbp-30h]
  unsigned __int64 c3u; // [rsp+400h] [rbp-30h]
  unsigned __int64 c3v; // [rsp+400h] [rbp-30h]
  unsigned __int64 c3w; // [rsp+400h] [rbp-30h]
  unsigned __int64 c3x; // [rsp+400h] [rbp-30h]
  unsigned __int64 c3y; // [rsp+400h] [rbp-30h]
  unsigned __int64 c3z; // [rsp+400h] [rbp-30h]
  unsigned __int64 c3ba; // [rsp+400h] [rbp-30h]
  unsigned __int64 c3bb; // [rsp+400h] [rbp-30h]
  unsigned __int64 c3bc; // [rsp+400h] [rbp-30h]
  unsigned __int64 c3bd; // [rsp+400h] [rbp-30h]
  unsigned __int64 c3be; // [rsp+400h] [rbp-30h]
  unsigned __int64 c3bf; // [rsp+400h] [rbp-30h]
  unsigned __int64 c3bg; // [rsp+400h] [rbp-30h]
  unsigned __int64 c2; // [rsp+408h] [rbp-28h]
  unsigned __int64 c2a; // [rsp+408h] [rbp-28h]
  unsigned __int64 c2b; // [rsp+408h] [rbp-28h]
  unsigned __int64 c2c; // [rsp+408h] [rbp-28h]
  unsigned __int64 c2d; // [rsp+408h] [rbp-28h]
  unsigned __int64 c2e; // [rsp+408h] [rbp-28h]
  unsigned __int64 c2f; // [rsp+408h] [rbp-28h]
  unsigned __int64 c2g; // [rsp+408h] [rbp-28h]
  unsigned __int64 c2h; // [rsp+408h] [rbp-28h]
  unsigned __int64 c2i; // [rsp+408h] [rbp-28h]
  unsigned __int64 c2j; // [rsp+408h] [rbp-28h]
  unsigned __int64 c2k; // [rsp+408h] [rbp-28h]
  unsigned __int64 c2l; // [rsp+408h] [rbp-28h]
  unsigned __int64 c2m; // [rsp+408h] [rbp-28h]
  unsigned __int64 c2n; // [rsp+408h] [rbp-28h]
  unsigned __int64 c2o; // [rsp+408h] [rbp-28h]
  unsigned __int64 c2p; // [rsp+408h] [rbp-28h]
  unsigned __int64 c2q; // [rsp+408h] [rbp-28h]
  unsigned __int64 c2r; // [rsp+408h] [rbp-28h]
  unsigned __int64 c2s; // [rsp+408h] [rbp-28h]
  unsigned __int64 c2t; // [rsp+408h] [rbp-28h]
  unsigned __int64 c2u; // [rsp+408h] [rbp-28h]
  unsigned __int64 c2v; // [rsp+408h] [rbp-28h]
  unsigned __int64 c2w; // [rsp+408h] [rbp-28h]
  unsigned __int64 c2x; // [rsp+408h] [rbp-28h]
  unsigned __int64 c2y; // [rsp+408h] [rbp-28h]
  unsigned __int64 c2z; // [rsp+408h] [rbp-28h]
  unsigned __int64 c2ba; // [rsp+408h] [rbp-28h]
  unsigned __int64 c2bb; // [rsp+408h] [rbp-28h]
  unsigned __int64 c2bc; // [rsp+408h] [rbp-28h]
  unsigned __int64 c2bd; // [rsp+408h] [rbp-28h]
  unsigned __int64 c2be; // [rsp+408h] [rbp-28h]
  unsigned __int64 c2bf; // [rsp+408h] [rbp-28h]
  unsigned __int64 c1; // [rsp+410h] [rbp-20h]
  unsigned __int64 c1a; // [rsp+410h] [rbp-20h]
  unsigned __int64 c1b; // [rsp+410h] [rbp-20h]
  unsigned __int64 c1c; // [rsp+410h] [rbp-20h]
  unsigned __int64 c1d; // [rsp+410h] [rbp-20h]
  unsigned __int64 c1e; // [rsp+410h] [rbp-20h]
  unsigned __int64 c1f; // [rsp+410h] [rbp-20h]
  unsigned __int64 c1g; // [rsp+410h] [rbp-20h]
  unsigned __int64 c1h; // [rsp+410h] [rbp-20h]
  unsigned __int64 c1i; // [rsp+410h] [rbp-20h]
  unsigned __int64 c1j; // [rsp+410h] [rbp-20h]
  unsigned __int64 c1k; // [rsp+410h] [rbp-20h]
  unsigned __int64 c1l; // [rsp+410h] [rbp-20h]
  unsigned __int64 c1m; // [rsp+410h] [rbp-20h]
  unsigned __int64 c1n; // [rsp+410h] [rbp-20h]
  unsigned __int64 c1o; // [rsp+410h] [rbp-20h]
  unsigned __int64 c1p; // [rsp+410h] [rbp-20h]
  unsigned __int64 c1q; // [rsp+410h] [rbp-20h]
  unsigned __int64 c1r; // [rsp+410h] [rbp-20h]
  unsigned __int64 c1s; // [rsp+410h] [rbp-20h]
  unsigned __int64 c1t; // [rsp+410h] [rbp-20h]
  unsigned __int64 c1u; // [rsp+410h] [rbp-20h]
  unsigned __int64 c1v; // [rsp+410h] [rbp-20h]
  unsigned __int64 c1w; // [rsp+410h] [rbp-20h]
  unsigned __int64 c1x; // [rsp+410h] [rbp-20h]
  unsigned __int64 c1y; // [rsp+410h] [rbp-20h]
  unsigned __int64 c1z; // [rsp+410h] [rbp-20h]
  unsigned __int64 c1ba; // [rsp+410h] [rbp-20h]
  unsigned __int64 c1bb; // [rsp+410h] [rbp-20h]
  unsigned __int64 c1bc; // [rsp+410h] [rbp-20h]
  unsigned __int64 c1bd; // [rsp+410h] [rbp-20h]
  unsigned __int64 c1be; // [rsp+410h] [rbp-20h]

  v3 = *b * (unsigned __int128)*a;
  v4 = (v3 + 0) >> 64;
  c3 = __CFADD__(*((_QWORD *)&v3 + 1), v4);
  *r = v3;
  v5 = b[1] * (unsigned __int128)*a;
  *(_QWORD *)&v3 = __CFADD__(__CFADD__((_QWORD)v5, v4), c3) | (unsigned __int8)__CFADD__(
                                                                                 *((_QWORD *)&v5 + 1),
                                                                                 (v5 + __PAIR128__(c3, v4)) >> 64);
  c2 = v5 + v4;
  c3a = (v5 + __PAIR128__(c3, v4)) >> 64;
  v6 = *b * (unsigned __int128)a[1];
  v7 = (v6 + __PAIR128__(c3a, (unsigned __int64)v5 + v4)) >> 64;
  *(_QWORD *)&v3 = (__CFADD__(__CFADD__((_QWORD)v6, c2), c3a) | (unsigned __int8)__CFADD__(
                                                                                   *((_QWORD *)&v6 + 1),
                                                                                   (v6 + __PAIR128__(c3a, c2)) >> 64))
                 + (_QWORD)v3;
  c3b = (v6 + __PAIR128__(c3a, c2)) >> 64;
  r[1] = v6 + c2;
  v8 = *b * (unsigned __int128)a[2];
  v9 = (v8 + __PAIR128__(v3, v7)) >> 64;
  *(_QWORD *)&v3 = __CFADD__(__CFADD__((_QWORD)v8, c3b), (_QWORD)v3) | (unsigned __int8)__CFADD__(
                                                                                          *((_QWORD *)&v8 + 1),
                                                                                          (v8 + __PAIR128__(v3, c3b)) >> 64);
  c3c = v8 + c3b;
  c1 = v9;
  v10 = b[1] * (unsigned __int128)a[1];
  v11 = (v10 + __PAIR128__(v9, c3c)) >> 64;
  *(_QWORD *)&v3 = (__CFADD__(__CFADD__((_QWORD)v10, c3c), c1) | (unsigned __int8)__CFADD__(
                                                                                    *((_QWORD *)&v10 + 1),
                                                                                    (v10 + __PAIR128__(c1, c3c)) >> 64))
                 + (_QWORD)v3;
  c3d = v10 + c3c;
  v12 = b[2] * (unsigned __int128)*a;
  *(_QWORD *)&v3 = (__CFADD__(__CFADD__((_QWORD)v12, c3d), v11) | (unsigned __int8)__CFADD__(
                                                                                     *((_QWORD *)&v12 + 1),
                                                                                     (v12 + __PAIR128__(v11, c3d)) >> 64))
                 + (_QWORD)v3;
  c1a = (v12 + __PAIR128__(v11, c3d)) >> 64;
  r[2] = v12 + c3d;
  v13 = b[3] * (unsigned __int128)*a;
  v14 = (v13 + __PAIR128__(v3, c1a)) >> 64;
  *(_QWORD *)&v3 = __CFADD__(__CFADD__((_QWORD)v13, c1a), (_QWORD)v3) | (unsigned __int8)__CFADD__(
                                                                                           *((_QWORD *)&v13 + 1),
                                                                                           v14);
  c1b = v13 + c1a;
  c2a = v14;
  v15 = b[2] * (unsigned __int128)a[1];
  v16 = (v15 + __PAIR128__(v14, c1b)) >> 64;
  *(_QWORD *)&v3 = (__CFADD__(__CFADD__((_QWORD)v15, c1b), c2a) | (unsigned __int8)__CFADD__(
                                                                                     *((_QWORD *)&v15 + 1),
                                                                                     (v15 + __PAIR128__(c2a, c1b)) >> 64))
                 + (_QWORD)v3;
  c1c = v15 + c1b;
  c2b = v16;
  v17 = b[1] * (unsigned __int128)a[2];
  v18 = (v17 + __PAIR128__(v16, c1c)) >> 64;
  *(_QWORD *)&v3 = (__CFADD__(__CFADD__((_QWORD)v17, c1c), c2b) | (unsigned __int8)__CFADD__(
                                                                                     *((_QWORD *)&v17 + 1),
                                                                                     (v17 + __PAIR128__(c2b, c1c)) >> 64))
                 + (_QWORD)v3;
  c1d = v17 + c1c;
  v19 = *b * (unsigned __int128)a[3];
  *(_QWORD *)&v3 = (__CFADD__(__CFADD__((_QWORD)v19, c1d), v18) | (unsigned __int8)__CFADD__(
                                                                                     *((_QWORD *)&v19 + 1),
                                                                                     (v19 + __PAIR128__(v18, c1d)) >> 64))
                 + (_QWORD)v3;
  c2c = (v19 + __PAIR128__(v18, c1d)) >> 64;
  r[3] = v19 + c1d;
  v20 = *b * (unsigned __int128)a[4];
  v21 = (v20 + __PAIR128__(v3, c2c)) >> 64;
  *(_QWORD *)&v3 = __CFADD__(__CFADD__((_QWORD)v20, c2c), (_QWORD)v3) | (unsigned __int8)__CFADD__(
                                                                                           *((_QWORD *)&v20 + 1),
                                                                                           v21);
  c2d = v20 + c2c;
  c3e = v21;
  v22 = b[1] * (unsigned __int128)a[3];
  v23 = (v22 + __PAIR128__(v21, c2d)) >> 64;
  *(_QWORD *)&v3 = (__CFADD__(__CFADD__((_QWORD)v22, c2d), c3e) | (unsigned __int8)__CFADD__(
                                                                                     *((_QWORD *)&v22 + 1),
                                                                                     (v22 + __PAIR128__(c3e, c2d)) >> 64))
                 + (_QWORD)v3;
  c2e = v22 + c2d;
  c3f = v23;
  v24 = b[2] * (unsigned __int128)a[2];
  v25 = (v24 + __PAIR128__(v23, c2e)) >> 64;
  *(_QWORD *)&v3 = (__CFADD__(__CFADD__((_QWORD)v24, c2e), c3f) | (unsigned __int8)__CFADD__(
                                                                                     *((_QWORD *)&v24 + 1),
                                                                                     (v24 + __PAIR128__(c3f, c2e)) >> 64))
                 + (_QWORD)v3;
  c2f = v24 + c2e;
  c3g = v25;
  v26 = b[3] * (unsigned __int128)a[1];
  v27 = (v26 + __PAIR128__(v25, c2f)) >> 64;
  *(_QWORD *)&v3 = (__CFADD__(__CFADD__((_QWORD)v26, c2f), c3g) | (unsigned __int8)__CFADD__(
                                                                                     *((_QWORD *)&v26 + 1),
                                                                                     (v26 + __PAIR128__(c3g, c2f)) >> 64))
                 + (_QWORD)v3;
  c2g = v26 + c2f;
  v28 = b[4] * (unsigned __int128)*a;
  *(_QWORD *)&v3 = (__CFADD__(__CFADD__((_QWORD)v28, c2g), v27) | (unsigned __int8)__CFADD__(
                                                                                     *((_QWORD *)&v28 + 1),
                                                                                     (v28 + __PAIR128__(v27, c2g)) >> 64))
                 + (_QWORD)v3;
  c3h = (v28 + __PAIR128__(v27, c2g)) >> 64;
  r[4] = v28 + c2g;
  v29 = b[5] * (unsigned __int128)*a;
  v30 = (v29 + __PAIR128__(v3, c3h)) >> 64;
  *(_QWORD *)&v3 = __CFADD__(__CFADD__((_QWORD)v29, c3h), (_QWORD)v3) | (unsigned __int8)__CFADD__(
                                                                                           *((_QWORD *)&v29 + 1),
                                                                                           v30);
  c3i = v29 + c3h;
  c1e = v30;
  v31 = b[4] * (unsigned __int128)a[1];
  v32 = (v31 + __PAIR128__(v30, c3i)) >> 64;
  *(_QWORD *)&v3 = (__CFADD__(__CFADD__((_QWORD)v31, c3i), c1e) | (unsigned __int8)__CFADD__(
                                                                                     *((_QWORD *)&v31 + 1),
                                                                                     (v31 + __PAIR128__(c1e, c3i)) >> 64))
                 + (_QWORD)v3;
  c3j = v31 + c3i;
  c1f = v32;
  v33 = b[3] * (unsigned __int128)a[2];
  v34 = (v33 + __PAIR128__(v32, c3j)) >> 64;
  *(_QWORD *)&v3 = (__CFADD__(__CFADD__((_QWORD)v33, c3j), c1f) | (unsigned __int8)__CFADD__(
                                                                                     *((_QWORD *)&v33 + 1),
                                                                                     (v33 + __PAIR128__(c1f, c3j)) >> 64))
                 + (_QWORD)v3;
  c3k = v33 + c3j;
  c1g = v34;
  v35 = b[2] * (unsigned __int128)a[3];
  v36 = (v35 + __PAIR128__(v34, c3k)) >> 64;
  *(_QWORD *)&v3 = (__CFADD__(__CFADD__((_QWORD)v35, c3k), c1g) | (unsigned __int8)__CFADD__(
                                                                                     *((_QWORD *)&v35 + 1),
                                                                                     (v35 + __PAIR128__(c1g, c3k)) >> 64))
                 + (_QWORD)v3;
  c3l = v35 + c3k;
  c1h = v36;
  v37 = b[1] * (unsigned __int128)a[4];
  v38 = (v37 + __PAIR128__(v36, c3l)) >> 64;
  *(_QWORD *)&v3 = (__CFADD__(__CFADD__((_QWORD)v37, c3l), c1h) | (unsigned __int8)__CFADD__(
                                                                                     *((_QWORD *)&v37 + 1),
                                                                                     (v37 + __PAIR128__(c1h, c3l)) >> 64))
                 + (_QWORD)v3;
  c3m = v37 + c3l;
  v39 = *b * (unsigned __int128)a[5];
  *(_QWORD *)&v3 = (__CFADD__(__CFADD__((_QWORD)v39, c3m), v38) | (unsigned __int8)__CFADD__(
                                                                                     *((_QWORD *)&v39 + 1),
                                                                                     (v39 + __PAIR128__(v38, c3m)) >> 64))
                 + (_QWORD)v3;
  c1i = (v39 + __PAIR128__(v38, c3m)) >> 64;
  r[5] = v39 + c3m;
  v40 = *b * (unsigned __int128)a[6];
  v41 = (v40 + __PAIR128__(v3, c1i)) >> 64;
  *(_QWORD *)&v3 = __CFADD__(__CFADD__((_QWORD)v40, c1i), (_QWORD)v3) | (unsigned __int8)__CFADD__(
                                                                                           *((_QWORD *)&v40 + 1),
                                                                                           v41);
  c1j = v40 + c1i;
  c2h = v41;
  v42 = b[1] * (unsigned __int128)a[5];
  v43 = (v42 + __PAIR128__(v41, c1j)) >> 64;
  *(_QWORD *)&v3 = (__CFADD__(__CFADD__((_QWORD)v42, c1j), c2h) | (unsigned __int8)__CFADD__(
                                                                                     *((_QWORD *)&v42 + 1),
                                                                                     (v42 + __PAIR128__(c2h, c1j)) >> 64))
                 + (_QWORD)v3;
  c1k = v42 + c1j;
  c2i = v43;
  v44 = b[2] * (unsigned __int128)a[4];
  v45 = (v44 + __PAIR128__(v43, c1k)) >> 64;
  *(_QWORD *)&v3 = (__CFADD__(__CFADD__((_QWORD)v44, c1k), c2i) | (unsigned __int8)__CFADD__(
                                                                                     *((_QWORD *)&v44 + 1),
                                                                                     (v44 + __PAIR128__(c2i, c1k)) >> 64))
                 + (_QWORD)v3;
  c1l = v44 + c1k;
  c2j = v45;
  v46 = b[3] * (unsigned __int128)a[3];
  v47 = (v46 + __PAIR128__(v45, c1l)) >> 64;
  *(_QWORD *)&v3 = (__CFADD__(__CFADD__((_QWORD)v46, c1l), c2j) | (unsigned __int8)__CFADD__(
                                                                                     *((_QWORD *)&v46 + 1),
                                                                                     (v46 + __PAIR128__(c2j, c1l)) >> 64))
                 + (_QWORD)v3;
  c1m = v46 + c1l;
  c2k = v47;
  v48 = b[4] * (unsigned __int128)a[2];
  v49 = (v48 + __PAIR128__(v47, c1m)) >> 64;
  *(_QWORD *)&v3 = (__CFADD__(__CFADD__((_QWORD)v48, c1m), c2k) | (unsigned __int8)__CFADD__(
                                                                                     *((_QWORD *)&v48 + 1),
                                                                                     (v48 + __PAIR128__(c2k, c1m)) >> 64))
                 + (_QWORD)v3;
  c1n = v48 + c1m;
  c2l = v49;
  v50 = b[5] * (unsigned __int128)a[1];
  v51 = (v50 + __PAIR128__(v49, c1n)) >> 64;
  *(_QWORD *)&v3 = (__CFADD__(__CFADD__((_QWORD)v50, c1n), c2l) | (unsigned __int8)__CFADD__(
                                                                                     *((_QWORD *)&v50 + 1),
                                                                                     (v50 + __PAIR128__(c2l, c1n)) >> 64))
                 + (_QWORD)v3;
  c1o = v50 + c1n;
  v52 = b[6] * (unsigned __int128)*a;
  *(_QWORD *)&v3 = (__CFADD__(__CFADD__((_QWORD)v52, c1o), v51) | (unsigned __int8)__CFADD__(
                                                                                     *((_QWORD *)&v52 + 1),
                                                                                     (v52 + __PAIR128__(v51, c1o)) >> 64))
                 + (_QWORD)v3;
  c2m = (v52 + __PAIR128__(v51, c1o)) >> 64;
  r[6] = v52 + c1o;
  v53 = b[7] * (unsigned __int128)*a;
  v54 = (v53 + __PAIR128__(v3, c2m)) >> 64;
  *(_QWORD *)&v3 = __CFADD__(__CFADD__((_QWORD)v53, c2m), (_QWORD)v3) | (unsigned __int8)__CFADD__(
                                                                                           *((_QWORD *)&v53 + 1),
                                                                                           v54);
  c2n = v53 + c2m;
  c3n = v54;
  v55 = b[6] * (unsigned __int128)a[1];
  v56 = (v55 + __PAIR128__(v54, c2n)) >> 64;
  *(_QWORD *)&v3 = (__CFADD__(__CFADD__((_QWORD)v55, c2n), c3n) | (unsigned __int8)__CFADD__(
                                                                                     *((_QWORD *)&v55 + 1),
                                                                                     (v55 + __PAIR128__(c3n, c2n)) >> 64))
                 + (_QWORD)v3;
  c2o = v55 + c2n;
  c3o = v56;
  v57 = b[5] * (unsigned __int128)a[2];
  v58 = (v57 + __PAIR128__(v56, c2o)) >> 64;
  *(_QWORD *)&v3 = (__CFADD__(__CFADD__((_QWORD)v57, c2o), c3o) | (unsigned __int8)__CFADD__(
                                                                                     *((_QWORD *)&v57 + 1),
                                                                                     (v57 + __PAIR128__(c3o, c2o)) >> 64))
                 + (_QWORD)v3;
  c2p = v57 + c2o;
  c3p = v58;
  v59 = b[4] * (unsigned __int128)a[3];
  v60 = (v59 + __PAIR128__(v58, c2p)) >> 64;
  *(_QWORD *)&v3 = (__CFADD__(__CFADD__((_QWORD)v59, c2p), c3p) | (unsigned __int8)__CFADD__(
                                                                                     *((_QWORD *)&v59 + 1),
                                                                                     (v59 + __PAIR128__(c3p, c2p)) >> 64))
                 + (_QWORD)v3;
  c2q = v59 + c2p;
  c3q = v60;
  v61 = b[3] * (unsigned __int128)a[4];
  v62 = (v61 + __PAIR128__(v60, c2q)) >> 64;
  *(_QWORD *)&v3 = (__CFADD__(__CFADD__((_QWORD)v61, c2q), c3q) | (unsigned __int8)__CFADD__(
                                                                                     *((_QWORD *)&v61 + 1),
                                                                                     (v61 + __PAIR128__(c3q, c2q)) >> 64))
                 + (_QWORD)v3;
  c2r = v61 + c2q;
  c3r = v62;
  v63 = b[2] * (unsigned __int128)a[5];
  v64 = (v63 + __PAIR128__(v62, c2r)) >> 64;
  *(_QWORD *)&v3 = (__CFADD__(__CFADD__((_QWORD)v63, c2r), c3r) | (unsigned __int8)__CFADD__(
                                                                                     *((_QWORD *)&v63 + 1),
                                                                                     (v63 + __PAIR128__(c3r, c2r)) >> 64))
                 + (_QWORD)v3;
  c2s = v63 + c2r;
  c3s = v64;
  v65 = b[1] * (unsigned __int128)a[6];
  v66 = (v65 + __PAIR128__(v64, c2s)) >> 64;
  *(_QWORD *)&v3 = (__CFADD__(__CFADD__((_QWORD)v65, c2s), c3s) | (unsigned __int8)__CFADD__(
                                                                                     *((_QWORD *)&v65 + 1),
                                                                                     (v65 + __PAIR128__(c3s, c2s)) >> 64))
                 + (_QWORD)v3;
  c2t = v65 + c2s;
  v67 = *b * (unsigned __int128)a[7];
  *(_QWORD *)&v3 = (__CFADD__(__CFADD__((_QWORD)v67, c2t), v66) | (unsigned __int8)__CFADD__(
                                                                                     *((_QWORD *)&v67 + 1),
                                                                                     (v67 + __PAIR128__(v66, c2t)) >> 64))
                 + (_QWORD)v3;
  c3t = (v67 + __PAIR128__(v66, c2t)) >> 64;
  r[7] = v67 + c2t;
  v68 = b[1] * (unsigned __int128)a[7];
  v69 = (v68 + __PAIR128__(v3, c3t)) >> 64;
  *(_QWORD *)&v3 = __CFADD__(__CFADD__((_QWORD)v68, c3t), (_QWORD)v3) | (unsigned __int8)__CFADD__(
                                                                                           *((_QWORD *)&v68 + 1),
                                                                                           v69);
  c3u = v68 + c3t;
  c1p = v69;
  v70 = b[2] * (unsigned __int128)a[6];
  v71 = (v70 + __PAIR128__(v69, c3u)) >> 64;
  *(_QWORD *)&v3 = (__CFADD__(__CFADD__((_QWORD)v70, c3u), c1p) | (unsigned __int8)__CFADD__(
                                                                                     *((_QWORD *)&v70 + 1),
                                                                                     (v70 + __PAIR128__(c1p, c3u)) >> 64))
                 + (_QWORD)v3;
  c3v = v70 + c3u;
  c1q = v71;
  v72 = b[3] * (unsigned __int128)a[5];
  v73 = (v72 + __PAIR128__(v71, c3v)) >> 64;
  *(_QWORD *)&v3 = (__CFADD__(__CFADD__((_QWORD)v72, c3v), c1q) | (unsigned __int8)__CFADD__(
                                                                                     *((_QWORD *)&v72 + 1),
                                                                                     (v72 + __PAIR128__(c1q, c3v)) >> 64))
                 + (_QWORD)v3;
  c3w = v72 + c3v;
  c1r = v73;
  v74 = b[4] * (unsigned __int128)a[4];
  v75 = (v74 + __PAIR128__(v73, c3w)) >> 64;
  *(_QWORD *)&v3 = (__CFADD__(__CFADD__((_QWORD)v74, c3w), c1r) | (unsigned __int8)__CFADD__(
                                                                                     *((_QWORD *)&v74 + 1),
                                                                                     (v74 + __PAIR128__(c1r, c3w)) >> 64))
                 + (_QWORD)v3;
  c3x = v74 + c3w;
  c1s = v75;
  v76 = b[5] * (unsigned __int128)a[3];
  v77 = (v76 + __PAIR128__(v75, c3x)) >> 64;
  *(_QWORD *)&v3 = (__CFADD__(__CFADD__((_QWORD)v76, c3x), c1s) | (unsigned __int8)__CFADD__(
                                                                                     *((_QWORD *)&v76 + 1),
                                                                                     (v76 + __PAIR128__(c1s, c3x)) >> 64))
                 + (_QWORD)v3;
  c3y = v76 + c3x;
  c1t = v77;
  v78 = b[6] * (unsigned __int128)a[2];
  v79 = (v78 + __PAIR128__(v77, c3y)) >> 64;
  *(_QWORD *)&v3 = (__CFADD__(__CFADD__((_QWORD)v78, c3y), c1t) | (unsigned __int8)__CFADD__(
                                                                                     *((_QWORD *)&v78 + 1),
                                                                                     (v78 + __PAIR128__(c1t, c3y)) >> 64))
                 + (_QWORD)v3;
  c3z = v78 + c3y;
  v80 = b[7] * (unsigned __int128)a[1];
  *(_QWORD *)&v3 = (__CFADD__(__CFADD__((_QWORD)v80, c3z), v79) | (unsigned __int8)__CFADD__(
                                                                                     *((_QWORD *)&v80 + 1),
                                                                                     (v80 + __PAIR128__(v79, c3z)) >> 64))
                 + (_QWORD)v3;
  c1u = (v80 + __PAIR128__(v79, c3z)) >> 64;
  r[8] = v80 + c3z;
  v81 = b[7] * (unsigned __int128)a[2];
  v82 = (v81 + __PAIR128__(v3, c1u)) >> 64;
  *(_QWORD *)&v3 = __CFADD__(__CFADD__((_QWORD)v81, c1u), (_QWORD)v3) | (unsigned __int8)__CFADD__(
                                                                                           *((_QWORD *)&v81 + 1),
                                                                                           v82);
  c1v = v81 + c1u;
  c2u = v82;
  v83 = b[6] * (unsigned __int128)a[3];
  v84 = (v83 + __PAIR128__(v82, c1v)) >> 64;
  *(_QWORD *)&v3 = (__CFADD__(__CFADD__((_QWORD)v83, c1v), c2u) | (unsigned __int8)__CFADD__(
                                                                                     *((_QWORD *)&v83 + 1),
                                                                                     (v83 + __PAIR128__(c2u, c1v)) >> 64))
                 + (_QWORD)v3;
  c1w = v83 + c1v;
  c2v = v84;
  v85 = b[5] * (unsigned __int128)a[4];
  v86 = (v85 + __PAIR128__(v84, c1w)) >> 64;
  *(_QWORD *)&v3 = (__CFADD__(__CFADD__((_QWORD)v85, c1w), c2v) | (unsigned __int8)__CFADD__(
                                                                                     *((_QWORD *)&v85 + 1),
                                                                                     (v85 + __PAIR128__(c2v, c1w)) >> 64))
                 + (_QWORD)v3;
  c1x = v85 + c1w;
  c2w = v86;
  v87 = b[4] * (unsigned __int128)a[5];
  v88 = (v87 + __PAIR128__(v86, c1x)) >> 64;
  *(_QWORD *)&v3 = (__CFADD__(__CFADD__((_QWORD)v87, c1x), c2w) | (unsigned __int8)__CFADD__(
                                                                                     *((_QWORD *)&v87 + 1),
                                                                                     (v87 + __PAIR128__(c2w, c1x)) >> 64))
                 + (_QWORD)v3;
  c1y = v87 + c1x;
  c2x = v88;
  v89 = b[3] * (unsigned __int128)a[6];
  v90 = (v89 + __PAIR128__(v88, c1y)) >> 64;
  *(_QWORD *)&v3 = (__CFADD__(__CFADD__((_QWORD)v89, c1y), c2x) | (unsigned __int8)__CFADD__(
                                                                                     *((_QWORD *)&v89 + 1),
                                                                                     (v89 + __PAIR128__(c2x, c1y)) >> 64))
                 + (_QWORD)v3;
  c1z = v89 + c1y;
  v91 = b[2] * (unsigned __int128)a[7];
  *(_QWORD *)&v3 = (__CFADD__(__CFADD__((_QWORD)v91, c1z), v90) | (unsigned __int8)__CFADD__(
                                                                                     *((_QWORD *)&v91 + 1),
                                                                                     (v91 + __PAIR128__(v90, c1z)) >> 64))
                 + (_QWORD)v3;
  c2y = (v91 + __PAIR128__(v90, c1z)) >> 64;
  r[9] = v91 + c1z;
  v92 = b[3] * (unsigned __int128)a[7];
  v93 = (v92 + __PAIR128__(v3, c2y)) >> 64;
  *(_QWORD *)&v3 = __CFADD__(__CFADD__((_QWORD)v92, c2y), (_QWORD)v3) | (unsigned __int8)__CFADD__(
                                                                                           *((_QWORD *)&v92 + 1),
                                                                                           v93);
  c2z = v92 + c2y;
  c3ba = v93;
  v94 = b[4] * (unsigned __int128)a[6];
  v95 = (v94 + __PAIR128__(v93, c2z)) >> 64;
  *(_QWORD *)&v3 = (__CFADD__(__CFADD__((_QWORD)v94, c2z), c3ba) | (unsigned __int8)__CFADD__(
                                                                                      *((_QWORD *)&v94 + 1),
                                                                                      (v94 + __PAIR128__(c3ba, c2z)) >> 64))
                 + (_QWORD)v3;
  c2ba = v94 + c2z;
  c3bb = v95;
  v96 = b[5] * (unsigned __int128)a[5];
  v97 = (v96 + __PAIR128__(v95, c2ba)) >> 64;
  *(_QWORD *)&v3 = (__CFADD__(__CFADD__((_QWORD)v96, c2ba), c3bb) | (unsigned __int8)__CFADD__(
                                                                                       *((_QWORD *)&v96 + 1),
                                                                                       (v96 + __PAIR128__(c3bb, c2ba)) >> 64))
                 + (_QWORD)v3;
  c2bb = v96 + c2ba;
  c3bc = v97;
  v98 = b[6] * (unsigned __int128)a[4];
  v99 = (v98 + __PAIR128__(v97, c2bb)) >> 64;
  *(_QWORD *)&v3 = (__CFADD__(__CFADD__((_QWORD)v98, c2bb), c3bc) | (unsigned __int8)__CFADD__(
                                                                                       *((_QWORD *)&v98 + 1),
                                                                                       (v98 + __PAIR128__(c3bc, c2bb)) >> 64))
                 + (_QWORD)v3;
  c2bc = v98 + c2bb;
  v100 = b[7] * (unsigned __int128)a[3];
  *(_QWORD *)&v3 = (__CFADD__(__CFADD__((_QWORD)v100, c2bc), v99) | (unsigned __int8)__CFADD__(
                                                                                       *((_QWORD *)&v100 + 1),
                                                                                       (v100 + __PAIR128__(v99, c2bc)) >> 64))
                 + (_QWORD)v3;
  c3bd = (v100 + __PAIR128__(v99, c2bc)) >> 64;
  r[10] = v100 + c2bc;
  v101 = b[7] * (unsigned __int128)a[4];
  v102 = (v101 + __PAIR128__(v3, c3bd)) >> 64;
  *(_QWORD *)&v3 = __CFADD__(__CFADD__((_QWORD)v101, c3bd), (_QWORD)v3) | (unsigned __int8)__CFADD__(
                                                                                             *((_QWORD *)&v101 + 1),
                                                                                             v102);
  c3be = v101 + c3bd;
  c1ba = v102;
  v103 = b[6] * (unsigned __int128)a[5];
  v104 = (v103 + __PAIR128__(v102, c3be)) >> 64;
  *(_QWORD *)&v3 = (__CFADD__(__CFADD__((_QWORD)v103, c3be), c1ba) | (unsigned __int8)__CFADD__(
                                                                                        *((_QWORD *)&v103 + 1),
                                                                                        (v103 + __PAIR128__(c1ba, c3be)) >> 64))
                 + (_QWORD)v3;
  c3bf = v103 + c3be;
  c1bb = v104;
  v105 = b[5] * (unsigned __int128)a[6];
  v106 = (v105 + __PAIR128__(v104, c3bf)) >> 64;
  *(_QWORD *)&v3 = (__CFADD__(__CFADD__((_QWORD)v105, c3bf), c1bb) | (unsigned __int8)__CFADD__(
                                                                                        *((_QWORD *)&v105 + 1),
                                                                                        (v105 + __PAIR128__(c1bb, c3bf)) >> 64))
                 + (_QWORD)v3;
  c3bg = v105 + c3bf;
  v107 = b[4] * (unsigned __int128)a[7];
  *(_QWORD *)&v3 = (__CFADD__(__CFADD__((_QWORD)v107, c3bg), v106) | (unsigned __int8)__CFADD__(
                                                                                        *((_QWORD *)&v107 + 1),
                                                                                        (v107 + __PAIR128__(v106, c3bg)) >> 64))
                 + (_QWORD)v3;
  c1bc = (v107 + __PAIR128__(v106, c3bg)) >> 64;
  r[11] = v107 + c3bg;
  v108 = b[5] * (unsigned __int128)a[7];
  v109 = (v108 + __PAIR128__(v3, c1bc)) >> 64;
  *(_QWORD *)&v3 = __CFADD__(__CFADD__((_QWORD)v108, c1bc), (_QWORD)v3) | (unsigned __int8)__CFADD__(
                                                                                             *((_QWORD *)&v108 + 1),
                                                                                             v109);
  c1bd = v108 + c1bc;
  c2bd = v109;
  v110 = b[6] * (unsigned __int128)a[6];
  v111 = (v110 + __PAIR128__(v109, c1bd)) >> 64;
  *(_QWORD *)&v3 = (__CFADD__(__CFADD__((_QWORD)v110, c1bd), c2bd) | (unsigned __int8)__CFADD__(
                                                                                        *((_QWORD *)&v110 + 1),
                                                                                        (v110 + __PAIR128__(c2bd, c1bd)) >> 64))
                 + (_QWORD)v3;
  c1be = v110 + c1bd;
  v112 = b[7] * (unsigned __int128)a[5];
  *(_QWORD *)&v3 = (__CFADD__(__CFADD__((_QWORD)v112, c1be), v111) | (unsigned __int8)__CFADD__(
                                                                                        *((_QWORD *)&v112 + 1),
                                                                                        (v112 + __PAIR128__(v111, c1be)) >> 64))
                 + (_QWORD)v3;
  c2be = (v112 + __PAIR128__(v111, c1be)) >> 64;
  r[12] = v112 + c1be;
  v113 = b[7] * (unsigned __int128)a[6];
  v114 = (v113 + __PAIR128__(v3, c2be)) >> 64;
  *(_QWORD *)&v3 = __CFADD__(__CFADD__((_QWORD)v113, c2be), (_QWORD)v3) | (unsigned __int8)__CFADD__(
                                                                                             *((_QWORD *)&v113 + 1),
                                                                                             v114);
  c2bf = v113 + c2be;
  v115 = b[6] * (unsigned __int128)a[7];
  r[13] = v115 + c2bf;
  *((_OWORD *)r + 7) = b[7] * (unsigned __int128)a[7]
                     + __PAIR128__(
                         (__CFADD__(__CFADD__((_QWORD)v115, c2bf), v114) | (unsigned __int8)__CFADD__(
                                                                                              *((_QWORD *)&v115 + 1),
                                                                                              (v115
                                                                                             + __PAIR128__(v114, c2bf)) >> 64))
                       + (unsigned __int64)v3,
                         (v115 + __PAIR128__(v114, c2bf)) >> 64);
}