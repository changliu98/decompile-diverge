void __cdecl bn_sqr_comba4(unsigned __int64 *r, const unsigned __int64 *a)
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
  unsigned __int64 v30; // rcx
  unsigned __int128 v31; // kr110_16
  unsigned __int128 v32; // kr120_16
  unsigned __int64 c3; // [rsp+A0h] [rbp-28h]
  unsigned __int64 c3a; // [rsp+A0h] [rbp-28h]
  unsigned __int64 c3b; // [rsp+A0h] [rbp-28h]
  unsigned __int64 c3c; // [rsp+A0h] [rbp-28h]
  unsigned __int64 c3d; // [rsp+A0h] [rbp-28h]
  unsigned __int64 c2; // [rsp+A8h] [rbp-20h]
  unsigned __int64 c2a; // [rsp+A8h] [rbp-20h]
  unsigned __int64 c2b; // [rsp+A8h] [rbp-20h]
  unsigned __int64 c2c; // [rsp+A8h] [rbp-20h]
  unsigned __int64 c2d; // [rsp+A8h] [rbp-20h]
  unsigned __int64 c2e; // [rsp+A8h] [rbp-20h]
  unsigned __int64 c1; // [rsp+B0h] [rbp-18h]
  unsigned __int64 c1a; // [rsp+B0h] [rbp-18h]
  unsigned __int64 c1b; // [rsp+B0h] [rbp-18h]
  unsigned __int64 c1c; // [rsp+B0h] [rbp-18h]
  unsigned __int64 c1d; // [rsp+B0h] [rbp-18h]
  unsigned __int64 c1e; // [rsp+B0h] [rbp-18h]
  unsigned __int64 c1f; // [rsp+B0h] [rbp-18h]

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
  v31 = v27 + __PAIR128__(v28, c2e);
  v30 = (v27 + __PAIR128__(v28, c2e)) >> 64;
  c1f = (v8 | (unsigned __int8)__CFADD__(*((_QWORD *)&v27 + 1), v30)) + v29;
  r[4] = v31;
  v32 = a[2] * (unsigned __int128)a[3];
  r[5] = v32 + v32 + v30;
  *((_OWORD *)r + 3) = a[3] * (unsigned __int128)a[3]
                     + __PAIR128__(
                         (__CFADD__(__CFADD__((_QWORD)v32, v32 + v30), (v32 + __PAIR128__(c1f, v30)) >> 64) | (unsigned __int8)__CFADD__(*((_QWORD *)&v32 + 1), (v32 + v32 + __PAIR128__(c1f, v30)) >> 64))
                       + (unsigned __int64)(__CFADD__(__CFADD__((_QWORD)v32, v30), c1f) | (unsigned __int8)__CFADD__(*((_QWORD *)&v32 + 1), (v32 + __PAIR128__(c1f, v30)) >> 64)),
                         (v32 + v32 + __PAIR128__(c1f, v30)) >> 64);
}