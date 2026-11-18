void __cdecl Mat4_T(float *mat)
{
  int t; // [rsp+0h] [rbp-Ch]
  int ta; // [rsp+0h] [rbp-Ch]
  int tb; // [rsp+0h] [rbp-Ch]
  int tc; // [rsp+0h] [rbp-Ch]
  int td; // [rsp+0h] [rbp-Ch]
  int te; // [rsp+0h] [rbp-Ch]

  t = *((_DWORD *)mat + 1);
  mat[1] = mat[4];
  *((_DWORD *)mat + 4) = t;
  ta = *((_DWORD *)mat + 2);
  mat[2] = mat[8];
  *((_DWORD *)mat + 8) = ta;
  tb = *((_DWORD *)mat + 3);
  mat[3] = mat[12];
  *((_DWORD *)mat + 12) = tb;
  tc = *((_DWORD *)mat + 6);
  mat[6] = mat[9];
  *((_DWORD *)mat + 9) = tc;
  td = *((_DWORD *)mat + 7);
  mat[7] = mat[13];
  *((_DWORD *)mat + 13) = td;
  te = *((_DWORD *)mat + 11);
  mat[11] = mat[14];
  *((_DWORD *)mat + 14) = te;
}