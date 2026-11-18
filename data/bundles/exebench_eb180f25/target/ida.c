double __cdecl Mat_doubleSwap(double *a)
{
  union {char a[8];double b;} tmp; // [rsp+0h] [rbp-10h]

  tmp.a[7] = *(_QWORD *)a;
  tmp.a[0] = HIBYTE(*(_QWORD *)a);
  tmp.a[6] = BYTE1(*(_QWORD *)a);
  tmp.a[1] = BYTE6(*(_QWORD *)a);
  tmp.a[5] = BYTE2(*(_QWORD *)a);
  tmp.a[2] = (unsigned __int16)WORD2(*(_QWORD *)a) >> 8;
  tmp.a[4] = BYTE3(*(_QWORD *)a);
  tmp.a[3] = BYTE4(*(_QWORD *)a);
  *a = tmp.b;
  return *a;
}