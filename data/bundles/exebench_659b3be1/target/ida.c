void __cdecl bitrv208(float *a)
{
  int x6i; // [rsp+0h] [rbp-28h]
  int x6r; // [rsp+4h] [rbp-24h]
  int x4i; // [rsp+8h] [rbp-20h]
  int x3i; // [rsp+10h] [rbp-18h]
  int x3r; // [rsp+14h] [rbp-14h]
  int x1i; // [rsp+18h] [rbp-10h]
  int x1r; // [rsp+1Ch] [rbp-Ch]

  x1r = *((_DWORD *)a + 2);
  x1i = *((_DWORD *)a + 3);
  x3r = *((_DWORD *)a + 6);
  x3i = *((_DWORD *)a + 7);
  x4i = *((_DWORD *)a + 9);
  x6r = *((_DWORD *)a + 12);
  x6i = *((_DWORD *)a + 13);
  a[2] = a[8];
  *((_DWORD *)a + 3) = x4i;
  *((_DWORD *)a + 6) = x6r;
  *((_DWORD *)a + 7) = x6i;
  *((_DWORD *)a + 8) = x1r;
  *((_DWORD *)a + 9) = x1i;
  *((_DWORD *)a + 12) = x3r;
  *((_DWORD *)a + 13) = x3i;
}