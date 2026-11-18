void __cdecl BGBBTJ_BC7_EncodeBlock_VecSwapA(int *clra, int *clrb)
{
  int t; // [rsp+0h] [rbp-14h]

  t = clra[3];
  clra[3] = clrb[3];
  clrb[3] = t;
}