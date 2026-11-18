void __cdecl BGBBTJ_BC7_EncodeBlock_VecSwapB(int *clra, int *clrb)
{
  int temp = clra[2];
  clra[2] = clrb[2];
  clrb[2] = temp;
}