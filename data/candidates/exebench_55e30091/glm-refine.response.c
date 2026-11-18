void __cdecl BGBBTJ_BC7_EncodeBlock_VecSwapA(int *clra, int *clrb)
{
  int temp = clra[3];
  clra[3] = clrb[3];
  clrb[3] = temp;
}