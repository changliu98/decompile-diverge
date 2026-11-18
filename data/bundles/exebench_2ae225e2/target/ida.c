void __cdecl make_double_bigendian(double *x)
{
  union {double d;unsigned __int8 b[8];} v; // [rsp+0h] [rbp-18h]

  v.b[0] = HIBYTE(*(_QWORD *)x);
  v.b[1] = BYTE6(*(_QWORD *)x);
  v.b[2] = (unsigned __int16)WORD2(*(_QWORD *)x) >> 8;
  v.b[3] = BYTE4(*(_QWORD *)x);
  v.b[4] = BYTE3(*(_QWORD *)x);
  v.b[5] = BYTE2(*(_QWORD *)x);
  v.b[6] = BYTE1(*(_QWORD *)x);
  v.b[7] = *(_QWORD *)x;
  *x = v.d;
}