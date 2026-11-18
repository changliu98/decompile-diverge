void __cdecl bn_mul_comba4(unsigned __int64 *r, unsigned __int64 *a, unsigned __int64 *b)
{
  unsigned __int128 v3; // kr00_16
  unsigned __int128 v4; // rax
  unsigned __int128 v5; // kr30_16
  unsigned __int128 v6; // rax
  unsigned __int128 v7; // kr40_16
  unsigned __int128 v8; // rax
  unsigned __int128 v9; // kr80_16
  unsigned __int128 v10; // krE0_16
  unsigned __int128 v11; // kr10_16
  unsigned __int128 v12; // kr110_16
  unsigned __int128 v13; // kr20_16
  unsigned __int128 v14; // kr140_16
  unsigned __int128 v15; // kr50_16
  unsigned __int128 v16; // kr60_16
  unsigned __int128 v17; // kr70_16
  unsigned __int64 v18; // kr1D0_8
  unsigned __int128 v19; // rax
  unsigned __int128 v20; // rax
  unsigned __int128 v21; // kr250_16
  unsigned __int128 v22; // kr2B0_16
  unsigned __int128 v23; // kr90_16
  unsigned __int64 c3; // [rsp+0h] [rbp-50h]
  unsigned __int64 c3a; // [rsp+0h] [rbp-50h]
  unsigned __int64 c3b; // [rsp+0h] [rbp-50h]
  unsigned __int64 c3c; // [rsp+0h] [rbp-50h]
  unsigned __int64 c3d; // [rsp+0h] [rbp-50h]
  unsigned __int64 c3e; // [rsp+0h] [rbp-50h]
  unsigned __int64 c2; // [rsp+8h] [rbp-48h]
  unsigned __int64 c2a; // [rsp+8h] [rbp-48h]
  unsigned __int64 c2b; // [rsp+8h] [rbp-48h]
  unsigned __int64 c2c; // [rsp+8h] [rbp-48h]
  unsigned __int64 c1; // [rsp+10h] [rbp-40h]
  __int128 c1a; // [rsp+10h] [rbp-40h]
  __int128 c1b; // [rsp+10h] [rbp-40h]
  __int128 c1c; // [rsp+10h] [rbp-40h]
  __int128 c1d; // [rsp+10h] [rbp-40h]
  __int128 c1e; // [rsp+10h] [rbp-40h]
  unsigned __int64 t1; // [rsp+20h] [rbp-30h]

  v3 = *b * (unsigned __int128)*a + 0;
  c3 = (*((unsigned __int64 *)&v3 + 1) + (unsigned __int128)0LL) >> 64;
  *r = *b * *a;
  v4 = b[1] * (unsigned __int128)*a + *((unsigned __int64 *)&v3 + 1);
  v5 = v4;
  v6 = __PAIR128__(*((unsigned __int64 *)&v4 + 1), 0LL);
  v7 = *((unsigned __int64 *)&v6 + 1) + (unsigned __int128)c3;
  c3a = *((_QWORD *)&v6 + 1) + c3;
  v8 = __PAIR128__((*b * (unsigned __int128)a[1] + (unsigned __int64)v5) >> 64, *((unsigned __int64 *)&v7 + 1));
  *(_QWORD *)&v8 = __CFADD__(*((_QWORD *)&v8 + 1), c3a) + (_QWORD)v8;
  c3b = ((*b * (unsigned __int128)a[1] + (unsigned __int64)v5) >> 64) + c3a;
  r[1] = *b * a[1] + v5;
  v9 = *b * (unsigned __int128)a[2];
  v10 = b[1] * (unsigned __int128)a[1] + (unsigned __int64)v9 + c3b;
  v11 = *((unsigned __int64 *)&v10 + 1) + ((v9 + c3b) >> 64) + (unsigned __int64)v8;
  *(_QWORD *)&v8 = v11 >> 64;
  c1 = v11;
  v12 = b[2] * (unsigned __int128)*a + (unsigned __int64)v10;
  v13 = *((unsigned __int64 *)&v12 + 1) + __PAIR128__(v8, c1);
  *(_QWORD *)&v8 = v13 >> 64;
  *(_QWORD *)&c1a = v13;
  r[2] = v12;
  *((_QWORD *)&c1a + 1) = (b[3] * (unsigned __int128)*a) >> 64;
  c1b = c1a + b[3] * *a;
  v14 = *((unsigned __int64 *)&c1b + 1) + (unsigned __int128)(unsigned __int64)v8;
  c2 = *((_QWORD *)&c1b + 1) + v8;
  *((_QWORD *)&c1b + 1) = (b[2] * (unsigned __int128)a[1]) >> 64;
  c1c = c1b + b[2] * a[1];
  v15 = *((unsigned __int64 *)&c1c + 1) + __PAIR128__(*((unsigned __int64 *)&v14 + 1), c2);
  *(_QWORD *)&v8 = v15 >> 64;
  c2a = v15;
  *((_QWORD *)&c1c + 1) = (b[1] * (unsigned __int128)a[2]) >> 64;
  c1d = c1c + b[1] * a[2];
  v16 = *((unsigned __int64 *)&c1d + 1) + __PAIR128__(v8, c2a);
  *(_QWORD *)&v8 = v16 >> 64;
  c2b = v16;
  *((_QWORD *)&c1d + 1) = (*b * (unsigned __int128)a[3]) >> 64;
  c1e = c1d + *b * a[3];
  v17 = *((unsigned __int64 *)&c1e + 1) + __PAIR128__(v8, c2b);
  *(_QWORD *)&v8 = v17 >> 64;
  c2c = v17;
  r[3] = c1e;
  v18 = b[1] * a[3] + c2c;
  c3c = ((b[1] * (unsigned __int128)a[3] + c2c) >> 64) + v8;
  v19 = __PAIR128__(
          (b[2] * (unsigned __int128)a[2] + v18) >> 64,
          (((b[1] * (unsigned __int128)a[3] + c2c) >> 64) + (unsigned __int64)v8) >> 64);
  *(_QWORD *)&v19 = __CFADD__(*((_QWORD *)&v19 + 1), c3c) + (_QWORD)v19;
  c3d = ((b[2] * (unsigned __int128)a[2] + v18) >> 64) + c3c;
  v20 = __PAIR128__((b[3] * (unsigned __int128)a[1] + b[2] * a[2] + v18) >> 64, v19);
  *(_QWORD *)&v20 = __CFADD__(*((_QWORD *)&v20 + 1), c3d) + (_QWORD)v20;
  c3e = *((_QWORD *)&v20 + 1) + c3d;
  r[4] = b[3] * a[1] + b[2] * a[2] + v18;
  v21 = b[3] * (unsigned __int128)a[2];
  v22 = b[2] * (unsigned __int128)a[3] + (unsigned __int64)v21 + c3e;
  v23 = *((unsigned __int64 *)&v22 + 1) + ((v21 + c3e) >> 64) + (unsigned __int64)v20;
  *(_QWORD *)&v20 = v23 >> 64;
  *(_QWORD *)&c1e = v23;
  r[5] = v22;
  *((_QWORD *)&c1e + 1) = (b[3] * (unsigned __int128)a[3]) >> 64;
  t1 = b[3] * a[3];
  r[6] = t1 + c1e;
  r[7] = ((c1e + (unsigned __int128)t1) >> 64) + v20;
}