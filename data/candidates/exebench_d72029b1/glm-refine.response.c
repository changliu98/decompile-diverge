void __cdecl test1(short n, int *x)
{
  for (short i = 0; i < n; i += 1)
  {
    x[i + 1] = 0;
  }
}