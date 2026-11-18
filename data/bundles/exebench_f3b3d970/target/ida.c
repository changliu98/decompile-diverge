void __cdecl bitrv208(double *a)
{
  __int64 x6i; // [rsp+0h] [rbp-48h]
  __int64 x6r; // [rsp+8h] [rbp-40h]
  __int64 x4i; // [rsp+10h] [rbp-38h]
  __int64 x3i; // [rsp+20h] [rbp-28h]
  __int64 x3r; // [rsp+28h] [rbp-20h]
  __int64 x1i; // [rsp+30h] [rbp-18h]
  __int64 x1r; // [rsp+38h] [rbp-10h]

  x1r = *((_QWORD *)a + 2);
  x1i = *((_QWORD *)a + 3);
  x3r = *((_QWORD *)a + 6);
  x3i = *((_QWORD *)a + 7);
  x4i = *((_QWORD *)a + 9);
  x6r = *((_QWORD *)a + 12);
  x6i = *((_QWORD *)a + 13);
  a[2] = a[8];
  *((_QWORD *)a + 3) = x4i;
  *((_QWORD *)a + 6) = x6r;
  *((_QWORD *)a + 7) = x6i;
  *((_QWORD *)a + 8) = x1r;
  *((_QWORD *)a + 9) = x1i;
  *((_QWORD *)a + 12) = x3r;
  *((_QWORD *)a + 13) = x3i;
}