void __cdecl arrayadd(int *src, int *dst)
{
  for (int i = 0; i < 50; ++i)
  {
    dst[i] = src[i] + 5;
  }
}