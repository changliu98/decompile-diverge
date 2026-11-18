void __cdecl BGBBTJ_BC7_EncodeBlock_VecSwapB(int *clra, int *clrb)
{
  int t; // [rsp+0h] [rbp-14h]

  t = clra[2];
  clra[2] = clrb[2];
  clrb[2] = t;
}