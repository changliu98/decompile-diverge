void __cdecl BGBBTJ_BC7_EncodeBlock_VecSwapRGB(int *clra, int *clrb)
{
  int t;

  // Swap Red (Index 0)
  t = clra[0];
  clra[0] = clrb[0];
  clrb[0] = t;

  // Swap Green (Index 1)
  t = clra[1];
  clra[1] = clrb[1];
  clrb[1] = t;

  // Swap Blue (Index 2)
  t = clra[2];
  clra[2] = clrb[2];
  clrb[2] = t;
}