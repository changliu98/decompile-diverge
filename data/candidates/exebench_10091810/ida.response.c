void __cdecl BGBBTJ_BC7_EncodeBlock_VecSwapRGB(int *clra, int *clrb)
{
  int t; // [rsp+0h] [rbp-14h]
  int ta; // [rsp+0h] [rbp-14h]
  int tb; // [rsp+0h] [rbp-14h]

  t = *clra;
  *clra = *clrb;
  *clrb = t;
  ta = clra[1];
  clra[1] = clrb[1];
  clrb[1] = ta;
  tb = clra[2];
  clra[2] = clrb[2];
  clrb[2] = tb;
}