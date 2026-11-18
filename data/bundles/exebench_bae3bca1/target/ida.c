void __cdecl bn_sqr_comba8(unsigned __int64 *r, unsigned __int64 *a)
{
  unsigned __int128 v2; // kr00_16
  unsigned __int128 v3; // kr10_16
  __int128 v4; // rax
  unsigned __int128 v5; // rax
  unsigned __int128 v6; // kr40_16
  unsigned __int128 v7; // rax
  unsigned __int128 v8; // kr70_16
  unsigned __int128 v9; // kr80_16
  unsigned __int128 v10; // kr90_16
  unsigned __int128 v11; // krC0_16
  unsigned __int128 v12; // kr20_16
  unsigned __int128 v13; // krD0_16
  unsigned __int128 v14; // kr100_16
  unsigned __int128 v15; // kr160_16
  unsigned __int128 v16; // kr170_16
  unsigned __int128 v17; // rax
  unsigned __int128 v18; // kr1A0_16
  unsigned __int128 v19; // rax
  unsigned __int128 v20; // kr1B0_16
  unsigned __int128 v21; // rax
  unsigned __int128 v22; // kr1E0_16
  unsigned __int128 v23; // rax
  unsigned __int128 v24; // kr1F0_16
  unsigned __int128 v25; // kr220_16
  unsigned __int128 v26; // kr230_16
  unsigned __int128 v27; // kr260_16
  unsigned __int128 v28; // kr270_16
  unsigned __int128 v29; // kr2A0_16
  unsigned __int128 v30; // kr2D0_16
  unsigned __int128 v31; // kr2E0_16
  unsigned __int128 v32; // kr310_16
  unsigned __int128 v33; // kr340_16
  unsigned __int128 v34; // kr370_16
  unsigned __int128 v35; // rax
  unsigned __int128 v36; // kr3A0_16
  unsigned __int128 v37; // rax
  unsigned __int128 v38; // kr3B0_16
  unsigned __int128 v39; // rax
  unsigned __int128 v40; // kr3E0_16
  unsigned __int128 v41; // rax
  unsigned __int128 v42; // kr3F0_16
  unsigned __int128 v43; // rax
  unsigned __int128 v44; // kr420_16
  unsigned __int128 v45; // rax
  unsigned __int128 v46; // kr430_16
  unsigned __int128 v47; // rax
  unsigned __int128 v48; // kr460_16
  unsigned __int128 v49; // rax
  unsigned __int128 v50; // kr490_16
  unsigned __int128 v51; // kr4A0_16
  unsigned __int128 v52; // kr4B0_16
  unsigned __int128 v53; // kr4E0_16
  unsigned __int128 v54; // kr30_16
  unsigned __int128 v55; // kr4F0_16
  unsigned __int128 v56; // kr520_16
  unsigned __int128 v57; // kr530_16
  unsigned __int128 v58; // kr560_16
  unsigned __int128 v59; // kr570_16
  unsigned __int128 v60; // kr5A0_16
  unsigned __int128 v61; // kr5D0_16
  unsigned __int128 v62; // kr630_16
  unsigned __int128 v63; // kr640_16
  unsigned __int128 v64; // rax
  unsigned __int128 v65; // kr670_16
  unsigned __int128 v66; // rax
  unsigned __int128 v67; // kr680_16
  unsigned __int128 v68; // rax
  unsigned __int128 v69; // kr6B0_16
  unsigned __int128 v70; // rax
  unsigned __int128 v71; // kr6C0_16
  unsigned __int128 v72; // kr6F0_16
  unsigned __int128 v73; // kr700_16
  unsigned __int128 v74; // kr730_16
  unsigned __int128 v75; // kr760_16
  unsigned __int128 v76; // kr770_16
  unsigned __int128 v77; // kr7A0_16
  unsigned __int128 v78; // kr7B0_16
  unsigned __int128 v79; // rax
  unsigned __int128 v80; // kr7E0_16
  unsigned __int64 c3; // [rsp+0h] [rbp-48h]
  unsigned __int64 c3a; // [rsp+0h] [rbp-48h]
  unsigned __int64 c3b; // [rsp+0h] [rbp-48h]
  unsigned __int64 c3c; // [rsp+0h] [rbp-48h]
  unsigned __int64 c3d; // [rsp+0h] [rbp-48h]
  unsigned __int64 c3e; // [rsp+0h] [rbp-48h]
  unsigned __int64 c3f; // [rsp+0h] [rbp-48h]
  unsigned __int64 c3g; // [rsp+0h] [rbp-48h]
  unsigned __int64 c3h; // [rsp+0h] [rbp-48h]
  unsigned __int64 c3i; // [rsp+0h] [rbp-48h]
  unsigned __int64 c3j; // [rsp+0h] [rbp-48h]
  unsigned __int64 c3k; // [rsp+0h] [rbp-48h]
  unsigned __int64 c3l; // [rsp+0h] [rbp-48h]
  unsigned __int64 c3m; // [rsp+0h] [rbp-48h]
  unsigned __int64 c3n; // [rsp+0h] [rbp-48h]
  unsigned __int64 c3o; // [rsp+0h] [rbp-48h]
  unsigned __int64 c3p; // [rsp+0h] [rbp-48h]
  unsigned __int64 c3q; // [rsp+0h] [rbp-48h]
  unsigned __int64 c3r; // [rsp+0h] [rbp-48h]
  unsigned __int64 c3s; // [rsp+0h] [rbp-48h]
  unsigned __int64 c2; // [rsp+8h] [rbp-40h]
  unsigned __int64 c2a; // [rsp+8h] [rbp-40h]
  unsigned __int64 c2b; // [rsp+8h] [rbp-40h]
  unsigned __int64 c2c; // [rsp+8h] [rbp-40h]
  unsigned __int64 c2d; // [rsp+8h] [rbp-40h]
  unsigned __int64 c2e; // [rsp+8h] [rbp-40h]
  unsigned __int64 c2f; // [rsp+8h] [rbp-40h]
  unsigned __int64 c2g; // [rsp+8h] [rbp-40h]
  unsigned __int64 c2h; // [rsp+8h] [rbp-40h]
  unsigned __int64 c2i; // [rsp+8h] [rbp-40h]
  unsigned __int64 c2j; // [rsp+8h] [rbp-40h]
  unsigned __int64 c2k; // [rsp+8h] [rbp-40h]
  unsigned __int64 c2l; // [rsp+8h] [rbp-40h]
  unsigned __int64 c2m; // [rsp+8h] [rbp-40h]
  unsigned __int64 c2n; // [rsp+8h] [rbp-40h]
  unsigned __int64 c2o; // [rsp+8h] [rbp-40h]
  unsigned __int64 c1; // [rsp+10h] [rbp-38h]
  __int128 c1a; // [rsp+10h] [rbp-38h]
  __int128 c1b; // [rsp+10h] [rbp-38h]
  __int128 c1c; // [rsp+10h] [rbp-38h]
  __int128 c1d; // [rsp+10h] [rbp-38h]
  __int128 c1e; // [rsp+10h] [rbp-38h]
  __int128 c1f; // [rsp+10h] [rbp-38h]
  __int128 c1g; // [rsp+10h] [rbp-38h]
  __int128 c1h; // [rsp+10h] [rbp-38h]
  __int128 c1i; // [rsp+10h] [rbp-38h]
  __int128 c1j; // [rsp+10h] [rbp-38h]
  __int128 c1k; // [rsp+10h] [rbp-38h]
  __int128 c1l; // [rsp+10h] [rbp-38h]

  v2 = *a * (unsigned __int128)*a;
  c2 = (v2 + 0) >> 64;
  c3 = (c2 + (unsigned __int128)0LL) >> 64;
  *r = v2;
  v3 = *a * (unsigned __int128)a[1];
  *(_QWORD *)&v4 = *a * a[1];
  *((_QWORD *)&v4 + 1) = 2LL * *((_QWORD *)&v3 + 1);
  v5 = v4 + (unsigned __int64)v3 + c2;
  v6 = v5;
  v7 = __PAIR128__(*((unsigned __int64 *)&v5 + 1), (2 * (unsigned __int128)*((unsigned __int64 *)&v3 + 1)) >> 64);
  *(_QWORD *)&v7 = __CFADD__(*((_QWORD *)&v7 + 1), c3) + (_QWORD)v7;
  r[1] = v6;
  v8 = a[1] * (unsigned __int128)a[1] + *((_QWORD *)&v7 + 1) + c3;
  v9 = *((unsigned __int64 *)&v8 + 1) + (unsigned __int128)(unsigned __int64)v7;
  c1 = *((_QWORD *)&v8 + 1) + v7;
  v10 = *a * (unsigned __int128)a[2];
  *(_QWORD *)&v7 = *a * a[2];
  *((_QWORD *)&v7 + 1) = 2LL * *((_QWORD *)&v10 + 1);
  v11 = v7 + (unsigned __int64)v10 + (unsigned __int64)v8;
  v12 = __PAIR128__(__CFADD__(*((_QWORD *)&v10 + 1), *((_QWORD *)&v10 + 1)), *((unsigned __int64 *)&v11 + 1))
      + __PAIR128__(*((unsigned __int64 *)&v9 + 1), c1);
  *(_QWORD *)&v7 = v12 >> 64;
  *(_QWORD *)&c1a = v12;
  c2a = v7;
  r[2] = v11;
  v13 = *a * (unsigned __int128)a[3];
  *(_QWORD *)&v7 = *a * a[3];
  *((_QWORD *)&v7 + 1) = 2LL * *((_QWORD *)&v13 + 1);
  *((_QWORD *)&c1a + 1) = (v7 + (unsigned __int64)v13) >> 64;
  c1b = c1a + (unsigned __int64)(v7 + v13);
  *(_QWORD *)&v7 = __CFADD__(*((_QWORD *)&c1b + 1), c2a)
                 + ((2 * (unsigned __int128)*((unsigned __int64 *)&v13 + 1)) >> 64);
  c2b = *((_QWORD *)&c1b + 1) + c2a;
  v14 = a[1] * (unsigned __int128)a[2];
  c3a = __CFADD__(*((_QWORD *)&v14 + 1), *((_QWORD *)&v14 + 1)) + (_QWORD)v7;
  *(_QWORD *)&v7 = a[1] * a[2];
  *((_QWORD *)&v7 + 1) = 2LL * *((_QWORD *)&v14 + 1);
  *((_QWORD *)&c1b + 1) = (v7 + (unsigned __int64)v14) >> 64;
  c1c = c1b + (unsigned __int64)(v7 + v14);
  c3b = __CFADD__(*((_QWORD *)&c1c + 1), c2b) + c3a;
  r[3] = c1c;
  v15 = ((a[2] * (unsigned __int128)a[2] + *((_QWORD *)&c1c + 1) + c2b) >> 64) + c3b;
  c3c = ((a[2] * (unsigned __int128)a[2] + *((_QWORD *)&c1c + 1) + c2b) >> 64) + c3b;
  v16 = a[1] * (unsigned __int128)a[3];
  *(_QWORD *)&v7 = a[1] * a[3];
  *((_QWORD *)&v7 + 1) = 2LL * *((_QWORD *)&v16 + 1);
  v17 = v7 + (unsigned __int64)v16 + a[2] * a[2] + *((_QWORD *)&c1c + 1) + c2b;
  v18 = v17;
  v19 = __PAIR128__(
          *((unsigned __int64 *)&v17 + 1),
          (unsigned __int64)__CFADD__(*((_QWORD *)&v16 + 1), *((_QWORD *)&v16 + 1)) + *((_QWORD *)&v15 + 1));
  *(_QWORD *)&v19 = __CFADD__(*((_QWORD *)&v19 + 1), c3c) + (_QWORD)v19;
  c3d = *((_QWORD *)&v19 + 1) + c3c;
  v20 = *a * (unsigned __int128)a[4];
  *(_QWORD *)&c1c = __CFADD__(*((_QWORD *)&v20 + 1), *((_QWORD *)&v20 + 1)) + (_QWORD)v19;
  *(_QWORD *)&v19 = *a * a[4];
  *((_QWORD *)&v19 + 1) = 2LL * *((_QWORD *)&v20 + 1);
  v21 = v19 + (unsigned __int64)v20 + (unsigned __int64)v18;
  v22 = v21;
  v23 = __PAIR128__(*((unsigned __int64 *)&v21 + 1), c1c);
  *(_QWORD *)&v23 = __CFADD__(*((_QWORD *)&v23 + 1), c3d) + (_QWORD)v23;
  c3e = *((_QWORD *)&v23 + 1) + c3d;
  *(_QWORD *)&c1c = v23;
  r[4] = v22;
  v24 = *a * (unsigned __int128)a[5];
  *(_QWORD *)&v23 = *a * a[5];
  *((_QWORD *)&v23 + 1) = 2LL * *((_QWORD *)&v24 + 1);
  v25 = v23 + (unsigned __int64)v24 + c3e;
  *(_QWORD *)&v23 = __CFADD__(*((_QWORD *)&v25 + 1), (_QWORD)c1c)
                  + ((2 * (unsigned __int128)*((unsigned __int64 *)&v24 + 1)) >> 64);
  *(_QWORD *)&c1c = *((_QWORD *)&v25 + 1) + c1c;
  v26 = a[1] * (unsigned __int128)a[4];
  c2c = __CFADD__(*((_QWORD *)&v26 + 1), *((_QWORD *)&v26 + 1)) + (_QWORD)v23;
  *(_QWORD *)&v23 = a[1] * a[4];
  *((_QWORD *)&v23 + 1) = 2LL * *((_QWORD *)&v26 + 1);
  v27 = v23 + (unsigned __int64)v26 + (unsigned __int64)v25;
  *(_QWORD *)&v23 = __CFADD__(*((_QWORD *)&v27 + 1), (_QWORD)c1c) + c2c;
  *(_QWORD *)&c1c = *((_QWORD *)&v27 + 1) + c1c;
  v28 = a[2] * (unsigned __int128)a[3];
  c2d = __CFADD__(*((_QWORD *)&v28 + 1), *((_QWORD *)&v28 + 1)) + (_QWORD)v23;
  *(_QWORD *)&v23 = a[2] * a[3];
  *((_QWORD *)&v23 + 1) = 2LL * *((_QWORD *)&v28 + 1);
  v29 = v23 + (unsigned __int64)v28 + (unsigned __int64)v27;
  *(_QWORD *)&v23 = __CFADD__(*((_QWORD *)&v29 + 1), (_QWORD)c1c) + c2d;
  *(_QWORD *)&c1c = *((_QWORD *)&v29 + 1) + c1c;
  r[5] = v29;
  *((_QWORD *)&c1c + 1) = (a[3] * (unsigned __int128)a[3]) >> 64;
  c1d = c1c + a[3] * a[3];
  v30 = *((unsigned __int64 *)&c1d + 1) + (unsigned __int128)(unsigned __int64)v23;
  c2e = *((_QWORD *)&c1d + 1) + v23;
  v31 = a[2] * (unsigned __int128)a[4];
  *(_QWORD *)&v23 = a[2] * a[4];
  *((_QWORD *)&v23 + 1) = 2LL * *((_QWORD *)&v31 + 1);
  *((_QWORD *)&c1d + 1) = (v23 + (unsigned __int64)v31) >> 64;
  c1e = c1d + (unsigned __int64)(v23 + v31);
  *(_QWORD *)&v23 = __CFADD__(*((_QWORD *)&c1e + 1), c2e)
                  + __CFADD__(*((_QWORD *)&v31 + 1), *((_QWORD *)&v31 + 1))
                  + *((_QWORD *)&v30 + 1);
  c2f = *((_QWORD *)&c1e + 1) + c2e;
  v32 = a[1] * (unsigned __int128)a[5];
  c3f = __CFADD__(*((_QWORD *)&v32 + 1), *((_QWORD *)&v32 + 1)) + (_QWORD)v23;
  *(_QWORD *)&v23 = a[1] * a[5];
  *((_QWORD *)&v23 + 1) = 2LL * *((_QWORD *)&v32 + 1);
  *((_QWORD *)&c1e + 1) = (v23 + (unsigned __int64)v32) >> 64;
  c1f = c1e + (unsigned __int64)(v23 + v32);
  *(_QWORD *)&v23 = __CFADD__(*((_QWORD *)&c1f + 1), c2f) + c3f;
  c2g = *((_QWORD *)&c1f + 1) + c2f;
  v33 = *a * (unsigned __int128)a[6];
  c3g = __CFADD__(*((_QWORD *)&v33 + 1), *((_QWORD *)&v33 + 1)) + (_QWORD)v23;
  *(_QWORD *)&v23 = *a * a[6];
  *((_QWORD *)&v23 + 1) = 2LL * *((_QWORD *)&v33 + 1);
  *((_QWORD *)&c1f + 1) = (v23 + (unsigned __int64)v33) >> 64;
  c1g = c1f + (unsigned __int64)(v23 + v33);
  c3h = __CFADD__(*((_QWORD *)&c1g + 1), c2g) + c3g;
  r[6] = c1g;
  v34 = *a * (unsigned __int128)a[7];
  *(_QWORD *)&v23 = *a * a[7];
  *((_QWORD *)&v23 + 1) = 2LL * *((_QWORD *)&v34 + 1);
  v35 = v23 + (unsigned __int64)v34 + *((_QWORD *)&c1g + 1) + c2g;
  v36 = v35;
  v37 = __PAIR128__(*((unsigned __int64 *)&v35 + 1), (2 * (unsigned __int128)*((unsigned __int64 *)&v34 + 1)) >> 64);
  *(_QWORD *)&v37 = __CFADD__(*((_QWORD *)&v37 + 1), c3h) + (_QWORD)v37;
  c3i = *((_QWORD *)&v37 + 1) + c3h;
  v38 = a[1] * (unsigned __int128)a[6];
  *(_QWORD *)&c1g = __CFADD__(*((_QWORD *)&v38 + 1), *((_QWORD *)&v38 + 1)) + (_QWORD)v37;
  *(_QWORD *)&v37 = a[1] * a[6];
  *((_QWORD *)&v37 + 1) = 2LL * *((_QWORD *)&v38 + 1);
  v39 = v37 + (unsigned __int64)v38 + (unsigned __int64)v36;
  v40 = v39;
  v41 = __PAIR128__(*((unsigned __int64 *)&v39 + 1), c1g);
  *(_QWORD *)&v41 = __CFADD__(*((_QWORD *)&v41 + 1), c3i) + (_QWORD)v41;
  c3j = *((_QWORD *)&v41 + 1) + c3i;
  v42 = a[2] * (unsigned __int128)a[5];
  *(_QWORD *)&c1g = __CFADD__(*((_QWORD *)&v42 + 1), *((_QWORD *)&v42 + 1)) + (_QWORD)v41;
  *(_QWORD *)&v41 = a[2] * a[5];
  *((_QWORD *)&v41 + 1) = 2LL * *((_QWORD *)&v42 + 1);
  v43 = v41 + (unsigned __int64)v42 + (unsigned __int64)v40;
  v44 = v43;
  v45 = __PAIR128__(*((unsigned __int64 *)&v43 + 1), c1g);
  *(_QWORD *)&v45 = __CFADD__(*((_QWORD *)&v45 + 1), c3j) + (_QWORD)v45;
  c3k = *((_QWORD *)&v45 + 1) + c3j;
  v46 = a[3] * (unsigned __int128)a[4];
  *(_QWORD *)&c1g = __CFADD__(*((_QWORD *)&v46 + 1), *((_QWORD *)&v46 + 1)) + (_QWORD)v45;
  *(_QWORD *)&v45 = a[3] * a[4];
  *((_QWORD *)&v45 + 1) = 2LL * *((_QWORD *)&v46 + 1);
  v47 = v45 + (unsigned __int64)v46 + (unsigned __int64)v44;
  v48 = v47;
  v49 = __PAIR128__(*((unsigned __int64 *)&v47 + 1), c1g);
  *(_QWORD *)&v49 = __CFADD__(*((_QWORD *)&v49 + 1), c3k) + (_QWORD)v49;
  r[7] = v48;
  v50 = a[4] * (unsigned __int128)a[4] + *((_QWORD *)&v49 + 1) + c3k;
  v51 = *((unsigned __int64 *)&v50 + 1) + (unsigned __int128)(unsigned __int64)v49;
  *(_QWORD *)&c1g = *((_QWORD *)&v50 + 1) + v49;
  v52 = a[3] * (unsigned __int128)a[5];
  *(_QWORD *)&v49 = a[3] * a[5];
  *((_QWORD *)&v49 + 1) = 2LL * *((_QWORD *)&v52 + 1);
  v53 = v49 + (unsigned __int64)v52 + (unsigned __int64)v50;
  v54 = __PAIR128__(__CFADD__(*((_QWORD *)&v52 + 1), *((_QWORD *)&v52 + 1)), *((unsigned __int64 *)&v53 + 1))
      + __PAIR128__(*((unsigned __int64 *)&v51 + 1), c1g);
  *(_QWORD *)&v49 = v54 >> 64;
  *(_QWORD *)&c1g = v54;
  v55 = a[2] * (unsigned __int128)a[6];
  c2h = __CFADD__(*((_QWORD *)&v55 + 1), *((_QWORD *)&v55 + 1)) + (_QWORD)v49;
  *(_QWORD *)&v49 = a[2] * a[6];
  *((_QWORD *)&v49 + 1) = 2LL * *((_QWORD *)&v55 + 1);
  v56 = v49 + (unsigned __int64)v55 + (unsigned __int64)v53;
  *(_QWORD *)&v49 = __CFADD__(*((_QWORD *)&v56 + 1), (_QWORD)c1g) + c2h;
  *(_QWORD *)&c1g = *((_QWORD *)&v56 + 1) + c1g;
  v57 = a[1] * (unsigned __int128)a[7];
  c2i = __CFADD__(*((_QWORD *)&v57 + 1), *((_QWORD *)&v57 + 1)) + (_QWORD)v49;
  *(_QWORD *)&v49 = a[1] * a[7];
  *((_QWORD *)&v49 + 1) = 2LL * *((_QWORD *)&v57 + 1);
  v58 = v49 + (unsigned __int64)v57 + (unsigned __int64)v56;
  *(_QWORD *)&v49 = __CFADD__(*((_QWORD *)&v58 + 1), (_QWORD)c1g) + c2i;
  *(_QWORD *)&c1g = *((_QWORD *)&v58 + 1) + c1g;
  c2j = v49;
  r[8] = v58;
  v59 = a[2] * (unsigned __int128)a[7];
  *(_QWORD *)&v49 = a[2] * a[7];
  *((_QWORD *)&v49 + 1) = 2LL * *((_QWORD *)&v59 + 1);
  *((_QWORD *)&c1g + 1) = (v49 + (unsigned __int64)v59) >> 64;
  c1h = c1g + (unsigned __int64)(v49 + v59);
  *(_QWORD *)&v49 = __CFADD__(*((_QWORD *)&c1h + 1), c2j)
                  + ((2 * (unsigned __int128)*((unsigned __int64 *)&v59 + 1)) >> 64);
  c2k = *((_QWORD *)&c1h + 1) + c2j;
  v60 = a[3] * (unsigned __int128)a[6];
  c3l = __CFADD__(*((_QWORD *)&v60 + 1), *((_QWORD *)&v60 + 1)) + (_QWORD)v49;
  *(_QWORD *)&v49 = a[3] * a[6];
  *((_QWORD *)&v49 + 1) = 2LL * *((_QWORD *)&v60 + 1);
  *((_QWORD *)&c1h + 1) = (v49 + (unsigned __int64)v60) >> 64;
  c1i = c1h + (unsigned __int64)(v49 + v60);
  *(_QWORD *)&v49 = __CFADD__(*((_QWORD *)&c1i + 1), c2k) + c3l;
  c2l = *((_QWORD *)&c1i + 1) + c2k;
  v61 = a[4] * (unsigned __int128)a[5];
  c3m = __CFADD__(*((_QWORD *)&v61 + 1), *((_QWORD *)&v61 + 1)) + (_QWORD)v49;
  *(_QWORD *)&v49 = a[4] * a[5];
  *((_QWORD *)&v49 + 1) = 2LL * *((_QWORD *)&v61 + 1);
  *((_QWORD *)&c1i + 1) = (v49 + (unsigned __int64)v61) >> 64;
  c1j = c1i + (unsigned __int64)(v49 + v61);
  c3n = __CFADD__(*((_QWORD *)&c1j + 1), c2l) + c3m;
  r[9] = c1j;
  v62 = ((a[5] * (unsigned __int128)a[5] + *((_QWORD *)&c1j + 1) + c2l) >> 64) + c3n;
  c3o = ((a[5] * (unsigned __int128)a[5] + *((_QWORD *)&c1j + 1) + c2l) >> 64) + c3n;
  v63 = a[4] * (unsigned __int128)a[6];
  *(_QWORD *)&v49 = a[4] * a[6];
  *((_QWORD *)&v49 + 1) = 2LL * *((_QWORD *)&v63 + 1);
  v64 = v49 + (unsigned __int64)v63 + a[5] * a[5] + *((_QWORD *)&c1j + 1) + c2l;
  v65 = v64;
  v66 = __PAIR128__(
          *((unsigned __int64 *)&v64 + 1),
          (unsigned __int64)__CFADD__(*((_QWORD *)&v63 + 1), *((_QWORD *)&v63 + 1)) + *((_QWORD *)&v62 + 1));
  *(_QWORD *)&v66 = __CFADD__(*((_QWORD *)&v66 + 1), c3o) + (_QWORD)v66;
  c3p = *((_QWORD *)&v66 + 1) + c3o;
  v67 = a[3] * (unsigned __int128)a[7];
  *(_QWORD *)&c1j = __CFADD__(*((_QWORD *)&v67 + 1), *((_QWORD *)&v67 + 1)) + (_QWORD)v66;
  *(_QWORD *)&v66 = a[3] * a[7];
  *((_QWORD *)&v66 + 1) = 2LL * *((_QWORD *)&v67 + 1);
  v68 = v66 + (unsigned __int64)v67 + (unsigned __int64)v65;
  v69 = v68;
  v70 = __PAIR128__(*((unsigned __int64 *)&v68 + 1), c1j);
  *(_QWORD *)&v70 = __CFADD__(*((_QWORD *)&v70 + 1), c3p) + (_QWORD)v70;
  c3q = *((_QWORD *)&v70 + 1) + c3p;
  *(_QWORD *)&c1j = v70;
  r[10] = v69;
  v71 = a[4] * (unsigned __int128)a[7];
  *(_QWORD *)&v70 = a[4] * a[7];
  *((_QWORD *)&v70 + 1) = 2LL * *((_QWORD *)&v71 + 1);
  v72 = v70 + (unsigned __int64)v71 + c3q;
  *(_QWORD *)&v70 = __CFADD__(*((_QWORD *)&v72 + 1), (_QWORD)c1j)
                  + ((2 * (unsigned __int128)*((unsigned __int64 *)&v71 + 1)) >> 64);
  *(_QWORD *)&c1j = *((_QWORD *)&v72 + 1) + c1j;
  v73 = a[5] * (unsigned __int128)a[6];
  c2m = __CFADD__(*((_QWORD *)&v73 + 1), *((_QWORD *)&v73 + 1)) + (_QWORD)v70;
  *(_QWORD *)&v70 = a[5] * a[6];
  *((_QWORD *)&v70 + 1) = 2LL * *((_QWORD *)&v73 + 1);
  v74 = v70 + (unsigned __int64)v73 + (unsigned __int64)v72;
  *(_QWORD *)&v70 = __CFADD__(*((_QWORD *)&v74 + 1), (_QWORD)c1j) + c2m;
  *(_QWORD *)&c1j = *((_QWORD *)&v74 + 1) + c1j;
  r[11] = v74;
  *((_QWORD *)&c1j + 1) = (a[6] * (unsigned __int128)a[6]) >> 64;
  c1k = c1j + a[6] * a[6];
  v75 = *((unsigned __int64 *)&c1k + 1) + (unsigned __int128)(unsigned __int64)v70;
  c2n = *((_QWORD *)&c1k + 1) + v70;
  v76 = a[5] * (unsigned __int128)a[7];
  *(_QWORD *)&v70 = a[5] * a[7];
  *((_QWORD *)&v70 + 1) = 2LL * *((_QWORD *)&v76 + 1);
  *((_QWORD *)&c1k + 1) = (v70 + (unsigned __int64)v76) >> 64;
  c1l = c1k + (unsigned __int64)(v70 + v76);
  *(_QWORD *)&v70 = __CFADD__(*((_QWORD *)&c1l + 1), c2n)
                  + __CFADD__(*((_QWORD *)&v76 + 1), *((_QWORD *)&v76 + 1))
                  + *((_QWORD *)&v75 + 1);
  c2o = *((_QWORD *)&c1l + 1) + c2n;
  c3r = v70;
  r[12] = c1l;
  v77 = a[6] * (unsigned __int128)a[7];
  *(_QWORD *)&v70 = a[6] * a[7];
  *((_QWORD *)&v70 + 1) = 2LL * *((_QWORD *)&v77 + 1);
  v78 = v70 + (unsigned __int64)v77;
  v79 = __PAIR128__((v78 + c2o) >> 64, (2 * (unsigned __int128)*((unsigned __int64 *)&v77 + 1)) >> 64);
  *(_QWORD *)&v79 = __CFADD__(*((_QWORD *)&v79 + 1), c3r) + (_QWORD)v79;
  c3s = ((v78 + c2o) >> 64) + c3r;
  r[13] = v78 + c2o;
  v80 = a[7] * (unsigned __int128)a[7];
  r[14] = v80 + c3s;
  r[15] = ((v80 + c3s) >> 64) + v79;
}